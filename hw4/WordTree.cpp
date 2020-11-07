//
//  WordTree.cpp
//  hw4
//
//  Created by 李心怡 on 8/8/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include "WordTree.h"
using namespace std;

//helper function for copy constructor, takes in rhs, copy it to this;
WordNode* WordTree::copyCnstr(const WordNode *node)
{
    if (node == nullptr){
        return nullptr;
    }
    WordNode *cur;
    cur = new WordNode(node->m_data, node->m_count);
    root = cur;
    cur->m_left = copyCnstr(node->m_left);
    // copy the node to this
    
    cur->m_right = copyCnstr(node->m_right);
    return cur;
}


WordTree::WordTree(const WordTree& rhs)
{
    root = copyCnstr(rhs.root);
}

/*
// copy constructor
WordTree::WordTree(const WordTree& rhs)
{
    stack<WordNode *> sr;
    stack<WordNode *> scp;
    WordNode *cur = rhs.root;
    WordNode *p; // pointer for creating this tree
    WordNode *child;
    //WordNode *lp; // the left pointer after p;
    //WordNode *rp; // the right pointer child of p;
    if (cur == nullptr){
        root = nullptr;
    }

    p = new WordNode(rhs.root->m_data, rhs.root->m_count);
    root = p;
    while(sr.empty() == false || cur != nullptr){
        while(cur != nullptr){
            sr.push(cur);
            // copy the node at cur to p;
            //p = new WordNode(cur->m_data,cur->m_count);
            // make a new node that child points to
            scp.push(p);
            //update left node;
            if (cur->m_left != nullptr){
                child = new WordNode(cur->m_left->m_data, cur->m_left->m_count);
            }
            else{
                child = nullptr;
            }
            p->m_left = child;
            p = child;
            cur = cur->m_left;
            
        }
        // cur is null here;
        // 回一次， 回到的node就被删除；然后去他的右边；
        cur = sr.top();
        p = scp.top();
        sr.pop();
        scp.pop();
        cur = cur->m_right;
        //child = p->m_right;
        if (cur != nullptr){
            child = new WordNode(cur->m_data, cur->m_count);
        }
        else{
            child = nullptr;
        }
        p->m_right = child;
        p = child;
        
    }
    
}
 */

const WordTree& WordTree::operator=(const WordTree& rhs)
{
    if (&rhs == this){
        return *this;
    }
    //delete the old tree;
    WordTree::~WordTree();
    
    root = copyCnstr(rhs.root);
    return *this;
}




//iterative method for assignment operator;
/*
const WordTree& WordTree::operator=(const WordTree& rhs)
{
    if (&rhs == this){
        return *this;
    }
    //delete the old tree;
    WordTree::~WordTree();

    stack<WordNode *> sr;
    stack<WordNode *> scp;
    WordNode *cur = rhs.root;
    WordNode *p; // pointer for creating this tree
    WordNode *child;
    //WordNode *lp; // the left pointer after p;
    //WordNode *rp; // the right pointer child of p;
    if (cur == nullptr){
        root = nullptr;
    }

    p = new WordNode(rhs.root->m_data, rhs.root->m_count);
    root = p;
    while(sr.empty() == false || cur != nullptr){
        while(cur != nullptr){
            sr.push(cur);
            // copy the node at cur to p;
            //p = new WordNode(cur->m_data,cur->m_count);
            // make a new node that child points to
            scp.push(p);
            //update left node;
            if (cur->m_left != nullptr){
                child = new WordNode(cur->m_left->m_data, cur->m_left->m_count);
            }
            else{
                child = nullptr;
            }
            p->m_left = child;
            p = child;
            cur = cur->m_left;
            
        }
        // cur is null here;
        // 回一次， 回到的node就被删除；然后去他的右边；
        cur = sr.top();
        p = scp.top();
        sr.pop();
        scp.pop();
        cur = cur->m_right;
        //child = p->m_right;
        if (cur != nullptr){
            child = new WordNode(cur->m_data, cur->m_count);
        }
        else{
            child = nullptr;
        }
        p->m_right = child;
        p = child;
    }

    return *this;
}
*/
void WordTree::add(WordType v)
{
    // if the tree is empty, dynamically allocate a WordNode and add it to the root pointer;
    if (root == nullptr){
        root = new WordNode(v,1);
        return;
    }
    else{
        WordNode *cur = root;
        while(true){
            if (cur->m_data == v){
                cur->m_count++;
                return;
            }
            else if (v < cur->m_data ){
                if (cur->m_left != nullptr){
                    cur = cur->m_left;
                }
                else{
                    cur->m_left = new WordNode(v,1);
                    return;
                }
            }
            else{
                if (cur->m_right != nullptr){
                    cur = cur->m_right;
                }
                else{
                    cur->m_right = new WordNode(v,1);
                    return;
                }
            }
        }
    }
}

int WordTree::countNodes(const WordNode *node) const{
    if (node == nullptr){
        return 0;
    }
    else{
        int left = countNodes(node->m_left);
        int right = countNodes(node->m_right);
        return left + right + 1;
    }
}


int WordTree::distinctWords() const
{
    // count total number of nodes;
    return countNodes(root);
    
}

int WordTree::countTot(const WordNode *node) const{
    if (node == nullptr){
        return 0;
    }
    else{
        int left = countTot(node->m_left);
        int right = countTot(node->m_right);
        return left + right + node->m_count;
    }
}

int WordTree::totalWords() const
{
    return countTot(root);
}


ostream& recPrint(ostream &out, const WordNode *node)
{
    if (node == nullptr){
        out << "";
        return out;
    }
    recPrint(out, node->m_left);
    out << node->m_data << " " << node->m_count << endl;
    recPrint(out, node->m_right);
    return out;
    
}

ostream& operator<<(ostream &out, const WordTree& rhs)
{
    
    return recPrint(out, rhs.root);
}
// the iterative method using stack is as follows;
/*
ostream& operator<<(ostream &out, const WordTree& rhs)
{

    // This algorithm is an iterative method to traverse a tree.
    // Features:
    //1. using stack, pop, top;
    //2. goes left first, inorder;
    //3. iterative, not recursive;
    
    // make a stack to store node pointers
    stack<WordNode *> s;
    // use the cur node pointer to initialy point to the root
    WordNode *cur = rhs.root;
    // stop loopin when cur is null and stack is empty;
    while (cur != nullptr || s.empty() == false){
        // find the very left leaf
        while(cur != nullptr){
            s.push(cur);
            cur = cur->m_left;
        }
        // before assign cur to s.top, here the cur must be null;
        // assign cur to the very left node, we don't know if this node's right is empty
        cur = s.top();
        s.pop();
        out << cur->m_data << " " << cur->m_count << endl;
        // cur goes back if right is empty, otherwise goes to the right side;
        cur = cur->m_right;
    }
    
    return out;
}
*/
void WordTree::RecurDelete(WordNode *node){
    if (node != nullptr){
        RecurDelete(node->m_left);
        RecurDelete(node->m_right);
        delete node;
    }
}
WordTree::~WordTree()
{
    RecurDelete(root);
}
