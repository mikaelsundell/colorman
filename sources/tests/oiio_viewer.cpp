// Copyright 2023-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include <widgets/application.h>

using namespace colorman;

int
main(int argc, char *argv[])
{
    widgets::Application app( argc, argv );
    return( app.exec() );
}
