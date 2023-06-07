#ifndef BLOODBANK_H
#define BLOODBANK_H
#include <vector>
#include "Donor.h"
#include "Recipient.h"
#include "BloodData.h"
#include "queue"
#include <nlohmann/json.hpp>
using namespace std;
class BloodBank
{
	private:
		unordered_map<string,Donor*> donors_;
		unordered_map<string, Recipient*> recipients_;
		unordered_map<string, vector<BloodData>> AvailableBlood;
		string Ssn;
		queue<Recipient*> RequestedRecipient;
public:
	void addPersonData(Person*);
	void readFileIntoJson(const string&, json&);
	void saveToJson(const string&, json&);
	bool Personlogin(string, string, string);
	void printPersonData(string);
	void deletePersonData(string);
	void requestAdonation();
	void updatePersonData(string);
	void displayBloodData();
	void requestBlood();
	void converJsonToMapDonor(json jsonObj);
	void converJsonToMapRecipient(json jsonObj);
	void convertJsontoMapBloodData(json jsonObj);
	void convertMapToJsonDonor(json& jsonObj);
	void convertMaptoJsonRecipient(json& jsonObj);
	void convertMaptoJsonBloodData(json& jsonObj);
};
#endif BLOODBANK_H