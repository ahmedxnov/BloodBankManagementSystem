#ifndef RECIPIENT_H
#define RECIPIENT_H
#include "Person.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
class Recipient : public Person
{
private:
	string hospital;
	string doctor;
public:
	//constructor for all data members
	Recipient(string, string, string, string, string, string, string, string);
	Recipient();
	Recipient(json);
	//setters
	void setHospital(string);
	void setDoctor(string);
	//getters
	string getHospital();
	string getDoctor();
	void toJson(json&) override;
};
#endif RECIPIENT_H