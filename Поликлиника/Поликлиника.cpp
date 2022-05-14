//=========================
#include "DayTimeTable.h";
#include "Doctor.h"
#include "FileManager.h";
#include "OutPatientCard.h";
#include "Patient.h";
#include "Talon.h";
//=======================
#include <iostream>
#include <windows.h>


//========================Глобальные переменные=======================
const char DELIMETER[40] = { "====================================" };
//====================================================================


void printUserMenu() {//функция вывода первичной информации для невошедшего пользователя
	std::cout << DELIMETER << "\nЗдравствуйте! Чем я могу Вам помочь?\n[1] Войти как врач\n[2] Войти как пациент\n[3] Зарегестрироваться как врач\n[4] Зарегестрироваться как пациент\n[5] Выйти\n" << DELIMETER << "\n";
}

void checkPatientInput(int& user_option) {//Проверка числового ввода от [1;5]
	while (!(std::cin >> user_option) || std::cin.get() != '\n' || user_option < 1 || user_option > 6)
	{
		std::cout << "Введите числовое значение [1;6]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
}
void checkDoctorInput(int& user_option) {//Проверка числового ввода от [1;5]
	while (!(std::cin >> user_option) || std::cin.get() != '\n' || user_option < 1 || user_option > 5)
	{
		std::cout << "Введите числовое значение [1;5]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
}
void checkUserInput(int& user_option) {//Проверка числового ввода от [1;5]
	while (!(std::cin >> user_option) || std::cin.get() != '\n' || user_option < 1 || user_option > 5)
	{
		std::cout << "Введите числовое значение [1;5]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
}

void stopAndCLS() {//останавливаем до нажатия клавиши + очищаем после экран
	system("pause");
	system("cls");
}

int main() {
	User user;
	SetConsoleCP(1251); //       русский язык в консоли
	SetConsoleOutputCP(1251);//  ввод на русском языке
	Patient patient;
	Doctor doctor;
	DayTimeTable day;
	int user_chosen_option = 0, quit = 1, patientExit = 1, doctorExit = 1;
	while (quit)
	{
		printUserMenu();//вывод меню для пользователя
		checkUserInput(user_chosen_option); //проверка на числовой ввод
		switch (user_chosen_option)
		{
		case 1: {
			if (doctor.Login())
			{
				std::cout << "Вход...\n";
				doctorExit = 1;
				Sleep(1000);
				system("cls");
				//======================
				while (doctorExit)
				{
					system("cls");
					int chosen_option = 0;
					std::cout << DELIMETER << "\n[1]Обслужить ближайшего клиента\n[2]Просмотреть расписание\n[3]Редактировать расписание\n[4]Поиск по имени клиента\n[5]Выход из аккаунта\n" << DELIMETER << std::endl;

					checkDoctorInput(chosen_option);
					switch (chosen_option)
					{
					case 1: {
						doctor.serveNextClient();
						stopAndCLS();
						break;
					}
					case 2: {
						doctor.showTimeTable();
						stopAndCLS();
						break;
					}
					case 3: {
						doctor.changeRecordDate();
						stopAndCLS();
						break;
					}
	
					case 4: {
						std::string patientName;
						std::cout << "Введите имя пациента: ";
						std::cin >> patientName;
						doctor.showByName(patientName);
						stopAndCLS();
						break;
					}
					case 5: {
						doctorExit = 0;
						break;
					}
					default:
						break;
					}
				}
			}
			break;
		}
		case 2: {
			if (patient.Login())//Вход
			{
				std::cout << "Вход...\n";
				patientExit = 1;
				Sleep(1000);
				system("cls");
				//=======================
				while (patientExit)//цикл
				{

					std::cout << DELIMETER << "\n[1]Создать талон\n[2]Удалить талон\n[3]Просмотреть список талонов\n[4]Сортировать талоны по дате\n[5]Просмотреть амбулаторную карту\n[6]Выход из аккаунта\n" << DELIMETER << std::endl;
					int chosen_option = 0,chosen_sort_option = 0;
					checkPatientInput(chosen_option);
					switch (chosen_option)
					{
					case 1: {
						patient.createTalon();
						stopAndCLS();
						break;
					}
					case 2: {
						patient.deleteTalonFromFile();
						stopAndCLS();
						break;
					}
					case 3: {
						patient.showTalons();
						stopAndCLS();
						break;
					}
					case 4: {
						patient.SortTalonByDate();
						stopAndCLS();
						break;
					}
					case 5: {
						patient.showOutPatientCard();
						stopAndCLS();
						break;
					}
					case 6: {
						patientExit = 0;
						break;
					}
					default:
						break;
					}
				}
			}
			break;
		}
		case 3: {
			doctor.signUp();
			break;
		}
		case 4: {
			patient.signUp();
			break;
		}
		case 5: {
			std::cout << "Досвидания!";
			Sleep(1000);
			quit = 0;
			break;
		}
		}
		system("cls");
	}
}

