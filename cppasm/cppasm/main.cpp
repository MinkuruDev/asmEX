#include <iostream>
#define ll long long

using namespace std;

struct YmmVal {
	union {
		int8_t i8[32];
		int16_t i16[16];
		float f[8];
		double d[4];
	};
};

template <typename T> void printArray(T* arr, int size) {
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

extern "C" ll testFunc();
extern "C" void addPack(float* res, float* a, float* b);
extern "C" void mulInt(int* res, int* a, int* b);

int main() {
	/*float A[] = { 1,2,3,4,5,6,7,8 };
	float B[] = { 4,4,4,4,4,4,4,4 };
	float C[] = { 0,0,0,0,0,0,0,0 };
	float dup = 5.0;
	addPack(C, A, &dup);
	printArray<float>(C, 8);*/

	int a[] = { 1,-2,-3,-4,5,6,7,8 };
	int b = 5;
	int c[] = { 0,0,0,0,0,0,0,0 };
	mulInt(c, a, &b);
	printArray<int>(c, 8);


	return 0;
}
