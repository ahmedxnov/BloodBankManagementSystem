#include "Person.h"
#include <string>
#include <time.h>
using namespace std;
Person::Person()
{}
Person::Person( string ssn, string name, string mail, string password, string gender, string bloodType)
	:ssn(ssn), name(name), mail(mail), password(password), gender(gender), bloodType(bloodType) {}
	//setters for all data members
void Person::setSsn(string ssn)
{
	this->ssn = ssn;
}
	void Person::setName(string name)
	{
		this->name = name;
	}
	void Person::setMail(string mail)
	{
		this->mail = mail;
	}
	void Person::setPassword(string password)
	{
		this->password = password;
	}
	void Person::setGender(string gender)
	{
		this->gender = gender;
	}
	void Person::setBloodType(string bloodType)
	{
		this->bloodType = bloodType;
	}
	//Getters for all data members(const getter for documentation and for const objects)
	string Person::getSsn() 
	{
		return ssn;
	}

	string Person::getName()  {
		return name;
	}

	string Person::getMail()  {
		return mail;
	}

	string Person::getPassword()  {
		return password;
	}

	string Person::getGender()  {
		return gender;
	}

	string Person::getBloodType() 
	{
		return bloodType;
	}
	vector<string> Person::dateOfBirth(string ssn)
	{
		vector<string> v;
		string y = ssn.substr(0, 1); //30209221303874

		if (y._Equal("2"))
			y = "19";
		else if (y._Equal("3"))
			y = "20";

		string year = y + ssn.substr(1, 2); //2002
		string month = ssn.substr(3, 2); //09
		string day = ssn.substr(5, 2); //22

		v.push_back(year);
		v.push_back(month);
		v.push_back(day);
		return v; //2002/09/022
	}
	int Person::retrieveAge(vector<string> v)
	{
		time_t currentTime = time(nullptr);
		tm currentDate;
		localtime_s(&currentDate, &currentTime);
		int birthYear = stoi(v[0]);
		int birthMonth = stoi(v[1]);
		int birthDay = stoi(v[2]);
		int age = (currentDate.tm_year + 1900) - birthYear;
		if (birthMonth > (currentDate.tm_mon + 1)    ||    (birthMonth == (currentDate.tm_mon + 1) && birthDay > currentDate.tm_mday)) 
		{
			age--;
		}
		return age;
	}
	void Person::toJson(json& j)
	{
		j = json{
			{"SSN", getSsn()},
			{"Name", getName()},
			{"Mail", getMail()},
			{"Age", retrieveAge(dateOfBirth(getSsn()))},
			{"Password", getPassword()},
			{"Gender", getGender()},
			{"Blood Type", getBloodType()}
		};
	}