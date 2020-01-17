// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <windows.h>
#include <iostream>
#include <chrono>
#include <algorithm>

void draw(float m)
{
	const int range = 50;
	int mId = range * m;
	for (int i = 0; i <= range; ++i)
	{
		if (mId == i)
			std::cout << "+";
		else
			std::cout << "-";
	}
}

int main()
{
	float marker = 0.5f;
	
	std::chrono::high_resolution_clock timer;
	auto prev = timer.now();
	while (true)
	{
		system("CLS");
		auto now = timer.now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - prev).count() / 1000.0f; //DELTATIME WAS LESS THAN 1 MILLISECOND SO THAT IS WHY I USED THIS
		prev = now;
		//std::cout << deltaTime << std::endl;

		const float deltaMove = deltaTime * 0.001f;
		if (GetAsyncKeyState(VK_LEFT))
		{
			marker -= deltaMove;
			marker = max(marker, 0.0f);
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			marker += deltaMove;
			marker = min(marker, 1.0f);
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}

		draw(marker);
	}

	float accumulator = 0.0f;

	return 0;
}