from distutils.core import setup, Extension
setup(ext_modules=[Extension("pymyarray", ["pymyarray.c"])])
