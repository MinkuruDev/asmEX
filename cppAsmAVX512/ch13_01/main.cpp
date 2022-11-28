#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

extern "C" double g_PI = M_PI;
extern "C" bool Avx512CalcSphereAreaVol_(double* sa, double* vol, double radius, double error_val);

bool Avx512CalcSphereAreaVolCpp(double* sa, double* vol, double radius, double error_val)
{
	bool rc;
	if (radius < 0.0)
	{
		*sa = error_val;
		*vol = error_val;
		rc = false;
	}
	else
	{
		*sa = 4.0 * g_PI * radius * radius;
		*vol = *sa * radius / 3.0;
		rc = true;
	}
	return rc;
}
int main()
{
	const double error_val = numeric_limits<double>::quiet_NaN();

	const double radii[] = { -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, -7.0, 10.0, -18.0, 20.0 };
	int num_r = sizeof(radii) / sizeof(double);
	string sp{ " " };
	string sep(75, '-');
	cout << setw(10) << "radius" << sp;
	cout << setw(6) << "rc1" << sp;
	cout << setw(6) << "rc2" << sp;
	cout << setw(10) << "sa1" << sp;
	cout << setw(10) << "sa2" << sp;
	cout << setw(10) << "vol1" << sp;
	cout << setw(10) << "vol2" << '\n';
	cout << sep << '\n';
	cout << fixed << setprecision(4);
	for (int i = 0; i < num_r; i++)
	{
		double sa1, sa2;
		double vol1, vol2;
		double r = radii[i];
		bool rc1 = Avx512CalcSphereAreaVolCpp(&sa1, &vol1, r, error_val);
		bool rc2 = Avx512CalcSphereAreaVol_(&sa2, &vol2, r, error_val);
		cout << setw(10) << r << sp;
		cout << setw(6) << boolalpha << rc1 << sp;
		cout << setw(6) << boolalpha << rc2 << sp;
		cout << setw(10) << sa1 << sp;
		cout << setw(10) << sa2 << sp;
		cout << setw(10) << vol1 << sp;
		cout << setw(10) << vol2 << '\n';
	}
	return 0;
}
