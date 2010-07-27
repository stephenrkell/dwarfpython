CXXFLAGS += -Iparser -I.
CXXFLAGS += -std=c++0x -g3 -fno-eliminate-unused-debug-types

LDLIBS += -lfl -lreadline -lffi -ldwarfpp -lsrk31c++ -lc++fileno -ldwarf -lelf -lgc -lstdc++ -lunwind -lunwind-ptrace -lunwind-x86 -lprocessimage -lboost_regex

C_SRC := buffer.c
CC_SRC := main.cc ops.cc

default: dwarfpy

.PHONY: clean
clean:
	rm -f dwarfpy *.o .*.d
	$(MAKE) -C parser clean

CC_DEPS := $(patsubst %.cc,.%.d,$(CC_SRC))
CPP_DEPS :=
C_DEPS += $(patsubst %.c,.%.d,$(C_SRC))
DEPS := $(CC_DEPS) $(CPP_DEPS) $(C_DEPS)

DEPS := $(CC_DEPS) $(C_DEPS) $(CPP_DEPS)

.PHONY: parser-recursive
parser-recursive: 
	$(MAKE) -C parser

$(CPP_DEPS): .%.d : %.cpp
	g++ -MM $(CXXFLAGS) "$<"  > "$@"
$(CC_DEPS): .%.d : %.cc
	g++ -MM $(CXXFLAGS) "$<"  > "$@"
$(C_DEPS): .%.d : %.c
	gcc -MM $(CFLAGS) "$<"  > "$@"

include $(DEPS)

dwarfpy: parser-recursive buffer.o ops.o
	$(CXX) $(CXXFLAGS) -o "$@" main.cc buffer.o ops.o parser/*.o parser/ast/*.o $(LDFLAGS) $(LDLIBS) 
