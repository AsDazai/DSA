#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Structure to represent a node in the AVL tree
struct AVLNode {
    string keyword;
    string meaning;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(string key, string meaning) : keyword(key), meaning(meaning), height(1), left(nullptr), right(nullptr) {}
};

// Class for AVL Tree Dictionary
class AVLDictionary {
private:
    AVLNode* root;

    // Get the height of a node
    int getHeight(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Get balance factor of a node
    int getBalance(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Rotate right
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    // Rotate left
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    // Insert a new node with keyword and meaning
    AVLNode* insertNode(AVLNode* node, string keyword, string meaning) {
        // Perform normal BST insertion
        if (node == nullptr)
            return new AVLNode(keyword, meaning);

        if (keyword < node->keyword)
            node->left = insertNode(node->left, keyword, meaning);
        else if (keyword > node->keyword)
            node->right = insertNode(node->right, keyword, meaning);
        else // Keyword already exists
            return node;

        // Update height of this ancestor node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Get the balance factor to check if this node became unbalanced
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && keyword < node->left->keyword)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && keyword > node->right->keyword)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && keyword > node->left->keyword) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && keyword < node->right->keyword) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        // Return the (unchanged) node pointer
        return node;
    }

    // Find the node with minimum keyword in the tree
    AVLNode* findMinNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Delete a node with keyword from the tree
    AVLNode* deleteNode(AVLNode* root, string keyword) {
        if (root == nullptr)
            return root;

        // Perform standard BST delete
        if (keyword < root->keyword)
            root->left = deleteNode(root->left, keyword);
        else if (keyword > root->keyword)
            root->right = deleteNode(root->right, keyword);
        else {
            // Node with only one child or no child
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLNode* temp = root->left ? root->left : root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else // One child case
                    *root = *temp; // Copy the contents of the non-empty child

                delete temp;
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                AVLNode* temp = findMinNode(root->right);

                // Copy the inorder successor's data to this node
                root->keyword = temp->keyword;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        // If the tree had only one node, return
        if (root == nullptr)
            return root;

        // Update height of the current node
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Get the balance factor to check if this node became unbalanced
        int balance = getBalance(root);

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // Inorder traversal to display sorted keywords
    void displayInorder(AVLNode* node) {
        if (node == nullptr)
            return;
        displayInorder(node->left);
        cout << node->keyword << ": " << node->meaning << endl;
        displayInorder(node->right);
    }

public:
    AVLDictionary() : root(nullptr) {}

    // Insert a new keyword and its meaning
    void insertKeyword(string keyword, string meaning) {
        root = insertNode(root, keyword, meaning);
    }

    // Delete a keyword and its meaning
    void deleteKeyword(string keyword) {
        root = deleteNode(root, keyword);
    }

    // Display keywords and meanings in ascending order
    void displayAscending() {
        cout << "Keywords and meanings in ascending order:" << endl;
        displayInorder(root);
    }

    // Display keywords and meanings in descending order
    void displayDescending() {
        cout << "Keywords and meanings in descending order:" << endl;
        displayDescendingHelper(root);
    }

    // Helper function for displaying keywords and meanings in descending order
    void displayDescendingHelper(AVLNode* node) {
        if (node == nullptr)
            return;
        displayDescendingHelper(node->right);
        cout << node->keyword << ": " << node->meaning << endl;
        displayDescendingHelper(node->left);
    }

    // Destructor to deallocate memory
    ~AVLDictionary() {
        deleteTree(root);
    }

    // Function to delete the tree and deallocate memory
    void deleteTree(AVLNode* node) {
        if (node == nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

int main() {
    AVLDictionary dictionary;

    // Insert keywords and meanings
    dictionary.insertKeyword("apple", "A fruit");
    dictionary.insertKeyword("banana", "A fruit");
    dictionary.insertKeyword("orange", "A fruit");
    dictionary.insertKeyword("car", "A vehicle");
    dictionary.insertKeyword("house", "A building");

    // Display keywords and meanings
    dictionary.displayAscending();
    cout << endl;
    dictionary.displayDescending();

    // Delete a keyword
    dictionary.deleteKeyword("banana");

    // Display keywords after deletion
    cout << endl << "Keywords after deleting 'banana':" << endl;
    dictionary.displayAscending();

    return 0;
}
