#define NOMINMAX //необходимо для очистки гетлайнов строчкой std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'), т.к. max определен в windows.h

#include "Talon.h"
#include "Patient.h"
#include "Doctor.h"
#include <Windows.h>




std::string Doctor::getSpeciality() {
	return this->speciality;
}

void Doctor::signUp()
{
	FileManager file_manager; //создаем объект класса файл_менеджер
	std::string name, spec; //инициализируем имя
	int password = 0, password_repeat = 0, quit = 1;
	std::cout << "====================================";
	std::cout << "\nВведите ваше ФИО: ";
	std::getline(std::cin, name);
	User::setName(name);//ставим введенное имя пользователю	
	std::cout << "Придумайте пароль [до 10 символов]: ";
	User::checkUserInput(password);//проверяем ввод пароля
	User::setPassword(password);//ставим пароль
	system("cls");//чистим экран, чтобы пароль пропал
	while (quit)//переменная выхода, в цикле равна 1
	{
		std::cout << "Повторите пароль: ";
		User::checkUserInput(password_repeat);

		if (password == password_repeat) {//если после повторного ввода пароли совпали, то вводим специальность и записываем в файл
			std::cout << "Введите Вашу специальность: ";
			std::getline(std::cin, spec);
			Doctor::setSpeciality(spec);
			std::cout << "Регистрация успешно завершена!\n";
			User::putInfoIntoFileDoctor(spec);//Записываем в файл данные
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
				return;
			}

		}
	}
}

bool Doctor::Login()
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
			fmanager.createDoctorDir(entered_name);
			fin.open(fmanager.getDoctorDir());
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
		quit = 1;
		std::getline(fin, real_password_string); //считывание первой строки из файла, которая является паролем
		real_password_int = atoi(real_password_string.c_str());//преобразование из типа string в Int
		while (quit)
		{
			std::cout << "Введите пароль: ";
			User::checkUserInput(enetered_password); //ввод пароля

			if (enetered_password == real_password_int) {
				this->setName(entered_name);
				this->setPassword(enetered_password);
				return true;
			}
			else {
				std::cout << "Желаете повторить попытку?\n[1] Да\n[2] Нет\n";
				std::cin >> try_repeat;
				switch (try_repeat)
				{
				case 1: continue;
				case 2: return false;
				}
			}
		}
	}
}
void Doctor::setSpeciality(std::string name) {
	this->speciality = name;
}

void Doctor::showTimeTable()
{
	FileManager fm;
	std::ifstream fin;
	int stringNumber = 0; //номер строчки в фале
	int dateNumber = 1; //номер строчки в фале
	std::string tempDate;

	fm.createDoctorDir(this->getName());
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
		if (stringNumber > 1) {//а вот на третьей и всех последущих итераций - расписание - то что нужно
			std::cout << "[" << dateNumber << "]" << " "; //выводим номер [1] [2] и т.д.
			std::cout << tempDate << std::endl; //выводим дату 12.12.2022
			dateNumber++;
		}
		stringNumber++;

		if (fin.eof()) {//проверка на конец файла
			fin.close();//закрываем
			return;
		}
	}
	fin.close();
}

