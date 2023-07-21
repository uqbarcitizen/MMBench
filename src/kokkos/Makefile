KOKKOS_PATH = ${HOME}/kokkos
KOKKOS_DEVICES = "Serial,Cuda"
EXE_NAME = "kokkosMMBench"

SRC = $(wildcard *.cpp)

default: build
	echo "Start Build"

ifneq(,$(findstring Cuda,$(KOKKOS_DEVICES)))
CXX = ${KOKKOS_PATH}/bin/nvcc_wrapper
EXE = ${EXE_NAME}.cuda
KOKKOS_ARCH = "Maxwell50"
KOKKOS_CUDA_OPTIONS = "enable_lambda"
else
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
	rm -f *.o *.host *.cuda

# Compilation rules

%.o:%.cpp 
	$(CXX) $(KOKKOS_CXXFLAGS) $(CXXFLAGS) -c $<

#%.o:%.cpp $(KOKKOS_CPP_DEPENDS)
#	$(CXX) $(KOKKOS_CPPFLAGS) $(KOKKOS_CXXFLAGS) $(CXXFLAGS) $(EXTRA_INC) -c $<

test: $(EXE)
	./$(EXE)