#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct sNode {
    char val;
    sNode* left;
    sNode* right;
    sNode(char v) : val(v), left(nullptr), right(nullptr) {}
};

sNode* ExpTree(const string& prefix) {
    stack<sNode*> stk;
    for (int i = prefix.size() - 1; i >= 0; --i) {
        char c = prefix[i];
        if (isalnum(c)) {
            stk.push(new sNode(c));
        } else {
            sNode* node = new sNode(c);
            node->left = stk.top(); stk.pop();
            node->right = stk.top(); stk.pop();
            stk.push(node);
        }
    }
    return stk.top();
}

void postOrder(sNode* root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val;
}

void deleteTree(sNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string prefix;
    cout<<"enter : ";
    cin>>prefix;
    sNode* root = ExpTree(prefix);
    
    cout << "Post-order traversal of the expression tree: ";
    postOrder(root);
    //cout<<"abc*-de/-f+";
    cout << endl;

    deleteTree(root); // Delete the entire tree to free memory

    return 0;
}
