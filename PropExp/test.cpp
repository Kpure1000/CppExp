#include <iostream>

#include "property.h"

struct A {
    A() :p(""){
    }

    PROP_WR(std::string, p,
        {
            std::cout << "Aset\n";
        },
        {
            std::cout << "Aget\n";
            return value;
        }
    );

};


struct B {
    B() :p(""){
    }

    PROP_W(std::string, p,
        {
            std::cout << "Bset\n";
        }
    );

};
struct C {
    C() :p(""), p2(""){
    }

    PROP_W(std::string, p,
        {
            std::cout << "Cset\n";
        }
    );

    PROP_R(std::string, p2,
        {
            std::cout << "Cget\n";
            return value;
        }
    );

};
    

int main(int argc, char const *argv[])
{
    std::string ss;
    A a;
    a.p = "asd"; // set
    std::string s = a.p; // get
    ss = a.p; // get

    
    B b;
    b.p = "asd"; // set

    C c;
    ss = c.p2; // get
    c.p = "dsa"; // set

    return 0;
}
