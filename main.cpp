#include <iostream>


using namespace std;

#include "Deque.h"

int main() {
    Deque<int> intDeque;
    intDeque.push_back(1);
    intDeque.push_front(0);
    intDeque.push_back(2);
    intDeque.push_front(-1);

    cout << "Int Deque size: " << intDeque.size() << endl;
    cout << "Front: " << intDeque.front() << ", Back: " << intDeque.back() << endl;

    intDeque.pop_front();
    intDeque.pop_back();
    cout << "After pop front and back: Front=" << intDeque.front() << ", Back=" << intDeque.back() << endl;

    Deque<string> strDeque;
    strDeque.push_back("world");
    strDeque.push_front("Hello");
    strDeque.push_back("!");

    cout << "String Deque size: " << strDeque.size() << endl;
    cout << "Front: " << strDeque.front() << ", Back: " << strDeque.back() << endl;

    strDeque.pop_front();
    cout << "After pop front: Front=" << strDeque.front() << ", Back=" << strDeque.back() << endl;

    return 0;
}
