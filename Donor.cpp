#include "Donor.h"
#include <algorithm>
#include <ctime>
#include <iostream>
Donor::Donor(string ssn, string name, string mail, string password, string gender, string bloodType, string lastDonationDate, vector<string> diseases)
	: Person(ssn,name,mail,password,gender,bloodType), lastDonationDate(lastDonationDate), diseases(diseases) {}
Donor::Donor(json j)
{
	setSsn(j["SSN"]);
	setName(j["Name"]);
	setMail(j["Mail"]);
	setPassword(j["Password"]);
	setGender(j["Gender"]);
	setBloodType(j["Blood Type"]);
	setLastDonationDate(j["Last Donation Date"]);
	json diseasesJson = j["Diseases"];
	for (auto& disease : diseasesJson)
	{
		setDisease(disease);
	}
}
Donor::Donor()
{
}
void Donor::setLastDonationDate(string lastDonationDate)
{
	this->lastDonationDate = lastDonationDate;
}
string Donor::getLastDonationDate()
{
	return lastDonationDate;
}
bool Donor::isValidAge(int age)
{
	if (age >= 17 && age <= 60)
		return true;
	else
		return false;
}
bool Donor::isValidDonationAgain(string s)
{
	if (s.empty())
		return true;
	else {
		//assuming that the date in DD/MM/YYYY format
		time_t currentTime = time(nullptr);
		tm currentDate;
		localtime_s(&currentDate, &currentTime);

		int day = stoi(s.substr(0, 2));
		int month = stoi(s.substr(3, 2));
		int year = stoi(s.substr(6, 4));

		int yearsDiff = currentDate.tm_year + 1900 - year;
		int monthsDiff = currentDate.tm_mon + 1 - month;
		int daysDiff = currentDate.tm_mday - day;

		// Adjust years difference if months difference is negative
		if (monthsDiff < 0)
		{
			yearsDiff--;
			monthsDiff += 12;
		}

		// Convert years to months for easier comparison
		int totalMonthsDiff = yearsDiff * 12 + monthsDiff;

		// Check if at least 3 months have passed since the last donation
		if (totalMonthsDiff > 3 || (totalMonthsDiff == 3 && daysDiff >= 0))
			return true;
		else
		
			return false;
	}
}
//choosing diseases from list provided in the main function
void Donor::setDisease(string s)
{
	
	diseases.push_back(s);
}
void Donor::setDiseases(vector<string> diseases)
{
	this->diseases = diseases;
}
vector<string>Donor::getDiseases()
{
	return diseases;
}

bool Donor::hasNoDisease(vector<string> v)
{
	if (v.empty())
		return true;
	else
		return false;
}
bool Donor::eligibilityForDonating()
{
	//checking if the donor matches all the criteria of age and diseases
	if (isValidAge(retrieveAge(dateOfBirth(getSsn())))&&hasNoDisease(getDiseases()))
	return true;
	else
		return false;
}
void Donor::toJson(json& j)
{
	Person::toJson(j);
	j["Last Donation Date"] = getLastDonationDate();
    j["Diseases"] = getDiseases();
}
