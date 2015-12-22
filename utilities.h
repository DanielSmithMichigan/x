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
	#include <fstream>

	using namespace std;

	float distanceTo(int x1, int y1, int x2, int y2);
	int randomBetween(int min, int max);
	void nsleep(long miliseconds);
	int absMax(int amount, int max);
	void getFilesInFolder(string path, vector<string> &output);
	bool chance(int n);
	double getRotationFromPoints(double x1, double y1, double x2, double y2);
	double getScalingFromPoints(double x1, double y1, double x2, double y2, double origWidth);
	double hypotenuse(double a, double b);
	double distanceBetween(double x1, double y1, double x2, double y2);
	double findAngle(double x1, double y1, double x2, double y2, double x3, double y3);
	double cosineLaw(double a, double b, double c);
	void writeToFile(double text, string filename);
#endif