CXX = g++
CXXFLAGS = -O3
NAME = serial.out

$(NAME): serial.cpp
		$(CXX) $(CXXFLAGS) -o $(NAME) serial.cpp

clean: 
		rm -f $(NAME)

test: $(NAME)
		./$(NAME)

.PHONY: clean