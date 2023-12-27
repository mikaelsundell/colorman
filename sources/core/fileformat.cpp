// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include <core/fileformat.h>
#include <QSharedData>
#include <QList>

namespace colorman {
namespace core {

class FileFormatPrivate : public QSharedData
{
    public:
        FileFormatPrivate();
        FileFormatPrivate(const FileFormatPrivate& copy);
        FileFormatPrivate(const QString& file, const QList<QString>& extensions, bool readable, bool writable);
        ~FileFormatPrivate();
        bool isSupported(const QString& extension) const;
        bool isValid() const;
        bool operator<(const FileFormat& fileformat) const;
        bool operator>(const FileFormat& fileformat) const;

    public:
        QString name;
        QList<QString> extensions;
        bool readable;
        bool writable;
};

FileFormatPrivate::FileFormatPrivate()
{
}

FileFormatPrivate::FileFormatPrivate(const FileFormatPrivate& copy)
: QSharedData(copy)
{
}

FileFormatPrivate::FileFormatPrivate(const QString& name, const QList<QString>& extensions, bool readable, bool writable)
: name(name)
, extensions(extensions)
, readable(readable)
, writable(writable)
{
}

FileFormatPrivate::~FileFormatPrivate()
{
}

bool
FileFormatPrivate::isSupported(const QString & extension) const
{
    foreach(const QString & ext, extensions)
    {
        if(ext.toLower() == extension.toLower()) {
            return(true);
        }
    }
    return(false);
}

bool
FileFormatPrivate::isValid() const
{
    return(!name.isEmpty() && !extensions.isEmpty());
}

bool
FileFormatPrivate::operator<(const FileFormat& fileformat) const
{
    return(QString::compare(name, fileformat.name(), Qt::CaseInsensitive ) < 0);
}

bool
FileFormatPrivate::operator>(const FileFormat& fileFormat) const
{
    return(QString::compare(name , fileFormat.name(), Qt::CaseInsensitive ) > 0);
}

FileFormat::FileFormat(const QString& name, const QList<QString>& extensions, bool readable, bool writable)
: p(new FileFormatPrivate(name, extensions, readable, writable))
{
}

FileFormat::FileFormat(const FileFormat& fileformat)
: p(fileformat.p)
{
}

FileFormat::~FileFormat()
{
}

QString
FileFormat::name() const
{
    return(p->name);
}

QList<QString>
FileFormat::extensions() const
{
    return(p->extensions);
}

bool
FileFormat::isSupported(const QString& extension) const
{
    return(p->isSupported(extension));
}
    
bool
FileFormat::isValid() const
{
    return(p->isValid());
}

FileFormat&
FileFormat::operator=(const FileFormat& fileFormat)
{
    p = fileFormat.p;
    return *this;
}

bool
FileFormat::operator==(const FileFormat& fileformat) const
{
    if(fileformat.p == p)
    {
        return(true);
    }
    if(p->name == fileformat.p->name)
    {
        return(true);
    }
    return(false);
}

bool
FileFormat::operator!=(const FileFormat& fileformat) const
{
    return(!( operator==(fileformat)));
}

bool
FileFormat::operator < (const FileFormat& fileformat) const
{
    return(p->operator<(fileformat));
}

bool
FileFormat::operator > (const FileFormat& fileformat) const
{
    return(p->operator>(fileformat));
}

}
}
