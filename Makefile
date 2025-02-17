CC = g++          
CFLAGS = -I"G:/msys2/mingw64/include" -I"./Libraries/Headers"
LIBFLAG = -L. -lessentials -lpath -lchecksum -lws2_32
TARGET = app_updater
SRC = updater.cpp checker.cpp

all: $(TARGET)

$(TARGET):
	$(CC) $(SRC) -o $(TARGET)  $(LIBFLAG) $(CFLAGS)

clean:
	@del /Q *.o app_updater.exe
	@rmdir /S /Q build

