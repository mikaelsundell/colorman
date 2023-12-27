// Copyright 2023-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "colorman.h"
#include <gui/application.h>
#include <QApplication>

using namespace colorman;

int main(int argc, char *argv[])
{
    gui::Application app(argc, argv);
    {
        Colorman colorman;
        colorman.show();
        return app.exec();
    }
}
