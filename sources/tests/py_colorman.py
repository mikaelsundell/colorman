# Copyright 2022-present Contributors to the vectorscope project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorman

import os
import sys

def size_to_mb(num_bytes):
    megabytes = num_bytes / (1024 * 1024)
    return "{:.2f} MB".format(megabytes)

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    build_dir = os.path.join(script_dir, '../../build/sources/python')

    if os.path.exists(build_dir) and os.path.isdir(build_dir):
        sys.path.append(build_dir)
    else:
        print(f"Build directory does not exist: {build_dir}")
        sys.exit(1)

    # PyColorman
    import PyColorman

    # core File
    file_path = os.path.join(script_dir, "../media/smptecolorbar.png")
    file = PyColorman.File(file_path)
    print("Display name: " + str(file.displayName()))
    print("File path: " + str(file.filePath()))
    print("File size: " + size_to_mb(file.size()))
    print("File isReadable: " + str(file.isReadable()))

if __name__ == "__main__":
    main()
