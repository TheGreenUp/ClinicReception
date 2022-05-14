#define NOMINMAX //необходимо для очистки гетлайнов строчкой std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'), т.к. max определен в windows.h

#include "Talon.h"
#include "Patient.h"
#include "Doctor.h"
#include <Windows.h>




std::string Doctor::getSpeciality() {
	return this->speciality;
}
void Doctor::setSpeciality(std::string name) {
	this->speciality = name;
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
	std::cout << "Придумайте пароль [максимум 8 символов, только цифры]: ";
	password = User::hidePasswordInput();//меняем на (*)
	User::setPassword(password);//ставим пароль
	system("cls");//чистим экран, чтобы пароль пропал
	while (quit)//переменная выхода, в цикле равна 1
	{
		std::cout << "Повторите пароль: ";
		password_repeat = User::hidePasswordInput();//меняем на (*)
		//User::checkUserInput(password);//проверяем ввод пароля

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
	std::string real_password_int;
	int enetered_password = 0, try_repeat = 0, quit = 1;
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
		//real_password_int = atoi(real_password_string.c_str());//преобразование из типа string в Int
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
				case 1: continue;
				case 2: return false;
				}
			}
		}
	}
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
		if (stringNumber - 1 != chosenDate) {//тут проверка, т.к. мы меняем дату, то надо, чтобы один раз не записалась дата сhosen date начинает отсчет с третьей строки, т.е. надо отнять
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
void Doctor::changeRecordByPatient(std::string date, std::string time, std::string name) {
	FileManager fm; User user;//юзер только для записи в файл
	std::ifstream fin;//поток записи
	std::vector<std::string> buff; //записываем весь файл сюда

	//====================
	int stringNumber = 0; //номер строчки в фале

	std::string tempDate;   //вся строка записи


	fm.createDoctorDir(name);
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
		if (!(stringNumber > 1)) {//а вот на третьей и всех последущих итераций - расписание - то что нужно
			buff.push_back(tempDate);//записываем все данные в буферную переменную
			stringNumber++;
			continue;
		}
		if (!(tempDate.find(date) > 0) && !(tempDate.find(date) < 1000)) {//если не нашли искомую дату 
			buff.push_back(tempDate);//пихаем в вектор
			stringNumber++;
			continue;
		}
		if (!(tempDate.find(time) > 0) && !(tempDate.find(time) < 1000)) {//если не нашли нужное время
			buff.push_back(tempDate);//туда его
			stringNumber++;
			continue;
		}
		tempDate.erase(21, 100); //стираем Занято и все что дальше
		tempDate += "Свободно |";
		buff.push_back(tempDate);//тут чето мой инсерт перестал работать, поэтому пушбэк
	}
	user.putInfoIntoFileDoctor(name, buff);
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
	if (month < 10) monthS = "0" + monthS;//если месяц меньше 10, то добавляем ноль, чтобы получилось 04

	switch (month) //узнаем по месяцу количество дней
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12: {
		maxDays = 31;
		break;
	}
	case 4: case 6: case 9: case 11: {
		maxDays = 30;
		break;
	}
	default:
		maxDays = 28;
		break;
	}

	std::cout << "Введите новый день: ";
	while (!(std::cin >> day) || (day <= 0 || day > 31) || day > maxDays) {
		std::cout << "Введите действительное числовое значение: ";
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

void Doctor::showByName(std::string name)
{
	FileManager fm;
	std::ifstream fin;
	//======================
	int busyPos = 0;
	std::string tempDate;
	bool found = false;

	fm.createDoctorDir(this->getName());
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
		busyPos = tempDate.find(name);
		if (!(busyPos > 0 && busyPos < 100)) continue;
		std::cout << tempDate << std::endl;
		found = true;
	}
	if (!found) {
		std::cout << "Нет клиентов с таким именем!\n";
	}
}



