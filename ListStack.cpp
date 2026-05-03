#include <cstddef>
#include "ListStack.h"
#include <stdexcept>

ListNode::ListNode(const ValueType& val)
    : data(val), next(nullptr), prev(nullptr) {}

ListStack::ListStack() : _head(nullptr), _tail(nullptr), _size(0) {}

ListStack::ListStack(const ListStack& other)
    : _head(nullptr), _tail(nullptr), _size(0)
{
    ListNode* current = other._head;
    while (current)
    {
        push(current->data);
        current = current->next;
    }
}


ListStack::~ListStack()
{
    while (!isEmpty())
    {
        pop();
    }
}

void ListStack::push(const ValueType& value)
{
    ListNode* newNode = new ListNode(value);
    if (isEmpty())
    {
        _head = newNode;
        _tail = newNode;
    }
    else
    {
        newNode->prev = _tail;
        _tail->next = newNode;
        _tail = newNode;
    }
    ++_size;
}

void ListStack::pop()
{
    if (isEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }
    ListNode* toDelete = _tail;
    if (_head == _tail)
    {
        _head = nullptr;
        _tail = nullptr;
    }
    else
    {
        _tail = _tail->prev;
        _tail->next = nullptr;
    }
    delete toDelete;
    --_size;
}

const ValueType& ListStack::top() const
{
    if (isEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }
    return _tail->data;
}

bool ListStack::isEmpty() const
{
    return _size == 0;
}

size_t ListStack::size() const
{
    return _size;
}



IStackImplementation* ListStack::clone() const
{
    return new ListStack(*this);
}
