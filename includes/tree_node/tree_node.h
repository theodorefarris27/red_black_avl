//
// Created by Theo Farris on 4/2/26.
//

#ifndef INC_11_AVL_CLASS_THEODOREFARRIS27_TREE_NODE_H
#define INC_11_AVL_CLASS_THEODOREFARRIS27_TREE_NODE_H

using namespace std;

template <typename T>
struct tree_node{
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;
    int _color;
    int balance_factor(){
        //balance factor = height of the left subtree
        //                        - the height of the right subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0
        //wamt tp use ternary operator more
        int left = (_left == nullptr) ? -1 : _left->_height;
        int right = (_right == nullptr) ? -1 : _right->_height;
        return left - right;
    }

    int height(){
        // Height of a node is 1 + height of the "taller" child
        //A leaf node has a height of zero: 1 + max(-1,-1)
        int left_height = (_left == nullptr) ? -1 : _left->_height;
        int right_height = (_right == nullptr) ? -1 : _right->_height;
        return 1 + (left_height > right_height ? left_height : right_height);
    }
    int update_height(){
        //set the _height member variable (call height();)
        _height = height();
        return _height;
    }

    tree_node(T item=T(), tree_node* left=nullptr,
                          tree_node* right=nullptr):
                    _item(item), _left(left), _right(right)
    {
        _height = height();
        //don't forget to set the _height.
    }
    friend ostream& operator <<(ostream& outs,
                                const tree_node<T>& t_node){
        outs<<"|"<<t_node._item<<"|";
        return outs;
    }
};


#endif //INC_11_AVL_CLASS_THEODOREFARRIS27_TREE_NODE_H