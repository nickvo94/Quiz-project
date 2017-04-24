#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class QuizLibrary
{
public:
	QuizLibrary();
	~QuizLibrary();
	void addQuest();
	void printCurrent(int);
	void printAllQ();
	void printQ();
	void save();
	void load();
	void compare(int);
	void initialize();
	void randi(int, int);
	void giveScore();
	void warning();
	bool displayAns();

private:
	std::vector< vector<string> > string_quest;
	std::vector<string> display;

	int dice;
	int row ;
	int col = 4;
	int number;
	int *questArray;
	int *altArray;
	int score;
	int n;
	int correct;
	int qnum;


};

