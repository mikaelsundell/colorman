# Copyright 2022-present Contributors to the colorman project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorman

# cmake
cmake_minimum_required( VERSION 3.0 )
cmake_policy (SET CMP0057 NEW)

# project
set( project_name "Colorman" )
project( ${project_name} )

# options
option (SIGN_CODE "Sign the code with Apple Developer ID" OFF)
set (CODE_SIGN_IDENTITY "" CACHE STRING "Code Sign Identity")
set (DEVELOPMENT_TEAM_ID "" CACHE STRING "Development Team ID")

# cmake
set (CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_PREFIX_PATH}/lib/cmake")


# Qt6 - cmake config
set (qt6_modules Core PrintSupport Gui Widgets OpenGL)
find_package (Qt6 COMPONENTS ${qt6_modules} CONFIG REQUIRED)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

# packages
find_package (OpenImageIO CONFIG REQUIRED )
find_package (Python3 COMPONENTS Interpreter Development REQUIRED)
find_package (pybind11 REQUIRED)
find_package (Lcms2 REQUIRED)

# configuration
set (BUILD_SHARED_LIBS ON)

# colorman
add_subdirectory (sources/colorman)
add_subdirectory (sources/core)
add_subdirectory (sources/gfx)
add_subdirectory (sources/widgets)
add_subdirectory (sources/python)
add_subdirectory (sources/tests)
