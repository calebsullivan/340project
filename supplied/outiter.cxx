#include <iterator>
#include <iostream>
#include <vector>

template <typename OutIter, typename T>
void five_times(OutIter&& out, T const& value)
{
  for (unsigned i{}; i != 5U; ++i)
    *out++ = value;
}


int main()
{
  using namespace std;

  vector<double> v{ 1.1, 2.2, 3.3, 4.4, 5.5 };
  
  five_times(begin(v), 99.9);

  for (auto& e : v)
    cout << e << ' ';
  cout << endl;

  five_times(ostream_iterator<double>(cout, " "), 10.1);
  cout << endl;
}
