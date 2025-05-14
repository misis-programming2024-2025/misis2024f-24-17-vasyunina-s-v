#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <stack_base.hpp>


template <typename T>
class StackArrT: public IStackBase<T> {
public:
	StackArrT();
	~StackArrT();
	StackArrT(const StackArrT<T>& other);
	StackArrT(StackArrT<T>&& other); //move
	StackArrT(const std::initializer_list<T>& list);

	void push(const T& value) override;
	void pop() override;
	T& top() const override;
	bool empty() const override;
	std::ptrdiff_t size() const override;
    void clear();
	StackArrT<T>& operator=(const StackArrT<T>& rhs) noexcept;
	StackArrT<T>& operator=(StackArrT<T>&& other);
    std::ostream& printToStream(std::ostream& os) const override;

    void swap(IStackBase<T>& other) override;
    void merge(IStackBase<T>& other) override;
    bool operator==(const IStackBase<T>& rhs) const override;
    bool operator!=(const IStackBase<T>& rhs) const override;
private:
    std::ptrdiff_t size_ = 0;   //!< число элементов в буфере
    std::ptrdiff_t i_top_ = -1; //!< индекс top элемента
    T* data_ = nullptr;   //!< элементы стека
};



template <typename T>
StackArrT<T>::StackArrT(): size_(0), i_top_(-1), data_(nullptr) {}

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
bool StackArrT<T>::empty() const {
        return i_top_ == -1;
    }


template <typename T>
std::ptrdiff_t StackArrT<T>::size() const {
        return size_;
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
std::ostream& StackArrT<T>::printToStream(std::ostream& os) const {
    for (std::ptrdiff_t i = 0; i <= i_top_; ++i) {
        os << data_[i] << " ";
      }
      return os;
}

template <typename T>
void StackArrT<T>::clear() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    i_top_ = -1;
}

template <typename T>
void StackArrT<T>::swap(IStackBase<T>& other) {
    auto* derived = dynamic_cast<StackArrT<T>*>(&other);
    if (derived) {
        std::swap(size_, derived->size_);
        std::swap(i_top_, derived->i_top_);
        std::swap(data_, derived->data_);
    }
}

template <typename T>
void StackArrT<T>::merge(IStackBase<T>& other) {
    auto* derived = dynamic_cast<StackArrT<T>*>(&other);
    if (!derived) return;
    
    T* new_data = new T[size_ + derived->size_];
    std::copy(data_, data_ + size_, new_data);
    std::copy(derived->data_, derived->data_ + derived->size_, new_data + size_);
    
    delete[] data_;
    data_ = new_data;
    size_ += derived->size_;
    i_top_ = size_ - 1;
    
    derived->size_ = 0;
    derived->i_top_ = -1;
    delete[] derived->data_;
    derived->data_ = nullptr;
}

template <typename T>
bool StackArrT<T>::operator==(const IStackBase<T>& rhs) const {
    const auto* derived = dynamic_cast<const StackArrT<T>*>(&rhs);
    if (!derived || size_ != derived->size_) return false;
    
    for (std::ptrdiff_t i = 0; i <= i_top_; ++i) {
        if (data_[i] != derived->data_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool StackArrT<T>::operator!=(const IStackBase<T>& rhs) const {
    return !(*this == rhs);
}