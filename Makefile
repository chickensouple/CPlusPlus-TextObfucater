SHELL := /bin/bash

TESTS := $(wildcard tests/programs/*.cpp)

test:
	@python main.py tests/programs/pascal.cpp tests/text/LifesForTheLiving.txt out.cpp

