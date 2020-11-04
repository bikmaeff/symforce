#include "./values.h"

#include "./assert.h"

namespace sym {

template <typename Scalar>
Values<Scalar>::Values() {}

template <typename Scalar>
Values<Scalar>::Values(std::initializer_list<Values<Scalar>> others) {
  for (const auto& other : others) {
    // add in the Keys with a different offset
    const size_t offset = data_.size();
    for (const auto& it : other.map_) {
      SYM_ASSERT(map_.find(it.first) == map_.end());
      map_[it.first] = it.second;
      map_[it.first].offset += offset;
    }

    // copy data from other Values
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
  }
}

template <typename Scalar>
Values<Scalar>::Values(const LcmType& msg) {
  for (const index_entry_t& entry : msg.index.entries) {
    map_[entry.key] = entry;
  }
  data_ = msg.data;
}

template <typename Scalar>
bool Values<Scalar>::Has(const Key& key) const {
  return map_.find(key) != map_.end();
}

template <typename Scalar>
void Values<Scalar>::UpdateOrSet(const index_t& index, const Values<Scalar>& other) {
  for (const auto& entry_other : index.entries) {
    const auto offset_other = other.data_.template begin() + entry_other.offset;
    const Key key(entry_other.key);
    auto it = map_.find(key);
    // insert keys if not existed
    if (it == map_.end()) {
      it = map_.emplace(key, index_entry_t{}).first;
      index_entry_t& entry_this = it->second;
      entry_this = entry_other;
      entry_this.offset = static_cast<int32_t>(data_.size());
      // extend end of data
      data_.insert(data_.end(), offset_other, offset_other + entry_other.storage_dim);
    } else {
      std::copy_n(offset_other, entry_other.storage_dim,
                  data_.template begin() + it->second.offset);
    }
  }
}

template <typename Scalar>
int32_t Values<Scalar>::NumEntries() const {
  return map_.size();
}

template <typename Scalar>
std::vector<Key> Values<Scalar>::Keys(const bool sort_by_offset) const {
  std::vector<Key> keys;
  keys.reserve(map_.size());
  for (const auto& kv : map_) {
    keys.push_back(kv.first);
  }

  // Sort the keys by offset so iterating through is saner and more memory friendly
  if (sort_by_offset) {
    std::sort(keys.begin(), keys.end(), [&](const sym::Key& a, const sym::Key& b) {
      return map_.at(a).offset < map_.at(b).offset;
    });
  }

  return keys;
}

template <typename Scalar>
const typename Values<Scalar>::MapType& Values<Scalar>::Items() const {
  return map_;
}

template <typename Scalar>
const typename Values<Scalar>::ArrayType& Values<Scalar>::Data() const {
  return data_;
}

template <typename Scalar>
bool Values<Scalar>::Remove(const Key& key) {
  size_t num_removed = map_.erase(key);
  return static_cast<bool>(num_removed);
}

template <typename Scalar>
void Values<Scalar>::RemoveAll() {
  map_.clear();
  data_.clear();
}

template <typename Scalar>
size_t Values<Scalar>::Cleanup() {
  // Copy the original data
  const ArrayType data_copy = data_;

  // Build an index of all keys
  const index_t full_index = CreateIndex(Keys());

  // Re-allocate data to the appropriate size
  data_.resize(full_index.storage_dim);
  SYM_ASSERT(data_copy.size() >= data_.size());

  // Copy into new data and update the offset in the map
  size_t new_offset = 0;
  for (const index_entry_t& entry : full_index.entries) {
    std::copy_n(data_copy.begin() + entry.offset, entry.storage_dim, data_.begin() + new_offset);
    map_[entry.key].offset = new_offset;
    new_offset += entry.storage_dim;
  }

  return data_copy.size() - data_.size();
}

template <typename Scalar>
index_t Values<Scalar>::CreateIndex(const std::vector<Key>& keys) const {
  index_t index{};
  index.entries.reserve(keys.size());
  for (const Key& key : keys) {
    const index_entry_t& entry = map_.at(key);
    index.entries.push_back(entry);
    index.storage_dim += entry.storage_dim;
    index.tangent_dim += entry.tangent_dim;
  }
  return index;
}

template <typename Scalar>
void Values<Scalar>::FillLcmType(LcmType* msg) const {
  SYM_ASSERT(msg != nullptr);
  msg->index = CreateIndex(Keys());
  msg->data = data_;
}

template <typename Scalar>
typename Values<Scalar>::LcmType Values<Scalar>::GetLcmType() const {
  LcmType msg;
  FillLcmType(&msg);
  return msg;
}

template <typename Scalar>
void Values<Scalar>::Update(const index_t& index, const Values<Scalar>& other) {
  SYM_ASSERT(data_.size() == other.data_.size());
  for (const index_entry_t& entry : index.entries) {
    std::copy_n(other.data_.template begin() + entry.offset, entry.storage_dim,
                data_.template begin() + entry.offset);
  }
}

template <typename Scalar>
void Values<Scalar>::Update(const index_t& index_this, const index_t& index_other,
                            const Values<Scalar>& other) {
  SYM_ASSERT(index_this.entries.size() == index_other.entries.size());
  for (int i = 0; i < index_this.entries.size(); ++i) {
    const index_entry_t& entry_this = index_this.entries[i];
    const index_entry_t& entry_other = index_other.entries[i];
    SYM_ASSERT(entry_this.storage_dim == entry_other.storage_dim);
    SYM_ASSERT(entry_this.key == entry_other.key);
    std::copy_n(other.data_.template begin() + entry_other.offset, entry_this.storage_dim,
                data_.template begin() + entry_this.offset);
  }
}

/**
 * Polymorphic helper to apply a retraction.
 */
template <typename T, typename Scalar = typename geo::StorageOps<T>::Scalar>
void RetractHelper(const Scalar* tangent_data, const Scalar epsilon, Scalar* t_ptr) {
  const T t_in = geo::StorageOps<T>::FromStorage(t_ptr);
  const typename geo::LieGroupOps<T>::TangentVec tangent_vec(tangent_data);
  const T t_out = geo::LieGroupOps<T>::Retract(t_in, tangent_vec, epsilon);
  geo::StorageOps<T>::ToStorage(t_out, t_ptr);
}
BY_TYPE_HELPER(RetractByType, RetractHelper);

template <typename Scalar>
void Values<Scalar>::Retract(const index_t& index, const Scalar* delta, const Scalar epsilon) {
  size_t tangent_inx = 0;
  for (const index_entry_t& entry : index.entries) {
    RetractByType<Scalar>(entry.type, /* tangent_data */ delta + tangent_inx, epsilon,
                          /* t_ptr */ data_.data() + entry.offset);
    tangent_inx += entry.tangent_dim;
  }
}

/**
 * Polymorphic helper to compute local coordinates
 */
template <typename T, typename Scalar = typename geo::StorageOps<T>::Scalar>
void LocalCoordinatesHelper(const Scalar* storage_this, const Scalar* storage_others,
                            Scalar* tangent_out, const Scalar epsilon) {
  const T t1 = geo::StorageOps<T>::FromStorage(storage_this);
  const T t2 = geo::StorageOps<T>::FromStorage(storage_others);
  const typename geo::LieGroupOps<T>::TangentVec tangent_vec =
      geo::LieGroupOps<T>::LocalCoordinates(t2, t1, epsilon);
  // TODO(alvin): can we avoid this copy?
  std::copy_n(tangent_vec.data(), geo::LieGroupOps<T>::TangentDim(), tangent_out);
}
BY_TYPE_HELPER(LocalCoordinatesByType, LocalCoordinatesHelper);

template <typename Scalar>
VectorX<Scalar> Values<Scalar>::LocalCoordinates(const Values<Scalar>& others, const index_t& index,
                                                 const Scalar epsilon) {
  VectorX<Scalar> tangent_vec(index.tangent_dim);
  size_t tangent_inx = 0;

  for (const index_entry_t& entry : index.entries) {
    LocalCoordinatesByType<Scalar>(entry.type, data_.data() + entry.offset,
                                   others.data_.data() + entry.offset,
                                   tangent_vec.data() + tangent_inx, epsilon);
    tangent_inx += entry.tangent_dim;
  }

  return tangent_vec;
}

template <typename T>
void PrintHelper(std::ostream& os, const typename geo::StorageOps<T>::Scalar* data_ptr) {
  os << geo::StorageOps<T>::FromStorage(data_ptr);
}
BY_TYPE_HELPER(PrintByType, PrintHelper);

}  // namespace sym

// Explicit instantiation
template class sym::Values<double>;
template class sym::Values<float>;

// ----------------------------------------------------------------------------
// Printing
// ----------------------------------------------------------------------------

template <typename Scalar>
std::ostream& operator<<(std::ostream& os, const sym::Values<Scalar>& v) {
  // Make an index so we iterate through in offset order
  const sym::index_t index = v.CreateIndex(v.Keys(/* sort by offset */ true));

  // Print header
  os << "<Values" << typeid(Scalar).name() << " entries=" << index.entries.size()
     << " array=" << v.Data().size() << " storage_dim=" << index.storage_dim
     << " tangent_dim=" << index.tangent_dim << std::endl;

  // Print each element
  for (const sym::index_entry_t& entry : index.entries) {
    os << "  " << sym::Key(entry.key) << " [" << entry.offset << ":"
       << entry.offset + entry.storage_dim << "] --> ";
    sym::PrintByType<Scalar>(entry.type, os, v.Data().data() + entry.offset);
    os << std::endl;
  }

  os << ">";
  return os;
}

template std::ostream& operator<<<float>(std::ostream& os, const sym::Values<float>& v);
template std::ostream& operator<<<double>(std::ostream& os, const sym::Values<double>& v);
