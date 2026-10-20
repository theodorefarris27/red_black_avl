#ifndef REDBLACK_H
#define REDBLACK_H

#include <string>
#include <vector>

struct Villager {
    std::string name;
    std::string species;
    std::string gender;
    std::string personality;
    std::string hobby;
    std::string birthday;
    std::string catchphrase;
    std::string favoriteSong;
    std::string style1;
    std::string style2;
    std::string color1;
    std::string color2;
    std::string wallpaper;
    std::string flooring;
    std::string furnitureList;
    std::string filename;
    std::string uniqueEntryID;
};

void printVillager(const Villager& villager);

class RedBlackTree {
private:

    static const bool RED = true;
    static const bool BLACK = false;

    struct Node {
        Villager data;
        Node* left;
        Node* right;
        bool color;

        Node(const Villager& v, bool c) {
            data = v;
            left = nullptr;
            right = nullptr;
            color = c;
        }
    };

    Node* root;

    bool isRed(Node* node);

    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    void flipColors(Node* node);

    Node* insert(Node* node, const Villager& villager);
    Node* search(Node* node, const std::string& name);

    void inorder(Node* node);
    void destroy(Node* node);

public:

    RedBlackTree();
    ~RedBlackTree();
    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;

    void insert(const Villager& villager);
    const Villager* search(const std::string& name);
    void inorder();
    const Villager* minimum() const;
    const Villager* maximum() const;
};

#endif
