#include "BloodData.h"
BloodData::BloodData(string type, string recieveDate, string expiryDate)
{
	this->type = type;
	this->recieveDate = recieveDate;
	this->expiryDate = expiryDate;
}
BloodData::BloodData(json j)
{
	setType(j["Type"]);
	setRecieveDate(j["Recieve Date"]);
	setExpiryDate(j["Expiry Date"]);
}
void BloodData::setType(string type)
{
	this->type = type;
}
void BloodData::setRecieveDate(string recieveDate)
{
	this->recieveDate = recieveDate;;
}
void BloodData::setExpiryDate(string expiryDate)
{
	this->expiryDate = expiryDate;
}
string BloodData::getType()
{
	return type;
}
string BloodData::getRecieveDate()
{
	return recieveDate;
}
string BloodData::getExpiryDate()
{
	return expiryDate;
}
void BloodData::toJson(json& j)
{
	j = json{ {"Type",getType()},{"Recieve Date",getRecieveDate()},{"Expiry Date",getExpiryDate()} };
}