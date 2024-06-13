#include<iostream>
#include<math.h>
#include<string>
#include<vector>
using namespace std;
#define CoBan 1230000;
class NhanVien {
private:
	string ms;
	string hoten;
protected:
	int type;
public:
	NhanVien(string hoten, string ms) {
		this->ms = ms;
		this->hoten = hoten;
	}
	int gettype() { return type; }
	virtual double luong() = 0;
	friend ostream& operator<<(ostream &os, NhanVien &orther) {
		os << "ho va ten: " << orther.hoten << endl;
		os << "ma so: " << orther.ms << endl;
		return os;
	}

};
class NhanVienSX :public NhanVien {
private:
	int sanPham;
public:
	NhanVienSX(string hoten, string ms, int sanPham) :NhanVien(hoten, ms) {
		this->type = 1;
		this->sanPham = sanPham;
	}
	double luong() {
		return sanPham * 20000;
	}
	friend ostream& operator<<(ostream &os, NhanVienSX &orther)
	{
		os << (NhanVien&)orther;
		os << "so luong san pham: " << orther.sanPham << endl;
		return os;
	}
};
class NhanVienCN :public NhanVien {
private:
	int soNgay;
public:
	NhanVienCN(string hoten, string ms, int soNgay) :NhanVien(hoten, ms) {
		this->type = 2;
		this->soNgay = soNgay;
	}
	double luong() {
		return soNgay * 50000;
	}
	friend ostream& operator<<(ostream &os, NhanVienCN &orther)
	{
		os << (NhanVien&)orther;
		os << "so ngay lam viec: " << orther.soNgay << endl;
		return os;
	}
};
class NhanVienQL :public NhanVien {
private:
	float chiSo;
public:
	NhanVienQL(string hoten, string ms,float ChiSo) :NhanVien(hoten, ms) {
		this->type = 3;
		chiSo = abs(ChiSo);
	}
	double luong() {
		return chiSo * CoBan;
	}
	friend ostream& operator<<(ostream &os, NhanVienQL &orther)
	{
		os << (NhanVien&)orther;
		os << "he so duong: " << orther.chiSo << endl;
		return os;
	}
};

//=============Cong Ty ABC==================
class CongTy {
private:
	vector<NhanVien*> vNhanVien;
public:
	void ThemNhanVien(NhanVienSX *nvsx) {
		NhanVienSX *nvmoi = new NhanVienSX(*nvsx);
		vNhanVien.push_back(nvmoi);
	}
	void ThemNhanVien(NhanVienCN *nvcn) {
		NhanVienCN *nvmoi = new NhanVienCN(*nvcn);
		vNhanVien.push_back(nvmoi);
	}
	void ThemNhanVien(NhanVienQL *nvql) {
		NhanVienQL *nvmoi = new NhanVienQL(*nvql);
		vNhanVien.push_back(nvmoi);
	}
	void DanhSachNV(ostream& os) {
		for (int i = 0; i < vNhanVien.size(); i++) {
			if(vNhanVien[i]->gettype() == 1)
			cout<<*vNhanVien[i];
		}
		for (int i = 0; i < vNhanVien.size(); i++) {
			if (vNhanVien[i]->gettype() == 2)
				cout << *vNhanVien[i];
		}
		for (int i = 0; i < vNhanVien.size(); i++) {
			if (vNhanVien[i]->gettype() == 3)
				cout << *vNhanVien[i];
		}
	}
	int SoLuongNhanVien() {
		return vNhanVien.size();
	}
	int SoLuongNhanVienQL() {
		int dem = 0;
		for (int i = 0; i < vNhanVien.size(); i++) {
			if (vNhanVien[i]->gettype() == 3)
				dem++;
		}
		return dem;
	}
	void nhapDS();
};
