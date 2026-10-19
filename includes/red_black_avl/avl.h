//
// Created by Theo Farris on 4/2/26.
//

#ifndef INC_11_AVL_CLASS_THEODOREFARRIS27_AVL_H
#define INC_11_AVL_CLASS_THEODOREFARRIS27_AVL_H

#include <iostream>
#include "../tree_node.h"
#include "../avl/avl_functions.h"

using namespace std;


template <typename T>
class AVL{
public:
    AVL();
    AVL(const T *sorted_list, int size = -1);
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    AVL(const AVL<T> &copy_me);
    AVL<T> &operator=(const AVL<T> &rhs);
    ~AVL();
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    void insert(const T &insert_me);

    void erase(const T &target);


    bool contains(const T &target)const;
    void clear_all();
    bool empty()const;
    friend ostream &operator<<(ostream &outs, const AVL<T> &tree)
    {
        const bool debug = false;
        if (debug){
            cout<<"-------------------------------"<<endl;
            tree_print_debug(tree._root, 0, outs);
            cout<<". . . . . . . . . . . . . . . ."<<endl;
        }
        tree_print(tree._root, 0, outs);
        return outs;
    }
    AVL<T> operator+=(const AVL<T> &rhs);
    string pre_order();
    string in_order();
    string post_order();

private:
    tree_node<T>* _root;
};

//definitions here

//done
template<typename T>
AVL<T>::AVL() : _root(nullptr){

}

//done
template<typename T>
AVL<T>::AVL(const T *sorted_list, int size) {
    if (sorted_list == nullptr) {
        return;
    }
    if (size == -1) {
        _root = tree_from_sorted_list(sorted_list);
    }
    else {
        _root = tree_from_sorted_list(sorted_list, size);
    }
}

//done
template<typename T>
AVL<T>::AVL(const AVL<T> &copy_me) {
    _root = tree_copy(copy_me._root);
}

//done
template<typename T>
AVL<T> & AVL<T>::operator=(const AVL<T> &rhs) {
    if (this != &rhs) {
        clear_all();
        _root = tree_copy(rhs._root);
    }
    return *this;
}

//done
template<typename T>
AVL<T>::~AVL() {
    clear_all();
}

//done
template<typename T>
void AVL<T>::insert(const T &insert_me) {
    tree_insert(_root, insert_me);
}

//done
template<typename T>
void AVL<T>::erase(const T &target) {
    tree_erase(_root, target);
}

template<typename T>
bool AVL<T>::contains(const T &target) const {
    return tree_search(_root, target);
}

//done
template<typename T>
void AVL<T>::clear_all() {
    tree_clear(_root);
}


//done
template<typename T>
bool AVL<T>::empty() const {
    return _root == nullptr;
}

//done
template<typename T>
AVL<T> AVL<T>::operator+=(const AVL<T> &rhs) {
    tree_add(_root, rhs._root);
    return *this;
}

//done
template<typename T>
string AVL<T>::pre_order() {
    return pre_order_string(_root);
}

//done
template<typename T>
string AVL<T>::in_order() {
    return in_order_string(_root);
}

//done
template<typename T>
string AVL<T>::post_order() {
    return post_order_string(_root);
}


#endif //INC_11_AVL_CLASS_THEODOREFARRIS27_AVL_H