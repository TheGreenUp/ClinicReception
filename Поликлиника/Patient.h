#pragma once
#include "User.h"
#include "OutPatientCard.h"
#include "FileManager.h"
#include "Talon.h"

#include <vector>



class Patient : public User
{
private:
	std::vector<Talon> talons;
	OutPatientCard card;
public:
	void createTalon();//создать талон
	
	//====
	void createTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);	//создать талон c заранее известными параметрами
	void editTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date); //перезапись талона у пациента
	//===
	void deleteTalonFromFile();
	void deleteTalonFromFile(int chosenTalon);
	void showOutPatientCard();
	//удалить талон из файла
	void SortTalonByClientName();// для сортировки талонов по алфавиту по имени клиента;
	void SortTalonByDoctorName();// для сортировки талонов по алфавиту по имени доктора;

	void showTalonInfoByClientName();// для поиска талона по имени клиента;
	void showTalonInfoByDocName();// для поиска талона по имени доктора;

	void getInfoFromFile();//для получения данных клиента врачом из файла;
	void getOutPatientCard();//для получения данных клиента врачом из файла;
	void showTalons();

	
	//===
	void signUp();//Для регистрации пациента
	bool Login();//Для входа пациентом
	//===

};

