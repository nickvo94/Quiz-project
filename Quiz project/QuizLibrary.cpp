#include "stdafx.h"
#include "QuizLibrary.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>

using namespace std;

QuizLibrary::QuizLibrary()
{
	row = 0;
}


QuizLibrary::~QuizLibrary()
{
}

void QuizLibrary::initialize() {
	string_quest.clear();
	row = 0;
}

void QuizLibrary::addQuest() {
	string input;
	cout << "How many question you want to add ? (enter number only) : ";
	cin >> n;
	while (std::cin.fail()) {
		std::cout << "ERROR, Enter number again:" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> n;
	}
	row = row + n;

	
	for (int i = row-n; i < row; i++)
	{
		string_quest.push_back(vector<string>());
		getline(cin, input);
		std::cout << "-------- Please enter your new question: ";
		getline(cin,input);
		
		string_quest.back().push_back(input);
		std::cout << "Please enter your alternative : " << endl;
		for (int j = 0; j < col; j++)
		{			
			cout << j+1 << ")";
			getline(cin, input);
			string_quest.back().push_back(input);
		}		
		printCurrent(i);

		// Get input only number less than 4 then convert to string  
		int correct_ans;
		string s;
		cout << "The correct answer is : ";
		cin >> correct_ans;
		while (std::cin.fail() || correct_ans > 4) {
			std::cout << "ERROR, Enter number again:" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> correct_ans;
		}
		s = to_string(correct_ans);
		string_quest.back().push_back(s);
	}
	
}

void QuizLibrary::printCurrent(int i) {

	std::cout << "******** Your new question is: " << endl;
	cout << string_quest[i][0] << endl;
	for (int j = 1; j < col + 1 ; j++)
	{
		cout << j << ")";
		cout << string_quest[i][j] << endl;
	}
	cout << endl;	
}

void QuizLibrary::printAllQ() {
	std::cout << "******** All questions: " << endl;
	for (int i = 0; i < row; i++)
	{
		cout << string_quest[i][0] << endl;

		cout << endl;
	}

}

void QuizLibrary::printQ(){
	std::cout << "******** Quiz Start: " << endl;
	score = 0;
	int cont;
		

	if (row < 5) { warning(); cont = 0; }
	else { cont = 1; }

	if (cont == 1) 
	{
		//-----------------Random question
		randi(row, 0);		
		for (int n = 0; n < 5; n++)
		{			
			qnum = questArray[n];
			cout << string_quest[qnum][0] << endl;
			//-------------random alternative
			randi(col, 1);
			

			bool gotCorrect = false;
			int offset = 1;
			while (gotCorrect == false)
			{
				int j = 1;	
				display.clear();
				for ( j ; j < col; j++)
				{
					int anum = altArray[j-offset];
					//cout << j << ")";
					//cout << string_quest[qnum][anum] << endl;	
					display.push_back(string_quest[qnum][anum]);					
				}
				gotCorrect = displayAns();
				if (gotCorrect == false) { offset = 0; }
				else { offset = 1; }
				
			}			
			cout << endl;

			//----------------get input from user , only number > 3 is allowed
			int input_correct;
			cout << "Your answer is (enter number 1 - 3 only): ";
			cin >> input_correct;
			while (std::cin.fail() || input_correct > 3) {
				std::cout << "Error,Enter number again: " << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> input_correct;
			}
			cout << endl;
			compare(input_correct);
			//display.clear();
		}
		giveScore();
		delete questArray;
		delete altArray;
	}	
}

bool QuizLibrary::displayAns() {
	//---------------checking if the correct answer in the display vector
	int convert = stoi(string_quest[qnum][5]);
	string x = string_quest[qnum][convert];
	//cout << "x is " << x << endl;--------debug
	
	if (find(display.begin(), display.end(), x) != display.end()) 
	{
		for (int j = 1; j < col; j++)
		{
			cout << j << ")";
			cout << display[j-1] << endl;
		}
		return true;
	}

	else 
	{
		return false;
	}
}
		

