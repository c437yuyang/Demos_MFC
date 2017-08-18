#include "StdAfx.h"
#include "ImagesStock.h"


template<class T>
bool Stock<T>::cur(T &)
{
	if (size() > 0)
	{
		T = stock[curIdx];
		return true;
	}
	return false;
}

template <class T>
bool Stock<T>::pre(T &obj)
{
	if (curIdx <= size() && curIdx > 0)
	{
		curIdx--;
		obj = stock[curIdx]; //必须T支持operator=才行
		return true;
	}
	return false;
}

template <class T>
bool Stock<T>::next(T &obj)
{
	if (curIdx < size() - 1)
	{
		curIdx++;
		obj = stock[curIdx];
		//stock[curIdx].CopyTo(img);
		return true;
	}
	return false;

}

template <class T>
bool Stock<T>::first(T &dst)
{
	if (size() > 0)
	{
		dst = stock[0];
		return true;
		//stock[0].CopyTo(dst);
	}
	return false;
}


template<class T>
int Stock<T>::add(T &obj)
{
	if (curIdx != sz() - 1) //在中间位置执行添加，先删除中间位置之后的存储
	{
		for (int i = 0; i != sz() - curIdx - 1; ++i)
			stock.pop_back();
		sz -= (sz - curIdx - 1);
		++sz;
		curIdx++;
		stock.push_back(obj);
	}
	else//常规添加(尾部)
	{
		if (size() > capacity - 1) //达到了最大存储数目
		{
			stock.pop_front(); //因为这里用到了pop_front所以需要用deque，vector不行
			stock.push_back(obj);
		}
		else //常规添加且未达到最大数目
		{
			++sz;
			++curIdx;
			stock.push_back(obj);
		}
	}
	return size();
}