#pragma once
#include <string>
class Score
{
public:
	int value = 0;
	std::string userName = ""; 


	Score()
	{
		value = 0;
		userName = "";
	}

	Score(int val, string user)
	{
		value = val;
		userName = user;
	}
};

