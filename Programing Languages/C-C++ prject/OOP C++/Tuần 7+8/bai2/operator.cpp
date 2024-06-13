#include"SoPhuc.h"



SP1::SP1()
{
	a = 0;
	b = 0;
}

SP1::SP1(float a, float b) {
	this->a = a;
	this->b = b;
}


ostream& operator<<(ostream &os, const SP2 &sp2) {
	if (sp2.a != 0)
		os << sp2.a;
	if (sp2.b != 0) {
		if (sp2.b > 0 && sp2.a != 0)
			os << " + " << sp2.b << "i";
		else {
			os << sp2.b << "i";
		}
	}
	if (sp2.a == 0 && sp2.b == 0)
		os << 0;
	return os;
}

istream& operator >> (istream &is, SP2 &sp2)
{
	cout << "Nhap vao phan thuc: ";
	is >> sp2.a;
	cout << "Nhap vao phan ao: ";
	is >> sp2.b;
	return is;
}

SP2::SP2(float a, float b) : SP1(a, b)
{
}
SP2::SP2() : SP1()
{
}
SP2 SP2::operator+(const SP2& sP2) {
	SP2 temp(this->a + sP2.a, this->b + sP2.b);
	return temp;
}
SP2 SP2::operator-(const SP2& sP2) {
	SP2 temp(this->a - sP2.a, this->b - sP2.b);
	return temp;
}
SP2 SP2::operator*(const SP2& sP2) {
	SP2 temp(this->a*sP2.a - this->b*sP2.b, this->a*sP2.b + this->b*sP2.a);
	return temp;
}
SP2 SP2::operator/(const SP2& sP2) {
	float thuc = (this->a*sP2.a + this->b*sP2.b) / (sP2.a*sP2.a + sP2.b*sP2.b);
	float ao = (this->b*sP2.a - this->a*sP2.b) / (sP2.a*sP2.a + sP2.b*sP2.b);
	SP2 temp(thuc, ao);
	return temp;
}

bool SP2::operator==(const SP2 & sP2)
{
	if (this->a == sP2.a && this->b == sP2.b)
		return true;
	return false;
}

bool SP2::operator!=(const SP2 & sP2)
{
	return !(*this == sP2);
}

bool SP2::operator>(const SP2 &sP2)
{
	float a = this->a*this->a + this->b*this->b;
	float b = sP2.a*sP2.a + sP2.b*sP2.b;
	if (a > b)
		return true;
	return false;
}

bool SP2::operator<(const SP2 & sP2)
{
	if ((*this > sP2) == false && (*this == sP2) == false)
		return true;
	return false;
}

bool SP2::operator<=(const SP2 &sP2)
{
	return !(*this>sP2);
}

bool SP2::operator>=(const SP2 & sP2)
{
	return !(*this<sP2);
}

SP2 SP2::operator++()
{
	this->a++;
	return *this;
}

SP2 SP2::operator++(int)
{
	SP2 temp(this->a, this->b);
	this->a++;
	return temp;
}

SP2 SP2::operator--()
{
	this->a--;
	return *this;
}

SP2 SP2::operator--(int)
{
	SP2 temp(this->a, this->b);
	this->a--;
	return temp;;
}
ostream& operator<< (ostream& os, const SP1 &orther)
{
	os << orther.a <<" + " <<orther.b << "i" << endl;
	return os;
}
istream& operator >> (istream& is, SP1 &orther)
{
	cout << "Nhap phan thuc: ";
	is >> orther.a;
	cout << "nhap ao: ";
	is >> orther.b;
	return is;
}