#ifndef utilities_h
#define utilities_h
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <time.h>
	#include <random>
	#include <vector>
	#include <string>
	#include <iostream>
	#include <dirent.h>
	#include <memory>

	using namespace std;

	float distanceTo(int x1, int y1, int x2, int y2);
	int randomBetween(int min, int max);
	void nsleep(long miliseconds);
	int absMax(int amount, int max);
	void getFilesInFolder(string path, vector<string> &output);
	bool chance(int n);
#endif