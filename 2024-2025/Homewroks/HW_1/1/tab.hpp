#pragma once
#include <string>
#include <ctime>
using namespace std;

struct Tab {
    string url;
    time_t timestamp;
    Tab* prev;
    Tab* next;

    Tab(const string& _url, time_t _timestamp)
        : url(_url), timestamp(_timestamp), prev(nullptr), next(nullptr) {}
};