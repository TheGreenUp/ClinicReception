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
	void getInfoFromFile();//получить инфу
	void PutInfoIntoFile(Talon talon, std::string path);//положить инфу
};

