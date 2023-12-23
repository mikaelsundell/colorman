# Copyright 2022-present Contributors to the colorman project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorman

cmake_minimum_required( VERSION 3.0 )
set( project_name "Colorman" )

project( ${project_name} )

# config
#list(APPEND CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}/lib/cmake")

# packages
set (qt6_modules Core PrintSupport Gui Widgets OpenGL)
find_package(Qt6 COMPONENTS ${qt6_modules} CONFIG REQUIRED)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package( Lcms2 REQUIRED )

# sources
set (app_sources
    vectorscopewidget.cpp
    vectorscopewidget.h
    colortools.cpp
    colortools.h
    imagewidget.h
    imagewidget.cpp
    main.cpp
    colorman.cpp
    colorman.h
    about.ui
    colorman.ui
    colorman.qrc
)

# resources
file( GLOB app_resources
    "resources/*.icns" 
    "resources/*.icc"
    "resources/*.css"
    "resources/App*.png"
    "resources/smptecolorbar.png"
)

# bundle
set (bundle_sources
    "resources/MacOSXBundle.plist.in"
)

if (APPLE)
    set (MACOSX_BUNDLE_EXECUTABLE_NAME ${project_name})
    set (MACOSX_BUNDLE_INFO_STRING ${project_name})
    set (MACOSX_BUNDLE_BUNDLE_NAME ${project_name})
    set (MACOSX_BUNDLE_ICON_FILE AppIcon.icns)
    set (MACOSX_BUNDLE_LONG_VERSION_STRING "1.0")
    set (MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0")
    set (MACOSX_BUNDLE_BUNDLE_VERSION "1.0")
    set (MACOSX_BUNDLE_COPYRIGHT "Copyright 2022-present Contributors to the ${project_name} project")
    set (MACOSX_DEPLOYMENT_TARGET ${DEPLOYMENT_TARGET})
    set (CMAKE_XCODE_ATTRIBUTE_OTHER_CODE_SIGN_FLAGS "-o linker-signed")
    set_source_files_properties(${app_resources} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    # executable
    add_executable (${project_name} MACOSX_BUNDLE ${app_sources} ${app_resources})
    set_target_properties(${project_name} PROPERTIES
        OUTPUT_NAME ${project_name}
        MACOSX_FRAMEWORK_INFO_PLIST ${bundle_sources})
    target_compile_options (${project_name} PRIVATE -Wno-deprecated-register)
    target_include_directories (${project_name} PRIVATE ${LCMS2_INCLUDE_DIR})
    target_link_libraries (${project_name} 
        Qt6::Core Qt6::PrintSupport Qt6::Gui Qt6::Widgets 
        ${LCMS2_LIBRARY}
        "-framework CoreFoundation"
        "-framework AppKit")
else ()
    message (WARNING "${project_name} is a Mac program, will not be built.")
endif ()