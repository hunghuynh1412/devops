#include <iostream>
#include <vector>
#include <string>
using namespace std;

class NhanVien {
protected:
	string fullName;
	string address;
public:
	virtual void Xuat() = 0;
	virtual bool isBest() = 0;
};
class NhanVienThuKy : public NhanVien {
private:
	string chungChiNgoaiNgu;
public:
	int slBaoCao;
	NhanVienThuKy(string fullName, string address, string chungChi, int slBC);
	NhanVienThuKy(const NhanVienThuKy& nvmoi);
	void Xuat();
	bool isBest();
};
class NhanVienKyThuat : public NhanVien {
private:
	string chungChiNganh;
public:
	int slSangKien;
	NhanVienKyThuat(string fullName, string address, string chungChi, int slSK);
	NhanVienKyThuat(const NhanVienKyThuat& nvmoi);
	void Xuat() {
		cout << fullName << " <" << address << ">" << " [Nganh: " << chungChiNganh << "], sang tao: " << slSangKien << endl;
	}
	bool isBest() {
		if (this->slSangKien < 6) return false;
		return true;
	}
};
class CongTy {
private:
	vector<NhanVien*> vNhanVien;
public:
	void ThemNhanVien(NhanVienThuKy *nvtk) {
		NhanVienThuKy *nvmoi = new NhanVienThuKy(*nvtk);
		vNhanVien.push_back(nvmoi);
	}
	void ThemNhanVien(NhanVienKyThuat *nvkt) {
		NhanVienKyThuat *nvmoi = new NhanVienKyThuat(*nvkt);
		vNhanVien.push_back(nvmoi);
	}
	void DanhSachNV(ostream& os) {
		for (int i = 0; i < vNhanVien.size(); i++) {
			vNhanVien[i]->Xuat();
		}
	}
	void DanhSachNVXuatSac(ostream& os) {
		for (int i = 0; i < vNhanVien.size(); i++) {
			if (vNhanVien[i]->isBest()) {
				vNhanVien[i]->Xuat();
			}
		}
	}
};