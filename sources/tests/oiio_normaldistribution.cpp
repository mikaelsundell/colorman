// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include <OpenImageIO/imageio.h>
#include <iostream>
#include <random>

int main() {
    OIIO::ImageBuf img("pattern_image.png");

    double sum = 0.0;
    int pixelCount = 0;

    for (int y = 0; y < img.spec().height; ++y) {
        for (int x = 0; x < img.spec().width; ++x) {
            OIIO::ImageBuf::ConstIterator<float> pixelValue(img, x, y);
            sum += pixelValue[0];  // Assuming it's grayscale
            pixelCount++;
        }
    }

    double mean = sum / pixelCount;

    sum = 0.0;
    for (int y = 0; y < img.spec().height; ++y) {
        for (int x = 0; x < img.spec().width; ++x) {
            OIIO::ImageBuf::ConstIterator<float> pixelValue(img, x, y);
            sum += (pixelValue[0] - mean) * (pixelValue[0] - mean);
        }
    }

    double standardDeviation = sqrt(sum / pixelCount);

    // random number generator with the calculated standard deviation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(mean, standardDeviation);

    OIIO::ImageSpec spec(img.spec());
    OIIO::ImageBuf generated_pattern(spec);

    // generate random numbers and write to the new image
    for (int y = 0; y < img.spec().height; ++y) {
        for (int x = 0; x < img.spec().width; ++x) {
            OIIO::ImageBuf::ConstIterator<float> pixelValue(img, x, y);
            double randomValue = distribution(gen);

            // set the pixel value in the new image
            generated_pattern.setpixel(x, y, 0, randomValue);  // assuming grayscale

            // clamping or scaling to control the output range
        }
    }
    generated_pattern.write("generated_pattern.png");
    return 0;
}
