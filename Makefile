OBJS	= build/main.o
SOURCE	= main.cpp
HEADER	=
OUT	= build/vec
CC	 = clang++
FLAGS	 = -c -g -Wall -Wextra -Werror -Wpedantic -std=c++17
LFLAGS	 =
# LFLAGS	 = -fsanitize=address -fno-omit-frame-pointer
# LFLAGS	 = -fsanitize=memory -fPIE -pie  -fno-omit-frame-pointer
# LFLAGS	 = -fsanitize=undefined -fno-omit-frame-pointer

all: $(OBJS)
	$(CC) $(SOURCE) -o $(OUT) $(LFLAGS)

build/main.o: main.cpp vec.hpp iterator.hpp
	 $(CC) $(FLAGS) main.cpp

tidy:
	clang-tidy *.hpp -- -std=c++17

clean:
	rm -f $(OBJS) $(OUT)

run:
	$(OUT)
