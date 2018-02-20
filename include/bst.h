/* HEADER FILE FOR BST EXAM */
#ifndef __BST_H__
#define __BST_H__

#ifndef TOL
#define TOL 0.000001
#endif

#include <iostream> // I/O
#include <memory> // smart pointers
#include <utility> // std::pair
#include <iterator>
//#include <bst_iterator.h>
#include <ap_error.h> // error handling
#include <string>
#include <sstream>
#include <cmath>


/*
TO DO: Introduce functions last to pick up the last element.
*/

template <typename K>
bool check_eq_keys(const K& a, const K& b){
  if (a==b) return true;
  else return false;
}

bool check_eq_keys(const double& a, const double& b){
  if ( fabs(a-b)< TOL ) return true;
  else return false;
}


/** Class Binary Search Tree (BST). Templated on both the key and the value stored in each node.
*/
template <typename K, typename V>
class BST{
  /** Struct Node: the fundamental brick in a BST which registers a pair (K, V).  */
  struct Node{
    /** Key-value pair in the node.
    std::pair defined in header <utility>.
    data.first stores the key.
    data.second stores the associated value.
    */
    /*typedef std::unique_ptr<std::pair<K, V>> pair; pair data;*/
    std::pair<K, V> data;
    /** Left link of the current node in the BST. */
    std::unique_ptr<Node> left;
    /** Right link of the current node in the BST. */
    std::unique_ptr<Node> right;
    /** Up link of the current node. It stores the address of the last node passed form left. */
    Node * up;


    /** Plain "DWIM" ctor for a new Node.
    * It stores the input key and value into the templated std::pair data  and
    * and sets both the left and the right links to nullptr.
    */
    Node(const K& k, const V& v) : data{k,v} , left{nullptr}, right{nullptr}, up{nullptr} {
      /*
      Iterator i {this};
      std::cout<<"Node "<< *i<<" ctor. My address: "<< this  <<"Up: " << this->up << " key: "<< i.get_key()<<std::endl;
      */
    }// custom ctor
    Node(const K& k, const V& v, Node * tmp) : data{k,v} , left{nullptr}, right{nullptr}, up{tmp} {
      /*
      Iterator i {this};
      std::cout<<"Node "<< *i<<" ctor. My address: "<< this  <<"  Up: " << this->up << " key: "<< i.get_key()<<std::endl;
      */
    }// custom ctor
  }; // end of struct Node

  /** Unique ptr to the root node. The gateway to the BST. */
  std::unique_ptr<Node> root;


  bool check_eq_keys(const K& a, const K& b){
    if (a==b) return true;
    else return false;
  }

  bool check_eq_keys(const double& a, const double& b){
    if ( fabs(a-b)< TOL ) return true;
    else return false;
  }


public:
  /** Default ctor for a BST. It initializes a Tree with no nodes. */
  BST(): root{nullptr} {}
  int insert_node(const K& k, const V& v);
  int cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp = nullptr);
  void populate_tree();
  void print_tree();
  void balance_tree();

  class Iterator;
  Iterator begin(); //{
    // Node * tmp {root.get()};
    // if(tmp!=nullptr){
    //   while(tmp->left.get()!=nullptr)
    //     tmp = tmp->left.get();
    // }
    // Iterator i {tmp};
    // std::cout<< "Begin = " << *i << std::endl;
    // return tmp;
    //} // to be modified
    Iterator end() { return Iterator{nullptr}; };

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const { return ConstIterator{nullptr}; }

    ConstIterator cbegin() const ;
    ConstIterator cend() const { return ConstIterator{nullptr}; }


  };
  /*END OF CLASS BST*/


  /* BEGIN OF CLASS BST<K,V>::ConstIterator */
  template <typename K, typename V>
  class BST<K,V>::ConstIterator : public BST<K,V>::Iterator {
    using parent = BST<K,V>::Iterator;

  public:
    using parent::Iterator; // inher ctor
    const V& operator*() const { return parent::operator*(); }
    const K& get_key() const {return parent::get_key();}
  };



  template <typename K, typename V>
  typename BST<K,V>::ConstIterator BST<K,V>::begin() const {
    using Node =  BST<K,V>::Node;
    using ConstIterator =  BST<K,V>::ConstIterator;
    Node * tmp {root.get()};
    if(tmp!=nullptr){
      while(tmp->left.get()!=nullptr)
      tmp = tmp->left.get();
    }
    ConstIterator i {tmp};
    std::cout<< "ConstIterator Begin = " << *i << std::endl;
    return i;
  }

  /*
  template <typename K, typename V>
  typename BST<K,V>::ConstIterator BST<K,V>::end() const {
  using Node =  BST<K,V>::Node;
  using Iterator =  BST<K,V>::Iterator;
  Node * tmp {root.get()};
  if(tmp!=nullptr){
  while(tmp->right.get()!=nullptr)
  tmp = tmp->right.get();
}
Iterator i {tmp};
std::cout<< "End = " << *i << std::endl;
return i;
}
*/


template <typename K, typename V>
typename BST<K,V>::ConstIterator BST<K,V>::cbegin() const {
  using Node =  BST<K,V>::Node;
  using ConstIterator =  BST<K,V>::ConstIterator;
  Node * tmp {root.get()};
  if(tmp!=nullptr){
    while(tmp->left.get()!=nullptr)
    tmp = tmp->left.get();
  }
  ConstIterator i {tmp};
  std::cout<< "ConstIterator Begin = " << *i << std::endl;
  return i;
}

