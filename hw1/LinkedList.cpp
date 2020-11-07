//
//  LinkedList.cpp
//  hw1
//
//  Created by 李心怡 on 7/8/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#include <iostream>
#include "LinkedList.h"

using namespace std;

// constructor
LinkedList::LinkedList(){
    // initialze a list with a nullptr
    head = nullptr;
}
// copy constructor
LinkedList::LinkedList(const LinkedList& rhs){
    // first initialize p to rhs's head, make new node called cp and change head to cp; then np is suppose to be next pointer of cp in the new cp list.
    // taverse thought rhs's nodes with pointer p
    //      copy rhs's value to cp
    //      make new node np for the next of cp
    //      link np to next of cp
    //      cp and np together;
    // at the end, add nullptr to cp. Now the rhs is fully copied to this list(cp/head);
    
    
    Node* p; // pointer refering to nodes of rhs's nodes
    Node* cp;// copy pointer from rhs, this is used for this linkedlist
    Node* np; // next pointer of cp
    cp = new Node;
    
    head = cp;
    p = rhs.head;
    while (p->next != nullptr){
        cp->value = p->value;
        np = new Node;
        cp->next = np;
        p = p->next;
        cp = cp->next;
    }
    cp->value = p->value;
    cp->next = nullptr;
}

// Destroys all the dynamically allocated memory
// in the list.
LinkedList::~LinkedList(){
    Node* p; // pointer that is used to traverse through the nodes

    p = head;
    while (p != nullptr){
        Node* tp = p->next;
        delete p;
        p = tp;
    }
}

// assignment operator
const LinkedList& LinkedList::operator=(const LinkedList& rhs)
{
    if (& rhs == this){ // check for aliasing
        return *this;
    }
    // Now delete the original allocated space first.
    // basically just the destructor;
    Node* dp; // delete_pointer that is used to traverse through the nodes
    Node* tp; // temperary pointer for p
    dp = head;
    while (dp != nullptr){
        tp = dp->next;
        delete dp;
        dp = tp;
    }
    
    // Now basically use the copy constructor to copy values from rhs;
    Node* p; // pointer refering to nodes of rhs's nodes
    Node* cp;// copy pointer from rhs, this is used for this linkedlist
    Node* np; // next pointer of cp
    cp = new Node;
    head = cp;
    p = rhs.head;
    while (p->next != nullptr){
        cp->value = p->value;
        np = new Node;
        cp->next = np;
        p = p->next;
        cp = cp->next;
    }
    cp->value = p->value;
    cp->next = nullptr;
    
    return *this;
}

// Inserts val at the front of the list
void LinkedList::insertToFront(const ItemType &val)
{
    // first allocate a new node
    // put the val into the new node
    // put the head to the next of the new node
    // change head to p
    Node* p = new Node;
    p->value = val;
    p->next = head;
    head = p;
    //printList();
}

// Prints the LinkedList
void LinkedList::printList() const
{
    // use p to traverse through the list and each step print the value out;
    Node* p;
    p = head;
    while(p != nullptr){
        cout << p->value << " ";
        p = p->next;
    }
    cout << endl;
}


// Sets item to the value at position i in this
// LinkedList and return true, returns false if
// there is no element i
bool LinkedList::get(int i, ItemType& item) const
{
    //first use p to get this list's head
    // traverse to the item i;
    // if i too big return false; otherwise change that p's value to item and return true
    Node* p;
    p = head;
    for (int j = 0; j < i; j++){
        // the 1st element is j = 0;
        p = p->next;
    }
    if (p == nullptr){
        return false;
    }
    else{
        item = p->value;
        return true;
    }
}

// Reverses the LinkedList
void LinkedList::reverseList()
{
    //Use pointer p to traverse this list
    // take p's node and put it to another list rp's head
    // go to next p
    // take p's node and put it in the front of rp
    // go to next p ...
    
    Node* p; // traverse pointer
    p = head;
    Node* rp; // reversed linked list pointer
    Node* rp_temp;
    rp = new Node;
    rp->value = p->value;
    rp->next = nullptr;
    while (p->next != nullptr){
        p = p->next;
        // copy the p's item in this linkedlist to rp using insertToFront;
        rp_temp = rp;
        rp = new Node;
        rp->value = p->value;
        rp->next = rp_temp;
    }
    p = head;
    while (p != nullptr){
        Node* tp = p->next;
        delete p;
        p = tp;
    }
    this->head = rp;
    
}

// Prints the LinkedList in reverse order
void LinkedList::printReverse() const
{
    // basically use the reverseList() method to just print out the reversed list
    // and not change original head
    Node* p; // traverse pointer
    p = head;
    Node* rp; // reversed linked list pointer
    Node* rp_temp;
    rp = new Node;
    rp->value = p->value;
    rp->next = nullptr;
    while (p->next != nullptr && p != nullptr){
        p = p->next;
        // copy the p's item in this linkedlist to rp using insertToFront;
        rp_temp = rp;
        rp = new Node;
        rp->value = p->value;
        rp->next = rp_temp;
    }
    // use logic in printList() to print out the reversed list;
    Node* rhead = rp;
    while (rp != nullptr){
        cout << rp->value << " ";
        rp = rp->next;
    }
    cout << endl;
    rp = rhead;
    while (rp != nullptr){
        Node* tp = p->next;
        delete p;
        p = tp;
    }
}

// Appends the values of other onto the end of this
// LinkedList.
void LinkedList::append(const LinkedList &other)
{
    //first traverse to the end of this list
    //then copy each node from the "other" list
    // add nullptr at the end
    
    Node* p;
    p = head;
    Node* op; // other's pointer;
    op = other.head;
    Node* np; // next pointer after p;
    if (p != nullptr){
        while(p->next != nullptr){
            p = p->next;
        }
    }
    
    
    while (op != nullptr){
        np = new Node; // this np is used for copying the other's values;
        np->value = op->value;
        if (p == nullptr){
            p = np;
            head = np;
        }
        else{
            p->next = np;
        }
        op = op->next;
        p = np;
    }
    p->next = nullptr;
    
}

// Exchange the contents of this LinkedList with the other
// one.
void LinkedList::swap(LinkedList &other)
{
    // put this list's head in a temp
    // put other's head in this head
    // last put temp in the other's head
    Node* temp;
    temp = head;
    head = other.head;
    other.head = temp;
}

int LinkedList::size() const
{
    // use a count integer to count the total items
    int count = 0;
    Node* p;
    p = head;

    while(p != nullptr){
        count++;
        p = p->next;
    }
    return count;
}
