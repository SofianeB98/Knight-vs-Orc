#pragma once
#include <iostream>
#include <sstream>

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

	/// <summary>
	/// Clamp the specific value between min and max
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	template<typename T>
	static T Clamp(T value, T min, T max)
	{
		return value > max ? max
						   : value < min ? min
										 : value;
	}

	static std::string ToString(double _value, int _precision)
	{
		std::ostringstream out;
		out.precision(_precision);
		out << std::fixed << _value;
		return out.str();
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