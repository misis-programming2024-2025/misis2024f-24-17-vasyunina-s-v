#include <iostream>

template <typename T>
class IStackBase {
public:
    IStackBase() = default;
    virtual ~IStackBase() = default;
    IStackBase(const IStackBase<T>& other) =  delete;
	IStackBase(IStackBase<T>&& other) =  delete; 
	IStackBase(const std::initializer_list<T>& list) =  delete;

    virtual void push(const T& value) = 0;
    virtual void pop() = 0;
    virtual T& top() const = 0;
    virtual std::ptrdiff_t size() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;
    virtual std::ostream& printToStream(std::ostream& os) const = 0;
    virtual void swap(IStackBase<T>& other) = 0;
	virtual void merge(IStackBase<T>& other) = 0;

    virtual bool operator==(const IStackBase<T>&  rhs) const = 0;
	virtual bool operator!=(const IStackBase<T>& rhs) const = 0;
	IStackBase<T>& operator=(const IStackBase<T>&  rhs) noexcept =  delete;
	IStackBase<T>& operator=(IStackBase<T>& other) =  delete;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const IStackBase<T>& stack) {
    stack.printToStream(os);
    return os;
}
