# Copyright 2022-present Contributors to the colorman project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorman

# cmake
cmake_minimum_required( VERSION 3.0 )

# project
set( project_name "Colorman" )
project( ${project_name} )

# cmake
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_PREFIX_PATH}/lib/cmake")

# cmake - Qt6
set (qt6_modules Core PrintSupport Gui Widgets OpenGL)
find_package(Qt6 COMPONENTS ${qt6_modules} CONFIG REQUIRED)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

# cmake - OpenImageIO
find_package( OpenImageIO CONFIG REQUIRED )

# cmake - lcms2
find_package( Lcms2 REQUIRED )

# configuration
set (BUILD_SHARED_LIBS ON)

# colorman
add_subdirectory (sources/colorman)
add_subdirectory (sources/core)
add_subdirectory (sources/gfx)
add_subdirectory (sources/gui)
add_subdirectory (sources/python)
add_subdirectory (sources/tests)
