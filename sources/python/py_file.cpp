// Copyright 2023-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <core/file.h>
#include <core/range.h>
#include <QFileInfo>
#include <QString>
#include <QList>

namespace py = pybind11;
namespace colorman {
namespace core {

void declare_file(py::module& m) {
    using namespace py;

    class_<File>(m, "File")
        .def(init<>())
        .def(init<const File&>())
        .def(init<const QString&>())
        .def(init<const QFileInfo&>())
        .def("type", &File::type)
        .def("displayName", &File::displayName)
        .def("displaySize", &File::displaySize)
        .def("dirName", &File::dirName)
        .def("fileName", &File::fileName)
        .def("filePath", &File::filePath)
        .def("size", &File::size)
        .def("suffix", &File::suffix)
        .def("modified", &File::modified)
        .def("owner", &File::owner)
        .def("group", &File::group)
        .def("exists", &File::exists)
        .def("isReadable", &File::isReadable)
        .def("isWritable", &File::isWritable)
        .def("isExecutable", &File::isExecutable)
        .def("start", &File::start)
        .def("end", &File::end)
        .def("hasFrame", &File::hasFrame)
        .def("findFile", &File::findFile)
        .def("addRange", &File::addRange)
        .def("ranges", &File::ranges)
        .def("isValid", &File::isValid)
        .def("__eq__", [](const File &self, const File &other) { return self == other; })
        .def("__ne__", [](const File &self, const File &other) { return self != other; })
        .def("__lt__", [](const File &self, const File &other) { return self < other; })
        .def("__gt__", [](const File &self, const File &other) { return self > other; })
        .def("__copy__", [](const File& self) { return File(self); })
        .def("__deepcopy__", [](const File& self, py::dict) { return File(self); }, "memo"_a)
        .def_static("parse", &File::parse);

    // Bind the File::Type enum
    enum_<File::Type>(m, "FileType")
        .value("Frame", File::Type::Frame)
        .value("Sequence", File::Type::Sequence)
        .export_values();
}

}
}

PYBIND11_MODULE(PyColorman, m) {
    py::class_<QString>(m, "QString")
        .def(py::init([](const std::string& s) {
            return QString::fromStdString(s);
        }))
        .def("__str__", [](const QString &s) {
            return s.toStdString();
        });
    py::implicitly_convertible<py::str, QString>();
    // core
    colorman::core::declare_file(m);
}