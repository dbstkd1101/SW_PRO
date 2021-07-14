#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
auto mySum(T a, T b) {
	//return { a.first + b.first, a.second + b.second }; // initializer list
	return make_pair{ a.first + b.first, a.second + b.second }; // pair<T, T>
}

int main() {
	int a{ 2 }; // int a=2;
	pair<int, int> p{ 1, 2 };
	pair<int, int> q{ 3, 3 };

	cout << p.first << " " << p.second << endl;
	cout << (p < q) << endl;

	//auto pp = p; // pair<int, int> pp;
	
	auto &pp = p;
	pp.first = 0;

	cout << p.first << " " << p.second << endl;

	//auto pq = mySum(p, q);

	int arr[5]{ 4, 5, 2, 4, 1 };
	for (auto x : arr) {
		cout << x << " ";
	}


	return 0;
}

