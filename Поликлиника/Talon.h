#pragma once

#include <windows.h>
#include <string>
#include <iostream>

#include "FileManager.h"

class Talon
{
private:
	std::string clientName, doctorName, doctorSpec, problemDescription, date;
public:
	std::string GetPatientName();// для получения ФИО клиента;
	std::string GetDoctorName();// для получения ФИО специалиста;


	void GetInfoFromFile(std::ifstream fin);


	void EditTalon(std::string problemDescription, std::string doctorName, std::string patientName);
	void editTalonByDoctor(std::string doctorName, std::string problemDescription);
	void editedSet(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);

	// для получения данных из файла;
	std::string GetTime();// для получения даты приёма;
	void PutTalonIntoPatientFile();
	// для записи информации в файл;
	void Set(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);
	// для указания необходимых данных при создании нового талона;
	void ShowInfo(std::string patientName);// для просмотра талона;
	
};

