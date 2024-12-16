#pragma once
#include <vector>

//建立一个vector
std::vector< int > v(10, 0); //建立了一个vector类 初始长度为10 ,每个元素为0 构造函数省略时vector的长度为0
// std::vector< typeName > objectName(length, init);

int main() {

	v.clear(); //清空vector
	// objectName.clear()

	v.resize(15, 0); //将vector类的长度调整为15 新增部分为0

	v.pop_back(); //弹出vector末尾的元素
	
	v.push_back(5);// 在vector的末尾插入元素5
	// objectName.push_back(object)

	std::vector< int >::iterator it; //建立一个vector< int >迭代器 指向一个vector中的一个int 
	// sstd::vector< typeName >::iterator it;
	//迭代器可以使用*it 取出里头的值 

	v.begin(); //返回vector的首个元素的迭代器

	v.end();//返回vector的末尾元素的后一位的迭代器

	it = v.begin();
	//erse成员函数
	//用法1
	v.erase(it); //删除vector it迭代器所指向的元素
	//用法2
	v.erase(v.begin(), v.end()); //删除vector begin至end-1 位的元素

	v.insert(v.begin(), 1); //将vector的迭代器后面的元素向后移一位 将v.begin()的值更改为1
	
}