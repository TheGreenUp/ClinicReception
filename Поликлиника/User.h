#pragma once
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>

#include "FileManager.h"


class User
{
private:
	std::string fullName;
	int password;
public:
	User();
	std::string getName();//Вернуть имя пользователя
	int getPassword();//Получить пароль пользователя
	void setName(std::string);//Изменить имя пользователя
	void setPassword(int);//Изменить пароль пользователя
	void putInfoIntoFileDoctor(std::string spec);//Записать данные доктора в файл
	void putInfoIntoFileDoctor(std::string doctorName,std::vector<std::string> vector);//Записать данные доктора в файл
	void putInfoIntoFilePatient();//Записать данные пациента в файл
	void checkUserInput(int& user_option);//Проверка на числовой ввод
	std::string encryptPassword(std::string password); //шифрование пароля в файле
	int decryptPassword(std::string password);//расшифровать пароль (можно и без него)
	int hidePasswordInput();//звездочки вместо цифр при вводе пароля
};

