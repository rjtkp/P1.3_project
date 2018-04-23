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




/** Class Binary Search Tree (BST). Templated on both the key and the value stored in each node.
*/
template <typename K, typename V>
class BST{

  /** Struct Node: the fundamental brick in a BST which registers a pair (K, V).  */
  struct Node{
    /** Key-value pair in the node.
    data.first stores the key.
    data.second stores the associated value.
    */
    std::pair<K, V> data;
    /** Left child of the current node in the BST. */
    std::unique_ptr<Node> left;
    /** Right child of the current node in the BST. */
    std::unique_ptr<Node> right;
    /** Up link of the current node. It stores the address of the last node passed from the left. */
    Node * up;

    /** Default ctor for a Node. (Ctor0)
    * It leaves uninitialized all the data members of the created Node.
    */
    Node() {}

    /** Ctor for a Node (Ctor1).
    * It stores the input key and value into the templated std::pair data and
    * sets both its children  Node * left and the Node * right to nullptr.
    */
    Node(const K& k, const V& v) : data{k,v} , left{nullptr}, right{nullptr}, up{nullptr} {
      /*
      Iterator i {this};
      std::cout<<"Node "<< *i<<" ctor. My address: "<< this  <<"Up: " << this->up << " key: "<< i.get_key()<<std::endl;
      */
    }

    /** Ctor for a Node (Ctor2).
    * In addition to initializing the Node members std::pair data, Node * left and the Node * right
    * it also sets the Node member Node * up.
    */
    Node(const K& k, const V& v, Node * tmp) : data{k,v} , left{nullptr}, right{nullptr}, up{tmp} {
      /*
      Iterator i {this};
      std::cout<<"Node "<< *i<<" ctor. My address: "<< this  <<"  Up: " << this->up << " key: "<< i.get_key()<<std::endl;
      */
    }

    /** Copy ctor for a Node */
    Node(const Node & old);

    //Node& operator=(const Node &);
  }; // end of struct Node

  /** Unique ptr to the root node in the tree. */
  std::unique_ptr<Node> root;

  /** bool check_eq_keys(const K& a, const K& b) is an auxiliary function which checks whether two nodes are
  storing the same key. It outputs true if a==b and false otherwise. Please note that the comparison operator
  may need to be overloaded for some data types for some reason, either of logical or computational nature.
  In this header file we have already overloaded this function for keys of type double.
  For this case, the object-like macro TOL set at the beginning of the header file defines the tolerance for the comparison between a and b (that is, fabs(a-b)<TOL ? true : false).
  */
  bool check_eq_keys(const K& a, const K& b);

  /** void cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp = nullptr) is an auxiliary function which compares the K-type value k with the key of the Node pointed to by tmp.
  * If k < tmp->data.first and tmp->left == nullptr, the function creates the node tmp->left featuring key
  * k, value v and Node * up = tmp (case 1).
  * If k > tmp->data.first and tmp->right == nullptr, the function creates the node tmp->right featuring key
  * k, value v and Node * up = nullptr (that is the default value for tmpUp) (case 2).
  * If k == tmp->data.first (actually if check_eq_keys(k, tmp->data.first)==true), the function replaces
  * tmp->data.second with v and leaves all the other members in the node unaltered (case 3).
  * If k != tmp->data.first (actually if check_eq_keys(k, tmp->data.first)==false) and tmp->left!=nullptr
  * (tmp->right!=nullptr), the function calls itself recursively to compare k with tmp->left.data.first
  * (tmp->right.data.second) until case 1 (2) is reached.
  */
  void cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp = nullptr);
  bool is_bced(Node * loc_root);




