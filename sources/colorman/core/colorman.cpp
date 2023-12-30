// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "colorman.h"
#include <core/macro.h>

namespace colorman {

QScopedPointer<Colorman, Colorman::Deleter> Colorman::p;

Colorman::Colorman()
{
}

Colorman::~Colorman()
{
    release();
}

Colorman*
Colorman::instance()
{
    if (!p) {
        p.reset(new Colorman);
    }
    return p.data();
}

void
Colorman::init()
{
    CoreDebug() << "init";
}

void
Colorman::release()
{
    CoreDebug() << "release";
}

void
Colorman::open(const QString& file)
{
    CoreDebug() << "open: " << file;
    emit fileOpened(file);
}

void
Colorman::close() const
{
    CoreDebug() << "Close";
}

}
