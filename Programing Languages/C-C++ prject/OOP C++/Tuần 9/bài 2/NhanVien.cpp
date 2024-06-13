#include"NhanVien.h"


void CongTy::nhapDS()
{
	int choose;
	string hoten, ms;
	int n;
	float chiSo;
	while (1) {
		cout << "Loai Nhan Vien(1,2,3): ";
		cin >> choose;
		cout << "ho va ten: ";
		cin.ignore();
		getline(cin, hoten);
		cout << "ma so: ";
		getline(cin, ms);
		switch (choose)
		{
		case 1: {
			cout << "nhap so luong san pham: ";
			cin >> n;
			ThemNhanVien(new NhanVienSX(hoten, ms, n));
			break;
		}
		case 2: {
			cout << "nhap so ngay lam: ";
			cin >> n;
			ThemNhanVien(new NhanVienCN(hoten, ms, n));
			break;
			
		}
		case 3:{
			cout << "he so luong: ";
			cin >> chiSo;
			ThemNhanVien(new NhanVienCN(hoten, ms, chiSo));
			break;
		}
		default:
			break;
		}
		if (choose == 0)
			break;
	}
}
int main()
{
	CongTy cty;
	cty.nhapDS();
	cty.ThemNhanVien(new NhanVienSX("Nguyen Thi A", "17A111", 60));
	cty.ThemNhanVien(new NhanVienCN("Tran Van B", "17B112", 30));
	cty.ThemNhanVien(new NhanVienQL("Le Nguyen Z", "17C113", 2.3));
	cty.ThemNhanVien(new NhanVienSX("Do Lan T", "17A112", 120));
	cty.ThemNhanVien(new NhanVienCN("Hoang Van D", "17B113", 10));
	cty.ThemNhanVien(new NhanVienQL("Ngo E", "17C114", 2.5));
	cout << "Xuat nhan vien theo cap bac: " << endl;
	cty.DanhSachNV(cout);
	cout << "so Luong nhan vien cua cong ty: " << cty.SoLuongNhanVien() << endl;
	cout << "so luong nhan vien quan ly: " << cty.SoLuongNhanVienQL() << endl;
	system("pause");
	return 0;
}