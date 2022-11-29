#include<iostream>
#include<chrono>
#include <functional>
#include <string>

using namespace std;

namespace bench {

	long long benchmark(function<void(void)> func, string description = "") {

		using namespace std::chrono;

		time_point<high_resolution_clock> start_point, end_point;

		start_point = high_resolution_clock::now();

		func();

		end_point = high_resolution_clock::now(); 

		auto start = time_point_cast<microseconds>(start_point).time_since_epoch().count();

		auto end = time_point_cast<microseconds>(end_point).time_since_epoch().count();

		if(description != "")
			cout << description  << (end - start) << " microseconds" << endl;

		return end - start;
	}

}
