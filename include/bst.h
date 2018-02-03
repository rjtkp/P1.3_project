/* HEADER FILE FOR BST EXAM */
#ifndef __BST_H__
#define __BST_H__

#include <iostream> // I/O
#include <memory> // smart pointers
#include <utility> // std::pair
#include <iterator>
//#include <bst_iterator.h>
#include <ap_error.h> // error handling
#include <string>
#include <sstream>


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
    typedef std::unique_ptr<std::pair<K, V>> pair;
    pair data;
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
    Node(const K& k, const V& v) : data{k,v} , left{nullptr}, right{nullptr}, up{nullptr} {}// custom ctor
  }; // end of struct Node

  /** Unique ptr to the root node. The gateway to the BST. */
  std::unique_ptr<Node> root;

  public:
    /** Default ctor for a BST. It initializes a Tree with no nodes. */
    BST(): root{nullptr} {}
    int insert_node(const K& k, const V& v);
    int cmp_key(Node * tmp, const K& k, const V& v);
    void populate_tree();


    class Iterator;
    //Iterator begin();

};
/*END OF CLASS BST*/






template <typename K, typename V>
int BST<K,V>::insert_node( const K& k, const V& v ){
  if (this->root.get() == nullptr){
    this->root.reset(new Node{k,v});
    return 1;
  }
  else {
    Node* tmp{this->root.get()};
    int check = BST::cmp_key(tmp, k, v);
    return check;
  }
}

template <typename K, typename V>
int BST<K,V>::cmp_key(Node * tmp, const K& k, const V& v){
  if(k < tmp->data->first){
    if(tmp->data->first == nullptr)
      tmp->left.reset(new Node{k, v});
    else{
      tmp = tmp->left;
      BST::cmp_key(tmp, k, v);
    }
    return 1;
  }
  else if (k == tmp->data->first){
    tmp->data->second = v;
    return 2; // should throw an exception
  }
  else{
    if(tmp->data->first == nullptr)
      tmp->right.reset(new Node{k, v});
    else{
      tmp = tmp->right;
      BST::cmp_key(tmp, k, v);
    }
    return 1;
  }
}


template <typename K, typename V>
void BST<K,V>::populate_tree(){
  std::string line;
  while (std::getline(std::cin, line)){
    std::stringstream ss(line);
    K k; V v;
    if (ss >> k >> v){
        int check = BST::insert_node(k,v); // check error or throw exception. to be cmpleted
        std::cout << check << '\n';
    }
  }
}



















#endif
