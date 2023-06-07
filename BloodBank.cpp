#pragma warning(suppress: 28020)
#pragma warning(disable: 26495)
#include "BloodBank.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <ctime>
#include <nlohmann/json.hpp>
#include "BloodData.h"
#include <memory>
using namespace std;
void BloodBank::readFileIntoJson(const string& filePath, json& json)
{
    ifstream inputFile(filePath);
    inputFile >> json;
    inputFile.close();
}
void BloodBank::saveToJson(const string& filePath, json& json)
{
    ofstream outputFile(filePath);
    outputFile << json.dump(4); // The second parameter sets the indentation level
    outputFile.close();
}
void BloodBank::converJsonToMapDonor(json jsonObj)
{
    for (auto& p : jsonObj.items())
    {
        Donor temp(p.value());
        donors_[p.key()] = new Donor(temp);
    }
}
void BloodBank::converJsonToMapRecipient(json jsonObj)
{
    for (auto& p : jsonObj.items())
    {
        Recipient temp(p.value());
        recipients_[p.key()] = new Recipient(temp);
    }
}
void BloodBank::convertJsontoMapBloodData(json jsonObj)
{
    for (auto& p : jsonObj.items())
    {
        vector<BloodData> temp;
        for (BloodData bd : p.value())
        {
            temp.push_back(bd);
        }
        AvailableBlood[p.key()] = temp;
    }
}
void BloodBank::convertMapToJsonDonor(json& jsonObj)
{
    for (auto& p : donors_)
    {
        json values;
        p.second->toJson(values);
        jsonObj[p.first] = values;
    }
}
void BloodBank::convertMaptoJsonRecipient(json& jsonObj)
{
    for (auto& p : recipients_)
    {
        json values;
        p.second->toJson(values);
        jsonObj[p.first] = values;
    }
}
void BloodBank::convertMaptoJsonBloodData(json& jsonObj)
{
    for (auto& p : AvailableBlood)
    {
        json arrayOfValues = json::array();
        for (BloodData bd : p.second)
        {
            json values = json::object();
            bd.toJson(values);
            arrayOfValues.push_back(values);
        }
        jsonObj[p.first] = arrayOfValues;
    }
}
void BloodBank::addPersonData(Person* person)
{
    if (Donor* donor = dynamic_cast<Donor*>(person))
    {
        if (donor->eligibilityForDonating())
        {
            donors_.clear();

            // Load the existing JSON data from the file
            json jsonObj;
            readFileIntoJson("data.json", jsonObj);

            // Check if the SSN already exists in the JSON data
            if (jsonObj.contains(donor->getSsn()))
            {
                cout << "SSN " << donor->getSsn() << " already exists. Please choose a different SSN." << endl;
                return;
            }

            //converting the json object to unordered_map donor_
            converJsonToMapDonor(jsonObj);

            //Add eligible donor to the map
            donors_[donor->getSsn()] = donor;

            //clearing the old json object
            jsonObj.clear();

            // Convert the updated unordered_map to json object
            convertMapToJsonDonor(jsonObj);

            // Save the updated JSON data to the file
            saveToJson("data.json", jsonObj);

            cout << "Sign up done" << endl;
        }
        else
        {
            cout << "You are not eligible for donating" << endl;
        }
    }
    else if (Recipient* recipient = dynamic_cast<Recipient*>(person))
    {
        recipients_.clear();

        // Load the existing JSON data from the file
        json jsonObj;
        readFileIntoJson("data2.json", jsonObj);

        // Check if the SSN already exists in the JSON data
        if (jsonObj.contains(recipient->getSsn()))
        {
            cout << "SSN " << recipient->getSsn() << " already exists. Please choose a different SSN." << endl;
            return;
        }

        //convert the json object to unordered_map recipeint_
        converJsonToMapRecipient(jsonObj);

        //Add the new recipient to the map
        recipients_[recipient->getSsn()] = recipient;

        //clearing the old json object
        jsonObj.clear();

        //converting the updated unordered_map to json object
        convertMaptoJsonRecipient(jsonObj);

        //Save the updated JSON data to the file
        saveToJson("data2.json", jsonObj);
        cout << "Sign up done" << endl;
    }
}