public:

  /** Default ctor for a BST. The tree root is initialized to nullptr. */
  BST(): root{nullptr} {}

  /** Copy ctor for a BST. */
  BST(const BST & old) {
    Node * tmp = old.root.get();
    //root.reset(new Node()); // check if already allocated!!!
    root.reset(new Node{*tmp});
    root->up = nullptr; // without this, root->up would remain uninitialized.
    //root{tmp}; // cannot do this: root is a smart pointer
  }

  /** Move ctor for a BST. */
  BST(BST && old): root{std::move(old.root)} {}

  /** Move assignment for a BST. */
  BST & operator=(BST&& old) {
    root = std::move(old.root);
    return *this;
  }

  /** Copy assignment for a BST. */
  BST & operator=(const BST & old){
    // must be declared within the class
    //https://stackoverflow.com/questions/871264/what-does-operator-must-be-a-non-static-member-mean
    using Node =  BST<K,V>::Node;
    Node * tmp = old.root.get();
    root.reset(new Node{*tmp});
    root->up = nullptr; // without this, root->up would remain uninitialized. Valgrinf would raise an error.
    return *this;
  }


  /** insert_node(const K& k, const V& v) inserts a new node having key k and value v in the tree.
  * The function first checks whether root has been already allocated. If not,
  * it allocates the root and it stores k into root->data.first and v into root->data.second.
  * Otherwise, the function makes use of the recursive function cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp = nullptr) to insert the new node at the right place in the tree.
  * The tree is left unbalanced after the insertion.
  */
  void insert_node(const K& k, const V& v);

  /** populate_tree() reads a variable number N of rows of K V pairs from stdin and creates a tree from scratch
  * having as many nodes as the number of K V pairs. The key (value) in the Nth node inserted is set to the key K(value V) in the Nth line in input.
  */
  void populate_tree();

  /** populate_tree(std::istream is) reads a variable number N of K V pairs from the input std::istream and creates a tree from scratch having as many nodes as the number of K V pairs. The key (value) in the Nth node inserted is set to the key K(value V) in the Nth line in input.
  */
  void populate_tree(std::istream& i_str);

  /** print_tree() prints to stdout the content in the tree nodes in increasing order with respect to the keys.
  In particular, the output is a sequence of N rows (where N is the number of nodes in the tree), the i-th of them displaying the key-value pair in the layout K : V
  */
  void print_tree();
  void balance_tree();
  void balance_tree2();
  /** void erase_tree() destruct safely all the nodes in the tree, including root. */
  void erase_tree();
  int find(Node * tmp, const K& k);
  int find_key(const K& k);
  int isBalanced();
  bool is_same_height(Node * tmp);
  int max(int a, int b);
  int height(Node * tmp);

  /** Iterator on the nodes in the tree. It inherits publicily the data and methods of
  std::iterator<std::bidirectional_iterator_tag, V>, where V is the data type of the value.
  */
  class Iterator;

  /** Iterator begin() returns an iterator to the node storing the smallest key in the tree. */
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

    Iterator begin(Node * loc_root);

    /** Iterator end() returns an iterator to nullptr, which is the "sentinel node" for the node in the tree storing the greatest key. */
    Iterator end() { return Iterator{nullptr}; };

    /** Iterator last() returns an iterator to the node storing the greatest key in the tree. */
    Iterator last();

    /** ConstIterator on the nodes in the tree. It inherits publicily the data and methods of the Iterator class, which in turns inherits publicily from std::iterator<std::bidirectional_iterator_tag, V>, where V is the data type of the value.
    */
    class ConstIterator;

    /** ConstIterator begin() returns an Iterator to the node storing the smallest key in the tree. */
    ConstIterator begin() const;

    /** ConstIterator end() returns an Iterator to nullptr, which is the "sentinel node" for the node in the tree storing the greatest key. */
    ConstIterator end() const { return ConstIterator{nullptr}; }

    /** ConstIterator last() returns an Iterator to the node storing the greatest key in the tree. */
    ConstIterator last() const;

    /** ConstIterator cbegin() returns a ConstIterator to the node storing the smallest key in the tree. */
    ConstIterator cbegin() const ;

    /** ConstIterator cend() returns a ConstIterator to nullptr, which is the "sentinel node" for the node in the tree storing the greatest key. */
    ConstIterator cend() const { return ConstIterator{nullptr}; }

    /** ConstIterator clast() returns a ConstIterator to the node storing the greatest key in the tree. */
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



// copy ctor
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

  public:
    using parent::Iterator; // to inherit the ctor
    const V& operator*() const { return parent::operator*(); }
    const K& get_key() const {return parent::get_key();}
  };



  template <typename K, typename V>
  typename BST<K,V>::ConstIterator BST<K,V>::begin() const {
    using Node =  BST<K,V>::Node;
    using ConstIterator =  BST<K,V>::ConstIterator;

    ConstIterator i;
    i.set_current(i.get_leftmost(root.get()));

    /*****OLD
    Node * tmp {root.get()};
    if(tmp!=nullptr){
      while(tmp->left.get()!=nullptr)
      tmp = tmp->left.get();
    }
    ConstIterator i {tmp};
    ******/
    //std::cout<< "ConstIterator Begin = " << *i << std::endl;
    return i;
  }


  template <typename K, typename V>
  typename BST<K,V>::ConstIterator BST<K,V>::last() const {

    ConstIterator i;
    i.set_current(i.get_rightmost(root.get()));

  /******
  using Node =  BST<K,V>::Node;
  using Iterator =  BST<K,V>::Iterator;
  Node * tmp {root.get()};
  if(tmp!=nullptr){
  while(tmp->right.get()!=nullptr)
  tmp = tmp->right.get();
}
ConstIterator i {tmp};
*******/
return i;
}



