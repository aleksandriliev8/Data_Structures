#include <iostream>
#include <stack>
#include <cassert>

template <typename T>
class Element {
public:
    T data;
    Element* next;

    Element(const T& value) {
        data = value;
        next = nullptr;
    };
};


template <typename T>
class Stack {
private:
    size_t sizeStack = 0;
    Element<T>* head;
public:
    Stack() {
        sizeStack = 0;
        head = nullptr;
    }

    ~Stack() {
        clear();
    }

    size_t size() const {
        return sizeStack;
    }

    void push(const T& value) {
        Element<T>* newElement = new Element<T>(value);

        newElement->next = head;
        head = newElement;
        ++sizeStack;
    }

    void pop() {
        assert(sizeStack > 0);

        Element<T>* toDelete = head;
        head = head->next;
        delete toDelete;

        --sizeStack;
    }

    T& top() const{
        assert(sizeStack > 0);
        return head->data;
    }

    bool empty() const {
        return !head;
    }

    void clear() {
        if (head) {
            while (head) {
                Element<T>* toDelete = head;
                head = head->next;
                delete toDelete;
            }
            sizeStack = 0;
        }
    }
};

bool isValidExpression(const char expression[]) {
    Stack<char> brackets;

    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        char cur = expression[i];

        if (cur == '(' || cur == '{' || cur == '[') {
            brackets.push(cur);
        }
        else if (cur == ')') {
            if (!brackets.empty() && brackets.top() == '(') {
                brackets.pop();
            }
            else {
                brackets.clear();
                return false;
            }
        }
        else if (cur == '}') {
            if (!brackets.empty() && brackets.top() == '{') {
                brackets.pop();
            }
            else {
                brackets.clear();
                return false;
            }
        }
        else if (cur == ']') {
            if (!brackets.empty() && brackets.top() == '[') {
                brackets.pop();
            }
            else {
                brackets.clear();
                return false;
            }
        }
        else {
            continue;
        }
    }

    return true;
}

int main()
{
    const char expression[] = {'(', '[', '{', ')', ']', ')'};

    std::cout << isValidExpression(expression);
}
