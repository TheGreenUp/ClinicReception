#pragma once
#include "User.h"
#include "OutPatientCard.h"
#include "FileManager.h"
#include "Talon.h"

#include <vector>



class Patient : public User
{
	std::vector<Talon> talons;
	OutPatientCard card;
public:
	void createTalon();//создать талон
	
	//====
	void createTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);	//создать талон c заранее известными параметрами
	//===
	void deleteTalonFromFile();
	void deleteTalonFromFile(int chosenTalon);
	void showOutPatientCard();
	//удалить талон из файла
	void SortTalonByDate();// для сортировки талонов по алфавиту по имени клиента;

	bool showTalons();

	
	//===
	void signUp();//Для регистрации пациента
	bool Login();//Для входа пациентом
	//===
	int checkDataInput();
	int checkChosenDoctorInput(std::vector<std::string> doctorVector);
};

