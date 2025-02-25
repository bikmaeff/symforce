// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     matrix_multiplication_benchmark.cc.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

///
/// Experiment to show timing for the matrix multiplication example in the SymForce paper.
///
/// Run with:
///
///     build/bin/benchmarks/matrix_multiplication_benchmark_lp_sc105
///
/// See run_matmul_benchmarks.py for more information
///

#include <chrono>
#include <thread>

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <spdlog/spdlog.h>

#include <symforce/opt/tic_toc.h>
#include <symforce/opt/util.h>

#include "catch.hpp"

using namespace sym;

#include "./compute_a_dense_dynamic_lp_sc105.h"
#include "./compute_a_dense_lp_sc105.h"
#include "./compute_a_lp_sc105.h"
#include "./compute_at_b_lp_sc105.h"
#include "./compute_b_dense_dynamic_lp_sc105.h"
#include "./compute_b_dense_lp_sc105.h"
#include "./compute_b_lp_sc105.h"

template <typename Scalar>
__attribute__((noinline)) Eigen::Matrix<Scalar, 163, 163> ComputeDenseFixedLpSc105(
    const Scalar x0, const Scalar x1, const Scalar x2, const Scalar x3, const Scalar x4) {
  Eigen::Matrix<Scalar, 105, 163> A = ComputeADenseLpSc105<Scalar>(x0, x1, x2, x3, x4);
  Eigen::Matrix<Scalar, 105, 163> B = ComputeBDenseLpSc105<Scalar>(x0, x1, x2, x3, x4);
  return A.transpose() * B;
}

template <typename Scalar>
__attribute__((noinline)) Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>
ComputeDenseDynamicLpSc105(const Scalar x0, const Scalar x1, const Scalar x2, const Scalar x3,
                           const Scalar x4) {
  const auto A = ComputeADenseDynamicLpSc105<Scalar>(x0, x1, x2, x3, x4);
  const auto B = ComputeBDenseDynamicLpSc105<Scalar>(x0, x1, x2, x3, x4);
  return A.transpose() * B;
}

template <typename Scalar>
__attribute__((noinline)) Eigen::SparseMatrix<Scalar> ComputeSparseLpSc105(
    const Scalar x0, const Scalar x1, const Scalar x2, const Scalar x3, const Scalar x4) {
  Eigen::SparseMatrix<Scalar> A = ComputeALpSc105<Scalar>(x0, x1, x2, x3, x4);
  Eigen::SparseMatrix<Scalar> B = ComputeBLpSc105<Scalar>(x0, x1, x2, x3, x4);
  return A.transpose() * B;
}

// ----------------------------------------------------------------------------
// Test Cases
// ----------------------------------------------------------------------------

TEMPLATE_TEST_CASE("sparse_lp_sc105", "", double, float) {
  using Scalar = TestType;

  fmt::print("n_runs_multiplier: {};\n", 10.0);

  const Scalar x2 = 1.0;
  const Scalar x3 = 2.0;
  const Scalar x4 = 3.0;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("sparse_lp_sc105_{}", typeid(Scalar).name());

    for (Scalar x0 = 0.1; x0 < 10.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 10.0; x1 += 0.1) {
        auto mat = ComputeSparseLpSc105(x0, x1, x2, x3, x4);
        sum += mat.valuePtr()[0];
      }
    }
  }
}

TEMPLATE_TEST_CASE("dense_dynamic_lp_sc105", "", double, float) {
  using Scalar = TestType;

  fmt::print("n_runs_multiplier: {};\n", 10.0);

  const Scalar x2 = 1.0;
  const Scalar x3 = 2.0;
  const Scalar x4 = 3.0;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("dense_dynamic_lp_sc105_{}", typeid(Scalar).name());
    for (Scalar x0 = 0.1; x0 < 10.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 10.0; x1 += 0.1) {
        auto mat = ComputeDenseDynamicLpSc105<Scalar>(x0, x1, x2, x3, x4);
        sum += mat(0, 0);
      }
    }
  }
}

TEMPLATE_TEST_CASE("flattened_lp_sc105", "", double, float) {
  using Scalar = TestType;

  fmt::print("n_runs_multiplier: {};\n", 10.0);

  const Scalar x2 = 1.0;
  const Scalar x3 = 2.0;
  const Scalar x4 = 3.0;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("flattened_lp_sc105_{}", typeid(Scalar).name());
    for (Scalar x0 = 0.1; x0 < 10.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 10.0; x1 += 0.1) {
        auto mat = ComputeAtBLpSc105(x0, x1, x2, x3, x4);
        sum += mat.valuePtr()[0];
      }
    }
  }
}
