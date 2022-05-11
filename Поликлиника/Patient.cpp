#define NOMINMAX //необходимо для очистки гетлайнов строчкой std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'), т.к. max определен в windows.h
#include "Patient.h"
#include "MyException.h"
#include "Doctor.h"

#include <string>
#include <iostream>
#include <Windows.h>


void Patient::showTalons()
{
	
	Talon talon;
	talon.ShowInfo(this->getName());

}

void Patient::signUp()
{
	FileManager file_manager; //создаем объект класса файл_менеджер
	std::string name; //инициализируем имя
	int password = 0, password_repeat = 0, quit = 1;
	std::cout << "====================================";
	std::cout << "\nВведите ваше ФИО: ";
	std::getline(std::cin, name);
	User::setName(name);
	std::cout << "Придумайте пароль [до 10 символов]: ";
	User::checkUserInput(password);
	User::setPassword(password);
	system("cls");
	while (quit)//переменная выхода, в цикле равна 1
	{
		std::cout << "Повторите пароль: ";
		User::checkUserInput(password_repeat);

		if (password == password_repeat) {
			std::cout << "Регистрация успешно завершена!\n";
			User::putInfoIntoFilePatient();//Записываем в файл данные
			Sleep(1000);//Даем пользователю увидеть, что все хорошо
			return;
		}
		else
		{
			int chosen_option = 0;
			std::cout << "Введенный пароль не совпадает с изначальным!\nХотите повторить попытку?\n[1] Да\n[2] Нет\n";
			std::cin >> chosen_option;
			switch (chosen_option)
			{
			case 1: {
				//ничего не делаем
				break;
			}
			case 2:
				quit = 0; //выходим
			}

		}
	}
}

bool Patient::Login()
{
	FileManager fmanager;//для проверки путя
	int real_password_int = 0, enetered_password = 0, try_repeat = 0, quit = 1;
	int successLogin = 0;//повторный ввод пользователем логина
	std::string entered_name, real_password_string;
	std::ifstream fin;

	while (quit)//проверка на существование такого пациента
	{
		while (!successLogin) {

			std::cout << "====================================";
			std::cout << "\nВведите ваше имя: ";
			std::getline(std::cin, entered_name);
			fmanager.createClientDir(entered_name);
			fin.open(fmanager.getClientDir());
			try
			{
				if (!fin) throw MyException("Неверный логин! ", 0);//если не существует файла с именем пациента, кинет exception
				else quit = 0;
			}
			catch (MyException& ex)
			{
				std::cout << ex.what();
				std::cout << "Желаете повторить попытку?\n[1] Да\n[2] Нет\n";
				std::cin >> try_repeat;
				switch (try_repeat)
				{
				case 1: {
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.clear();
					continue;
				}
				case 2: return false;
				}
			}
			successLogin = 1;
		}
	}
	quit = 1;
	std::getline(fin, real_password_string); //считывание первой строки из файла, которая является паролем
	real_password_int = atoi(real_password_string.c_str());//преобразование из типа string в Int
	while (quit)
	{
	std::cout << "Введите пароль: ";
	User::checkUserInput(enetered_password); //ввод пароля

	if (enetered_password == real_password_int) {
		this->setName(entered_name);
		this->setPassword(real_password_int);
		return true;
	}
	else {
		std::cout << "Желаете повторить попытку?\n[1] Да\n[2] Нет\n";
		std::cin >> try_repeat;
		switch (try_repeat)
		{
		case 1: break;
		case 2: return false;
		}
	}
	}
}

void Patient::createTalon()
{
	int chosenDoctor = 0, chosenDate;

	std::ifstream fin;//поток вывода из файла

	DayTimeTable dtt;
	FileManager fm;//файлменеджер для открытия папок

	std::vector<std::string> doctorNames; //вектор имен врачей
	std::string problemDescription, date;
	std::string spec, nameOfChosenDoctor, tempDate;//специальность врача и имя выбранного доктора, буферная переменная для времени
	
	std::string patientName = this->getName();

	//=====Получаем инфу о врачах======
	doctorNames = fm.getDoctorsNames();//записываем в вектор имена всех врачей
	//Выводим имя + специальность
	fm.showDoctorsInfo(doctorNames); //ТУТ ТОЖЕ ОШИБКА
	//===========ВЫВОД РАСПИСАНИЯ======
	std::cout << "К какому врачу хотите записаться на прием?\n";
	std::cin >> chosenDoctor;
	nameOfChosenDoctor = doctorNames[chosenDoctor - 1];
	dtt.GetInfoFromFile(nameOfChosenDoctor);
	//===============БРОНЬ=============
	std::cout << "Выберите удобное время:\n";
	std::cin >> chosenDate;
	while (!dtt.checkIsFree(chosenDate, nameOfChosenDoctor)) {//если занято //ПОЧИНИТЬ
		std::cout << "Выбранное время занято, выберите другое:\n";
		std::cin >> chosenDate;
	};
	std::cout << "Опишите проблему:";
	std::getline(std::cin.ignore(), problemDescription); //ТУТ ПРОБЛЕМА (вроде решил)
	dtt.BookChosenTime(chosenDate, nameOfChosenDoctor, patientName, problemDescription, date, spec); //последние два аргумента в функции получат свои значение, т.к. передаются по ссылке
	Talon talon;
	talon.Set(patientName,nameOfChosenDoctor, spec, problemDescription, date);//наконец-то создаем талон
	this->talons.push_back(talon);
	talon.PutTalonIntoPatientFile();
}

void Patient::createTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date) {
	Talon talon;
	talon.editedSet(clientName, doctorName, doctorSpec, problemDescription, date);//наконец-то создаем талон
	this->talons.push_back(talon);
	talon.editTalonByDoctor(doctorName, problemDescription);
}

void Patient::editTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date) {
	Talon talon;

}