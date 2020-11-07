//
//  BirthdayParty.cpp
//  BirthdayParty
//
//  Created by 李心怡 on 7/14/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#include <stdio.h>
#include "BirthdayParty.h"
#include <string>
#include <iostream>
using namespace std;

BirthdayParty::BirthdayParty(){
    head = nullptr;
    tail = nullptr;
}

bool BirthdayParty::noInvitees() const{
    //if empty return true
    if (head == nullptr && tail == nullptr){
        return true;
    }
    else{
        return false;
    }
}
// destructor
BirthdayParty::~BirthdayParty(){
    Node* p = head;
    
    while (p != nullptr){
        Node* tp = p->next;
        delete p;
        p = tp;
    }
}

// copy constructor
BirthdayParty::BirthdayParty(const BirthdayParty& rhs){
    Node* p; // pointer refering to nodes of rhs's nodes
    Node* cp;// copy pointer from rhs, this is used for this linkedlist
    Node* np; // next pointer of cp;
    Node* pp; // prev pointer of cp;
    
    
    p = rhs.head;
    
    if (p == nullptr){
        cp = nullptr;
        head = cp;
        tail = cp;
    }
    else{
        cp = new Node;
        head = cp;
        pp = nullptr;
        while (p->next != nullptr){
            cp->first = p->first;
            cp->last = p->last;
            cp->value = p->value;
            np = new Node;
            cp->next = np;
            cp->prev = pp;
            p = p->next;
            pp = cp;
            cp = cp->next;
        }
        cp->first = p->first;
        cp->last = p->last;
        cp->value = p->value;
        cp->prev = pp;
        cp->next = nullptr;
    }
    
}

// assignment operartor
const BirthdayParty& BirthdayParty::operator=(const BirthdayParty& rhs){
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
    Node* p; // pointer refering to nodes of rhs's nodes
    Node* cp;// copy pointer from rhs, this is used for this linkedlist
    Node* np; // next pointer of cp;
    Node* pp; // prev pointer of cp;
    
    
    p = rhs.head;
    
    if (p == nullptr){
        cp = nullptr;
        head = cp;
        tail = cp;
        return *this;
    }
    else{
        cp = new Node;
        head = cp;
        pp = nullptr;
        while (p->next != nullptr){
            cp->first = p->first;
            cp->last = p->last;
            cp->value = p->value;
            np = new Node;
            cp->next = np;
            cp->prev = pp;
            p = p->next;
            pp = cp;
            cp = cp->next;
        }
        cp->first = p->first;
        cp->last = p->last;
        cp->value = p->value;
        cp->prev = pp;
        cp->next = nullptr;
        return *this;
    }
}

int BirthdayParty::whosOnTheGuestList() const
{
    Node* p = head;
    int count = 0;
    while(p != nullptr){
        count++;
        p = p->next;
    }
    return count;
}
// Return the number of players
//in
// the BirthdayParty list.

