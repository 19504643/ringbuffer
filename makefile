all: *.cpp
	g++ *.cpp -o ringbuf -lpthread -std=c++11 -std=gnu++11

clean:
	rm -rf *o ringbuf
