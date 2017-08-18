// 09_Redo_Undo_Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ImagesStock.h"
#include <iostream>
using namespace std;

class Widget 
{

public:
	Widget(int a) { id = a; }
	void sayHi() { cout << "hi:" << id << endl; }
private:
	int id;
};

int main()
{

	Widget *pw[10];


	Stock<Widget> s(8);
	for (int i=0;i!=10;++i)
	{
		pw[i] = new Widget(i);
		pw[i]->sayHi();
		s.add(*pw[i]);
	}

	

	for (int i=0;i!=s.size();++i)
	{
		
	}



    return 0;
}

