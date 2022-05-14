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
	std::string GetDoctorName();
	std::string GetDoctorSpec();
	std::string getProblemDescription();
	// для получения ФИО специалиста;


	void EditTalon(std::string problemDescription, std::string doctorName, std::string patientName);
	void editTalonByDoctor(std::string doctorName, std::string problemDescription);
	void editedSet(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);

	// для получения данных из файла;
	std::string GetTime();// для получения даты приёма;
	void PutTalonIntoPatientFile();
	// для записи информации в файл;
	void Set(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);
	void addTalonToOutPatientCard(std::string patientDate, std::string doctorName, std::string doctorSpec, std::string problemDescription);
	// для указания необходимых данных при создании нового талона;
	bool ShowInfo(std::string patientName);// для просмотра талона;
	
};

