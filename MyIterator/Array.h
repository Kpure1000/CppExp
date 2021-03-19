#include <cstdlib>

template <typename Array>
class ArrayIterator_Const
{
public:
    using ValueType = typename Array::ValueType;
    using PointerType = ValueType *;
    using ReferenceType = ValueType &;

public:
    ArrayIterator_Const(PointerType data)
        : m_Data(data)
    {
    }

    ReferenceType operator*()
    {
        return *m_Data;
    }

    PointerType operator->()
    {
        return m_Data;
    }

    ReferenceType operator[](int index)
    {
        return *(m_Data + index);
    }

    bool operator==(const ArrayIterator_Const &other)
    {
        return this->m_Data == other.m_Data;
    }

    bool operator!=(const ArrayIterator_Const &other)
    {
        return this->m_Data != other.m_Data;
    }

    ArrayIterator_Const &operator++()
    {
        m_Data++;
        return *this;
    }

    ArrayIterator_Const operator++(int)
    {
        ArrayIterator_Const tmpItr = *this;
        ++(*this);
        return tmpItr;
    }

private:
    PointerType m_Data;
};

template <typename _Type, size_t _Size>
class Array
{
public:
    using ValueType = _Type;
    using Iterator_Const = ArrayIterator_Const<Array<_Type, _Size> >;

public:
    Array()
    {
    }

    _Type &operator[](size_t index) { return m_Data[index]; }
    _Type operator[](size_t index) const { return m_Data[index]; }

    Iterator_Const begin() { return Iterator_Const(m_Data); }
    Iterator_Const end() { return Iterator_Const(m_Data + _Size); }

private:
    _Type m_Data[_Size];
};