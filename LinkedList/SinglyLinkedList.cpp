#include "SinglyLinkedList.hpp"
// #include <crtdefs.h>
#include <bits/move.h>>

namespace LearningDataStruct
{

template<typename Type>
SinglyLinkedList<Type>::Node::Node()
: next(nullptr) { }

template<typename Type>
SinglyLinkedList<Type>::Node::Node(const Type &_data)
: data(_data), next(nullptr) { }

template<typename Type>
SinglyLinkedList<Type>::Node::Node(Type &&_data)
: data(_data), next(nullptr) { }

template<typename Type>
SinglyLinkedList<Type>::Node::Node(const Type &_data, const Node *_next)
: data(_data), next(_next) { }

template<typename Type>
SinglyLinkedList<Type>::Node::Node(Type &&_data, const Node *_next)
: data(_data), next(_next) { }



template<typename Type>
SinglyLinkedList<Type>::Iterator::Iterator()
: prev(first) { }

template<typename Type>
SinglyLinkedList<Type>::Iterator::Iterator(Node *_prev)
: prev(_prev) { }

template<typename Type>
SinglyLinkedList<Type>::Iterator::Iterator(const Iterator &it)
: prev(it.prev) { }

template<typename Type>
inline Type& SinglyLinkedList<Type>::Iterator::operator*()
{
    return prev->next->data;
}

template<typename Type>
inline const Type& SinglyLinkedList<Type>::Iterator::operator*() const
{
    return prev->next->data;
}

template<typename Type>
inline SinglyLinkedList<Type>::Iterator& SinglyLinkedList<Type>::Iterator::operator++()
{
    prev = prev->next;
    return *this;
}

template<typename Type>
inline const SinglyLinkedList<Type>::Iterator SinglyLinkedList<Type>::Iterator::operator++(int)
{
    decltype(*this) old(*this);
    ++(*this);
    return old;
}

template<typename Type>
inline bool SinglyLinkedList<Type>::Iterator::operator==(const Iterator &iterator) const
{
    return prev == iterator.prev;
}

template<typename Type>
inline bool SinglyLinkedList<Type>::Iterator::operator!=(const Iterator &iteraotr) const
{
    return prev != iteraotr.prev;
}

template<typename Type>
inline SinglyLinkedList<Type>::Iterator& SinglyLinkedList<Type>::Iterator::assign(const Iterator &iterator)
{
    prev = iterator.prev;
    return *this;
}

template<typename Type>
inline SinglyLinkedList<Type>::Iterator& SinglyLinkedList<Type>::Iterator::operator=(const Iterator &iterator)
{
    return this->assign(iterator);
}

template<typename Type>
inline SinglyLinkedList<Type>::Node* SinglyLinkedList<Type>::Iterator::operator->() const
{
    return prev->next;
}

template<typename Type>
SinglyLinkedList<Type>::SinglyLinkedList()
: first(new Node()), rear(Iterator()), elementAmount(0) { }

template<typename Type>
SinglyLinkedList<Type>::SinglyLinkedList(const SinglyLinkedList &otherList)
: first(new Node()), elementAmount(otherList.elementAmount)
{
    Node *i = first;
    Node *j = otherList.first->next;
    while (j != nullptr)
    {
        i->next = new Node(j->data);
        i = i->next;
        j = j->next;
    }
    rear = new Iterator();
}

template<typename Type>
SinglyLinkedList<Type>::SinglyLinkedList(SinglyLinkedList &&otherList)
: first(otherList.first), rear(otherList.rear), elementAmount(otherList.elementAmount)
{
    otherList.first = new Node();
    otherList.rear = Iterator();
    otherList.elementAmount = 0;
}

template<typename Type>
SinglyLinkedList<Type>::~SinglyLinkedList()
{
    decltype(first) temp;
    while (first != nullptr)
    {
        temp = first;
        first = first->next;
        delete temp;
    }
}

template<typename Type>
inline Type& SinglyLinkedList<Type>::front() const
{
    return first->next->data;
}

template<typename Type>
inline Type& SinglyLinkedList<Type>::getFront() const
{
    return front();
}

template<typename Type>
inline Type& SinglyLinkedList<Type>::back() const
{
    return rear->data;
}

template<typename Type>
inline Type& SinglyLinkedList<Type>::getBack() const
{
    return back();
}

template<typename Type>
inline long long SinglyLinkedList<Type>::getSize() const
{
    return this->elementAmount;
}

template<typename Type>
inline long long SinglyLinkedList<Type>::size() const
{
    return this->elementAmount;
}

template<typename Type>
inline bool SinglyLinkedList<Type>::empty() const
{
    return 0 == this->elementAmount;
}

template<typename Type>
inline bool SinglyLinkedList<Type>::isEmpty() const
{
    return empty();
}

template<typename Type, typename... Args>
SinglyLinkedList<Type>::Iterator SinglyLinkedList<Type>::emplace(const Iterator &position, Args&&... args)
{
    return this->insert(position, std::forward<Args>(args));
    // Node *emplaced = new Node(std::forward<Args>(args), position->next);
    // Node *next = position->next;
}

template<typename Type, typename... Args>
Type& SinglyLinkedList<Type>::emplaceBack(Args&&... args)
{
    return *(this->insert(this->rear, std::forward<Args>(args)));
}

template<typename Type, typename... Args>
Type& SinglyLinkedList<Type>::emplaceFront(Args&&... args)
{
    return *(this->insert(this->first, std::forward<Args>(args)));
}




}   // end of namespace