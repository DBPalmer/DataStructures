#ifndef INC_22S_FLIGHT_PLANNER_DSLINKEDLIST_H
#define INC_22S_FLIGHT_PLANNER_DSLINKEDLIST_H
using namespace std;
#include <iostream>

template <typename T>
class DSNode{//node class with all public variables
public:
    T data;
    DSNode<T>* prev;
    DSNode<T>* next;
};
template <typename T>
class DSLinkedList{
private:
    DSNode<T>* head;
    DSNode<T>* end;
    DSNode<T>* itr;
public:
    /**
     * constructors and destructor
     */
    DSLinkedList();
    DSLinkedList(const DSLinkedList<T>&);
    ~DSLinkedList();
    /**
     * overloaded asg op
     * @return DSLL
     */
    DSLinkedList<T>& operator=(const DSLinkedList<T>&);
    /**
     * adds element to back
     */
    void push_back(T&);
    /**
     * adds element to front
     */
    void push_front(T&);
    /**
     * removes element from back
     */
    void remove_back();
    /**
     * resets itr to point at head
     */
    void reset();
    /**
     * checks if itr is nullptr, therefore has the end of the LL been reached
     * @return bool
     */
    bool hasElement();
    /**
     * @return itr
     */
    DSNode<T>& getElement();
    /**
     * sets itr to next
     */
    void getNext();
    /**
     * getters
     */
    DSNode<T>& getHead();
    DSNode<T>& getEnd();
    /**
     * searches for an element inside LL
     * @return bool
     */
    bool search(T&);
    /**
     * @return element in list, needed so that all of the element's other data is captured
     */
    T& find(T&);
};
template <typename T>
DSLinkedList<T>::DSLinkedList(){//all to nullptr
    head = nullptr;
    end = nullptr;
    itr = nullptr;
}
template <typename T>
DSLinkedList<T>::DSLinkedList(const DSLinkedList<T>& list){
    if (list.head == nullptr) {//checks if list is empty
        head = nullptr;
        end = nullptr;
        itr = nullptr;
    }
    else {//if not
        DSNode<T>* temp = list.head;
        end = nullptr;//end and head will change with the push_back function
        head = nullptr;
        while (temp != nullptr) {//takes all the data from list and adds it to this one by one
            push_back(temp->data);
            temp = temp->next;
        }
    }
}
template <typename T>
DSLinkedList<T>::~DSLinkedList(){
    while (head != nullptr) {//removes all the elements in list
        remove_back();
    }
}
template <typename T>
DSLinkedList<T>& DSLinkedList<T>::operator=(const DSLinkedList<T>& list){
    if (this != &list) {//if they are not equal
        DSNode<T>* temp = list.head;
        end = nullptr;//end and head will change with the push_back function
        head = nullptr;
        while (temp != nullptr){//takes all the data from list and adds it to this one by one
            this->push_back(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}
template <typename T>
void DSLinkedList<T>::push_back(T& data){
    //reference: https://www.studytonight.com/data-structures/doubly-linked-list
    DSNode<T>* temp = new DSNode<T>;
    temp->data = data;//sets node data to the data being pushed in
    temp->next = nullptr;//nothing in front of it
    if (head == nullptr){//checks to see if list is empty
        temp->prev = nullptr;
        head = temp;//if so, the beginning is also temp
        this->reset();//resets iterator to point to the new head
    }
    else {//end is now pointing forward to the new end (temp)
        temp->prev = end;//since it is at the end, it has to point back to the old end
        end->next = temp;
    }
    end = temp;
}
template <typename T>
void DSLinkedList<T>::push_front(T& data){
    //reference: https://www.studytonight.com/data-structures/doubly-linked-list
    DSNode<T>* temp = new DSNode<T>;
    temp->data = data;//sets node data to the data being pushed in
    temp->prev = nullptr;//since it is at the front, prev doesnt point to anything
    if (head == nullptr) {//checks to see if list is empty
        end = temp;//if so, the end is also temp
        temp->next = nullptr;
        this->reset();//resets iterator to point to the new head
    }
    else {//otherwise, head (now being 2nd) points back to temp
        temp->next = head;//its next is now what used to be at the beginning
        head->prev = temp;
    }
    head = temp;//resets head pointer
}
template <typename T>
void DSLinkedList<T>::remove_back(){
    if (head != nullptr){//as long as it is not already empty
        if (end->prev != nullptr) {//if it is longer than one
            DSNode<T>* temp = end;
            end = end->prev;//end is now what it used to point back to
            end->next = nullptr;//end doesnt point forward
            delete temp;//delete old end
        }
        else {//if it has 1 element, list will now be empty
            DSNode<T>* temp = end;
            delete temp;//delete old end
            head = nullptr;
            end = nullptr;
            itr = nullptr;
        }
    }
}
template <typename T>
void DSLinkedList<T>::reset(){
    itr = head;//itr is back at the front
}
template <typename T>
bool DSLinkedList<T>::hasElement(){
    return (itr != nullptr);//means that there are no more elements in the linked list if false
}
template <typename T>
DSNode<T>& DSLinkedList<T>::getElement(){
    return *itr;//return the node
}
template <typename T>
void DSLinkedList<T>::getNext(){
    itr = itr->next;//grabs the next element
}
template <typename T>
DSNode<T>& DSLinkedList<T>::getHead(){
    return *head;
}
template <typename T>
DSNode<T>& DSLinkedList<T>::getEnd(){
    return *end;
}
template <typename T>
bool DSLinkedList<T>::search(T& data){
    reset();
    while (hasElement()){
        if (getElement().data == data){//if element is found
            return true;
        }
        getNext();
    }
    return false;//return false if it was not found
}
template <typename T>
T& DSLinkedList<T>::find(T& data){
    reset();
    while (hasElement()){
        if (getElement().data == data){//if element is found
            return getElement().data;//returning the actual city(data) inside, so that its data can be accessed
        }
        getNext();
    }
    //doesn't need to return something if not found because search will be used on top of it, or it will be known if it is inside the LL
}
#endif //INC_22S_FLIGHT_PLANNER_DSLINKEDLIST_H
