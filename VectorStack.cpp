#include <cstddef>
#include "VectorStack.h"
#include <stdexcept>

VectorStack::VectorStack() : _data(nullptr), _size(0), _capacity(0) {}

VectorStack::VectorStack(const VectorStack& other)
    : _data(nullptr), _size(other._size), _capacity(other._capacity)
{
    if (_capacity > 0)
    {
        _data = new ValueType[_capacity];
        for (size_t i = 0; i < _size; ++i)
            _data[i] = other._data[i];
    }
}

VectorStack::~VectorStack()
{
    delete[] _data;
}

void VectorStack::resize(size_t newCapacity)
{
    ValueType* newData = new ValueType[newCapacity];
    for (size_t i = 0; i < _size; ++i)
    {
        newData[i] = _data[i];
    }
    delete[] _data;
    _data = newData;
    _capacity = newCapacity;
}

void VectorStack::push(const ValueType& value)
{
    if (_size >= _capacity)
    {
        size_t newCapacity = (_capacity == 0) ? 1 : _capacity * 2;
        resize(newCapacity);
    }
    _data[_size++] = value;
}

void VectorStack::pop()
{
    if (isEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }
    --_size;
}

const ValueType& VectorStack::top() const
{
    if (isEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }
    return _data[_size - 1];
}

bool VectorStack::isEmpty() const
{
    return _size == 0;
}

size_t VectorStack::size() const
{
    return _size;
}




IStackImplementation* VectorStack::clone() const
{
    return new VectorStack(*this);
}
