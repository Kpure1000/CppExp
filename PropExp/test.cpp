#include <iostream>

#include "property.h"

struct A {
    A() : p(""), p1("p1"), p2("p2") {
    }

    std::string getp1() {
        return p1.p1;
    }

    PROP_WR(A, std::string, p,
        {
            std::cout << "p set\n";
            p += value + value;
        },
        {
            std::cout << "p get\n";
            return p;
        }
    );
    PROP_W(A, std::string, p1,
        {
            std::cout << "p1 set\n";
            p1 += value + value;
        }
    );
    PROP_R(A, std::string, p2,
            std::cout << "p2 get\n";
            return p2 + "+++";
    );

};

int main(int argc, char const *argv[])
{
    A a;
    a.p = "asd"; // p set
    std::string s = a.p; // p get
    std::cout << s << std::endl;

    a.p1 = a.p2; // p2 get and p1 set
    std::cout << a.getp1() << std::endl;

    std::string sp2 = a.p2; // p2 get
    std::cout << sp2 << std::endl;

    return 0;
}
