#include <cstddef>
#include "Stack.h"
#include "StackImplementation.h"
#include <stdexcept>
#include <vector>


class VectorStackImplementation : public IStackImplementation
{
private:
    ValueType* _data;
    size_t _size;
    size_t _capacity;

    void resize(size_t newCapacity)
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

public:
    VectorStackImplementation() : _data(nullptr), _size(0), _capacity(0) {}

    ~VectorStackImplementation()
    {
        delete[] _data;
    }

    void push(const ValueType& value) override
    {
        if (_size >= _capacity)
        {
            size_t newCapacity = (_capacity == 0) ? 1 : _capacity * 2;
            resize(newCapacity);
        }
        _data[_size++] = value;
    }

    void pop() override
    {
        if (isEmpty())
        {
            throw std::runtime_error("Stack is empty");
        }
        --_size;
    }

    const ValueType& top() const override
    {
        if (isEmpty())
        {
            throw std::runtime_error("Stack is empty");
        }
        return _data[_size - 1];
    }

    bool isEmpty() const override
    {
        return _size == 0;
    }

    size_t size() const override
    {
        return _size;
    }
};

struct ListNode
{
    ValueType data;
    ListNode* next;
    ListNode* prev;
    ListNode(const ValueType& val) : data(val), next(nullptr), prev(nullptr) {}
};

class ListStackImplementation : public IStackImplementation
{
private:
    ListNode* _head;
    ListNode* _tail;
    size_t _size;

public:
    ListStackImplementation() : _head(nullptr), _tail(nullptr), _size(0) {}

    ~ListStackImplementation()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void push(const ValueType& value) override
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

    void pop() override
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

    const ValueType& top() const override
    {
        if (isEmpty())
        {
            throw std::runtime_error("Stack is empty");
        }
        return _tail->data;
    }

    bool isEmpty() const override
    {
        return _size == 0;
    }

    size_t size() const override
    {
        return _size;
    }
};

static IStackImplementation* createImplementation(StackContainer container)
{
    switch (container)
    {
        case StackContainer::Vector:
            return new VectorStackImplementation();
        case StackContainer::List:
            return new ListStackImplementation();
        default:
            return new VectorStackImplementation();
    }
}

Stack::Stack(StackContainer container)
    : _containerType(container)
{
    _pimpl = createImplementation(container);
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
    : _containerType(container)
{
    _pimpl = createImplementation(container);
    for (size_t i = 0; i < arraySize; ++i)
    {
        push(valueArray[i]);
    }
}


Stack::Stack(const Stack& copyStack)
    : _containerType(copyStack._containerType)
{
    _pimpl = createImplementation(_containerType);
    size_t sz = copyStack.size();
    ValueType* buffer = new ValueType[sz];
    Stack& nonConstCopy = const_cast<Stack&>(copyStack);
    for (size_t i = 0; i < sz; ++i)
    {
        buffer[sz - 1 - i] = nonConstCopy.top();
        nonConstCopy.pop();
    }
    for (size_t i = 0; i < sz; ++i)
    {
        nonConstCopy.push(buffer[i]);
        push(buffer[i]);
    }
    delete[] buffer;
}

Stack& Stack::operator=(const Stack& copyStack)
{
    if (this != &copyStack)
    {
        while (!isEmpty())
        {
            pop();
        }
        size_t sz = copyStack.size();
        ValueType* buffer = new ValueType[sz];
        Stack& nonConstCopy = const_cast<Stack&>(copyStack);
        for (size_t i = 0; i < sz; ++i)
        {
            buffer[sz - 1 - i] = nonConstCopy.top();
            nonConstCopy.pop();
        }
        for (size_t i = 0; i < sz; ++i)
        {
            nonConstCopy.push(buffer[i]);
            push(buffer[i]);
        }
        delete[] buffer;
        _containerType = copyStack._containerType;
    }
    return *this;
}






Stack::Stack(Stack&& moveStack) noexcept
    : _pimpl(moveStack._pimpl)
    , _containerType(moveStack._containerType)
{
    moveStack._pimpl = nullptr;
}

Stack& Stack::operator=(Stack&& moveStack) noexcept
{
    if (this != &moveStack)
    {
        delete _pimpl;
        _pimpl = moveStack._pimpl;
        _containerType = moveStack._containerType;
        moveStack._pimpl = nullptr;
    }
    return *this;
}

Stack::~Stack()
{
    delete _pimpl;
}

void Stack::push(const ValueType& value)
{
    if (_pimpl)
    {
        _pimpl->push(value);
    }
}

void Stack::pop()
{
    if (_pimpl)
    {
        _pimpl->pop();
    }
}

const ValueType& Stack::top() const
{
    if (!_pimpl || _pimpl->isEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }
    return _pimpl->top();
}

bool Stack::isEmpty() const
{
    return !_pimpl || _pimpl->isEmpty();
}

size_t Stack::size() const
{
    return _pimpl ? _pimpl->size() : 0;
}
