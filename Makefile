CXX ?= g++

CXXFLAGS ?= -D _DEBUG -ggdb3 -std=c++17 -O2 -g

cache.o: cache.cpp tests.cpp cache.hpp ideal_cache.hpp
	$(CXX) $(CXXFLAGS) cache.cpp tests.cpp -o $@

.PHONY: clean
clean:
	rm -rf *.o
