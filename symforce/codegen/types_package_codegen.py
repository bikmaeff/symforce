# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

import os
import numpy as np
import tempfile

from symforce import sympy as sm
from symforce import logger
from symforce import typing as T
from symforce.values import Values, IndexEntry
from symforce.codegen import template_util
from symforce.codegen import codegen_util


def generate_types(
    package_name: str,
    file_name: str,
    values_indices: T.Mapping[str, T.Dict[str, IndexEntry]],
    use_eigen_types: bool,
    shared_types: T.Mapping[str, str] = None,
    scalar_type: str = "double",
    output_dir: T.Openable = None,
    lcm_bindings_output_dir: T.Openable = None,
    templates: template_util.TemplateList = None,
) -> T.Dict[str, T.Any]:
    """
    Generates LCM types from the given values_indices, including the necessary subtypes
    and references to external LCM types.

    Args:
        package_name: Package of LCM types to be generated
        file_name: Name of the LCM file to generate (without the extension)
        values_indices: Mapping between the name each LCM type to be generated and its index (computed using Values.index())
        shared_types: Used to specify whether specific types and subtypes have already been generated, either externally or internally
            (i.e. if one generated type is to represent multiple objects in values_indices).
            Usage examples:
                shared_types={"my_values" : "external_package.my_values"} (Reuse the implementation of "my_values" defined in package
                    "external_package", meaning that "my_values" as defined in values_indices will not be generated. Note
                    that "external_package" can equal package_name, e.g. when generating multiple functions in the same package which
                    reuse the same types)
                shared_types={"my_values.V1" : "my_subvalues_t", "my_values.V2" : "my_subvalues_t"} (Only generate one type named
                    "my_subvalues_t" to represent Values objects defined by "my_values.V1" and "my_values.V2".
        scalar_type: Type of scalars used in LCM type definition
        output_dir: Where to output the files. ".lcm" files are output in "output_dir/lcmtypes", and language-specific implementations
            are generated in "output_dir/package_name".
        lcm_bindings_output_dir: Where to output language-specific LCM bindings.  Defaults to output_dir
        templates: TemplateList used if types are being generated as part of a larger code generation (e.g. when generating the
            types required by a generated function). If None, we generate both the ".lcm" files and the language-specific
            implementations, else we assume the templates and language-specific type implementations will be rendered
            in an external function.
    """
    # Create output directory if needed
    if output_dir is None:
        output_dir = tempfile.mkdtemp(prefix=f"sf_codegen_types_{package_name}_", dir="/tmp")
        logger.debug(f"Creating temp directory: {output_dir}")
    lcm_type_dir = os.path.join(output_dir, "lcmtypes")

    using_external_templates = True
    if templates is None:
        # List of (template_path, output_path, data)
        templates = template_util.TemplateList()
        using_external_templates = False

    types_dict = build_types_dict(
        package_name=package_name, values_indices=values_indices, shared_types=shared_types
    )

    # Default data for templates
    data = {
        "T": T,
        "Values": Values,
        "list": list,
        "tuple": tuple,
        "issubclass": issubclass,
        "name": package_name,
        "scalar_type": scalar_type,
        "types_dict": types_dict,
        "to_set": set,
        "DataBuffer": sm.DataBuffer,
    }

    types_util = {"np.prod": np.prod}

    types_to_generate = []
    for typename in types_dict:
        # If a module is specified, this type is external - don't generate it
        if "." in typename:
            continue
        types_to_generate.append(typename)

    lcm_files = []
    if len(types_to_generate) > 0:
        logger.info(f'Creating LCM type at: "{lcm_type_dir}"')
        lcm_template = os.path.join(template_util.LCM_TEMPLATE_DIR, "types.lcm.jinja")

        # Type definition
        lcm_file_name = f"{file_name}.lcm"
        lcm_files.append(lcm_file_name)
        templates.add(
            lcm_template,
            os.path.join(lcm_type_dir, lcm_file_name),
            dict(
                data,
                types_to_generate=types_to_generate,
                types_util=types_util,
                use_eigen_types=use_eigen_types,
            ),
        )

    # Save input args for handy reference
    codegen_data: T.Dict[str, T.Any] = {}
    codegen_data["package_name"] = package_name
    codegen_data["values_indices"] = values_indices
    codegen_data["shared_types"] = shared_types
    codegen_data["scalar_type"] = scalar_type

    # Save outputs and intermediates
    codegen_data["output_dir"] = output_dir
    codegen_data["lcm_type_dir"] = lcm_type_dir
    codegen_data["lcm_bindings_output_dir"] = lcm_bindings_output_dir
    codegen_data["lcm_files"] = lcm_files
    codegen_data["types_dict"] = types_dict

    # Save mapping between names of types and their namespace/typename. This is used, e.g.,
    # to get the namespace of a type (whether internal or external) from the name of the variable
    # when generating code.
    # TODO(nathan): Not sure if all edge cases are caught in the following, could probably clean this up some
    codegen_data["typenames_dict"] = {}  # Maps typenames to generated types
    codegen_data["namespaces_dict"] = {}  # Maps typenames to namespaces
    for name in values_indices.keys():
        # Record namespace/typenames for top-level types. If the type is external, we get the
        # namespace and typename from shared_types.
        if shared_types is not None and name in shared_types:
            codegen_data["typenames_dict"][name] = shared_types[name].split(".")[-1]
            if "." in shared_types[name]:
                codegen_data["namespaces_dict"][name] = shared_types[name].split(".")[0]
            else:
                codegen_data["namespaces_dict"][name] = package_name
        else:
            codegen_data["typenames_dict"][name] = f"{name}_t"
            codegen_data["namespaces_dict"][name] = package_name
    for typename, data in types_dict.items():
        # Iterate through types in types_dict. If type is external, use the shared_types to
        # get the namespace.
        unformatted_typenames = T.cast(T.List[str], data["unformatted_typenames"])
        for unformatted_typename in unformatted_typenames:
            name = unformatted_typename.split(".")[-1]
            if shared_types is not None and name in shared_types:
                name = shared_types[name]
            if "." in name:
                codegen_data["typenames_dict"][name] = name.split(".")[-1]
                codegen_data["namespaces_dict"][name] = name.split(".")[0]
            else:
                codegen_data["typenames_dict"][name] = f"{name}_t"
                codegen_data["namespaces_dict"][name] = package_name

    if not using_external_templates:
        templates.render()
        lcm_data = codegen_util.generate_lcm_types(lcm_type_dir, lcm_files, lcm_bindings_output_dir)
        codegen_data.update(lcm_data)

    return codegen_data


