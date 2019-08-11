#include <Python.h>
#include "mylib.c"

/* This is where we define the PyMyArray object structure */
typedef struct {
    PyObject_HEAD
    /* Type-specific fields go below. */
    MyArray arr;
} PyMyArray;


/* This is the __init__ function, implemented in C */
static int
PyMyArray_init(PyMyArray *self, PyObject *args, PyObject *kwds)
{
    // init may have already been called
    if (self->arr.arr != NULL)
        deallocate_MyArray(&self->arr);

    int length = 0;
    static char *kwlist[] = {"length", NULL};
    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist, &length))
        return -1;

    if (length < 0)
        length = 0;

    initialize_MyArray(&self->arr, length);

    return 0;
}


/* this function is called when the object is deallocated */
static void
PyMyArray_dealloc(PyMyArray* self)
{
    deallocate_MyArray(&self->arr);
    Py_TYPE(self)->tp_free((PyObject*)self);
}


/* This function returns the string representation of our object */
static PyObject *
PyMyArray_str(PyMyArray * self)
{
  char* s = stringify(&self->arr, 10);
  PyObject* ret = PyUnicode_FromString(s);
  free(s);
  return ret;
}

/* Here is the type structure: we put the above functions in the appropriate place
   in order to actually define the Python object type */
static PyTypeObject PyMyArrayType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pymyarray.PyMyArray",        /* tp_name */
    sizeof(PyMyArray),            /* tp_basicsize */
    0,                            /* tp_itemsize */
    (destructor)PyMyArray_dealloc,/* tp_dealloc */
    0,                            /* tp_print */
    0,                            /* tp_getattr */
    0,                            /* tp_setattr */
    0,                            /* tp_reserved */
    (reprfunc)PyMyArray_str,      /* tp_repr */
    0,                            /* tp_as_number */
    0,                            /* tp_as_sequence */
    0,                            /* tp_as_mapping */
    0,                            /* tp_hash  */
    0,                            /* tp_call */
    (reprfunc)PyMyArray_str,      /* tp_str */
    0,                            /* tp_getattro */
    0,                            /* tp_setattro */
    0,                            /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,           /* tp_flags */
    "PyMyArray object",           /* tp_doc */
    0,                            /* tp_traverse */
    0,                            /* tp_clear */
    0,                            /* tp_richcompare */
    0,                            /* tp_weaklistoffset */
    0,                            /* tp_iter */
    0,                            /* tp_iternext */
    0,                            /* tp_methods */
    0,                            /* tp_members */
    0,                            /* tp_getset */
    0,                            /* tp_base */
    0,                            /* tp_dict */
    0,                            /* tp_descr_get */
    0,                            /* tp_descr_set */
    0,                            /* tp_dictoffset */
    (initproc)PyMyArray_init,     /* tp_init */
};

/* now we initialize the Python module which contains our new object: */
static PyModuleDef pymyarray_module = {
    PyModuleDef_HEAD_INIT,
    "pymyarray",
    "Extension type for myarray object.",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit_pymyarray(void) 
{
    PyObject* m;

    PyMyArrayType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&PyMyArrayType) < 0)
        return NULL;

    m = PyModule_Create(&pymyarray_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyMyArrayType);
    PyModule_AddObject(m, "PyMyArray", (PyObject *)&PyMyArrayType);
    return m;
}
