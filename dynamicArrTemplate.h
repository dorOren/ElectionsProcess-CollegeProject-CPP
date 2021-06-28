#include "ProgramCasing.h"

namespace elections {

	template <class W>
	void myswap(W& a, W& b)
	{
		W temp = a;
		a = b;
		b = temp;
	}

	template <class T>
	class DynamicArray
	{
	public:
		DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size)
		{
			_arr = new T[size];
			try { _arr = new T[size]; }
			CHECK_BAD_ALLOC
		}

		DynamicArray(const DynamicArray& other) : _arr(nullptr) {
			*this = other;
		}
		~DynamicArray() {
			delete[] _arr;
		}

		const DynamicArray& operator=(const DynamicArray& other) {
			if (this != &other) {
				_logicalSize = other._logicalSize;
				_physicalSize = other._physicalSize;
				delete[] _arr;
				try { _arr = new T[_physicalSize]; } CHECK_BAD_ALLOC
				for (int i = 0; i < _logicalSize; i++)
					_arr[i] = other._arr[i];
			}
			return *this;
		}

		const T& operator[](int i) const { return _arr[i]; }
		T& operator[](int i) { return _arr[i]; }

		void push_back(const T& value) {
 			if (_logicalSize == _physicalSize)
				resize();
			_arr[_logicalSize++] = value;
		}

		const T& front()    const { return _arr[0]; }
		int      size()     const { return _logicalSize; }
		int      capacity() const { return _physicalSize; }
		bool     empty()    const { return _logicalSize == 0; }
		void     clear()          { _logicalSize = 0; }


		class iterator
		{
		private:
			DynamicArray* _da;
			int           _i;
			bool          _isReverse;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			iterator(DynamicArray& arr = nullptr, int i = 0, bool isReverse = false) : _da(&arr), _i(i), _isReverse(isReverse) {}
			iterator(const iterator& other) : _da(other._da), _i(other._i), _isReverse(other.isReverse) {}

			friend class const_iterator;

			const iterator& operator=(const iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			// comparison with another iterator
			bool operator==(const iterator& other) const {
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const iterator& other) const {
				return !(*this == other);
			}

			// smart-pointer iterator methods
			T& operator*() {
				return _da->_arr[_i];
			}
			T* operator->() {
				return &_da->_arr[_i];
			}

			// increment-decrement iterator methods
			iterator& operator++() {
				++_i;
				return *this;
			}
			iterator operator++(int) {
				iterator temp(*this);
				++_i;
				return temp;
			}
			iterator& operator--() {
				--_i;
				return *this;
			}
			iterator operator--(int) {
				iterator temp(*this);
				--_i;
				return temp;
			}
		};

		class const_iterator : public iterator
		{
		private:
			const DynamicArray* _da;
			int                 _i;
			bool                _isReverse;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = const T;
			using pointer = const T*;
			using reference = const T&;

			const_iterator(const DynamicArray& arr = nullptr, int i = 0, bool isReverse = false) : _da(&arr), _i(i), _isReverse(isReverse) {}
			const_iterator(const iterator& other) : _da(other._da), _i(other._i), _isReverse(other.isReverse) {}
			const_iterator(const const_iterator& other) : _da(other._da), _i(other._i), _isReverse(other.isReverse) {}

			const const_iterator& operator=(const iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			const const_iterator& operator=(const const_iterator& other) {
				_da = other._da;
				_i = other._i;
				return *this;
			}

			// comparison with another iterator
			bool operator==(const const_iterator& other) const {
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const const_iterator& other) const {
				return !(*this == other);
			}

			// smart-pointer iterator methods
			const T& operator*() {
				return _da->_arr[_i];
			}
			const T* operator->() {
				return &_da->_arr[_i];
			}

			// increment-decrement iterator methods
			const_iterator& operator++() {
				if (_isReverse == true) {
					--_i;
					return *this;
				}
				++_i;
				return *this;
			}
			const_iterator operator++(int) {
				if (_isReverse == true) {
					const_iterator temp(*this);
					--_i;
					return temp;
				}
				const_iterator temp(*this);
				++_i;
				return temp;
			}
			const_iterator& operator--() {
				if (_isReverse == true) {
					++_i;
					return *this;
				}
				--_i;
				return *this;
			}
			const_iterator operator--(int) {
				if (_isReverse == true) {
					const_iterator temp(*this);
					++_i;
					return temp;
				}
				const_iterator temp(*this);
				--_i;
				return temp;
			}
		};