bool BirthdayParty::addInvitee(const string& firstName, const string&
                lastName, const BirthdayType& value)
{
    // insert to front if empty list;
    Node* p;
    Node* np;
    if (whosOnTheGuestList() == 0){
        p = new Node;
        p->first = firstName;
        p->last = lastName;
        p->value = value;
        p->prev = nullptr;
        p->next = head;
        head = p;
        return true;
    }
    else{
        p = head;
        while(p != nullptr){
            if (lastName == p->last){
                if (firstName == p->first){
                    return false;
                }
                else if (firstName < p->first){
                    //put this person before p
                    np = new Node;
                    np->first = firstName;
                    np->last = lastName;
                    np->value = value;
                    np->prev = p->prev;
                    np->next = p;
                    if(p->prev != nullptr){
                        p->prev->next = np;
                    }
                    else{
                        head = np;
                    }
                    p->prev = np;
                    return true;
                }
                else{
                    // p goto next node;
                    // make need more; maybe another check;
                    //if p->next = null;
                    if (p->next != nullptr){
                        p = p->next;
                    }
                    else{
                        // insert after the last node of the list, @p is the last node
                        np = new Node;
                        np->first = firstName;
                        np->last = lastName;
                        np->value = value;
                        np->prev = p;
                        np->next = p->next;
                        p->next = np;
                        tail = np;
                        return true;
                    }
                    
                }
            }
            else if (lastName < p->last){
                // add this person before p;
                
                np = new Node;
                np->first = firstName;
                np->last = lastName;
                np->value = value;
                np->prev = p->prev;
                np->next = p;
                if(p->prev != nullptr){
                    p->prev->next = np;
                }
                else{
                    head = np;
                }
                p->prev = np;

                return true;
            }
            else{
                if (p->next != nullptr){
                    p = p->next;
                }
                else{
                    // insert after the last node of the list, @p is the last node
                    np = new Node;
                    np->first = firstName;
                    np->last = lastName;
                    np->value = value;
                    np->prev = p;
                    np->next = p->next;
                    p->next = np;
                    tail = np;
                    
                    return true;
                }
            }
        }
    }
    return false;
}
// If the full name (both the first and last name) is not equal
// to any full name currently in the list then add it and return
// true. Elements should be added according to their last name.
// Elements with the same last name should be added according to
// their first names. Otherwise, make no change to the list and
// return false (indicating that the name is already in the
// list).

bool BirthdayParty::modifyInvitee(const string& firstName, const string& lastName, const BirthdayType& value)
{
    Node* p = head;
    if (head == nullptr) return false;
    while(p != nullptr){
        if (p->first == firstName && p->last == lastName){
            //copy the value to this node
            p->value = value;
            return true;
        }
        else p = p->next;
    }
    return false;
}
// If the full name is equal to a full name currently in the
// list, then make that full name no longer map to the value it
// currently maps to, but instead map to the value of the third
// parameter; return true in this case. Otherwise, make no
// change to the list and return false.

bool BirthdayParty::addOrModify(const string& firstName, const string& lastName, const BirthdayType& value)
{
    Node* p = head;
    if (head == nullptr) {
        addInvitee(firstName, lastName, value);
        return true;
    }
    //int checksame = 0;
    while (p != nullptr){
        if (firstName == p->first && lastName == p->last){
            //checksame = 1;
            modifyInvitee(firstName, lastName, value);
            return true;
        }
        else{
            p = p->next;
        }
    }

    addInvitee(firstName, lastName, value);
    return true;

}
// If full name is equal to a name currently in the list, then
// make that full name no longer map to the value it currently
// maps to, but instead map to the value of the third parameter;
// return true in this case. If the full name is not equal to
// any full name currently in the list then add it and return
// true. In fact, this function always returns true.

bool BirthdayParty::dropFromGuestList(const string& firstName, const string& lastName)
{
    Node* p = head;
    
    while (p != nullptr){
        if (firstName == p->first && lastName == p->last){
            // delete this node
            if (p->prev == nullptr && p->next == nullptr){
                head = nullptr;
                tail = nullptr;
                delete p;
                return true;
            }
            else if (p->prev == nullptr){
                head = p->next;
                head->prev = nullptr;
                delete p;
                return true;
            }
            else if (p->next == nullptr){
                tail = p->prev;
                tail->next = nullptr;
                delete p;
                return true;
            }
            else{
                p->next->prev  = p->prev;
                p->prev->next = p->next;
                delete p;
                return true;
            }
        }
        else{
            p = p->next;
        }
    }
    return false;
}
// If the full name is equal to a full name currently in the
// list, remove the full name and value from the list and return
// true. Otherwise, make no change to the list and return
// false.

bool BirthdayParty::personOnGuestList(const string& firstName, const string& lastName) const
{
    Node* p = head;
    while (p != nullptr){
        if (firstName == p->first && lastName == p->last){
            return true;
        }
        p = p->next;
    }
    return false;
}
// Return true if the full name is equal to a full name
// currently in the list, otherwise false.

