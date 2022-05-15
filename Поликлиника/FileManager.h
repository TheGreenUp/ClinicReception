#pragma once
#include <direct.h>
#include <string>	
#include <vector>	
#include <iostream>
#include <iomanip>

#include <filesystem>
#include <fstream>


namespace fs = std::filesystem;
class FileManager
{
private:
	std::string clientDir;
	std::string doctorDir;
	std::string outPatientCardDir;
public:
	std::string getDoctorDir();//вернуть путь к врачам
	std::string getClientDir();//вернуть путь к клиентам
	std::string getOutPatientCardDir();//вернуть путь к клиентам

	void createClientDir(std::string name);//создать путь к клиентам
	void createDoctorDir(std::string name);//создать путь к докторам
	void createOutPatientCardDir(std::string name);//создать путь к докторам

	std::vector<std::string> getDoctorsNames();//получить инфу о врачах
	void showDoctorsInfo(std::vector<std::string> doctorNames);//вывести инфу о врачах

};

