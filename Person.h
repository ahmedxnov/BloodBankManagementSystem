#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;
class Person
{
protected:
	string ssn;
	string name;
	string mail;
	//Age will be derived data member from ssn to ensure accurate data
	string password;
	string gender;
	string bloodType;
public:
	//all members constructor
	Person( string, string, string, string, string, string);
	Person();
	//setters for all data members
	void setSsn(string);
	void setName(string);
	void setMail(string);
	void setPassword(string);
	void setGender(string);
	void setBloodType(string);
	//Getters for all data members(const getter for documentation and for const objects)
	string getSsn() ;
	string getName() ;
	string getMail() ;
	string getPassword() ;
	string getGender() ;
	string getBloodType() ;
	//data of birth retrieval from ssn
	vector<string> dateOfBirth(string);
	//age retrieval from dateOfBirth
	int retrieveAge(vector<string>);
	// Serialization to JSON
	virtual void toJson(json& j);

};
#endif PERSON_H
