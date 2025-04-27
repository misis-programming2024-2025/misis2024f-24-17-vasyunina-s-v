#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class StackLstT: public IStackBase<T> {
public:
    StackLstT();
    ~StackLstT();
    StackLstT(const StackLstT<T>& other);
    StackLstT(StackLstT<T>&& other);
    StackLstT(const std::initializer_list<T>& list);
  
    void push(const T& value);
    void pop();
    T& top() const;
    void swap(StackLstT<T>& other);
    void merge(StackLstT<T>& other);
  
    bool empty() const;
    std::ptrdiff_t size() const;
    void clear();

    bool operator==(const StackLstT<T>& rhs) const;
    bool operator!=(const StackLstT<T>& rhs) const;

    StackLstT<T>& operator=(const StackLstT<T>& rhs) noexcept;
    StackLstT<T>& operator=(StackLstT<T>&& other);
    std::ostream& printToStream(std::ostream& os) const override;

    void swap(IStackBase<T>& other) override;
    void merge(IStackBase<T>& other) override;
    bool operator==(const IStackBase<T>& rhs) const override;
    bool operator!=(const IStackBase<T>& rhs) const override;

private:
    struct Node {
        T value;
        Node* next = nullptr;
    };

    Node* head_ = nullptr;  
};


template <typename T>
StackLstT<T>::StackLstT() : head_(nullptr) {}

template <typename T>
StackLstT<T>::~StackLstT() {
    while (head_ != nullptr){
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
    }
}

template <typename T>
StackLstT<T>::StackLstT(const StackLstT<T>& other) : head_(nullptr){
    Node* tail = nullptr; //указатель на хвост новго списка
    Node* current = other.head_; //указатель для обхода текущего списка
    while (current != nullptr) {
        Node* newNode = new Node{current->value};
        if (tail == nullptr) {
            head_ = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;  
        current = current->next;
    }
}

template <typename T>
StackLstT<T>::StackLstT(StackLstT<T>&& other) : head_(other.head_) {
    other.head_ = nullptr;
}

template <typename T>
StackLstT<T>::StackLstT(const std::initializer_list<T>& list) : head_(nullptr){
     for (auto it = list.begin(); it != list.end(); ++it) {
        head_ = new Node{*it, head_};  
    }
}

template <typename T>
void StackLstT<T>::push(const T& value) {
    head_ = new Node{value, head_};
}

template <typename T>
void StackLstT<T>::pop(){
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    Node* temp = head_;
    head_ = head_->next;
    delete temp;
}

template <typename T>
T& StackLstT<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return head_->value;
}

template <typename T>
void StackLstT<T>::swap(StackLstT<T>& other) {
    std::swap(head_, other.head_);
}

template <typename T>
void StackLstT<T>::merge(StackLstT<T>& other) {
    if (this == &other) {
        return; // merge самого себя
    }

    if (other.head_ == nullptr) {
        return; // нечего мержить
    }
    Node* last = head_;
    if (last != nullptr) {
        while (last->next != nullptr) {
                last = last->next;
        }
            // Присоединяем другой стек
        last->next = other.head_;
    } else {
            // Если текущий стек пуст, просто берем другой стек
        head_ = other.head_;
    }
    other.head_ = nullptr;
}

template <typename T>
bool StackLstT<T>::empty() const {
    return head_ == nullptr;
}

template <typename T>
std::ptrdiff_t StackLstT<T>::size() const {
    std::ptrdiff_t size = 0;
    Node* current = head_;
    while (current != nullptr) {
        ++size;
        current = current->next;
    }
    return size;
}

template <typename T>
bool StackLstT<T>::operator==(const StackLstT<T>& rhs) const {
    Node* current1 = head_;
    Node* current2 = rhs.head_;
    while (current1 != nullptr && current2 != nullptr) {
        if (current1->value != current2->value) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return current1 == nullptr && current2 == nullptr;
}

template <typename T>
bool StackLstT<T>::operator!=(const StackLstT<T>& rhs) const {
    return !(*this == rhs);
}

template <typename T>
StackLstT<T>& StackLstT<T>::operator=(const StackLstT<T>& rhs) noexcept {
    if (this != &rhs) {
        StackLstT<T> temp(rhs);
        swap(temp);
    }
    return *this;
}

template <typename T>
StackLstT<T>& StackLstT<T>::operator=(StackLstT<T>&& other) {
    if (size() != other.size()) return false;
    
    Node* curr1 = head_;
    Node* curr2 = other.head_;
    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->value != curr2->value) return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    return true;
}


template <typename T>
std::ostream& StackLstT<T>::printToStream(std::ostream& os) const {
    Node* current = head_;
        while (current) {
            os << current->value << " ";
            current = current->next;
        }
        return os;
}

template <typename T>
void StackLstT<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template <typename T>
void StackLstT<T>::swap(IStackBase<T>& other) {
    auto* derived = dynamic_cast<StackLstT<T>*>(&other);
    if (derived) {
        std::swap(head_, derived->head_);
    }
}

template <typename T>
void StackLstT<T>::merge(IStackBase<T>& other) {
    auto* derived = dynamic_cast<StackLstT<T>*>(&other);
    if (!derived || this == &other) return;
    
    if (derived->head_ == nullptr) return;
    
    if (head_ == nullptr) {
        head_ = derived->head_;
    } else {
        Node* last = head_;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = derived->head_;
    }
    derived->head_ = nullptr;
}

template <typename T>
bool StackLstT<T>::operator==(const IStackBase<T>& rhs) const {
    const auto* derived = dynamic_cast<const StackLstT<T>*>(&rhs);
    if (!derived) return false;
    
    Node* current1 = head_;
    Node* current2 = derived->head_;
    while (current1 != nullptr && current2 != nullptr) {
        if (current1->value != current2->value) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return current1 == nullptr && current2 == nullptr;
}

template <typename T>
bool StackLstT<T>::operator!=(const IStackBase<T>& rhs) const {
    return !(*this == rhs);
}