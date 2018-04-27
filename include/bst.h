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


/* TO BE TESTED!!! XXXXXXXXXX */
//https://stackoverflow.com/questions/15734020/error-declaration-of-operator-as-non-function
// NB: if placed after def of BST, compiler throws error for fw declaration!
template <typename K, typename V>

// need to declare here BST due to use in the overloading of std::operator<<
class BST;

/** Overload of std::operator<<, to print the all the pairs key-value in the tree.
*/
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const BST<K,V>& tree) {
 auto i=tree.cbegin();
 if(i==nullptr){
   os << "Empty tree"<< std::endl;
  }
  for ( ; i!=tree.cend(); ++i)
    os << i.get_key() << " : " << *i << std::endl;

  return os;
}

/** Overload of std::operator<< to easily populate the tree.
Usage example:
BST<K,V> bst;
std::istringstream is("k v");
is>>bst;
will add to the tree the Node storing the pair (k, v).
*/
template <typename K, typename V>
std::istream& operator>>(std::istream& is, BST<K,V>& tree) {

  tree.populate_tree(is);

  return is;
}



/** Class Binary Search Tree (BST). Templated on the key-value pairs K,V stored for each node in an std::pair.
*Limitations:* Operators ==, > and < must have been already defined for data of type K. To overcome the issues of round-off errors,
two doubles are considered to be equal if they differ at most TOL one from the other.
The default value for TOL is 1e6. This value can be set in $(SRCDIR)/Makefile before compiling.
*/
template <typename K, typename V>
class BST{

  /** Struct Node: the fundamental brick in the BST which stores a std::pair (K, V).
  */
  struct Node{
    /** Key-value pair in the node.
    data.first stores the key (type K).
    data.second stores the associated value (type V).
    */
    std::pair<K, V> data;
    /** Left child of the current node in the BST. */
    std::unique_ptr<Node> left;
    /** Right child of the current node in the BST. */
    std::unique_ptr<Node> right;
    /** Up link of the current node. It stores the address of the last node passed from the left by the current node.*/
    Node * up;


    /** Default Node ctor (Ctor0).
    * It leaves uninitialized all the data members of the Node.
    */
    Node() {}

    /** Node Ctor for a Node (Ctor1).
    * It stores the input key and value into the templated std::pair data and
    * sets both its children  Node * left and the Node * right to nullptr.
    */
    Node(const K& k, const V& v) : data{k,v} , left{nullptr}, right{nullptr}, up{nullptr} { // case of int and chars better
      /*
      Iterator i {this};
      std::cout<<"Node "<< *i<<" ctor. My address: "<< this  <<"Up: " << this->up << " key: "<< i.get_key()<<std::endl;
      */
    }

    /** Ctor for a Node (Ctor2).
    * In addition to initializing the Node members std::pair data, Node * left and the Node * right
    * it also initializes the Node member Node * up.
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
  storing the same key. It outputs true if a==b and false otherwise. Please read the note to class BST
  regarding comparison operations.
  */
  bool check_eq_keys(const K& a, const K& b) const noexcept;

  /** void cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp = nullptr) is an auxiliary function
  exploited when populating the tree. It compares the K-type value k with the key of the Node pointed to by tmp.
   If k < tmp->data.first and tmp->left == nullptr, the function creates the node tmp->left featuring key
   k, value v and Node * up = tmp (case 1).
   If k > tmp->data.first and tmp->right == nullptr, the function creates the node tmp->right featuring key
   k, value v and Node * up = nullptr (that is the default value for tmpUp) (case 2).
   If k == tmp->data.first (actually if check_eq_keys(k, tmp->data.first)==true), the function replaces
   tmp->data.second with v and leaves all the other members in the node unaltered (case 3).
   If k != tmp->data.first (actually if check_eq_keys(k, tmp->data.first)==false) and tmp->left!=nullptr
   (tmp->right!=nullptr), the function calls itself recursively to compare k with tmp->left.data.first
   (tmp->right.data.second) until case 1 (2) is reached.
  */
  void cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp = nullptr) const noexcept;

