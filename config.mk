ifndef CPPFLAGS
CPPFLAGS=
endif

CPPFLAGS+=-I..

ifndef CFLAGS
CFLAGS=
endif

ifndef CXXFLAGS
CXXFLAGS=
endif

ifndef LDFLAGS
LDFLAGS=
endif

ifdef WIN32
# You might need to adjust these depending on your MinGW installation
# The default assumes cross-compiling on a Debian-like distro.
HOST=i586-mingw32msvc
TOOL_PREFIX=$(HOST)-
HOST_PREFIX=/usr/$(HOST)
CPPFLAGS+=-DMTK_WIN32=1 -I$(HOST_PREFIX)/include
LDFLAGS+=-L$(HOST_PREFIX)/lib
DLLEXT=.dll
EXEEXT=.exe
else
TOOL_PREFIX=
DLLEXT=.so
EXEEXT=
endif

CC=$(TOOL_PREFIX)cc
CXX=$(TOOL_PREFIX)c++
