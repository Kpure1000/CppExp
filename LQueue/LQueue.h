#include <exception>
template <typename T>
struct LQueue
{
private:
    struct LNode
    {
        LNode() {}
        T *val = nullptr;
        LNode *next = nullptr, *pre = nullptr;
    };
    LNode *m_Rear, *m_Front;
    size_t m_Size;

public:
    LQueue() : m_Rear(new LNode()), m_Front(m_Rear), m_Size(0) {}
    inline bool is_empty() { return m_Rear == m_Front; }
    inline size_t size() { return m_Size; }
    void push_front(T *val)
    {
        m_Front->val = val;
        LNode *newN = new LNode();
        m_Front->next = newN;
        newN->pre = m_Front;
        m_Front = newN;

        m_Size++;
    }
    void pop_back()
    {
        if (is_empty())
            throw std::bad_exception();
        auto _rear = m_Rear;
        m_Rear = m_Rear->next;
        m_Rear->pre = nullptr;
        delete _rear;

        m_Size--;
    }
    inline const T *rear() const { return m_Rear->next->pre->val; }
    inline T *front() { return m_Front->pre->val; }
};