void Doctor::serveNextClient()
{
	FileManager fm;
	std::ifstream fin;
	std::vector<std::string> buff;
	//======================
	int stringNumber = 0; //номер строчки в фале
	int chosenTalon = 0; //номер строчки в фале
	int specSymbolIterator = 0; //количество прочитанных специальных символов (всего 5) [в идеале заменить на Enum]
	//======================
	bool shoudEdit = true;
	bool isSpecSymbol = false;
	//======================
	int busyPos = 0;
	int numberOfWordsInPatientName = 0;
	int numberOfWordInPatientPB = 0;
	//======================
	//===========Данные из файла===========
	std::string fileDate;
	std::string fileTime;
	std::string filePatientName;
	std::string fileDoctorName = this->getName();
	std::string fileSpec;
	std::string fileProblemDescription;
	//=====================================
	std::string wordInRecord;
	std::string tempDate;


	fm.createDoctorDir(this->getName());
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
		busyPos = tempDate.find("Занято");
		if (!(busyPos > 0 && busyPos < 100) || shoudEdit == false) buff.push_back(tempDate);
		if (stringNumber == 1) fileSpec = tempDate;
		if (stringNumber > 1) {//а вот на третьей и всех последущих итераций - расписание - то что нужно
			if (busyPos > 0 && busyPos < 100 && shoudEdit) {//12.12.2022 | 15:30 | Занято |
				chosenTalon = stringNumber - 2;
				std::stringstream ss(tempDate);
				while (specSymbolIterator < 5) {
					ss >> wordInRecord;
					if (wordInRecord == "|") { isSpecSymbol = true; specSymbolIterator++; }
					if (isSpecSymbol == false) {
						switch (specSymbolIterator)
						{
						case 0: {
							fileDate = wordInRecord;
							break;
						}
						case 1: {
							fileTime = wordInRecord;
							break;
						}
						case 3: {//пропускаем  0, 1 и 2, т.к. там хранится не нужная нам информация
							if (numberOfWordsInPatientName == 0)//если одно слово в имени, тогда заходим в этот кейс
								filePatientName = wordInRecord;
							else filePatientName += " " + wordInRecord;//а вот если слов больше, чем одно, тогда берем слово, которое считали первым и добавляем пробелы
							numberOfWordsInPatientName++;//и естественно увеличиваем колиество слов в имени пациента
							break;
						}
						case 4: {
							if (numberOfWordInPatientPB == 0)									//====================//
								fileProblemDescription = wordInRecord;							//====================//
							else fileProblemDescription += " " + wordInRecord;					//смотри ситуацию выше//
							numberOfWordInPatientPB++;											//====================//
							break;																//====================//
						}
						default:
							break;
						}
					}
					isSpecSymbol = false;
				}
				tempDate.erase(21, 6);
				tempDate.insert(21, "Свободен");//12.12.2023 | 16:30 | Свободен | 
				tempDate.erase(32, 1000);
				buff.push_back(tempDate);
				shoudEdit = false;
			}

		}
		stringNumber++;
	}
	fin.close();
	if (!shoudEdit) {
		User user;
		Talon talon;
		std::ofstream fout;
		std::string pathOPCD;
		std::string conclusion;

		Patient patient;
		patient.setName(filePatientName);
		user.putInfoIntoFileDoctor(this->getName(), buff);//записываем измененное расписание доктору

		fileDate = fileDate + " | " + fileTime + " | ";//приводим дату к необходимому формату
		talon = addRecordToOutPatientCard(fileDate, fileDoctorName, fileSpec, fileProblemDescription);//получаем талон нужного формата

		fm.createOutPatientCardDir(filePatientName);
		fm.createClientDir(filePatientName);
		pathOPCD = fm.getOutPatientCardDir();
		patient.deleteTalonFromFile(chosenTalon);
		std::cout << "Введите заключение: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, conclusion);
		OutPatientCard opc;
		opc.AddConclusion(conclusion);
		opc.PutInfoIntoFile(talon, pathOPCD);
		std::cout << "Пациент успешно обслужен!\n";
	}
	else std::cout << "Нет пациентов в очереди!\n";
}
Talon Doctor::addRecordToOutPatientCard(std::string patientDate, std::string doctorName, std::string doctorSpec, std::string problemDescription) {
	Talon talon;
	talon.addTalonToOutPatientCard(patientDate, doctorName, doctorSpec, problemDescription);
	return talon;

}