bool BloodBank::Personlogin(string ssn, string password, string type)
{
    json jsonObj;

    if (type == "donor")
    {
        donors_.clear();
        //reading the json file of donors to a json object
        readFileIntoJson("data.json", jsonObj);

        //converting the json object to unoredered_map recipient
        converJsonToMapDonor(jsonObj);

        // Check if the SSN key exists in the unordered_map
        if (donors_.find(ssn) != donors_.end())
        {
            //check if the password matches
            if (donors_[ssn]->getPassword() == password)
            {
                Ssn = ssn;
                return true; // Password match found, login successful
            }
            else
            {
                system("cls");
                cout << "Invalid username or password" << endl;
                return false; // Password does not match
            }
        }
        else
        {
            cout << "Invalid username or password";
            return false; // SSN does not exist in the unordered_map
        }
    }
    else if (type == "recipient")
    {
        recipients_.clear();

        //reading the json file of donors to a json object
        readFileIntoJson("data2.json", jsonObj);

        //converting the json object to unordered_map of recipient_
        converJsonToMapRecipient(jsonObj);

        //checking if the ssn exist in the map
        if (recipients_.find(ssn) != recipients_.end())
        {
            //check if the password matches
            if (recipients_[ssn]->getPassword() == password)
            {
                Ssn = ssn;
                return true; // Password match found, login successful
            }
            else
            {
                system("cls");
                cout << "Invalid username or password" << endl;
                return false; // Password does not match
            }
        }
        else
        {
            cout << "Invalid username or password";
            return false; // SSN does not exist in the unordered_map
        }
    }
}


void BloodBank::printPersonData(string type)
{
    json jsonObj = json::object();
    if (type == "donor")
    {
        donors_.clear();
        readFileIntoJson("data.json", jsonObj);
        converJsonToMapDonor(jsonObj);
        cout << "SSN: " << donors_[Ssn]->getSsn() << endl;
        cout << "Name: " << donors_[Ssn]->getName() << endl;
        cout << "Age: " << donors_[Ssn]->retrieveAge(donors_[Ssn]->dateOfBirth(donors_[Ssn]->getSsn())) << endl;
        cout << "Mail: " << donors_[Ssn]->getMail() << endl;
        cout << "Gender: " << donors_[Ssn]->getGender() << endl;
        cout << "Blood Type: " << donors_[Ssn]->getBloodType() << endl;
        cout << "Last Donation Date: " << donors_[Ssn]->getLastDonationDate() << endl;
        cout << "Diseases: ";
        for (string p : donors_[Ssn]->getDiseases())
        {
            cout << p << ", ";
        }
        cout << endl;
    }
    else {
    recipients_.clear();
    readFileIntoJson("data2.json", jsonObj);
    converJsonToMapRecipient(jsonObj);
    cout << "SSN: " << recipients_[Ssn]->getSsn() << endl;
    cout << "Name: " << recipients_[Ssn]->getName() << endl;
    cout << "Age: " << recipients_[Ssn]->retrieveAge(recipients_[Ssn]->dateOfBirth(recipients_[Ssn]->getSsn())) << endl;
    cout << "Mail: " << recipients_[Ssn]->getMail() << endl;
    cout << "Gender: " << recipients_[Ssn]->getGender() << endl;
    cout << "Blood Type: " << recipients_[Ssn]->getBloodType() << endl;
    cout << "Hospital: " << recipients_[Ssn]->getHospital() << endl;
    cout << "Doctor: " << recipients_[Ssn]->getDoctor() << endl;
    }
}
void BloodBank::requestAdonation()
{
    vector<BloodData> v;
    // Load the existing content of data3.json into jsonObj2
    json jsonObj2;
    json jsonObj;

    readFileIntoJson("data3.json", jsonObj2);
    AvailableBlood.clear();
    convertJsontoMapBloodData(jsonObj2);

    readFileIntoJson("data.json", jsonObj);

    Donor donor(jsonObj[Ssn]);

    if (donor.hasNoDisease(donor.getDiseases()))
    {
        if (donor.isValidDonationAgain(donor.getLastDonationDate()))
        {
            string lastDonationDate;
            time_t currentTime = time(nullptr);
            tm currentDate;
            localtime_s(&currentDate, &currentTime);
            string day;
            string month;
            string year;

            if (currentDate.tm_mday >= 10)
                day = to_string(currentDate.tm_mday);
            else
                day = "0" + to_string(currentDate.tm_mday);

            if ((currentDate.tm_mon + 1) < 10)
                month = "0" + to_string(currentDate.tm_mon + 1);
            else
                month = to_string(currentDate.tm_mon + 1);

            year = to_string(currentDate.tm_year + 1900);
            string currentDatestr = day + "/" + month + "/" + year;
            lastDonationDate = currentDatestr;
            currentDate.tm_mday += 42;
            mktime(&currentDate);
            if (currentDate.tm_mday >= 10)
                day = to_string(currentDate.tm_mday);
            else
                day = "0" + to_string(currentDate.tm_mday);

            if ((currentDate.tm_mon + 1) < 10)
                month = "0" + to_string(currentDate.tm_mon + 1);
            else
                month = to_string(currentDate.tm_mon + 1);

            string futureDatestr = day + "/" + month + "/" + year;
            BloodData bd(donor.getBloodType(), currentDatestr, futureDatestr);

            AvailableBlood[donor.getBloodType()].push_back(bd);
            /* if (jsonObj2.contains(donor.getBloodType()))
             {
                 json values = json::array();
                 values = jsonObj2[donor.getBloodType()];
                 if (values.is_array())
                 {
                     for (auto& p : values)
                     {
                         v.push_back(p);
                     }
                 }
             }*/
            cout << "Requested successfully" << endl;
            donor.setLastDonationDate(lastDonationDate);

            // Update the last donation date directly in jsonObj
            jsonObj[Ssn]["Last Donation Date"] = lastDonationDate;
            convertMaptoJsonBloodData(jsonObj2);

            /*
            //save BlooData
           for (auto& p : AvailableBlood)
           {
               json values = json::array();
               for (BloodData& bd : p.second)
               {
                   json tmp;
                   bd.toJson(tmp);
                   values.push_back(tmp);
               }
               jsonObj2[p.first] = values;
           }
           */

           //Save the updated JSON data to the file
            saveToJson("data.json", jsonObj);
            saveToJson("data3.json", jsonObj2);

        }
        else
        {
            cout << "You have to wait for at least 3 months to donate again\n";
        }
    }
    else
        cout << "Your are not eligible for donating due to diseases\n";
}

