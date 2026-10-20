#include "RedBlackTree.h"
#include <iostream>

using namespace std;


// Constructor
RedBlackTree::RedBlackTree() {
    root = nullptr;
}

RedBlackTree::~RedBlackTree() {
    destroy(root);
}

void RedBlackTree::destroy(Node* node) {
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

// --------------------------------------------------
// CHECK COLOR
// --------------------------------------------------

bool RedBlackTree::isRed(Node* node) {
    if (node == nullptr)
        return false;
    return node->color == RED;
}

// --------------------------------------------------
// ROTATE LEFT
// --------------------------------------------------

RedBlackTree::Node* RedBlackTree::rotateLeft(Node* node) {
    Node* x = node->right;
    node->right = x->left;
    x->left = node;
    x->color = node->color;
    node->color = RED;
    return x;
}

// --------------------------------------------------
// ROTATE RIGHT
// --------------------------------------------------

RedBlackTree::Node* RedBlackTree::rotateRight(Node* node) {
    Node* x = node->left;
    node->left = x->right;
    x->right = node;
    x->color = node->color;
    node->color = RED;
    return x;
}

// --------------------------------------------------
// FLIP COLORS
// --------------------------------------------------

void RedBlackTree::flipColors(Node* node) {
    node->color = !node->color;
    node->left->color = !node->left->color;
    node->right->color = !node->right->color;
}

// --------------------------------------------------
// INSERT
// --------------------------------------------------

RedBlackTree::Node*
RedBlackTree::insert(Node* node, const Villager& villager) {

    // Normal BST insertion
    if (node == nullptr)
        return new Node(villager, RED);

    if (villager.name < node->data.name)
        node->left = insert(node->left, villager);

    else if (villager.name > node->data.name)
        node->right = insert(node->right, villager);

    else
        node->data = villager;

    //red link on the right
    if (isRed(node->right) && !isRed(node->left))
        node = rotateLeft(node);

    //two red links in a row
    if (isRed(node->left) &&
        isRed(node->left->left))
        node = rotateRight(node);

    //both children are red
    if (isRed(node->left) &&
        isRed(node->right))
        flipColors(node);

    return node;
}

//public insert
void RedBlackTree::insert(const Villager& villager) {
    root = insert(root, villager);
    root->color = BLACK;
}

// --------------------------------------------------
// SEARCH
// --------------------------------------------------

RedBlackTree::Node*
RedBlackTree::search(Node* node, const string& name) {
    if (node == nullptr)
        return nullptr;
    if (name == node->data.name)
        return node;
    if (name < node->data.name)
        return search(node->left, name);
    return search(node->right, name);
}


const Villager* RedBlackTree::search(const string& name) {
    Node* found = search(root, name);
    return found == nullptr ? nullptr : &found->data;
}


// --------------------------------------------------
// IN-ORDER TRAVERSAL
// --------------------------------------------------

void RedBlackTree::inorder(Node* node) {
    if (node == nullptr)
        return;
    inorder(node->left);
    cout << node->data.name;
    if (node->color == RED)
        cout << "(R)";
    else
        cout << "(B)";
    cout << endl;
    inorder(node->right);
}

void RedBlackTree::inorder() {
    inorder(root);
}

// --------------------------------------------------
// MINIMUM AND MAXIMUM
// --------------------------------------------------

const Villager* RedBlackTree::minimum() const {
    Node* node = root;
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) node = node->left;
    return &node->data;
}

const Villager* RedBlackTree::maximum() const {
    Node* node = root;
    if (node == nullptr) return nullptr;
    while (node->right != nullptr) node = node->right;
    return &node->data;
}

void printVillager(const Villager& v) {
    cout << "Name: " << v.name << '\n'
         << "Species: " << v.species << '\n'
         << "Gender: " << v.gender << '\n'
         << "Personality: " << v.personality << '\n'
         << "Hobby: " << v.hobby << '\n'
         << "Birthday: " << v.birthday << '\n'
         << "Catchphrase: " << v.catchphrase << '\n'
         << "Favorite Song: " << v.favoriteSong << '\n'
         << "Style 1: " << v.style1 << '\n'
         << "Style 2: " << v.style2 << '\n'
         << "Color 1: " << v.color1 << '\n'
         << "Color 2: " << v.color2 << '\n'
         << "Wallpaper: " << v.wallpaper << '\n'
         << "Flooring: " << v.flooring << '\n'
         << "Furniture List: " << v.furnitureList << '\n'
         << "Filename: " << v.filename << '\n'
         << "Unique Entry ID: " << v.uniqueEntryID << '\n';
}
