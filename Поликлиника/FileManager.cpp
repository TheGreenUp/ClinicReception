#include "FileManager.h"


std::string FileManager::getClientDir()
{
	return this->clientDir;
}
std::string FileManager::getOutPatientCardDir()
{
	return this->outPatientCardDir;
}
std::string FileManager::getDoctorDir()
{
	return this->doctorDir;
}

void FileManager::createClientDir(std::string name)
{
	setlocale(LC_ALL, "russian");
	std::string userName = name; //имя папки = имя пользователя
	int stringLength = name.length();//длина строки
	int pos = userName.find("|"); //если находим специальный символ, то удаляем его, 

	if (pos != -1) {//вот мы его нашли и вот, а т.к. у нас userName = name + " | "
		userName.resize(userName.size() - 3);//удаляем три позиции
		stringLength -=3;
	}
	while (name[stringLength - 1] == ' ') {//если последний символ - пробел, то удаляем его
		userName.erase(stringLength - 1, 1);//стираем пробел
		stringLength--;//и уменьшаем длину строки
	}

	std::string format = ".txt"; //делаем текстовое расширение
	userName += format; //соединяем
	_mkdir("Patients"); //создаем папку Пациенты
	std::string path = "Patients\\"; //указываем путь к папке пациенты
	path += userName; //совмещаем каталог и название
	this->clientDir = path;//путь к файлу - в папке с названием клиенты
}

void FileManager::createDoctorDir(std::string name)
{
	setlocale(LC_ALL, "russian");
	std::string userName = name; //имя папки = имя доктора
	std::string format = ".txt"; //делаем текстовое расширение
	userName += format; //соединяем
	_mkdir("Doctors"); //создаем папку 
	std::string path = "Doctors\\"; //указываем путь к папке докторов
	path += userName; //совмещаем каталог и название
	this->doctorDir = path;//путь к файлу - в папке с названием доктор
}

void FileManager::createOutPatientCardDir(std::string name)
{
	setlocale(LC_ALL, "russian");
	std::string userName = name; //имя папки = имя доктора
	std::string format = ".txt"; //делаем текстовое расширение
	userName += format; //соединяем
	_mkdir("OutPatientsCard"); //создаем папку 
	std::string path = "OutPatientsCard\\"; //указываем путь к папке докторов
	path += userName; //совмещаем каталог и название
	this->outPatientCardDir = path;//путь к файлу - в папке с названием доктор
}

std::vector<std::string> FileManager::getDoctorsNames()
{
	std::vector<std::string> doctorsNames; //массив имен докторов
	std::string tempStr;
	std::string inputPath = "Doctors";        // путь к папке с файлами
	//fs::path path;
	std::filesystem::path path;


	for (auto& p : fs::directory_iterator(inputPath)) //при помощи этой команды читаем названия всех файлов, лежащих в inputPath
	{
		path = p;
		tempStr = path.fs::path::generic_string();
		tempStr.erase(0, 8); //стираем имя папки (Doctors)
		tempStr.erase(tempStr.size() - 4);//стираем расширение (.txt)
		doctorsNames.push_back(tempStr); //закидываем в вектор
	}
	return doctorsNames;
}

void FileManager::showDoctorsInfo(std::vector<std::string> doctorNames) {



	std::ifstream fin;//поток вывода из файла
	FileManager fm;//файлменеджер для открытия папок
	std::string spec;//специальность врача

	int i = 0;

	{
		for (int x = 0; x < doctorNames.size(); x++) {//проходимся по именам всех докторов
			{
				std::cout << "[" << x + 1 << "]" << " "; //выводим номер
				std::cout << std::setw(30) << std::left << doctorNames[x] << "\t" << std::setw(50) <<std::left;//выводим имя

				//считываем специальность
				fm.createDoctorDir(doctorNames[x]);
				fin.open(fm.getDoctorDir());
				for (i; i < 2; i++) {//нас интересует вторая строчка, поэтому цикл только сработает дважды
					std::getline(fin, spec);//считываем строчку, но т.к. первая строчка - пароль, то ее просто считаем вникуда
					if (i == 1) {//а вот на второй итерации - специальность - то что нужно
						std::cout << spec << std::endl; //выводим ее 
					}
				}
					fin.close();
					i = 0;
			}
		}
	}
	fin.close();
}
