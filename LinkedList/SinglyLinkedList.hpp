
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

        Node() : next(nullptr) { }
        Node(const Type &_data) : data(_data), next(nullptr) { }
        Node(Type &&_data) : data(_data), next(nullptr) { }
        Node(const Type &_data, const Node *_next) : data(_data), next(_next) { }
        Node(Type &&_data, const Node *_next) : data(_data), next(_next) { }
    };      // end of struct Node
public:
    class ConstIterator
    {
    private:     // 私有类的共有构造
        ConstIterator() : prev(first) { }
        ConstIterator(const Node *_prev) : prev(_prev) { }
        ConstIterator(const ConstIterator &it) : prev(it.prev) { }: prev(it.prev) { }
    public:
        const Type& operator*() const
        {
            return prev->next->data;
        }
        const Type* operator->() const
        {
            return &(prev->next->data);
        }

        ConstIterator& operator++()       
        {
            this->prev = this->prev->next;
            return *this;
        }
        const ConstIterator operator++(int)
        {
            decltype(*this) old = BasicIterator(*this);
            ++*this;
            return old;
        }

        bool operator==(const ConstIterator &iterator) const
        {
            return this->prev->next == iterator.prev->next;
        }
        bool operator!=(const ConstIterator &iterator) const
        {
            return !(*this != iterator);
        }

        ConstIterator& assign(const ConstIterator &iterator)
        {
            this->prev = iterator->prev;
            return *this;
        }
        ConstIterator& operator=(const ConstIterator &iterator) {
            return this->assign(iterator);
        }

    protected:
        Node *prev;
    };
public:
    class Iterator : public ConstIterator
    {
    private:
        Iterator() : prev(first) { }
        Iterator(const Node *_prev) : prev(_prev) { }
        Iterator(const ConstIterator &it) : prev(it.prev) { }
        // Iterator(const Iterator &it) : prev(it.prev) { }
    public:
        Type& operator*() 
        {
            return prev->next->data;
        }
        Type* operator->()
        {
            return &(prev->next->data);
        }

        Iterator& assign(const Iterator &iterator)
        {
            this->prev = iterator->prev;
            return *this;
        }
        Iterator& operator=(const Iterator &iterator)
        {
            return this->assign(iterator);
        }
        Iterator& operator=(const ConstIterator &iterator)
        {
            this->prev = iterator.prev;
            return *this;
        }

        Iterator next()
        {
            return Iterator(this->prev->next);
        }

        Iterator insert(const Type &data)
        {
            insert(this->prev->next, data);
            if (this->prev->next == rear)
                rear = rear->next;
            return Iterator(this->prev->next);
        }
        Iterator insert(Type &&data)
        {
            insert(this->prev->next, data);
            if (this->prev->next == rear)
                rear = rear->next;
            return Iterator(this->prev->next);
        }
    };
    
public:
    SinglyLinkedList() : first(new Node()), rear(first), elementAmount(0) { }
    SinglyLinkedList(const SinglyLinkedList &otherList);
    // : first(new Node()), elementAmount(otherList.elementAmount)
    // {
    //     Node *i = first;
    //     Node *j = otherList.first->next;
    //     while (j != nullptr)
    //     {
    //         i->next = new Node(j->data);
    //         i = i->next;
    //         j = j->next;
    //     }
    //     rear = new Iterator();
    // }
    SinglyLinkedList(SinglyLinkedList &&otherList) = default;
    ~SinglyLinkedList()
    {
        this->clear();
        delete first;
    }


    Type& front() const
    {return first->next->data;}
    Type& getFront() const
    {return this->front();}
    Type& back() const
    {return *rear;}
    Type& getBack() const
    {return this->back();}
    size_t size() const
    {return this->elementAmount;}
    size_t getSize() const
    {return this->back();}
    bool empty() const
    {return (0 == this->elementAmount);}
    bool isEmpty() const
    {return this->empty();}

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
    void pushBack(const Type &data)
    {
        this->insert(this->rear, data);
    }
    void pushFront(const Type &data)
    {
        this->insert(this->first, data);
    }
    SinglyLinkedList& operator<<(const Type &data)
    {
        this->pushBack(data);
        return *this;
    }
    friend void operator>>(const Type &data, SinglyLinkedList<Type> &sll)
    {this->pushFront(data);}

    void pushBack(Type &&data)
    {
        this->insert(this->rear, data);
    }
    void pushFront(Type &&data)
    {this->insert(this->first, data);}
    SinglyLinkedList& operator<<(Type &&data)
    {
        this->pushBack(data);
        return *this;
    }
    friend void operator>>(Type &&data, SinglyLinkedList<Type> &sll)
    {this->pushFront(data);}

    void popBack()
    {
        Node *it = first;
        while (it->next != rear)
        {it = it->next;}
        delete rear;
        while 
        
    }
    void popFront()
    {
        Node *newFront = first->next->next;
        delete first->next;
        first->next = newFront;
    }

    /**
     * @brief Insert an element or a series of element behind the position.
     * @param position, the begin position of inserting.
     * @return An iterator points to the head of the newly inserted position.
     */
    // Iterator insert(const Iterator &position, std::initializer_list<Type> &ilist)
    // {
    //     this->insert(Iterator)
    //     return ++Iterator(position);
    // }
    Iterator insert(const Iterator &position, const Type &data)
    {return position.insert(data);}
    Iterator insert(const Iterator &position, Type &&data)
    {return position.insert(data);}
    Iterator insert(const Iterator &position, size_t n, const Type &data)
    {
        while (n--)
            position.insert(data);
        return position.next();
    }
    Iterator insert(const Iterator &position, Iterator inputBegin, Iterator inputEnd)
    {
        Iterator it(position);
        while (inputBegin != inputEnd)
        {
            it = it.insert(*inputBegin);
            ++inputBegin;
        }
        return position.next();
    }
private:
    Node* insert(Node* node, const Type &data)
    {
        Node *newNode = new Node(data, node->next);
        if (node == rear) rear = rear->next;
        return (node->next = newNode);
    }
    Node* insert(Node* node, Type &&data)
    {
        Node *newNode = new Node(data, node->next);
        if (node == rear) rear = rear->next;
        return (node->next = newNode);
    }

public:
    Iterator begin()
    {return Iterator(first);}
    ConstIterator begin() const
    {return ConstIterator(first);}
    Iterator getBegin()
    {return begin();}
    ConstIterator getBegin() const
    {return begin();}
    Iterator end()
    {return Iterator(rear);}
    ConstIterator end() const;
    Iterator getEnd();
    ConstIterator getEnd() const;

    enum RemoveMode{FIRST, LAST, ALL};
    void remove(const Type &value, RemoveMode=RemoveMode.FIRST);
    int removeFirst(const Type &value);
    int removeLast(const Type &value);
    int removeAll(const Type &value);

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
    void defineSort(boolean *(cmp)(const Type &obj0, const Type &obj1));

    void rotate(int k);


    void clear();

    SinglyLinkedList& assign(const SinglyLinkedList &otherList);
    SinglyLinkedList& operator=(const SinglyLinkedList &otherList);
    SinglyLinkedList& assign(SinglyLinkedList &&otherList);
    SinglyLinkedList& operator=(SinglyLinkedList &&otherList);

private:
    Node *first;
    // Iterator rear;
    Node *rear;
    size_t elementAmount;
};      // end of class SinglyLinkedList




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

