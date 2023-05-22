import ctypes

fts_lib = ctypes.cdll.LoadLibrary('libmiaufts.so')

fts_lib.search.restype = ctypes.py_object
fts_lib.indexator.restype = ctypes.py_object