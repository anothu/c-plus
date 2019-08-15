#include"IntArray.h"

IntArray::~IntArray() {
	delete[] ia;
	cout << "已撤销数组分配的空间!" << endl;
}
void IntArray::common() {
	ia = new int[size];
}
IntArray::IntArray(int sz) {
	size = sz;         // 设置数据成员 
	common();
	for (int ix = 0; ix < size; ++ix)
		ia[ix] = 0;     // 初始化数组元素
}
IntArray::IntArray(int *array, int sz) {
	size = sz;         // 设置数据成员 
	common();
	for (int ix = 0; ix < size; ++ix)
		ia[ix] = array[ix];    // 拷贝数据成员
}
IntArray::IntArray(const IntArray &rhs)
{
	size = rhs.size;
	common();
	for (int ix = 0; ix < size; ix++)
		ia[ix] = rhs.ia[ix];
}
void IntArray::printAll()
{
	for (int ix = 0; ix < size; ++ix)
		cout << ia[ix] << "  ";
	cout << endl;
}
//析构函数