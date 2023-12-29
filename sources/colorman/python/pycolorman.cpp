// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include <Python.h>
#include "colorman.h"

static PyModuleDef yourappModule = {
    PyModuleDef_HEAD_INIT,
    "colorman",
    "Python interface for the colorman application",
    -1,
    nullptr, nullptr, nullptr, nullptr, nullptr
};

typedef struct {
    PyObject_HEAD
    colorman::Colorman* colorman;
} PyColormanObject;

static void PyColorman_dealloc(PyColormanObject *self) {
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *PyColorman_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    PyColormanObject *self;
    self = (PyColormanObject *) type->tp_alloc(type, 0);
    if (self != nullptr) {
        self->colorman = colorman::Colorman::instance();
    }
    return (PyObject *) self;
}

static PyObject *PyColorman_open(PyColormanObject *self, PyObject *args) {
    const char *fileName;
    if (!PyArg_ParseTuple(args, "s", &fileName))
        return nullptr;
    self->colorman->open(fileName);
    Py_RETURN_NONE;
}

static PyMethodDef PyColorman_methods[] = {
    {"open", (PyCFunction) PyColorman_open, METH_VARARGS, "Open a file"},
    {nullptr}
};

static PyTypeObject PyColormanType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
    .tp_name = "colorman.Colorman",
    .tp_basicsize = sizeof(PyColormanObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyColorman_new,
    .tp_dealloc = (destructor) PyColorman_dealloc,
    .tp_methods = PyColorman_methods,
};

PyMODINIT_FUNC PyInit_colorman(void) {
    PyObject *module;

    if (PyType_Ready(&PyColormanType) < 0)
        return nullptr;

    module = PyModule_Create(&yourappModule);
    if (module == nullptr)
        return nullptr;

    Py_INCREF(&PyColormanType);
    if (PyModule_AddObject(module, "Colorman", (PyObject *) &PyColormanType) < 0) {
        Py_DECREF(&PyColormanType);
        Py_DECREF(module);
        return nullptr;
    }

    return module;
}

// pycolorman wrapper
extern "C" PyObject* PyInit_colorman_wrapper() {
    return PyInit_colorman();
}
