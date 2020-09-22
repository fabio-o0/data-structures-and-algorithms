//
//  LinkedList.h
//  Linked List
//
//  Created by Fabio Suarez on 9/29/19.
//  Copyright © 2019 Fabio Suarez. All rights reserved.
//

#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include "leaker.h"

using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };

    //behaviors
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node *node) const;
    void PrintReverseRecursive(const Node *node) const;
    
    //accessors
    unsigned int NodeCount() const;
    void FindAll(vector<Node *> &outData, const T&value) const;
    const Node *Find(const T &data) const;
    Node *Find(const T &data);
    const Node *GetNode(unsigned int index) const;
    Node *GetNode(unsigned int index);
    Node *Head();
    const Node *Head() const;
    Node *Tail();
    const Node *Tail() const;
    
    //insertion
    void AddHead(const T &data);
    void AddTail(const T &data);
    void AddNodesHead(const T *data, unsigned int count);
    void AddNodesTail(const T *data, unsigned int count);
    void InsertAfter(Node *node, const T &data);
    void InsertBefore(Node *node, const T &data);
    void InsertAt(const T &data, unsigned int index);
    
    //removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T &data);
    bool RemoveAt(int index);
    void Clear();
    
    //operators
    const T &operator[](unsigned int index) const;
    T &operator[](unsigned int index);
    bool operator==(const LinkedList<T> &other) const;
    LinkedList<T> &operator=(const LinkedList<T> &other);
    
    //construction/deconstruction
    LinkedList<T>();
    LinkedList<T>(const LinkedList<T> &other);
    ~LinkedList<T>();
    
    //helper
    LinkedList<T>::Node* findAt(int index);
    int getNodeIndex(Node* node);
    
private:
    Node* head;
    Node* tail;
    Node* current;
    int numNodes;
};

