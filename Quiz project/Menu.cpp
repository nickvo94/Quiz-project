#include "stdafx.h"
#include "QuizLibrary.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


Menu::Menu()
{
	
}

void Menu::display() {
	int input;	
	bool start = true;
	while (start)
	{
		//QandA.load();
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "# WARNING : you need to RELOAD quiz from the file first OR ADD at least 5 new   questions to take the quiz " << endl;
		cout << "----------Menu----------" << endl;
		cout << "1.Initialize( clear all questions)" << endl;
		cout << "2.Save to the file " << endl;
		cout << "3.ReLoad file  " << endl;
		cout << "4.Add new questions " << endl;
		cout << "5.Take the quiz " << endl;
		cout << "6.Print out " << endl;
		cout << "7.Exit without save " << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
				cout << "---------- Enter a number to choose :  " ;
		cin >> input;
		while (std::cin.fail()) {
			std::cout << "Error,Enter number again: " << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> input;
		}
		
		switch (input)
		{
		case 1:
			cout << "----------Initialize---------- " << endl;
			QandA.initialize();
			break;
		case 2:
			cout << "----------Save questions---------- " << endl;
			QandA.save();
			break;
		case 3:
			cout << "----------ReLoad----------  " << endl;
			QandA.load();
			break;
		case 4:
			cout << "----------Add new questions---------- " << endl;
			add();
			break;
		case 5:
			cout << "----------Take the quiz---------- " << endl;
			takeQ();
			break;
		case 6:
			cout << "----------Print out---------- " << endl;
			QandA.printAllQ();
			break;
		case 7:
			cout << "Exit " << endl;
			start = false;
			break;
		}
	}
	
}

void Menu::takeQ() {
	QandA.printQ();
	
}

void Menu::add() {
	cout << "********** Enter your new question here ******** " << endl;
	QandA.addQuest();
}



Menu::~Menu()
{
}
