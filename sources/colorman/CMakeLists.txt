# Copyright 2022-present Contributors to the colorman project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorman

set( project_name "colorman" )
project( ${project_name} )

# sources
file(GLOB colorman_sources
    "*.cpp"
    "*.mm"
    "*.h"
    "*.ui"
    "*.qrc"
)

# resources
file( GLOB colorman_resources
    "resources/*.icns" 
    "resources/*.icc"
    "resources/*.css"
    "resources/App*.png"
    "resources/smptecolorbar.png"
)

# bundle
set( colorman_bundle
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
    set_source_files_properties (${colorman_resources} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    # executable
    add_executable (${project_name} MACOSX_BUNDLE ${colorman_sources} ${colorman_resources})
    set_target_properties(${project_name} PROPERTIES
        OUTPUT_NAME ${project_name}
        MACOSX_FRAMEWORK_INFO_PLIST ${colorman_bundle})
    target_compile_options (${project_name} PRIVATE -Wno-deprecated-register)
    target_include_directories (${project_name} PRIVATE ${LCMS2_INCLUDE_DIR})
    target_link_libraries (${project_name}
        PRIVATE
            colorman::core
            colorman::gui
            Qt6::Core Qt6::PrintSupport Qt6::Gui Qt6::Widgets 
            ${LCMS2_LIBRARY}
            "-framework CoreFoundation"
            "-framework AppKit"
  
    )
else ()
    message (WARNING "${project_name} is a Mac program, will not be built.")
endif ()
