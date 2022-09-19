
namespace LearningDataStruct
{
#include <initializer_list>
// #include <iterator>
// #include <functional>
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
public:
    class Iterator
    {
        private:
            Iterator();
            Iterator(Node *_prev);
            Iterator(const Iterator &it);
        public:
            Type& operator*();
            const Type& operator*() const;
            
            Iterator& operator++();
            const Iterator operator++(int);

            bool operator==(const Iterator &iterator) const;
            bool operator!=(const Iterator &iterator) const;

            Iterator& assign(const Iterator &iterator);
            Iterator& operator=(const Iterator &iterator);
        
            Node* operator->() const;
        private:
            Node *prev;
            // Node *curr;
    };      // end of Iterator

    // class ConstIterator
    // {
    //     Node *prev, *curr;
    // };

public:
    SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList &otherList);
    SinglyLinkedList(SinglyLinkedList &&otherList);
    ~SinglyLinkedList();

    Type& front() const;
    Type& getFront() const;
    Type& back() const;
    Type& getBack() const;
    long long getSize() const;
    long long size() const;
    bool empty() const;
    bool isEmpty() const;

    /**
     * @brief  Constructs object in %list before specified iterator.
     * @param position  A const_iterator into the %list.
     * @param args  Arguments.
     * @return  An iterator that points to the inserted data.
     */
    template<typename... Args>
    Iterator emplace(const Iterator &position, Args&&... args);
    template<typename... Args>
    Type& emplaceBack(Args&&... args);
    template<typename... Args>
    Iterator emplaceFront(Args&&... args);

    void pushBack(const Type &data);
    void pushFront(const Type &data);
    void operator<<(const Type &data);
    friend void operator>>(const Type &data, SinglyLinkedList<Type> &sll);

    void emplace(Type &&data);
    void emplaceBack(const Type &&data);
    void emplaceFront(const Type &&data);
    void pushBack(Type &&data);
    void pushFront(Type &&data);
    void operator<<(Type &&data);
    friend void operator>>(Type &&data, SinglyLinkedList<Type> &sll);

    void popBack();
    void popFront();

    /**
     * @param position, the begin position of inserting.
     * @brief Insert an element or a series of element behind the position.
     * @return An iterator points to the newly inserted position.
     */
    Iterator insert(const Iterator &position, std::initializer_list<Type> &il);
    Iterator insert(const Iterator &position, const Type &data);
    Iterator insert(const Iterator &position, Type &&data);
    Iterator insert(const Iterator &position, size_t n, const Type &data);
    Iterator insert(const Iterator &position, Iterator inputFirst, Iterator inputLast);

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

    void reverse();

    /**
     * @brief Delete the same continuous element
     */
    void unique();

    void sort(SortMode mode = SortMode.ASCEND);
    enum SortMode{ASCEND, DECEND};


    void clear();

    SinglyLinkedList& assign(const SinglyLinkedList &otherList);
    SinglyLinkedList& operator=(const SinglyLinkedList &otherList);
    SinglyLinkedList& assign(SinglyLinkedList &&otherList);
    SinglyLinkedList& operator=(SinglyLinkedList &&otherList);

    Iterator begin();
    Iterator end();

private:
    Node *first;
    Iterator rear;  // Node *rear;
    long long elementAmount;
};      // end of class SinglyLinkedList

}       // end of namespace

