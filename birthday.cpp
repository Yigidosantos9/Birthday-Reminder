#define _CRT_SECURE_NO_WARNINGS
#include "birthday.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <stdexcept>

using namespace std;

// Birthday class implementation

Birthday::Birthday() : day(0), month(0), year(0) {}

void Birthday::setName(const string& n) {
    name = n;
}

bool Birthday::setDate(const string& dateStr) {
    return parseDate(dateStr, day, month, year);
}

bool Birthday::setPhoneNumber(const string& phone) {
    if (isValidPhoneNumber(phone)) {
        phoneNumber = phone;
        return true;
    }
    return false;
}

string Birthday::getName() const {
    return name;
}

string Birthday::getPhoneNumber() const {
    return phoneNumber;
}

int Birthday::getDay() const {
    return day;
}

int Birthday::getMonth() const {
    return month;
}

int Birthday::getYear() const {
    return year;
}

bool Birthday::parseDate(const string& dateStr, int& day, int& month, int& year) {
    char delimiter;
    stringstream ss(dateStr);
    if (ss >> day >> delimiter >> month >> delimiter >> year) {
        return (day > 0 && day <= 31) && (month > 0 && month <= 12) && (year > 0);
    }
    return false;
}

bool Birthday::isValidPhoneNumber(const string& phoneNumber) {
    regex phoneRegex("^\\+[1-9][0-9]{10,12}$");
    return regex_match(phoneNumber, phoneRegex);
}

void saveBirthdaysToFile(const vector<Birthday>& birthdays) {
    ofstream file("birthdays.txt");
    if (!file) {
        throw runtime_error("Could not open file! Saving failed.");
    }
    for (const auto& b : birthdays) {
        file << b.getName() << " "
            << setw(2) << setfill('0') << b.getDay() << "/"
            << setw(2) << setfill('0') << b.getMonth() << "/"
            << b.getYear() << " " << b.getPhoneNumber() << endl;
    }
    file.close();
}

vector<Birthday> loadBirthdaysFromFile() {
    vector<Birthday> birthdays;
    ifstream file("birthdays.txt");
    if (!file) {
        cerr << "File could not be opened. A new file will be created.\n";
        return birthdays;
    }

    Birthday b;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, dateStr, phoneNumber;

        ss >> name;
        string tempName;

        while (ss >> tempName && tempName.find('/') == string::npos && tempName.find('.') == string::npos) {
            name += " " + tempName;
        }

        dateStr = tempName;
        ss >> phoneNumber;

        b.setName(name);

        if (b.setDate(dateStr)) {
            time_t now = time(0);
            tm* ltm = localtime(&now);
            int currentYear = 1900 + ltm->tm_year;

            if (b.getYear() > currentYear) {
                cerr << "Invalid year! Skipping: " << b.getName() << endl;
                continue;
            }

            if (b.setPhoneNumber(phoneNumber)) {
                birthdays.push_back(b);
            }
            else {
                cerr << "Invalid phone number format found and skipped for: " << b.getName() << endl;
            }
        }
        else {
            cerr << "Invalid date entry found and skipped: " << b.getName() << endl;
        }
    }
    file.close();
    return birthdays;
}
