#include "SmartPointer.h"
#pragma once

#include <iostream>

//конструктор умного указателя
template <class T>
SmartPointer<T>::SmartPointer(T* ptr) {
	if (!ptr) smartPtr = NULL; // указатель на объект пустой 
	else {
		smartPtr = new Status<T>;
		smartPtr->ptr = ptr; // инициализирует объект указателем 
		smartPtr->counter = 1; // счетчик «прикрепленных» объектов инициализируем единицей
	}
}
//конструктор копирования умного указателя
template <class T>
SmartPointer<T>::SmartPointer(const SmartPointer& obj)
	:smartPtr(obj.smartPtr) {
	if (smartPtr) smartPtr->counter++; // только увеличение числа ссылок 
}
//деструктор умного указателя
template <class T>
SmartPointer<T>::~SmartPointer() {
	if (smartPtr) {
		smartPtr->counter--; // уменьшается число ссылок на объект 
		if (smartPtr->counter <= 0) { // если число ссылок на объект меньше либо равно нулю, то уничтожается объект
			delete smartPtr->ptr;//ссылка на объект уничтожается
			delete smartPtr;
		}
	}
}

template <class T>
void showCounter() {
	std::cout << this->smartPtr->counter;
}

template <class T>
T* SmartPointer<T>::operator->() const {
	if (smartPtr) return smartPtr->ptr;
	else return NULL;
}

template <class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& obj) {
	if (smartPtr) {
		smartPtr->counter--; // уменьшаем счетчик «прикрепленных» объектов
		if (smartPtr->counter <= 0) { // если объектов нет, то выполняется освобождается выделенная память
			delete smartPtr->ptr;
			delete smartPtr;
		}
	}
	smartPtr = obj.smartPtr; // присоединение к новому указателю 
	if (smartPtr) smartPtr->counter++; // увеличить счетчик «прикрепленных» объектов
	return *this;
}

