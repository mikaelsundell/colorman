// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include <core/range.h>
#include <QSharedData>
#include <QMap>

namespace colorman {
namespace core {

class RangePrivate : public QSharedData
{
    public:
        RangePrivate();
        RangePrivate(const RangePrivate& copy);
        ~RangePrivate();
        void addFrame(int frame, const File& file);
        File frame(int frame) const;
        int start() const;
        int end() const;
        size_t size() const;
        bool isValid() const;
        bool operator<(const Range& range) const;
        bool operator>(const Range& range) const;

    public:
        QMap<int, File> ranges;
};

RangePrivate::RangePrivate()
{
}

RangePrivate::RangePrivate(const RangePrivate& copy)
: QSharedData(copy)
, ranges(copy.ranges)
{
}

RangePrivate::~RangePrivate()
{
}

void
RangePrivate::addFrame(int frame, const File& file)
{
    ranges.insert(frame, file);
}

File
RangePrivate::frame(int frame) const
{
    return(ranges.value(frame));
}

int
RangePrivate::start() const
{
    return(ranges.keys().front());
}
        
int
RangePrivate::end() const
{
    return(ranges.keys().back());
}

size_t
RangePrivate::size() const
{
    return(ranges.size());
}

bool
RangePrivate::isValid() const
{
    return(ranges.size());
}

bool
RangePrivate::operator<(const Range& range) const
{
    return(ranges.size() < range.p->ranges.size());
}

bool
RangePrivate::operator>(const Range& range) const
{
    return(ranges.size() > range.p->ranges.size());
}

Range::Range()
: p(new RangePrivate())
{
}

Range::Range(const Range& range)
: p(range.p)
{
}

Range::~Range()
{
}

void
Range::addFrame(int frame, const File& file)
{
    p->addFrame(frame, file);
}
        
File
Range::frame(int frame) const
{
    return(p->frame(frame));
}
        
int
Range::start() const
{
    return(p->start());
}
        
int
Range::end() const
{
    return(p->end());
}

size_t
Range::size() const
{
    return(p->size());
}

bool
Range::isValid() const
{
    return(p->isValid());
}

Range&
Range::operator=(const Range& range)
{
    p = range.p;
    return *this;
}

bool
Range::operator==(const Range& range) const
{
    return(const_cast<const Range *>(this)->operator==(range));
}

bool
Range::operator!=(const Range& range) const
{ 
    return(!(operator==(range)));
}

bool
Range::operator<(const Range& range) const
{
    return(p->operator<(range));
}

bool
Range::operator>(const Range& range) const
{
    return(p->operator>(range));
}

}
}
