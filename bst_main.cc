/* BST EXAM MAIN FILE  */
#include <iostream>
#include <memory>
#include <utility>
 #include <bst.h>
// #include <bst_iterator.h>
//#include <bst_all.h>
#include <ap_error.h>


int main(){

  BST<int, int> bst {};
  bst.populate_tree();
  auto i = bst.begin();
  auto k = bst.end();
  auto j = bst.cbegin();
  auto l = bst.cend();
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

  return 0;

}
