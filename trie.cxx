#include "caleb-debug.hxx"
// #include "preney-bm.hxx"

#include <fstream>
#include <iterator>
#include <iostream>
#include "trie.hxx"

using namespace std;
//using namespace cxx_project;


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