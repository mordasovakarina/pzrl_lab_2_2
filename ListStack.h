#ifndef LIST_STACK_H
#define LIST_STACK_H

#include "StackImplementation.h"

struct ListNode
{
    ValueType data;
    ListNode* next;
    ListNode* prev;
    ListNode(const ValueType& val);
};

class ListStack : public IStackImplementation
{
private:
    ListNode* _head;
    ListNode* _tail;
    size_t _size;

public:
    ListStack();
    ListStack(const ListStack& other);
    ~ListStack();

    void push(const ValueType& value) override;
    void pop() override;
    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;

    IStackImplementation* clone() const override; 
};

#endif
