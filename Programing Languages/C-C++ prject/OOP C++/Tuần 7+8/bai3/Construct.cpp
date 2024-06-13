#include"NhanVien.h"

void NGUOI::nhap() {
	cout << "NHAP:" << endl;
	cout << "ho ten: ";
	cin.ignore();
	getline(cin, hoten);
	cout << "ngay sinh: ";
	cin.ignore(0);
	getline(cin, ngaysinh);
	cout << "dia chi: ";
	cin.ignore(0);
	getline(cin, diachi);
}
void NGUOI::Xuat() {
	cout << "\nho ten: ";
	cout << hoten;
	cout << "\nngay sinh: "; 
	cout << ngaysinh;
	cout << "\ndia chi: "; 
	cout << diachi;
}
void NV::nhap() {
	NGUOI::nhap();
	cout << "phong ban: "; cin.ignore(); 
	getline(cin, phongBan);
	cout << "he so luong:  "; 
	cin >> heSoLuong;
	cout << "phu Cap: "; 
	cin >> phuCap;
}
void NV::Xuat() {
	NGUOI::Xuat();
	cout << "\nphong ban: " << phongBan;
	cout << "\nhe so luong:  " << heSoLuong;
	cout << "\nphu Cap: " << phuCap;
}
void ArrayNV::nhapDS() {
	int n = 0;
	cout << "nhap n: ";
	cin >> n;
	NGUOI *p = new NV;
	for (int i = 0; i < n; i++) {
		cout << "NHAP NHAN VIEN THU " << i + 1 << endl;
		p->nhap();
		vNguoi.push_back(p);
	}
}
void ArrayNV::XuatDS() {
	for (int i = 0; i < vNguoi.size(); i++) {
		vNguoi[i]->Xuat(); cout << endl;
	}
}