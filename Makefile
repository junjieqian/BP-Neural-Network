CC = g++
DEBUG = -g
SOURCE_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(SOURCE_FILES:.cpp=.o)))
CFLAGS = -c -Wall -std=c++11 $(DEBUG) -I./include
LDFLAGS = -pthread

BPNN: $(OBJ_FILES)
	$(CC) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY:clean

clean:
	rm -rf ./obj/*.o BPNN
