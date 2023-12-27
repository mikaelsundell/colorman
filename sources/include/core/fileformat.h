// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <core/core.h>

namespace colorman {
namespace core {
    
class FileFormatPrivate;
class FileFormat : public QObject
{
    public:
        FileFormat(const QString& name, const QList<QString>& extensions, bool readable, bool writable);
        FileFormat(const FileFormat& fileformat);
        virtual ~FileFormat();
        
    public:
        QString name() const;
        QList<QString> extensions() const;
        bool isReadable() const;
        bool isWritable() const;
        bool isSupported(const QString& extension) const;
        bool isValid() const;
    
    public:
        FileFormat& operator=(const FileFormat& fileformat);
        bool operator==(const FileFormat& fileformat) const;
        bool operator!=(const FileFormat& fileformat) const;
        bool operator<(const FileFormat& fileformat) const;
        bool operator>(const FileFormat& fileformat) const;
        
    private:
        QSharedPointer<FileFormatPrivate> p;
        friend class FileFormatPrivate;
};

} 
}
