/* HEADER FILE FOR BST EXAM */
#ifndef __BST_H__
#define __BST_H__

  #ifndef TOL
  #define TOL 0.000001
  #endif

#include <iostream> // I/O
#include <iterator>
#include <memory>  // smart pointers
#include <utility> // std::pair
//#include <bst_iterator.h>
#include <ap_error.h> // error handling
#include <cmath>
#include <sstream>
#include <string>
#include<vector>

/*
TO DO: Introduce functions last to pick up the last element.
*/

/** Class Binary Search Tree (BST). Templated on both the key and the value
 * stored in each node.
*/
template <typename K, typename V> class BST {
  /** Struct Node: the fundamental brick in a BST which registers a pair (K, V).
   */
  struct Node {
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
    /** Up link of the current node. It stores the address of the last node
     * passed form left. */
    Node *up;

    Node() {}
    /** Plain "DWIM" ctor for a new Node.
    * It stores the input key and value into the templated std::pair data  and
    * and sets both the left and the right links to nullptr.
    */
    Node(const K &k, const V &v)
        : data{k, v}, left{nullptr}, right{nullptr}, up{nullptr} {
      /*
      Iterator i {this};
      std::cout<<"Node "<< *i<<" ctor. My address: "<< this  <<"Up: " <<
      this->up << " key: "<< i.get_key()<<std::endl;
      */
    } // custom ctor
    Node(const K &k, const V &v, Node *tmp)
        : data{k, v}, left{nullptr}, right{nullptr}, up{tmp} {
      /*
      Iterator i {this};
      std::cout<<"Node "<< *i<<" ctor. My address: "<< this  <<"  Up: " <<
      this->up << " key: "<< i.get_key()<<std::endl;
      */
    }// custom ctor

    Node(const Node & old);
    //Node& operator=(const Node &);
  }; // end of struct Node

  /** Unique ptr to the root node. The gateway to the BST. */
  std::unique_ptr<Node> root;

  bool check_eq_keys(const K& a, const K& b);

public:
  /** Default ctor for a BST. It initializes a Tree with no nodes. */
  BST(): root{nullptr} {}
  BST(const BST & old) {
    Node * tmp = old.root.get();
    //root.reset(new Node()); // check if already allocated!!!
    root.reset(new Node{*tmp});
    root->up = nullptr; // without this, root->up would remain uninitialized.
    //root{tmp}; // cannot do this: root is a smart pointer
  }

  BST(BST && old): root{std::move(old.root)} {}

  BST & operator=(BST&& old) {
    root = std::move(old.root);
    return *this;
  }


  BST & operator=(const BST & old){
    // must be declared within the class
    //https://stackoverflow.com/questions/871264/what-does-operator-must-be-a-non-static-member-mean
    using Node =  BST<K,V>::Node;
    Node * tmp = old.root.get();
    root.reset(new Node{*tmp});
    root->up = nullptr; // without this, root->up would remain uninitialized.
    return *this;
  }



  void insert_node(const K& k, const V& v);
  void cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp = nullptr);
  void populate_tree();
  void populate_tree(std::istream& i_str);
  void print_tree();
  void balance();
  void erase_tree();
  int find(Node *tmp, const K &k);
  int find_key(const K &k);
  int isBalanced();
  bool is_same_height(Node *tmp);
  int max(int a, int b);
  int height(Node *tmp);
  int height_differnce(Node *tmp);
  Node *height_diff(Node * tmp);
  Node *right_rotation(Node * tmp);
  Node *left_rotation(Node * tmp);
  Node *balanced_insert(Node *tmp, const K &k, const V &v);
  int print_as_inserted(Node * tmp);


  // balaced_insert();

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
    Iterator last();

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const { return ConstIterator{nullptr}; }
    ConstIterator last() const;

    ConstIterator cbegin() const ;
    ConstIterator cend() const { return ConstIterator{nullptr}; }
    ConstIterator clast() const;


  };
  /*END OF CLASS BST*/


  template<typename K, typename V>
  bool BST<K,V>::check_eq_keys(const K& a, const K& b){
    if (a==b) return true;
    else return false;
  }

  template<>
  bool BST<double,double>::check_eq_keys(const double& a, const double& b){
    if ( fabs(a-b)< TOL ) return true;
    else return false;
  }




  template <typename K, typename V>
  BST<K,V>::Node::Node(const BST<K,V>::Node & old) : data{old.data}, left{nullptr}, right{nullptr} {
    if (old.left){
      Node * old_node_l {old.left.get()};
      left.reset(new Node{*old_node_l});  // recursively call copy constructor
      left->up = old_node_l;
    }
    if (old.right){
      Node * old_node_r {old.right.get()};
      right.reset(new Node{*old_node_r});  // recursively call copy constructor
      right->up = old_node_r->up;
    }
  }





  /* BEGIN OF CLASS BST<K,V>::ConstIterator */
  template <typename K, typename V>
  class BST<K,V>::ConstIterator : public BST<K,V>::Iterator {
    using parent = BST<K,V>::Iterator;

  ConstIterator cbegin() const;
  ConstIterator cend() const { return ConstIterator{nullptr}; }
};
/*END OF CLASS BST*/