  /** T's balance function
  */
  bool is_bced(Node * loc_root);

  /** Ancillary static variable exploited when calling the copying ctor of BST. */
  static Node * last_up;



public:

  /** Default ctor for a BST. The tree root is initialized to nullptr. */
  BST(): root{nullptr} {}

  /** Copy ctor for a BST. */
  BST(const BST & old) {
    if (old.root.get()==nullptr)
      this->root=nullptr; //the new BST is set to nullptr. Done
    else
      root.reset(new Node{*old.root.get()});
    //root->up = nullptr; // without this, root->up would remain uninitialized.
    //root{tmp}; // cannot do this: root is a smart pointer
  }
  //last_up=nullptr;

  /** Move ctor for a BST. Noexcept guaranteed. */
  BST(BST && old) noexcept: root{std::move(old.root)} {}

  /** Move assignment for a BST. */
  BST & operator=(BST&& old) noexcept {
    root = std::move(old.root);
    return *this;
  }

  /** Copy assignment for a BST. */
  BST & operator=(const BST & old){
    // must be declared within the class
    //https://stackoverflow.com/questions/871264/what-does-operator-must-be-a-non-static-member-mean
    using Node =  BST<K,V>::Node;
    // Node * tmp = old.root.get();
    // root.reset(new Node{*tmp});
    root.reset(new Node{*old.root.get()});
    //root->up = nullptr; // without this, root->up would remain uninitialized. Valgrind would raise an error.
    return *this;
  }


  /** insert_node(const K& k, const V& v) inserts a new node having key k and value v in the tree.
  * The function first checks whether root has been already allocated. If not,
  * it allocates the root and it stores k into root->data.first and v into root->data.second.
  * Otherwise, the function makes use of the recursive function cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp = nullptr) to insert the new node at the right place in the tree.
  * The tree is left unbalanced after the insertion.
  */
  void insert_node(const K& k, const V& v) noexcept;

  /** populate_tree() reads a variable number N of rows of K V pairs from stdin and creates a tree from scratch
  * having as many nodes as the number of K V pairs. The key (value) in the Nth node inserted is set to the key K(value V) in the Nth line in input.
  */
  void populate_tree() ;

  /** populate_tree(std::istream is) reads a variable number N of K V pairs from the input std::istream and creates a tree from scratch having as many nodes as the number of K V pairs. The key (value) in the Nth node inserted is set to the key K(value V) in the Nth line in input.
  */
  void populate_tree( std::istream& i_str);

  /** print_tree() prints to std::cout the content in the tree nodes in increasing order with respect to the key values.
  In particular, the output is a sequence of N rows (where N is the number of nodes in the tree), the i-th of them displaying the key-value pair in the layout k : v
  If the tree is empty, the function prints the string "The tree is empty".
  */
  void print_tree() const noexcept;
  /**
  In addition to printing the couples k : v, print_addresses() prints the address of the current node.
  */
  void print_addresses() const noexcept;
  void balance_tree();
  /*
  void balance_tree2();
  */
  /** void erase_tree() prunes safely all the nodes in the tree. Root is pointing to nullptr after erase_tree() has returned.
  */
  void erase_tree() noexcept;
  int find(Node * tmp, const K& k);
  int find_key(const K& k);
  int isBalanced();
  bool is_same_height(Node * tmp);
  int max(int a, int b);
  int height(Node * tmp);

  /** Iterator on the nodes in the tree. It inherits publicily the data and methods of
  std::iterator<std::forward_iterator_tag, V>, where V is the data type of the value.
  */
  class Iterator;

  /** Iterator begin() returns an iterator to the node storing the smallest key in the tree. */
  Iterator begin()  noexcept; //{
    // Node * tmp {root.get()};
    // if(tmp!=nullptr){
    //   while(tmp->left.get()!=nullptr)
    //     tmp = tmp->left.get();
    // }
    // Iterator i {tmp};
    // std::cout<< "Begin = " << *i << std::endl;
    // return tmp;
    //} // to be modified

    /*
    Iterator begin(Node * loc_root);
    */

