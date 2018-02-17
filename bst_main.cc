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
  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;
  ++i;
  std::cout<< "i="<<*i<<std::endl;


  return 0;

}
