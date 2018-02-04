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
std::cout<< "\nTry ++ operator: "<< std::endl;
  ++i;
  ++i;
  ++i;
  ++i;
  ++i;
  ++i;
  ++i;
  ++i;
  ++i;


  return 0;

}
