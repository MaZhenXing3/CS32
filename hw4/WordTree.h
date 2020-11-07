//
//  WordTree.h
//  hw4
//
//  Created by 李心怡 on 8/8/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#ifndef WordTree_h
#define WordTree_h

#include <stdio.h>
#include <iostream>
#include <string>

typedef std::string WordType;
typedef int WordCount;

struct WordNode {
    WordType m_data;
    WordCount m_count;
    WordNode *m_left;
    WordNode *m_right;
   // You may add additional data members and member functions
   // in WordNode
    
    // constructor of WordNode
    WordNode(WordType val, WordCount count): m_data(val), m_count(count){
        m_left = nullptr;
        m_right = nullptr;
    }
};

class WordTree {
   private:
      WordNode *root;
      void RecurDelete(WordNode *node);
      int countNodes(const WordNode *node) const;
      int countTot(const WordNode *node) const;
      std::ostream& recPrint(std::ostream &out, const WordNode *node);
      WordNode* copyCnstr(const WordNode *node);
   public:

      // default constructor
      WordTree() : root(nullptr) { };
      // copy constructor
      WordTree(const WordTree& rhs);
      // assignment operator
      const WordTree& operator=(const WordTree& rhs);
    
      // Inserts v into the WordTree
      void add(WordType v);
    
      // Returns the number of distinct words / nodes
      int distinctWords() const;
    
      // Returns the total number of words inserted, including
        // duplicate values
      int totalWords() const;
    
        // Prints the LinkedList
      friend std::ostream& operator<<(std::ostream &out, const WordTree& rhs);
    
        // Destroys all the dynamically allocated memory in the
        // tree
      ~WordTree();
};

#endif /* WordTree_hpp */
