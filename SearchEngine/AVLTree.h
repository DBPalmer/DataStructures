//
// Created by Deuce Palmer on 4/11/22.
//
//Citation: AVLTree code from Mark Allen Weiss 4th edition, as Dr. Fontenot told us in class on 4/11/22
//last edit on: 4/28/22
#ifndef INC_22S_FINAL_PROJ_AVLTREE_H
#define INC_22S_FINAL_PROJ_AVLTREE_H
#include <iostream>
#include <fstream>
#include "Word.h"
using namespace std;


class AVLTree {
private:
    /**
     * Contains a Word object and pointers to its children
     */
    struct AVLNode {//struct so that all members are public
        Word element;//Word with vector of documents
        AVLNode *left;//left ptr
        AVLNode *right;//right ptr
        int height;//height is calc as the amount of max levels below the node
        //constructor
        AVLNode(const Word &theElement, AVLNode *lt, AVLNode *rt, int h = 0) : element(theElement), left(lt), right(rt), height(h) {
        }
        //constructor with added sting which is the document ID
        AVLNode(const Word &theElement, AVLNode *lt, AVLNode *rt, Document doc, int h = 0) : element(theElement), left(lt), right(rt), height(h) {
            element.push_back(doc);
        }
    };
    AVLNode *root;//pointer to root of tree
    /**
     * inserts an element in the tree, while balancing and handling duplicates
     */
    void insert(Word&, AVLNode *&, Document&);
    void insert(Word&, AVLNode *&);
    /**
     * provides any necessary rotations to keep the tree balanced
     */
    void balance(AVLNode*&);
    /**
     * searches for a word
     */
    bool contains(Word &, AVLNode *) const;
    /**
     * same as contains, but returns the word when it is found
     */
    Word& find(Word &, AVLNode *) const;
    /**
     * deletes all the nodes in a tree, used inside destructor
     */
    void makeEmpty(AVLNode *&);
    /**
     * inOrder. prints elements in order from least to greatest
     */
    void printTree(AVLNode *) const;
    /**
     * inOrder. prints Word name along with other data to file
     */
    void printTreeToFile(AVLNode *, basic_ofstream<char>&) const;
    /**
     * copies and returns a cloned node
     */
    AVLNode* clone(AVLNode *t) const {
        if (t == nullptr) {
            return nullptr;
        } else {
            return new AVLNode(t->element, clone(t->left), clone(t->right), t->height);
        }
    }
    /**
     * @return height (max levels below it) for node
     */
    int height(AVLNode *) const;
    /**
     * case 1 rotation
     */
    void rotateWithLeftChild(AVLNode *&);
    /**
     * case 4 rotation
     */
    void rotateWithRightChild(AVLNode *&);
    /**
     * case 2 rotation
     */
    void doubleWithLeftChild(AVLNode *&);
    /**
     * case 3 rotation
     */
    void doubleWithRightChild(AVLNode *&);
    /**
     * count the number of unique items for statistics print out
     */
    void count(AVLNode *, int&);
    /**
     * same method as count, but will store each pair (word & # of docs) into a vector, needed for top 25 print out
     */
    void topWords(AVLNode *, vector<pair<int, string>>&);
public:
    /**
     * constructors & destructor
     */
    AVLTree();
    AVLTree(const AVLTree &rhs);
    ~AVLTree();
    /**
     * overloaded asg op
     */
    const AVLTree &operator=(const AVLTree &);
    /**
     * searches for a word
     */
    bool contains(Word &) const;
    /**
     * same as contains, but returns the word when it is found
     */
    Word& find(Word &) const;
    /**
     * @return whether or not tree contains any nodes
     */
    bool isEmpty() const;
    /**
     * inOrder. prints elements in order from least to greatest
     */
    void printTree() const;
    /**
     * inOrder. prints elements in order from least to greatest to file
     */
    void printTreeToFile(basic_ofstream<char>&) const;
    /**
     * deletes all the nodes in a tree, used inside destructor
     */
    void makeEmpty();
    /**
    * inserts an element in the tree
    */
    void insert(Word &, Document&);
    /**
     * inserts an element in the tree, Document not needed since this is used when reading persistent index
     */
    void insert(Word&);
    /**
     * count the number of unique items for statistics print out
     * @return # of nodes
     */
    int count();
    /**
     * needed for top 25 print out
     * @return vector of pairs
     */
    vector<pair<int, string>> topWords();
};
#endif //INC_22S_FINAL_PROJ_AVLTREE_H
