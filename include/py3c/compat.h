/* Copyright (c) 2015, Red Hat
 * Licensed under the MIT license; see py3c.h
 */

#ifndef _PY3C_COMPAT_H_
#define _PY3C_COMPAT_H_
#include <Python.h>

#if PY_MAJOR_VERSION >= 3

/***** Python 3 *****/

#define IS_PY3 1

/* Strings */

#define PyStr_Type PyUnicode_Type
#define PyStr_Check PyUnicode_Check
#define PyStr_CheckExact PyUnicode_CheckExact
#define PyStr_FromString PyUnicode_FromString
#define PyStr_FromStringAndSize PyUnicode_FromStringAndSize
#define PyStr_FromFormat PyUnicode_FromFormat
#define PyStr_FromFormatV PyUnicode_FromFormatV
#define PyStr_AsString PyUnicode_AsUTF8
#define PyStr_Concat PyUnicode_Concat
#define PyStr_Format PyUnicode_Format
#define PyStr_InternInPlace PyUnicode_InternInPlace
#define PyStr_InternFromString PyUnicode_InternFromString
#define PyStr_Decode PyUnicode_Decode

#define PyStr_AsUTF8String PyUnicode_AsUTF8String // returns PyBytes
#define PyStr_AsUTF8AndSize PyUnicode_AsUTF8AndSize

/* Ints */

#define PyInt_FromLong PyLong_FromLong
#define PyInt_AsLong PyLong_AsLong
#define PyInt_Check PyLong_Check

/* Module init */

#define MODULE_INIT_FUNC(name) \
    PyMODINIT_FUNC PyInit_ ## name(void); \
    PyMODINIT_FUNC PyInit_ ## name(void)

/* Types */

#define Py_TPFLAGS_HAVE_WEAKREFS 0
#define Py_TPFLAGS_HAVE_ITER 0

#else

/***** Python 2 *****/

#define IS_PY3 0

/* Strings */

#define PyStr_Type PyString_Type
#define PyStr_Check PyString_Check
#define PyStr_CheckExact PyString_CheckExact
#define PyStr_FromString PyString_FromString
#define PyStr_FromStringAndSize PyString_FromStringAndSize
#define PyStr_FromFormat PyString_FromFormat
#define PyStr_FromFormatV PyString_FromFormatV
#define PyStr_AsString PyString_AsString
#define PyStr_Concat PyString_Concat
#define PyStr_Format PyString_Format
#define PyStr_InternInPlace PyString_InternInPlace
#define PyStr_InternFromString PyString_InternFromString
#define PyStr_Decode PyString_Decode

#define PyStr_AsUTF8String(unicode) PyString_AsEncodedString(unicode, "UTF-8", "strict")
#define PyStr_AsUTF8AndSize(pystr, sizeptr) \
    ((*sizeptr=PyString_Size(pystr)), PyString_AsString(pystr))

#define PyBytes_Type PyString_Type
#define PyBytes_Check PyString_Check
#define PyBytes_CheckExact PyString_CheckExact
#define PyBytes_FromString PyString_FromString
#define PyBytes_FromStringAndSize PyString_FromStringAndSize
#define PyBytes_FromFormat PyUnicode_FromFormat
#define PyBytes_FromFormatV PyUnicode_FromFormatV
#define PyBytes_Size PyString_Size
#define PyBytes_GET_SIZE PyString_GET_SIZE
#define PyBytes_AsString PyString_AsString
#define PyBytes_AS_STRING PyString_AS_STRING
#define PyBytes_AsStringAndSize PyString_AsStringAndSize
#define PyBytes_Concat PyString_Concat
#define PyBytes_ConcatAndDel PyString_ConcatAndDel
#define _PyBytes_Resize _PyString_Resize

/* Module init */

#define PyModuleDef_HEAD_INIT 0

typedef struct PyModuleDef {
    int m_base;
    const char* m_name;
    const char* m_doc;
    Py_ssize_t m_size;
    PyMethodDef *m_methods;
} PyModuleDef;

#define PyModule_Create(def) \
    Py_InitModule3((def)->m_name, (def)->m_methods, (def)->m_doc)

#define MODULE_INIT_FUNC(name) \
    static PyObject *PyInit_ ## name(void); \
    void init ## name(void); \
    void init ## name(void) { PyInit_ ## name(); } \
    static PyObject *PyInit_ ## name(void)


#endif

#endif
