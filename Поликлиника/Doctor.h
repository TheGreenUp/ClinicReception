#pragma once
#include "User.h"
#include "MyException.h"
#include "DayTimeTable.h"
#include "Talon.h"

class Doctor : public User {
private:
	std::string speciality;
public:
	void signUp();//Регистрация
	bool Login();//Вход в аккаунт
	void setSpeciality(std::string spec);// для установки спецификации при регистрации;
	std::string getSpeciality();// для получения
	void serveNextClient();// для обслуживания следующего клиента, у которого талон;
	void showTimeTable();// для просмотра расписания специалиста;
	void changeRecordDate();	// редактировать timetable
	void changeRecordByPatient(std::string date, std::string time, std::string name);
	std::string checkDateInput(); //все проверки для создания необходимой даты
	void showByName(std::string name);//вывести по имени
	Talon addRecordToOutPatientCard(std::string patientName, std::string patientDate, std::string doctorName, std::string doctorSpec);//на выходе из функции получим готовый талон, с которым можно работать
	int checkRecordDataInput();//проверить ввод
};

