#include <functional>
#include <iostream>
#include <vector>

template<typename T>
class Array {
private:
	std::vector<T> arr;

public:
	Array();
	Array(std::vector<T> arr);
	std::vector<T>& value();
	std::vector<T> filter(std::function<bool(T)> valid);
	template<typename _T> std::vector<_T> map(std::function<_T(T)> modify);
	T reduce(std::function<T(T,T)> combine, T acc);
};

int
main() {
	Array<int> array({0, 1, 2, 3, 4, 5});
	
	// Filter Implementation
	std::vector<int> odds = array.filter([](const int& val) {
		return (val % 2 == 1);
	});
	
	for (int& val: odds)
		std::cout << val << " ";
	std::cout << std::endl;
	
	// Map Implementation
	std::vector<char> letters = array.map<char>([](const int &val) {
		return (char)('a' + val);
	});
	
	for (char& c: letters)
		std::cout << c << " ";
	std::cout << std::endl;
	
	// Reduce Implementation
	int sum = array.reduce([](int a, int b) {
		return a + b;
	}, 0);
	
	std::cout << sum << std::endl;
	
	// Direct Access To Vector
	array.value().push_back(6);
	std::cout << array.value().size() << std::endl;
	
	return 0;
}

template<typename T>
Array<T>::Array() {
	this->arr = std::vector<T>();
}

template<typename T> std::vector<T>&
Array<T>::value() {
	return this->arr;
}

template<typename T>
Array<T>::Array(std::vector<T> arr) {
	this->arr = arr;
}

template<typename T> std::vector<T>
Array<T>::filter(std::function<bool(T)> valid) {
	std::vector<T> filtered_arr;
	
	for (T& val: arr)
		if (valid(val))
			filtered_arr.push_back(val);
	
	return filtered_arr; 
}

template<typename T>
template<typename _T> std::vector<_T>
Array<T>::map(std::function<_T(T)> modify) {
	std::vector<_T> modified_arr;
	
	for (T& val: arr)
		modified_arr.push_back(modify(val));
	
	return modified_arr; 
}

template<typename T> T
Array<T>::reduce(std::function<T(T,T)> combine, T acc) {
	for (T& val: arr)
		acc = combine(acc, val);
	return acc;
}
