// Copyright 2023-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "colorman.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Colorman colorman;
    colorman.show();
    return app.exec();
}
