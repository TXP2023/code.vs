#pragma once
#include <set>

// 声明方法
// std::set< typeName > objectName;
std::set<int> s;

// 相关函数
int main() {
	//在集合s里插入元素
	//函数原型 
	// pair<iterator, bool> insert(value_type&& _Val)
	//返回值里的first成员是插入后被插入元素的迭代器,second成员为是否插入成功
	s.insert(int(0));

	//查询集合里元素的数量
	//函数原型
	//_NODISCARD size_type size() const noexcept
	s.size();
}