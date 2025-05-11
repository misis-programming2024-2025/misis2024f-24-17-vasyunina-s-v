#include <iostream>
#include <string>
#include "hash_table.hpp"

int main() {
    HashTable<std::string, int> table(10);

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);
    table.insert("four", 4);


    std::cout << "Contains 'two': " << table.contains("two") << std::endl;
    std::cout << "Contains 'five': " << table.contains("five") << std::endl;

    table.insert("two", 22);

    table["five"] = 5;
    table["one"] = 11; 

    std::cout << "\nAll elements in the table:" << std::endl;
    for (const auto& pair : table) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::cout << "\nUsing explicit iterators:" << std::endl;
    for (auto it = table.begin(); it != table.end(); ++it) {
        auto pair = *it;
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    HashTable<std::string, int> empty_table(0);
    empty_table.insert("test_key", 42);

    return 0;
}