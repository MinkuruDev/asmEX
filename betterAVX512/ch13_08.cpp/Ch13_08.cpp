#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include "Ch13_08.h"
#include "../AlignedMem.h"
#include "../Benchmark.h"

using namespace std;
bool VecCompare(const Vec4x1_F32* v1, const Vec4x1_F32* v2)
{
	static const float eps = 1.0e-12f;
	bool b0 = (fabs(v1->W - v2->W) <= eps);
	bool b1 = (fabs(v1->X - v2->X) <= eps);
	bool b2 = (fabs(v1->Y - v2->Y) <= eps);
	bool b3 = (fabs(v1->Z - v2->Z) <= eps);
	return b0 && b1 && b2 && b3;
}
void InitVecArray(Vec4x1_F32* va, size_t num_vec)
{
	uniform_int_distribution<> ui_dist{ 1, 500 };
	default_random_engine rng{ 187 };
	for (size_t i = 0; i < num_vec; i++)
	{
		va[i].W = (float)ui_dist(rng);
		va[i].X = (float)ui_dist(rng);
		va[i].Y = (float)ui_dist(rng);
		va[i].Z = (float)ui_dist(rng);
	}
	if (num_vec >= 4)
	{
		// Test values
		va[0].W = 5; va[0].X = 6; va[0].Y = 7; va[0].Z = 8;
		va[1].W = 15; va[1].X = 16; va[1].Y = 17; va[1].Z = 18;
		va[2].W = 25; va[2].X = 26; va[2].Y = 27; va[2].Z = 28;
		va[3].W = 35; va[3].X = 36; va[3].Y = 37; va[3].Z = 38;
	}
}
bool Avx512MatVecMulF32Cpp(Vec4x1_F32* vec_b, float mat[4][4], Vec4x1_F32* vec_a, size_t
	num_vec)
{
	if (num_vec == 0 || num_vec % 4 != 0)
		return false;
	if (!AlignedMem::IsAligned(vec_a, 64) || !AlignedMem::IsAligned(vec_b, 64))
		return false;
	if (!AlignedMem::IsAligned(mat, 64))
		return false;
	for (size_t i = 0; i < num_vec; i++)
	{
		vec_b[i].W = mat[0][0] * vec_a[i].W + mat[0][1] * vec_a[i].X;
		vec_b[i].W += mat[0][2] * vec_a[i].Y + mat[0][3] * vec_a[i].Z;
		vec_b[i].X = mat[1][0] * vec_a[i].W + mat[1][1] * vec_a[i].X;
		vec_b[i].X += mat[1][2] * vec_a[i].Y + mat[1][3] * vec_a[i].Z;
		vec_b[i].Y = mat[2][0] * vec_a[i].W + mat[2][1] * vec_a[i].X;
		vec_b[i].Y += mat[2][2] * vec_a[i].Y + mat[2][3] * vec_a[i].Z;
		vec_b[i].Z = mat[3][0] * vec_a[i].W + mat[3][1] * vec_a[i].X;
		vec_b[i].Z += mat[3][2] * vec_a[i].Y + mat[3][3] * vec_a[i].Z;
	}
	return true;
}
void Avx512MatVecMulF32(void)
{
	const size_t num_vec = 8;
	alignas(64) float mat[4][4]
	{
	10.0, 11.0, 12.0, 13.0,
	20.0, 21.0, 22.0, 23.0,
	30.0, 31.0, 32.0, 33.0,
	40.0, 41.0, 42.0, 43.0
	};
	AlignedArray<Vec4x1_F32> vec_a_aa(num_vec, 64);
	AlignedArray<Vec4x1_F32> vec_b1_aa(num_vec, 64);
	AlignedArray<Vec4x1_F32> vec_b2_aa(num_vec, 64);
	Vec4x1_F32* vec_a = vec_a_aa.Data();
	Vec4x1_F32* vec_b1 = vec_b1_aa.Data();
	Vec4x1_F32* vec_b2 = vec_b2_aa.Data();
	InitVecArray(vec_a, num_vec);
	bool rc1 = Avx512MatVecMulF32Cpp(vec_b1, mat, vec_a, num_vec);
	bool rc2 = Avx512MatVecMulF32_(vec_b2, mat, vec_a, num_vec);
	cout << "Results for Avx512MatVecMulF32\n";
	if (!rc1 || !rc2)
	{
		cout << "Invalid return code\n";
		cout << " rc1 = " << boolalpha << rc1 << '\n';
		cout << " rc2 = " << boolalpha << rc2 << '\n';
		return;
	}
	const unsigned int w = 8;
	cout << fixed << setprecision(1);
	for (size_t i = 0; i < num_vec; i++)
	{
		cout << "Test case #" << i << '\n';
		cout << "vec_b1: ";
		cout << " " << setw(w) << vec_b1[i].W << ' ';
		cout << " " << setw(w) << vec_b1[i].X << ' ';
		cout << " " << setw(w) << vec_b1[i].Y << ' ';
		cout << " " << setw(w) << vec_b1[i].Z << '\n';
		cout << "vec_b2: ";
		cout << " " << setw(w) << vec_b2[i].W << ' ';
		cout << " " << setw(w) << vec_b2[i].X << ' ';
		cout << " " << setw(w) << vec_b2[i].Y << ' ';
		cout << " " << setw(w) << vec_b2[i].Z << '\n';
		if (!VecCompare(&vec_b1[i], &vec_b2[i]))
		{
			cout << "Error - vector compare failed\n";
			return;
		}
	}
}

