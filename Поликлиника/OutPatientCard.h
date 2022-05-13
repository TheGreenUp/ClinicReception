#pragma once
#include "FileManager.h"
#include "Talon.h"
#include <string>


class OutPatientCard
{
private: 
	std::string conclusion;
public:
	void AddConclusion(std::string conclusion);// для записи заключения врача в амбулаторную карту пациента;
	void GetConclusionsCount();// для получения размера заключения, записываемого в файл;
	void getInfoFromFile();
	void PutInfoIntoFile(Talon talon, std::string path);
	// для получения данных из файла;
	void ShowInfo();// для просмотра необходимой информации в карте пациента;

};

