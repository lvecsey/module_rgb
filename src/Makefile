CC=gcc

module_rgb : LIBS=-lrt -ldl

module_rgb : module_rgb.o
	$(CC) -o $@ $^ $(LIBS)
