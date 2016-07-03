#include<iostream>
#include<initializer_list>
#include<vector>
using namespace std;



template <class ElementType> class MyVector { 
	vector<ElementType> vector;
	public:
	MyVector(const initializer_list<ElementType> &lst) {
		for(auto data : lst) { // auto and for each loop
			vector.push_back(std::move(data)); // std::move
		}
	}
	
	void oldFunction() = delete; // delete functions not to be used 
	
	template <class ResultType> ResultType reduce(ResultType defaultValue, function<ResultType(ElementType, ResultType)> func) { // std::function
		for(auto data : vector) {
			defaultValue = func(data, defaultValue);
		}
		return defaultValue;
	};
};

int main() {
	MyVector<int> v1 {0, 1, 2, 3};
	MyVector<int> v2 = {0, 1, 2, 3};
	
	// v1.oldFunction(); // can't use this function - COMPILE time error
	
	cout << v1.reduce<int>(0, [] (int x, int y) { return std::move(x + y);}) << endl;	// lambda expressions
	
	auto multiply = [] (int x, int y) { return std::move(x * y); }; // function<int(int, int)> in place of auto also works
	
	cout << v1.reduce<int>(1, multiply) << endl;
	
	const char *rawString = R"(\\ja\i)";
	cout << "rawString = " << rawString << endl;
	
	const char *utf8 = u8"jai";
	cout << "rawString = " << utf8 << endl;
	
	const char16_t *utf16 = u"jai";
	cout << "utf16 = " << utf16  << endl;
		
	const char32_t *utf32 = U"jai";
	cout << "utf32 = " << utf32 << endl;
			
	return 0;
}
