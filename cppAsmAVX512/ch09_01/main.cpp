#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../YmmVal.h"
#include "../Benchmark.h"

using namespace std;
extern "C" void AvxPackedMathF32_(const YmmVal & a, const YmmVal & b, YmmVal c[8]);
extern "C" void AvxPackedMathF64_(const YmmVal & a, const YmmVal & b, YmmVal c[8]);
void AvxPackedMathF32(void)
{
	alignas(32) YmmVal a;
	alignas(32) YmmVal b;
	alignas(32) YmmVal c[8];
	a.m_F32[0] = 36.0f; b.m_F32[0] = -0.1111111f;
	a.m_F32[1] = 0.03125f; b.m_F32[1] = 64.0f;
	a.m_F32[2] = 2.0f; b.m_F32[2] = -0.0625f;
	a.m_F32[3] = 42.0f; b.m_F32[3] = 8.666667f;
	a.m_F32[4] = 7.0f; b.m_F32[4] = -18.125f;
	a.m_F32[5] = 20.5f; b.m_F32[5] = 56.0f;
	a.m_F32[6] = 36.125f; b.m_F32[6] = 24.0f;
	a.m_F32[7] = 0.5f; b.m_F32[7] = -98.6f;
	AvxPackedMathF32_(a, b, c);
	cout << ("\nResults for AvxPackedMathF32\n");
	cout << "a[0]: " << a.ToStringF32(0) << '\n';
	cout << "b[0]: " << b.ToStringF32(0) << '\n';
	cout << "addps[0]: " << c[0].ToStringF32(0) << '\n';
	cout << "subps[0]: " << c[1].ToStringF32(0) << '\n';
	cout << "mulps[0]: " << c[2].ToStringF32(0) << '\n';
	cout << "divps[0]: " << c[3].ToStringF32(0) << '\n';
	cout << "absps b[0]: " << c[4].ToStringF32(0) << '\n';
	cout << "sqrtps a[0]:" << c[5].ToStringF32(0) << '\n';
	cout << "minps[0]: " << c[6].ToStringF32(0) << '\n';
	cout << "maxps[0]: " << c[7].ToStringF32(0) << '\n';
	cout << '\n';
	cout << "a[1]: " << a.ToStringF32(1) << '\n';
	cout << "b[1]: " << b.ToStringF32(1) << '\n';
	cout << "addps[1]: " << c[0].ToStringF32(1) << '\n';
	cout << "subps[1]: " << c[1].ToStringF32(1) << '\n';
	cout << "mulps[1]: " << c[2].ToStringF32(1) << '\n';
	cout << "divps[1]: " << c[3].ToStringF32(1) << '\n';
	cout << "absps b[1]: " << c[4].ToStringF32(1) << '\n';
	cout << "sqrtps a[1]:" << c[5].ToStringF32(1) << '\n';
	cout << "minps[1]: " << c[6].ToStringF32(1) << '\n';
	cout << "maxps[1]: " << c[7].ToStringF32(1) << '\n';
}

void AvxPackedMathF64(void)
{
	alignas(32) YmmVal a;
	alignas(32) YmmVal b;
	alignas(32) YmmVal c[8];
	a.m_F64[0] = 2.0; b.m_F64[0] = M_PI;
	a.m_F64[1] = 4.0; b.m_F64[1] = M_E;
	a.m_F64[2] = 7.5; b.m_F64[2] = -9.125;
	a.m_F64[3] = 3.0; b.m_F64[3] = -M_PI;
	AvxPackedMathF64_(a, b, c);
	cout << ("\nResults for AvxPackedMathF64\n");
	cout << "a[0]: " << a.ToStringF64(0) << '\n';
	cout << "b[0]: " << b.ToStringF64(0) << '\n';
	cout << "addpd[0]: " << c[0].ToStringF64(0) << '\n';
	cout << "subpd[0]: " << c[1].ToStringF64(0) << '\n';
	cout << "mulpd[0]: " << c[2].ToStringF64(0) << '\n';
	cout << "divpd[0]: " << c[3].ToStringF64(0) << '\n';
	cout << "abspd b[0]: " << c[4].ToStringF64(0) << '\n';
	cout << "sqrtpd a[0]:" << c[5].ToStringF64(0) << '\n';
	cout << "minpd[0]: " << c[6].ToStringF64(0) << '\n';
	cout << "maxpd[0]: " << c[7].ToStringF64(0) << '\n';
	cout << '\n';
	cout << "a[1]: " << a.ToStringF64(1) << '\n';
	cout << "b[1]: " << b.ToStringF64(1) << '\n';
	cout << "addpd[1]: " << c[0].ToStringF64(1) << '\n';
	cout << "subpd[1]: " << c[1].ToStringF64(1) << '\n';
	cout << "mulpd[1]: " << c[2].ToStringF64(1) << '\n';
	cout << "divpd[1]: " << c[3].ToStringF64(1) << '\n';
	cout << "abspd b[1]: " << c[4].ToStringF64(1) << '\n';
	cout << "sqrtpd a[1]:" << c[5].ToStringF64(1) << '\n';
	cout << "minpd[1]: " << c[6].ToStringF64(1) << '\n';
	cout << "maxpd[1]: " << c[7].ToStringF64(1) << '\n';
}
int main()
{
	bench::benchmark(AvxPackedMathF32, "AVXPasckedMathF32", 10000);
	bench::benchmark(AvxPackedMathF64, "AVXPasckedMathF64", 10000);
	//AvxPackedMathF32();
	//AvxPackedMathF64();
	return 0;
}
