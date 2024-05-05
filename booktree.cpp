#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class TNode {
public:
    string name;
    TNode* child;

    TNode(string n) : name(n), child(nullptr) {}
   
    void addChild(TNode* node) {
        child = node;
    }

    void print(int level = 0) {
        for (int i = 0; i <= level; ++i) {
            cout << "  ";
        }
        cout << "- " << name << endl;
        if (child != nullptr) {
            child->print(level + 1);
        }
    }
};

void constructTree(TNode* root) {
    string chapterName;
    cout << "Enter the name of the chapter: ";
    cin >> chapterName;
    TNode* chapterNode = new TNode(chapterName);
    root->addChild(chapterNode);

    int sections;
    cout << "Enter the number of sections in "  << ": ";
    cin >> sections;
    for (int i = 0; i < sections; ++i) {
        string sectionName;
        cout << "Enter the name of section " << i << ": ";
        cin >> sectionName;
        TNode* sectionNode = new TNode(sectionName);
        chapterNode->addChild(sectionNode);

        cout << "Enter the number of subsections in " << sectionName << ": ";
        int numSubsections;
        cin >> numSubsections;
        for (int j = 1; j <= numSubsections; ++j) {
            cout << "Enter the name of subsection " << j << ": ";
            string subsectionName;
            cin >> subsectionName;
            TNode* subsectionNode = new TNode(subsectionName);
            sectionNode->addChild(subsectionNode);
        }
    }
}

int main() {
    TNode* bookTree = new TNode("Book");

    constructTree(bookTree);
    cout << "\nTree representing the book structure:\n";
    bookTree->print();

    return 0;
}
