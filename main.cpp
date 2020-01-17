#include <windows.h>
#include <iostream>
#include <chrono>
#include <algorithm>
#undef min
#undef max
#undef clamp

float clamp(float v, float a, float b)
{
	return std::min(std::max(v, a), b);
}

void draw(float target, float current)
{
	const int range = 100;
	int indexTarget = (int)(range * (target + 1.0f) * 0.5f);
	int indexCurrent = (int)(range * (current + 1.0f) * 0.5f);
	for (int i = 0; i <= range; ++i)
	{
		if (indexTarget == indexCurrent && indexTarget == i)
			std::cout << 'S';
		else if (indexTarget == i || indexCurrent == i)
			std::cout << (char)((indexTarget == i) ? 'T' : 'C');
		else
			std::cout << '-';
	}
}

int main()
{
	float target = 0.0f;
	float current = 0.0f;

	float velocity = 0.0f;

	std::chrono::high_resolution_clock timer;
	auto prev = timer.now();
	while (true)
	{
		system("CLS");
		auto now = timer.now();
		float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - prev).count() * 0.001f;
		prev = now;

		const float deltaMove = deltaTime * 2.0f;
		if (GetAsyncKeyState(VK_LEFT))
		{
			target -= deltaMove;
			target = std::max(target, -1.0f);
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			target += deltaMove;
			target = std::min(target, 1.0f);
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}

		draw(target, current);

		const float delta = current - target;
		const float dampMult = 4.0f - clamp(std::abs(delta), 0.1f, 1.0f);
		const float dampForce = -dampMult * velocity;
		const float k = 25.0f;
		const float pullForce = -k * delta + dampForce;
		velocity += pullForce * deltaTime;
		current += velocity * deltaTime;
	}

	return 0;
}