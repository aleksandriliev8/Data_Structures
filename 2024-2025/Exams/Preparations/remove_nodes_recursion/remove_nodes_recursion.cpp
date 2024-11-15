#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNodes(ListNode* head)
    {
        int maxVal = INT_MIN;
        return removeNodesRecursive(head, maxVal);
    }

private:
    ListNode* removeNodesRecursive(ListNode* node, int& maxVal)
    {
        if (!node)
        {
            return nullptr;
        }

        ListNode* filteredNext = removeNodesRecursive(node->next, maxVal);

        if (node->val >= maxVal)
        {
            maxVal = node->val;
            node->next = filteredNext;
            return node;
        }
        else
        {
            delete node;
            return filteredNext;
        }
    }
};

void printList(ListNode* node)
{
    cout << "[";

    while (node)
    {
        cout << node->val;

        if (node->next)
        {
            cout << ",";
        }

        node = node->next;
    }

    cout << "]" << endl;
}

int main()
{
    Solution s;

    ListNode* result =
        s.removeNodes(new ListNode(5, new ListNode(2, new ListNode(13, new ListNode(3, new ListNode(8))))));

    printList(result);

    ListNode* current = result;

    while (current)
    {
        ListNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }

    return 0;
}