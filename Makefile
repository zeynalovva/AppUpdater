TARGET = app_updater
INCLUDE = -I"G:/msys2/mingw64/include"
LIBS = -L"G:\msys2\mingw64\lib"
FTP = FTPClient
FTPRun = g++ .\GenerateHash\FTPClient.cpp -o FTPTest -lcurl -lws2_32 -std=c++17 $(INCLUDE) $(LIBS)
AppRun = g++ .\GenerateHash\updater.cpp .\GenerateHash\checker.cpp -o app_updater -L. -lessentials -lpath -lchecksum -lws2_32 $(INCLUDE) -I"./Libraries/Headers"

all: $(TARGET) $(FTP)

$(TARGET):
	$(AppRun)
$(FTP):
	$(FTPRun)

clean:
	@del /Q *.o app_updater.exe
	@del /Q *.o FTPClient.exe
	@rmdir /S /Q build


