//
// Created by Theo Farris on 4/2/26.
//

#ifndef INC_11_AVL_CLASS_THEODOREFARRIS27_AVL_FUNCTIONS_H
#define INC_11_AVL_CLASS_THEODOREFARRIS27_AVL_FUNCTIONS_H


#include <iomanip>
#include <iostream>
#include "../tree_node.h"
using namespace std;

//declarations
template <typename T>
bool tree_insert(tree_node<T>* &root, const T& insert_me);

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target);
template <typename T>
bool tree_search(tree_node<T>* root, const T& target,
                 tree_node<T>* &found_ptr);

template<typename T>
void tree_print(tree_node<T>* root, int depth=0,
                                    ostream& outs=cout);

template<typename T> //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int depth=0,
                                          ostream& outs=cout);

template <typename T> //clear the tree
void tree_clear(tree_node<T>* &root);

template <typename T> //erase target from the tree
bool tree_erase(tree_node<T>*& root, const T& target);
template <typename T> //erase rightmost node from the tree -> max_value
void tree_remove_max(tree_node<T>* &root, T& max_value);


template <typename T> //print in_order
void in_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //print pre_order
void  pre_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //print post_order
void  post_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //string in_order
string in_order_string(tree_node<T>* root);

template <typename T> //string pre_order
string pre_order_string(tree_node<T>* root);

template <typename T> //string post_order
string post_order_string(tree_node<T>* root);


template <typename T> //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root);

template <typename T> //Add tree src to dest
void tree_add(tree_node<T>* & dest, const tree_node<T>* src);

template <typename T> //sorted array of ints -> tree
tree_node<T>* tree_from_sorted_list(const T* a);

template <typename T> // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size);

// ---------------- ROTATIONS --------------------------
template <typename T>
tree_node<T>* rotate_right(tree_node<T>* &root);
template <typename T>
tree_node<T>* rotate_left(tree_node<T>* &root);
template <typename T>
tree_node<T>* rotate(tree_node<T>* & root); //decide which rotate is needed based on balance factor



//implementations

//done
template <typename T>
bool tree_insert(tree_node<T>* &root, const T& insert_me) {
    //sanity checks
    bool success = false;
    if (root == nullptr) {
        //if nothing here then just put it at the start
        root = new tree_node<T>(insert_me);
        success = true;
    }
    //if its less than it goes down left side
    else if (insert_me < root->_item) {
        //call it again to make sure we can get all the way to the bottom
        success = tree_insert(root->_left, insert_me);
    }
    else if (insert_me > root->_item) {
        //if its bigger than do the same thing
        success = tree_insert(root->_right, insert_me);
    }
    else if (insert_me == root->_item) {
        root->_item = insert_me;
        success = false;
    }
    //once we get to bottom, one of the calls will get a nullptr passed in and fail the first check
    //once its inserted now we update the height
    root->update_height();
    if(abs(root->balance_factor()) == 2){
        rotate(root);
    }
    return success;
}

//done
template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target) {
    //need something to return
    const bool debug = false;
    //sanity check
    if (!root) {
        if (debug) cout << "tree_search: element not found" << endl;
        return root;
    }
    //is it the item we need?
    if (root->_item == target) {
        if (debug) cout << "tree_search: element found" << endl;
        return root;
    }
    //is it less that what we need?
    if (target < root->_item) {
        if (debug) cout << "tree_search: going left" << endl;
        return tree_search(root->_left, target);
    }
    //is it more than what we need
    if (target > root->_item) {
        if (debug) cout << "tree_search: going right" << endl;
        return tree_search(root->_right, target);
    }
    //shoudlnt get here
    cout << "WHAT??" << endl;
}

template <typename T>
bool tree_search(tree_node<T>* root, const T& target,
                 tree_node<T>* &found_ptr) {
    //just use the one we alreaedy made
    found_ptr = tree_search(root, target);
    return found_ptr != nullptr;
}

