CXX = g++
CXXFLAGS = -O3
NAME = ompMMBench.out

$(NAME): ompMMBench.cpp
		$(CXX) $(CXXFLAGS) -o $(NAME) ompMMBench.cpp -fopenmp

clean:
		rm -rf $(NAME)

test: $(NAME)
		./$(NAME)

.PHONY: clean