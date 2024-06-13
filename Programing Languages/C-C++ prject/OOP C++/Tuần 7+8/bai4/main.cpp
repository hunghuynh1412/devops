#include"HinhHocPhang.h"

int main() {
	QuanLyHinhHocPhang ql;
	ql.AddHinh(new HinhChuNhat(5.6, 2.3));
	ql.AddHinh(new HinhTamGiac(-1.5, 6.7, 5.9));
	ql.AddHinh(new HinhTron(12.7));
	ql.AddHinh(new HinhThangVuong(10.1, 8.6, 3.5));
	cout << "Tong Dien tich: " << ql.TongDienTich() << endl;
	cout << "Tong Chu vi: " << ql.TongChuVi() << endl;
	cout << endl << endl;
}