//done
template<typename T>
void tree_print(tree_node<T>* root, int depth, ostream& outs) {
    //sanity check also lets us print until the end
    if (root) {
        tree_print(root->_right, depth+1);
        outs << setw(4*depth) << "" << "[" << root->_item << "]" << endl;
        tree_print(root->_left, depth+1);
    }

}

template<typename T> //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int depth,
                                          ostream& outs) {
    //same thing but more information
    if (root) {
        tree_print_debug(root->_right, depth+1, outs);
        outs << setw(4*depth) << ""
             << "[" << root->_item << "]"
             << " h:" << root->_height
             << endl;
        tree_print_debug(root->_left, depth+1, outs);
    }
}

//done
template <typename T> //clear the tree
void tree_clear(tree_node<T>* &root) {
    //make sure we have something to delete
    if (root) {
        tree_clear(root->_left);
        tree_clear(root->_right);
        delete root;
        root = nullptr;
    }

}

//done
template <typename T> //erase target from the tree
bool tree_erase(tree_node<T>*& root, const T& target) {
    const bool debug = false;
    bool erased = false;
    //case 1
    if (!root) {
        if (debug) cout << "tree_erase: element not found" << endl;
        return false;
    }
    //case 2
    if (target < root->_item) {
        if (debug) cout << "tree_erase: going left" << endl;
        erased = tree_erase(root->_left, target);
    }
    //case 3
    if (target > root->_item) {
        if (debug) cout << "tree_erase: going right" << endl;
        erased = tree_erase(root->_right, target);
    }
    //case 4
    if (root->_item == target) {
        if (debug) cout << "tree_erase: element found" << endl;
        if (root->_left == nullptr && root->_right == nullptr) {
            delete root;
            root = nullptr;
            erased = true;
        }
        //case 4.a only right tree
        else if (root->_left == nullptr) {
            tree_node<T>* temp = root;
            root = root->_right;
            delete temp;
            erased = true;
        }
        //case 4.b only left tree
        else if (root->_right == nullptr) {
            tree_node<T>* temp = root;
            root = root->_left;
            delete temp;
            erased = true;
        }
        //case 4.c two trees
        else {
            T max_value;
            tree_remove_max(root->_left, max_value);
            root->_item = max_value;
            erased = true;
        }
    }
    if (root) {
        root->update_height();
        if(abs(root->balance_factor()) >= 2){
            rotate(root);
        }
    }
    return erased;
}

template <typename T> //erase rightmost node from the tree -> max_value
void tree_remove_max(tree_node<T>* &root, T& max_value) {
    const bool debug = false;
    if (!root->_right) {
        if(debug) cout << "tree_remove_max: farthest right element" << endl;
        max_value = root->_item;
        tree_node<T>* temp = root;
        root = root->_left;
        delete temp;
    }
    else {
        if (debug) cout << "tree_remove_max: going right" << endl;
        tree_remove_max(root->_right, max_value);
        if (root) {
            root->update_height();
            if(abs(root->balance_factor()) >= 2){
                rotate(root);
            }
        }
    }
}

//left -> root -> right
template <typename T> //print in_order
void in_order(tree_node<T>* root,ostream& outs) {
    if (root == nullptr) return;

    in_order(root->_left, outs);
    outs << "[" << root->_item << "]";
    in_order(root->_right, outs);
}

//root -> left -> right
template <typename T> //print pre_order
void  pre_order(tree_node<T>* root,ostream& outs) {
    if (root == nullptr) return;

    outs << "[" << root->_item << "]";
    pre_order(root->_left, outs);
    pre_order(root->_right, outs);
}

//left -> right -> root
template <typename T> //print post_order
void  post_order(tree_node<T>* root,ostream& outs) {
    if (root == nullptr) return;

    post_order(root->_left, outs);
    post_order(root->_right, outs);
    outs << "[" << root->_item << "]";
}

//in order to check for the correct tree the grader needs it a string
template <typename T> //string in_order
string in_order_string(tree_node<T>* root) {
    if (root == nullptr) return "";

    return in_order_string(root->_left)
         + "[" + to_string(root->_item) + "]"
         + in_order_string(root->_right);
}

