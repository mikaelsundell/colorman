// Copyright 2023-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include <core/file.h>
#include <QTextStream>
#include <QStringList>
#include <QList>

using namespace colorman;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        QTextStream(stderr) << "Invalid number of arguments.\n"
                            << "Usage: " << argv[0] << " <dir>\n";
        return 1;
    }
    QList<core::File> files = core::File::parse(argv[1], QStringList{"*"}, true);
    QTextStream console(stdout);
    console << "Total " << files.size() << Qt::endl;

    for (const core::File& file : files) {
        console << Qt::left 
                << qSetFieldWidth(30) << file.displayName()
                << qSetFieldWidth(10) << (file.type() == core::File::Frame ? "File" : "Range")
                << qSetFieldWidth(10) << file.size()
                << qSetFieldWidth(5) << (file.isWritable() ? "w" : "")
                << (file.isReadable() ? "r" : "")
                << (file.isExecutable() ? "x" : "") << " "
                << qSetFieldWidth(15) << file.owner()
                << qSetFieldWidth(15) << file.group()
                << qSetFieldWidth(10) << file.modified()
                << qSetFieldWidth(0) << Qt::endl;
    }
    return 0;
}
