// Copyright 2023-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "window.h"
#include "colorman.h"
#include "pythoninterpreter.h"
#include <gui/application.h>
#include <QApplication>

using namespace colorman;

int
main(int argc, char *argv[])
{
    int exit = 0;
    try {
        gui::Application app(argc, argv);
        {
            Colorman* colorman = Colorman::instance();
            colorman->init();
            
            PythonInterpreter* interpreter = PythonInterpreter::instance();
            interpreter->init();

            Window window;
            window.show();
            exit = app.exec();
        }
    }
    catch (const std::exception& e) {
        qDebug() << "standard exception:" << e.what();
        exit = -1;
    }
    catch (...) {
        qDebug() << "unknown exception occurred";
        exit = -1;
    }
    return exit;
}
