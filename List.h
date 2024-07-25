#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <string>
#include <sstream>
#include <utility>
#include <cstddef> //NULL


template <typename T>
class List {
    //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

    // List<T>() {
    //     first = nullptr;
    //     last = nullptr;
    //     num_element = 0;
    // }

    // ~List<T>() {
    //     delete first;
    //     delete last;
    // }

    List();
    List(const List& other);
    ~List();
    List& operator=
        (const List& rhs);

    //EFFECTS:  returns true if the list is empty
    bool empty() const;

    //EFFECTS: returns the number of elements in this List
    //HINT:    Traversing a list is really slow.  Instead, keep track of the size
    //         with a private member variable.  That's how std::list does it.
    int size() const;

    //REQUIRES: list is not empty
    //EFFECTS: Returns the first element in the list by reference
    T& front();

    //REQUIRES: list is not empty
    //EFFECTS: Returns the last element in the list by reference
    T& back();

    //EFFECTS:  inserts datum into the front of the list
    void push_front(
        const T& datum);

    //EFFECTS:  inserts datum into the back of the list
    void push_back(
        const T& datum);

    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the front of the list
    void pop_front();

    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the back of the list
    void pop_back();

    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes all items from the list
    void clear();

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Lists

private:
    //a private type
    struct Node {
        Node* next;
        Node* prev;
        T datum;
    };

    //REQUIRES: list is empty
    //EFFECTS:  copies all nodes from other to this
    void copy_all(
        const List<T>& other);

    Node* first;   // points to first Node in list, or nullptr if list is empty
    Node* last;    // points to last Node in list, or nullptr if list is empty
    int num_element;

public:
    ////////////////////////////////////////
    class Iterator {
        //OVERVIEW: Iterator interface to List

        // You should add in a default constructor, destructor, copy constructor,
        // and overloaded assignment operator, if appropriate. If these operations
        // will work correctly without defining these, you can omit them. A user
        // of the class must be able to create, copy, assign, and destroy Iterators.

        // Your iterator should implement the following public operators: *,
        // ++ (prefix), default constructor, == and !=.


    public:

        // This operator will be used to test your code. Do not modify it.
        // Requires that the current element is dereferenceable.
        Iterator& operator--() {
            assert(node_ptr);
            node_ptr = node_ptr->prev;
            return *this;
        }
        // above do not edit

        Iterator() : 
            node_ptr(nullptr) {}

        T& operator*() const {
            assert(node_ptr);  // check whether this is a past-the-end iterator
            return node_ptr->datum;
        }

        Iterator& operator++() {
            assert(node_ptr);  // check whether this is a past-the-end iterator
            node_ptr 
                = node_ptr->next;
            return *this;
        }

        bool operator==(
            List<T>::Iterator i) 
            const {
            return node_ptr 
                == i.node_ptr;
        }

        bool operator!=(
            List<T>::Iterator i) 
            const {
            return node_ptr 
                != i.node_ptr;
        }

    private:
        Node* node_ptr; //current Iterator position is a List node

        // add any additional necessary member variables here

        // add any friend declarations here
        friend class List;

        // construct an Iterator at a specific position
        Iterator(Node* p) 
            : node_ptr(p) {}

    };//List::Iterator
    ////////////////////////////////////////

    // return an Iterator pointing to the first element
    Iterator begin() const {
        return Iterator(first);
    }

    // return an Iterator pointing to "past the end"
    Iterator end() const {
        return Iterator();
    }

    //REQUIRES: i is a valid, dereferenceable iterator associated with this list
    //MODIFIES: may invalidate other list iterators
    //EFFECTS: Removes a single element from the list container
    void erase(Iterator i) {
        assert(!empty());
        Node* currentNode 
            = i.node_ptr;
        num_element--;
        if (currentNode 
                == first) {
            pop_front();
            i.node_ptr = first;
        }
        else if (currentNode 
                == last) {
            pop_back();
            i.node_ptr = last;
        }
        else {
            currentNode->prev->next 
                = currentNode->next;
            currentNode->next->prev 
                = currentNode->prev;
            delete currentNode;
        }

    }


    //REQUIRES: i is a valid iterator associated with this list
    //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i,
        const T& datum) {

        Node* currentNode 
            = new Node();

        if (i == Iterator(first)) {
            push_front(datum);
            delete currentNode;
        }
        else if (i == Iterator(last)) {
            push_back(datum);
            delete currentNode;
        }
        else {
            currentNode->next = i.node_ptr;
            i.node_ptr->prev->next = currentNode;
            currentNode->prev = i.node_ptr->prev;
            i.node_ptr->prev = currentNode;
            currentNode->datum = datum;
        }
        ++num_element;
    }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

// constructor, copy constructor, and destructor
template <typename T>
List<T>::List() : 
    first(nullptr), 
    last(nullptr), 
    num_element(0) {}

template <typename T>
List<T>:: ~List() {
    clear();
}

template <typename T>
List<T>::List(const List& other) : 
    first(nullptr), 
    last(nullptr) {
    num_element = 0;
    copy_all(other);
}

template <typename T>
List<T>& List<T>::operator= (const List& rhs) {
    if (this == &rhs) {
        return *this;
    }
    clear();
    copy_all(rhs);
    return *this;
}

// functions
template<typename T>
bool List<T>::empty() const {
    return num_element == 0;
}

template<typename T>
int List<T>::size() const {
    return num_element;
}

template<typename T>
T& List<T>::front() {
    return first->datum;
}

template<typename T>
T& List<T>::back() {
    return last->datum;
}

template<typename T>
void List<T>::push_front(
    const T& datum) {
    Node* addNode = new Node;
    addNode->datum = datum;
    addNode->prev = nullptr;
    addNode->next = nullptr;
    if (empty()) {
        first = last = addNode;
    }
    else {
        addNode->next = first;
        first->prev = addNode;
        first = addNode;
    }
    ++num_element;

}

template<typename T>
void List<T>::push_back(
    const T& datum) {
    Node* addNode = new Node;
    addNode->datum = datum;
    addNode->prev = nullptr;
    addNode->next = nullptr;
    if (empty()) {
        first = last = addNode;
    }
    else {
        addNode->prev = last;
        last->next = addNode;
        last = addNode;
    }
    ++num_element;
}

template<typename T>
void List<T>::pop_front() {
    assert(!empty());

    Node* item = first;
    first = first->next;
    if (first == nullptr) {
        last = nullptr;
    }
    else {
        first->prev = nullptr;
    }
    delete item;
    --num_element;
}

template<typename T>
void List<T>::pop_back() {
    assert(!empty());

    Node* item = last;
    last = last->prev;
    if (last == nullptr) {
        first = nullptr;
    }
    else {
        last->next = nullptr;
    }
    delete item;
    --num_element;
}

template<typename T>
void List<T>::clear() {
    num_element = 0;
    Node* temp = first;
    while (first != nullptr) {
        temp = first;
        first = first->next;
        delete temp;
    }
}

template<typename T>
void List<T>::copy_all(
    const List<T>& other) {
    for (Node* thisNode = 
        other.first; 
        thisNode != 0; 
        thisNode = 
            thisNode->next) {
        push_back(thisNode->datum);
    }
}
#endif // Do not remove this. Write all your code above this line.
