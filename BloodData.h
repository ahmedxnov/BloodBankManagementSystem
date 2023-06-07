#ifndef BLOODDATA_H
#define BLOODDATA_H
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <string>
using namespace std;
class BloodData
{
private:
	string type;
	string recieveDate;
	string expiryDate;
public:
	BloodData(string ,string, string);
	BloodData(json);
	void setType(string);
	void setRecieveDate(string);
	void setExpiryDate(string);
	string getType();
	string getRecieveDate();
	string getExpiryDate();
	void toJson(json&);
};
#endif BLOODDATA_H