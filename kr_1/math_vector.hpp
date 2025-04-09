#include <iostream>
#include <initializer_list>
#include <stdexcept>


template <int capacity>
class MathVector {
public:
    MathVector();
    MathVector(const MathVector& other);
    ~MathVector();

    int getSize() const;
    int getFront() const;
    int getBack() const;

    int* begin();
    int* end();

    void push_back(int value); 
    int& at(int i) const; 
    bool empty() const; 
    void replace_at(int i, int value) const;

    int& operator[](int i) const; 
    bool operator==(const MathVector& rhs) const;
    bool operator!=(const MathVector& rhs) const;

private:
    int size_ = 0;
    int* begin_ = nullptr;
};


template <int capacity>
MathVector<capacity>::MathVector() : size_(0){
    if (capacity > 0){
        begin_ = new int[capacity];
    }
    else{
        begin_ = nullptr;
    }
}

template <int capacity>
MathVector<capacity>::MathVector(const MathVector& other) : size_(other.size_), begin_(new int[capacity]) {
    if (size_ > 0) {
        std::copy(other.begin_, other.begin_ + size_, begin_);
    } else {
        begin_ = nullptr;
    }
}

template <int capacity>
MathVector<capacity>::~MathVector(){
    delete[] begin_;
}

template <int capacity>
bool MathVector<capacity>::empty() const {
    return (size_ ==  0);
}

template <int capacity>
int MathVector<capacity>::getSize() const{
    return size_;
}

template <int capacity>
int& MathVector<capacity>::at(int i) const{
    if (i < 0 || i > size_) {
        throw std::out_of_range("Index out of range");
    }
    return *(begin_ + i);
}

template <int capacity>
int MathVector<capacity>::getBack() const {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    return *(begin_ + size_);
}

template <int capacity>
int MathVector<capacity>::getFront() const {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    return *begin_;
}

template <int capacity>
void MathVector<capacity>::push_back(int value){
    if (size_ >= capacity){
        throw std::out_of_range("Vector is full");
    }
    begin_[size_] = value;
    size_++;
}

template <int capacity>
void MathVector<capacity>::replace_at(int i, int value) const {
    if (i < 0 || i > size_) {
        throw std::out_of_range("Index out of range");
    }
    begin_[i] = value;
}

template <int capacity>
int* MathVector<capacity>::begin(){
    return begin_;
}

template <int capacity>
int* MathVector<capacity>::end(){
    return (begin_ + size_);
}

template <int capacity>
int& MathVector<capacity>::operator[](int i) const{
    if (i < 0 || i > size_) {
        throw std::out_of_range("Index out of range");
    }
    return *(begin_ + i);
}

template <int capacity>
bool MathVector<capacity>::operator==(const MathVector& rhs) const{
    if (size_ != rhs.size_) return false;
    for (int i = 0; i < size_; ++i) {
        if (begin_[i] != rhs.begin_[i]) return false;
    }
    return true;
}

template <int capacity>
bool MathVector<capacity>::operator!=(const MathVector& rhs) const{
    return !(*this == rhs);
}


