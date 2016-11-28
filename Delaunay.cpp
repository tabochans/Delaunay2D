#include"Delaunay.h"
using namespace mDy;
using namespace std;
using namespace PTUtility;



int Delaunay2D::FlipStack(const std::deque<LINE> Init){

	std::deque<LINE> stack = Init;

	while (stack.size() > 0){

		LINE L = stack[stack.size() - 1];
		stack.pop_back();


		int ID[2];
		FindTriFromLine(L, ID[0], ID[1]);

		if (ID[0] != -1 && ID[1] != -1){
			if (IfValidTriangle(m_TriA[ID[0]], m_TriA[ID[1]])){
				continue;
			}
			else{
				Flip(m_TriA[ID[0]], m_TriA[ID[1]]);

				LINE sL;
				m_TriA[ID[0]].IfShareLine(m_TriA[ID[1]], sL);

				for (int i = 0; i < 3; i++){
					for (int j = 0; j < 2; j++){
						LINE tL = m_TriA[ID[j]].L(i);
						if (tL == sL){
						}
						else{
							stack.push_back(tL);
						}

					}
				}
			}
		}
	}
}


int  Delaunay2D::P_Create(const std::vector<PTUtility::Vec2>& Data, int depth){

	int Dsize = Data.size();


	while (Dsize > 0){

		PTUtility::Vec2 SelectP = Data[Dsize - 1];
		int TID = FindTri(SelectP);

		if (TID != -1){
			std::vector<TRIANGLE> res;
			TRIANGLE tt = m_TriA[TID];
			DivideTriangle(tt, SelectP, res);
			m_TriA.erase(m_TriA.begin() + TID);

			for (int i = 0; i < 3; i++){
				m_TriA.push_back(res[i]);
			}

			std::deque<LINE> sss;
			sss.push_back(tt.L(0));
			sss.push_back(tt.L(1));
			sss.push_back(tt.L(2));
			FlipStack(sss);

		}


		Dsize--;
	}

	return 0;

}

int Delaunay2D::DivideTriangle(const TRIANGLE& T, const PTUtility::Vec2& P, std::vector<TRIANGLE>& result){

	result.resize(3);

	result[0] = TRIANGLE(P, T.P(0), T.P(1));
	result[1] = TRIANGLE(P, T.P(1), T.P(2));
	result[2] = TRIANGLE(P, T.P(2), T.P(0));

	return 3;
}

bool Delaunay2D::IfValidTriangle(const TRIANGLE& T1, const TRIANGLE& T2){
	
	double A = pow(T1.L(0).Length(),2);
	double B = pow(T1.L(1).Length(),2);
	double C = pow(T1.L(2).Length(),2);

	double a = T1.L(0).Length();
	double b = T1.L(1).Length();
	double c = T1.L(2).Length();
	
	double S = 2.0f *(A*B + B*C + C*A) - (A*A + B*B + C*C);

	//外心位置
	PTUtility::Vec2 Pc =
		T1.P(2) * (A * (B + C - A)) +
		T1.P(0) * (B *(C + A - B)) +
		T1.P(1) * (C * (A + B - C));
	Pc /= (S);

	//半径
	double R = a*b*c / sqrt((a + b + c) * (-a + b + c) * (a - b + c)*(a + b - c));

	int rc = 0;
	for (int i = 0; i < 3; i++){

		//個々のパラメータは調整がむずい
		if ((T2.P(i) - Pc).norm2() > R*R + 0.000001){
			return true;
		}
	}
	return false;

	if (rc == 3){
		return false;
	}
	return true;

}



int Delaunay2D::FindTri(const PTUtility::Vec2& P){

	for (int i = 0; i < m_TriA.size(); i++){
		if (m_TriA[i].IfInTriangle(P) > 0){
			return i;
		}
	}
	return -1;

}


int Delaunay2D::RandArray(std::vector<PTUtility::Vec2>& Data){
	for (int i = 0; i < Data.size(); i++){
		int tt = (Data.size() - 1) * RGe(1);
		swap(Data[tt], Data[i]);
	}
	return 0;
}

int Delaunay2D::FindTriFromLine(const LINE& ref, int& ID1, int& ID2){

	int IDID[2] = { -1, -1 };
	int cid = 0;
	for (int i = 0; i < m_TriA.size(); i++){

		for (int j = 0; j < 3; j++){
			if (m_TriA[i].L(j) == ref){
				IDID[cid] = i;
				cid++;
				if (cid == 2){
					ID1 = IDID[0];
					ID2 = IDID[1];
					return 1;
				}
				break;
			}
		}

	}

	ID1 = IDID[0];
	ID2 = IDID[1];

	return 1;

}



void Delaunay2D::Flip(TRIANGLE& A, TRIANGLE& B){
	LINE LL;
	bool FL = false;
	for (int j = 0; j < 3; j++){
		for (int k = 0;k < 3; k++){
			if (A.L(j) == B.L(k)){
				LL = A.L(j);
				FL = true;
				break;
			}
		}
	}

	if (!FL){
		return;
	}

	PTUtility::Vec2 P1;
	PTUtility::Vec2 P2;

	for (int i = 0; i < 3; i++){
		if ((A.P(i) - LL._P[0]).norm2() > 0.0001 && (A.P(i) - LL._P[1]).norm2() > 0.0000001){
			P1 = A.P(i);
		}
	}
	for (int i = 0; i < 3; i++){
		if ((B.P(i) - LL._P[0]).norm2() > 0.0001 && (B.P(i) - LL._P[1]).norm2() > 0.0000001){
			P2 = B.P(i);
		}
	}

	A = TRIANGLE(P1, P2, LL._P[0]);
	B = TRIANGLE(P1, P2, LL._P[1]);

}

bool Delaunay2D::Create(const std::vector<PTUtility::Vec2>& Data){

	std::vector<Vec2> cc = Data;
	RandArray(cc);

	//支え
	m_TriA.push_back(TRIANGLE(Vec2(-16, -10), Vec2(0, 16), Vec2(16, -10)));
	Vec2 fP[3] = { m_TriA[0].P(0), m_TriA[0].P(1), m_TriA[0].P(2) };

	P_Create(cc, 0);

	for (auto it = m_TriA.begin(); it != m_TriA.end() ; ){

		bool er = false;
		for (int p = 0; p < 3; p++){
			for (int pp = 0; pp < 3; pp++){
				if ((it->P(pp) - fP[p]).norm2() < 0.01){
					it = m_TriA.erase(it);
					er = true;
				}
			}
		}
		if (!er){
			it++;
		}
	}





	ofstream file;
	file.open("PC.obj");
	for (auto v : Data){
		file << "v " << v.x() << " " << v.y() << " " << 0.0 << std::endl;
	}
	file.close();


	return true;
}
void Delaunay2D::Write(const char* FileName){
	
	ofstream file;
	file.open(FileName);
	WriteTriangle(file);
	file.close();

}

void Delaunay2D::WriteTriangle(std::ofstream& of){

	static int PNum = 1;


	for (auto s : m_TriA){

		for (int i = 0; i < 3; i++){
			of << "v " << s.P(i).x() << " " << s.P(i).y() << " " << 0.0 << std::endl;
		}
		of << "f " << PNum << " " << PNum + 1 << " " << PNum + 2 << std::endl;
		PNum += 3;
	}

}


Delaunay2D::Delaunay2D(){

}

Delaunay2D::~Delaunay2D(){

}