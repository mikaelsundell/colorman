// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "pythoninterpreter.h"
#include <core/macro.h>

#undef slots // ignore slots in Qt headers
#include <Python.h>
#define slots Q_SLOTS

#include <QPointer>
#include <QDebug>

extern "C" PyObject* PyInit_colorman_wrapper();

namespace colorman {

QScopedPointer<PythonInterpreter, PythonInterpreter::Deleter> PythonInterpreter::ip;

class PythonInterpreterPrivate
{
    public:
        PythonInterpreterPrivate();
        void init();
        void release();
    
    public:
        QString executeScript(const QString& script) const;
        QString pythonError() const;
        
    public:
        PyObject* globals;
        PyObject* locals;
};

PythonInterpreterPrivate::PythonInterpreterPrivate()
{
}

void
PythonInterpreterPrivate::init()
{
    if (PyImport_AppendInittab("colorman", PyInit_colorman_wrapper) == -1) {
        Q_ASSERT_X(false, "Python Init", "Failed to add 'colorman' to the interpreter's module table");
    }
    Py_Initialize();
    globals = PyDict_New();
    locals = PyDict_New();
    PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());
}

void
PythonInterpreterPrivate::release()
{
    Py_DECREF(globals);
    Py_DECREF(locals);
    Py_Finalize();
}

QString
PythonInterpreterPrivate::executeScript(const QString& script) const
{
    QString output;
    PyGILState_STATE gilstate = PyGILState_Ensure();
    QByteArray scriptBytes = script.toUtf8();
    const char* scriptCStr = scriptBytes.constData();
    PyObject* value = PyRun_String(scriptCStr, Py_single_input, globals, locals);
    if (value != nullptr) {
        PyObject* str = PyObject_Str(value);
        output = PyUnicode_AsUTF8(str);
        Py_DECREF(str);
        Py_DECREF(value);
    } else {
        output = pythonError();
    }
    PyGILState_Release(gilstate);
    return output;
}


QString
PythonInterpreterPrivate::pythonError() const
{
    PyObject* type, *value, *traceback;
    PyErr_Fetch(&type, &value, &traceback); // Fetch the error
    QString errormessage;
    if (type != nullptr) {
        PyObject* str_obj = PyObject_Str(type);
        if (str_obj != nullptr) {
            errormessage += QString::fromUtf8(PyUnicode_AsUTF8(str_obj));
            Py_DECREF(str_obj);
        }
        Py_DECREF(type);
    }
    if (value != nullptr) {
        errormessage += ": ";
        PyObject* str_obj = PyObject_Str(value);
        if (str_obj != nullptr) {
            errormessage += QString::fromUtf8(PyUnicode_AsUTF8(str_obj));
            Py_DECREF(str_obj);
        }
        Py_DECREF(value);
    }
    if (traceback != nullptr) {
        errormessage += "\nTraceback: ";
        PyObject* str_obj = PyObject_Str(traceback);
        if (str_obj != nullptr) {
            errormessage += QString::fromUtf8(PyUnicode_AsUTF8(str_obj));
            Py_DECREF(str_obj);
        }
        Py_DECREF(traceback);
    }
    return errormessage;
}

PythonInterpreter::PythonInterpreter()
: p(new PythonInterpreterPrivate())
{
}

PythonInterpreter::~PythonInterpreter()
{
    release();
}

PythonInterpreter*
PythonInterpreter::instance()
{
    if (!ip) {
        ip.reset(new PythonInterpreter);
    }
    return ip.data();
}

void
PythonInterpreter::init()
{
    CoreDebug() << "init";
    p->init();
}

void
PythonInterpreter::release()
{
    CoreDebug() << "release";
    p->release();
}

QString PythonInterpreter::executeScript(const QString& script) const {
    return p->executeScript(script);
}

}
