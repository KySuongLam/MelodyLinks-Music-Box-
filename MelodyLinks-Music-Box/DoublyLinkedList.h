#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST
#include "OutOfRangeExcept.h"
#include "Song.h"

/*
    Author: Ky Lam
    Date: October 29, 2023
    Description: Implement a template-based doubly linked list 
    that offers essential operations for efficient data management. 
    This list allows you to add items to the end, remove specific elements, 
    check the current size, retrieve items at a given index, 
    verify item existence, and replace elements.
*/

template <class T>
struct Node
{
    T data;
    Node<T>* next;
    Node<T>* previous;

    Node(const T& item, Node<T>* n = nullptr, Node<T>* p = nullptr) : data(item), next(n), previous(p) 
    {}
};


template <class T>
class DoublyLinkedList
{
    private:
        Node<T>* head;      // Pointer to the head (start) of the list.
        Node<T>* tail;      // Pointer to the tail (last) of the list.
        int count;          // Number of items in the list.

    public:
        // Constructor: Initializes an empty list.
        DoublyLinkedList();

        // Copy constructor: Creates a new DoublyLinkedList as a copy of another DoublyLinkedList.
        DoublyLinkedList(const DoublyLinkedList<T>& other);

        // Assignment operator: Assigns the contents of another DoublyLinkedList to this one.
        DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);

        // Add an item to the end of the list.
        void push_back(const T& newItem);

        // Remove an item from list.
        bool remove(const T& removeItem);

        // Get the current size of the list.
        int getSize() const;

        // Get an item at a given position.
        T at (int position) const;

        // Check if the item is on the list.
        bool contains (const T& checkItem) const;

        // Replace an item at a given position with a new item.
        T replace(int position, const T& newItem);

        // Destructor: Cleans up the list by removing all items.
        ~DoublyLinkedList();

        // Helper methods: These allow external code to retrieve these pointers (head and tail). 
        Node<T>* getHead() const 
        {
            return head;
        }
        Node<T>* getTail() const 
        {
            return tail;
        }

};

// Constructor
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(): head(nullptr), tail(nullptr), count(0)
{
}

// Copy Constructor
// Parameters:
//     - other: the other DoublyLinkedList is copied.
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other): head(nullptr), tail(nullptr), count(0)
{
    Node<T>* curr = other.head;
    while (curr != nullptr)
    {
        push_back(curr->data);
        curr = curr->next;
    }
}

// Assignment Operator
// Parameters:
//     - other: the other DoublyLinkedList is copied.
// Returns: the new DoublyLinkedList after copy from the other.
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
    if (this == &other)
    {
        return *this;
    }
    
   //Clean the current list
    Node<T>* curr = head;
    while (curr != nullptr)  
    {
        Node<T>* temp = curr->next;
        delete curr;
        curr = temp;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;

    // Copy items from other list to this list
    Node<T>* otherCurr = other.head;
    while (otherCurr != nullptr) 
    {
        push_back(otherCurr->data);
        otherCurr = otherCurr -> next;
    }

    return *this;
}


// Add an item to the end of the list.
// Parameters:
//   - newItem: The item to be added.
template <class T>
void DoublyLinkedList<T>::push_back (const T& newItem)
{
    Node<T>* newNode = new Node<T>(newItem, nullptr, nullptr);

    if(head == nullptr) //If the list is empty
    {
        head = newNode;
        tail = newNode;
    }
    else //If the list is not empty
    {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    count++;
}

// Remove an given item from the list.
// Parameters:
//   - removeItem: The item to remove.
// Returns: True if the removal is successful, false otherwise.
template <class T>
bool DoublyLinkedList<T>::remove(const T& removeItem)
{
    Node<T>* curr = head;
    while (curr != nullptr)
    {
        if(curr->data == removeItem)
        {
            if(curr == head && curr == tail)
            {
                head = tail = nullptr;
            }
            else if(curr == head)
            {
                head = curr->next;
                head->previous = nullptr;

            }
            else if(curr == tail)
            {
                tail = curr->previous;
                tail->next = nullptr;
            }
            else
            {
                curr->previous->next = curr->next;
                curr->next->previous = curr->previous;
            }

            delete curr;
            curr = nullptr;
            count--;
            return true;
        }

        curr = curr->next;
    }
    return false;
}

// Get the number of items in the list.
template <class T>
int DoublyLinkedList<T>::getSize() const
{
    return count;
}

// Get an item at a given position.
// Parameters:
//   - position: The position of the item to retrieve (1-based).
// Returns: The item at the specified position.
// Throws: OutOfRangeExcept if the position is out of bounds.
template <class T>
T DoublyLinkedList<T>::at (int position) const
{
    if(position > 0 && position <= count)
    {
        Node<T>* curr = head;
        for (int i = 1; i < position; i++)
        {
            curr = curr->next;
        }

        return curr->data;
    }
    else
    {
        throw OutOfRangeExcept();
    }
}

// Check if the item is on the list.
// Parameters:
//   - checkItem: The item needs to be checked.
// Returns: True if the item is on the list, false otherwise.
template <class T>
bool DoublyLinkedList<T>::contains (const T& checkItem) const
{
    Node<T>* curr = head;
    while (curr != nullptr)
    {
        if(curr->data == checkItem)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Replace an item at a given position with a new item.
// Parameters:
//   - position: The position of the item to replace (1-based).
//   - newItem: The new item to replace the old one.
// Returns: The old element that was replaced.
// Throws: OutOfRangeExcept if the position is out of bounds.
template <class T>
T DoublyLinkedList<T>::replace(int position, const T& newItem)
{
    if (position > 0 && position <= count)
    {
        Node<T>* curr = head;
        for (int i = 1; i < position; i++)
        {
            curr = curr->next;
        }
        T oldEntry = curr->data;
        curr->data = newItem;
        return oldEntry;
    }
    else
    {
        throw OutOfRangeExcept();
    }
}

// Destructor
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    Node<T>* curr = head;
    while (curr != nullptr) 
    {
        Node<T>* temp = curr->next;
        delete curr;
        curr = temp;
    }
    
    head = tail = nullptr;
    count = 0;
}

#endif