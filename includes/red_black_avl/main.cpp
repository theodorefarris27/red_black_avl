#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "RedBlackTree.h"

using namespace std;

bool readCSVRow(istream& file, vector<string>& columns) {
    columns.clear();
    string field;
    bool inQuotes = false;
    bool started = false;
    char ch;

    while (file.get(ch)) {
        started = true;
        if (ch == '"') {
            if (inQuotes && file.peek() == '"') {
                file.get(ch);
                field += '"';
            } else {
                inQuotes = !inQuotes;
            }
        } else if (ch == ',' && !inQuotes) {
            columns.push_back(field);
            field.clear();
        } else if (ch == '\n' && !inQuotes) {
            columns.push_back(field);
            return true;
        } else if (ch == '\r' && !inQuotes && file.peek() == '\n') {
            file.get(ch);
            columns.push_back(field);
            return true;
        } else {
            field += ch;
        }
    }
    if (started) {
        columns.push_back(field);
        return true;
    }
    return false;
}

bool loadVillagers(const string& filename, RedBlackTree& tree,
                   vector<string>& names) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    vector<string> columns;
    if (!readCSVRow(file, columns)) return false; // header
    if (!columns.empty() && columns[0].compare(0, 3, "\xEF\xBB\xBF") == 0)
        columns[0].erase(0, 3);
    if (columns.size() != 17 || columns[0] != "Name") {
        cerr << "Unexpected CSV header: expected 17 columns starting with Name.\n";
        return false;
    }

    while (readCSVRow(file, columns)) {
        if (columns.size() == 1 && columns[0].empty()) continue;
        if (columns.size() != 17) {
            cerr << "Skipping invalid CSV row with " << columns.size() << " columns.\n";
            continue;
        }
        if (columns[0].empty()) continue;

        Villager v;
        v.name = columns[0];
        v.species = columns[1];
        v.gender = columns[2];
        v.personality = columns[3];
        v.hobby = columns[4];
        v.birthday = columns[5];
        v.catchphrase = columns[6];
        v.favoriteSong = columns[7];
        v.style1 = columns[8];
        v.style2 = columns[9];
        v.color1 = columns[10];
        v.color2 = columns[11];
        v.wallpaper = columns[12];
        v.flooring = columns[13];
        v.furnitureList = columns[14];
        v.filename = columns[15];
        v.uniqueEntryID = columns[16];

        tree.insert(v);
        names.push_back(v.name);
    }
    return true;
}

void showSearch(RedBlackTree& tree, const string& name) {
    cout << "\nSearch for " << name << ":\n";
    const Villager* found = tree.search(name);
    if (found != nullptr) printVillager(*found);
    else cout << "Not found\n";
}

int main(int argc, char* argv[]) {
    RedBlackTree tree;
    vector<string> names;
    string filename = argc > 1 ? argv[1] : "villagers.csv";

    if (!loadVillagers(filename, tree, names)) {
        cerr << "Could not load " << filename << endl;
        return 1;
    }

    cout << "Loaded " << names.size() << " villager records.\n";
    if (names.empty()) return 0;

    cout << "\n--- TEST SEARCHES ---\n";
    for (size_t i = 0; i < names.size() && i < 3; ++i)
        showSearch(tree, names[i]);
    showSearch(tree, "__MissingVillagerOne__");
    showSearch(tree, "__MissingVillagerTwo__");

    cout << "\n--- MINIMUM ---\n";
    if (tree.minimum()) printVillager(*tree.minimum());
    cout << "\n--- MAXIMUM ---\n";
    if (tree.maximum()) printVillager(*tree.maximum());

    string choice;
    while (true) {
        cout << "\n1. Display all villagers alphabetically\n"
             << "2. Search by name\n"
             << "3. Show minimum villager\n"
             << "4. Show maximum villager\n"
             << "0. Exit\nChoice: ";
        if (!getline(cin, choice) || choice == "0") break;
        if (choice == "1") tree.inorder();
        else if (choice == "2") {
            string name;
            cout << "Villager name: ";
            if (!getline(cin, name)) break;
            showSearch(tree, name);
        } else if (choice == "3") {
            if (tree.minimum()) printVillager(*tree.minimum());
        } else if (choice == "4") {
            if (tree.maximum()) printVillager(*tree.maximum());
        } else cout << "Invalid choice.\n";
    }
    return 0;
}