/* BEGIN OF CLASS BST<K,V>::ConstIterator */
template <typename K, typename V>
class BST<K, V>::ConstIterator : public BST<K, V>::Iterator {
  using parent = BST<K, V>::Iterator;

public:
  using parent::Iterator; // inher ctor
  const V &operator*() const { return parent::operator*(); }
  const K &get_key() const { return parent::get_key(); }
};

template <typename K, typename V>
typename BST<K, V>::ConstIterator BST<K, V>::begin() const {
  using Node = BST<K, V>::Node;
  using ConstIterator = BST<K, V>::ConstIterator;
  Node *tmp{root.get()};
  if (tmp != nullptr) {
    while (tmp->left.get() != nullptr)
      tmp = tmp->left.get();
  }
  ConstIterator i{tmp};
  // std::cout<< "ConstIterator Begin = " << *i << std::endl;
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


template <typename K, typename V>
typename BST<K, V>::ConstIterator BST<K, V>::cbegin() const {
  using Node = BST<K, V>::Node;
  using ConstIterator = BST<K, V>::ConstIterator;
  Node *tmp{root.get()};
  if (tmp != nullptr) {
    while (tmp->left.get() != nullptr)
      tmp = tmp->left.get();
  }
  ConstIterator i{tmp};
  // std::cout<< "ConstIterator Begin = " << *i << std::endl;
  return i;
}


template <typename K, typename V>
typename BST<K,V>::ConstIterator BST<K,V>::clast() const {
using Node =  BST<K,V>::Node;
using ConstIterator =  BST<K,V>::ConstIterator;
Node * tmp {root.get()};
if(tmp!=nullptr){
while(tmp->right.get()!=nullptr)
tmp = tmp->right.get();
}
ConstIterator i {tmp};
//std::cout<< "ConstIterator End = " << *i << std::endl;
return i;
}


/* BEGIN OF CLASS BST<K,V>::Iterator */
template <typename K, typename V>
class BST<K, V>::Iterator
    : public std::iterator<std::bidirectional_iterator_tag, V> {
  using Node = BST<K, V>::Node;
  Node *current;
  Node *get_leftmost(Node *start);
  Node *get_rightmost(Node *start);

  public:
    Iterator(Node* n) : current{n} {}
    V& operator*() const { return current->data.second; }
    K& get_key() const { return current->data.first; }
    // ++it
    Iterator& operator++() {  // now take care of issues when calling operator++
      // on the node having the greatest key!
      Node * tmp = current->right.get();
      if( tmp!=nullptr ){
        current = BST<K,V>::Iterator::get_leftmost(tmp);
      }
      else{
        current = current->up;
      }
      return *this;
    }

  Iterator operator++(int) { // now take care of issues when calling operator++
    // on the node having the greatest key!
    Iterator it{current};
    ++(*this);
    return it;
  }

  bool operator==(const Iterator &other) {
    return this->current == other.current;
  }
  /* The following is wrong. You're comparing iterators, not hte data holded by
them
  These data may not exist (eg if Iterator == Iterator{nullptr})
  bool operator==(const Iterator& other) {
  return this->current->data.second == other.current->data.second;
}
*/

  bool operator!=(const Iterator &other) { return !(*this == other); }
};

template <typename K, typename V>
typename BST<K, V>::Node *
BST<K, V>::Iterator::get_leftmost(BST<K, V>::Node *start) {
  // using Node =  BST<K,V>::Node;
  // using Iterator =  BST<K,V>::Iterator;
  // Node * tmp {root.get()};
  // if(tmp!=nullptr){ // do error handling!!
  Node *tmp = start;
  while (tmp->left.get() != nullptr)
    tmp = tmp->left.get();
  //}
  // Iterator i {tmp};
  // std::cout<< "Value of the leftmost node attached to the one in input  = "
  // << *i << std::endl;
  return tmp;
}

template <typename K, typename V>
typename BST<K, V>::Node *
BST<K, V>::Iterator::get_rightmost(BST<K, V>::Node *start) {
  // using Node =  BST<K,V>::Node;
  // using Iterator =  BST<K,V>::Iterator;
  // Node * tmp {root.get()};
  // if(tmp!=nullptr){ // do error handling!!
  Node *tmp = start;
  while (tmp->right.get() != nullptr)
    tmp = tmp->right.get();
  //}
  // Iterator i {tmp};
  // std::cout<< "Value of the rightmost node attached to the one in input  = "
  // << *i << std::endl;
  return tmp;
}

template <typename K, typename V>
typename BST<K, V>::Iterator BST<K, V>::begin() {
  using Node = BST<K, V>::Node;
  using Iterator = BST<K, V>::Iterator;
  Node *tmp{root.get()};
  if (tmp != nullptr) {
    while (tmp->left.get() != nullptr)
      tmp = tmp->left.get();
  }
  Iterator i{tmp};
  // std::cout<< "Begin = " << *i << std::endl;
  return i;
}

template <typename K, typename V>
typename BST<K,V>::Iterator BST<K,V>::last(){
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


template <typename K, typename V> void BST<K, V>::erase_tree() { root.reset(); }

template <typename K, typename V>
void BST<K,V>::erase_tree(){
  root.reset();
}




template <typename K, typename V>
void BST<K,V>::insert_node( const K& k, const V& v ){
  if (root.get() == nullptr){
    root.reset(new Node{k,v});
  }
  else {
    Node* tmp{root.get()};
    BST::cmp_key(tmp, k, v);
  }
}

/* populate_tree(istream&) makes the same job
template <typename K, typename V>
int BST<K,V>::insert_nodes(std::istream& i_str ){
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
*/

template <typename K, typename V> int BST<K, V>::find_key(const K &k) {
  Node *tmp{root.get()};
  find(tmp, k);
  return 1;
}

template <typename K, typename V> int BST<K, V>::find(Node *tmp, const K &k) {
  /** One starts srearching from the root or any of the nodes possible*/

  if (check_eq_keys(k, tmp->data.first)) {
    std::cout << "The key has been found." << k << std::endl;
    return 2;
  }

  /** Entering in the left banch from the starting node if not found.*/
  else if (k < tmp->data.first) {
    if (tmp->left == nullptr)
      std::cout << "key is not present in the tree." << '\n';
    else {
      tmp = tmp->left.get();
      BST::find(tmp, k);
    }
    return 1;
  }

  /** Entering in the left banch from the starting node if not found.*/
  else {
    if (tmp->right == nullptr) {
      std::cout << "key is not present in the tree." << '\n';
    } else {
      tmp = tmp->right.get();
      BST::find(tmp, k);
    }
    return 1;
  }
}

template <typename K, typename V>
void BST<K,V>::cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp){
  if (check_eq_keys(k, tmp->data.first) ){ // to be placed first to take care of == comparison
                                           // for type double variables
    tmp->data.second = v;
    //return 2; // should throw an exception
  }
  else if(k < tmp->data.first){
    tmpUp = tmp;
    // std::cout << "tmp= " << tmp << " tmpUp= " << tmpUp <<std::endl;
    if (tmp->left == nullptr)
      tmp->left.reset(new Node{k, v, tmpUp}); // costruttore con up!
    else {
      tmp = tmp->left.get();
      BST::cmp_key(tmp, k, v, tmpUp);
    }
    //return 1;
  }
  else{
    if(tmp->right == nullptr)
    tmp->right.reset(new Node{k, v, tmpUp});
    else{
      tmp = tmp->right.get();
      BST::cmp_key(tmp, k, v, tmpUp);
    }
    //return 1;
  }
}



template <typename K, typename V>
void BST<K,V>::print_tree(){
  //using cIt = BST<K,V>::ConstIterator;
    // for (const auto& x : *this)
    //  std::cout << " : "<< x << std::endl;
    for (auto i=this->cbegin(); i!=this->cend(); ++i)
        std::cout << i.get_key() << " : " << *i << std::endl;
}


/* TO BE TESTED!!! XXXXXXXXXX
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const BST<K,V>& tree) {
  for (const auto& x : *tree)
    os << x << std::endl;
  return os;
}
*/


template <typename K, typename V>
void BST<K,V>::balance_tree(){

}



























template <typename K, typename V>
void BST<K,V>::populate_tree(){
  std::string line;
  K k;
  V v;
  while (std::getline(std::cin, line)) {
    std::stringstream ss(line);
    if (ss >> k >> v) {
      // std::cout << k << v <<'\n';
      BST::insert_node(k, v); // check error or throw exception. to be cmpleted
      // std::cout << check << '\n';
    }
  }
}

template <typename K, typename V>
void BST<K, V>::populate_tree(std::istream &i_str) {
  std::string line;
  K k;
  V v;
  while (std::getline(i_str, line)) {
    std::stringstream ss(line);
    if (ss >> k >> v) {
      // std::cout << k << v <<'\n';
      BST::insert_node(k, v); // check error or throw exception. to be cmpleted
      // std::cout << check << '\n';
    }
  }
}

/** returns maximum of two integers */
template <typename K, typename V> int BST<K, V>::max(int a, int b) {
  return (a >= b) ? a : b;
}

/** This function gives us the output for the biggest branch in the tree
if started from the root of the tree  */
template <typename K, typename V> int BST<K, V>::height(Node *tmp) {
  if (tmp == nullptr)
    return 0;

  /** If tree is not empty then height = 1 + max of leftheight and right heights
   */
  return 1 + max(height(tmp->left.get()), height(tmp->right.get()));
}
/** Returns true if binary tree with root as root is height-balanced */
template <typename K, typename V> bool BST<K, V>::is_same_height(Node *tmp) {

  int lh; /* for height of left subtree */
  int rh; /* for height of right subtree */

  /** If the tree is empty.*/
  if (tmp == nullptr) {
    std::cout << "The tree is balanced" << '\n';
    return true;
  }

  /* Get the height of left and right sub trees */
  lh = height(tmp->left.get());
  rh = height(tmp->right.get());

  if (abs(lh - rh) <= 1 && is_same_height(tmp->right.get()) &&
      is_same_height(tmp->left.get())) {
    std::cout << "The tree is balanced" << '\n';
    return true;
  }

  /** In this point the tree is not balanced with respect to the chosen root.
  Which signifies that at some level/height all the nodes don't have the same
  number of childeren nodes.*/
  // std::cout << "The tree is not balanced" << '\n';
  return false;
}

template <typename K, typename V> int BST<K, V>::isBalanced() {
  Node *tmp{root.get()};
  if (!is_same_height(tmp))
    std::cout << "tree is not balanced" << '\n';
  ;
  return 0;
}

/** Get difference of height between the right and left child of the node. */
template <typename K, typename V> int BST<K, V>::height_differnce(Node *tmp) {
  if (tmp == nullptr)
    return 0;
  return height(tmp->left.get()) - height(tmp->right.get());
}

/**This function is to just test for the template for the node type functions.*/
template <typename K, typename V>
typename BST<K, V>::Node *BST<K, V>::height_diff(Node *tmp) {
  return tmp;
}

/** */
template <typename K, typename V>
typename BST<K, V>::Node *BST<K, V>::right_rotation(Node * tmp){
  Node *l = tmp->left.get();
  Node *r = tmp->right.get();

  l->right.reset(tmp);
  tmp->left.reset(r);

  return l;
}

/** */
template <typename K, typename V>
typename BST<K, V>::Node *BST<K, V>:: left_rotation(Node * tmp){
  Node *l = tmp->left.get();
  Node *r = tmp->right.get();

  r->right.reset(tmp);
  tmp->right.reset(l);

  return r;
}

template <typename K, typename V>
typename BST<K, V>::Node *BST<K, V>:: balanced_insert(Node *tmp, const K &k, const V &v){

    if (tmp == nullptr) {
      root.reset(new Node{k, v});
      tmp = root.get();
      return tmp;
    }

    if (k < tmp->data.first)
        tmp->left.reset(balanced_insert(tmp->left.get(), k, v));
    else if (k > tmp->data.first)
        tmp->right.reset(balanced_insert(tmp->right.get(), k, v));
    else
        return tmp;
    // BST::insert_node(k,v);
    // tmp = root.get();

    int diff = height_differnce(tmp);

    if (diff > 1 && k < tmp->left->data.first)
        return right_rotation(tmp);

    if (diff < -1 && k > tmp->right->data.first)
        return left_rotation(tmp);

    if (diff > 1 && k > tmp->left->data.first){
        tmp->left.reset(left_rotation(tmp->left.get()));
        return right_rotation(tmp);
    }

    if (diff < -1 && k < tmp->right->data.first){
        tmp->right.reset(right_rotation(tmp->right.get()));
        return left_rotation(tmp);
    }
    return tmp;
}

template <typename K, typename V> void BST<K, V>::balance() {
  using ConstIterator = BST<K,V>::ConstIterator;
    std::string line;
    K k;
    V v;
    std::vector<std::pair<K,V>> vect;

}



#endif
