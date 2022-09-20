
#include <initializer_list>
#include <bits/move.h>
#include <bits/c++config.h>

namespace LearningDataStruct
{
// #include <iterator>
// #include <functional>

using std::size_t;

template<typename Type>
class SinglyLinkedList
{
private:
    struct Node
    {
        Type data;
        Node *next;

        Node();
        Node(const Type &_data);
        Node(Type &&_data);
        Node(const Type &_data, const Node *_next);
        Node(Type &&_data, const Node *_next);
    };      // end of struct Node
private:
    class BasicIterator
    {
    private:
        BasicIterator();
        BasicIterator(const Node *_prev);
        BasicIterator(const BasicIterator &it);
    public:
        const Type& operator*() const;
        const Type* operator->() const;

        BasicIterator& operator++();
        const BasicIterator operator++(int);

        bool operator==(const BasicIterator &iterator) const;
        bool operator!=(const BasicIterator &iterator) const;

        BasicIterator& assign(const BasicIterator &iterator);
    private:
        Node *prev;
    };
public:
    class Iterator : public BasicIterator
    {
    private:
        Iterator();
        Iterator(const Node *_prev);
        Iterator(const Iterator &it);
        Iterator(const ConstIterator &it);
    public:
        Type& operator*();
        Type* operator->();

        // Iterator& operator=(const BasicIterator &iterator);
        Iterator& operator=(const Iterator &iterator);
        Iterator& operator=(const ConstIterator &iterator);
    // private:
        // Node *prev;
    };      // end of class Iterator

    class ConstIterator : public BasicIterator
    {
    private:
        ConstIterator();
        ConstIterator(const Node *_prev);
        ConstIterator(const Iterator &it);
        ConstIterator(const ConstIterator &it);
    public:
        ConstIterator& operator=(const Iterator &iterator);
        ConstIterator& operator=(const ConstIterator &iterator);
    };      // end of class ConstIterator

public:
    SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList &otherList);
    SinglyLinkedList(SinglyLinkedList &&otherList);
    ~SinglyLinkedList();

    Type& front() const;
    Type& getFront() const;
    Type& back() const;
    Type& getBack() const;
    size_t getSize() const;
    size_t size() const;
    bool empty() const;
    bool isEmpty() const;

    /**
     * @brief  Constructs object in %list before specified iterator.
     * @param position  A const_iterator into the %list.
     * @param args  Arguments.
     * @return  An iterator that points to the inserted data.
     */
    template<typename... Args>
    Iterator emplace(const Iterator &position, Args&&... args)
    {
        return this->insert(position, std::forward<Args>(args)...);
    }
    template<typename... Args>
    Type& emplaceBack(Args&&... args)
    {
        this->insert(rear, std::forward<Args>(args)...);
        return back();
    }
    template<typename... Args>
    Iterator emplaceFront(Args&&... args)
    {
        this->insert(first, std::forward<Args>(args)...);
    }

    /**
     * @brief push an element into the SinglyLinkedList object.
     */
    void pushBack(const Type &data);
    void pushFront(const Type &data);
    void operator<<(const Type &data);
    friend void operator>>(const Type &data, SinglyLinkedList<Type> &sll);

    // void emplace(Type &&data);
    // void emplaceBack(const Type &&data);
    // void emplaceFront(const Type &&data);
    void pushBack(Type &&data);
    void pushFront(Type &&data);
    void operator<<(Type &&data);
    friend void operator>>(Type &&data, SinglyLinkedList<Type> &sll);

    void popBack();
    void popFront();

    /**
     * @brief Insert an element or a series of element behind the position.
     * @param position, the begin position of inserting.
     * @return An iterator points to the newly inserted position.
     */
    Iterator insert(const Iterator &position, std::initializer_list<Type> &ilist);
    Iterator insert(const Iterator &position, const Type &data);
    Iterator insert(const Iterator &position, Type &&data);
    Iterator insert(const Iterator &position, size_t n, const Type &data);
    Iterator insert(const Iterator &position, Iterator inputFirst, Iterator inputLast);
private:
    Node* insert(const Node* &node, Type &&data);

public:
    Iterator begin();
    ConstIterator begin() const;
    Iterator getBegin();
    ConstIterator getBegin() const;
    Iterator end();
    ConstIterator end() const;
    Iterator getEnd();
    ConstIterator getEnd() const;

    void remove(const Type &value, RemoveMode=RemoveMode.FIRST);
    enum RemoveMode{FIRST, LAST, ALL};

    Iterator find(const Type &value, FindMode mode=FindMode.FIRST) const;
    enum FindMode {FIRST, LAST};

    Iterator count(const Type &value) const;

    void swap(SinglyLinkedList &sll);
    void swap(SinglyLinkedList &&sll);

    void erase(Iterator position);
    void erase(Iterator first, Iterator last);      // reserve the last;

    template<typename Compare = std::less<Type> >
    void merge(SinglyLinkedList &&otherList);
    template<typename Compare = std::less<Type> >
    void merge(SinglyLinkedList &otherList);

    void splice(const Iterator &position, SinglyLinkedList &otherList);
    void splice(const Iterator &position, SinglyLinkedList &&otherList);
    void splice(const Iterator &position, Iterator first);
    void splice(const Iterator &position, Iterator first, const Iterator &last);

    /**
     * @brief Reverse the SinglyLinkedList.
     */
    void reverse();

    /**
     * @brief Delete the same continuous element
     */
    void unique();

    /**
     * @brief Sort the SinglyLinkedList object ascendingly or decendingly.
     */
    void sort(SortMode mode = SortMode.ASCEND);
    enum SortMode{ASCEND, DECEND};      // 也许可以用merge那种形式。


    void clear();

    SinglyLinkedList& assign(const SinglyLinkedList &otherList);
    SinglyLinkedList& operator=(const SinglyLinkedList &otherList);
    SinglyLinkedList& assign(SinglyLinkedList &&otherList);
    SinglyLinkedList& operator=(SinglyLinkedList &&otherList);

private:
    Node *first;
    Iterator rear;  // Node *rear;
    size_t elementAmount;
};      // end of class SinglyLinkedList

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
SinglyLinkedList<Type>::Iterator::Iterator(const Node *_prev)
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
inline size_t SinglyLinkedList<Type>::getSize() const
{
    return this->elementAmount;
}

template<typename Type>
inline size_t SinglyLinkedList<Type>::size() const
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

// template<typename... Args>
// SinglyLinkedList<Args[0]>::Iterator emplace(const Iterator &position, Args&&... args+1)
// {

// }

// template<typename Type, typename... Args>
// inline SinglyLinkedList<Type>::Iterator SinglyLinkedList<Type>::emplace(const Iterator &position, Args&&... args)
// {
//     return this->insert(position, std::forward<Args>(args));
//     // Node *emplaced = new Node(std::forward<Args>(args), position->next);
//     // Node *next = position->next;
// }

// template<class Class, typename... Args>
// SinglyLinkedList<Class>::Iterator SinglyLinkedList<Class>::emplace(const SinglyLinkedList<Class>::Iterator &positoin, Args&&... args)
// {
    
// }

// template<typename Type, typename... Args>
// inline Type& SinglyLinkedList<Type>::emplaceBack(Args&&... args)
// {
//     return *(this->insert(this->rear, std::forward<Args>(args)...));
// }

// template<typename Type, typename... Args>
// Type& SinglyLinkedList<Type>::emplaceFront(Args&&... args)
// {
//     return *(this->insert(this->first, std::forward<Args>(args)...));
// }

}       // end of namespace

