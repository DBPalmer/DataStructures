//
// Created by Deuce Palmer on 4/16/22.
//
//Citation: AVLTree code from Mark Allen Weiss 4th edition, as Dr. Fontenot told us in class on 4/11/22
//last edit on: 5/02/22

#include "AVLTree.h"

//private functions

void AVLTree::insert(Word& x, AVLNode *&t, Document& doc) {
    if (t == nullptr) {//creates a node if the root (tree) is empty
        t = new AVLNode(x, nullptr, nullptr, doc);//needs to have doc as well, so Word still contains that document ID
    } else if (x < t->element) {//moves to the left
        insert(x, t->left, doc);
    } else if (t->element < x) {//moves to the right
        insert(x, t->right, doc);
    } else {//duplicate handling
        t->element.push_back(doc);//will not create a new word in the tree, instead just adds a document to the pre-existing Word
    }
    balance(t);//after an insertion, will check if a rotation is needed
}
void AVLTree::insert(Word& x, AVLNode *&t) {
    if (t == nullptr) {//creates a node if the root (tree) is empty
        t = new AVLNode(x, nullptr, nullptr);
    } else if (x < t->element) {//moves to the left
        insert(x, t->left);
    } else if (t->element < x) {//moves to the right
        insert(x, t->right);
    } else {//duplicate handling
        //technically this shouldn't be reach, this version of the insert is only called when reading persistent index, so no duplicates
    }
    balance(t);//after an insertion, will check if a rotation is needed
}
void AVLTree::balance(AVLNode*& t){
    if (t != nullptr) {//not needed if t is nullptr
        if (height(t->left) - height(t->right) > 1) {//is left side height too much bigger than right height?
            if (height(t->left->left) >= height(t->left->right)) {//narrows down between C1 & C2
                rotateWithLeftChild(t);//case 1
            } else {
                doubleWithLeftChild(t);//case 2
            }
        } else if (height(t->right) - height(t->left) > 1) {//is right side height too much bigger than left height?
            if (height(t->right->right) >= height(t->right->left)) {//narrows down between C4 & C3
                rotateWithRightChild(t);//case 4
            } else {
                doubleWithRightChild(t);//case 3
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;//recalculates height after any necessary rotations
    }
}
bool AVLTree::contains(Word &x, AVLNode *t) const {
    if (t == nullptr) {
        return false;
    } else if (x < t->element) {//moves to the left
        return contains(x, t->left);
    } else if (t->element < x) {//moves to the right
        return contains(x, t->right);
    } else {//reached if Word was found
        return true;
    }
}
Word& AVLTree::find(Word &x, AVLNode *t) const {
    if (t == nullptr) {
    } else if (x < t->element) {//moves to the left
        return find(x, t->left);
    } else if (t->element < x) {//moves to the right
        return find(x, t->right);
    } else {//reached if Word was found
        return t->element;//returns the Word, being able to access its documents
    }
}
void AVLTree::makeEmpty(AVLNode *&t) {
    //delete each node starting from the top and working down
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}
void AVLTree::printTree(AVLNode *t) const {
    if (t != nullptr) {
        printTree(t->left);//goes to the left first, so that it is in order
        cout << t->element.getWord() << endl;
        printTree(t->right);//gets the larger values second
    }
}
void AVLTree::printTreeToFile(AVLNode *t, basic_ofstream<char>& file) const{
    if (t != nullptr) {
        printTreeToFile(t->left, file);//goes to the left first, so that it is in order
        file << t->element.getWord() << " ";//prints name
        file << t->element.getDoc().size() << " ";
        for (int i = 0; i < t->element.getDoc().size(); i++) {//along with all the documents and their data
            file << t->element.getDoc()[i].getId() << "," << t->element.getDoc()[i].getScore() << " ";
        }
        file << endl;
        printTreeToFile(t->right, file);//gets the larger values second
    }
}
int AVLTree::height(AVLNode *t) const {
    //max level of nodes below t
    return t == nullptr ? -1 : t->height;
}
void AVLTree::rotateWithLeftChild(AVLNode *&k2) {
    //code given in class
    //alpha is k1
    AVLNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}
void AVLTree::rotateWithRightChild(AVLNode *&k1) {
    //flipped everything from case 1
    //alpha is k2
    AVLNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}
void AVLTree::doubleWithLeftChild(AVLNode *&k3) {
    rotateWithRightChild(k3->left);//first transforms into a case 1
    rotateWithLeftChild(k3);//case 1 operation
}
void AVLTree::doubleWithRightChild(AVLNode *&k1) {
    rotateWithLeftChild(k1->right);//first transforms into a case 4
    rotateWithRightChild(k1);//case 4 operation
}
void AVLTree::count(AVLNode *t, int& num){
    //adds 1 to num with every node visited
    if (t != nullptr) {
        count(t->left, num);
        num++;
        count(t->right, num);
    }
}
void AVLTree::topWords(AVLNode *t, vector<pair<int, string>>& vec){
    //adds the pair {word, # of docs} to the vector for every node visited
    if (t != nullptr) {
        topWords(t->left, vec);
        vec.push_back({t->element.getDoc().size(), t->element.getWord()});
        topWords(t->right, vec);
    }
}
//public functions

AVLTree::AVLTree() : root(nullptr) {//automatically sets root to nullptr since the tree is empty
}
AVLTree::AVLTree(const AVLTree &rhs) : root(nullptr) {//copy constructor
    *this = rhs;
}
AVLTree::~AVLTree() {//destructor
    makeEmpty();
}
const AVLTree &AVLTree::operator=(const AVLTree &rhs) {
    if (this != &rhs) {//if not already equal
        makeEmpty();//first empty this tree
        root = clone(rhs.root);//then copy over each element from rhs
    }
    return *this;
}
bool AVLTree::contains(Word &x) const {
    return contains(x, root);//calls private contains
}
Word& AVLTree::find(Word &x) const {
    return find(x, root);//calls private find
}
bool AVLTree::isEmpty() const {
    return root == nullptr;//if root is nullptr, tree is empty
}
void AVLTree::printTree() const {
    if (isEmpty()) {//checks if tree is empty
        cout << "AVL Tree is empty" << endl;
    }
    else {
        printTree(root);//calls private printTree
    }
}
void AVLTree::printTreeToFile(basic_ofstream<char>& file) const{
    if (isEmpty()) {//checks if tree is empty
        cout << "AVL Tree is empty" << endl;
    }
    else {
        printTreeToFile(root, file);//calls private printTree
    }
}
void AVLTree::makeEmpty() {
    makeEmpty(root);//calls private makeEmpty
}
void AVLTree::insert(Word &x, Document& doc) {
    insert(x, root, doc);//calls private insert
}
void AVLTree::insert(Word &x) {
    insert(x, root);//calls private insert
}
int AVLTree::count(){
    int num = 0;
    count(root, num);//call to private count
    return num;//return size
}
vector<pair<int, string>> AVLTree::topWords(){
    vector<pair<int, string>>* vec = new vector<pair<int, string>>;
    topWords(root, *vec);//call to private topWords
    return *vec;//returns vector of pairs that will be sorted and the last 25 will be printed
}