#include "Set.h"

Set::SetIterator::SetIterator(const Set& set_ref, int _index, bool first_existing) : set_ref(set_ref) {
    if (_index < set_ref.table_size) {
        index = _index;
    }
    else {
        index = 0;
    }
    it = set_ref.table[index]->newIterator();
    if (first_existing) {
        while (set_ref.table[index]->empty()) {
            if ((++index) == set_ref.table_size) { break; }
        }
        operator delete(it, set_ref._memory);
        it = nullptr;
        if (index < set_ref.table_size) {
            it = set_ref.table[index]->newIterator();
        }
    }
}
Set::SetIterator::~SetIterator() { clear(); }
void* Set::SetIterator::getElement(size_t& size) {
    if (it == nullptr) {
        size = 0;
        return nullptr;
    }
    return it->getElement(size);
}
bool Set::SetIterator::hasNext() {
    if (it == nullptr) { return false; }
    if (it->hasNext()) {
        return true;
    }
    int i = index + 1;
    while (i < set_ref.table_size) {
        if (!set_ref.table[i]->empty()) {
            return true;
        }
        ++i;
    }
    return false;
}
void Set::SetIterator::goToNext() {
    if (it == nullptr) { return; }
    if (it->hasNext()) {
        it->goToNext();
    }
    else {
        if (hasNext()) {
            while (set_ref.table[++index]->empty()) {
                continue;
            }
            operator delete(it, set_ref._memory);
            it = set_ref.table[index]->newIterator();
        }
        else {
            it = nullptr;
        }
    }
}
bool Set::SetIterator::equals(Iterator* right) {
    SetIterator* right_iter = dynamic_cast<SetIterator*>(right);
    if (right_iter == nullptr) {
        return false;
    }
    return it->equals(right_iter->it);
}
List* Set::SetIterator::getList() {
    return set_ref.table[index];
}
void Set::SetIterator::clear() {
    operator delete(it, set_ref._memory);
    operator delete(this, set_ref._memory);
}

AbstractSet::Iterator* Set::findByKey(void* key, size_t keySize) {
    const unsigned char* data = static_cast<const unsigned char*>(key);
    size_t hash = 5381;
    for (size_t i = 0; i < keySize; ++i) {
        hash = ((hash << 5) + hash + data[i]) % MOD;
    }
    hash %= table_size;
    return new(_memory) SetIterator(*this, hash, false);
}
int Set::insert(void* elem, size_t size) {
    if (elem == nullptr) { return 0; }

    SetIterator* it = dynamic_cast<SetIterator*>(find(elem, size));
    if (it == nullptr) { return 1; }
    if (it->it != nullptr) {
        it->clear(); it = nullptr;
        return 1;
    }

    List* desired_list = it->getList();
    int flag = desired_list->push_front(elem, size);
    if (flag) { return 2; }

    if (desired_list->size() > 10) {
        rehash();
    }

    it->clear(); it = nullptr;
    return 0;
}
AbstractSet::Iterator* Set::find(void* elem, size_t size) {
    SetIterator* it = dynamic_cast<SetIterator*>(findByKey(elem, size));
    if (it == nullptr) { return nullptr; }
    it->it = it->getList()->find(elem, size);
    return it;
}
AbstractSet::Iterator* Set::newIterator() {
    return new(_memory) SetIterator(*this);
}
void Set::remove(Iterator* iter) {
    SetIterator* it = dynamic_cast<SetIterator*>(iter);
    if (it != nullptr) {
        it->getList()->remove(it->it);
    }
}
void Set::rehash() {
    List** table_tmp = table; int table_size_tmp = table_size;
    void* elem; size_t elemSize;
    table_size <<= 2;
    table = new(_memory) List * [table_size];
    for (int i = 0; i < table_size; ++i) {
        table[i] = new(_memory) List(_memory);
    }
    for (int i = 0; i < table_size_tmp; ++i) {
        while (table_tmp[i]->list_size > 0) {
            elem = table_tmp[i]->front(elemSize);
            SetIterator* it = dynamic_cast<SetIterator*>(findByKey(elem, elemSize));
            it->getList()->push_front(elem, elemSize);
            it->clear(); it = nullptr;
            table_tmp[i]->pop_front();
        }
        operator delete(table_tmp[i], _memory);
        table_tmp[i] = nullptr;
    }
    operator delete(table_tmp, _memory);
    table_tmp = nullptr;
}
ostream& operator<<(ostream& out, Set& st) {
    for (int i = 0; i < st.table_size; ++i) {
        out << *st.table[i] << "\n";
    }
    return out;
}