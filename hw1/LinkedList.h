//
//  LinkedList.hpp
//  hw1
//
//  Created by 李心怡 on 7/8/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h
#include <string>
#include <stdio.h>

typedef std::string ItemType;

struct Node {
    ItemType value;
    Node *next;
};

class LinkedList {
    private:
        Node *head;
    public:
        //psuedocode style
        //NAME:
        //INPUT:
        //OUTPUT:
        //DESCRIPTION:
    
        // default constructor
        //NAME:LinkedList
        //INPUT: void
        //OUTPUT:void
        //DESCRIPTION: constructor for the linkedlist class
        LinkedList();
        // copy constructor
        //NAME:LinkedList
        //INPUT:reference of a linkedlist object rhs
        //OUTPUT:void
        //DESCRIPTION: This function copies the rhs linkedlist to this linkedlist
        LinkedList(const LinkedList& rhs);
        // Destroys all the dynamically allocated memory
        // in the list.
        //NAME:~LinkedList
        //INPUT: void
        //OUTPUT: void
        //DESCRIPTION: this function delete the dynamically allocated memory and serve
        // as a desctructor
        ~LinkedList();
        // assignment operator
        //NAME:operator=
        //INPUT:reference of a linkedlist rhs
        //OUTPUT: void
        //DESCRIPTION: copy the rhs linkedlist to this linkedlist that is already
        //initialized
        const LinkedList& operator=(const LinkedList& rhs);
        //NAME: insertToFront
        //INPUT:reference of a val that is used to put into the value of the node
        //OUTPUT: void
        //DESCRIPTION: this functoin insert a node containing val to the front of this linkedlist
        // Inserts val at the front of the list
        void insertToFront(const ItemType &val);
        // Prints the LinkedList
        //NAME: printList
        //INPUT: void
        //OUTPUT: void
        //DESCRIPTION: print the whole linkedlist
        void printList() const;
        // Sets item to the value at position i in this
        // LinkedList and return true, returns false if
        // there is no element i
        //NAME: get
        //INPUT: an interger that holds index number, and a reference to an target item
        //OUTPUT: if i exceed the length of list, return false, else after set the value, return true
        //DESCRIPTION: to check wether node i holds the value item.
        bool get(int i, ItemType& item) const;
        // Reverses the LinkedList
        //NAME:reverseList
        //INPUT: void
        //OUTPUT:void
        //DESCRIPTION: reverse the linkedlist
        void reverseList();
        // Prints the LinkedList in reverse order
        //NAME:printReverse
        //INPUT:void
        //OUTPUT:void
        //DESCRIPTION: print the list in reversed order but not changing the list
        void printReverse() const;
        // Appends the values of other onto the end of this
        // LinkedList.
        //NAME:append
        //INPUT:reference of a list called other
        //OUTPUT: void
        //DESCRIPTION:  append other list to this list
        void append(const LinkedList &other);
        // Exchange the contents of this LinkedList with the other
        // one.
        //NAME:swap
        //INPUT:reference to other
        //OUTPUT: void
        //DESCRIPTION: swap the content of this list with other list
        void swap(LinkedList &other);
        // Returns the number of items in the Linked List.
        //NAME:size
        //INPUT: void
        //OUTPUT: integer holds the size of this list
        //DESCRIPTION: get the size of the list
        int size() const;
};

#endif /* LinkedList_h */
