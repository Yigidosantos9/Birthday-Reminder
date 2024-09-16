#define _CRT_SECURE_NO_WARNINGS
#include "birthday.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

void addBirthday(vector<Birthday>& birthdays) {
    Birthday b;
    cout << "Enter the following details to add a new birthday:\n";

    cout << "Name: ";
    cin.ignore();
    string name;
    getline(cin, name);
    b.setName(name);

    cout << "Enter birthday (format: dd.mm.yyyy or dd/mm/yyyy, e.g., 11.09.2024 or 11/09/2024): ";
    string dateStr;
    cin >> dateStr;

    if (b.setDate(dateStr)) {
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);
        int currentYear = 1900 + ltm.tm_year;

        if (b.getYear() > currentYear) {
            cerr << "Invalid year! Birthday not added.\n";
            return;
        }

        cout << "Enter phone number (format: +12345678901): ";
        string phoneNumber;
        cin.ignore();
        getline(cin, phoneNumber);

        // Remove all spaces from the phone number
        phoneNumber.erase(remove(phoneNumber.begin(), phoneNumber.end(), ' '), phoneNumber.end());

        if (b.setPhoneNumber(phoneNumber)) {
            birthdays.push_back(b);
            try {
                saveBirthdaysToFile(birthdays);
                cout << "Birthday added successfully!\n";
            }
            catch (const runtime_error& e) {
                cerr << e.what() << endl;
            }
        }
        else {
            cerr << "Invalid phone number format! Birthday not added.\n";
        }
    }
    else {
        cerr << "Invalid date format! Birthday not added.\n";
    }
}

void deleteBirthday(vector<Birthday>& birthdays) {
    if (birthdays.empty()) {
        cout << "No birthdays available to delete.\n";
        return;
    }

    cout << "Enter the number of the birthday you want to delete: ";
    size_t index;
    cin >> index;

    if (index > 0 && index <= birthdays.size()) {
        birthdays.erase(birthdays.begin() + (index - 1));  // -1 because the index starts from 0
        try {
            saveBirthdaysToFile(birthdays);
            cout << "Birthday deleted successfully!\n";
        }
        catch (const runtime_error& e) {
            cerr << e.what() << endl;
        }
    }
    else {
        cout << "Invalid index! No birthday deleted.\n";
    }
}

void sendBirthdayReminder(const string& name, const string& phoneNumber) {
    string command = "python send_whatsapp.py \"" + name + "\" \"" + phoneNumber + "\"";
    system(command.c_str());
}

void checkTodaysBirthdays(const vector<Birthday>& birthdays) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int todayDay = ltm->tm_mday;
    int todayMonth = 1 + ltm->tm_mon;

    bool found = false;
    for (const auto& b : birthdays) {
        if (b.getDay() == todayDay && b.getMonth() == todayMonth) {
            cout << "Today is " << b.getName() << "'s birthday!" << endl;
            sendBirthdayReminder(b.getName(), b.getPhoneNumber());
            found = true;
        }
    }
    if (!found) {
        cout << "No birthdays today.\n";
    }
}

void printAll(const vector<Birthday>& birthdays) {
    if (birthdays.empty()) {
        cout << "File is empty!\n";
    }
    else {
        int cnt = 1;
        for (const auto& b : birthdays) {
            cout << cnt << ") Name: " << b.getName()
                << " | Birthday: "
                << setw(2) << setfill('0') << b.getDay() << "."
                << setw(2) << setfill('0') << b.getMonth() << "."
                << b.getYear()
                << " | Phone number: " << b.getPhoneNumber()
                << endl;
            cnt++;
        }
    }
}

int main() {
    vector<Birthday> birthdays = loadBirthdaysFromFile();
    int choice;

    do {
        cout << "\nBirthday Reminder Application\n";
        cout << "1. Add a birthday\n";
        cout << "2. Check today's birthdays\n";
        cout << "3. Print all\n";
        cout << "4. Delete a birthday by list number\n";
        cout << "5. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBirthday(birthdays);
            break;
        case 2:
            checkTodaysBirthdays(birthdays);
            break;
        case 3:
            printAll(birthdays);
            break;
        case 4:
            deleteBirthday(birthdays);
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}