bool BirthdayParty::checkGuestList(const string& firstName, const
                    string& lastName, BirthdayType& value) const
{
    Node* p = head;
    if (head == nullptr) return false;
    while(p != nullptr){
        if (p->first == firstName && p->last == lastName){
            //copy the value to this node
            if (value != p->value){
                value = p->value;
                return true;
            }
            else{
                return false;
            }
        }
        p = p->next;
    }
    return false;
}
// If the full name is equal to a full name currently in the
// list, set value to the value in the list that that full name
// maps to, and return true. Otherwise, make no change to the
// value parameter of this function and return false.

bool BirthdayParty::selectInvitee(int i, string& firstName, string& lastName, BirthdayType& value) const
{
    Node* p = head;
    if (i < 0 && i >= whosOnTheGuestList()) {
        return false;
    }
    else{
        for (int j = 0; j < i; j++){
            p = p->next;
        }
    }
    // copy the node's info to parameters
    firstName = p->first;
    lastName = p->last;
    value = p->value;
    return true;
}
// If 0 <= i < size(), copy into firstName, lastName and value
// parameters the corresponding information of the element at
// position i in the list and return true. Otherwise, leave the
// parameters unchanged and return false. (See below for details
// about this function.)

void BirthdayParty::changeGuestList(BirthdayParty& other)
{
    Node* temph;
    Node* tempt;
    temph = head;
    tempt = tail;
    head = other.head;
    tail = other.tail;
    other.head = temph;
    other.tail = tempt;
    
}
// Exchange the contents of this list with the other one.

bool combineGuestLists(const BirthdayParty & bpOne, const BirthdayParty & bpTwo, BirthdayParty & bpJoined)
{
    //can't access bp's private data, eg. bpOne->head;
    // if bpJoined is not empty, let's delete it first
    int result = 0;
    
    if (bpJoined.whosOnTheGuestList() > 0 &&  &bpOne != &bpJoined && &bpTwo != &bpJoined){
        int count = bpJoined.whosOnTheGuestList();
        for (int n = 0; n < count; n++)
            {
                string first;
                string last;
                BirthdayType val;
                bpJoined.selectInvitee (0, first, last, val);
                bpJoined.dropFromGuestList(first, last);
        }
    }
    
    if (&bpOne == &bpJoined || ( &bpOne != &bpJoined && &bpTwo != &bpJoined )){
    // if bpjoin is bpone or bpjoin is itself.
        
    // copy bpOne to bpJoined
        bpJoined = bpOne;
        int count_b2 = bpTwo.whosOnTheGuestList();
        for (int i = 0; i < count_b2; i++){
            string f2;
            string l2;
            BirthdayType val2; // this is a holder for the value of nodes in val2.
            bpTwo.selectInvitee(i, f2, l2, val2);
            if (bpJoined.personOnGuestList(f2, l2)){//person on the list
                if (bpJoined.checkGuestList(f2, l2, val2)) // val2 is changed when true. means  values of these two nodes are not same, so delete the node from bpjoined.
                {
                    bpJoined.dropFromGuestList(f2, l2);
                    result++;
                }
                // else if vals are different, just do nothing;
        
            }
            else{ // person not on the list, then add the b2 person to bpjoined
                bpJoined.addInvitee(f2, l2, val2);
            }
        
        }
    }
    else if (&bpTwo == &bpJoined){
        bpJoined = bpTwo;
        int count_b2 = bpOne.whosOnTheGuestList();
        for (int i = 0; i < count_b2; i++){
            string f2;
            string l2;
            BirthdayType val2; // this is a holder for the value of nodes in val2.
            bpOne.selectInvitee(i, f2, l2, val2);
            if (bpJoined.personOnGuestList(f2, l2)){//person on the list
                if (bpJoined.checkGuestList(f2, l2, val2)) // val2 is changed when true. means  values of these two nodes are not same, so delete the node from bpjoined.
                {
                    bpJoined.dropFromGuestList(f2, l2);
                    result++;
                }
                // else if vals are different, just do nothing;
        
            }
            else{ // person not on the list, then add the b2 person to bpjoined
                bpJoined.addInvitee(f2, l2, val2);
            }
        }
    }
    
    
    if (result > 0){
        return false;
    }
    else{
        return true;
    }
}

