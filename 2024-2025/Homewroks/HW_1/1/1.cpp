#include <iostream>
#include <string>
#include <ctime>
#include "./tab.hpp"
#include "./merge_sort_list.hpp"
using namespace std;

class Browser
{
private:
    Tab* head;
    Tab* tail;
    Tab* current;

    void updateTime(Tab* tab)
    {
        tab->timestamp = time(nullptr);
    }

    void sort(bool by_url)
    {
        if (!head || !head->next)
            return;

        head = mergeSort(head, by_url);

        current = head;
    }

public:
    Browser() : head(nullptr), tail(nullptr), current(nullptr)
    {
        go("about:blank");
    }

    ~Browser()
    {
        while (head)
        {
            Tab* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void go(const string& url)
    {
        if (!current)
        {
            insert(url);
            return;
        }

        current->url = url;
        updateTime(current);
    }

    void insert(const string& url)
    {
        Tab* new_tab = new Tab(url, time(nullptr));
        if (!head)
            head = tail = current = new_tab;
        else
        {
            new_tab->prev = current;
            new_tab->next = current->next;

            if (current->next)
                current->next->prev = new_tab;
            else
                tail = new_tab;

            current->next = new_tab;
            current = new_tab;
        }
    }

    void back()
    {
        if (current && current->prev)
            current = current->prev;
    }

    void forward()
    {
        if (current && current->next)
            current = current->next;
    }

    void remove()
    {
        if (!current) return;

        Tab* to_delete = current;

        if (current->prev)
            current->prev->next = current->next;
        else
            head = current->next;

        if (current->next)
            current->next->prev = current->prev;
        else
            tail = current->prev;

        if (current->next)
            current = current->next;
        else if (current->prev)
            current = current->prev;
        else
        {
            delete to_delete;
            current = head = tail = nullptr;
            return;
        }

        delete to_delete;
    }

    void print() const
    {
        for (Tab* tab = head; tab; tab = tab->next)
        {
            if (tab == current)
                cout << ">";
            cout << tab->url << " " << tab->timestamp << endl;
        }
    }

    void sortUrl() { sort(true); }
    void sortTime() { sort(false); }
};

int main()
{
    Browser browser;
    string command;

    cout << '$';

    while (cin >> command)
    {   
        if (command == "GO")
        {
            string url;
            cin >> url;
            browser.go(url);
        }
        else if (command == "INSERT")
        {
            string url;
            cin >> url;
            browser.insert(url);
        }
        else if (command == "BACK")
        {
            browser.back();
        }
        else if (command == "FORWARD")
        {
            browser.forward();
        }
        else if (command == "REMOVE")
        {
            browser.remove();
        }
        else if (command == "PRINT")
        {
            browser.print();
        }
        else if (command == "SORT")
        {
            string sort_by;
            cin >> sort_by;

            if (sort_by == "URL")
                browser.sortUrl();
            else if
                (sort_by == "TIME") browser.sortTime();
            else
                throw invalid_argument("Invalid sort by command");
        }
        else
        {
            cerr << "Invalid command: " << command << endl;
            continue;
        }

        cout << '$';
    }

    return 0;
}