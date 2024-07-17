#include <iostream>

using namespace std;

// Definition of a node in BST
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    // Helper function for searching a value in BST
    TreeNode* searchRecursive(TreeNode* root, int val) {
        if (root == nullptr || root->val == val)
            return root;

        if (val < root->val)
            return searchRecursive(root->left, val);
        else
            return searchRecursive(root->right, val);
    }

    // Helper function to find minimum value node in a subtree
    TreeNode* findMin(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    // Helper function to delete a node with given value from subtree
    TreeNode* deleteRecursive(TreeNode* root, int val) {
        if (root == nullptr)
            return root;

        if (val < root->val)
            root->left = deleteRecursive(root->left, val);
        else if (val > root->val)
            root->right = deleteRecursive(root->right, val);
        else {
            // Case 1: Node to be deleted has no children or only one child
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            // Case 2: Node to be deleted has two children
            TreeNode* temp = findMin(root->right);
            root->val = temp->val;
            root->right = deleteRecursive(root->right, temp->val);
        }
        return root;
    }

public:
    BST() : root(nullptr) {}

    // Function to search for a value in BST
    bool search(int val) {
        TreeNode* result = searchRecursive(root, val);
        return result != nullptr;
    }

    // Function to insert a value into BST
    void insert(int val) {
        root = insertRecursive(root, val);
    }

    // Function to delete a value from BST
    void remove(int val) {
        root = deleteRecursive(root, val);
    }

    // Helper function to insert a value recursively
    TreeNode* insertRecursive(TreeNode* root, int val) {
        if (root == nullptr)
            return new TreeNode(val);

        if (val < root->val)
            root->left = insertRecursive(root->left, val);
        else if (val > root->val)
            root->right = insertRecursive(root->right, val);

        return root;
    }

    // Helper function to get the root of the BST
    TreeNode* getRoot() {
        return root;
    }
};

// Function to print inorder traversal of BST (for testing)
void inorder(TreeNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}

int main() {
    BST bst;

    cout << "Binary Search Tree Operations" << endl;
    cout << "=============================" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Search" << endl;
    cout << "3. Delete" << endl;
    cout << "4. Exit" << endl;

    int choice;
    int value;
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                bst.insert(value);
                cout << value << " inserted into BST." << endl;
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                if (bst.search(value))
                    cout << value << " found in the BST." << endl;
                else
                    cout << value << " not found in the BST." << endl;
                break;
            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                bst.remove(value);
                cout << value << " deleted from BST." << endl;
                break;
            case 4:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }

        // Print the BST inorder traversal after each operation
        cout << "BST inorder traversal: ";
        inorder(bst.getRoot());
        cout << endl;
        cout << endl;
    }

    return 0;
}
