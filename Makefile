OBJS	= main.o
SOURCE	= main.cpp
HEADER	=
OUT	= vec
CC	 = clang++
FLAGS	 = -c -Wall -Wextra -Werror -pedantic -std=c++17
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	 $(CC) $(FLAGS) main.cpp

tidy:
	clang-tidy --checks='modernize*' vec.hpp -- -std=c++17

clean:
	rm -f $(OBJS) $(OUT)
