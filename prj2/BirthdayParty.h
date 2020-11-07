//
//  BirthdayParty.h
//  BirthdayParty
//
//  Created by 李心怡 on 7/14/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#ifndef BirthdayParty_h
#define BirthdayParty_h
#include <string>


typedef std::string BirthdayType;

struct Node{
    BirthdayType value;
    std::string first;
    std::string last;
    Node* next;
    Node* prev;
};

class BirthdayParty
{
private:
    Node* head;
    Node* tail;
public:
    BirthdayParty(); // Create an empty BirthdayParty list
    ~BirthdayParty();
    BirthdayParty(const BirthdayParty& rhs);
    const BirthdayParty& operator=(const BirthdayParty& rhs);
    bool noInvitees() const; // Return true if the BirthdayParty list
    // is empty, otherwise false.
    int whosOnTheGuestList() const; // Return the number of players
    //in
    // the BirthdayParty list.
    bool addInvitee(const std::string& firstName, const std::string&
                    lastName, const BirthdayType& value);
    // If the full name (both the first and last name) is not equal
    // to any full name currently in the list then add it and return
    // true. Elements should be added according to their last name.
    // Elements with the same last name should be added according to
    // their first names. Otherwise, make no change to the list and
    // return false (indicating that the name is already in the
    // list).
    
    
    bool modifyInvitee(const std::string& firstName, const
                       std::string& lastName, const BirthdayType& value);
    // If the full name is equal to a full name currently in the
    // list, then make that full name no longer map to the value it
    // currently maps to, but instead map to the value of the third
    // parameter; return true in this case. Otherwise, make no
    // change to the list and return false.
    bool addOrModify(const std::string& firstName, const std::string&
                     lastName, const BirthdayType& value);
    // If full name is equal to a name currently in the list, then
    // make that full name no longer map to the value it currently
    // maps to, but instead map to the value of the third parameter;
    // return true in this case. If the full name is not equal to
    // any full name currently in the list then add it and return
    // true. In fact, this function always returns true.
    bool dropFromGuestList(const std::string& firstName, const
                           std::string& lastName);
    // If the full name is equal to a full name currently in the
    // list, remove the full name and value from the list and return
    // true. Otherwise, make no change to the list and return
    // false.
    bool personOnGuestList(const std::string& firstName, const
                           std::string& lastName) const;
    // Return true if the full name is equal to a full name
    // currently in the list, otherwise false.
    bool checkGuestList(const std::string& firstName, const
                        std::string& lastName, BirthdayType& value) const;
    // If the full name is equal to a full name currently in the
    // list, set value to the value in the list that the full name
    // maps to, and return true. Otherwise, make no change to the
    // value parameter of this function and return false.
    bool selectInvitee(int i, std::string& firstName, std::string&
                       lastName, BirthdayType& value) const;
    // If 0 <= i < size(), copy into firstName, lastName and value
    // parameters the corresponding information of the element at
    // position i in the list and return true. Otherwise, leave the
    // parameters unchanged and return false. (See below for details
    // about this function.)
    void changeGuestList(BirthdayParty& other);
    // Exchange the contents of this list with the other one.
    
    void printList() const;
    //need to delete this func when turn in;
};

bool combineGuestLists(const BirthdayParty & bpOne, const BirthdayParty & bpTwo, BirthdayParty & bpJoined);

void verifyGuestList (const std::string& fsearch, const std::string& lsearch, const BirthdayParty& bpOne, BirthdayParty& bpResult);

#endif /* BirthdayParty_h */
