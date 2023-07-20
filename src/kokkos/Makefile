KOKKOS_PATH = ${HOME}/kokkos
KOKKOS_DEVICES = "Serial"
EXE_NAME = "kokkosMMBench"

SRC = $(wildcard *.cpp)

default: build
	echo "Start Build"

CXX = g++
EXE = ${EXE_NAME}.host
KOKKOS_ARCH = ""

CXXFLAGS = -O3
LINK = ${CXX}
LINKFLAGS =

DEPFLAGS = -M

OBJ = $(SRC:.cpp=.o)
LIB =

include $(KOKKOS_PATH)/Makefile.kokkos

build: $(EXE)

$(EXE): $(OBJ) $(KOKKOS_LINK_DEPENDS)
	$(LINK) $(KOKKOS_LDFLAGS) $(LINKFLAGS) $(EXTRA_PATH) $(OBJ) $(KOKKOS_LIBS) $(LIB) -o $(EXE)

clean: kokkos-clean
	rm -f *.o *.host

# Compilation rules

%.o:%.cpp 
	$(CXX) $(KOKKOS_CXXFLAGS) $(CXXFLAGS) -c $<

#%.o:%.cpp $(KOKKOS_CPP_DEPENDS)
#	$(CXX) $(KOKKOS_CPPFLAGS) $(KOKKOS_CXXFLAGS) $(CXXFLAGS) $(EXTRA_INC) -c $<

test: $(EXE)
	./$(EXE)