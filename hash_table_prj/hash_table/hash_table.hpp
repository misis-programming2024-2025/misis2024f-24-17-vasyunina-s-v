#include <iostream>
#include <vector>
#include <functional>
#include <utility>


template<typename KeyType, typename ValueType>
class HashTable {
private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* next;
        Node(const KeyType& k, const ValueType& v) : key(k), value(v), next(nullptr) {}
    };

    std::vector<Node*> table;
    std::hash<KeyType> hash_function;

public:
    HashTable(size_t size = 0);  
    ~HashTable();

    void insert(const KeyType& key, const ValueType& value);
    bool contains(const KeyType& key) const;
    ValueType& operator[](const KeyType& key);

    class Iterator {
    private:
        size_t index;
        Node* current;
        const std::vector<Node*>& table;

    public:
        Iterator(size_t i, Node* node, const std::vector<Node*>& tbl);
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
        std::pair<const KeyType&, ValueType&> operator*() const;
    };

    Iterator begin() const;
    Iterator end() const;
};


template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(size_t size) : table(size, nullptr) {}


template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
    for (auto& bucket : table) {
        while (bucket) {
            Node* temp = bucket;
            bucket = bucket->next;
            delete temp;
        }
    }
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    if (table.empty()) {
        table.resize(16, nullptr);
    }

    size_t index = hash_function(key) % table.size();
    Node* current = table[index];
    
    while (current) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    Node* newNode = new Node(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::contains(const KeyType& key) const {
    size_t index = hash_function(key) % table.size();
    Node* current = table[index];
    
    while (current) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename KeyType, typename ValueType>
ValueType& HashTable<KeyType, ValueType>::operator[](const KeyType& key) {
    size_t index = hash_function(key) % table.size();
    Node* current = table[index];
    
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    
    Node* newNode = new Node(key, ValueType());
    newNode->next = table[index];
    table[index] = newNode;
    return newNode->value;
}



template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::Iterator::Iterator(
    size_t i, 
    typename HashTable<KeyType, ValueType>::Node* node,
    const std::vector<typename HashTable<KeyType, ValueType>::Node*>& tbl
) : index(i), current(node), table(tbl) {}


template<typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator& 
HashTable<KeyType, ValueType>::Iterator::operator++() {
    if (current) {
        current = current->next;  // Переход к следующему узлу в текущей корзине
        if (!current) {
            // Поиск следующей непустой корзины
            for (++index; index < table.size() && !table[index]; ++index) {}
            current = (index < table.size()) ? table[index] : nullptr;
        }
    }
    return *this;
}

template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::Iterator::operator!=(const Iterator& other) const {
    return index != other.index || current != other.current;
}

template<typename KeyType, typename ValueType>
std::pair<const KeyType&, ValueType&> HashTable<KeyType, ValueType>::Iterator::operator*() const {
    return {current->key, current->value};
}

template<typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator 
HashTable<KeyType, ValueType>::begin() const {
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i] != nullptr) {
            return Iterator(i, table[i], table);
        }
    }
    return end();
}

template<typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator 
HashTable<KeyType, ValueType>::end() const {
    return Iterator(table.size(), nullptr, table);
}