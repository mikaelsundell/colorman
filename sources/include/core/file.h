// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <core/core.h>
#include <QFileInfo>

namespace colorman {
namespace core {

class Range;
class FilePrivate;
class File : public QObject
{
    public:
        enum Type
        {
            Frame,
            Sequence
        };

    public:
        File();
        File(const File& file);
        File(const QString& file);
        File(const QFileInfo& info);
        virtual ~File();
    
    public:
        Type type() const;
        QString displayName() const;
        QString displaySize() const;
        QString dirName() const;
        QString fileName() const;
        QString filePath() const;
        qint64 size() const;
        QString suffix() const;
        QString modified() const;
        QString owner() const;
        QString group() const;
        bool exists() const;
        bool isReadable() const;
        bool isWritable() const;
        bool isExecutable() const;
        int start() const;
        int end() const;
        bool hasFrame(int frame);
        File findFile(int frame);
        void addRange(const Range& range);
        QList<Range> ranges() const;
        bool isValid() const;
    
        File& operator=(const File& file);
        bool operator==(const File& file) const;
        bool operator!=(const File& file) const;
        bool operator<(const File& file) const;
        bool operator>(const File& file) const;
        
    public:
        static QList<File> parse(const QString& dir, const QStringList& namefilters, bool useranges = true);
        
    private:
        QSharedPointer<FilePrivate> p;
        friend class FilePrivate;
};

}
}
