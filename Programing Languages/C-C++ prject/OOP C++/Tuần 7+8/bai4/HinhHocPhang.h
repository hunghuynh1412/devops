#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define pi 3.141592653
class HinhHocPhang {
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
};

class HinhThangVuong : public HinhHocPhang {
private:
	double dayLon, dayBe, h;
public:
	HinhThangVuong(double dl, double db, double cao) {
		dayBe = db;
		dayLon = dl;
		h = cao;
	}
	double P() {
		return sqrt(pow((dayLon - dayBe), 2) + (h * h)) + dayLon + dayBe + h;
	}

	double S() {
		return h * ((dayLon + dayBe) / 2);
	}
};

class HinhTamGiac : public HinhHocPhang {
private:
	double c1, c2, c3;
public:
	HinhTamGiac(double c1, double c2, double c3) {
		this->c1 = abs(c1);
		this->c2 = abs(c2);
		this->c3 = abs(c3);
	}
	double P() {
		return c3 + c2 + c1;
	}

	double S() {
		double p = (c1 + c2 + c3) / 2;
		return sqrt(p * ((p - c1) * (p - c2) * (p - c3)));
	}
};
class QuanLyHinhHocPhang {
private:
	vector<HinhHocPhang*> vHhp;
public:
	void AddHinh(HinhHocPhang* hinhmoi) {
		vHhp.push_back(hinhmoi);
	}
	double TongDienTich() {
		double sum = 0.0;
		for (int i = 0; i < vHhp.size(); i++) {
			sum += vHhp[i]->S();
		}
		return sum;
	}

	double TongChuVi() {
		double sum = 0.0;
		for (int i = 0; i < vHhp.size(); i++) {
			sum += vHhp[i]->P();
		}
		return sum;
	}
};