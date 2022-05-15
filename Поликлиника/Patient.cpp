#define NOMINMAX //необходимо для очистки гетлайнов строчкой std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'), т.к. max определен в windows.h
#include "Patient.h"
#include "MyException.h"
#include "Doctor.h"

#include <string>
#include <iostream>
#include <Windows.h>


bool Patient::showTalons()
{

	Talon talon;
	if (talon.ShowInfo(this->getName())) return true;
	else return false;

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
	std::cout << "Придумайте пароль [до 8 символов, только цифры]: ";
	password = User::hidePasswordInput();//меняем на (*)
	User::setPassword(password);
	system("cls");
	while (quit)//переменная выхода, в цикле равна 1
	{
		std::cout << "Повторите пароль: ";
		password_repeat = User::hidePasswordInput();//меняем на (*)
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
	int enetered_password = 0, try_repeat = 0, quit = 1;
	int successLogin = 0;//повторный ввод пользователем логина
	std::string entered_name, real_password_string;
	std::ifstream fin;

	while (quit)//проверка на существование такого пациента
	{
		while (!successLogin) {

			std::cout << "====================================";
			std::cout << "\nВведите ФИО: ";
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
	while (quit)
	{
		std::cout << "Введите пароль [максимум 8 символов]: ";
		enetered_password = User::hidePasswordInput();
		//User::checkUserInput(enetered_password); //ввод пароля
		if (enetered_password == User::decryptPassword(real_password_string)) {
			this->setName(entered_name);
			this->setPassword(enetered_password);
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

int Patient::checkDataInput()
{
	int chosenDate;
	std::cout << "Выберите удобную дату: ";
		while (!(std::cin >> chosenDate) || std::cin.get() != '\n' || chosenDate < 1 || chosenDate > 10)
	{
		std::cout << "Введите числовое значение [1;10]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');

	}
	return chosenDate;
}

int Patient::checkChosenDoctorInput(std::vector<std::string> doctorVector) {
	int chosenDate;
	int vectorSize = doctorVector.size();
	std::cout << "К какому врачу хотите записаться на прием: ";
	while (!(std::cin >> chosenDate) || std::cin.get() != '\n' || chosenDate < 1 || chosenDate > vectorSize)
	{
		std::cout << "Неверный ввод! ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	return chosenDate;
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
	doctorNames = fm.getDoctorsNames();//записываем в вектор имена всех врачей //Выводим имя + специальность

	if (doctorNames.size() == 0) {
		std::cout << "Врачей нет! спят наверное...\n";
		return;
	}

	fm.showDoctorsInfo(doctorNames); //ТУТ ТОЖЕ ОШИБКА
	//===========ВЫВОД РАСПИСАНИЯ======
	chosenDoctor = checkChosenDoctorInput(doctorNames);
	nameOfChosenDoctor = doctorNames[chosenDoctor - 1];
	dtt.GetInfoFromFile(nameOfChosenDoctor);
	//===============БРОНЬ=============
	chosenDate = checkDataInput();
	while (!dtt.checkIsFree(chosenDate, nameOfChosenDoctor)) {//если занято //ПОЧИНИТЬ
		std::cout << "Выбранное время занято, выберите другое:\n";
		std::cin >> chosenDate;
	};
	std::cout << "Опишите проблему: ";
	//std::getline(std::cin, problemDescription);
	std::getline(std::cin, problemDescription);
	dtt.BookChosenTime(chosenDate, nameOfChosenDoctor, patientName, problemDescription, date, spec); //последние два аргумента в функции получат свои значение, т.к. передаются по ссылке
	Talon talon;
	talon.Set(patientName, nameOfChosenDoctor, spec, problemDescription, date);//наконец-то создаем талон
	this->talons.push_back(talon);
	talon.PutTalonIntoPatientFile();
}

void Patient::createTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date) {
	Talon talon;
	talon.editedSet(clientName, doctorName, doctorSpec, problemDescription, date);//наконец-то создаем талон
	this->talons.push_back(talon);
	talon.editTalonByDoctor(doctorName, problemDescription);
}

void Patient::deleteTalonFromFile() {
	std::ifstream fout;
	if (!showTalons()) return;//если талонов нет, то выходим
	int chosenTalon = 0;
	std::cout << "Введите номер талона, который хотите удалить: ";
	std::cin >> chosenTalon;

	FileManager fm;
	Doctor doctor;

	std::string tempDate, wordInRecord;
	std::string date, time, doctorName;
	std::vector<std::string> buff;

	int stringNumber = 0;
	int specSymbolIterator = 0;
	int numberOfWordsInDoctorName = 0;

	bool isSpecSymbol = false;

	fm.createClientDir(this->getName());
	fout.open(fm.getClientDir());

	for (int n; std::getline(fout, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
		if (!stringNumber) {//первая строка (пароль) записываем сразу
			stringNumber++;
			buff.push_back(tempDate);
			continue;
		}
		if (stringNumber == chosenTalon) {//если нашли, то
			std::stringstream ss(tempDate);// используем строковый поток

			while (specSymbolIterator < 3) {
				ss >> wordInRecord;// выпнули слово, повторяем в цикле, пока слова не кончатся
				if (wordInRecord == "|") { specSymbolIterator++; isSpecSymbol = true; } //если нашли спец.символ, то увеличиваем их количество и говорим программе, что код красный - символ специальный
				if (isSpecSymbol == false) {//если в данный момент не управляющий символ, то
					switch (specSymbolIterator)//в зависимости от количества управляющих символов, которые программа успела прочитать, выщипываем нужные слова
					{
					case 0: {//выхватываем дату
						date = wordInRecord;
						break;
					}
					case 1: {//выхватываем время
						time = wordInRecord;
						break;
					}
					case 2: {//выхватываем имечко
						if (numberOfWordsInDoctorName == 0)//если одно слово в имени, тогда заходим в этот кейс
							doctorName = wordInRecord;
						else doctorName += " " + wordInRecord;//а вот если слов больше, чем одно, тогда берем слово, которое считали первым и добавляем пробелы
						numberOfWordsInDoctorName++;//и естественно увеличиваем колиество слов в имени пациента
						break;
					}
					}
				}
					isSpecSymbol = false;
			}
				doctor.changeRecordByPatient(date, time, doctorName);
				stringNumber++;
				continue;
			}
			else {
				buff.push_back(tempDate);
				stringNumber++;

			}
		}
		fout.close();
		std::ofstream fin;
		fin.open(fm.getClientDir());
		for (int i = 0; i < buff.size(); i++) {
			fin << buff[i] << std::endl;
		}
		fin.close();
	}

void Patient::deleteTalonFromFile(int chosenTalon) {
	std::ifstream fout;

	FileManager fm;
	Doctor doctor;

	std::string tempDate, wordInRecord;
	std::string date, time, doctorName;
	std::vector<std::string> buff;

	int stringNumber = 0;
	int specSymbolIterator = 0;
	int numberOfWordsInDoctorName = 0;

	bool isSpecSymbol = false;

	fm.createClientDir(this->getName());
	fout.open(fm.getClientDir());

	for (int n; std::getline(fout, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
		if (!stringNumber) {
			stringNumber++;
			buff.push_back(tempDate);
			continue;
		}
		if (stringNumber == chosenTalon) {
			stringNumber++;
			continue;
		}
		else {
			buff.push_back(tempDate);
			stringNumber++;

		}
	}
	fout.close();
	std::ofstream fin;
	fin.open(fm.getClientDir());
	for (int i = 0; i < buff.size(); i++) {
		fin << buff[i] << std::endl;
	}
	fin.close();
}

void Patient::showOutPatientCard() {
	FileManager fm;
	std::string path;
	std::string tempDate;
	std::ifstream fin;

	bool isData = false;

	fm.createOutPatientCardDir(this->getName());
	path = fm.getOutPatientCardDir();
	fin.open(path); 

	for (int n; std::getline(fin, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня 
		std::cout << tempDate << std::endl;
		isData = true;
	}
	fin.close();
	if (!isData) std::cout << "Нет записей!\n";	
}

void Patient::SortTalonByDate()
{

	FileManager fm;
	std::ifstream fin;//поток вывода из файлa

	int stringNumber = 0; //номер строчки в фале
	int dateNumber = 1; //номер строчки в фале
	int stringTalonSize = 0;
	int numberOfSymbolsInTalon = 0; //итератор для проверки на то, кончился ли талон

	std::string tempDate;
	std::string talonString;

	std::vector<std::string> buff;

	bool areRecordsInFile = false;


	fm.createClientDir(this->getName());
	fin.open(fm.getClientDir());

	for (int n; std::getline(fin, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
		buff.push_back(tempDate);
		}
	
}

