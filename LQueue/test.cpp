#include "LQueue.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    LQueue<int> l;
    int * a = new int(1);
    int * b = new int(2);
    l.push_front(a);
    l.push_front(b);
    std::cout << "front: " << *l.front() << "\n";
    std::cout << "rear: " << *l.rear() << "\n";
    std::cout << "size: " << l.size() << "\n";
    std::cout << std::endl;
    l.pop_back();
    std::cout << "front: " << *l.front() << "\n";
    std::cout << "rear: " << *l.rear() << "\n";
    std::cout << "size: " << l.size() << "\n";
    std::cout << std::endl;
    l.pop_back();
    std::cout << l.is_empty() << "\n";
    std::cout << "size: " << l.size() << "\n";
    std::cout << std::endl;
    l.push_front(b);
    std::cout << "front: " << *l.front() << "\n";
    std::cout << "rear: " << *l.rear() << "\n";
    std::cout << "size: " << l.size() << "\n";

    return 0;
}
