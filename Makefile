CC=gcc
CFLAGS=-Wall -Wextra

example: example.c
	$(CC) $(CFLAGS) -o $@ $<;
	./example
	make display
clean:
	rm -f example
display: output.ppm
	xdg-open $<