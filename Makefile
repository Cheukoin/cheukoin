CXX=clang++
CXXFLAGS=-Wall -g -Wextra -Wformat=2 -Wno-format-nonliteral -Wshadow \
	-Wpointer-arith -Wcast-qual -Wmissing-prototypes -Wno-missing-braces \
	-D_GNU_SOURCE -O2 -std=c++11 -stdlib=libc++ -lsfml-graphics \
	-lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all:
	$(CXX) -o cheukoin Cheukoin/*.cpp $(CXXFLAGS)

test:
	$(CXX) -o cheukoin-tests Cheukoin/*.cpp CheukoinTests/main.cpp $(CXXFLAGS)

clean:
	rm cheukoin
