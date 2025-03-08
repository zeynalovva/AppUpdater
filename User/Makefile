INCLUDE = -I"G:/msys2/mingw64/include"
LIBS = -L"G:\msys2\mingw64\lib" -L.
RUN = g++ updater.cpp -o update -lcurl -lessentials -lpath -lchecksum -lws2_32 -std=c++17 $(INCLUDE) $(LIBS)
TARGET = test.cpp


all: $(TARGET)

$(TARGET):
	$(RUN)


