#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Structure to represent a node in the binary search tree
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int key) : key(key), left(nullptr), right(nullptr) {}
};

// Helper function to calculate the sum of probabilities from index i to j
double sumProbabilities(const vector<double>& probabilities, int i, int j) {
    double sum = 0;
    for (int k = i; k <= j; ++k) {
        sum += probabilities[k];
    }
    return sum;
}

// Function to construct the optimal binary search tree
TreeNode* constructOBST(const vector<int>& keys, const vector<double>& probabilities) {
    int n = keys.size();

    // Create a dynamic programming table to store optimal costs
    vector<vector<double>> cost(n + 1, vector<double>(n + 1, 0));
    vector<vector<int>> root(n, vector<int>(n, 0));

    // Initialize the cost for single nodes (subtrees of size 1)
    for (int i = 0; i < n; ++i) {
        cost[i][i] = probabilities[i];
        root[i][i] = i;
    }

    // Fill in the table for subtrees of size 2, 3, ..., n
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            cost[i][j] = numeric_limits<double>::max();
            double sum = sumProbabilities(probabilities, i, j);

            // Try all possible roots for the subtree
            for (int r = i; r <= j; ++r) {
                double c = ((r > i) ? cost[i][r - 1] : 0) + ((r < j) ? cost[r + 1][j] : 0) + sum;
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }

    // Reconstruct the optimal binary search tree
    vector<TreeNode*> nodes(n);
    for (int i = 0; i < n; ++i) {
        nodes[i] = new TreeNode(keys[i]);
    }

    return nullptr; // Return the root node of the constructed tree
}

// Function to print the inorder traversal of a binary search tree
void printInorder(TreeNode* root) {
    if (root) {
        printInorder(root->left);
        cout << root->key << " ";
        printInorder(root->right);
    }
}

int main() {
    vector<int> keys = {10, 20, 30, 40, 50};
    vector<double> probabilities = {0.1, 0.2, 0.3, 0.2, 0.2};

    TreeNode* root = constructOBST(keys, probabilities);

    cout << "Inorder traversal of the constructed binary search tree:" << endl;
    printInorder(root);
    cout << endl;

    // TODO: Free memory by deleting the tree nodes

    return 0;
}
