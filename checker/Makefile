CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -D CMS -D TESTSYS
CHECKER_LIST = diff float_diff car busker_checker

all: $(CHECKER_LIST)

clean:
	rm -f $(CHECKER_LIST)

car: car.cpp
	$(CC) car.cpp $(CCARGS) -o car

diff: diff.cpp
	$(CC) diff.cpp $(CCARGS) -o diff

float_diff: float_diff.cpp
	$(CC) float_diff.cpp $(CCARGS) -o float_diff

busker_checker: busker_checker.cpp
	$(CC) $< $(CCARGS) -o $@
