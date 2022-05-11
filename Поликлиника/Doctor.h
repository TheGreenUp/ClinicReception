#pragma once
#include "User.h"
#include "MyException.h"
#include "DayTimeTable.h"

class Doctor : public User {
private:
	std::string speciality;
public:
	void signUp();//Регистрация
	bool Login();//Вход в аккаунт
	void setSpeciality(std::string spec);// для установки спецификации при регистрации;
	std::string getSpeciality();// для получения
	void findFirstTalon();// для поиска первого талона в очереди
	void getInfoFromFile();// для получения информации из файла;
	void putInfoIntoFile();// для записи необходимой информации в файл;
	void serveNextClient();// для обслуживания следующего клиента, у которого оплачен талон;
	void setSpec();// для установки спецификации при регистрации;
	void showTimeTable();// для просмотра расписания специалиста;
	void changeRecordDate();	// редактировать timetable
	std::string checkDateInput(); //все проверки для создания необходимой даты


};

