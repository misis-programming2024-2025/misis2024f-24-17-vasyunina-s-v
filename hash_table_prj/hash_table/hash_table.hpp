#include <iostream>


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

    void insert(const KeyType& key, const ValueType& value);
    bool contains(const KeyType& key) const;
    ValueType& operator[](const KeyType& key)

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


    Iterator begin() const;
    Iterator end() const;

    };
};
