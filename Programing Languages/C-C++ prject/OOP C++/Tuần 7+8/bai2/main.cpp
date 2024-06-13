#include"SoPhuc.h"




int main()
{
	//cau a
	SP1 sp1, sp2;
	cout << "Nhap sp1(thuc, ao): \n";
	cin >> sp1;
	cout << "Nhap sp2(thuc, ao): \n";
	cin >> sp2;
	cout << "so phuc thu 1: " << sp1 << endl;
	cout << "so phuc thu 2: " << sp2 << endl;

	//cau b
	SP2 sp3, sp4;
	cout << "Nhap SP3: ";
	cin >> sp3;
	cout << "Nhap SP4: ";
	cin >> sp4;
	cout << sp3 << " CO LON HON " << sp4 << " KO? " << ((sp3 > sp4) ? "True" : "False") << endl;
	cout << sp3 << " CO BE HON " << sp4 << " KO? " << ((sp3 < sp4) ? "True" : "False") << endl;
	cout << sp3 << " CO BANG " << sp4 << " KO? " << ((sp3 == sp4) ? "True" : "False") << endl;
	cout << sp3 << " CO LON HON HOAC BANG " << sp4 << " KO? " << ((sp3 >= sp4) ? "True" : "False") << endl;
	cout << sp3 << " CO BE HON HOAC BANG " << sp4 << " KO? " << ((sp3 <= sp4) ? "True" : "False") << endl;
	system("pause");
	return 0;
}
