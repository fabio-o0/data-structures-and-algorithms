#include <memory>
#include <exception>
#include <iostream>

namespace cop3530 {

template <typename T>
class deque {
    
    struct node {
        // something to point to the next node
        node* next;
        // something to point to the previous node
        node* prev;
        // something to hold a value of type T
        T data;
    };

    // something to hold the head of the list
    node* head;
    // something else?
    node* tail;
    node* curr;
    size_t currSize;

    public:
        deque();
        void push_front(T data);
        void push_back(T data);
        void pop_front();
        void pop_back();
        T front();
        T back();
        size_t size();
        bool empty();
        void print();
};

template <typename T>
deque<T>::deque() {
    this->head = new node;
    this->tail = this->head;
    this->curr = this->head;
    this->currSize = 0;
}

template <typename T>
void deque<T>::push_front(T data) {\
    if (this->currSize == 0) {
        this->head->data = data;
        this->currSize++;
    } else {
        if (this->tail == this->head) {
            this->tail = new node;
            this->tail->data = this->head->data;
            this->tail->prev = this->head;
            this->head->next = this->tail;
            this->head->data = data;
            this->currSize++;
        } else {
            this->currSize++;
            this->curr = new node;
            this->curr->data = data;
            this->curr->next = this->head;
            this->head->prev = this->curr;
            this->head = this->curr;
        }
    }
}

template <typename T>
void deque<T>::push_back(T data) {
    if (this->currSize == 0) {
        this->tail->data = data;
        this->currSize++;
    } else {
        this->currSize++;
        this->curr = new node;
        this->curr->data = data;
        this->curr->prev = this->tail;
        this->tail->next = this->curr;
        this->tail = this->curr;
    }
}

template <typename T>
void deque<T>::pop_front() {
    if (this->currSize == 0) {
        throw std::runtime_error("List is empty.");
    } else {
        if (this->currSize == 1) {
            this->currSize--;
            node* temp = this->head;
            this->head = this->tail = nullptr;
            delete temp;
        } else {
            this->currSize--;
            this->head->next->prev = nullptr;
            node* temp = this->head;
            this->head = this->head->next;
            temp->next = nullptr;
            delete temp;
        }
    }
}

template <typename T>
void deque<T>::pop_back() {
    if (this->currSize == 0) {
        throw std::runtime_error("List is empty.");
    } else {
        if (this->currSize == 1) {
            this->currSize--;
            node* temp = this->head;
            this->head = this->tail = nullptr;
            delete temp;
        } else {
            this->currSize--;
            this->tail->prev->next = nullptr;
            node* temp = this->tail;
            this->tail = this->tail->prev;
            temp->prev = nullptr;
            delete temp;
        }
    }
}

template <typename T>
T deque<T>::front() {
    if (this->currSize == 0) {
        throw std::runtime_error("List is empty.");
    } else {
        return this->head->data;
    }
}

template <typename T>
T deque<T>::back() {
    if (this->currSize == 0) {
        throw std::runtime_error("List is empty.");
    } else {
        return this->tail->data;
    }
}

template <typename T>
size_t deque<T>::size() {
    return this->currSize;
}

template <typename T>
bool deque<T>::empty() {
    return this->currSize == 0;
}

template <typename T>
void deque<T>::print() {
    this->curr = this->head;
    unsigned int count = 1;
    std::cout << "Size: " << this->currSize << std::endl;
    while (this->curr->next != nullptr) {
        std::cout << "Item " << count << ": " << this->curr->data << std::endl;
        count++;
        this->curr = this->curr->next;
    }
    std::cout << "Item " << count << ": " << this->curr->data << std::endl;
}

}
