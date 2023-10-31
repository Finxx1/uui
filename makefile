TARGET = uui_example
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib
INC_DIR = include
OBJ_DIR = obj

LIBS = \
kernel32.lib \
user32.lib \
gdi32.lib \
advapi32.lib \
comdlg32.lib

all:
	$(CC) /Fe$(BIN_DIR)\$(TARGET).exe /I$(INC_DIR) $(SRC_DIR)\*.c /Fo$(OBJ_DIR)\ /link /LIBPATH:$(LIB_DIR) $(LIBS)
	