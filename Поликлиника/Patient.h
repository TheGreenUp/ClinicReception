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
	void createTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);	//создать талон c заранее известными параметрами
	void deleteTalonFromFile();//удалить талон
	void deleteTalonFromFile(int chosenTalon);//удалить заранее известный талон
	void showOutPatientCard();//вывести амбулаторную карту
	void SortTalonByDate();// для сортировки талонов
	bool showTalons();//вывести талоны
	//===
	void signUp();//Для регистрации пациента
	bool Login();//Для входа пациентом
	//===
	int checkDataInput();//проверка ввода
	int checkChosenDoctorInput(std::vector<std::string> doctorVector);//проверка ввода
};

