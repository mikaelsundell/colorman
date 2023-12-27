# Copyright 2023-present Contributors to the vectorscope project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/colorman

import os
import sys
import random

def create_files(directory):
    for i in range(1, 21):
        filename = os.path.join(directory, f"sequence1.{i:04d}.tif")
        open(filename, 'a').close()

    for i in range(1, 21):
        filename = os.path.join(directory, f"sequence2.{i:03d}.tif")
        open(filename, 'a').close()

    for i in range(60):
        random_num = random.randint(1, 10)
        filename = os.path.join(directory, f"file{random_num}.exr")
        open(filename, 'a').close()

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <directory_path>")
        sys.exit(1)

    directory = sys.argv[1]

    if not os.path.exists(directory):
        print(f"Directory {directory} does not exist.")
        sys.exit(1)

    create_files(directory)
    print(f"Files created in {directory}")

if __name__ == "__main__":
    main()
