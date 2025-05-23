//
// Created by rafal on 5/23/25.
//

#define PY_SSIZE_T_CLEAN

#include <Python.h>

#include "RafLaz.h"

static PyObject *wrap_foo(PyObject *self, PyObject *args) {
    int32_t result = Foo();
    return PyLong_FromLong(result);
}

static PyMethodDef RafLazMethods[] = {
    {"foo", wrap_foo, METH_NOARGS, "Execute the RafLaz::Foo function."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef raflaz_module = {
    PyModuleDef_HEAD_INIT,
    "raflaz",
    "Python interface for raflaz library",
    -1,
    RafLazMethods
};

PyMODINIT_FUNC PyInit_raflaz(void) {
    return PyModule_Create(&raflaz_module);
}
