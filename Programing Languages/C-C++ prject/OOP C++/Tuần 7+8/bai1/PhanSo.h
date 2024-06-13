
#include<iostream>
#include<math.h>

using namespace std;

class PS1 {
protected:
	int	tu, mau;
public:
	virtual void nhap();
	PS1();
	void refresh(PS1 &a);
	PS1(int tu, int mau);
	//các phép tính toán
	PS1 operator+(const PS1 &orther);
	PS1 operator-(const PS1 &orther);
	PS1 operator*(const PS1 &orther);
	PS1 operator/(const PS1 &orther);
	void operator++();
	void operator--();
	//việc nhập và xuất
	friend ostream &operator<<(ostream &os, const PS1 &orther);
	friend istream &operator >> (istream &is, PS1 &orther);
	//các phép so sánh
	bool operator>(const PS1 &orther);
	bool operator>=(const PS1 &orther);
	bool operator==(const PS1 &orther);
	bool operator!=(const PS1 &orther);
	bool operator<(const PS1 &orther);
	bool operator<=(const PS1 &orther);
};
class PS2 :public PS1 {
	char dau;
public:
	PS2(int tu, int mau, char dau) :PS1(tu, mau)
	{
		if (dau == '-' || dau == '+')
			this->dau = dau;
		else
			this->dau = '+';
	}
	PS2() :PS1()
	{
		dau = '+';
	}
	friend istream& operator >> (istream& is, PS2 &ps2)
	{
		is >> ps2.dau;
		is >> ps2.tu;
		is >> ps2.mau;
		return is;
	}
	friend ostream& operator<<(ostream& os, PS2 &ps2)
	{
		os << ps2.dau;
		os << (PS1)ps2;
		return os;
	}

};
