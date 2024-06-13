#include"PhanSo.h"

int main()
{
	//cau a
	PS1 ps1, ps2;
	cout << "Nhap ps1(tu, mau): \n";
	cin >> ps1;
	cout << "Nhap ps2(tu, mau): \n"; 
	cin >> ps2;
	cout << "phan so thu 1: "<< ps1 << endl;
	cout << "phan so thu 2: "<< ps2 << endl;
	PS1 c = ps1 + ps2;
	cout << "Tong la: "<< c << endl;

	//cau b
	PS2 ps3, ps4;
	cout << "Nhap PS3(dau, tu, mau): ";
	cin >> ps3;
	cout << "Nhap PS4(tu, mau, dau): ";
	cin >> ps4;
	cout << ps3 << " CO LON HON " << ps4 << " KO? " << ((ps3 > ps4) ? "True" : "False") << endl;
	cout << ps3 << " CO BE HON " << ps4 << " KO? " << ((ps3 < ps4) ? "True" : "False") << endl;
	cout << ps3 << " CO BANG " << ps4 << " KO? " << ((ps3 == ps4) ? "True" : "False") << endl;
	cout << ps3 << " CO LON HON HOAC BANG " << ps4 << " KO? " << ((ps3 >= ps4) ? "True" : "False") << endl;
	cout << ps3 << " CO BE HON HOAC BANG " << ps4 << " KO? " << ((ps3 <= ps4) ? "True" : "False") << endl;
	system("pause");
	return 0;
}

