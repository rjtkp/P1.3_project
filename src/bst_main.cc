/* BST EXAM MAIN FILE  */
#include <iostream>
#include <memory>
#include <utility>
#include <bst.h>
// #include <bst_iterator.h>
//#include <bst_all.h>
#include <ap_error.h>


int main(){
  /******** CHECKING BST<int, int>, printing, node insertion, balance status ********/

  BST<int, int> bst {};
  bst.populate_tree(); // read automatically from std::cin

  //bst.populate_tree(std::cin) // also works
  //bst.print_tree();
  std::cout << "\n\nbst addresses original\n"<< std::endl;
  bst.print_addresses();

  BST<int, int> bst2 {bst};

  std::istringstream iss("7 7");
  bst.populate_tree(iss);
  std::istringstream iss2("73 73");
 iss2>>bst;

 BST<int, int> bst4;
 BST<int, int> bst5 {bst4};
 bst4.print_addresses();
 bst5.print_addresses();
 bst4.erase_tree();

 std::cout << "\n\nbst4\n"<< bst4<< std::endl;
 std::cout << "\n\nbst5\n"<< bst5<<std::endl;


  //std::cout << "\n\ncout bst\n"<< bst<< std::endl;

  BST<int, int> bst3 {bst};
  //std::cout << "\n\ncout bst2\n"<< bst2<< std::endl;

  std::cout << "\n\nbst addresses\n"<< std::endl;
  bst.print_addresses();
  std::cout << "\n\nbst2 addresses\n"<< std::endl;
  bst2.print_addresses();
  std::cout << "\n\nbst3 addresses dopo aggiunta\n"<< bst3 << std::endl;
  bst3.print_addresses();




//
//
//   bst.balance_tree2();
//
//
//   std::istringstream iss("34 34");
//   std::istringstream iss1("344 344");
//
//   // Raj's tests on balancing the tree
//   bst.populate_tree(iss); // read from specified istream
//   bst.print_tree();
//   if (bst.isBalanced( )) std::cout << "balanced" << '\n';
//
//   bst.populate_tree(iss1);
//   bst.print_tree();
//   if (bst.isBalanced( )) std::cout << "balanced" << '\n';
//
//   bst.insert_node(0,0); // insert single node from main
//   bst.print_tree();
//   if (bst.isBalanced( )) std::cout << "balanced" << '\n';
//
//   bst.insert_node(100,100);
//   bst.print_tree();
//   if (bst.isBalanced( )) std::cout << "balanced" << '\n';
//
//   //****** END of checking BST<int, int> ************/
//
//
//
//   /******* CHECKING BST<double, double> *******/
//   //Check BST<double, double>
//   BST<double, double> bstd {};
//   bstd.populate_tree();
//   bstd.print_tree();
//   bstd.erase_tree();
//   //******* END OF CHECKING BST<double, double> ********/
//
//
//
//   /******* CHECKING CTORS *******/
//     // Check copy ctor
//     BST<int, int> bst2{bst};
//     std::cout << "bst2{bst} "<<std::endl;
//     bst2.print_tree();
//
//     // Check copy assignment
//     BST<int, int> bst3;
//     bst3 = bst2;
//     std::cout << "bst3 = bst2 "<<std::endl;
//     // bst2.print_tree(); // uncomment after adding error handling
//     bst3.print_tree();
//
//     // Check move ctor
//     BST<int, int> bst4{std::move(bst)};
//     std::cout << "bst4{std::move(bst)} "<<std::endl;
//     bst4.print_tree();
//     // bst.print_tree(); // uncomment after adding error handling
//
//     // Check move assignment
//     BST<int, int> bst5;
//     bst5 = std::move(bst2);
//     std::cout << "bst5 = std::move(bst2) "<<std::endl;
//     bst5.print_tree();
//     // bst2.print_tree();  // uncomment after adding error handling
//   //******* END CHECKING CTORS ********/
//
//
//   /******* CHECKING TREE ERASURE ********/
//   // bst.erase_tree();  // uncomment after adding error handling
//   // bst2.erase_tree();
//   bst3.erase_tree();
//   // bst4.erase_tree();
//   // bst5.erase_tree();
//   //******* END CHECKING TREE ERASURE ********/
//
//
// /******* CHECKING FIND & MAX ********/
//   bst = bst4;
//   bst.find_key(1);
//   bst.find_key(2);
//   bst.find_key(3);
//   bst.find_key(4);
//   bst.find_key(5);
//   bst.max(11,12);
//   std::cout <<"the bigger one is:" << bst.max(11,12) << '\n';
//   bst.isBalanced( );
//   // bst.erase_tree();
// //******* END CHECKING TREE ERASURE ********/
//
//
// /******* CHECKING ITERATORS: still to be fixed ********/
//   auto b = bst.begin();
//   auto e = bst.end();
//   auto l = bst.last();
//   auto cb = bst.cbegin(); // pay attention cause cbegin and cend are overloaded
//   auto ce = bst.cend();
//   auto cl = bst.clast();
//
//   // check == and != operators
//   bool eq = b==l;
//   bool neq = b!=l;
//   std::cout << "begin==last is " << eq << std::endl;
//   std::cout << "begin!=last is " << neq << std::endl;
//
//   // check ++ and ++(int) operators
//   std::cout<< "b="<<*b<<std::endl;
//   ++b;
//   std::cout<< "b+1="<<*b<<std::endl;
//   b++;
//   std::cout<< "b+2="<<*b<<std::endl;
//   ++b;
//   std::cout<< "b+3="<<*b<<std::endl;
//   b++;
//   std::cout<< "b+4="<<*b<<std::endl;
// //******* END CHECKING ITERATORS ********/





  return 0;

}
