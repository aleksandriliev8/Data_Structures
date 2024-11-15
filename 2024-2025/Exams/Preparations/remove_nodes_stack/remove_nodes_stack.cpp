#include <iostream>
#include <stack>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution 
{
public:
    ListNode* removeNodes(ListNode* node) 
    {
        if (!node || !node->next)
            return node;

        stack<ListNode*> listNodes;
        int maxValue = INT_MIN;

        ListNode* iter = nullptr;

        while (node)
        {
            listNodes.push(node);
            node = node->next;
        }

        while (!listNodes.empty())
        {
            ListNode* current = listNodes.top();
            listNodes.pop();

            if (current->val >= maxValue)
            {
                maxValue = current->val;
                current->next = iter;
                iter = current;
            }
            else
            {
                delete current;
            }
        }

        return iter;
    }
};

void freeList(ListNode* node)
{
    while (node)
    {
        ListNode* toDelete = node;
        node = node->next;
        delete toDelete;
    }
}

int main()
{
    Solution s;

    ListNode* result =
        s.removeNodes(new ListNode(5, new ListNode(2, new ListNode(13, new ListNode(3, new ListNode(8))))));

    ListNode* toDelete = result;

    while (result)
    {
        std::cout << result->val << " ";
        result = result->next;
    }

    freeList(toDelete);
}