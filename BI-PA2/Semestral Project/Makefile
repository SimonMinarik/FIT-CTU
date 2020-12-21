NAME = minarsim
DXFILE = Doxyfile

CFLAGS = -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++14

RPG_SRCS = $(wildcard src/*.cpp)
RPG_OBJS = $(RPG_SRCS:.cpp=.o)

all:
	compile doc

run:
	./$(NAME) $(MAP) $(QUESTS) $(SAVES)

compile: $(RPG_OBJS)
	g++ $(CFLAGS) $(RPG_OBJS) -o ./$(NAME) -lncurses

doc:
	doxygen $(DXFILE)

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(RPG_OBJS) ./$(NAME) ./doc