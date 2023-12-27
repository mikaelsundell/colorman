// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <gui/gui.h>
#include <QApplication>

namespace colorman {
namespace gui {

class ApplicationPrivate;
class Application : public QApplication
{
    Q_OBJECT
    public:
        Application(int & argc, char ** argv);
        virtual ~Application();
        virtual int exec();
        
    private:
        QScopedPointer<ApplicationPrivate> p;
};

}
}
