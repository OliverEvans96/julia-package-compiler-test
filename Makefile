JL_SHARE = $(shell julia -e 'print(joinpath(Sys.BINDIR, Base.DATAROOTDIR, "julia"))')
CFLAGS   += $(shell $(JL_SHARE)/julia-config.jl --cflags)
CXXFLAGS += $(shell $(JL_SHARE)/julia-config.jl --cflags)
LDFLAGS  += $(shell $(JL_SHARE)/julia-config.jl --ldflags)
LDLIBS   += $(shell $(JL_SHARE)/julia-config.jl --ldlibs)
JFLAGS=$(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

CC=gcc
CXX=g++

.PHONY: all clean

all: test

clean:
	rm -f *.so test

%.so: %.jl
	julia -e 'using PackageCompiler; create_sysimage(script="$<", sysimage_path="$@")'

test: test.c myscript.so
	$(CC) -std=c99 -Wall -O0 $(JFLAGS) -ldl -ggdb $< -o $@
