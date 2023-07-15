CC = g++
CFLAGS = -Wall
NAME = serial.out

$(NAME): serial.cpp
		$(CC) $(CFLAGS) -o $(NAME) serial.cpp

clean:
		rm -f $(NAME)

test: $(NAME)
		./$(NAME)

.PHONY: clean