template <typename K, typename V>
typename BST<K,V>::ConstIterator BST<K,V>::cbegin() const {
  using Node =  BST<K,V>::Node;
  using ConstIterator =  BST<K,V>::ConstIterator;


  ConstIterator i;
  i.set_current(i.get_leftmost(root.get()));
  /*********
  Node * tmp {root.get()};
  if(tmp!=nullptr){
    while(tmp->left.get()!=nullptr)
    tmp = tmp->left.get();
  }
  ConstIterator i {tmp};
  ********/

  //std::cout<< "ConstIterator Begin = " << *i << std::endl;
  return i;
}


template <typename K, typename V>
typename BST<K,V>::ConstIterator BST<K,V>::clast() const {
  ConstIterator i;
  i.set_current(i.get_rightmost(root.get()));

/*
using Node =  BST<K,V>::Node;
using ConstIterator =  BST<K,V>::ConstIterator;
Node * tmp {root.get()};
if(tmp!=nullptr){
while(tmp->right.get()!=nullptr)
tmp = tmp->right.get();
}
ConstIterator i {tmp};
*/
//std::cout<< "ConstIterator End = " << *i << std::endl;
return i;
}




/* BEGIN OF CLASS BST<K,V>::Iterator */
template <typename K, typename V>
class BST<K,V>::Iterator : public std::iterator<std::bidirectional_iterator_tag, V> {
  using Node =  BST<K,V>::Node;
  Node* current;


  public:
    Iterator() {}
    Iterator(Node* n) : current{n} {}
    V& operator*() const { return current->data.second; }
    K& get_key() const { return current->data.first; }
    void set_current(Node * curr) {current=curr;}
    Node * get_leftmost(Node * start);
    Node * get_rightmost(Node * start);

