template <typename T>
class StackArrT {
public:
	StackArrT();
	~StackArrT();
	StackArrT(const StackArrT<T>& other);
	StackArrT(StackArrT<T>&& other);
	StackArrT(const std::initializer_list<T>& list);

	void push(const T& value);
	void pop();
	T& top() const;
	void swap(StackArrT<T>& other);
	void merge(StackArrT<T>& other);

	bool empty() const;
	std::ptrdiff_t size() const;

	bool operator==(const StackArrT<T>& rhs) const;
	bool operator!=(const StackArrT<T>& rhs) const;

	StackArrT<T>& operator=(const StackArrT<T>& rhs) noexcept;
	StackArrT<T>& operator=(StackArrT<T>&& other);
private:
    std::ptrdiff_t size_ = 0;   //!< число элементов в буфере
    std::ptrdiff_t i_top_ = -1; //!< индекс top элемента
    T* data_ = nullptr;   //!< элементы стека
};

