#include"PhanSo.h"
int UCLN(int a, int b)
{

	while (a != b)
	{
		if (a > b)
			a -= b;
		if (a < b)
			b -= a;
	}
	return a;
}
void PS1::refresh(PS1 &a)
{
	int UC = UCLN(a.tu, a.mau);
	a.tu /= UC;
	a.mau /= UC;
}
//Phần operator cho việc tính toán 
PS1 PS1::operator+(const PS1 &orther)
{
	PS1 temp = *this;
	temp.tu = this->tu*orther.mau + this->mau*orther.tu;
	temp.mau = this->mau*orther.mau;
	refresh(temp);
	return temp;
}
PS1 PS1::operator-(const PS1 &orther)
{
	PS1 temp = *this;
	temp.tu = this->tu*orther.mau - this->mau*orther.tu;
	temp.mau = this->mau*orther.mau;
	refresh(temp);
	return temp;
}

PS1 PS1::operator*(const PS1 &orther)
{
	PS1 temp = *this;
	temp.tu = this->tu*orther.tu;
	temp.mau = this->mau*orther.mau;
	refresh(temp);
	return temp;
}
PS1 PS1::operator/(const PS1 &orther)
{
	PS1 temp = *this;
	temp.tu = this->tu*orther.mau;
	temp.mau = this->mau*orther.tu;
	refresh(temp);
	return temp;
}
void PS1::operator++()
{
	this->tu += mau;
}
void PS1::operator--()
{
	this->tu -= mau;
}
//kết thúc phần các phép tính toán
void PS1::nhap() {
	cout << "nhap tu so: ";
	cin >> this->tu;
	cout << "nhap mau so: ";
	cin >> this->mau;
	while (this->mau == 0)
	{
		cout << "mau khong hop le xin nhap lai: ";
		cin >> this->mau;
	}
	refresh(*this);
}
PS1::PS1()
{
	this->tu = 0;
	this->mau = 1;
}
//Phần operator cho việc xuất nhập
ostream &operator<<(ostream &os, const PS1 &orther)
{
	os << orther.tu << "/" << orther.mau;
	return os;
}
istream &operator >> (istream &is, PS1 &orther)
{
	is >> orther.tu >> orther.mau;
	return is;
}
//kết thúc phần nhập xuất
//phần so sánh hai phân số
bool PS1::operator>(const PS1 &orther)
{
	if (this->tu*orther.mau - this->mau*orther.tu <= 0)
		return false;
	else
		return true;

}
bool PS1::operator>=(const PS1 &orther)
{
	if (this->tu*orther.mau - this->mau*orther.tu >= 0)
		return true;
	else
		return false;

}
bool PS1::operator<(const PS1 &orther)
{
	if (this->tu*orther.mau - this->mau*orther.tu >= 0)
		return false;
	else
		return true;

}
bool PS1::operator<=(const PS1 &orther)
{
	if (this->tu*orther.mau - this->mau*orther.tu <= 0)
		return true;
	else
		return false;

}
bool PS1::operator==(const PS1 &orther)
{
	if (this->tu*orther.mau - this->mau*orther.tu != 0)
		return false;
	else
		return true;

}
bool PS1::operator!=(const PS1 &orther)
{
	if (this->tu*orther.mau - this->mau*orther.tu == 0)
		return false;
	else
		return true;

}
//kết thúc phần so sánh