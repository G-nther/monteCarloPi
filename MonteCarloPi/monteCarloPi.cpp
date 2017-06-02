#include <iostream>
#include <ctime>
#include <cstdlib>

double montePi(int pointNumber);

int main(void)
{
	time_t start = time(NULL);

	double pi = montePi(10000000);

	std::cout << "Estimation for Pi:\t" << pi << "\nElapsed time:\t\t" << (long)(time(NULL) - start) << " second(s)";

	return 0;
}

double montePi(int pointNumber)
{
	double x = 0.0, y = 0.0;
	double r = 0.0, ratio = 0.0;
	int pointsInside = 0;

	srand(time(NULL));

	for (int i = 0; i < pointNumber; i++)
	{
		x = (double)rand() / RAND_MAX;			//produce random point with x- and y-coordinate-values between 0 and 1
		y = (double)rand() / RAND_MAX;

		r = sqrt(x*x + y*y);					//calculate distance of the point to the (0,0)-point

		if (r <= 1) {							//if the distance is <= 1 the point is inside the quater-circle
			pointsInside++;
		}
	}

	ratio = (double)pointsInside / pointNumber;		//the ration between the quater circle with radius = 1 and the square with sidelength = 1 is pi/4 and 
													//should be approached by the ratio of pointsInside and total points

	return 4 * ratio;
}