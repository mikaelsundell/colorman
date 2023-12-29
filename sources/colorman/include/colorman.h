
// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <QObject>
#include <QString>
#include <QScopedPointer>

namespace colorman {

class Colorman : public QObject
{
    Q_OBJECT
    public:
        static Colorman* instance();
        void init();
        void release();
        void open(const QString& file);
        void close() const;
    
    Q_SIGNALS:
        void fileOpened(const QString& file);

    private:
        Colorman();
        ~Colorman();
        Colorman(const Colorman&) = delete;
        Colorman& operator=(const Colorman&) = delete;
        class Deleter {
        public:
            static void cleanup(Colorman* pointer) {
                delete pointer;
            }
        };
        static QScopedPointer<Colorman, Deleter> p;
};

}
