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
class red_black_avl{
public:
    red_black_avl();
    red_black_avl(const T *sorted_list, int size = -1);
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    red_black_avl(const red_black_avl<T> &copy_me);
    red_black_avl<T> &operator=(const red_black_avl<T> &rhs);
    ~red_black_avl();
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    void insert(const T &insert_me);
    void erase(const T &target);
    void flip_color();
    int is_red();
    bool contains(const T &target)const;
    void clear_all();
    bool empty()const;
    friend ostream &operator<<(ostream &outs, const red_black_avl<T> &tree)
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
    red_black_avl<T> operator+=(const red_black_avl<T> &rhs);
    string pre_order();
    string in_order();
    string post_order();

private:
    tree_node<T>* _root;
};

//definitions here

//done
template<typename T>
red_black_avl<T>::red_black_avl() : _root(nullptr){

}

//done
template<typename T>
red_black_avl<T>::red_black_avl(const T *sorted_list, int size) {
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
red_black_avl<T>::red_black_avl(const red_black_avl<T> &copy_me) {
    _root = tree_copy(copy_me._root);
}

//done
template<typename T>
red_black_avl<T> & red_black_avl<T>::operator=(const red_black_avl<T> &rhs) {
    if (this != &rhs) {
        clear_all();
        _root = tree_copy(rhs._root);
    }
    return *this;
}

//done
template<typename T>
red_black_avl<T>::~red_black_avl() {
    clear_all();
}

//done
template<typename T>
void red_black_avl<T>::insert(const T &insert_me) {
    tree_insert(_root, insert_me);
}

//done
template<typename T>
void red_black_avl<T>::erase(const T &target) {
    tree_erase(_root, target);
}

template<typename T>
bool red_black_avl<T>::contains(const T &target) const {
    return tree_search(_root, target);
}

//done
template<typename T>
void red_black_avl<T>::clear_all() {
    tree_clear(_root);
}


//done
template<typename T>
bool red_black_avl<T>::empty() const {
    return _root == nullptr;
}

//done
template<typename T>
red_black_avl<T> red_black_avl<T>::operator+=(const red_black_avl<T> &rhs) {
    tree_add(_root, rhs._root);
    return *this;
}

//done
template<typename T>
string red_black_avl<T>::pre_order() {
    return pre_order_string(_root);
}

//done
template<typename T>
string red_black_avl<T>::in_order() {
    return in_order_string(_root);
}

//done
template<typename T>
string red_black_avl<T>::post_order() {
    return post_order_string(_root);
}

template<typename T>
void red_black_avl<T>::flip_color() {
    return flip_color(_root);
}

template<typename T>
int red_black_avl<T>::is_red() {
    return is_red(_root);
}


#endif //INC_11_AVL_CLASS_THEODOREFARRIS27_AVL_H