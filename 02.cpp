#include <iostream>

template<typename T>
class mtable
{
public:
	mtable(T _r, T _c);
	~mtable();
	T* operator[](T r);
	const T* operator[](T r) const;
	int size();

private:
	T row;
	T column;
	T** t_table;
	T** create_table();
	void delete_table();
};

template<typename T>
mtable<T>::mtable(T _r, T _c) : row(_r), column(_c)
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

template<typename T>
T* mtable<T>::operator[](T r)
{
	if (r < 0 || r > this->row) throw std::exception("Row index out of array!");
	return this->t_table[r];
}

template<typename T>
const T* mtable<T>::operator[](T r) const
{
	if (r < 0 || r > this->row) throw std::exception("Row index out of array!");
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
