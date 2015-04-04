#include "caleb-debug.hxx"
// #include "preney-bm.hxx"

#include <fstream>
#include <iterator>
#include <iostream>
#include "trie.hxx"

using namespace std;
//using namespace cxx_project;

template <typename OutIter>
std::size_t trie::output_matches(std::string const& pattern, OutIter&& out) const{
	size_t retval{};
	size_t cur_prefix_len = 0;
	queue<pair<std::string, trie const*>> bfs;
	

	bfs.emplace(string{}, this);

	er("output_matches start");

	//http://stackoverflow.com/a/9438329
	for(auto curchar : pattern){ // for each char in string
		// et(curchar);
		ftype(curchar);

		for(; bfs.front().first.size() == cur_prefix_len; ){
			auto node = bfs.front();
			eb("!");

			if(node.second == nullptr){ 
				//Guard against node's trie const* being nullptr. 
				
				continue;
			}
			auto child = node.second->children.find(curchar);
			auto childEnd = nullptr; //end iterator of the child map

			if(curchar != '?'){

				if(child != childEnd){

				}
			} else if(curchar == '?'){
				// range-based for loop that iterates over node's immediate children.
				for(auto child : node.second->children) 
					// where prefix is node.first + child.first
					bfs.emplace(prefix, child->second); //replace prefix	
			}

			bfs.pop();
		}
		++cur_prefix_len;
	}



	for(; !bfs.empty(); ){ // for each element in queue
		bool is_match = false;
		auto node = bfs.front(); // trie*

		// size() == pattern.size() AND if node's trie const* is not nullptr
		if(size() == pattern.size() && node_ptr.second != nullptr){
			auto i = node.second->children.find(char{});
			auto iEnd = node.second->children.end();

			if( i!=iEnd && i.second == nullptr){ //end of sequence marker found
				is_match = true;
			}

			if(is_match){
				//out + node.first //need to append iterator
				//out++ // ++iterator
				++retval;

			}
		}
		bfs.pop();
	}

	er("output_matches exit");
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