void Avx512MatVecMulF32_BM() {
	const size_t num_vec = 8;
	alignas(64) float mat[4][4]
	{
	10.0, 11.0, 12.0, 13.0,
	20.0, 21.0, 22.0, 23.0,
	30.0, 31.0, 32.0, 33.0,
	40.0, 41.0, 42.0, 43.0
	};
	AlignedArray<Vec4x1_F32> vec_a_aa(num_vec, 64);
	AlignedArray<Vec4x1_F32> vec_b1_aa(num_vec, 64);
	AlignedArray<Vec4x1_F32> vec_b2_aa(num_vec, 64);
	Vec4x1_F32* vec_a = vec_a_aa.Data();
	Vec4x1_F32* vec_b1 = vec_b1_aa.Data();
	Vec4x1_F32* vec_b2 = vec_b2_aa.Data();
	InitVecArray(vec_a, num_vec);

	using namespace std::chrono;

	time_point<high_resolution_clock> start_point, end_point;
	start_point = high_resolution_clock::now();
	for (int i = 0; i < 5'000'000; i++) {
		Avx512MatVecMulF32Cpp(vec_b1, mat, vec_a, num_vec);
	}
	end_point = high_resolution_clock::now();
	auto start = time_point_cast<microseconds>(start_point).time_since_epoch().count();
	auto end = time_point_cast<microseconds>(end_point).time_since_epoch().count();
	long long cpptime = end - start;

	start_point = high_resolution_clock::now();
	for (int i = 0; i < 5'000'000; i++) {
		Avx512MatVecMulF32_(vec_b2, mat, vec_a, num_vec);
	}
	end_point = high_resolution_clock::now();
	start = time_point_cast<microseconds>(start_point).time_since_epoch().count();
	end = time_point_cast<microseconds>(end_point).time_since_epoch().count();
	long long avxtime = end - start;

	cout << "\nMatrix multiple vector 5 000 000 times: \n";
	cout << "Avx512MatVecMulF32Cpp time: " << cpptime << " microseconds\n";
	cout << "Avx512MatVecMulF32_ time: " << avxtime << " microseconds\n";
}

int main()
{
	Avx512MatVecMulF32();
	Avx512MatVecMulF32_BM();
	return 0;
}