CXX = g++

debug_or_optimize = -O1
CXXFLAGS = -Wall -Werror -pedantic --std=c++11 $(debug_or_optimize)

card_test_srcs = $(wildcard Card_test*.cpp)
card_test_exes = $(card_test_srcs:.cpp=.exe)

pack_test_srcs = $(wildcard Pack_test*.cpp)
pack_test_exes = $(pack_test_srcs:.cpp=.exe)

player_test_srcs = $(wildcard Player_test*.cpp)
player_test_exes = $(player_test_srcs:.cpp=.exe)

all: test

debug: debug_or_optimize = -g
debug: test

test: Card_tests Pack_tests Player_tests Card_public_test Pack_public_test Player_public_test euchre
	python run_my_tests.py
	./Card_public_test
	./Pack_public_test
	./Player_public_test

	./euchre pack.in noshuffle 1 Alice Simple Bob Simple Cathy Simple Drew Simple > euchre_test00.out
	diff -q euchre_test00.out euchre_test00.out.correct
	./euchre pack.in shuffle 10 Alice Simple Bob Simple Cathy Simple Drew Simple > euchre_test01.out
	diff -q euchre_test01.out euchre_test01.out.correct
	./euchre pack.in noshuffle 1 Alice Human Bob Human Cathy Human Drew Human < euchre_test50.in > euchre_test50.out
	diff -q euchre_test50.out euchre_test50.out.correct


Card_public_test: Card.cpp Card_public_test.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Card_tests: $(card_test_exes)
Card_test%.exe: Card.cpp Card_test%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Pack_public_test: Card.cpp Pack.cpp Pack_public_test.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Pack_tests: $(pack_test_exes)
Pack_test%.exe: Card.cpp Pack.cpp Pack_test%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Player_public_test: Card.cpp Player.cpp Player_public_test.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Player_tests: $(player_test_exes)
Player_test%.exe: Card.cpp Player.cpp Player_test%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

euchre: Card.cpp Pack.cpp Player.cpp euchre.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.SUFFIXES:

.PHONY: clean
clean:
	rm -vf *.out *.exe euchre Card_public_test Pack_public_test Player_public_test
