#pragma once

#include <deque>
#include <iostream>
//using namespace std;
using std::deque;

//这个版本deprecated，请用Image_Processing里的版本(stock.h)

template<class T>
class Stock
{
public:
	Stock(int capacity):capacity(capacity) { sz = 0; curIdx = -1; }
	~Stock(void) { stock.clear(); }
	int add(T &obj);
	int getIdx() { return curIdx; }
	const int size() const { return sz; }
	bool cur(T &);
	bool pre(T &);
	bool next(T &);
	bool first(T &);
	void clear() { stock.clear(); curIdx = -1; sz = 0; }
private:
	deque<T> stock;
	int curIdx; //当前指针
	int sz; //当前数量
	const int capacity; //最大容量
};

