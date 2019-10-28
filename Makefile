CC=gcc
FLAGS=-Werror -Wall -Wno-unused-variable -std=c99
TARGET=bomblab
OBJS=bomblab.c

all: $(OBS)
	$(CC) $(FLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -rf $(TARGET)

dist:
	-rm -rf ./bomblab_source.zip
	zip -r bomblab_source.zip $(OBJS) Makefile solution.txt
