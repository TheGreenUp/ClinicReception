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
	std::string GetPatientName();//геттеры
	std::string GetDoctorName();//геттеры
	std::string GetDoctorSpec();//геттеры
	std::string getProblemDescription();//геттеры
	
	void editTalonByDoctor(std::string doctorName, std::string problemDescription);//редактировать талон доктором
	void editedSet(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);//изменить талон в файле у пациента

	std::string GetTime();//получить время
	void PutTalonIntoPatientFile();//добавить талон в файл пациента
	void Set(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);//записаться к врачу
	void addTalonToOutPatientCard(std::string patientDate, std::string doctorName, std::string doctorSpec, std::string problemDescription);//добавить талон в амбулаторную карту

	bool ShowInfo(std::string patientName);// для просмотра талона;
	
};

