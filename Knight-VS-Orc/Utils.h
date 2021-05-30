#pragma once
#include <iostream>

struct Utils
{
	/// <summary>
	/// Return a random float between min and max
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	static float GetRandomFloat(float min, float max)
	{
		if (!isRandomInitialized)
			InitializeRandom();
		
		return ((float)rand() / RAND_MAX) * (max - min) + min;
	}

	template<typename T>
	static T Clamp(T min, T max, T value)
	{
		return value > max ? max
						   : value < min ? min
										 : value;
	}
	
private:
	static bool isRandomInitialized;

	/// <summary>
	/// Initialize random with srand(time(0))
	/// </summary>
	static void InitializeRandom()
	{
		std::cout << "Initialize Random" << std::endl;
		srand(time(nullptr));
		Utils::isRandomInitialized = true;
		std::cout << "Random Initialized" << std::endl;
	}
};