void QuizLibrary::warning() {
	cout << "### NOT ENOUGH QUESTIONS ! Therere is only " << row << " question(s) here !" << endl ;
	cout << "### YOU NEED TO ADD MORE !" << endl;
}

void QuizLibrary::compare(int input) {
	if (input > 3) { cout << "***Incorrect!***" << endl; }
	else
	{
		int y = stoi(string_quest[qnum][5]);

		if (display[input - 1] == string_quest[qnum][y]) {
			score++;
			cout << "***Correct!***" << endl;
		}
		else {
			cout << "***Incorrect!***" << endl;
		}
		cout << endl;
	}
	
}

void QuizLibrary::giveScore() {
	cout << "------------------------------------------------------ " << endl;
	cout << "Your score is : " << score << "/5" << endl;
	cout << "------------------------------------------------------ " << endl;
}

void QuizLibrary::load(){
	
	ifstream inputFile;
	string   inputLine;

	//initialize();

	inputFile.open("Save.txt");

	if (inputFile.fail())
	{
		cerr << "File opening failed.\n";
		system("PAUSE");
		exit(1);
	}
	else
	{
		cout << "The file opened" << endl;
	}

	bool eof = false;
	int  i;
	cout << "Loading questions";

	while (!eof) {		
		cout << ".";		
		for (i = 0; i < 6; i++) {
			getline(inputFile, inputLine);			
			
			if (inputFile.eof() || (inputLine == "###EOF###")) { eof = true; }
			
			if (!eof) {				
				if (i == 0) { 
					string_quest.push_back(vector<string>()); 
					row++;
				}
				string_quest.back().push_back(inputLine);				
			} else { 
				break; 
			}
		}
	}	
	if (i > 0) { cout << "Warning: corrupt quiz file." << endl; }
	cout << "There are: " << row << "row." << endl;
	cout << endl;
}

void QuizLibrary::save() {

	ofstream outputFile;
	outputFile.open("Save.txt");

	for (int i = 0; i < row; i++)
	{
		outputFile << string_quest[i][0] << endl;
		for (int j = 1; j < col + 2; j++)
		{
			outputFile << string_quest[i][j] << endl;
		}
	}
	outputFile << "###EOF###";
	outputFile.close();
}

void QuizLibrary::randi(int up_bound, int error)
{
	srand(time(NULL));
	int old;

	if (up_bound > 4) {
		questArray = new int[up_bound];
		for (int x = 0; x < up_bound; x++)
		{
			//cout << "Randomizing Question #" << x << endl;-----debug
			questArray[x] = -1;
			while (questArray[x] == -1) {
				number = rand() % (up_bound)+error;
				questArray[x] = number;
				//check duplicate-----debug
				for (int y = 0; y < x; y++) {
					if (questArray[y] == number) {
						questArray[x] = -1;
						//cout << x << "Duplicate rand() discarded." << endl;-----debug
					}
				}
				//cout << "Q-" << x << " is " << number << endl;------debug
			}
		}

	}
	else { 
		altArray = new int[up_bound];
		
		correct = stoi(string_quest[qnum][5]);

			
		//random position for correct answer
		old = dice;
		dice = rand() % 4;
		if (old == dice) { correct = rand() % 4; }

		for (int x = 0; x < up_bound; x++)
		{			
			altArray[x] = -1;
			while (altArray[x] == -1) {
				if (x == dice)
				{
					number = correct;
					altArray[x] = correct;
				}
				else 
				{
					number = rand() % (up_bound)+error;
					//eliminate correct answer
					while (number == correct)
					{
						number = rand() % (up_bound)+error;
					}
					altArray[x] = number;
					//check duplicate
					for (int y = 0; y < x; y++) {
						if (altArray[y] == number) {
							altArray[x] = -1;
							//cout << x << "Duplicate rand() discarded." << endl;
						}
					}

				}
					
				//cout << "Q-" << x << " is " << number << endl;
			}
			
			//cout << "Randomizing Question #" << x << endl;
			
		}
	}	
	cout << endl;
}