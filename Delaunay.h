#pragma once
#include"Vec2.h"
#include"Vec3.h"
#include<vector>
#include<fstream>
#include<deque>


namespace mDy{


	class Delaunay2D{
	public:

		struct Triangle{

			PTUtility::Vec2 _P[3];
			Triangle(){
			}
			Triangle(
				const PTUtility::Vec2& p1,
				const PTUtility::Vec2& p2,
				const PTUtility::Vec2& p3){
				_P[0] = p1;
				_P[1] = p2;
				_P[2] = p3;
			}
			~Triangle(){

			}
		};


	private:

		double RGe(double r){
			return r * rand() / (double)(RAND_MAX)-r / (double)(RAND_MAX);
		}

		struct LINE{

			bool operator==(const LINE& ref){
				if ((ref._P[0] - _P[0]).norm2() < 0.000000001 && (ref._P[1] - _P[1]).norm2() < 0.000000001){
					return true;
				}
				if ((ref._P[1] - _P[0]).norm2() < 0.000000001 && (ref._P[0] - _P[1]).norm2() < 0.000000001){
					return true;
				}
				return false;
			}
			bool operator==(const LINE& ref)const{

				if ((ref._P[0] - _P[0]).norm2() < 0.000000001 && (ref._P[1] - _P[1]).norm2() < 0.000000001){
					return true;
				}
				if ((ref._P[1] - _P[0]).norm2() < 0.000000001 && (ref._P[0] - _P[1]).norm2() < 0.000000001){
					return true;
				}
				return false;
			}


			PTUtility::Vec2 _P[2];
			int _Axis;

			void Swap(){
				PTUtility::Vec2 tt = _P[0];
				_P[0] = _P[1];
				_P[1] = tt;
			}
			double Length()const{
				return (_P[0] - _P[1]).norm();
			}
			int PSide(const PTUtility::Vec2& p) const{
				if (_Axis < 0){
					double p1x = _P[0].x();
					double p2x = _P[0].x();
					double p1y = _P[0].y();
					double p2y = _P[0].y();

					if (p.y() >(p1y - p2y)*p.x() / (p1x - p2x) + (p1x*p2y - p1y*p2x) / (p1x - p2x)){
						return 1;
					}
					else{
						return -1;
					}

				}
				else if (_Axis == 0){
					return (p.y() > 0) * 2 - 1;
				}
				else{
					return (p.x() > 0) * 2 - 1;
				}
			}
			LINE(){
				_P[0] = PTUtility::Vec2(-1, -1);
				_P[1] = PTUtility::Vec2(1, 1);
				_Axis = -1;
			}
			LINE(const PTUtility::Vec2& P1, const PTUtility::Vec2& P2) : _Axis(-1){
				_P[0] = P1;
				_P[1] = P2;
				if (abs((_P[0] - _P[1]).x()) < 0.00000001){
					//y軸平行
					_Axis = 1;
				}
				if (abs((_P[0] - _P[1]).y()) < 0.00000001){
					//x軸平行
					_Axis = 0;
				}
			}
			~LINE(){

			}

		};

		struct TRIANGLE{

			bool IfIncludeLine(const LINE& LL){
				for (int i = 0; i < 3; i++){
					if (L(i) == LL){
						return true;
					}
				}
				return false;
			}

			bool IfShareLine(const TRIANGLE& ref, LINE& SLine)const{
				
				for (int i = 0; i < 3; i++){
					for (int j = 0; j < 3; j++){
						if (ref.L(j) == L(i)){
							SLine = L(i);
							return true;
						}
					}
				}
				return false;
			}

