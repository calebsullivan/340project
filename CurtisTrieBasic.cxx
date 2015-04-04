#include <map>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

//
// trie_node
//
// Implements a trie. This version is hard-coded to use char. The
// end-of-sequence value is a map entry of { char{}, nullptr }.
// This permits char{} values to be within the string as no other
// map entries will have nullptr values stored in them in the entire
// trie.
//
// NOTE: Some functions are provided and some are not. You must write
//       the missing code.
//
class trie_node
{
public:
  using value_type = char;

private:
  using elem_type = char;
  using child_node_type = trie_node*;

  map< elem_type, child_node_type > children;

public:
  //
  // Default construction is simple: since the children map has a default
  // uctor, no data is needed in it, and that is the only data
  // member, let the compiler generate the code...
  //
  trie_node() = default;

  //
  // Copy construction performs a breadth-first search (BFS) of the trie
  // being copied from. The BFS is tracked using a std::vector as a queue
  // where the vector is a pair of trie_node*. The pair of trie_node*
  // is used to simultaneously track the BFS in the source trie with the
  // corresponding element in the BFS construction of the *this trie.
  //
  // Know that a BFS traversal of a tree uses a queue. Essentially, one
  // visits a node, queues all its children, and then repeat processing
  // the next element at the front of the queue until the queue is empty.
  //
  // For time reasons this code has been provided to you. Do take note
  // how the solution is crafted using contrainers, etc.
  //
  trie_node(trie_node const& n)
  {
    // stack: breadth first search, std::pair< newtrie, oldtrie >
    std::vector< std::pair<trie_node*, trie_node const*> > stack;

    // Start stack with (this, &n)...
    stack.emplace_back(this, &n);

    do
    {
      auto curpos = stack.back(); 
      stack.pop_back();

      // If this node has no children, then record such and loop...
      if (curpos.second == nullptr)
      {
        curpos.first = nullptr;
        continue;
      }

      // Enumerate all children...
      for (
        auto i=begin(curpos.second->children), 
          iEnd = end(curpos.second->children);
        i != iEnd;
        ++i
      )
      {
        // Create the child trie_node iff i->second != nullptr.
        // If i->second == nullptr then it is an end-of-sequence character.
        trie_node* tmp_node{
          (i->second != nullptr)
          ? new trie_node
          : nullptr
        };

        // Copy the new node...
        curpos.first->children.emplace(
          i->first, tmp_node
        );

        // And continue updating the stack queue...
        stack.emplace_back( tmp_node, i->second );
      }
    } while (!stack.empty());
  }

  //
  // HINT: 1) Create a local trie_node variable as n is const.
  //       2) Use swap.
  //
  trie_node& operator =(trie_node const& n)
  // see copy and swap ideom: http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Copy-and-swap
  {
    trie_node temp (n);
    temp.swap (*this);
    return *this;
  }

  //
  // Move constructor.
  //
  // HINT: There is only one data member. Try moving it! :-)
  //
  // RESTRICTION: No code must appear inside the { } braces.
  //
  trie_node(trie_node&& n) : children(std::move(n.children)) {};

  //
  // Move assignment operator.
  //
  // HINT: The trie_node class has a swap() member function. Use it!
  //
  trie_node& operator =(trie_node&& n)
  {
    return n;
  }
  

  //
  // TODO: Destructor.
  //
  // HINT: The trie_node class has a clear() member function. Use it!
  //
  ~trie_node() 
  {
    clear();
  }
 
  //
  // TODO: swap().
  //
  // HINT: You know how to swap variables using a temporary variable.
  //
  //       Do exactly this.
  //
  //       Now add std::move() around each variable on the right-hand
  //       side of each assignment operator. This will allow moves
  //       instead of copies where possible.
  //
  void swap(trie_node& n)
  {
    trie_node temp;
    temp.children = std::move(children);
    children = std::move(n.children);
    n.children = std::move(temp.children);
  }


