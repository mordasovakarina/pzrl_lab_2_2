#include <cstddef>
#include "Stack.h"
#include "VectorStack.h"
#include "ListStack.h"
#include <stdexcept>

static IStackImplementation* createImplementation(StackContainer container)
{
    switch (container)
    {
        case StackContainer::Vector:
            return new VectorStack();
        case StackContainer::List:
            return new ListStack();
        default:
            return new VectorStack();
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
    _pimpl = copyStack._pimpl->clone();
   /* if (_containerType == StackContainer::Vector)
    {
        _pimpl = new VectorStack(*dynamic_cast<VectorStack*>(copyStack._pimpl));
    }
    else
    {
        _pimpl = new ListStack(*dynamic_cast<ListStack*>(copyStack._pimpl));
    }*/
/*    _pimpl = createImplementation(_containerType);
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
*/
}

Stack& Stack::operator=(const Stack& copyStack)
{
    if (this != &copyStack)
    {
        IStackImplementation* newImpl = copyStack._pimpl->clone();
        delete _pimpl;
        _pimpl = newImpl;
        _containerType = copyStack._containerType;
    }
    return *this;
}

/*{
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
*/
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