def build_types_dict(
    package_name: str,
    values_indices: T.Mapping[str, T.Dict[str, IndexEntry]],
    shared_types: T.Optional[T.Mapping[str, str]] = None,
) -> T.Dict[str, T.Dict[str, T.Any]]:
    """
    Compute the structure of the types we need to generate for the given Values.
    """
    if shared_types is None:
        shared_types = {}

    types_dict: T.Dict[str, T.Dict[str, T.Any]] = {}

    for key, index in values_indices.items():
        _fill_types_dict_recursive(
            key=key,
            index=index,
            package_name=package_name,
            shared_types=shared_types,
            types_dict=types_dict,
        )

    return types_dict


def typename_from_key(key: str, shared_types: T.Mapping[str, str]) -> str:
    """
    Compute a typename from a key, or from shared_types if provided by the user.
    """
    return shared_types.get(key, key.replace(".", "_") + "_t")


def get_subvalues_from_list_index(
    list_index: T.Dict[str, IndexEntry]
) -> T.Optional[T.Dict[str, IndexEntry]]:
    """
    Returns index of Values object if base element of list is a Values object,
    otherwise returns None
    """
    index_element = list(list_index.values())[0]
    datatype = index_element.datatype()
    if issubclass(datatype, Values):
        assert index_element.item_index is not None
        return index_element.item_index
    elif issubclass(datatype, (list, tuple)):
        assert index_element.item_index is not None
        return get_subvalues_from_list_index(index_element.item_index)
    return None


def _fill_types_dict_recursive(
    key: str,
    index: T.Dict[str, IndexEntry],
    package_name: str,
    shared_types: T.Mapping[str, str],
    types_dict: T.Dict[str, T.Dict[str, T.Any]],
) -> None:
    """
    Recursively compute type information from the key and values index and fill into types_dict.
    """
    data: T.Dict[str, T.Any] = {}

    typename = typename_from_key(key, shared_types)
    data["typename"] = typename
    data["unformatted_typenames"] = [key]

    # Add the current module for cases where it's not specified
    data["full_typename"] = typename if "." in typename else ".".join([package_name, typename])

    data["index"] = index
    data["storage_dims"] = {key: info.storage_dim for key, info in index.items()}

    # Process child types
    data["subtypes"] = {}
    for subkey, entry in index.items():
        datatype = entry.datatype()
        if key in shared_types and "." in shared_types[key]:
            # This is a shared type. Don't generate any subtypes.
            continue
        if issubclass(datatype, Values):
            element_index = entry.item_index
        elif issubclass(datatype, (list, tuple)):
            assert entry.item_index is not None
            # Assumes all elements in list are the same type as the first
            element_index = get_subvalues_from_list_index(entry.item_index)
            if element_index is None:
                # Not a list of Values
                continue
        else:
            continue

        full_subkey = f"{key}.{subkey}"
        data["subtypes"][subkey] = typename_from_key(full_subkey, shared_types)

        assert element_index is not None
        _fill_types_dict_recursive(
            key=full_subkey,
            index=element_index,
            package_name=package_name,
            shared_types=shared_types,
            types_dict=types_dict,
        )

    if typename in types_dict:

        def assert_equal(field: str) -> None:
            assert types_dict[typename][field] == data[field]

        # Everything had better be the same, except unformatted_typenames
        assert_equal("full_typename")
        assert_equal("typename")
        assert_equal("index")
        assert_equal("storage_dims")
        assert_equal("subtypes")

        types_dict[typename]["unformatted_typenames"].extend(data["unformatted_typenames"])
    else:
        types_dict[typename] = data
