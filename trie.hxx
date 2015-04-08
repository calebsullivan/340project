#ifndef _MAP
#define _MAP
  #include <map>
#endif
#ifndef _QUEUE
#define _QUEUE
  #include <queue>
#endif
#ifndef _IOSTREAM
#define _IOSTREAM
  #include <iostream>
#endif
#ifndef _STRING
#define _STRING
  #include <string>
#endif

#ifndef _TRIE
#define _TRIE

namespace cxx_project {


using namespace std;

//
// trie
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
class trie
{
public:
  using value_type = char;

private:
  using elem_type = char;
  using child_node_type = trie*;

  map< elem_type, child_node_type > children;

public:
  //
  // Default construction is simple: since the children map has a default
  // constructor, no data is needed in it, and that is the only data
  // member, let the compiler generate the code...
  //
  trie() = default;

  template <typename OutIter>
  std::size_t output_matches(std::string const& pattern, OutIter&& out) const;
  //
  // Copy construction performs a breadth-first search (BFS) of the trie
  // being copied from. The BFS is tracked using a std::vector as a queue
  // where the vector is a pair of trie*. The pair of trie*
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
  trie(trie const& n)
  {
    // stack: breadth first search, std::pair< newtrie, oldtrie >
    std::vector< std::pair<trie*, trie const*> > stack;

    // Start stack with (this, &n)...
    stack.emplace_back(this, &n);

    do
    {
      auto curpos = stack.back(); stack.pop_back();

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
        // Create the child trie iff i->second != nullptr.
        // If i->second == nullptr then it is an end-of-sequence character.
        trie* tmp_node{
          (i->second != nullptr)
          ? new trie
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
  // TODO: Write copy assignment operator.
  //
  // HINT: 1) Create a local trie variable as n is const.
  //       2) Use swap.
  //
  trie& operator =(trie const& n){
    auto temp = n;
    swap(temp);
    return *this;
  }

  //
  // TODO: Move constructor.
  //
  // HINT: There is only one data member. Try moving it! :-)
  //
  // RESTRICTION: No code must appear inside the { } braces.
  //
  trie(trie&& n):
    children(move(n.children)) 
  {}

  //
  // TODO: Move assignment operator.
  //
  // HINT: The trie class has a swap() member function. Use it!
  //
  trie& operator =(trie&& n){
    swap(n);
    return n;
  }

  //
  // TODO: Destructor.
  //
  // HINT: The trie class has a clear() member function. Use it!
  //
  ~trie(){
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
  void swap(trie& n){
    auto temp = std::move(n.children); // map<char const, trie*>
    n.children = std::move(children);
    children = std::move(temp);
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
  // RESTRICTION: You must use std::queue<trie*> to do this 
  //              solution.
  //
  void clear(){
    std::queue<trie*> bfs;
    bfs.push(this); 
    
    do{
      auto node_ptr = bfs.front(); // trie*
      for(auto i : node_ptr->children) // pair<char const, trie*>
        if(i.second != nullptr) 
          bfs.push(i.second);
      node_ptr->children.clear();
      if(this != node_ptr)
        delete node_ptr;
      bfs.pop();
    }while(!bfs.empty());
  }


  // void clear(){
  //   std::queue<trie*> bfs;
  //   bfs.push(this); 

  //   do{
  //     auto node_ptr = bfs.front();
  //     if ( !node_ptr->children.empty()){ 
  //       for (auto&& i : node_ptr->children){
  //         if (i.second != nullptr)
  //           bfs.push(i.second);
  //       node_ptr->children.clear();
  //     }
  //     if (node_ptr != this)
  //       delete node_ptr;
  //     bfs.pop();
  //   }while((!bfs.empty()))
  // }

  
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
    trie* curpos = this;

    // Build trie for s...
    for (auto i=begin(s), iEnd=end(s); i != iEnd; ++i)
    {
      // Add the next sequence value...
      //  result's type: pair<iterator, bool>
      auto result = curpos->children.emplace(elem_type(*i), nullptr);

      // If the next sequence value was inserted, then ensure
      // a default trie is allocated with new...
      if (result.second)
      {
        // *i is not already stored and next entry must at least 
        // be end-of-string...
        result.first->second = new trie;
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
    trie const * curpos = this;

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
//  TODO: swap()
//
//  HINT: Simply invoke trie's swap()!
//
//  NOTE: This is needed to support calling a free swap() function.
//        One may or may not know about the member function --but one
//        shouldn't have to know about it at all if this function is
//        provided!
//
inline void swap(trie& a, trie& b){
  a.swap(b);
}

} //future

#endif
