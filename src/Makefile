CC = gcc
COMPILER_FLAGS = -std=c99 -fstack-protector-all
LINKER_FLAGS = -lm
EXEC_NAME = siguel
OBJECTS = *.c util/*.c arquivos/*.c nx/*.c svg/*.c figuras/*.c 

siguel: $(OBJECTS)
	$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

clean:
	rm -rf *.o
