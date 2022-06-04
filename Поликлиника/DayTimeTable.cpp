#include "DayTimeTable.h"



DayTimeTable::DayTimeTable() {
	std::vector<std::string> date;
	date.push_back("25.05.2022 | 08:00 | Свободен |");
	date.push_back("25.05.2022 | 08:30 | Свободен |");
	date.push_back("25.05.2022 | 09:00 | Свободен |");
	date.push_back("25.05.2022 | 09:30 | Свободен |");
	date.push_back("25.05.2022 | 10:00 | Свободен |");
	date.push_back("25.05.2022 | 10:30 | Свободен |");
	date.push_back("25.05.2022 | 11:00 | Свободен |");
	date.push_back("25.05.2022 | 11:30 | Свободен |");
	date.push_back("25.05.2022 | 12:00 | Свободен |");
	date.push_back("25.05.2022 | 12:30 | Свободен |");
	this->date = date;
}

std::vector<std::string> DayTimeTable::getDateVector()
{
	return this->date;
}

void DayTimeTable::GetInfoFromFile(std::string nameOfChosenDoctor)
{
	FileManager fm;
	std::ifstream fin;//поток вывода из файлa

	int stringNumber = 0; //номер строчки в фале
	int dateNumber = 1; //номер строчки в фале
	std::string tempDate;

	fm.createDoctorDir(nameOfChosenDoctor);
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
}

void DayTimeTable::BookChosenTime(int chosenDate, std::string doctorName, std::string patientName, std::string problemDescription, std::string& justDate, std::string& spec)
{
#pragma region Variables

	std::vector<std::string> buff; //записываем весь файл сюда
	FileManager fm; User user; //user Нужен только для записи в файл
	std::ifstream fin;//поток вывода из файлa

	int stringNumber = 0; //номер строчки в фале
	std::string tempDate;
	std::string changedDate;
#pragma endregion

#pragma region FileWork
	fm.createDoctorDir(doctorName);
	fin.open(fm.getDoctorDir());
	for (int n; std::getline(fin, tempDate); ) {//так же как и в ситуации с чтением из файла расписания - в for мы и считываем, а чекаем на конец файла после цикла
		buff.insert(buff.begin() + stringNumber, tempDate);//записываем все данные в буферную переменную
		if (stringNumber == 1) spec = tempDate; //выхватываем специальность
		if (stringNumber > 1) {//а вот на третьей и всех последущих итераций - расписание - то что нужно
			if (stringNumber - 1 == chosenDate) { // в файле такая структура 1. пароль 2. специальность 3 и далее - расписание, поэтому отнимаем три
				tempDate.erase(21, 100); //удаляем "Свободно"
				justDate = tempDate;
				tempDate += "Занято | " + patientName + " | " + problemDescription + " |"; //меняем на "занято + имя + проблема"
				changedDate = tempDate;
			}
		}
		stringNumber++;
	}
	buff[chosenDate + 1] = changedDate;
	fin.close();//закрываем
#pragma endregion

	user.putInfoIntoFileDoctor(doctorName, buff);//перезаписываем

}

bool DayTimeTable::checkIsFree(int chosenDate, std::string doctorName) {
	FileManager fm;
	std::ifstream fin;//поток вывода из файлa

	int stringNumber = 0; //номер строчки на которой мы сейчас находимся
	std::string tempDate;

	fm.createDoctorDir(doctorName);
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) {//так же как и в ситуации с чтением из файла расписания - в for мы и считываем, а чекаем на конец файла после цикла
		stringNumber++;
		if (stringNumber > 1) {//а вот на третьей и всех последущих итераций - расписание - то что нужно
			if (stringNumber - 2 == chosenDate) { // в файле такая структура: 1. пароль 2. специальность 3 и далее - расписание, поэтому отнимаем три
				int pos = tempDate.find("Занято"); //интовая позиция в файле
				if (pos != -1) {//если найдено слово "занято", то ретерним false
					fin.close();
					return false;
				}
			}
		}
	}
	fin.close();
	return true;
}

