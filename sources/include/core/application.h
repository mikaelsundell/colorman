// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include "core/core.h"
#include <QCoreApplication>

namespace colorman {
namespace core {

class ApplicationPrivate;
class Application : public QCoreApplication
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
