#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <stack_base.hpp>


template <typename T>
class StackArrT {
public:
	StackArrT();
	~StackArrT();
	StackArrT(const StackArrT<T>& other);
	StackArrT(StackArrT<T>&& other); //move
	StackArrT(const std::initializer_list<T>& list);

	void push(const T& value);
	void pop();
	T& top() const;
	void swap(StackArrT<T>& other);
    // значение второго стека с конца приклеиваются к первому стеку
	void merge(StackArrT<T>& other);

	bool empty() const;
	std::ptrdiff_t size() const;

	bool operator==(const StackArrT<T>& rhs) const;
	bool operator!=(const StackArrT<T>& rhs) const;

	StackArrT<T>& operator=(const StackArrT<T>& rhs) noexcept;
	StackArrT<T>& operator=(StackArrT<T>&& other);
    void PrintToStream(std::ostream& os) const override;
private:
    std::ptrdiff_t size_ = 0;   //!< число элементов в буфере
    std::ptrdiff_t i_top_ = -1; //!< индекс top элемента
    T* data_ = nullptr;   //!< элементы стека
};



template <typename T>
StackArrT<T>::StackArrT() : size_(0), i_top_(-1), data_(nullptr) {}

template <typename T>
StackArrT<T>::~StackArrT() {
        delete[] data_;
    }

template <typename T>
StackArrT<T>::StackArrT(const StackArrT<T>& other): size_(other.size_), i_top_(other.i_top_), data_(new T[other.size_]) {
        for (std::ptrdiff_t i = 0; i <= i_top_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
template <typename T>
StackArrT<T>::StackArrT(StackArrT<T>&& other) : size_(other.size_), i_top_(other.i_top_), data_(other.data_) {
        other.size_ = 0;
        other.i_top_ = -1;
        other.data_ = nullptr;
    }

    
template <typename T>
StackArrT<T>::StackArrT(const std::initializer_list<T>& list): size_(list.size()), i_top_(list.size() - 1), data_(new T[size_]) {
        std::ptrdiff_t index = 0;
        for (const T& val : list) {
            data_[index++] = val;
        }
    }


template <typename T>
void StackArrT<T>::push(const T& value) {
        if (size_ == 0) {
            data_ = new T[1];
            size_ = 1;
        } else {
            T* new_data = new T[size_ + 1];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            size_++;
        }
        i_top_++;
        data_[i_top_] = value;
    }

template <typename T>
void StackArrT<T>::pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        i_top_--;
        size_--;
    }


template <typename T>
T& StackArrT<T>::top() const {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data_[i_top_];
    }


template <typename T>    
void StackArrT<T>::swap(StackArrT<T>& other) {
        std::swap(size_, other.size_);
        std::swap(i_top_, other.i_top_);
        std::swap(data_, other.data_);
    }


template <typename T>
void StackArrT<T>::merge(StackArrT<T>& other) {
        T* new_data = new T[size_ + other.size_];
        std::copy(data_, data_ + size_, new_data);
        std::copy(other.data_, other.data_ + other.size_, new_data + size_);
        delete[] data_;
        data_ = new_data;
        size_ += other.size_;
        i_top_ = size_ - 1;
        other.size_ = 0;
        other.i_top_ = -1;
        delete[] other.data_;
        other.data_ = nullptr;
    }

template <typename T>
bool StackArrT<T>::empty() const {
        return i_top_ == -1;
    }


template <typename T>
std::ptrdiff_t StackArrT<T>::size() const {
        return size_;
    }


template <typename T>
bool StackArrT<T>::operator==(const StackArrT<T>& rhs) const {
        if (size_ != rhs.size_) return false;
        for (std::ptrdiff_t i = 0; i <= i_top_; ++i) {
            if (data_[i] != rhs.data_[i]) return false;
        }
        return true;
    }

template <typename T>
bool StackArrT<T>::operator!=(const StackArrT<T>& rhs) const {
        return !(*this == rhs);
    }


template <typename T>
StackArrT<T>& StackArrT<T>::operator=(const StackArrT<T>& rhs) noexcept {
        if (this == &rhs) return *this;

        delete[] data_;
        size_ = rhs.size_;
        i_top_ = rhs.i_top_;
        data_ = new T[size_];
        for (std::ptrdiff_t i = 0; i <= i_top_; ++i) {
            data_[i] = rhs.data_[i];
        }
        return *this;
    }


template <typename T>
StackArrT<T>& StackArrT<T>::operator=(StackArrT<T>&& other) {
        if (this == &other) return *this;

        delete[] data_;
        size_ = other.size_;
        i_top_ = other.i_top_;
        data_ = other.data_;

        other.size_ = 0;
        other.i_top_ = -1;
        other.data_ = nullptr;

        return *this;
    }

    
template <typename T>
void StackArrT<T>::PrintToStream(std::ostream& os) const {
    for (auto it = data_.rbegin(); it != data_.rend(); ++it) {
        os << *it << " ";
    }
}
