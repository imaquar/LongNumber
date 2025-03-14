CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17 

SRCS = long_number.cpp pi_calc.cpp tests.cpp 
OBJS = $(SRCS:.cpp=.o)

all: pi test 

pi: pi_calc.o long_number.o
	$(CXX) $(CXXFLAGS) -o pi_calc pi_calc.o long_number.o
	./pi_calc 100

test: tests.o long_number.o
	$(CXX) $(CXXFLAGS) -o tests tests.o long_number.o
	./tests

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) pi_calc tests 

.PHONY: all clean