#include<iostream>
#include<string>
#include<vector>

using namespace std;

class NGUOI {
protected:
	string hoten;
	string ngaysinh;
	string diachi;
public:
	virtual void nhap();
	virtual void Xuat();
};

class NV : public NGUOI {
private:
	string phongBan;
	float heSoLuong;
	float phuCap;
public:
	void nhap();
	void Xuat();
};

class ArrayNV {
private:
	vector<NGUOI*> vNguoi;
public:
	void nhapDS();
	void XuatDS();
};