		// should return iterator to new element
		void insert(const iterator& pos, const T& val) {
			if (_logicalSize == _physicalSize)
				resize();

			iterator itrEnd = end();
			iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
			while (itrCurrent != pos)
			{
				*itrCurrent = *itrPrev;
				itrCurrent = itrPrev--;
			}

			iterator p = pos;
			*p = val;
			++_logicalSize;
		}
		
		// returns iterator to first element after deleted element/s
		iterator erase(const iterator& iter)
		{
			iterator next;
			if (iter == end())
				if (end() == begin())
					next = { nullptr,0,false };
				else
					next = --iter;
			else
				next = ++iter;

			for (int i = 0; i < _logicalSize; i++) {
				if (_arr[i] == *iter) {
					int k = i;
					while (k < _logicalSize - 1) {
						myswap(_arr[k], _arr[k + 1]);
						k = k + 1;
					}
					break;
				}
			}
			_logicalSize--;
			return next;
		}
		iterator erase(const iterator& first, const iterator& last) {
			iterator next;
			int start = -1, end1 = -1, gap = 0;
			if (last == end())
				if (first == begin())
					next = { nullptr,0,false };
				else
					next =--first;
			else
				next = ++last;

			for (int i = 0; i < _logicalSize; i++) {   //search for the "iterator first idx" in the arr
				if (_arr[i] == *first)
					start = i;
				if (_arr[i] == *last)
					end1 = i;
				if (_arr[i] == *last && _arr[i] == *first)   //pointless to keep searching
					return erase(first);   //need to delete only 1
			}
			if (start < 0 || end1 < 0) {
				//need to add error since one of them not found ******************************************************************************
				return next = { nullptr,0,false };
			}

			//we will delete more than 1 iterator
			if (start > end1)
				myswap(start, end1);
			gap = end1 - start + 1;   //will tell how many we need to delete since we know its biggers than 1
			int k = start;
			while (k + gap < _logicalSize) {   //swap the places till we get to the end of the arr
				myswap(_arr[k], _arr[k + gap]);   //push the places we want to delete to the end without mess the order
				k = k + 1;
			}
			_logicalSize -= gap;  //we delete atleast one
			return next;
		}
		
		iterator begin() {
			return iterator(*this, 0);
		}
		iterator end() {
			return iterator(*this, _logicalSize);
		}
		const_iterator begin() const {
			return const_iterator(*this, 0);
		}
		const_iterator end() const {
			return const_iterator(*this, _logicalSize);
		}
		const_iterator cbegin() const {
			return const_iterator(*this, 0);
		}
		const_iterator cend() const {
			return const_iterator(*this, _logicalSize);
		}
		iterator rbegin() {
			return iterator(*this, _logicalSize, true);
		}
		iterator rend() {
			return iterator(*this, 0, true);
		}
		const_iterator rbegin() const {
			return const_iterator(*this, _logicalSize, true);
		}
		const_iterator rend() const {
			return const_iterator(*this, 0, true);
		}

		void print() const {
			for (int i = 0; i < _logicalSize; i++)
				cout << _arr[i] << " ";
			cout << endl;
		}

		//sort the dynamic array if contains pointers
		void pointersSort() {
			for (int i = 0; i < _logicalSize; i++) {
				for (int k = i; k < _logicalSize; k++) {
					if (*_arr[i] < *_arr[k]) {
						myswap(_arr[i], _arr[k]);
					}
					if (*_arr[i] == *_arr[k]) {
						myswap(_arr[i], _arr[k]);
					}
				}
			}
		}

		//sort the dynamic array if contains non-pointer values
		void sort() {
			for (int i = 0; i < _logicalSize; i++) {
				for (int k = i + 1; k < _logicalSize; k++) {
					if (_arr[i] < _arr[k]) {
						myswap(_arr[i], _arr[k]);
					}
					if (_arr[i] == _arr[k]) {
						myswap(_arr[i], _arr[k]);
					}
				}
			}
		}

	private:
		void resize() {
			_physicalSize *= 2;
			T* temp;
			try { temp = new T[_physicalSize]; } CHECK_BAD_ALLOC
			for (int i = 0; i < _logicalSize; i++)
				temp[i] = _arr[i];

			delete[] _arr;
			_arr = temp;
		}

		T* _arr;
		int _logicalSize;
		int _physicalSize;
	};
}