template <typename T> //string pre_order
string pre_order_string(tree_node<T>* root) {
    if (root == nullptr) return "";

    return "[" + to_string(root->_item) + "]"
         + pre_order_string(root->_left)
         + pre_order_string(root->_right);
}

template <typename T> //string post_order
string post_order_string(tree_node<T>* root) {
    if (root == nullptr) return "";
    return post_order_string(root->_left)
         + post_order_string(root->_right)
         + "[" + to_string(root->_item) + "]";
}

//done
template <typename T> //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root) {
    //make sure its not null
    if (root) {
        //make a new node that is the root of a new tree
        //put in the root item and then make a copy of the left and right subtrees
        return new tree_node<T>(root->_item,
            tree_copy(root->_left),
            tree_copy(root->_right));
    }
    else {
        return NULL;
    }
}

template <typename T> //Add tree src to dest
void tree_add(tree_node<T>* & dest, const tree_node<T>* src) {
    //sanity check
    if (src == nullptr) return;
    //put it in
    tree_insert(dest, src->_item);
    //give it a left and a right
    tree_add(dest, src->_left);
    tree_add(dest, src->_right);
}

template <typename T> // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int  size) {
    //sanity check
    if (size <= 0) {
        return nullptr;
    }
    //middle to make it balanced
    int mid = size / 2;
    //make a new root at the middle
    tree_node<T>* root = new tree_node<T>(a[mid]);
    //make the left now be a tree from start to mid
    root->_left = tree_from_sorted_list(a, mid);
    //make the right now be a tree from mid to end
    root->_right = tree_from_sorted_list(a + mid + 1, size - mid - 1);
    //update the height and return root for access
    root->update_height();
    return root;
}

template <typename T> //sorted array of ints -> tree
tree_node<T>* tree_from_sorted_list(const T* a) {
    int size = 0;
    while (a[size] != -1) {
        size++;
    }
    return tree_from_sorted_list(a, size);
}

template <typename T>
tree_node<T>* rotate_right(tree_node<T>* &root){
	//sanity check, the root must have a left child to pull up to top
	if(root == nullptr || root->_left == nullptr){
 	   return root;
	}
	//make a copy of it so i can keep the data
	//temp will replace root
	//new root goes to left child
	tree_node<T>* temp = root->_left;
	//move the thing hanging off of left child up
	root->_left = temp->_right;
	//move the old root to the right child
	temp->_right = root;

	//make sure the heights are good
	root->update_height();
	temp->update_height();

	//finally reassign root to our new one
	//passed by reference so return original
	root = temp;
	return root;
}

//same thing but opposite
template <typename T>
tree_node<T>* rotate_left(tree_node<T>* &root){
    //sanity check, the root must have a right child to pull up to top
    if(root == nullptr || root->_right == nullptr){
        return root;
    }
    //make a copy of it so i can keep the data
    //temp will replace root
    //new root goes to left child
    tree_node<T>* temp = root->_right;
    //move the thing hanging off of left child up
    root->_right = temp->_left;
    //move the old root to the right child
    temp->_left = root;

    //make sure the heights are good
    root->update_height();
    temp->update_height();

    //finally reassign root to our new one
    //passed by reference so return original
    root = temp;
    return root;
}

template <typename T>
tree_node<T>* rotate(tree_node<T>* & root){
	//sanity check
	if(root == nullptr) return root;
	root->update_height();
	//going to use the balance factor from node to do this
	int bf = root->balance_factor();
	//is it already balanced?
	if(bf == 0) {
	return root;
	}
	//is it left leaning?
	if(bf > 1){
		//left and then right
		if(root->_left && root->_left->balance_factor() < 0){
			rotate_left(root->_left);
		}
		rotate_right(root);
	}
	if(bf < -1){
		//right and then left
	if(root->_right && root->_right->balance_factor() > 0){
		rotate_right(root->_right);
	}
		rotate_left(root);
	}
	if(root){
		root->update_height();
	}
	return root;
}
 //decide which rotate is needed based on balance factor

#endif //INC_11_AVL_CLASS_THEODOREFARRIS27_AVL_FUNCTIONS_H