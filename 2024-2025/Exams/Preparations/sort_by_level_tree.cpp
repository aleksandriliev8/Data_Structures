#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct node
{
    int data;
    node* left = nullptr;
    node* right = nullptr;

    node(int d, node* l = nullptr, node* r = nullptr) :
        data(d), left(l), right(r) {}
};

void fill(node* root, vector<int>& v)
{
    if (!root)
        return;

    v.push_back(root->data);
    fill(root->left, v);
    fill(root->right, v);
}

node* level_sort(node* tree)
{
    vector<int> v;
    fill(tree, v);

    sort(v.begin(), v.end());

    node* to_return = new node(v[0]);
    int index = 1;

    queue<node*> q;
    q.push(to_return);

    while (index < v.size())
    {
        node* current = q.front();
        q.pop();

        current->left = new node(v[index++]);
        if (index < v.size())
            current->right = new node(v[index++]);

        q.push(current->left);
        q.push(current->right);
    }

    return to_return;
}

void free_tree(node* root)
{
    if (!root)
        return;

    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

void print_levels(node* result)
{
    queue<node*> q;
    q.push(result);
    q.push(nullptr);

    while (!q.empty())
    {
        node* current = q.front();
        q.pop();

        if (current == nullptr)
        {
            if (!q.empty())
            {
                q.push(nullptr);
                cout << endl;
            }
            continue;
        }

        cout << current->data << " ";
        if(current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
}

int main()
{
    node* tree = new node(5,
        new node(3,
            new node(4),
            new node(0,
                new node(1),
                new node(2))),
        new node(8,
            new node(9),
            new node(7, new node(10))));

    node* result = level_sort(tree);
    print_levels(result);

    free_tree(result);
    free_tree(tree);
}