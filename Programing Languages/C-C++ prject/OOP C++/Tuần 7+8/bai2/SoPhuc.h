#include<iostream>
using namespace std;

class SP1
{
protected:
	float a, b;
public:
	SP1();
	SP1(float, float);
	friend ostream& operator<< (ostream& os, const SP1&);
	friend istream& operator >> (istream& is, SP1&);
};
class SP2 : public SP1 {
private:
public:
	SP2(void);
	SP2(float a, float b);
	friend ostream& operator<< (ostream& os, const SP2&);
	friend istream& operator >> (istream& is, SP2&);
	SP2 operator+(const SP2&);
	SP2 operator-(const SP2&);
	SP2 operator*(const SP2&);
	SP2 operator/(const SP2&);
	bool operator==(const SP2&);
	bool operator!=(const SP2&);
	bool operator>(const SP2&);
	bool operator<(const SP2&);
	bool operator<=(const SP2&);
	bool operator>=(const SP2&);
	SP2 operator++();
	SP2 operator++(int);
	SP2 operator--();
	SP2 operator--(int);
};
