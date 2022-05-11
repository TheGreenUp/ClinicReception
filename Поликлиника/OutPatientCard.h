#pragma once

#include <string>


class OutPatientCard
{
private: 
	std::string conclusion;
public:
	void AddConclusion();// для записи заключения врача в амбулаторную карту пациента;
	void GetConclusionsCount();// для получения размера заключения, записываемого в файл;
	void GetIntoFromFile();// для получения данных из файла;
	void PutInfoIntoFile();// для записи данных в файл;
	void ShowInfo();// для просмотра необходимой информации в карте пациента;

};

