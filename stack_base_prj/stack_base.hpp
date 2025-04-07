#include <iostream>

template <typename T>
class IStackBase {
public:
    IStackBase() = 0;
    virtual ~IStackBase() = default;
    IStackBase(const IStackBase<T>& other) = 0;
	IStackBase(IStackBase<T>&& other) = 0; 
	IStackBase(const std::initializer_list<T>& list) = 0;

    virtual void push(const T& value) = 0;
    virtual void pop() = 0;
    virtual T& top() const = 0;
    std::ptrdiff_t size() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;
    virtual void printToStream(std::ostream& os) const = 0;
    void swap(IStackBase<T>& other) = 0;
	void merge(IStackBase<T>& other) = 0;

    bool operator==(const IStackBase<T>&  rhs) const = 0;
	bool operator!=(const IStackBase<T>& rhs) const = 0;
	IStackBase<T>& operator=(const IStackBase<T>&  rhs) noexcept = 0;
	IStackBase<T>& operator=(IStackBase<T>& & other) = 0;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const IStackBase<T>& stack) {
    stack.PrintToStream(os);
    return os;
}
