#ifndef VECTOR_STACK_H
#define VECTOR_STACK_H

#include "StackImplementation.h"

class VectorStack : public IStackImplementation
{
private:
    ValueType* _data;
    size_t _size;
    size_t _capacity;

    void resize(size_t newCapacity);

public:
    VectorStack();
    VectorStack(const VectorStack& other);
    ~VectorStack();

    void push(const ValueType& value) override;
    void pop() override;
    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;


    IStackImplementation* clone() const override;
};

#endif
