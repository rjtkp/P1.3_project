/* BST FUNCTION IMPLEMENTATIONS */
#include <iostream>
#include <memory>
#include <utility>
#include <iterator>
#include <bst.h>
#include <ap_error.h>
#include <string>
#include <sstream>



template <typename K, typename V>
int BST<K,V>::insert( const K& k, const V& v ){
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
        int check = BST::insert(k,v); // check error or throw exception. to be cmpleted
        std::cout << check << '\n';
    }
  }
}




/**/
