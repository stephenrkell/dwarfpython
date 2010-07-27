SRC := $(wildcard *.cc)

OBJS := $(patsubst %.cc,build/%.o,$(SRC))
LINKS := $(patsubst build/%.o,%.o,$(OBJS))

CXXFLAGS += -I..
CXXFLAGS += -I${HOME}/work/devel/dwarf/libdwarfpp/include
CXXFLAGS += -I${HOME}/work/devel/libsrk31c++
CXXFLAGS += -I${HOME}/work/devel/c++-fileno/include
CXXFLAGS += -I${HOME}/scratch/opt/include
CXXFLAGS += -I${HOME}/opt/include
CXXFLAGS += -Iparser
CXXFLAGS += -std=c++0x -g3

build/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o "$@" "$<"

%.o: build/%.o
	ln -s "$<" "$@"

default: $(OBJS) $(LINKS)

#objs-links:
#	for obj in $(OBJS); do if [ -h build ] && ! [ -e $$obj ]; then ln -s build/$$obj $$obj; fi; done