template <typename T>
LinkedList<T>::LinkedList() {
    this->numNodes = 0;
    this->current = nullptr;
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    if (this->head != nullptr) {
        Node* toDelete = this->head;
        while (toDelete != nullptr) {
            Node* next = toDelete->next;
            delete toDelete;
            toDelete = next;
        }
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other) {
    this->numNodes = other->numNodes;
    this->current = other->current;
    this->head = other->head;
    this->tail = other->tail;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other) {
    if (this != other) {
        this->numNodes = other->numNodes;
        this->current = other->current;
        this->head = other->head;
        this->tail = other->tail;
    }
    return *this;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &other) const {
    if (
        this->numNodes == other->numNodes &&
        this->current == other->current &&
        this->head == other->head &&
        this->tail == other->tail
        ) {
        return true;
    }
    return false;
}

template <typename T>
void LinkedList<T>::Clear() {
    ~LinkedList();
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::findAt(int index) {
    if (index >= this->numNodes || index < 0) {
        throw runtime_error("Index out of range.");
    }
    int atIndex = 0;
    if (index == 0) {
        return this->head;
    } else {
        this->current = this->head->next;
        atIndex++;
        while (atIndex != index) {
            atIndex++;
            this->current = this->current->next;
        }
    }
    return this->current;
}

template <typename T>
T &LinkedList<T>::operator[](unsigned int index) {
    return findAt(index)->data;
}

template <typename T>
const T &LinkedList<T>::operator[](unsigned int index) const {
    return findAt(index)->data;
}

template <typename T>
void LinkedList<T>::AddTail(const T &data) {
    this->tail = new Node;
    this->tail->next = nullptr;
    this->tail->data = data;
    this->numNodes++;
    
    if (this->head != nullptr) {
        this->current = this->head;
        while (this->current->next != nullptr) {
            this->current = this->current->next;
        }
        this->current->next = this->tail;
        this->tail->prev = this->current;
    } else {
        this->head = this->tail;
    }
}

template <typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {
    if ((int)index >= this->numNodes || index < 0) {
        throw runtime_error("Index out of range.");
    }
    if (index == 0) {
        AddHead(data);
    } else {
        this->current = findAt(index);
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = this->current;
        newNode->prev = this->current->prev;
        this->current = newNode;
    }
    this->numNodes++;
}

template <typename T>
int LinkedList<T>::getNodeIndex(Node* node) {
    Node* temp = new Node;
    int atIndex = 0;
    if (node == this->head) {
        return atIndex;
    } else {
        temp = this->head;
        this->current = this->head->next;
        atIndex++;
        while (this->current != node) {
            atIndex++;
            temp->prev = temp;
            temp = temp->next;
            this->current = this->current->next;
        }
    }
    delete temp;
    return atIndex;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T &data) {
    if (node == this->head) {
        AddHead(data);
    } else {
        InsertAt(data, getNodeIndex(node));
    }
    this->numNodes++;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T &data) {
    Node* temp = new Node;
    temp->data = data;
    temp->next = nullptr;
    if (node == this->tail) {
        temp = this->tail;
        this->tail->data = data;
        this->tail->next = nullptr;
        this->tail->prev = temp;
        temp->next = this->tail;
    } else {
        this->current = node;
        temp->next = this->current->next;
        this->current->next = temp;
        temp->prev = this->current;
        this->current->next->prev = temp;
    }
    this->numNodes++;
}

template <typename T>
bool LinkedList<T>::RemoveAt(int index) {
    try {
        this->current = findAt(index);
        this->current->prev->next = this->current->next;
        this->current = this->current->prev->next;
        this->numNodes--;
        return true;
    } catch (const runtime_error &e) {
        return false;
    }
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T &data) {
    unsigned int count = 0;
    Node* temp = new Node;
    Node* prev = new Node;
    temp = this->head;
    prev = nullptr;
    
    while (temp != nullptr && temp->data == data) {
        this->head = temp->next;
        temp = this->head;
    }
    
    while (temp != nullptr) {
        while (temp != nullptr && temp->data != data) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != nullptr) {
            prev->next = temp->next;
            temp = prev->next;
            this->numNodes--;
            count++;
        }
    }
    delete temp;
    delete prev;
    return count;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
    if (this->head != nullptr) {
        this->numNodes--;
        this->head = this->head->next;
        if (this->head != nullptr) {
            this->head->prev = nullptr;
        }
        return true;
    }
    return false;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
    if (this->tail != nullptr) {
        this->numNodes--;
        this->tail = this->tail->prev;
        if (this->tail != nullptr) {
            this->tail->next = nullptr;
        }
        return true;
    }
    return false;
}


template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* temp = new Node;
    temp = this->head;
    if (temp == nullptr) {
        throw runtime_error("List is empty!");
    } else {
        while (temp != nullptr) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
    delete temp;
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
    Node* prev = nullptr;
    Node* current = this->head;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    if (prev == nullptr) {
        throw runtime_error("List is empty!");
    } else {
        while (prev != nullptr) {
            cout << prev->data << endl;
            prev = prev->next;
        }
    }
    delete current;
    delete next;
    delete prev;
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
    while (node->next != nullptr) {
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const{
    while (node->prev != nullptr) {
        cout << node->data << endl;
        PrintForwardRecursive(node->prev);
    }
}

template <typename T>
void LinkedList<T>::AddHead(const T &data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = this->head;
    this->head = newNode;
    this->numNodes++;
    if (numNodes == 1) {
        this->tail = this->head;
    }
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {
    for (int i = count - 1; i >= 0; i--) {
        AddHead(data[i]);
    }
    this->numNodes += count;
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        AddTail(data[i]);
    }
    this->numNodes += count;
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return this->numNodes;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*> &outData, const T &value) const {
    Node* temp = new Node;
    temp = this->head;
    while (temp != nullptr) {
        if (temp->data == value) {
            outData.push_back(temp);
        }
        temp = temp->next;
    }
    delete temp;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) const {
    return Find(data);
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) {
    this->current = this->head;
    while (this->current->next != nullptr) {
        if (this->current->data == data) {
            return this->current;
        }
        this->current = this->current->next;
        this->current->prev = this->current;
    }
    return this->current;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    return findAt(index);
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    return findAt(index);
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return this->head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return this->head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return this->tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return this->tail;
}

