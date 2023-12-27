// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include <gui/application.h>

namespace colorman {
namespace gui {

class ApplicationPrivate
{
};

Application::Application( int & argc, char ** argv )
: QApplication( argc, argv )
, p( new ApplicationPrivate )
{
}

Application::~Application()
{
}

int
Application::exec()
{
    return(QApplication::exec());
}

}
}