    /** Iterator end() returns an iterator to nullptr, which is the "sentinel node" for the node in the tree storing the greatest key. */
    Iterator end()  noexcept{ return Iterator{nullptr}; };

    /** Iterator last() returns an iterator to the node storing the greatest key in the tree. */
    Iterator last()  noexcept;

    /** ConstIterator on the nodes in the tree. It inherits publicily the data and methods of the Iterator class, which in turns inherits publicily from std::iterator<std::forward_iterator_tag, V>, where V is the data type of the value.
    */
    class ConstIterator;

    /** ConstIterator begin() returns an Iterator to the node storing the smallest key in the tree. */
    ConstIterator begin() const noexcept;

    /** ConstIterator end() returns an Iterator to nullptr, which is the "sentinel node" for the node in the tree storing the greatest key. */
    ConstIterator end() const noexcept{ return ConstIterator{nullptr}; }

    /** ConstIterator last() returns an Iterator to the node storing the greatest key in the tree. */
    ConstIterator last() const noexcept;

    /** ConstIterator cbegin() returns a ConstIterator to the node storing the smallest key in the tree. */
    ConstIterator cbegin() const noexcept;

    /** ConstIterator cend() returns a ConstIterator to nullptr, which is the "sentinel node" for the node in the tree storing the greatest key. */
    ConstIterator cend() const noexcept { return ConstIterator{nullptr}; }

    /** ConstIterator clast() returns a ConstIterator to the node storing the greatest key in the tree. */
    ConstIterator clast() const noexcept;


    friend std::ostream& operator << <>(std::ostream& os, const BST<K,V> & tree);
    friend std::istream& operator >> <>(std::istream& is, BST<K,V> & tree);


  };
  /*END OF CLASS BST*/


  template<typename K, typename V>
  bool BST<K,V>::check_eq_keys(const K& a, const K& b) const noexcept{
    if (a==b) return true;
    else return false;
  }

  template<>
  bool BST<double,double>::check_eq_keys(const double& a, const double& b) const noexcept{
    if ( fabs(a-b)< TOL ) return true;
    else return false;
  }

