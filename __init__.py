import ctypes

lib = ctypes.CDLL("./main.dll")
lib.main()
