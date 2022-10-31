#include <iostream>

template<typename T> 
struct LNode
{
    LNode<T> *next;
    T val;
    LNode(T val = -1) : val(val)
    {
    }
};

template<typename T>
struct List
{
    LNode<T> *m_Head;
    LNode<T> *m_Tail;
    size_t m_Size=0;

    List()
    {
        m_Head = new LNode<T>();
        m_Tail = m_Head;
        m_Tail->next = nullptr;
    }

    inline void add_next(T val, LNode<T> *cur)
    {
        auto newNode = new LNode<T>(val);
        newNode->next = cur->next;
        cur->next = newNode;
        m_Size++;

    }

    inline void add_tail(T val)
    {
        add_next(val, m_Tail);
        m_Tail = m_Tail->next;
    }

};

template <typename T>
std::ostream &operator<<(std::ostream &os, List<T> const &l)
{
    for (auto p = l.m_Head->next; p != nullptr; p = p->next)
    {
        os << p->val << " ";
    }
    return os;
}

using ListInt = List<int>;

template <typename T>
void swap_seg(List<T> &l, int n1, int n2, int m1, int m2)
{
    printf("swap: [%d ~ %d] <-> [%d ~ %d]\n", n1, n2, m1, m2);
    auto p = l.m_Head;
    auto pn1_pre = p;
    auto pn2 = p;
    auto pm1_pre = p;
    auto pm2 = p;
    for ( int i = -1 ; p->next != nullptr ; i++, p = p->next )
    {
        if (i + 1 == n1)
        {
            pn1_pre = p;
        }
        if (i == n2)
        {
            pn2 = p->next;
        }
        if (i + 1 == m1)
        {
            pm1_pre = p;
        }
        if (i == m2)
        {
            pm2 = p->next;
        }
    }

    auto pn1 = pn1_pre->next;
    auto pm1 = pm1_pre->next;
    auto pn2_next = pn2->next;
    auto pm2_next = pm2->next;

    pn1_pre->next = pm1;
    pm1_pre->next = pn1;
    pn2->next = pm2_next;
    pm2->next = pn2_next;
}
#include <chrono>
#include <vector>
#include <iomanip>
using FloatingPointMicroSeconds = std::chrono::duration<double, std::micro>;
struct Timer
{
    std::chrono::steady_clock::time_point start;
    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::setprecision(4) << std::fixed << "cost: " << (FloatingPointMicroSeconds(end.time_since_epoch()) - 
		FloatingPointMicroSeconds(start.time_since_epoch())).count() * 0.001 << "ms\n";
    }
};

int main(int argc, char const *argv[])
{
    {
        ListInt l;
        for (int i = 0; i < 7; i++)
        {
            l.add_tail(i);
        }
        std::cout << l << "\n";
        swap_seg(l, 0,2,4,6);
        std::cout << l << "\n";
        std::cout <<"----------------------------------------\n";
    }

// #define N 200000
//     srand(0);
//     int insert_at = 0;
//     {
//         Timer t;
//         ListInt L;
//         for (int i = 0; i < N; i++)
//         {
//             insert_at = rand() % 100;
//             auto p = L.m_Head;
//             for (int k = 0; p->next != nullptr && k < insert_at; k++, p = p->next)
//                 ;
//             L.add_next(i, p);
//         }
//     }
//     {
//         Timer t;
//         std::vector<int> V;
//         for (int i = 0; i < N; i++)
//         {
//             insert_at = rand() % 100;
//             if (insert_at < V.size())
//                 V.insert(V.begin() + insert_at, i);
//             else
//                 V.push_back(i);
//         }
//     }

    return 0;
}

