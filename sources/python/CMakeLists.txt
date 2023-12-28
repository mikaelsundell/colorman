# Copyright 2022-present Contributors to the colorman project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorman

set (project_name "PyColorman")
project (${project_name})

# sources
file (GLOB sources
    "*.cpp"
)

# python module
pybind11_add_module (${project_name} MODULE ${sources})

# target
target_link_libraries (${project_name}
    PRIVATE
        colorman::core
        colorman::gui
)
