#include<iostream>
#include<math.h>
#include<vector>
#include <iomanip>

using namespace std;
#define pi 3.141592653
class Hinh {
public:

	virtual void print(ostream &os) {
		os << "khong tim thay loai hinh";
	}

	friend ostream& operator<<(ostream &os, Hinh &orther) {
		orther.print(os);
		return os;
	}
};

class HinhHocPhang :public Hinh {
public:
	virtual double P() = 0;
	virtual double S() = 0;
};
class HinhTron : public HinhHocPhang {
private:
	double R;
public:
	HinhTron(double bk) {
		R = bk;
	}
	double P() {
		return 2 * R * pi;
	}
	double S() {
		return R * R * pi;
	}

	void print(ostream& os)
	{
		os << "HinhTron[P=" << P() << ", S=" << S() << "]" << endl;
	}
};

class HinhVuong : public HinhHocPhang {
private:
	double canh;
public:
	HinhVuong(double c) {
		canh = c;
	}
	double P() {
		return 4 * canh;
	}

	double S() {
		return canh * canh;
	}

	void print(ostream &os) {
		os << "HinhVuong[P=" << P() << ", S=" << S() << "]" << endl;
	}
};

class HinhChuNhat : public HinhHocPhang {
private:
	double D, R;
public:
	HinhChuNhat(double cd, double cr) {
		D = cd;
		R = cr;
	}
	double P() {
		return 2 * (D + R);
	}

	double S() {
		return D * R;
	}

	void print(ostream &os)
	{
		os << "HinhChuNhat[P=" << P() << ", S=" << S() << "]" << endl;
	}
};
class HinhTamGiacDeu :public HinhHocPhang {
private:
	double Canh;
public:
	HinhTamGiacDeu(double C) {
		Canh = C;
	}
	double P() {
		return 3 * Canh;
	}

	double S() {
		return Canh*Canh*sqrt(3) / 2;
	}
	void print(ostream &os) {
		os << "HinhTamGiacDeu[P=" << P() << ", S=" << S() << "]" << endl;
	}
};


//=======================Hinh 3D=====================================
class Hinh3D :public Hinh {
public:
	virtual double Sxq() = 0;
	virtual double V() = 0;
};
class HinhCau : public Hinh3D {
private:
	double R;
public:

	HinhCau(double bk) {
		R = bk;
	}
	double Sxq() {
		return 4 * R * R * pi;
	}
	double V() {
		return 4 / 3.0 * R * pi;
	}
	void print(ostream& os) {
		os << "Hinh Cau " << " [Sxq = " << Sxq() << ", V = " << V() << "]";
	}
};
class HinhHop :public Hinh3D {
private:
	double D, R, _h;
public:
	HinhHop(double d, double r, double h) {
		D = d;
		R = r;
		_h = h;
	}
	double Sxq() {
		return 2 * _h*(D + R);
	}
	double V() {
		return R*D*_h;
	}
	void print(ostream& os) {
		os << "Hinh Hop " << " [Sxq = " << Sxq() << ", V = " << V() << "]";
	}
};
class HinhLapPhuong :public Hinh3D {
private:
	double C;
public:
	HinhLapPhuong(double Canh) {
		C = Canh;
	}

	double Sxq() {
		return 4 * C*C;
	}
	double V()
	{
		return C*C*C;
	}
	void print(ostream& os) {
		os << "Hinh Lap Phuong " << " [Sxq = " << Sxq() << ", V = " << V() << "]";
	}
};
class HinhTru :public Hinh3D {
private:
	double R, _h;
public:
	HinhTru(double bkday, double cao) {
		R = bkday;
		_h = cao;
	}

	double Sxq() {
		return 2 * pi*R*_h;
	}
	double V()
	{
		return pi*R*R*_h;
	}
	void print(ostream& os) {
		os << "Hinh Tru " << " [Sxq = " << Sxq() << ", V = " << V() << "]";
	}
};
class HinhNon :public Hinh3D {
private:
	double R, _h;
public:
	HinhNon(double bkday, double cao) {
		R = bkday;
		_h = cao;
	}
	double Sxq() {
		return  pi*R*sqrt(R*R + _h*_h);
	}
	double V()
	{
		return (1 / 3.0)*pi*R*R*_h;
	}
	void print(ostream& os) {
		os << "Hinh Non " << " [Sxq = " << Sxq() << ", V = " << V() << "]";
	}
};
