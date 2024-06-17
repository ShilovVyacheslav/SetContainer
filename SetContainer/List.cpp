#include "List.h"

Node::Node(void* elem, size_t elemSize) : data(elem), data_size(elemSize), next(nullptr) {}
Node::~Node() {}

List::List(MemoryManager& _memory) : AbstractList(_memory), head(nullptr), list_size(0) {}
List::~List() { clear(); }

List::ListIterator::ListIterator(Node* ptr) : current(ptr) {}
List::ListIterator::~ListIterator() {}
void* List::ListIterator::getElement(size_t& size) {
    if (current == nullptr) {
        size = 0;
        return nullptr;
    }
    size = current->data_size;
    return current->data;
}
bool List::ListIterator::hasNext() {
    return current && current->next;
}
void List::ListIterator::goToNext() {
    if (current != nullptr) {
        current = current->next;
    }
}
bool List::ListIterator::equals(Iterator* right) {
    ListIterator* right_it = dynamic_cast<ListIterator*>(right);
    if (right_it == nullptr) {
        return false;
    }
    return (current == right_it->current);
}

int List::insert(Iterator* iter, void* elem, size_t elemSize) {
    ListIterator* it = dynamic_cast<ListIterator*>(iter);
    if (it == nullptr) { return 1; }

    void* new_elem = static_cast<void*>(new(_memory) char[elemSize]);
    if (new_elem == nullptr) { return 1; }
    memcpy(new_elem, elem, elemSize);
    Node* new_node = new(_memory) Node(new_elem, elemSize);
    if (new_node == nullptr) { return 1; }

    Node* current_node = it->current;
    Node* next_node = current_node->next;
    current_node->next = new_node;
    new_node->next = next_node;
    ++list_size;

    return 0;
}
int List::push_front(void* elem, size_t elemSize) {
    void* new_elem = static_cast<void*>(new(_memory) char[elemSize]);
    if (new_elem == nullptr) { return 1; }
    memcpy(new_elem, elem, elemSize);
    Node* new_node = new(_memory) Node(new_elem, elemSize);
    if (new_node == nullptr) { return 1; }

    new_node->next = head;
    head = new_node;
    ++list_size;

    return 0;
}
void List::pop_front() {
    if (head != nullptr) {
        Node* tmp = head;
        head = tmp->next;
        operator delete(tmp->data, _memory);
        operator delete(tmp, _memory);
        tmp = nullptr;
        --list_size;
    }
}
void* List::front(size_t& size) {
    if (head == nullptr) {
        size = 0;
        return nullptr;
    }
    size = head->data_size;
    return head->data;
}
int List::size() {
    return list_size;
}
size_t List::max_bytes() {
    return _memory.maxBytes();
}
AbstractList::Iterator* List::find(void* elem, size_t size) {
    Node* current_node = head;
    while (current_node != nullptr) {
        if (memcmp(current_node->data, elem, size) == 0) {
            return new(_memory) ListIterator(current_node);
        }
        current_node = current_node->next;
    }
    return nullptr;
}
AbstractList::Iterator* List::newIterator() {
    return new(_memory) ListIterator(head);
}
void List::remove(Iterator* iter) {
    ListIterator* it = dynamic_cast<ListIterator*>(iter);
    if (it == nullptr) { return; }

    Node* previous_node = nullptr;
    Node* current_node = head;
    while (current_node && (current_node != it->current)) {
        previous_node = current_node;
        current_node = current_node->next;
    }

    if (current_node) {
        if (previous_node) {
            previous_node->next = current_node->next;
        }
        else {
            head = current_node->next;
        }
        operator delete(current_node->data, _memory);
        operator delete(current_node, _memory);
        current_node = nullptr;
        --list_size;
    }
}
void List::clear() {
    while (!empty()) {
        pop_front();
    }
}
bool List::empty() {
    return list_size == 0;
}
ostream& operator<<(ostream& out, List& lst) {
    List::ListIterator* it = dynamic_cast<List::ListIterator*>(lst.newIterator());
    if (it == nullptr) { return out; }
    void* data; size_t data_size;

    if (it->getElement(data_size) != nullptr) {
        data = it->getElement(data_size);
        out << *(static_cast<int*>(data)) << " ";
        while (it->hasNext()) {
            it->goToNext();
            data = it->getElement(data_size);
            out << *(static_cast<int*>(data)) << " ";
        }
    }

    operator delete(it, lst._memory);
    it = nullptr;
    return out;
}