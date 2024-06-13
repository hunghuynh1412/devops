#include"Cty.h"

int main() {
	CongTy cty;
	cty.ThemNhanVien(new NhanVienThuKy("Nguyen Thi A", "Tp Ho Chi Minh", "Toefl iBT 100", 15));
	cty.ThemNhanVien(new NhanVienKyThuat("Tran Van B", "Tp Ho Chi Minh", "CNTT", 8));
	cty.ThemNhanVien(new NhanVienThuKy("Le Nguyen Z", "Tp Ha Noi", "TOEIC 700", 10));
	cty.ThemNhanVien(new NhanVienKyThuat("Do Lan T", "Binh Duong", "Hoa thuc pham", 4));
	cty.ThemNhanVien(new NhanVienKyThuat("Hoang Van D", "Khanh Hoa", "Dien tu", 10));
	cty.ThemNhanVien(new NhanVienThuKy("Ngo E", "Tp Ha Noi", "IELTS 7.0", 12));
	cout << "DS Nhan vien trong cong ty:" << endl;
	cty.DanhSachNV(cout);
	cout << endl << "DS Nhan vien xuat sac:" << endl;
	cty.DanhSachNVXuatSac(cout);
	cout << endl << endl;
	system("pause");
	return 0;
}
