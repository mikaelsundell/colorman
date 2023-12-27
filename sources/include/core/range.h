// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <core/core.h>
#include <core/file.h>

namespace colorman {
namespace core {

class RangePrivate;
class Range : public QObject
 {
    public:
        Range();
        Range(const Range& range);
        virtual ~Range();
     
    public:
        void addFrame(int frame, const File& file);
        File frame(int frame) const;
        int start() const;
        int end() const;
        size_t size() const;
        bool isValid() const;
    
    public:
        Range& operator=(const Range& range);
        bool operator==(const Range& range) const;
        bool operator!=(const Range& range) const;
        bool operator <(const Range& range) const;
        bool operator >(const Range& range) const;
        
    private:
        QSharedPointer<RangePrivate> p;
        friend class RangePrivate;
};

}
}
