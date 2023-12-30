# Copyright 2022-present Contributors to the colorman project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorman

set( project_name "Colorman" )
project( ${project_name} )

# headers
file(GLOB headers
    "include/*.h"
)

# sources
file(GLOB sources
    "*.cpp"
    "*.mm"
    "*.qrc"
    "*.ui"
)

file(GLOB core_sources
    "core/*.cpp"
)

file(GLOB python_sources
    "python/*.cpp"
)

file( GLOB resources_sources
    "resources/*.icns" 
    "resources/*.icc"
    "resources/*.css"
    "resources/*.png"
)

file(GLOB widgets_sources
    "widgets/*.cpp"
    "widgets/*.ui"
)

set( bundle_sources
    "resources/MacOSXBundle.plist.in"
)

# source groups
source_group("Source Files" FILES ${sources})
source_group("Header Files" FILES ${headers})
source_group("Core Files" FILES ${core_sources})
source_group("Python Files" FILES ${python_sources})
source_group("Resources Files" FILES ${resources_sources})
source_group("Widgets Files" FILES ${widgets_sources})
source_group("Bundle Files" FILES ${bundle_sources})

# bundle
if (APPLE)
    set (MACOSX_BUNDLE_GUI_IDENTIFIER "com.github.mikaelsundell.colorman")
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
    set_source_files_properties (${resources_sources} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable (${project_name} 
        MACOSX_BUNDLE 
        ${headers} 
        ${sources} 
        ${core_sources}
        ${widgets_sources} 
        ${python_sources} 
        ${python_sources}
        ${resources_sources}
        ${widgets_sources}
        # macosx bundle
        ${bundle_sources}
    )
    # code signing
    if (SIGN_CODE)
        if (CODE_SIGN_IDENTITY STREQUAL "" OR DEVELOPMENT_TEAM_ID STREQUAL "")
            message (FATAL_ERROR "Code signing is enabled, but CODE_SIGN_IDENTITY or DEVELOPMENT_TEAM_ID is not set.")
        else ()
            message ("Code signing enabled for Xcode")
            message ("  Sign identify: ${CODE_SIGN_IDENTITY}")
            message ("  Development team: ${DEVELOPMENT_TEAM_ID}")
        endif()
        set_target_properties(${project_name} PROPERTIES
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "${CODE_SIGN_IDENTITY}"
            XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "${DEVELOPMENT_TEAM_ID}"
            XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${MACOSX_BUNDLE_GUI_IDENTIFIER}"
            MACOSX_BUNDLE_GUI_IDENTIFIER "${MACOSX_BUNDLE_GUI_IDENTIFIER}"
        )
    endif()
    set_target_properties (${project_name} PROPERTIES
        OUTPUT_NAME ${project_name}
        MACOSX_FRAMEWORK_INFO_PLIST ${bundle_sources})
    target_compile_options (${project_name} PRIVATE -Wno-deprecated-register)
    target_include_directories (${project_name} 
        PRIVATE 
            include
            ${LCMS2_INCLUDE_DIR}
    )
    target_link_libraries (${project_name}
        PRIVATE
            colorman::core
            colorman::widgets
            Qt6::Core Qt6::PrintSupport Qt6::Gui Qt6::Widgets 
            Python3::Python
            ${LCMS2_LIBRARY}
            "-framework CoreFoundation"
            "-framework AppKit"
  
    )
else ()
    message (WARNING "${project_name} is a Mac program, will not be built.")
endif ()
