// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include <core/file.h>
#include <core/range.h>
#include <QLocale>
#include <QRegularExpression>
#include <QDateTime>
#include <QDir>
#include <QtAlgorithms>

namespace colorman {
namespace core {

class FilePrivate : public QSharedData
{

    public:
        FilePrivate();
        FilePrivate(const FilePrivate& copy);
        FilePrivate(const QString& file);
        FilePrivate(const QFileInfo& info);
        ~FilePrivate();
        QString displayName() const;
        QString displaySize() const;
        void addRange(const Range& range);
        QList<Range> ranges() const;
        int start() const;
        int end() const;
        File::Type type() const;
        bool isValid() const;
        bool operator < (const File& file) const;
        bool operator > (const File& file) const;

    public:
        class RangeValue
        {
            public: 
                RangeValue() {}
                RangeValue(const QString& rangename, int frame)
                : rangename(rangename)
                , frame(frame) {}
                bool isValid() const
                {
                    return(!rangename.isEmpty());
                }
                QString rangename;
                int frame;
        };

    public:
        static RangeValue rangeName(const QString& displayname);
        static QChar fillChar;

    public:
        QFileInfo info;
        QList<Range> rangelist;
};

QChar FilePrivate::fillChar = '#';
FilePrivate::FilePrivate()
{
}

FilePrivate::FilePrivate(const FilePrivate& copy)
: QSharedData(copy)
, info(copy.info)
{
}

FilePrivate::FilePrivate(const QString& file)
{
    if(file.contains(fillChar))
    {
        QFileInfo fileInfo( file );
        QString path = fileInfo.absolutePath();
        QString nameFilter = fileInfo.fileName().replace(QRegularExpression(QString("[%1]+").arg(fillChar)), "*");
        QList<File> files = File::parse(
            QFileInfo(file).absolutePath(), 
            QStringList() << nameFilter, 
            true 
        );
        if(files.size()) {
            info = files[0].p->info;
            rangelist = files[0].p->rangelist;
        }
    }
    if(!info.isFile())
    {
        info = QFileInfo( file );
    }
}

FilePrivate::FilePrivate(const QFileInfo& info)
: QSharedData()
, info(info)
{
}

FilePrivate::~FilePrivate()
{
}

QString
FilePrivate::displayName() const
{
    if(type() == File::Frame)
    {
        return(info.fileName());
    }
    else
    {
        QString displayname = 
            QString("%1 %2-%3").arg(rangeName(info.fileName()).rangename) // file stores the first frame
                               .arg(ranges().front().start())
                               .arg(ranges().back().end());
        if( ranges().size() > 1 ) 
        {
            displayname += " ( ";
            foreach(const core::Range& range, ranges()) {
                if( range.start() < range.end() )
                {
                    displayname += QString("%1-%2 ").arg( range.start() )
                                                      .arg( range.end() );
                }
                else
                {
                    displayname += QString("%1 ").arg( range.start() );
                }
            }
            displayname += ")";
        }
        return(displayname);
    }
}
	
QString
FilePrivate::displaySize() const
{
    qint64 bytes = info.size();
    // SI standard KB is 1000 bytes, KiB is 1024, on windows sizes
    // are calculated by dividing by 1024 so we do what they do.
    const qint64 kb = 1024;
    const qint64 mb = 1024 * kb;
    const qint64 gb = 1024 * mb;
    const qint64 tb = 1024 * gb;
    if (bytes >= tb)
    {
        return(File::tr("%1TB").arg(QLocale().toString(qreal(bytes) / tb, 'f', 3)));
    }
    if (bytes >= gb )
    {
        return(File::tr("%1GB").arg(QLocale().toString(qreal(bytes) / gb, 'f', 2)));
    }
    if (bytes >= mb )
    {
        return(File::tr("%1MB").arg(QLocale().toString(qreal(bytes) / mb, 'f', 1)));
    }
    if (bytes >= kb)
    {
        return(File::tr("%1KB").arg(QLocale().toString(bytes / kb)));
    }
    return(File::tr("%1 bytes").arg(QLocale().toString(bytes)));
}

void
FilePrivate::addRange(const Range& range)
{
    rangelist.append(range );
}

QList<Range>
FilePrivate::ranges() const
{
    return(rangelist);
}

int
FilePrivate::start() const
{
    if(type() == File::Frame)
    {
        return( rangeName(info.fileName() ).frame);
    }
    else
    {
        return(rangelist.front().start());
    }
}
        
int
FilePrivate::end() const
{
    if(type() == File::Frame)
    {
        return(rangeName( info.fileName() ).frame); // get end frame from fileName
    }
    else
    {
        return(rangelist.back().end());
    }
}

File::Type
FilePrivate::type() const
{
    if(rangelist.size())
    {
        return(File::Sequence);
    }
    else
    {
        return(File::Frame);
    }
}

bool
FilePrivate::isValid() const
{
    return(info.isFile() && info.exists());
}

bool
FilePrivate::operator<(const File& file) const
{
    return(QString::compare(displayName() , file.displayName(), Qt::CaseInsensitive) < 0);
}

bool
FilePrivate::operator>(const File& file) const
{
    return(QString::compare(displayName() , file.displayName(), Qt::CaseInsensitive) > 0);
}
           
FilePrivate::RangeValue
FilePrivate::rangeName(const QString& displayname) {
    Q_ASSERT(!displayname.isEmpty() && "displayname cannot be empty");
    QString name = displayname;
    QString cap;
    qsizetype pos = -1;
    QRegularExpression regex("(\\d+)");
    QRegularExpressionMatchIterator iterator = regex.globalMatch(name);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        cap = match.captured(1); 
        pos = match.capturedStart(1);
    }
    if (pos != -1) {
        int frame = cap.toInt();
        QString fill = cap.fill(fillChar);
        return RangeValue(name.replace(pos, cap.length(), fill), frame);
    } else {
        return RangeValue(name, 0); // default to zero frame
    }
}
         
File::File()
: p(new FilePrivate() )
{
}

File::File( const File & file )
: p(file.p)
{
}

File::File(const QString& file)
: p(new FilePrivate(file))
{
}

File::File(const QFileInfo& info)
: p( new FilePrivate(info))
{
}

File::~File()
{
}
    
File::Type
File::type() const
{
    return(p->type());
}

QString
File::displayName() const
{
    return(p->displayName());
}
	
QString
File::displaySize() const
{
	return(p->displaySize());
}

QString
File::dirName() const
{
    return(p->info.dir().path());
}

QString
File::fileName() const
{
    return(p->info.fileName());
}

QString
File::filePath() const
{
    return(p->info.filePath());
}

qint64
File::size() const
{
	return(p->info.size());
}
	
QString
File::suffix() const
{
    return(p->info.suffix());
}

QString
File::modified() const
{
    return QLocale::system().toString(p->info.lastModified(), QLocale::FormatType::ShortFormat);
}

QString
File::owner() const
{
    return(p->info.owner());
}

QString
File::group() const
{
    return(p->info.group());
}

bool
File::exists() const
{
    return(p->info.exists());
}

bool
File::isReadable() const
{
    return(p->info.isReadable());
}
        
bool
File::isWritable () const
{
    return(p->info.isWritable());
}

bool
File::isExecutable() const
{
    return(p->info.isExecutable());
}

int
File::start() const
{
    return(p->start());
}

int
File::end() const
{
    return(p->end());
}
    
bool
File::hasFrame(int frame)
{
    return(findFile(frame).isValid());
}
    
File
File::findFile( int frame )
{
    if(ranges().size() > 1)
    {
        foreach(const core::Range & range, ranges())
        {
            if(frame >= range.start() && frame <= range.end()) // make sure we include start and end frame for compare
            {
                return range.frame(frame);
            }
        }
    }
    else
    {
        return(ranges().first().frame(frame));
    }
    return(File());
}

bool
File::isValid() const
{
    return(p->isValid());
}
    
void
File::addRange(const Range & range)
{
    p->addRange(range);
}
    
QList<Range>
File::ranges() const
{
    return(p->ranges());
}

File &
File::operator=(const File& file)
{
    p = file.p;
    return *this;
}

bool
File::operator==(const File& file) const
{
    if(file.p == p)
    {
        return(true);
    }
    if(p->info.filePath() == file.p->info.filePath())
    {
        return(true);
    }
    return(false);
}

bool
File::operator!=(const File& file) const
{ 
    return(!(operator==(file)));
}

bool
File::operator < (const File& file) const
{
    return(p->operator<(file));
}

bool
File::operator > (const File & file) const
{
    return(p->operator>(file));
}

QList<File>
File::parse(const QString& path, const QStringList& namefilters, bool useranges )
{
    QDir dir(path);
    QList<File> files;
    int frame;
    QString rangename;
    QScopedPointer<Range> range;
    QFileInfoList entries = dir.entryInfoList(namefilters, QDir::Files, QDir::Type);
    foreach(const QFileInfo & entry, entries) {
        if(useranges) {
            FilePrivate::RangeValue value = FilePrivate::rangeName(entry.fileName());
            if(value.isValid())
            {    
                bool last = entry == entries.back() ? true : false;
                if(value.rangename != rangename) {
                    // only add the range if the range contains
                    // more than one file or already contains ranges
                    if(files.size() && (range->size() > 1 || files.back().ranges().size())) {
                        // new range, add range to file
                        files.back().addRange( *range.data() );
                    }
                    files.append( core::File( entry ) );
                    frame = value.frame;
                    rangename = value.rangename;
                    range.reset( new Range() );
                    
                } else {
                    if( value.frame != frame ) {
                        // new range, add range to file
                        files.back().addRange( *range.data() ); 
                        frame = value.frame;
                        range.reset( new Range() ); 
                    }
                }
                range->addFrame( value.frame, entry );
                if(last && ( range->size() > 1 || files.back().ranges().size())) {
                    files.back().addRange( *range.data() );
                }
                frame++; 
            }
        }
        else
        {
            files.append(File(entry));
        }
    }
    return(files);
}

}
}
