#include "Recipient.h"

Recipient::Recipient( string ssn, string name, string mail, string password, string gender, string bloodType, string hospital, string doctor)
	:Person(ssn,name,mail,password,gender,bloodType), hospital(hospital), doctor(doctor){}
Recipient::Recipient(json j)
{
	setSsn(j["SSN"]);
	setName(j["Name"]);
	setMail(j["Mail"]);
	setPassword(j["Password"]);
	setGender(j["Gender"]);
	setBloodType(j["Blood Type"]);
	setHospital(j["Hospital"]);
	setDoctor(j["Doctor"]);
}
Recipient::Recipient(){}
void Recipient::setHospital(string hospital)
{
	this->hospital = hospital;
}
void Recipient::setDoctor(string doctor)
{
	this->doctor = doctor;
}
string Recipient::getHospital()
{
	return hospital;
}
string Recipient::getDoctor()
{
	return doctor;
}
void Recipient::toJson(json& j)
{
	Person::toJson(j);
	j["Hospital"] = getHospital();
	j["Doctor"] = getDoctor();
}