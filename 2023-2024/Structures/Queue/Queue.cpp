#include <iostream>
#include <queue>
#include <cassert>

template <typename T>
class Element {
public:
    T data;
    Element<T> *next, *prev;

    Element(const T& value) {
        data = value;
        prev = next = nullptr;
    }
};

template <typename T>
class Queue {
private:
    size_t sizeQueue;
    Element<T> *head, *tail;
public:
    Queue() : sizeQueue(0){
        head = tail = nullptr;
    };

    bool empty() const{
        return !head;
    }

    size_t size() const {
        return sizeQueue;
    }

    T& back() const {
        assert(sizeQueue > 0);
        return tail->data;
    }

    void push(const T& value) {
        Element<T>* newElement = new Element<T>(value);

        if (sizeQueue == 0) {
            head = tail = newElement;
        }
        else {
            tail = tail->next = newElement;
        }

        ++sizeQueue;
    }

    T& front() const {
        assert(sizeQueue > 0);
        return head->data;
    }

    void clear() {
        assert(sizeQueue > 0);

        if (sizeQueue > 0) {
            while (head != tail) {
                Element<T>* toDelete = head;
                head = head->next;
                delete toDelete;
            }

            delete head;
            head = nullptr;
            tail = nullptr;

            sizeQueue = 0;
        }
        else {
            return;
        }
    }

    void pop() {
        assert(sizeQueue > 0);

        if (sizeQueue > 0) {
            Element<T>* toDelete = head;
            head = head->next;
            delete toDelete;
        }
        else {
            return;
        }
    }
};

int main()
{
    unsigned int n;
    std::cin >> n;

    Queue<int> q2;
    Queue<int> q3;
    Queue<int> q5;

    q2.push(2);
    q2.push(4);
    q2.push(8);
    q2.push(16);
    q2.push(32);
    q2.push(64);

    q3.push(3);
    q3.push(9);
    q3.push(27);
    q3.push(81);
    q3.push(243);

    q5.push(5);
    q5.push(25);
    q5.push(125);
    q5.push(625);


    for (size_t i = 1; i <= n; i++)
    {
        std::cout << q2.front() * q3.front() * q5.front();

        if (i != n) {
            std::cout << ", ";
        }

        if (i % 3 == 0) {
            q5.pop();
        }
        else if (i % 2 == 0) {
            q3.pop();
        }
        else {
            q2.pop();
        }
    }
}
