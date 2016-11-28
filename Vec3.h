#pragma once

#include<cmath>

namespace PTUtility{


	//åpè≥Ç∑ÇÈÇ»ÇÊÅAê‚ëŒÇæÇºÅHÅI
	class Vec3{

	private:

		double a[3];

	public:

		static Vec3 Ones(){
			return Vec3(1, 1, 1);
		}
		static Vec3 Zero(){
			return Vec3(0, 0, 0);
		}

		void Mult(const Vec3& ref){
			x() *= ref.x();
			y() *= ref.y();
			z() *= ref.z();
		}
		void Div(const Vec3& ref){
			x() /= ref.x();
			y() /= ref.y();
			z() /= ref.z();
		}

		static Vec3 MultVec(const Vec3& left, const Vec3& right){
			return Vec3(left.x() * right.x(), left.y() * right.y(), left.z() * right.z());
		}
		static Vec3 DivVec(const Vec3& left, const Vec3& right){
			return Vec3(left.x() / right.x(), left.y() / right.y(), left.z() / right.z());
		}



		double dot(const Vec3& ref)const{
			return a[0] * ref.x() + a[1] * ref.y() + a[2] * ref.z();
		}
		Vec3 cross(const Vec3& ref)const{
			return Vec3(
				a[1] * ref.z() - a[2] * ref.y(),
				a[2] * ref.x() - a[0] * ref.z(),
				a[0] * ref.y() - a[1] * ref.x());
		}


		double norm()const{
			return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
		}
		double norm2()const{
			return a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
		}
	
		void normalize(){
			double d = norm();
			a[0] /= d;
			a[1] /= d;
			a[2] /= d;
		}
		Vec3 normalized()const{
			double d = norm();
			return Vec3(a[0] / d, a[1] / d, a[2] / d);
		}


		inline const Vec3 operator+(const Vec3& ref)const{
			return Vec3(a[0] + ref.x(), a[1] + ref.y(), a[2] + ref.z());
		}
		inline const Vec3 operator-(const Vec3& ref)const{
			return Vec3(a[0] - ref.x(), a[1] - ref.y(), a[2] - ref.z());
		}
		inline const Vec3 operator-()const{
			return Vec3(-a[0], -a[1], -a[2]);
		}
		inline const Vec3 operator+()const{
			return *this;
		}



		inline double x()const{
			return a[0];
		}
		inline double y()const{
			return a[1];
		}
		inline double z()const{
			return a[2];
		}
		inline double& x(){
			return a[0];
		}
		inline double& y(){
			return a[1];
		}
		inline double& z(){
			return a[2];
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

		inline Vec3& operator+=(const Vec3& ref){
			a[0] += ref.x();
			a[1] += ref.y();
			a[2] += ref.z();
			return *this;
		}
		inline Vec3& operator-=(const Vec3& ref){
			a[0] -= ref.x();
			a[1] -= ref.y();
			a[2] -= ref.z();
			return *this;
		}


		Vec3(const Vec3& ref){
			a[0] = ref.x();
			a[1] = ref.y();
			a[2] = ref.z();
		}
		Vec3& operator=(const Vec3& ref){
			a[0] = ref.x();
			a[1] = ref.y();
			a[2] = ref.z();
			return *this;
		}

		Vec3(){
			a[0] = a[1] = a[2] = 0.0f;
		}
		Vec3(double x, double y, double z){
			a[0] = x;
			a[1] = y;
			a[2] = z;
		}


		~Vec3(){

		}

	};


	inline const Vec3 operator*(double left, const Vec3& right){
		return Vec3(left*right.x(), left*right.y(), left*right.z());
	}
	inline const Vec3 operator*(const Vec3& left, double right){
		return Vec3(right*left.x(), right*left.y(), right*left.z());
	}
	inline const Vec3 operator*=(Vec3& left, double right){
		left.x() *= right;
		left.y() *= right;
		left.z() *= right;
		return left;
	}
	inline const Vec3 operator/=(Vec3& left, double right){
		left.x() /= right;
		left.y() /= right;
		left.z() /= right;
		return left;
	}

	inline const Vec3 operator/(const Vec3& left, double right){
		return Vec3(left.x() / right, left.y() / right, left.z() / right);
	}


}