  //
  // TODO: clear()
  //
  // HINT: Like the copy constructor, clear() will traverse the trie
  //       using breadth-first search.
  //
  //       Look up std::queue in your textbooks. You'll notice the
  //       functions: push(), pop(), front(), back(), and empty().
  //
  //       Pseudocode is given in the task description within the
  //       project.
  //
  // RESTRICTION: You must use std::queue<trie_node*> to do this 
  //              solution.
  //
  void clear()
  {
    queue<trie_node*> bfs;
    //  cout << "start clear" << endl;

    for ( bfs.push(this); !bfs.empty(); bfs.pop() )
    {
      ///cout<<"forStart ";
      
      trie_node* nodePtr = bfs.front();
      
      if ( !nodePtr->children.empty() )
      // if node pointer has children nodes
      // 1: Use a range-based for loop to loop all of the children. Add each child node's trie_node* to the bfs queue.
      // 2: After the range-based for loop, clear() all of nodePtr's children data.
      { 
        // 1
        for (auto&& child : nodePtr->children ) 
        {
          if (child.second != nullptr)
            bfs.push(child.second);
        }

        // 2
        nodePtr->children.clear();
      }

      if (nodePtr != this)
      //If node_ptr is not equal to the this pointer, invoke "delete node_ptr;".
      {
        //cout<<"predelete ";
        delete nodePtr;
        //cout<<"postdelete ";
      }
      //cout<<"forend"<<endl;
    }
  }



  //
  // This is the code done in class for the add() function except
  // support has been added to handle an end-of-sequence marker.
  //
  // NOTE: Notice the use of emplace() instead of insert().
  //       The emplace() function passes its arguments directly
  //       to the constructor of the std::pair in the map.
  //
  void add(std::string const& s)
  {
    // Start at this (root) node...
    trie_node* curpos = this;

    // Build trie for s...
    for (auto i=begin(s), iEnd=end(s); i != iEnd; ++i)
    {
      // Add the next sequence value...
      //  result's type: pair<iterator, bool>
      auto result = curpos->children.emplace(elem_type(*i), nullptr);

      // If the next sequence value was inserted, then ensure
      // a default trie_node is allocated with new...
      if (result.second)
      {
        // *i is not already stored and next entry must at least 
        // be end-of-string...
        result.first->second = new trie_node;
      }

      // Continue with next node's information...
      curpos = result.first->second; 
    }

    // When done adding the sequence, ensure there is an end-of-sequence
    // value added...
    curpos->children.emplace(elem_type{}, nullptr);
  }

  //
  // This is the code done in class for the find() function except
  // support has been added to handle an end-of-sequence marker.
  //
  bool find(std::string const& s) const
  {
    bool retval = false;
    trie_node const * curpos = this;

    for (auto curvalue : s)
    {
      auto const sEnd = end(curpos->children);

      auto iter = curpos->children.find(elem_type(curvalue));
      if (iter != sEnd)
        curpos = iter->second;
      else
        curpos = nullptr; // not found

      if (curpos == nullptr)
        return retval;
    }

    // If we get here, then the sequence is in the trie iff
    // there is an end-of-sequence character...
    auto result = curpos->children.find(elem_type{});
    if (result != end(curpos->children) && result->second == nullptr)
      retval = true;

    return retval;
  }

  //
  // You might need to debug your code. Also you might wonder how
  // to obtain every sequence in the trie. This recursive function
  // shows how to do an inorder traversal of the trie. It will
  // output all sequences to the basic_ostream os.
  //
  template <typename Ch, typename ChTr>
  void print_inorder(
    std::basic_ostream<Ch,ChTr>& os, 
    std::vector<elem_type> prefix={}
  )
  {
    for (auto&& child : this->children)
    {
      prefix.push_back(child.first);

      if (child.second != nullptr)
        child.second->print_inorder(os, prefix);
      else
      {
        auto i = begin(prefix);
        auto iEnd = end(prefix);

        // Discard the end of string marker...
        if (iEnd != i)
          --iEnd;

        // Output sequence...
        for (; i != iEnd; ++i)
          os << *i;
        os << endl;
      }

      prefix.pop_back();
    }
  }
};

//
//  swap()
//
//  HINT: Simply invoke trie_node's swap()!
//
//  NOTE: This is needed to support calling a free swap() function.
//        One may or may not know about the member function --but one
//        shouldn't have to know about it at all if this function is
//        provided!
//
inline void swap(trie_node& a, trie_node& b)
{
  a.swap(b);
}


int main()
{
  trie_node n;

  string test = "ab";

  n.add(test);
  n.add(string("abcde"));
  n.add(string("abcdd"));
  n.add(string("airplane"));
  n.add(string("airlock"));
  n.print_inorder(cout);

  trie_node o = n;

  bool b2 = o.find(string("airplane"));
  bool b3 = o.find(string("airlock"));
  bool b4 = o.find(string("a"));
  cout << b2 << b3 << b4 << '\n'; // Outputs: 110
}

