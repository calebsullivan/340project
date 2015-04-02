all: 
	clang++ -std=c++11 -Wall -Wextra -o a.out trie.cxx

trie:
	clang++ -std=c++11 -Wall -Wextra -o a.out trie.cxx

crun:
	clang++ -std=c++11 -Wall -Wextra -o a.out trie.cxx && ./a.out

run:
	./a.out

valgrind:
	clang++ -std=c++11 -Wall -Wextra -o a.out trie.cxx && valgrind ./a.out

help:
	@echo "Usage: make || make run"

clean:
	@rm a.out