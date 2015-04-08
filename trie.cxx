#include <fstream>
#include <iterator>
#ifndef _IOSTREAM
#define _IOSTREAM
  #include <iostream>
#endif
#include "trie.hxx"

using namespace std;
using namespace cxx_project;

template <typename OutIter>
std::size_t trie::output_matches(std::string const& pattern, OutIter&& out) const{
	size_t retval {};
	size_t cur_prefix_len {};
	queue<pair<std::string, trie const*>> bfs;
	
	bfs.emplace(string{}, this);

	for(auto curchar : pattern){ // for each char in string
		while(bfs.front().first.size() == cur_prefix_len && !bfs.empty()){
			auto node = bfs.front();
			if(node.second == nullptr){ 
				bfs.pop();
				continue;
			}
			auto child = node.second->children.find(curchar);
			auto childEnd = node.second->children.end(); //end iterator of the child map

			if(curchar != '?'){
				if(child != childEnd){ //this is a possible match
					bfs.emplace(node.first + curchar, child->second);
				}
			} else if(curchar == '?'){
				for(auto child : node.second->children) 
					bfs.emplace(node.first + child.first, child.second); //possible match	
			}
			bfs.pop();
		}
		++cur_prefix_len;
	}

	while(!bfs.empty()){
		bool is_match = false;
		auto node = bfs.front(); // trie*

		if(node.first.size() == pattern.size() && node.second != nullptr){
			auto i = node.second->children.find(char{});
			auto iEnd = node.second->children.end();

			if( i!=iEnd && i->second == nullptr){ //end of sequence marker found
				is_match = true;
			}

			if(is_match){
				++out;
				*out = node.first;
				++retval;
			}
		}
		bfs.pop();
	}

	return retval;
}


// int main(int argc, char *argv[])
// {
//   trie n;

//   string test = "ab";

//   n.add(test);
//   n.add(string("abcde"));
//   n.add(string("abcdd"));
//   n.add(string("airplane"));
//   n.add(string("airlock"));
//   n.print_inorder(cout);

//   trie o = n;

//   bool b2 = o.find(string("airplane"));
//   bool b3 = o.find(string("airlock"));
//   bool b4 = o.find(string("a"));
//   cout << b2 << b3 << b4 << '\n'; // Outputs: 110
// }


template <typename OutIter, typename T>
void five_times(OutIter&& out, T const& value)
{
  for (unsigned i{}; i != 5U; ++i)
    *out++ = value;
}

// int main()
// {
//   using namespace std;

//   vector<double> v{ 1.1, 2.2, 3.3, 4.4, 5.5 };
  
//   five_times(begin(v), 99.9);

//   for (auto& e : v)
//     cout << e << ' ';
//   cout << endl;

//   five_times(ostream_iterator<double>(cout, " "), 10.1);
//   cout << endl;
// }

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    cerr << "Usage: " << argv[0] << " <FILENAME> <PATTERN>" << endl;
    return 1;
  }

  try
  {
    trie t;

    ifstream in(argv[1]);
    for (string s; in >> s; )
      t.add(s);

    auto count = t.output_matches(
      argv[2],
      ostream_iterator<string>(cout, "\n")
    );

    cout 
      << "\n" 
      << count 
      << (count != 1 ? " matches were found." : " match was found.")
      << endl
    ;
  }
  catch (...)
  {
    cerr << "EXCEPTION OCCURRED! Aborting..." << endl;
  }
}