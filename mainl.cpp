#include"Header.h"
#include"Delaunay.h"
#include"Vec2.h"
#include<iostream>
#include<fstream>
#include<random>

using namespace std;

double RR(double R){
	return R * rand() / double(RAND_MAX + 1.0f);
}

void Init(vector<PTUtility::Vec2>& ref){
	const int SS = 1250;
	srand(1999);

	for (int i = 0; i < SS; i++){
		PTUtility::Vec2 RP(5.0 - RR(10.0), 5.0 - RR(10.0));
		
		bool Add = true;
		for (int j = 0; j < ref.size(); j++){
			if ((RP - ref[j]).norm2() < 0.05){
				Add = false;
				break;
			}
		}
		if (Add){
			ref.push_back(RP);
		}
	}

}

int main(){

	mDy::Delaunay2D mm;
	

	std::vector<PTUtility::Vec2> dd;
	Init(dd);

	mm.Create(dd);
	mm.Write("result.obj");




	return 0;
}