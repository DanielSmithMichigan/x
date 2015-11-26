#ifndef utilities_h
#define utilities_h
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <time.h>
	#include <random>

	using namespace std;

	float distanceTo(int x1, int y1, int x2, int y2);
	int randomBetween(int min, int max);
	void nsleep(long miliseconds);
	int absMax(int amount, int max);
#endif