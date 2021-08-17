#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include <ctime>
#pragma once

using namespace std;
class Player
{
private:
	string name;
	int score;
public:
	Player() :Player{ "" } {}
	Player(string n) :score{ 0 }, name{ n }{}

	void won() 
	{
		// Increment score
		score++;
	}
	int getScore() { return this->score; }

	string getName() { return this->name; }
};

