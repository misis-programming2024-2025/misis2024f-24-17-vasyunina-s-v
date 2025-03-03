#include "dynamic_array.hpp"
#include <iostream>

//конструктор
DynamicArray::DynamicArray(int64_t size, int value) : size(size), capacity(size) {
    if (size > 0) {
        data = new int[size];
        std::fill(data, data + size, value);
    } else {
        data = nullptr;
    }
}

//заполнение массива элементами переданными списком по ссылке
DynamicArray::DynamicArray(const std::initializer_list<int>& list) : size(list.size()), capacity(list.size()){
    if (size > 0) {
        data = new int[size];
        std::copy(list.begin(), list.end(), data);
    } else {
        data = nullptr;
    }
}

//конструктор копирования
DynamicArray::DynamicArray(const DynamicArray& other)  : size(other.size), capacity(other.capacity){
    if (size > 0) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
    } else {
        data = nullptr;
    }
}

//деструктор, очищаем память
DynamicArray::~DynamicArray(){
    delete[] data;
}


//возвращаем размер массива
int64_t DynamicArray::Size() const{
    return size;
};

//возвращаем capacity
int64_t DynamicArray::Capacity() const {
    return capacity;
};

//проверка на пустоту
bool DynamicArray::empty() const{
    return (size == 0);
}; 

//добавление в конец массива
void DynamicArray::push_back(int value){
    if (size != capacity){
        *(data + 1) = value;
    } else {
        capacity = capacity * 2;
        int* new_data = new int[capacity];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        *(data + 1) = value;
    }
}

//удаление с конца массива
void DynamicArray::pop_back(){
    if (size > 0) {
        size -= 1;
    }
} 

//чистим массив
void DynamicArray::clear(){
    size = 0;
}

//удаление элемента по индексу
void DynamicArray::erase(int64_t index){
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    for (int64_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size -= 1;
}

//изменение размера массива
void DynamicArray::resize(int64_t new_size){
    if (new_size > capacity){
        int* new_data = new int[new_size];
        capacity = new_size;
        std::copy(data, data + size, new_data);
        std::fill(new_data + size, new_data + new_size, 0);
        delete[] data;
        data = new_data;
    }
    size = new_size;
}


//меняется размер масиива и он заполняется value
void DynamicArray::assign(int64_t new_size, int value){
    if (new_size > capacity) {
        capacity = new_size;
        delete[] data;
        data = new int[capacity];
    }
    size = new_size;
    std::fill(data, data + size, value);
}

//вставка элемента по индексу
void DynamicArray::insert(int64_t index, const int value){
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of range");
    } else {
        push_back(0);
        for (int64_t i = size - 1; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
    }
}


//меняем местами два массива
void DynamicArray::swap(DynamicArray& other){
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

int* DynamicArray::begin(){
    return data;
}

int* DynamicArray::end(){
    return data + size;
}

//доступ по индексу
int& DynamicArray::at(int64_t i) const{
    if (i < 0 || i > size) {
        throw std::out_of_range("Index out of range");
    }
    return *(data + i);
}

//доступ по индексу, нет проверки выхода за границы массива
int& DynamicArray::operator[](int64_t i) const{
    return *(data + i);
}

//присваивание другого массива
DynamicArray& DynamicArray::operator=(const DynamicArray& rhs){
    delete[] data;
    size = rhs.size;
    capacity = rhs.capacity;
    data = new int[capacity];
    std::copy(rhs.data, rhs.data + size, data);
    return *this;
}

//проверка на равенство массивов
bool DynamicArray::operator==(const DynamicArray& rhs) const{
    if (size != rhs.size) return false;
    for (int64_t i = 0; i < size; ++i) {
        if (data[i] != rhs.data[i]) return false;
    }
    return true;
}

//проверка на неравенство массивов
bool DynamicArray::operator!=(const DynamicArray& rhs) const{
    return !(*this == rhs);
}