void Doctor::changeRecordDate()
{
	showTimeTable();//сначала выводим расписание
	int chosenDate;
	std::cout << "Выберите время, которое хотите изменить:\n";	std::cin >> chosenDate;

	FileManager fm; User user;//юзер только для записи в файл
	std::ifstream fin;//поток записи
	std::vector<std::string> buff; //записываем весь файл сюда

	//====================
	int stringNumber = 0; //номер строчки в фале
	int stringRecordSize = 0; //номер строчки в фале
	int currentSymbolsInString = 0; //количество прочитанных символов

	int wordsIterator = 0; //количество прочитанных слов
	int specSymbolIterator = 0; //количество прочитанных специальных символов (всего 5) [в идеале заменить на Enum]

	int numberOfWordsInPatientName = 0; //количество слов в имени пациента (необходимо для дальнейших проверок)
	int numberOfWordInPatientPB = 0; //количество слов в описании проблемы пациента (необходимо для дальнейших проверок)

	std::string tempDate;   //вся строка записи
	std::string wordInRecord;   //слово, выхваченное из записи

	//==========
	std::string chDate; //изменяемая дата

	bool isSpecSymbol = false;//проверка на управляющий символ в выхваченной строке
	bool shouldEditPatientFile = false;//проверка на управляющий символ в выхваченной строке

	//===========Для пациента===============
	std::string patientTalonDate;					//Выхваченное из файла доктора дата
	std::string patientTalonName;					//И имя туда же
	std::string patientTalonDoctorSpec;				//специальность
	std::string patientTalonProblemDescription;		//Описание проблемы не забываем
	std::string patientTalonDoctorName = this->getName(); //И имечко доктора
	//======================================


	fm.createDoctorDir(this->getName());
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
		if (stringNumber - 2 != chosenDate) {//тут проверка, т.к. мы меняем дату, то надо, чтобы один раз не записалась дата сhosen date начинает отсчет с третьей строки, т.е. надо отнять
			buff.insert(buff.begin() + stringNumber, tempDate);//записываем все данные в буферную переменную
		}
		if (stringNumber == 1) patientTalonDoctorSpec = tempDate;
		if (stringNumber > 1) {//а вот на третьей и всех последущих итераций - расписание - то что нужно
			if (stringNumber - 1 == chosenDate) {

				//===============МЕНЯЕМ У ДОКТОРА В ФАЙЛЕ==============
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				chDate = checkDateInput();
				tempDate.erase(0, 18); //стираем дату (первые 18 символов) 12.12.2022 | 15:30
				tempDate = chDate + tempDate;//скрепочкой их
				patientTalonDate = chDate;//введенная нами дата
				buff.push_back(tempDate);//тут чето мой инсерт перестал работать, поэтому пушбэк
				//====================================================


				if (tempDate.find("Занято") > 0 && tempDate.find("Занято") < 1000) {//если в строке есть слово занято, тогда меняем файл пациента
					//==============МЕНЯЕМ У ПАЦИЕНТА В ФАЙЛЕ==============
					std::stringstream ss(tempDate);// используем строковый поток
					stringRecordSize = tempDate.size();//размер талона

					for (currentSymbolsInString; currentSymbolsInString <= stringRecordSize;) {//читает до тех пор, пока не кончится талон
						ss >> wordInRecord;// выпнули слово, повторяем в цикле, пока слова не кончатся
						if (wordInRecord == "|") { specSymbolIterator++; isSpecSymbol = true; } //если нашли спец.символ, то увеличиваем их количество и говорим программе, что код красный - символ специальный
						if (isSpecSymbol == false) {//если в данный момент не управляющий символ, то
							switch (specSymbolIterator)//в зависимости от количества управляющих символов, которые программа успела прочитать, выщипываем нужные слова
							{
							case 3: {//пропускаем  0, 1 и 2, т.к. там хранится не нужная нам информация
								if (numberOfWordsInPatientName == 0)//если одно слово в имени, тогда заходим в этот кейс
									patientTalonName = wordInRecord;
								else patientTalonName += " " + wordInRecord;//а вот если слов больше, чем одно, тогда берем слово, которое считали первым и добавляем пробелы
								numberOfWordsInPatientName++;//и естественно увеличиваем колиество слов в имени пациента
								break;
							}
							case 4: {
								if (numberOfWordInPatientPB == 0)									//====================//
									patientTalonProblemDescription = wordInRecord;					//====================//
								else patientTalonProblemDescription += " " + wordInRecord;			//смотри ситуацию выше//
								numberOfWordInPatientPB++;											//====================//
								break;																//====================//
							}
							}
						}

						if (currentSymbolsInString == 0) currentSymbolsInString++; //в связи с тем, что в строке есть пробелы, способ немного некорректный, а вот таким хитрым костылем мы все правим =)
						currentSymbolsInString += wordInRecord.size();//добаляем к итератору длину слова, которое вывели
						currentSymbolsInString += 1; //пробел
						wordsIterator++;
						isSpecSymbol = false;
						if (currentSymbolsInString >= stringRecordSize) {
							std::cout << std::endl; //если закончился талон, делаем переход на следующую строчку
							shouldEditPatientFile = true;
						}
					}
				}
				currentSymbolsInString = 0; //обнуляем количество прочитанных символов в строке 
			}
		}
		stringNumber++;//сколько строк прочитано
	}
	user.putInfoIntoFileDoctor(this->getName(), buff);//измененное расписание записываем в файл доктора
	if (shouldEditPatientFile) {//если мы изменяли файл пациента, надо закинуть туда инфу
		Patient patient; //буферного пациента создаем для создания ему талона
		patient.createTalon(patientTalonName, patientTalonDoctorName, patientTalonDoctorSpec, patientTalonProblemDescription, patientTalonDate); //и прямиком в талон
	}
	fin.close();//закрываем
}

std::string Doctor::checkDateInput() {
	int day = 0, month = 0, year = 0, hour = 0, minute = 0;
	std::string dayS, monthS, yearS, hourS, minuteS;
	std::string tmp;
	std::string changedDate;
	
	int maxDays = 0;

	std::cout << "Введите новый месяц: ";
	while (!(std::cin >> month) || (month <= 0 || month > 12)) {
		std::cout << "Введите числовое значение [1;12]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	monthS = std::to_string(month);//переводим int в std::string
	monthS = "0" + monthS;//если месяц меньше 10, то добавляем ноль, чтобы получилось 04

	switch (month) //узнаем по месяцу количество дней
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12: {
		maxDays = 31;
	}
	 case 4: case 6: case 9: case 11: {
		maxDays = 30;
	}
	default:
		maxDays = 28;
	}

	std::cout << "Введите новый день: ";
	while (!(std::cin >> day) || (day <= 0 || day > 31) ) {
		std::cout << "Введите числовое значение [1;31]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	dayS = std::to_string(day);//переводим int в std::string
	if (day < 10) dayS = "0" + dayS;//если день меньше 10, то добавляем ноль, чтобы получилось 04

	std::cout << "Введите новый год: ";
	while (!(std::cin >> year) || (year < 2022 || year > 2030)) {
		std::cout << "Введите числовое значение [2022;2030]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	yearS = std::to_string(year);

	std::cout << "Введите новое время (час): ";
	while (!(std::cin >> hour) || (hour <= 7 || hour > 22)) {
		std::cout << "Введите числовое значение [8;22]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	hourS = std::to_string(hour);//переводим int в std::string
	if (hour < 10) hourS = "0" + hourS;//если час меньше 10, то добавляем ноль, чтобы получилось 04

	std::cout << "Введите новое время (минуты): ";
	while (!(std::cin >> minute) || (minute < 0 || minute > 60)) {
		std::cout << "Введите числовое значение [1;59]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	minuteS = std::to_string(minute);//переводим int в std::string
	if (minute < 10) minuteS = "0" + minuteS;//если минуты меньше 10, то добавляем ноль, чтобы получилось 04


	changedDate = dayS + "." + monthS + "." + yearS + " | " + hourS + ":" + minuteS;
	return changedDate;
}