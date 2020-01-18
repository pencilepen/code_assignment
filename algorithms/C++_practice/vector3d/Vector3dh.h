
#pragma once
	class Vector3d
	{
	private:
		double x;
		double y;
		double z;
	public:
		double getX();
		double getY();
		double getZ();
		void setX(double);
		void setY(double);
		void setZ(double);
		void input();
		void output();
		Vector3d();
		Vector3d(double, double, double);
		//double norm(Vector3d);
		~Vector3d();
	};

	Vector3d operator+ (Vector3d a, Vector3d b);
	Vector3d operator- (Vector3d a, Vector3d b);

	/*template <class T>
	T Sum(T a, T b)
	{
		return a + b;
	}*/


