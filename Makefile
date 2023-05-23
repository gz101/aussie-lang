CXX = clang++
CFLAGS = -std=c++11 -O2

all: aussie tests

aussie: main.o lexer.o
	$(CXX) $(CFLAGS) main.o lexer.o -o aussie

main.o: main.cpp lexer.h
	$(CXX) $(CFLAGS) -c main.cpp

lexer.o: lexer.cpp lexer.h
	$(CXX) $(CFLAGS) -c lexer.cpp

tests: test_lexer.o lexer.o
	$(CXX) $(CFLAGS) test_lexer.o lexer.o -o tests

test_lexer.o: test_lexer.cpp lexer.h
	$(CXX) $(CFLAGS) -c test_lexer.cpp

clean:
	rm -f *.o aussie tests
