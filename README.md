Birthday Reminder 🎉

A C++ and Python project that helps you store and manage birthdays while sending WhatsApp birthday reminders automatically using Python. I know that it can easily be improved and contributions are welcome! However, I wanted to showcase my C++ skills (especially OOP principles) 
and create a program that utilizes both Python and C++

Project Overview

Birthday Reminder allows you to keep track of birthdays by storing the name, date of birth, and phone numbers of people. The system also checks if today is someone’s birthday and sends an automated WhatsApp message via Python.

Prerequisites

	•	C++ compiler (e.g., g++)
	•	Python 3 installed on your machine
	•	The pywhatkit Python library for sending WhatsApp messages

Features

	•	Store birthdays: Easily add, delete, and view birthdays using a C++ interface.
	•	WhatsApp birthday reminders: Automatically send a WhatsApp message on someone’s birthday using Python.
	•	Input validation: The system checks for valid date and phone number formats.
	•	File-based storage: All birthdays are saved to and loaded from a text file.

 The application presents a menu with the following options:
	•	Add a birthday: Input name, birthday (format dd/mm/yyyy or dd.mm.yyyy), and phone number (format +12345678901).
	•	Check today’s birthdays: If a birthday matches today’s date, a WhatsApp message will be sent to the phone number.
	•	Print all birthdays: Displays the list of stored birthdays.
	•	Delete a birthday: Removes a birthday from the list by its index.

Sending WhatsApp Messages:
  When checking today’s birthdays, if there’s a match, the program calls the Python script send_whatsapp.py to send an automated message.
  You can also manually run the Python script to send a message:

  python send_whatsapp.py "Name" "+12345678901"


If it does not run, you may try to change these lines in the addBirthday function
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);
        int currentYear = 1900 + ltm.tm_year;

 You should add these lines instead : 
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int currentYear = 1900 + ltm->tm_year;

 
  Contributions are welcome! 
