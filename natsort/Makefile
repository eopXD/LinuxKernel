CFLAGS = -Wall -g -Werror

OBJS = strnatcmp.o natsort.o

.PHONY: clean test

natsort: $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm natsort $(OBJS)
