/* BST EXAM MAIN FILE  */
#include <iostream>
#include <memory>
#include <utility>
 #include <bst.h>
// #include <bst_iterator.h>
//#include <bst_all.h>
#include <ap_error.h>


int main(){

  std::istringstream iss("34 34");
  std::istringstream iss1("344 344");


  BST<int, int> bst {};
  bst.populate_tree(); // read automatically from std::cin
  //bst.populate_tree(std::cin); // read from a specified istream
  bst.populate_tree(iss);
  bst.populate_tree(iss1);
  /*
  auto i = bst.begin();
  auto k = bst.end();
  auto j = bst.cbegin();
  auto l = bst.cend();
  */

auto it = bst.cbegin();
auto it_end = bst.cend();
for (; it != it_end; ++it){
  std::cout << *it << std::endl;
}

  bst.insert_node(0,0);
  bst.insert_node(100,100);

  for (const auto& x : bst)
    std::cout << x << std::endl;

  std::cout << "/* message */" << std::endl;
  bst.print_tree();
  bst.erase_tree();
  std::cout << "/* TREE ERASED */" << std::endl;
  //bst.print_tree(); --> if called here it causes SIGSEGV
  /*
  std::cout<< " ConstIterator cbegin j="<<*j<<std::endl;
  std::cout<< "ConstIterator cend l="<<*l<<std::endl;

  j++;
  *i=20;
  // *j=90; error: assignment of read-only location ‘j.BST<K, V>::ConstIterator::operator*<int, int>()’ *j=90;


  std::cout<< "i="<<*i<<"\nTry ++ operator: "<< std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  ++i;

  bool eq = i==k;
  bool neq = i!=k;
  std::cout << "i==k is " << eq << std::endl;
  std::cout << "i!=k is " << neq << std::endl;

  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  i++;
  std::cout<< "i="<<*i<<std::endl;
  i++;
  std::cout<< "i="<<*i<<std::endl;

  eq = i==k;
  neq = i!=k;
  std::cout << "i==k is " << eq << std::endl;
  std::cout << "i!=k is " << neq << std::endl;
*/
  return 0;

}
