#ifndef DONOR_H
#define DONOR_H
#include "Person.h"
#include<vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
class Donor : public Person
{
private:
	string lastDonationDate = "";
	vector<string> diseases;
public:
	//constructor
	Donor(string, string, string, string, string, string,string,vector<string>);
	Donor(json);
	Donor();

	//setters
	void setLastDonationDate(string);
	void setDisease(string);
	void setDiseases(vector<string>);

	//getters
	string getLastDonationDate();
	vector<string> getDiseases();

	//age checking
	bool isValidAge(int);

	//check lastDonationDate
	bool isValidDonationAgain(string);

	//checking for diseases
	bool hasNoDisease(vector<string>);

	//final eligibility checking
	bool eligibilityForDonating();
	// Serialization to JSON
	void toJson(json&) override;
};
#endif DONOR_H