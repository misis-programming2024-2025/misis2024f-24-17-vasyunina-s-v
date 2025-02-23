#include <initializer_list>
#include <cstdint>
#include <algorithm>
#include <iostream>

class DynamicArray {
    public:
        DynamicArray(int64_t size = 0, int value = 0);

        // {1, 2, 3, 4, 5}
        DynamicArray(const std::initializer_list<int>& list);

        DynamicArray(const DynamicArray& other);
        ~DynamicArray();

        // геттеры
        int64_t Size() const;
        int64_t Capacity() const;
        bool empty() const; 

        void push_back(int value); 
        void pop_back(); 
        void clear(); 
        void erase(int64_t index);
        // 1, 2, 3 -> 1, 2, 3, 0 ,0, 
        void resize(int64_t new_size); 
        // 1, 2, 3 -> value, value, value, value, 
        void assign(int64_t new_size, int value); 
        // 1, 2, 3,  -> 1, value, 2, 3, 
        void insert(int64_t index, const int value); 

        void swap(DynamicArray& other); 

        int* begin();
        int* end();

        int& at(int64_t i) const; 
        int& operator[](int64_t i) const; 

        DynamicArray& operator=(const DynamicArray& rhs); 

        // size == и все элементы, не capacity
        bool operator==(const DynamicArray& rhs) const;
        bool operator!=(const DynamicArray& rhs) const;
    private:
        int64_t size = 0;
        int64_t capacity = 0;
        int* data = nullptr;
}; 