template <typename K, typename V>
typename BST<K,V>::Node * BST<K,V>::last_up = nullptr;
// copy ctor
  template <typename K, typename V>
  BST<K,V>::Node::Node(const BST<K,V>::Node & old) : data{old.data}, left{nullptr}, right{nullptr}, up{last_up} {

    // if(old.right) last_up = this->up;
    // if(old.left)  last_up = this;

    if (old.left){
      last_up = this;
      // Node * old_node_l {old.left.get()};
      // left.reset(new Node{*old_node_l});  // recursively call copy constructor
      left.reset(new Node{*old.left.get()});  // recursively call copy constructor
      //left->up = old_node_l;
      //left->up = this;

    }
    //else left.reset(nullptr);

    if (old.right){
      last_up = this->up;
      // Node * old_node_r {old.right.get()};
      // right.reset(new Node{*old_node_r});  // recursively call copy constructor
      right.reset(new Node{*old.right.get()});  // recursively call copy constructor
      //right->up = this->up;
      //right->up = last_up;
    }
    //else right.reset(nullptr);
    last_up = nullptr;
  }





  /* BEGIN OF CLASS BST<K,V>::ConstIterator */
  template <typename K, typename V>
  class BST<K,V>::ConstIterator : public BST<K,V>::Iterator {
    using parent = BST<K,V>::Iterator;

  public:
    using parent::Iterator; // to inherit the ctor
    const V& operator*() const { return parent::operator*();}
    const K& get_key() const {return parent::get_key();}
    const Node *  get_address() const noexcept{ return parent::get_address(); }
    const Node *  get_up() const noexcept {return parent::get_up();}
    //void set_current(const Node * curr) {this->current=curr;}
    //const Node * get_leftmost(Node * start) const {return parent::get_leftmost(start);}
    //const Node * get_rightmost(Node * start) const {return parent::get_rightmost(start);}
  };



  template <typename K, typename V>
  typename BST<K,V>::ConstIterator BST<K,V>::begin() const noexcept{
//    using Node =  BST<K,V>::Node;
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
  typename BST<K,V>::ConstIterator BST<K,V>::last() const noexcept{

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
typename BST<K,V>::ConstIterator BST<K,V>::cbegin() const noexcept{
  //using Node =  BST<K,V>::Node;
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
typename BST<K,V>::ConstIterator BST<K,V>::clast() const noexcept{
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
class BST<K,V>::Iterator : public std::iterator<std::forward_iterator_tag, V> {
  using Node =  BST<K,V>::Node;
  Node* current;


  public:
    Iterator() {}
    Iterator(Node* n) : current{n} {}
    V& operator*() const {
      if(current == nullptr) {
        AP_error("Trying to dereference nullptr!");
      }
      return current->data.second;
    }
    K& get_key() const {
      if(!current) {
        AP_error("Trying to read data from nullptr!");
      }
      return current->data.first;
    }
    Node *  get_address() const noexcept{ return current; }
    Node *  get_up() const noexcept{ return current->up; }
    void set_current( Node * curr) noexcept {current=curr;}
    Node * get_leftmost (Node * start) const noexcept;
    Node * get_rightmost (Node * start) const noexcept;

    // ++it
    Iterator& operator++() {  // now take care of issues when calling operator++
      // on the node having the greatest key!
      if(!current){
        AP_error("Current is set to the sentinel node of the tree. ++ not permitted.");
      }

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

    bool operator==(const Iterator& other) const noexcept {
      return this->current == other.current;
    }
    /* The following is wrong. You're comparing iterators, not hte data holded by them
    These data may not exist (eg if Iterator == Iterator{nullptr})
    bool operator==(const Iterator& other) {
    return this->current->data.second == other.current->data.second;
  }
  */

    bool operator!=(const Iterator& other) const noexcept { return !(*this == other); }


};


template <typename K, typename V>
typename BST<K,V>::Node * BST<K,V>::Iterator::get_leftmost( BST<K,V>::Node * start) const noexcept{
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
typename BST<K,V>::Node * BST<K,V>::Iterator::get_rightmost( BST<K,V>::Node * start) const noexcept{
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
typename BST<K,V>::Iterator BST<K,V>::begin() noexcept{
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
typename BST<K,V>::Iterator BST<K,V>::last() noexcept{
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
void BST<K,V>::erase_tree() noexcept{
  if(root!=nullptr){
    root.reset(); // does it leave root in an uninitialized state or does it make root =nullptr?
                  // 2nd answer
  }
}




template <typename K, typename V>
void BST<K,V>::insert_node( const K& k, const V& v ) noexcept{
  if (root.get() == nullptr){
    root.reset(new Node{k,v});
  }
  else {
    // Node* tmp{root.get()};
    // BST::cmp_key(tmp, k, v);
    BST::cmp_key(root.get(), k, v);
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
void BST<K,V>::cmp_key(Node * tmp, const K& k, const V& v, Node * tmpUp) const noexcept{
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
void BST<K,V>::print_tree() const noexcept{
  //using cIt = BST<K,V>::ConstIterator;
    // for (const auto& x : *this)
    //  std::cout << " : "<< x << std::endl;
    auto i = this->cbegin();
    if(i==nullptr)
      std::cout << "Empty tree"<< std::endl;

    for (; i!=this->cend(); ++i)
        std::cout << i.get_key() << " : " << *i << std::endl;
}

template <typename K, typename V>
void BST<K,V>::print_addresses() const noexcept{
  //using cIt = BST<K,V>::ConstIterator;
    // for (const auto& x : *this)
    //  std::cout << " : "<< x << std::endl;
    auto i=this->cbegin();
    if(i==nullptr){
     std::cout << "Empty tree"<< std::endl;
    }

    for (; i!=this->cend(); ++i)
        std::cout << i.get_key() << " : " << *i << "  this: " << i.get_address()<<"  this->up: " << i.get_up() << std::endl;
}



template <typename K, typename V>
  void BST<K,V>::balance_tree(){

}

/*
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
*/

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
void BST<K,V>::populate_tree() {
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
void BST<K,V>::populate_tree( std::istream& i_str){
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
