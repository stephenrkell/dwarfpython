CFLAGS := -I${HOME}/work/devel/dwarf/libdwarfpp/include

CXXFLAGS := -I${HOME}/work/devel/dwarf/libdwarfpp/include
CXXFLAGS += -I${HOME}/work/devel/libsrk31c++
CXXFLAGS += -I${HOME}/work/devel/c++-fileno/include
CXXFLAGS += -I${HOME}/work/devel/cake
CXXFLAGS += -I${HOME}/scratch/opt/include
CXXFLAGS += -I${HOME}/opt/include
CXXFLAGS += -Iparser
CXXFLAGS += -std=c++0x -g3
CXXFLAGS += -Wl,-R$$(readlink -f $${HOME}/work/devel/dwarf/libdwarfpp/src)
CXXFLAGS += -Wl,-R$$(readlink -f $${HOME}/work/devel/cake/libcake)

LIBS += -L${HOME}/opt/lib -L${HOME}/scratch/opt/lib 
LIBS += -L${HOME}/work/devel/dwarf/libdwarfpp/src
LIBS += -L${HOME}/work/devel/libsrk31c++/
LIBS += -L${HOME}/work/devel/cake/libcake
LIBS += -L${HOME}/work/devel/c++-fileno/lib
LIBS += -lfl -lreadline -lffi -ldwarfpp -lsrk31c++ -lfileno -ldwarf -lelf -lgc -lstdc++ -lcake

CC_SRC := main.cc

CC_DEPS := $(patsubst %.cc,.%.d,$(CC_SRC))
CPP_DEPS :=
C_DEPS += $(patsubst %.c,.%.d,$(C_SRC))
DEPS := $(CC_DEPS) $(CPP_DEPS) $(C_DEPS)

DEPS := $(CC_DEPS) $(C_DEPS) $(CPP_DEPS)

default: dwarfpy

.PHONY: parser
parser: 
	$(MAKE) -C parser

$(CPP_DEPS): .%.d : %.cpp
	g++ -MM $(CXXFLAGS) "$<"  > "$@"
$(CC_DEPS): .%.d : %.cc
	g++ -MM $(CXXFLAGS) "$<"  > "$@"
$(C_DEPS): .%.d : %.c
	gcc -MM $(CFLAGS) "$<"  > "$@"

include $(DEPS)

dwarfpy: parser
	$(CXX) $(CXXFLAGS) -o "$@" main.cc parser/*.o parser/ast/*.o $(LIBS) 