			bool operator==(const TRIANGLE& ref){
				int rr = 0;
				for (int i = 0; i < 3; i++){
					for (int j = 0; j < 3; j++){
						if ((ref.P(i) - P(j)).norm2() < 0.000000001){
							rr++;
							break;
						}
					}
				}
				if (rr == 3){
					return true;
				}
				return false;

			}
			bool operator==(const TRIANGLE& ref)const{
				int rr = 0;
				for (int i = 0; i < 3; i++){
					for (int j = 0; j < 3; j++){
						if ((ref.P(i) - P(j)).norm2() < 0.000000001){
							rr++;
							break;
						}
					}
				}
				if (rr == 3){
					return true;
				}
				return false;
			}

			LINE _Line[3];

			TRIANGLE(){
				_Line[0] = LINE(PTUtility::Vec2(-1.0, 0.0), PTUtility::Vec2(1.0, 0.1));
				_Line[1] = LINE(PTUtility::Vec2(1.0, 0.1), PTUtility::Vec2(0.0, 1.0));
				_Line[2] = LINE(PTUtility::Vec2(0.0, 1.0), PTUtility::Vec2(-1.0, 0.0));
			}
			TRIANGLE(const PTUtility::Vec2& p1, const PTUtility::Vec2& p2, const PTUtility::Vec2& p3){



				if (PTUtility::Vec3((p2 - p1).x(), (p2 - p1).y(), 0.0).cross(PTUtility::Vec3((p3 - p2).x(), (p3 - p2).y(), 0.0)).z() < 0){
					_Line[0] = LINE(p1, p3);
					_Line[1] = LINE(p3, p2);
					_Line[2] = LINE(p2, p1);
				}
				else{
					_Line[0] = LINE(p1, p2);
					_Line[1] = LINE(p2, p3);
					_Line[2] = LINE(p3, p1);
				}


			}
			~TRIANGLE(){

			}

			//内部なら1　外部なら-1を返す
			int IfInTriangle(const PTUtility::Vec2& p)const{
				
				char rr = 0;
				for (int i = 0; i < 3; i++){

					PTUtility::Vec3 vv(_Line[i]._P[1].x() - _Line[i]._P[0].x(), _Line[i]._P[1].y() - _Line[i]._P[0].y(), 0.0f);
					rr += 2 * (vv.cross(PTUtility::Vec3(p.x() - _Line[i]._P[0].x(), p.y() - _Line[i]._P[0].y(), 0.0f)).z() > 0) - 1;

				}
				if (abs(rr) == 3){
					return 1;
				}
				else{
					return -1;
				}

			}

			PTUtility::Vec2 P(int i)const{
				if (i == 0){
					return _Line[0]._P[0];
				}
				else if (i == 1){
					return _Line[0]._P[1];
				}
				else if (i == 2){
					return _Line[1]._P[1];
				}
				else{
					throw;
				}

			}

			LINE L(int i)const{
				return _Line[i];
			}

		};

		void Flip(TRIANGLE& A, TRIANGLE& B);
		std::vector<TRIANGLE> m_TriA;
		bool IfValidTriangle(const TRIANGLE& T1, const TRIANGLE& T2);
		int RandArray(std::vector<PTUtility::Vec2>& Data);
		int P_Create(const std::vector<PTUtility::Vec2>& Data, int depth);
		void WriteTriangle(std::ofstream& of);
		int DivideTriangle(const TRIANGLE& T, const PTUtility::Vec2& P, std::vector<TRIANGLE>& result);
		
		int FindTriFromLine(const LINE& ref, int& ID1, int& ID2);
		int FindTri(const PTUtility::Vec2& P);
		int FlipStack(const std::deque<LINE> Init);


	protected:


	public:

		std::vector<Triangle> GetTriangles(){
			std::vector<Triangle> res(m_TriA.size());
			for (int i = 0; i < m_TriA.size(); i++){
				res[i]._P[0] = m_TriA[i].P(0);
				res[i]._P[1] = m_TriA[i].P(1);
				res[i]._P[2] = m_TriA[i].P(2);
			}
			return res;
		}

		bool Create(const std::vector<PTUtility::Vec2>& Data);
		void Write(const char* FileName);

		Delaunay2D();
		virtual ~Delaunay2D();

	};




}