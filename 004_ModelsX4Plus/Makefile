# Makefile 适合 MSVC2022 namke
# 编译器和链接器
CC = cl.exe
LINK = link.exe

# 编译和链接选项
CFLAGS = /nologo /W3 /EHsc  /Ox /DNDEBUG  /I..\TypeLibs  /D_CRT_SECURE_NO_WARNINGS
LDFLAGS = /nologo  Gdi32.lib user32.lib Kernel32.lib comctl32.lib Shell32.lib Comdlg32.lib winmm.lib

# 源文件和资源文件
SOURCE = start_GuiLauncher.cpp radio_button.cpp  main.cpp
RC_FILE = resource.rc
RESOURCES = resource.res

# 目标文件
OBJECT = $(SOURCE:.cpp=.obj)

# 最终输出
TARGET = X4PlusLauncher.exe

all: $(TARGET)

$(TARGET): $(OBJECT) $(RESOURCES)
    $(LINK) $(LDFLAGS) /out:$@ $(OBJECT) $(RESOURCES)

$(RESOURCES): $(RC_FILE)
    rc.exe /fo$@ $(RC_FILE)

.cpp.obj:
    $(CC) $(CFLAGS) /c $<

clean:
    del *.obj *.res *.dll *.orig X4PlusLauncher.exe


.PHONY: all clean