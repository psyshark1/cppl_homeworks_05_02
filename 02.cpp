﻿#include <iostream>

template<typename T>
class mtable
{
public:
	mtable(int _r, int _c);
	~mtable();
	mtable(const mtable&) = delete;
	mtable& operator=(const mtable&) = delete;
	//class row_proxy;
	//row_proxy operator[](int r);

	//class row_proxy
	//{
	//public:
	//	row_proxy() {};
	//	~row_proxy() {};
	//	T& operator[](int c);

	//	int& row = mtable<T>::row;
	//	int& column = mtable<T>::column;
	//	T**& t_table = mtable<T>::t_table;
	//};

	T* operator[](int r);
	const T* operator[](int r) const;
	int size();

private:
	int row;
	int column;
	T** t_table;
	T** create_table();
	void delete_table();
};

template<typename T>
mtable<T>::mtable(int _r, int _c) : row(_r), column(_c)
{
	this->t_table = create_table();
}

template<typename T>
T** mtable<T>::create_table()
{
	T** tmp = new T* [this->row];
	for (unsigned short i = 0; i < this->row; ++i)
	{
		tmp[i] = new T[this->column]{0};
	}
	return tmp;
}

//template<typename T>
//mtable<T>::row_proxy mtable<T>::operator[](int r)
//{
//	if (r < 0 || r >= this->row) throw std::exception("Row index out of array!");
//	return mtable<T>::row_proxy;
//}
//
//template<typename T>
//T& mtable<T>::row_proxy::operator[](int c)
//{
//	if (c < 0 || c >= this->column) throw std::exception("Column index out of array!");
//	return this->column;
//}

template<typename T>
T* mtable<T>::operator[](int r)
{
	if (r < 0 || r >= this->row) throw std::exception("Row index out of array!");
	return this->t_table[r];
}

template<typename T>
const T* mtable<T>::operator[](int r) const
{
	if (r < 0 || r >= this->row) throw std::exception("Row index out of array!");
	return this->t_table[r];
}


template<typename T>
int mtable<T>::size()
{
	return this->row * this->column * sizeof(T);
}

template<typename T>
void mtable<T>::delete_table()
{
	for (unsigned short i = 0; i < this->row; ++i)
	{
		delete[] this->t_table[i];
	}
	delete[] this->t_table;
}

template<typename T>
mtable<T>::~mtable()
{
	this->delete_table();
}


int main()
{
	try
	{
		auto test = mtable<int>(2, 3);
		test[0][0] = 4;
		std::cout << test[0][0] << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
