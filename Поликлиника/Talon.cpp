#include "Talon.h"

std::string Talon::GetPatientName()
{
	return this->clientName;
}

std::string Talon::GetDoctorName()
{
	return this->doctorName;
}

void Talon::GetInfoFromFile(std::ifstream fin)
{

}

//void Talon::EditTalon(std::string problemDescription, std::string doctorName, std::string patientName) {
//	FileManager fm;
//	std::ifstream fin;//поток вывода из файлa
//
//	int stringNumber = 0; //номер строчки в фале
//	int wordIterator = 0;
//	int dateNumber = 1; //номер строчки в фале
//	std::string tempDate;
//	std::string talonString;
//
//	std::string fileDoctorName;
//	int stringTalonSize = 0;
//
//	int numberOfSymbolsInTalon = 0; //итератор для проверки на то, кончился ли талон
//
//	fm.createClientDir(patientName);
//	fin.open(fm.getClientDir());
//
//	for (int n; std::getline(fin, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
//		if (stringNumber != 0) {//все талоны в файле пациента находятся после первой строчки, поэтому первую итерацию пропускаем
//			std::stringstream ss(tempDate);// используем строковый поток
//			stringTalonSize = tempDate.size();//размер талона
//			for (numberOfSymbolsInTalon; numberOfSymbolsInTalon <= stringTalonSize;) {//читает до тех пор, пока не кончится талон
//				ss >> talonString;// выпнули слово, повторяем в цикле, пока слова не кончатся
//				switch (wordIterator)
//				{
//				case 0: {//первая строка - дата
//					fileDoctorName = talonString;
//					break;
//				}
//				}
//
//				std::cout << talonString << " ";//выводим слово
//				if (numberOfSymbolsInTalon == 0) numberOfSymbolsInTalon++; //в связи с тем, что в строке есть пробелы, способ немного некорректный, а вот таким хитрым костылем мы все правим =)
//				numberOfSymbolsInTalon += talonString.size();//добаляем к итератору длину слова, которое вывели
//				numberOfSymbolsInTalon += 1; //пробел
//				wordIterator++;
//
//			}
//			if (numberOfSymbolsInTalon >= stringTalonSize) {
//				std::cout << std::endl; //если закончился талон, делаем переход на следующую строчку
//				numberOfSymbolsInTalon = 0;
//			}
//		}
//		stringNumber++;
//
//
//		if (fin.eof()) {//проверка на конец файла
//			fin.close();//закрываем
//			return;
//		}
//	}
//}


void Talon::PutTalonIntoPatientFile()//дозаписываем файл клиента, внося туда талон (запись) к врачу
{
	FileManager fmanager;//для проверки путя
	fmanager.createClientDir(this->clientName);//создаем директорию (если она существует, то строчка игнорируется)
	std::string path = fmanager.getClientDir();//берем путь нужного доктора
	std::ofstream out;// поток для записи
	out.open(path, std::ios::app); // окрываем файл для записи
	if (out.is_open())
	{
		out << this->date << this->doctorName << this->doctorSpec << this->problemDescription << std::endl;

	}
	out.close();
}


void Talon::Set(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date)
{
	this->clientName = clientName + " | ";
	this->doctorName = doctorName + " | ";
	this->doctorSpec = doctorSpec + " | ";
	this->problemDescription = problemDescription + " |";
	this->date = date;
}


//==========РЕДАКТИРОВАНИЕ ДОКТОРОМ==========
void Talon::editTalonByDoctor(std::string doctorName, std::string problemDescription)//дозаписываем файл клиента, внося туда талон (запись) к врачу
{
	FileManager fmanager;//для проверки путя
	std::vector<std::string> buff;
	fmanager.createClientDir(this->clientName);//создаем директорию (если она существует, то строчка игнорируется)
	std::string path = fmanager.getClientDir();//берем путь нужного доктора
	std::string tempDate;
	std::string newTalon = this->date + this->doctorName + this->doctorSpec + this->problemDescription;

	bool foundDoctor = false;

	int numberOfString = 0;
	std::ifstream fout;// поток для записи
	fout.open(path); // окрываем файл для записи

	int doctorPos;
	int probDescPos;

	for (int n; std::getline(fout, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
		if (!numberOfString) {
			
			numberOfString++;
			buff.push_back(tempDate);
			continue;
		}

		doctorPos = tempDate.find(doctorName);
		probDescPos = tempDate.find(problemDescription);
		

		if (doctorPos > 0 && doctorPos < 1000) {//Если не нашли имя нужного доктора
			foundDoctor = true;
		}
		if (probDescPos > 0 && probDescPos < 1000 && foundDoctor) {//Если не нашли проблему
			buff.push_back(newTalon);
			numberOfString++;
			foundDoctor = false;
			continue;
		}
		buff.push_back(tempDate);
		numberOfString++;
	}
	fout.close();

	std::ofstream fin;
	fin.open(path);
	for (int i = 0; i < buff.size(); i++) {
		fin << buff[i] << std::endl;
	}

	fin.close();
}
void Talon::editedSet(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date)
{
	this->clientName = clientName + " | ";
	this->doctorName = doctorName + " | ";
	this->doctorSpec = doctorSpec + " | ";
	this->problemDescription = problemDescription + " |";
	this->date = date + " | ";
}
//===========================================


void Talon::ShowInfo(std::string patientName)//ДОРАБОТАТЬ, чтобы из файла читались данные 
{
	FileManager fm;
	std::ifstream fin;//поток вывода из файлa

	int stringNumber = 0; //номер строчки в фале
	int dateNumber = 1; //номер строчки в фале
	std::string tempDate;
	std::string talonString;
	int stringTalonSize = 0;

	int numberOfSymbolsInTalon = 0; //итератор для проверки на то, кончился ли талон

	fm.createClientDir(patientName);
	fin.open(fm.getClientDir());

	for (int n; std::getline(fin, tempDate); ) { //пишем такую строчку, пушо писать через while (fin.eof()) - херня
		if (stringNumber != 0) {//все талоны в файле пациента находятся после первой строчки, поэтому первую итерацию пропускаем
			std::stringstream ss(tempDate);// используем строковый поток
			stringTalonSize = tempDate.size();//размер талона
			for (numberOfSymbolsInTalon; numberOfSymbolsInTalon <= stringTalonSize;) {//читает до тех пор, пока не кончится талон
				ss >> talonString;// выпнули слово, повторяем в цикле, пока слова не кончатся
				std::cout << talonString << " ";//выводим слово
				if (numberOfSymbolsInTalon == 0) numberOfSymbolsInTalon++; //в связи с тем, что в строке есть пробелы, способ немного некорректный, а вот таким хитрым костылем мы все правим =)
				numberOfSymbolsInTalon += talonString.size();//добаляем к итератору длину слова, которое вывели
				numberOfSymbolsInTalon += 1; //пробел

			}
			if (numberOfSymbolsInTalon >= stringTalonSize) {
				std::cout << std::endl; //если закончился талон, делаем переход на следующую строчку
				numberOfSymbolsInTalon = 0;
			}
		}
		stringNumber++;


		if (fin.eof()) {//проверка на конец файла
			fin.close();//закрываем
			return;
		}
	}
}