void verifyGuestList (const string& fsearch, const string& lsearch, const BirthdayParty&  bpOne, BirthdayParty& bpResult)
{
    //delete the bpresult if bpresult != empty
    if (bpResult.whosOnTheGuestList() > 0 && &bpResult != &bpOne){
        int count = bpResult.whosOnTheGuestList();
        for (int n = 0; n < count; n++)
            {
                string first;
                string last;
                BirthdayType val;
                bpResult.selectInvitee (0, first, last, val);
                bpResult.dropFromGuestList(first, last);
        }
    }
    // aliasing case;
    if (&bpResult == &bpOne){
        BirthdayParty new_party;
        //four cases as below;
        if (fsearch == "*" && lsearch == "*"){
            // bpresult = bpone;
            new_party = bpOne;
        }
        else if (fsearch == "*"){
            // traverse bpone; if lsearch == last: add this person to bpresult;
            int count = bpOne.whosOnTheGuestList();
            for (int i = 0; i < count; i++){
                string first;
                string last;
                BirthdayType val;
                bpOne.selectInvitee (i, first, last, val);
                if (last == lsearch){
                    new_party.addInvitee(first, last, val);
                }
            }
            
        }
        else if (lsearch == "*"){
            // traverse bpone; if fsearch == first: add this person to bpresult;
            int count = bpOne.whosOnTheGuestList();
            for (int i = 0; i < count; i++){
                string first;
                string last;
                BirthdayType val;
                bpOne.selectInvitee (i, first, last, val);
                if (first == fsearch){
                    new_party.addInvitee(first, last, val);
                }
            }
        }
        else{
            // traverse bpone; if fsearch == first && lsearch == last: add this person to bpresult;
            int count = bpOne.whosOnTheGuestList();
            for (int i = 0; i < count; i++){
                string first;
                string last;
                BirthdayType val;
                bpOne.selectInvitee (i, first, last, val);
                if (first == fsearch && last == lsearch){
                    new_party.addInvitee(first, last, val);
                }
            }
        }
        bpResult = new_party;
    }
    
    // normal case, no aliasing
    if (fsearch == "*" && lsearch == "*"){
        // bpresult = bpone;
        bpResult = bpOne;
    }
    else if (fsearch == "*"){
        // traverse bpone; if lsearch == last: add this person to bpresult;
        int count = bpOne.whosOnTheGuestList();
        for (int i = 0; i < count; i++){
            string first;
            string last;
            BirthdayType val;
            bpOne.selectInvitee (i, first, last, val);
            if (last == lsearch){
                bpResult.addInvitee(first, last, val);
            }
        }
        
    }
    else if (lsearch == "*"){
        // traverse bpone; if fsearch == first: add this person to bpresult;
        int count = bpOne.whosOnTheGuestList();
        for (int i = 0; i < count; i++){
            string first;
            string last;
            BirthdayType val;
            bpOne.selectInvitee (i, first, last, val);
            if (first == fsearch){
                bpResult.addInvitee(first, last, val);
            }
        }
    }
    else{
        // traverse bpone; if fsearch == first && lsearch == last: add this person to bpresult;
        int count = bpOne.whosOnTheGuestList();
        for (int i = 0; i < count; i++){
            string first;
            string last;
            BirthdayType val;
            bpOne.selectInvitee (i, first, last, val);
            if (first == fsearch && last == lsearch){
                bpResult.addInvitee(first, last, val);
            }
        }
    }
    
}