    // ++it
    Iterator& operator++() {  // now take care of issues when calling operator++
      // on the node having the greatest key!
      Node * tmp = current->right.get();
      if( tmp!=nullptr ){
        current = get_leftmost(tmp);
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
typename BST<K,V>::Node * BST<K,V>::Iterator::get_leftmost( BST<K,V>::Node * start){
  //using Node =  BST<K,V>::Node;
  //using Iterator =  BST<K,V>::Iterator;
  //Node * tmp {root.get()};
  //if(tmp!=nullptr){ // do error handling!!
  Node * tmp {start};
  if(tmp!=nullptr){  // do error handling!!
    while(tmp->left.get()!=nullptr)
    tmp = tmp->left.get();
  }
  //}
  //Iterator i {tmp};
  //std::cout<< "Value of the leftmost node attached to the one in input  = " << *i << std::endl;
  return tmp;
}





template <typename K, typename V>
typename BST<K,V>::Node * BST<K,V>::Iterator::get_rightmost( BST<K,V>::Node * start){
  //using Node =  BST<K,V>::Node;
  //using Iterator =  BST<K,V>::Iterator;
  //Node * tmp {root.get()};
  //if(tmp!=nullptr){ // do error handling!!
  Node * tmp {start};
  if(tmp!=nullptr){  // do error handling!!
    while(tmp->right.get()!=nullptr)
    tmp = tmp->right.get();
  }
  //}
  //Iterator i {tmp};
  //std::cout<< "Value of the rightmost node attached to the one in input  = " << *i << std::endl;
  return tmp;
}



template <typename K, typename V>
typename BST<K,V>::Iterator BST<K,V>::begin(){
  //using Node =  BST<K,V>::Node;
  using Iterator =  BST<K,V>::Iterator;

  /***** OLD VERSION
  Node * tmp {root.get()};
  if(tmp!=nullptr){
    while(tmp->left.get()!=nullptr)
    tmp = tmp->left.get();
  }
  Iterator i {tmp};
  ********/
  Iterator i;
  i.set_current(i.get_leftmost(root.get()));
  /** SECOND VERSION
  Node * tmp {root.get()};
  Node * tmp2;
  tmp2 = get_leftmost(tmp);
  Iterator i {tmp2};
  ***/

  // std::cout<< "Begin = " << *i << std::endl;
  return i;
}

template <typename K, typename V>
typename BST<K,V>::Iterator BST<K,V>::last(){
//using Node =  BST<K,V>::Node;
using Iterator =  BST<K,V>::Iterator;

Iterator i;
i.set_current(i.get_rightmost(root.get()));

/***********
Node * tmp {root.get()};
if(tmp!=nullptr){
while(tmp->right.get()!=nullptr)
tmp = tmp->right.get();
}
Iterator i {tmp};
***********/
return i;
}













template <typename K, typename V>
void BST<K,V>::erase_tree(){
  if(root!=nullptr){
    root.reset(); // does it leave root in an uninitialized state or does it make root =nullptr?
  }
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

template <typename K, typename V>
int BST<K,V>::find_key(const K& k){
  Node* tmp{root.get()};
  find(tmp, k);
  return 1;
}

  template <typename K, typename V>
  int BST<K,V>::find(Node * tmp, const K& k){
  /** One starts srearching from the root or any of the nodes possible*/

  if (check_eq_keys(k, tmp->data.first) ) {
    std::cout << "The key has been found."<< k << std::endl;
    return 2;
  }

  /** Entering in the left banch from the starting node if not found.*/
  else if (k < tmp->data.first) {
    if(tmp->left == nullptr)
    std::cout << "key is not present in the tree." << '\n';
    else{
      tmp = tmp->left.get();
      BST::find(tmp, k);
    }
    return 1;
  }

  /** Entering in the left banch from the starting node if not found.*/
  else {
    if(tmp->right == nullptr){
      std::cout << "key is not present in the tree." << '\n';
  }
    else{
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
    //std::cout << "tmp= " << tmp << " tmpUp= " << tmpUp <<std::endl;
    if(tmp->left == nullptr)
    tmp->left.reset(new Node{k, v, tmpUp}); // costruttore con up!
    else{
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
void BST<K,V>::balance_tree2(){
  Node * loc_root {root.get()};
  // while ....{
  //  1. vedere se "albero innestato in loc_root è bilanciato"
  bool bced = is_bced(loc_root);
  std::cout<< "Is the tree balanced?  "<< bced <<std::endl<<std::endl;

  //  2. If sbilanciato:  Bilanciarlo
  // }
}

template <typename K, typename V>
bool BST<K,V>::is_bced(BST<K,V>::Node * loc_root){
  using ConstIterator = BST<K,V>::ConstIterator;
  int sx{};
  int dx{};

  //if(this.cbegin()!=nullptr) //... do error handling!!
  ConstIterator it_root {loc_root};
  ConstIterator i=this->cbegin();
  for (; i!=it_root; ++i)
    ++sx;
  //std::cout<<*i<<std::endl;
  ++i;
  //std::cout<<*i<<std::endl;
  for (; i!=this->cend(); ++i)
    ++dx;

  if( abs(dx-sx) > 1) return false;
  else return true;
}


























template <typename K, typename V>
void BST<K,V>::populate_tree(){
  std::string line;
  K k; V v;
  while (std::getline(std::cin, line)){
    std::stringstream ss(line);
    if (ss >> k >> v){
      // std::cout << k << v <<'\n';
      BST::insert_node(k,v); // check error or throw exception. to be cmpleted
      //std::cout << check << '\n';
    }
  }
}


template <typename K, typename V>
void BST<K,V>::populate_tree(std::istream& i_str){
  std::string line;
  K k; V v;
  while (std::getline(i_str, line)){
    std::stringstream ss(line);
    if (ss >> k >> v){
      // std::cout << k << v <<'\n';
      BST::insert_node(k,v); // check error or throw exception. to be cmpleted
      //std::cout << check << '\n';
    }
  }
}

/** returns maximum of two integers */
template <typename K, typename V>
int BST<K,V>::max(int a, int b){
  return (a >= b)? a: b;

}

/** This function gives us the output for the biggest branch in the tree
if started from the root of the tree  */
template <typename K, typename V>
int BST<K,V>::height(Node * tmp){
   if(tmp == nullptr)
       return 0;

   /** If tree is not empty then height = 1 + max of leftheight and right heights */
   return 1 + max(height(tmp->left.get()), height(tmp->right.get()));
}
/** Returns true if binary tree with root as root is height-balanced */
template <typename K, typename V>
bool BST<K,V>::is_same_height(Node * tmp){

  int lh; /* for height of left subtree */
  int rh; /* for height of right subtree */

   /** If the tree is empty.*/
   if(tmp == nullptr){
     std::cout << "The tree is balanced" << '\n';
     return true;
   }

   /* Get the height of left and right sub trees */
   lh = height(tmp->left.get());
   rh = height(tmp->right.get());

   if( abs(lh-rh) <= 1 && is_same_height(tmp->right.get()) && is_same_height(tmp->left.get())){
     std::cout << "The tree is balanced" << '\n';
     return true;
   }

   /** In this point the tree is not balanced with respect to the chosen root.
   Which signifies that at some level/height all the nodes don't have the same
   number of childeren nodes.*/
   // std::cout << "The tree is not balanced" << '\n';
   return false;
}

template <typename K, typename V>
int BST<K,V>::isBalanced(){
  Node* tmp{root.get()};
  if(!is_same_height(tmp)) std::cout << "tree is not balanced" << '\n';;
  return 0;
}




















#endif
