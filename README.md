# <img src="https://github.com/mikaelsundell/colorman/blob/cd4a38626bbd312005d04f8f87e078dd55341357/sources/colorman/resources/AppIcon.png" valign="middle" alt="Icon" width="50" height="50"> Colorman #

[![License](https://img.shields.io/badge/license-BSD%203--Clause-blue.svg?style=flat-square)](https://github.com/mikaelsundell/logctool/blob/master/README.md)

Introduction
------------

<img src="https://github.com/mikaelsundell/colorman/blob/db44f33595b75b9b6bd051a266dfdfa10902ec19/sources/colorman/resources/AppImage.png" />

Colorman is an app for color processing and Inspection with grading, scopes, and scripting capabilities.

This project is still in development and not ready for use.

**Important Gatekeeper note**

Use `xattr -cr /Applications/Colorman.app` if downloaded from releases to clear attributes added by Gatekeeper.

Documentation
-------------

Build & Package
------------------
Colorman is built using the ```build.sh``` script.

Build all - debug and release:
```shell
./build.sh all
```

Requires 3rdparty build at the same level as Colorman.


Colorman Advanced
--------

The Colorman app can be built both from commandline or using Xcode `-GXcode`. Use `DYLD_IMAGE_SUFFIX=_debug` environment variable to link and run with Qt debug frameworks.

## CMake configuration ##

Add cmake to path:

```shell
export PATH=$PATH:/Applications/CMake.app/Contents/bin
```

## Build configuration ##

```shell
mkdir build
cd build
cmake .. -DCMAKE_MODULE_PATH=<path>/colorman/modules -DCMAKE_PREFIX_PATH=<path>/3rdparty/build/macosx/arm64.debug -GXcode
cmake --build . --config Release --parallel
```

**Packaging**

The `macdeploy.sh` script will deploy mac bundle to dmg including dependencies.

```shell
./macdeploy.sh -b <path>/Colorman.app -m <path>/macdeployqt -d <path>/Colorman_macOS<version>_<arch>.dmg
```

Dependencies
-------------

| Project     | Description |
| ----------- | ----------- |
| OpenImageIO | [OpenImageIO project @ Github](https://github.com/OpenImageIO/oiio)
| 3rdparty    | [3rdparty project containing all dependencies @ Github](https://github.com/mikaelsundell/3rdparty)


Project
-------------

* GitHub page   
https://github.com/mikaelsundell/colorman

* Issues   
https://github.com/mikaelsundell/colorman/issues


Copyright
---------

* Roboto font   
https://fonts.google.com/specimen/Roboto   
Designed by Christian Robertson
