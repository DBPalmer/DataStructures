#ifndef INC_22S_FLIGHT_PLANNER_DSSTACK_H
#define INC_22S_FLIGHT_PLANNER_DSSTACK_H
#include "DSLinkedList.h"
using namespace std;
template <typename T>
class DSStack{
private:
    DSLinkedList<T> list;
public:
    /**
     * @return top element
     */
    T& peek();
    /**
     * removes top
     */
    void pop();
    /**
     * adds to top
     */
    void push(T&);
    /**
     * checks if stack is empty
     * @return bool
     */
    bool is_empty();
    /**
     * @return stack's LL
     */
    DSLinkedList<T>& getList();
    /**
     * search for an element in the stack
     * @return bool
     */
    bool search(T&);
};
template <typename T>
T& DSStack<T>::peek(){
    return list.getEnd().data;//end of stack's LL
}
template <typename T>
void DSStack<T>::pop(){
    list.remove_back();//DSLL wrapper
}
template <typename T>
void DSStack<T>::push(T& data){
    list.push_back(data);//DSLL wrapper
}
template <typename T>
bool DSStack<T>::is_empty(){
    return (&list.getHead() == nullptr);//checks to see if list is empty
}
template <typename T>
DSLinkedList<T>& DSStack<T>::getList(){
    return list;
}
template <typename T>
bool DSStack<T>::search(T& data){
    return (list.search(data));//DSLL wrapper
}
#endif //INC_22S_FLIGHT_PLANNER_DSSTACK_H