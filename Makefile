CXX=g++
CXXFLAGS=-std=c++11 -g -Werror -Wall -Wextra
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Demo.cpp
#SOURCES=Node.cpp Tree.cpp TestCounter.cpp Test.cpp Demo.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

#run: test 
run: tree
	./$^

tree: Demo.o 
	$(CXX) $(CXXFLAGS) $^ -o tree	

test: TestCounter.o Test.o node.o tree.o complex.o
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: tree test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o tree test
