CXXFLAGS += -Iparser -I.
CXXFLAGS += -std=gnu++0x -g3 -fno-eliminate-unused-debug-types

# This order matters a lot! It controls inter-object static initialization order.
# (Recall: __attribute__((init_priority(N))) controls ordering
# *within* an object, but *between* CUs in that object.)
LDLIBS += \
-lreflect \
-lpmirror \
-ldwarfidl \
-lcxxgen \
-ldwarfpp \
-lsrk31c++ \
-lboost_regex \
-lc++fileno \
-lstdc++ \
-lunwind -lunwind-ptrace -lunwind-$(shell uname -m) \
-lgc \
-lffi \
-ldwarf \
-lelf \
-lfl \
-lreadline 

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

ifneq ($(MAKECMDGOAL),clean)
-include $(DEPS)
endif

libdwarfpy.a: init.o buffer.o ops.o function_definition.o util.o arithmetic.o assign.o control.o resolve.o archdep.o parser/*.o parser/ast/*.o| parser-recursive
	ar r "$@" $^

dwarfpy: parser-recursive main.o libdwarfpy.a
	$(CXX) $(CXXFLAGS) -o "$@" main.cc -L. -ldwarfpy $(LDFLAGS) $(LDLIBS) 

debug-fac: dwarfpy
	gdb dwarfpy --eval-command "run <<<\$$'def fac(n):\n\tif n == 0: return 1\n\tprint \"calculating fac of \"\n\tprint n\n\treturn n * fac(n-1)\n\nprint fac(2)\n'"

debug-cmp: dwarfpy
	gdb dwarfpy --eval-command "break 'ComparisonOperator::compare(val, val)'" --eval-command "run <<<\$$'print (0 == 0)\nprint(1 == 1)\nprint(1 == 0)\nprint(1 > 0)\nprint(1 >= 0)\nprint(1 < 0)\nprint(1 <= 0)\nif 1:\n\tprint \"1 is true\"\nelse:\n\tprint \"1 is false\"\n\n'"
