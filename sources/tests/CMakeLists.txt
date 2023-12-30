# Copyright 2022-present Contributors to the colorman project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorman

# oiio_viewer
add_executable ("oiio_viewer" oiio_viewer.cpp)
target_link_libraries ("oiio_viewer"
    PRIVATE
        colorman::core
        colorman::widgets
        Qt6::Core Qt6::PrintSupport Qt6::Gui Qt6::Widgets
        OpenImageIO::OpenImageIO
)

# oiio_file
add_executable ("oiio_file" oiio_file.cpp)
target_link_libraries ("oiio_file"
    PRIVATE
        colorman::core
        OpenImageIO::OpenImageIO
)
