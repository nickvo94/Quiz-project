#pragma once
#include "QuizLibrary.h"
class Menu
{
public:
	Menu();
	void display();
	void add();
	void takeQ();
	

	QuizLibrary QandA;
	~Menu();
};

