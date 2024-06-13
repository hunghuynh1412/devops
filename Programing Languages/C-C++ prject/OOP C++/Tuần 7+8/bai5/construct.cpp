#include"Cty.h"

NhanVienThuKy::NhanVienThuKy(string fullName, string adress, string chungChi, int slBC)
{
		this->chungChiNgoaiNgu = chungChi;
		this->fullName = fullName;
		this->address = address;
		this->slBaoCao = slBC;
}
NhanVienThuKy::NhanVienThuKy(const NhanVienThuKy& nvmoi) {
	this->chungChiNgoaiNgu = nvmoi.chungChiNgoaiNgu;
	this->fullName = nvmoi.fullName;
	this->address = nvmoi.address;
	this->slBaoCao = nvmoi.slBaoCao;
}
void NhanVienThuKy::Xuat() {
	cout << fullName << " <" << address << ">" << " [NN: " << chungChiNgoaiNgu << "], bao cao hoan thanh: " << slBaoCao << endl;
}
bool NhanVienThuKy::isBest() {
	if (this->slBaoCao < 12) return false;
	return true;
}
NhanVienKyThuat::NhanVienKyThuat(string fullName, string address, string chungChi, int slSK) {
	this->chungChiNganh = chungChi;
	this->fullName = fullName;
	this->fullName = address;
	this->slSangKien = slSK;
}
NhanVienKyThuat::NhanVienKyThuat(const NhanVienKyThuat& nvmoi) {
	this->chungChiNganh = nvmoi.chungChiNganh;
	this->fullName = nvmoi.fullName;
	this->address = nvmoi.address;
	this->slSangKien = nvmoi.slSangKien;
}