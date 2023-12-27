#!/bin/bash
##  Copyright 2022-present Contributors to the colorman project.
##  SPDX-License-Identifier: BSD-3-Clause
##  https://github.com/mikaelsundell/colorman

script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
machine_arch=$(uname -m)
macos_version=$(sw_vers -productVersion)
major_version=$(echo "$macos_version" | cut -d '.' -f 1)

# exit on error
set -e 

# clear
clear

# build type
build_type="$1"
if [ "$build_type" != "debug" ] && [ "$build_type" != "release" ] && [ "$build_type" != "all" ]; then
    echo "invalid build type: $build_type (use 'debug', 'release', or 'all')"
    exit 1
fi

echo "Building Colorman for $build_type"
echo "---------------------------------"

# check if cmake is in the path
if ! command -v cmake &> /dev/null; then
    echo "cmake not found in the PATH, will try to set to /Applications/CMake.app/Contents/bin"
    export PATH=$PATH:/Applications/CMake.app/Contents/bin
    if ! command -v cmake &> /dev/null; then
        echo "cmake could not be found, please make sure it's installed"
        exit 1
    fi
fi

# check if cmake version is compatible
if ! [[ $(cmake --version | grep -o '[0-9]\+\(\.[0-9]\+\)*' | head -n1) < "3.28.0" ]]; then
    echo "cmake version is not compatible with Qt, must be before 3.28.0 for multi configuration"
    exit 1;
fi

# build colorman
build_colorman() {
    local build_type="$1"

    # cmake
    export PATH=$PATH:/Applications/CMake.app/Contents/bin &&

    # script dir
    cd "$script_dir"

    # clean dir
    build_dir="$script_dir/build.$build_type"
    if [ -d "$build_dir" ]; then
        rm -rf "$build_dir"
    fi

    # build dir
    mkdir -p "build.$build_type"
    cd "build.$build_type"

    # prefix dir
    prefix="$script_dir/../3rdparty/build/macosx/$machine_arch.$build_type"
    if ! [ -d "$prefix" ]; then
        echo "could not find 3rdparty for build in: $prefix"
        exit 1;
    fi

    # xcode build
    xcode_type=$(echo "$build_type" | awk '{ print toupper(substr($0, 1, 1)) tolower(substr($0, 2)) }')

    # build
    cmake .. -DCMAKE_MODULE_PATH="$script_dir/modules" -DCMAKE_PREFIX_PATH="$prefix" -G Xcode &&
    cmake --build . --config $xcode_type --parallel

    # clean dmg
    dmg_file="$script_dir/Colorman_macOS${major_version}_${machine_arch}_${build_type}.dmg"
    if [ -f "$dmg_file" ]; then
        rm -f "$dmg_file"
    fi

    # deploy
    $script_dir/scripts/macdeploy.sh -b "$xcode_type/Colorman.app" -m "$prefix/bin/macdeployqt" -d "$dmg_file"
}

# build types
if [ "$build_type" == "all" ]; then
    build_colorman "debug"
    build_colorman "release"
else
    build_colorman "$build_type"
fi