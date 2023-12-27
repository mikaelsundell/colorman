# Copyright 2022-present Contributors to the colorman project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorman

set (project_name "gui")
project (${project_name})

# sources
file (GLOB sources
    "*.cpp"
)

file (GLOB headers
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/${project_name}/*.h"
)

# library
add_library (${project_name} ${sources} ${headers})

# alias
add_library(colorman::${project_name} ALIAS ${project_name})

# target
target_include_directories (${project_name}
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries (${project_name}
    PUBLIC
        Qt6::Core
        Qt6::Widgets
)