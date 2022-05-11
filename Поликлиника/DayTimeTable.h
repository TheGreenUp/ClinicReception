#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <iostream>
#include <fstream>

#include "FileManager.h"
#include "User.h"
class DayTimeTable
{
private:
	SYSTEMTIME real_date;
	std::vector<std::string> date;
	bool isFree;
public:
	DayTimeTable();
	SYSTEMTIME getRealTimeDate();// для получения данных;
	std::vector<std::string> getDateVector();// для получения свободного времени у выбранного специалиста;
	void GetInfoFromFile(std::string nameOfChosenDoctor);// для получения данных о расписании из файла;
	void GetTime();// для получения времени, которое выбрал пациента для посещения специалиста;
	void PutInfoIntoFile();// для записи расписания в файл;
	void BookChosenTime(int chosenDate, std::string doctorName, std::string patientName, std::string problemDescription, std::string& justDate, std::string& spec);// для выбора свободного времени в расписании врача;
	bool checkIsFree(int tempDate, std::string doctorName);// для проверки свободно ли выбранное пациентом время у специалиста;
	void ShowInfo();// для просмотра расписания специалистов;

};

