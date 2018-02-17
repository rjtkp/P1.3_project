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
