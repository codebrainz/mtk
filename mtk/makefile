include ../config.mk

LIB_NAME=libmtk$(DLLEXT)
SOURCES=win32app.cc win32log.cc
OBJECTS=$(SOURCES:.cc=.o)

ifndef WIN32
CXXFLAGS+=-fPIC
endif

all: $(LIB_NAME) demo$(EXEEXT)

$(LIB_NAME): $(OBJECTS)
	$(CXX) -shared $(strip $(CPPFLAGS) $(CXXFLAGS)) -o $@ $(OBJECTS) $(strip $(LDFLAGS))

%.o: %.cc makefile
	$(CXX) -c $(strip $(CPPFLAGS) $(CXXFLAGS)) -o $@ $<

demo$(EXEEXT): demo.cc $(LIB_NAME)
	$(CXX) $(strip $(CPPFLAGS) $(CXXFLAGS)) -o $@ $^

-include makefile.deps
makefile.deps: $(SOURCES)
	$(CXX) -MM $(strip $(CPPFLAGS) $(CXXFLAGS)) $(SOURCES) > $@

clean:
	$(RM) *.[ao] *.so *.dylib *.dll *.exe
