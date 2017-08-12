#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

double montePi(int pointNumber, bool writePoints);

int main(int argc, char* argv[])
{
	time_t start = time(NULL);
	int points = 10000000;
	bool writePoints = false;

	for (int i = 1; i < argc; i++)
	{
		if ((strcmp(argv[i], "-p") == 0) || (strcmp(argv[i], "--points") == 0))
		{
			i++;
			if (i < argc && argv[i][0] != '-')
			{
				try
				{
					points = std::stoi(argv[i]);
				}
				catch (const std::exception&)
				{
					std::cout << "-p or --points argument couldn't be converted to int\n";
					return 1;
				}
			}
			else
			{
				std::cout << "-p or --points requires an argument\n";
				return 1;
			}
		}
		if ((strcmp(argv[i], "-f") == 0) || (strcmp(argv[i], "--file") == 0))
		{
			writePoints = true;
		}
	}

	double pi = montePi(points, writePoints);

	std::cout << "Estimation for Pi:\t" << pi << "\nElapsed time:\t\t" << (long)(time(NULL) - start) << " second(s)";
	return 0;
}

double montePi(int pointNumber, bool writePoints)		//returns estimation of Pi
{
	double x = 0.0, y = 0.0;
	double r = 0.0, ratio = 0.0;
	int pointsInside = 0;
	std::ofstream pointLog;

	srand(time(NULL));

	if (writePoints)
	{
		pointLog.open("points.dat");
		pointLog << "x;y;inCircle\n";
	}

	for (int i = 0; i < pointNumber; i++)
	{
		x = (double)rand() / RAND_MAX;			//produce random point with x- and y-coordinate-values between 0 and 1
		y = (double)rand() / RAND_MAX;

		r = sqrt(x*x + y*y);					//calculate distance of the point to the (0,0)-point

		if (r <= 1) {							//if the distance is <= 1 the point is inside the quater-circle
			pointsInside++;
		}

		if (writePoints)
			pointLog << x << ";" << y << ";" << (r <= 1) << "\n";

	}

	if (writePoints)
		pointLog.close();

	ratio = (double)pointsInside / pointNumber;		//the ration between the quater circle with radius = 1 and the square with sidelength = 1 is pi/4 and 
													//should be approached by the ratio of pointsInside and total points

	return 4 * ratio;
}