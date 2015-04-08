all: 
	clang++ -std=c++11 -Wall -Wextra -o a.out trie.cxx

arun:
	clang++ -std=c++11 -Wall -Wextra -o a.out trie.cxx && ./a.out wn.txt 'c?t'

crun:
	clang++ -std=c++11 -Wall -Wextra -o a.out trie.cxx && ./a.out web1913.txt 'c?t'

run:
	./a.out

valgrind:
	clang++ -std=c++11 -Wall -Wextra -o a.out trie.cxx && valgrind ./a.out wn.txt 'c?t'

help:
	@echo "Usage: make || make run"

clean:
	@rm a.out