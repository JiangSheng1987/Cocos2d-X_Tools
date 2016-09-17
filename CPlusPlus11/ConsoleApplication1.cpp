// Cocos2d-x����Щ���õ�C++11������
//����С��� 2016.09.16

#include "stdafx.h"
#include <iostream>
#include <initializer_list>
#include <vector>
#include <memory>
#include <functional>
using namespace std;

//��ʹ�ó�ʼ���б�
class ClassA{
public:
	ClassA(std::initializer_list<int>list){}
};

//����ʹ�ó�ʼ���б�
void func(std::initializer_list<float>list){
	/*Function Body*/
}

//��׼����ʹ�ó�ʼ���б�
vector<string> s = {"hello","C++","11"};



C::C()
{
}

C::~C()
{
}
int _tmain(int argc, _TCHAR* argv[])
{
	/*��ʼ���б�*/
	ClassA a = { 1, 2, 3 };
	func({1.6f,2.8f});

	/*�Զ������Ƶ�*/
	vector<int> v;
	vector<int>::iterator it=v.begin();		//ʹ�������Ƶ�ǰ
	auto it2 = v.begin();					//ʹ�������Ƶ���
	int num;
	decltype(num) b = 5;

	/*�Զ���Χ�Ƶ�*/
	for (int i = 0; i < 10; i++){			//ʹ���Զ���Χ�Ƶ�ǰ
		cout << i << endl;
	}
	int arr []= { 1, 2, 3, 4, 5 };
	for (int &i : arr){
		cout << i << endl;
	}

	/*����ָ��Ϳ�ָ��*/
	//����ָ��ֻ�ܱ�����ָ�븳ֵ��������shared_ptr<int> pq= new int;
	shared_ptr<int> p1(new int);
	//��{ }����һ���µ�������
	{
		//�µ�����ָ��ָ��p1�������൱�ڶ�int�ڴ���һ��retain
		shared_ptr<int> p2 = p1;
		*p2 = 123;
		//p2�����٣��൱�ڶ�int�ڴ���һ��release����������p1��ָ����ڴ棬���ü�������Ϊ0����˲����ͷ�
	}

	/*Lambda���ʽ*/
	int b, c, d;
	auto func0 = [&]()->void {b = 1; c = 2; d = 3; };
	auto func1 = [=]()->int {return 2 * 3; };
	auto func2 = [=, &b, &c]()->void {++b; c += d + b; };
	auto func3 = [=]()->int {return b + d; };

	func0();	//b,c,d�ֱ�Ϊ1��2��3
	c=func1();	//c=6
	func2();	//b=2;c=858993456,d=6;
	b = func3();//b=1717986916
	
	function<void()> f1 = func0;
	function<int()>f2 = func1;

	ClassA *obj = new ClassA();
	function<void(int)> f2 = bind(&ClassA::memberFunc1,obj,std::placeholders::_1);
	function<void(int, char)>f3 = bind(&ClassA::memberFunc2,obj,std::placeholders::_2);
	return 0;
	//p1Ҳ�����٣���ʱ���ü���Ϊ0��int��ռ�õ��ڴ汻�Զ�����

	/*ע�⣡ʹ��shared_ptr��Ҫinclude <memory>*/
}

