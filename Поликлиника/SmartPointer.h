#pragma once
template <class T>
struct Status {
	T* ptr; // указатель на объект
	int counter; // счетчик числа ссылок на объект 
};


//Класс умного указателя. Цель умного указателя состоит в подсчете  количества ссылок
//через множество умных указателей на один объект
template <class T>
class SmartPointer {
	Status<T>* smartPtr;
public:
	SmartPointer(T* ptr = 0);
	SmartPointer(const SmartPointer&);
	~SmartPointer();
	SmartPointer& operator=(const SmartPointer&); //перегрузка оператора =
	T* operator->() const; // перегрузка оператора ->
	void showCounter();
};
