// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <QString>
#include <QScopedPointer>

namespace colorman {

class PythonInterpreterPrivate;
class PythonInterpreter {
    public:
        static PythonInterpreter* instance();
        void init();
        void release();
        QString executeScript(const QString& script) const;

    private:
        PythonInterpreter();
        ~PythonInterpreter();
        PythonInterpreter(const PythonInterpreter&) = delete;
        PythonInterpreter& operator=(const PythonInterpreter&) = delete;
        class Deleter {
        public:
            static void cleanup(PythonInterpreter* pointer) {
                delete pointer;
            }
        };
        QScopedPointer<PythonInterpreterPrivate> p;
        static QScopedPointer<PythonInterpreter, Deleter> ip;
};

}
