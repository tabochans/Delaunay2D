#pragma once
#include<cmath>


namespace PTUtility{

	//åpè≥Ç∑ÇÈÇ»ÇÊÅAê‚ëŒÇæÇºÅHÅI
	class Vec2{

	private:

		double a[2];

	public:

		static Vec2 Ones(){
			return Vec2(1, 1);
		}
		static Vec2 Zero(){
			return Vec2(0, 0);
		}

		static Vec2 MultVec(const Vec2& left, const Vec2& right){
			return Vec2(left.x() * right.x(), left.y() * right.y());
		}
		static Vec2 DivVec(const Vec2& left, const Vec2& right){
			return Vec2(left.x() / right.x(), left.y() / right.y());
		}

		double dot(const Vec2& ref)const{
			return a[0] * ref.x() + a[1] * ref.y();
		}

		double norm()const{
			return sqrt(a[0] * a[0] + a[1] * a[1]);
		}
		double norm2()const{
			return a[0] * a[0] + a[1] * a[1];
		}

		void normalize(){
			double d = norm();
			a[0] /= d;
			a[1] /= d;
		}
		Vec2 normalized()const{
			double d = norm();
			return Vec2(a[0] / d, a[1] / d);
		}

		inline const Vec2 operator+(const Vec2& ref)const{
			return Vec2(a[0] + ref.x(), a[1] + ref.y());
		}
		inline const Vec2 operator-(const Vec2& ref)const{
			return Vec2(a[0] - ref.x(), a[1] - ref.y());
		}
		inline const Vec2 operator-()const{
			return Vec2(-a[0], -a[1]);
		}
		inline const Vec2 operator+()const{
			return *this;
		}



		inline double x()const{
			return a[0];
		}
		inline double y()const{
			return a[1];
		}
		inline double& x(){
			return a[0];
		}
		inline double& y(){
			return a[1];
		}

		inline double operator[](size_t id)const{
			return a[id];
		}
		inline double& operator[](size_t id){
			return a[id];
		}

		inline double operator()(size_t id)const{
			return a[id];
		}
		inline double& operator()(size_t id){
			return a[id];
		}


		Vec2(const Vec2& ref){
			a[0] = ref.x();
			a[1] = ref.y();
		}
		Vec2& operator=(const Vec2& ref){
			a[0] = ref.x();
			a[1] = ref.y();
			return *this;
		}

		Vec2(){
			a[0] = a[1] = 0.0f;
		}
		Vec2(double x, double y){
			a[0] = x;
			a[1] = y;
		}


		inline Vec2& operator+=(const Vec2& ref){
			a[0] += ref.x();
			a[1] += ref.y();
			return *this;
		}
		inline Vec2& operator-=(const Vec2& ref){
			a[0] -= ref.x();
			a[1] -= ref.y();
			return *this;
		}


		~Vec2(){

		}

	};


	inline const Vec2 operator*(double left, const Vec2& right){
		return Vec2(left*right.x(), left*right.y());
	}
	inline const Vec2 operator*(const Vec2& left, double right){
		return Vec2(right*left.x(), right*left.y());
	}

	inline const Vec2 operator*=(Vec2& left, double right){
		left.x() *= right;
		left.y() *= right;
		return left;
	}
	inline const Vec2 operator/=(Vec2& left, double right){
		left.x() /= right;
		left.y() /= right;
		return left;
	}

	inline const Vec2 operator/(const Vec2& left, double right){
		return Vec2(left.x() / right, left.y() / right);
	}


}