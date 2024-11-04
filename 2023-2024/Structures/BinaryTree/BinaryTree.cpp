#include <iostream>

template <typename T>
class TreeNode {
private:
    T data;
    TreeNode<T>* right, *left;

    void clear(TreeNode<T>*& root) {
        if (!root) {
            return;
        }

        clear(root->left);
        clear(root->right);

        delete root;
        root = nullptr;
    }

public:
    TreeNode() : data(0), right(nullptr), left(nullptr) {};
    TreeNode(const T& value) : data(value), right(nullptr), left(nullptr) {};
    ~TreeNode() { };

    void insert(TreeNode<T>*& cur, const T& value) {
        if (!cur) {
            cur = new TreeNode<T>(value);
            return;
        }

        if (cur->data > value) {
            insert(cur->left, value);
        }
        else if (cur->data < value) {
            insert(cur->right, value);
        }
        else {
            return;
        }
    }

    void print(TreeNode<T>* cur) {
        if (!cur) {
            return;
        }

        print(cur->left);
        std::cout << cur->value << ", ";
        print(cur->right);
    }
};


int main()
{
    TreeNode<int>* tree1 = new TreeNode<int>();

    tree1->insert(tree1, 5);
    //tree1->print(tree1);
}