void BloodBank::deletePersonData(string type)
{
    json jsonObj = json::object();
    if (type == "donor")
    {
        //clearing the old map
        donors_.clear();

        //load existing file to JSON object
        readFileIntoJson("data.json", jsonObj);

        //converting JSON object to unordered_map
        converJsonToMapDonor(jsonObj);

        //clearing the old data in json obj
         jsonObj.clear();

         //deleting from the unordered_map
         donors_.erase(Ssn);

         //converting the unordered_map to JSON object
         convertMapToJsonDonor(jsonObj);

         //saving the updated JSON object
            cout << "Account is deleted\n";
            saveToJson("data.json", jsonObj);
    }
    else if (type == "recipient")
    {
        //clearing the old map
        recipients_.clear();

        //load existing file to JSON object
        readFileIntoJson("data2.json", jsonObj);

        //converting JSON object to unordered_map
        converJsonToMapRecipient(jsonObj);

        //clearing the old data in json obj
        jsonObj.clear();

        //deleting from the unordered_map
        recipients_.erase(Ssn);

        //converting the unordered_map to JSON object
        convertMaptoJsonRecipient(jsonObj);

        //saving the updated JSON object
        cout << "Account is deleted\n";
        saveToJson("data2.json", jsonObj);
    }
}
void BloodBank::updatePersonData(string type)
{
    int option;
    string newValue;
    string oldSsn;
    bool ssnChanged = false;
    string filePath;
    if (type == "donor")
    {
        filePath = "data.json";
        json jsonObj;
        readFileIntoJson(filePath, jsonObj);
        json values = jsonObj[Ssn];
        Donor donor(values);
        cout << "Enter the number corresponding to the attribute you want to update:\n";
        cout << "1. SSN\n";
        cout << "2. Name\n";
        cout << "3. Mail\n";
        cout << "4. Password\n";
        cout << "5. Gender\n";
        cout << "6. Blood Type\n";
        cout << "7. Last Donation Date\n";
        cout << "8. Diseases\n";
        cout << "9. to exit\n";
        cin >> option;
        system("cls");
        switch (option) {
        case 1:
            // Update SSN
            cout << "Enter the new SSN: ";
            cin >> newValue;
            if (jsonObj.contains(newValue))
            {
                cout << "this ssn already exists, no change is done\n";
                break;
            }
            else {
                oldSsn = Ssn;
                Ssn = newValue;
                donor.setSsn(newValue);
                ssnChanged = true;
                break;
            }
        case 2:
            // Update Name
            cout << "Enter the new Name: ";
            cin.ignore();
            getline(cin, newValue);
            donor.setName(newValue);
            break;
        case 3:
            // Update Mail
            cout << "Enter the new Mail: ";
            cin.ignore();
            getline(cin, newValue);
            donor.setMail(newValue);
            break;
        case 4:
            // Update Password
            cout << "Enter the new Password: ";
            cin.ignore();
            getline(cin, newValue);
            donor.setPassword(newValue);
            break;
        case 5:
            // Update Gender
            cout << "Enter the new Gender: ";
            cin.ignore();
            getline(cin, newValue);
            donor.setGender(newValue);
            break;
        case 6:
            // Update Blood Type
            cout << "Enter the new Blood Type: ";
            cin.ignore();
            getline(cin, newValue);
            donor.setBloodType(newValue);
            break;
        case 7:
            // Update Last Donation Date
            cout << "Enter the new Last Donation Date: ";
            cin.ignore();
            getline(cin, newValue);
            donor.setLastDonationDate(newValue);
            break;
        case 8:
        {
            int opt;
            if (donor.getDiseases().size() == 0)
            {
                cout << "Enter the new disease: ";
                cin.ignore();
                getline(cin, newValue);
                donor.setDisease(newValue);
            }
            else
            {
                cout << "Do you want to delete a disease or add a disease? Enter 1 to delete, 2 to add: ";
                cin >> opt;
                if (opt == 1)
                {
                    vector<string> temp;
                    temp = donor.getDiseases();
                    int c = 1;
                    for (string s : temp)
                    {
                        cout << c << ". " << s << endl;
                        c++;
                    }
                    cout << "Select the disease you want to delete: ";
                    cin >> opt;

                    if (opt >= 1 && opt <= temp.size())
                    {
                        temp.erase(temp.begin() + opt - 1);
                        donor.setDiseases(temp);
                    }
                    else
                    {
                        cout << "Invalid option. No disease deleted." << endl;
                    }
                }
                else if (opt == 2)
                {
                    cout << "Enter the new disease: ";
                    cin.ignore();
                    getline(cin, newValue);
                    donor.setDisease(newValue);
                }
                else
                {
                    cout << "Invalid option." << endl;
                }
            }
            break;
        }
        case 9:
            break;
        }
        if (ssnChanged)
        {
            jsonObj.erase(oldSsn);
        }
        donor.toJson(values);
        jsonObj[Ssn] = values;
        saveToJson("data.json", jsonObj);
    }
    else if (type == "recipient")
    {
        json jsonObj;
        readFileIntoJson("data2.json", jsonObj);
        json values = jsonObj[Ssn];
        Recipient recipient(values);
        cout << "Enter the number corresponding to the attribute you want to update:\n";
        cout << "1. SSN\n";
        cout << "2. Name\n";
        cout << "3. Mail\n";
        cout << "4. Password\n";
        cout << "5. Gender\n";
        cout << "6. Blood Type\n";
        cout << "7. Hospital\n";
        cout << "8. Doctor\n";
        cin >> option;
        system("cls");
        switch (option) {
        case 1:
            // Update SSN
            cout << "Enter the new SSN: ";
            cin.ignore();
            getline(cin, newValue);
            if (jsonObj.contains(newValue))
            {
                cout << "this ssn already exists, no change is done\n";
                break;
            }
            else {
                oldSsn = Ssn;
                Ssn = newValue;
                recipient.setSsn(newValue);
                ssnChanged = true;
                break;
            }
        case 2:
            // Update Name
            cout << "Enter the new Name: ";
            cin.ignore();
            getline(cin, newValue);
            recipient.setName(newValue);
            break;
        case 3:
            // Update Mail
            cout << "Enter the new Mail: ";
            cin.ignore();
            getline(cin, newValue);
            recipient.setMail(newValue);
            break;
        case 4:
            // Update Password
            cout << "Enter the new Password: ";
            cin.ignore();
            getline(cin, newValue);
            recipient.setPassword(newValue);
            break;
        case 5:
            // Update Gender
            cout << "Enter the new Gender: ";
            cin.ignore();
            getline(cin, newValue);
            recipient.setGender(newValue);
            break;
        case 6:
            // Update Blood Type
            cout << "Enter the new Blood Type: ";
            cin.ignore();
            getline(cin, newValue);
            recipient.setBloodType(newValue);
            break;
        case 7:
            // Update Hospital
            cout << "Enter the new Hospital: ";
            cin.ignore();
            getline(cin, newValue);
            recipient.setHospital(newValue);
            break;
        case 8:
            // Update Doctor
            cout << "Enter the new Doctor: ";
            cin.ignore();
            getline(cin, newValue);
            recipient.setDoctor(newValue);
            break;
        }
        system("cls");
        if (ssnChanged)
        {
            jsonObj.erase(oldSsn);
        }
        recipient.toJson(values);
        jsonObj[Ssn] = values;
        saveToJson("data2.json", jsonObj);
    }
}
void BloodBank::displayBloodData()
{
    // Load the content of data3.json into jsonObj2
    json jsonObj;
    readFileIntoJson("data3.json", jsonObj);

    AvailableBlood.clear();
    //converting the JSON object to map
    convertJsontoMapBloodData(jsonObj);
    for (auto& p : AvailableBlood)
    {
        //printing the bloodType
        if (p.second.size() == 0)
            continue;
        else {
            cout << "Blood Type " << p.first <<":\n";
            int count = 1;
            for (BloodData& b : p.second)
            {
                cout << "Data of blood bag " << count << ":\n";
                cout << "Donation Date: " << b.getRecieveDate() << endl;
                cout << "Expiration Date: " << b.getExpiryDate() << endl;
                cout << endl;
                count++;
            }
        }
            cout << "Quantity of " << p.first << ": " << p.second.size() << endl;
            cout << "---------------------" << endl;
    }


    /*
    // Iterate over each blood type
    for (auto& p : jsonObj2.items())
    {
        // Iterate over each blood data entry
        for (json& bloodData : p.value())
        {
            cout << "Blood Type: " << bloodData["Type"] << endl;
            cout << "Donation Date: " << bloodData["Recieve Date"] << endl;
            cout << "Expiration Date: " << bloodData["Expiry Date"] << endl;
        }
        if (p.value().size() != 0)
        {
            cout << "Quantity of "<<p.key() << ": " << p.value().size() << endl;
            cout << "---------------------" << endl;
        }
    }
    */
}
void BloodBank::requestBlood()
{
    string bloodtype;
    int quantity;
    json jsonobj;
    readFileIntoJson("data3.json", jsonobj);
    AvailableBlood.clear();
    convertJsontoMapBloodData(jsonobj);

    cout << "Enter the blood type you want: ";
    cin >> bloodtype;
    cout << "Enter the quantity you want: ";
    cin >> quantity;
    if (AvailableBlood.find(bloodtype) != AvailableBlood.end())
    {
        if (AvailableBlood[bloodtype].size() >= quantity)
        {
            for (int i = 1; i <= quantity; i++)
            {
                AvailableBlood[bloodtype].pop_back();
            }
            cout << "You have recieved " << quantity << " bags of " << bloodtype << " blood type.\n";
        }
        else {
            cout << "No enough blood bags available, there is only " << AvailableBlood[bloodtype].size() << " blood bags left!\n";
        }
    }
    else {
        cout << bloodtype << " blood type is not available right now\n";
    }
    convertMaptoJsonBloodData(jsonobj);
    saveToJson("data3.json",jsonobj);
    /*int quantity;
    string bloodType;

    // Load the content of data3.json into jsonObj2
    json jsonObj;
    readFileIntoJson("data3.json", jsonObj);

    cout << "Enter the blood type you want: ";
    cin >> bloodType;
    // Check if the blood type exists in the data
    if (jsonObj.contains(bloodType)&&jsonObj[bloodType].size()!=0)
    {
        cout << "Blood type " << bloodType << " is available" << endl;
        cout << "Enter the quantity do you want: ";
        cin >> quantity;
        for (auto& p : jsonObj.items())
        {
            if (p.key() == bloodType)
            {
                vector<BloodData> v;
                for (BloodData bd : p.value())
                {
                    v.push_back(bd);
                }
                if (v.size() < quantity)
                {
                    cout << "No enough quantities in the blood bank for " << p.key() << " blood type";
                }
                else
                {
                    for (int i = 1; i <= quantity;i++)
                    {
                        v.pop_back();
                    }
                }
                json values = json::array();
                for (auto& bd : v)
                {
                    json j = json::object();
                    bd.toJson(j);
                    values.push_back(j);
                }
                jsonObj[p.key()] = values;
            }
        }
        saveToJson("data3.json", jsonObj);
        cout << "Requested successfully" << endl;
    }
    else
    {
        cout << "Blood type " << bloodType << " is not available" << endl;
        RequestedRecipient.push(recipients_[Ssn]);
        cout << "Your added to the waiting list" << endl;
    }*/
}