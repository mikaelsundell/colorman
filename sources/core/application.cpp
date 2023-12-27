// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "core/application.h"
#include <QtCore/QDir>

namespace colorman {
namespace core {

class ApplicationPrivate
{
};

Application::Application( int & argc, char ** argv )
: QCoreApplication( argc, argv )
, p( new ApplicationPrivate )
{
}

Application::~Application()
{
}

int
Application::exec()
{
    return(QCoreApplication::exec());
}

}
}
