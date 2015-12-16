all: example
	
example: example.o
	$(CC) -Wall -o $@ $^ -lusys -lubus2 -ljson-c -lblobpack

%.o: %.c
	$(CC) -Wall -c $^

clean: 
	rm -f example example.o

