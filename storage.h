#include <stdexcept>

#ifndef OOP_LAB_3_STORAGE_STORAGE_H
#define OOP_LAB_3_STORAGE_STORAGE_H

template<typename T>
class Node;

template<typename T>
class Storage {
public:
    Storage();
    Storage(const Storage<T> &storage);
    ~Storage();

    T &getCurrent();
    T popCurrent();

    void addBefore(T value);
    void addAfter(T value);

    void addFront(T value);
    void addBack(T value);

    void prev();
    void next();

    void prevN(int n);
    void nextN(int n);

    bool isEnd();
    bool isStart();

    void toFirst();
    void toLast();

protected:
    Node<T> *firstNode;
    Node<T> *currentNode;
    Node<T> *lastNode;
};

template<typename T>
class Node {
private:
    explicit Node(const T &val) : value(val), next(0), prev(0) {}

    Node *next = nullptr;
    Node *prev = nullptr;
    T value;

    friend class Storage<T>;
};

template<typename T>
Storage<T>::Storage(): firstNode(0), currentNode(0), lastNode(0) {}

template<typename T>
Storage<T>::Storage(const Storage<T> &storage): Storage() {
    for (storage.toFirst(); storage.isEnd(); storage.next()) {
        this->addBack(storage.getCurrent());
    }
}

template<typename T>
Storage<T>::~Storage() {
    Node<T> *first = firstNode;
    while (first != 0) {
        Node<T> *next = first->next;
        delete first;
        first = next;
    }
}

template<typename T>
T &Storage<T>::getCurrent() {
    if (currentNode != 0) {
        return currentNode->value;
    }

    throw std::out_of_range("no elements are available");
}

template<typename T>
T Storage<T>::popCurrent() {
    if (currentNode != 0) {
        if (currentNode->prev != 0)
            currentNode->prev->next = currentNode->next;
        if (currentNode->next != 0)
            currentNode->next->prev = currentNode->prev;

        if (currentNode == firstNode)
            firstNode = currentNode->next;
        if (currentNode == lastNode)
            lastNode = currentNode->prev;

        auto value = currentNode->value;
        delete currentNode;

        this->toFirst();

        return value;
    }

    throw std::out_of_range("no elements are available");
}

template<typename T>
void Storage<T>::addBefore(T value) {
    if (currentNode != 0) {
        auto newNode = new Node<T>(value);

        newNode->prev = currentNode->prev;
        newNode->next = currentNode;

        if (currentNode->prev != 0)
            currentNode->prev->next = newNode;
    } else {
        this->addFront(value);
    }
}

template<typename T>
void Storage<T>::addAfter(T value) {
    if (currentNode != 0) {
        auto newNode = new Node<T>(value);

        newNode->next = currentNode->next;
        newNode->prev = currentNode;

        if (currentNode->next != 0)
            currentNode->next->prev = newNode;
    } else {
        this->addBack(value);
    }
}

template<typename T>
void Storage<T>::addFront(T value) {
    auto newNode = new Node<T>(value);
    if (firstNode == 0) {
        firstNode = lastNode = newNode;
    } else {
        newNode->next = firstNode;
        firstNode->prev = newNode;
        firstNode = newNode;
    }
}

template<typename T>
void Storage<T>::addBack(T value) {
    auto newNode = new Node<T>(value);
    if (lastNode == 0) {
        lastNode = firstNode = newNode;
    } else {
        newNode->prev = lastNode;
        lastNode->next = newNode;
        lastNode = newNode;
    }
}

template<typename T>
void Storage<T>::prev() {
    if (currentNode == 0)
        currentNode = lastNode;
    else
        currentNode = currentNode->prev;
}

template<typename T>
void Storage<T>::next() {
    if (currentNode == 0)
        currentNode = firstNode;
    else
        currentNode = currentNode->next;
}

template<typename T>
void Storage<T>::prevN(int n) {
    for (int i = 0; i < n && this->isStart(); i++, this->prev());
}

template<typename T>
void Storage<T>::nextN(int n) {
    for (int i = 0; i < n && this->isEnd(); i++, this->next());
}

template<typename T>
bool Storage<T>::isEnd() {
    return currentNode == 0;
}

template<typename T>
bool Storage<T>::isStart() {
    return currentNode == 0;
}

template<typename T>
void Storage<T>::toFirst() {
    currentNode = firstNode;
}

template<typename T>
void Storage<T>::toLast() {
    currentNode = lastNode;
}

#endif //OOP_LAB_3_STORAGE_STORAGE_H
