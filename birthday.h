#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Birthday {
private:
    string name;
    int day;
    int month;
    int year;
    string phoneNumber;

public:
    Birthday();

    // Setters
    void setName(const string& n);
    bool setDate(const string& dateStr);
    bool setPhoneNumber(const string& phone);

    // Getters
    string getName() const;
   string getPhoneNumber() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // Static utility functions
    static bool parseDate(const string& dateStr, int& day, int& month, int& year);
    static bool isValidPhoneNumber(const string& phoneNumber);
};

// Function declarations for handling file operations
void saveBirthdaysToFile(const vector<Birthday>& birthdays);
vector<Birthday> loadBirthdaysFromFile();

