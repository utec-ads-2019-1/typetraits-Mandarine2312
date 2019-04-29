#ifndef LIST_H
#define LIST_H

#include "node.h"

template <typename Tr>
class List {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
      
    private:
        Node<T>* head;
        Operation cmp;
        int nodes = 0;
              
    public:
        List() : head(nullptr) {};

        bool find(T search, Node<T> **&pointer) {
            (*pointer) = head;
            if((*pointer)->data == search){
                return true;
            }else{
                while((*pointer)->next != nullptr){
                    pointer = &((*pointer)->next);
                    if((*pointer)->data == search){
                        return true;
                    }
                }
            }
            return false;
        }

        bool insert(T data) {
            if (nodes == 0) {
                auto newElement = new Node<T>(data);
                head = newElement;
                nodes++;
                return true;
            } else {
                auto tempPtrPtr = &head;
                if (find(data, tempPtrPtr)) {
                    return false;
                } else {
                    auto newElement = new Node<T>(data);
                    if (cmp(newElement->data, head->data)) {
                        newElement->next = head;
                        head->prev = newElement;
                        head = newElement;
                    }else{
                        tempPtrPtr = &head;
                        while ((cmp((*tempPtrPtr)->data, data)) && ((*tempPtrPtr)->next != nullptr)){
                            tempPtrPtr = &((*tempPtrPtr)->next);
                        } if ((*tempPtrPtr)->next != nullptr){
                            newElement->next = (*tempPtrPtr);
                            newElement->prev = (*tempPtrPtr)->prev;
                            (*tempPtrPtr)->prev->next = newElement;
                            (*tempPtrPtr)->prev = newElement;
                        }else{
                            newElement->prev  = (*tempPtrPtr);
                            (*tempPtrPtr)->next = newElement;
                        }

                    }
                }
            }
            nodes++;
            return true;
        }
             
        bool remove(T data) {
            auto whereToRemove = &head;
            if (find(data, whereToRemove)) {
                if ((*whereToRemove) == head) {
                    head = head->next;
                    whereToRemove = &(head->prev);
                    delete *whereToRemove;
                    nodes--;
                    // Falta return
                } else {
                    (*whereToRemove)->prev->next = (*whereToRemove)->next;
                    (*whereToRemove)->next->prev = (*whereToRemove)->prev;
                    delete (*whereToRemove);
                    nodes--;
                    return true;
                }
            } else {
                return false;
            }
        }
             
        int size() {
            return nodes;
        }

        T operator[](int index) {
            auto temp = head;
            for(int i = 0; i < index; i++){
                temp = temp->next;
            }

            return temp->data;
        }

        ~List() {
	    // Falta validar que head no sea null cuando es una lista vacía
            head->killSelf();
        }         
};

#endif