/*
template <typename K, typename V>
typename BST<K,V>::ConstIterator BST<K,V>::cend() const {
using Node =  BST<K,V>::Node;
using ConstIterator =  BST<K,V>::ConstIterator;
Node * tmp {root.get()};
if(tmp!=nullptr){
while(tmp->right.get()!=nullptr)
tmp = tmp->right.get();
}
ConstIterator i {tmp};
std::cout<< "ConstIterator End = " << *i << std::endl;
return i;
}
*/



/* BEGIN OF CLASS BST<K,V>::Iterator */
template <typename K, typename V>
class BST<K,V>::Iterator : public std::iterator<std::bidirectional_iterator_tag, V> {
  using Node =  BST<K,V>::Node;
  Node* current;
  Node * begin(Node * start);

public:
  Iterator(Node* n) : current{n} {}
  V& operator*() const { return current->data.second; }
  K& get_key() const { return current->data.first; }
  // ++it
  Iterator& operator++() {  // now take care of issues when calling operator++
    // on the node having the greatest key!
    Node * tmp = current->right.get();
    if( tmp!=nullptr ){
      current = BST<K,V>::Iterator::begin(tmp);
    }
    else{
      current = current->up;
    }
    return *this;
  }

  Iterator operator++(int) {  // now take care of issues when calling operator++
    // on the node having the greatest key!
    Iterator it{current};
    ++(*this);
    return it;
  }

  bool operator==(const Iterator& other) {
    return this->current == other.current;
  }
  /* The following is wrong. You're comparing iterators, not hte data holded by them
  These data may not exist (eg if Iterator == Iterator{nullptr})
  bool operator==(const Iterator& other) {
  return this->current->data.second == other.current->data.second;
}
*/

bool operator!=(const Iterator& other) { return !(*this == other); }


};


template <typename K, typename V>
typename BST<K,V>::Node * BST<K,V>::Iterator::begin( BST<K,V>::Node * start){
  //using Node =  BST<K,V>::Node;
  //using Iterator =  BST<K,V>::Iterator;
  //Node * tmp {root.get()};
  //if(tmp!=nullptr){ // do error handling!!
  Node * tmp = start;
  while(tmp->left.get()!=nullptr)
  tmp = tmp->left.get();
  //}
  //Iterator i {tmp};
  //std::cout<< "Value of the leftmost node attached to the one in input  = " << *i << std::endl;
  return tmp;
}






template <typename K, typename V>
typename BST<K,V>::Iterator BST<K,V>::begin(){
  using Node =  BST<K,V>::Node;
  using Iterator =  BST<K,V>::Iterator;
  Node * tmp {root.get()};
  if(tmp!=nullptr){
    while(tmp->left.get()!=nullptr)
    tmp = tmp->left.get();
  }
  Iterator i {tmp};
  std::cout<< "Begin = " << *i << std::endl;
  return i;
}
/*
template <typename K, typename V>
typename BST<K,V>::Iterator BST<K,V>::end(){
using Node =  BST<K,V>::Node;
using Iterator =  BST<K,V>::Iterator;
Node * tmp {root.get()};
if(tmp!=nullptr){
while(tmp->right.get()!=nullptr)
tmp = tmp->right.get();
}
Iterator i {tmp};
std::cout<< "End = " << *i << std::endl;
return i;
}
*/

















template <typename K, typename V>
int BST<K,V>::insert_node( const K& k, const V& v ){
  if (root.get() == nullptr){
    root.reset(new Node{k,v});
    return 1;
  }
  else {
    Node* tmp{root.get()};
    int check = BST::cmp_key(tmp, k, v);
    return check;
  }
}

template <typename K, typename V>
int BST<K,V>::cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp){
  if (check_eq_keys(k, tmp->data.first) ){ // to be placed first to take care of == comparison
                                           // for type double variables
    tmp->data.second = v;
    return 2; // should throw an exception
  }
  else if(k < tmp->data.first){
    tmpUp = tmp;
    //std::cout << "tmp= " << tmp << " tmpUp= " << tmpUp <<std::endl;
    if(tmp->left == nullptr)
    tmp->left.reset(new Node{k, v, tmpUp}); // costruttore con up!
    else{
      tmp = tmp->left.get();
      BST::cmp_key(tmp, k, v, tmpUp);
    }
    return 1;
  }
  else{
    if(tmp->right == nullptr)
    tmp->right.reset(new Node{k, v, tmpUp});
    else{
      tmp = tmp->right.get();
      BST::cmp_key(tmp, k, v, tmpUp);
    }
    return 1;
  }
}



template <typename K, typename V>
void BST<K,V>::print_tree(){
  for (const auto& x : *this)
  std::cout << x << std::endl;
}



template <typename K, typename V>
void BST<K,V>::balance_tree(){

}



























template <typename K, typename V>
void BST<K,V>::populate_tree(){
  std::string line;
  while (std::getline(std::cin, line)){
    std::stringstream ss(line);
    K k; V v;
    if (ss >> k >> v){
      int check = BST::insert_node(k,v); // check error or throw exception. to be cmpleted
      //std::cout << check << '\n';
    }
  }
}


















#endif
