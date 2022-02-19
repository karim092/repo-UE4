// Lesson 3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#define PI 3.14159265358979323846

float getRadian(float degree)
{
	return PI / 180 * degree;
}

class Figure
{
public:
	virtual float area() = 0;
	virtual ~Figure() { };
};

class Parallelogram : public Figure
{
private:
	float m_side_a;
	float m_side_b;
	float m_height;
protected:
	float getSideA() const
	{
		return m_side_a;
	}

	float getSideB() const
	{
		return m_side_b;
	}
public:
	Parallelogram(float side_a, float height, float side_b = 0.0)
		: m_side_a(side_a), m_side_b(side_b), m_height(height) { }

	float area()
	{
		float area = m_side_a * m_height;

		std::cout << "Площадь параллелограмма равна " << area << std::endl;

		return area;
	}
};

class Circle : public Figure
{
private:
	float m_radius;
public:
	Circle(float radius) : m_radius(radius) { }

	float area()
	{
		float area = PI * pow(m_radius, 2);

		std::cout << "Площадь круга равна " << area << std::endl;

		return area;
	}
};

class Rectangle : public Parallelogram
{
public:
	Rectangle(float side_a, float side_b)
		: Parallelogram(side_a, side_b, side_b) { }

	float area()
	{
		float area = getSideA() * getSideB();

		std::cout << "Площадь прямоугольника равна " << area << std::endl;

		return area;
	}
};

class Square : public Parallelogram
{
public:
	Square(float side_a)
		: Parallelogram(side_a, side_a, side_a) { }

	float area()
	{
		float area = pow(getSideA(), 2);
		std::cout << "Площадь квадрата равна " << area << std::endl;

		return area;
	}
};

class Rhombus : public Parallelogram
{
public:
	Rhombus(float side_a, float side_b)
		: Parallelogram(side_a, side_b, side_b) { }

	float area()
	{
		float area = (getSideA() * getSideB()) / 2; // тут getSideA() и getSideB() это диагонали ромба
		std::cout << "Площадь ромба равна " << area << std::endl;

		return area;
	}
};

// Task 2

class Car
{
private:
	std::string m_company;
	std::string m_model;
protected:
	std::string getCompany() const
	{
		return m_company;
	}

	std::string getModel() const
	{
		return m_model;
	}
public:
	Car(std::string company, std::string model) : m_company(company), m_model(model)
	{
		std::cout << "Транспортное средство компании " + getCompany() + ", модель " + getModel() << std::endl;
	}
};

class PassengerCar : virtual public Car
{
public:
	PassengerCar(std::string company, std::string model) : Car(company, model)
	{
		std::cout << "Легковой автомобиль компании " + getCompany() + ", модель " + getModel() << std::endl;
	}
};

class Bus : virtual public Car
{
public:
	Bus(std::string company, std::string model) : Car(company, model)
	{
		std::cout << "Автобус компании " + getCompany() + ", модель " + getModel() << std::endl;
	}
};

class Minivan : public PassengerCar, public Bus
{
public:
	Minivan(std::string company, std::string model) :
		Car(company, model), PassengerCar(company, model), Bus(company, model)
	{
		std::cout << "Минивэн компании " + getCompany() + ", модель " + getModel() << std::endl;
	}
};

// Task 3

class Fraction
{
private:
	bool is_zero;
	bool is_integer;
	int numerator;
	int denominator;

	int NOD(int n1, int n2)

	{
		int div;
		if (n1 == n2)  return n1;
		int d = n1 - n2;
		if (d < 0)
		{
			d = -d;
			div = NOD(n1, d);
		}
		else
			div = NOD(n2, d);

		return div;
	}

	/*
	 * Поиск наименьшего общего кратного
	 * для знаменателей
	 */
	int NOK(int n1, int n2)
	{
		return n1 * n2 / NOD(n1, n2);
	}

	/*
	 * Функция сокращения дроби
	 */
	void reduceFraction(int& a, int& b)
	{
		int divisor = NOD(abs(a), abs(b));
		a = a / divisor;
		b = b / divisor;
	}
public:
	Fraction() : numerator(0), denominator(0)
	{
		is_zero = true;
		is_integer = true;
	}

	Fraction(int num, int dnum) : numerator(num), denominator(dnum)
	{
		if (numerator == 0 || denominator == 0)
		{
			std::cout << "Числитель или знаменатель не может быть нулевым!\n"
				<< "Число будет инициализировано нулём!" << std::endl;
			numerator = 0;
			denominator = 0;
			is_zero = true;
			is_integer = true;
		}
		else
		{
			is_zero = false;
			is_integer = (abs(numerator) == abs(denominator) || denominator == 1);
		}
	}

	friend std::ostream& operator<<(std::ostream&, const Fraction&);

	Fraction operator+(const Fraction&);
	Fraction operator-(const Fraction&);
	Fraction operator*(const Fraction&);
	Fraction operator/(const Fraction&);

	Fraction operator-() const;

	bool operator==(const Fraction&);
	bool operator!=(const Fraction&);
	bool operator<(const Fraction&);
	bool operator>=(const Fraction&);
	bool operator>(const Fraction&);
	bool operator<=(const Fraction&);
};

std::ostream& operator<<(std::ostream& s, const Fraction& f)
{
	if (f.is_integer)
	{
		if (f.is_zero)
			s << f.numerator;
		else
			s << f.numerator / f.denominator;
	}
	else
		s << f.numerator << '/' << f.denominator;

	return s;
}

Fraction Fraction::operator+(const Fraction& f)
{
	if (f.is_zero)
		return Fraction(numerator, denominator);

	if (is_zero)
		return Fraction(f.numerator, f.denominator);

	int new_denominator = NOK(denominator, f.denominator);
	int new_numerator = numerator * (new_denominator / denominator) + f.numerator * (new_denominator / f.denominator);

	reduceFraction(new_numerator, new_denominator);

	return Fraction(new_numerator, new_denominator);
}

Fraction Fraction::operator-(const Fraction& f)
{
	if (f.is_zero)
		return Fraction(numerator, denominator);

	if (is_zero)
		return Fraction(-f.numerator, f.denominator);

	int new_denominator = NOK(denominator, f.denominator);
	int new_numerator = numerator * (new_denominator / denominator) - f.numerator * (new_denominator / f.denominator);

	if (new_numerator == 0)
		return Fraction();

	reduceFraction(new_numerator, new_denominator);

	return Fraction(new_numerator, new_denominator);
}

Fraction Fraction::operator*(const Fraction& f)
{
	if (is_zero || f.is_zero)
		return Fraction();

	int new_numerator = numerator * f.numerator;
	int new_denominator = denominator * f.denominator;

	reduceFraction(new_numerator, new_denominator);

	return Fraction(new_numerator, new_denominator);
}

Fraction Fraction::operator/(const Fraction& f)
{
	if (f.is_zero)
	{
		std::cout << " [На 0 делить нельзя!] ";
		return Fraction();
	}

	if (is_zero)
		return Fraction();

	return *this * Fraction(f.denominator, f.numerator);
}

Fraction Fraction::operator-() const
{
	return Fraction(-numerator, denominator);
}

bool Fraction::operator==(const Fraction& f)
{
	if (is_zero || f.is_zero)
		return numerator == f.numerator;

	int a_n = numerator;
	int a_d = denominator;

	int b_n = f.numerator;
	int b_d = f.denominator;

	reduceFraction(a_n, a_d);
	reduceFraction(b_n, b_d);

	return a_n == b_n && a_d == b_d;
}

bool Fraction::operator!=(const Fraction& f)
{
	return !(*this == f);
}

bool Fraction::operator<(const Fraction& f)
{
	if (is_zero || f.is_zero)
		return numerator < f.numerator;

	int new_denominator = NOK(denominator, f.denominator);
	int a_n = numerator * (new_denominator / denominator);
	int b_n = f.numerator * (new_denominator / f.denominator);

	return a_n < b_n;
}

bool Fraction::operator>=(const Fraction& f)
{
	return (*this == f || !(*this < f));
}

bool Fraction::operator>(const Fraction& f)
{
	return (*this != f && !(*this < f));
}

bool Fraction::operator<=(const Fraction& f)
{
	return (*this == f || *this < f);
}

using namespace std;

void task_1();
void task_2();
void task_3();

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Задача 1 \n" << endl;
	task_1();
	cout << " \n" << endl;

	cout << "Задача 2 \n" << endl;
	task_2();
	cout << " \n" << endl;

	cout << "Задача 3 \n" << endl;
	task_3();
	cout << " \n" << endl;

	return 0;
}

void task_1()
{
	// Task 1

	Parallelogram Pgrm(15.2, 9.5);
	Circle Crcl(14.5);
	Rectangle Rctgl(14.0, 7.1);
	Square Sqre(23.3);
	Rhombus Rmbs(17.4, 13.2);


	Pgrm.area();
	Crcl.area();
	Rctgl.area();
	Sqre.area();
	Rmbs.area();

}

void task_2()
{
	Minivan m("Макдоналдс", "ABC");
}

void task_3()
{
	Fraction a(3, 9);
	Fraction b(2, 3);
	Fraction c; // 0

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
	cout << "[a + b] " << a << " + " << b << " = " << a + b << endl;
	cout << "[a - b] " << a << " - " << b << " = " << a - b << endl;
	cout << "[a * b] " << a << " * " << b << " = " << a * b << endl;
	cout << "[a / b] " << a << " / " << b << " = " << a / b << endl;
	cout << "[c + b] " << c << " + " << b << " = " << c + b << endl;
	cout << "[b + c] " << b << " + " << c << " = " << b + c << endl;
	cout << "[c - b] " << c << " - " << b << " = " << c - b << endl;
	cout << "[b - c] " << b << " - " << c << " = " << b - c << endl;
	cout << "[c * b] " << c << " * " << b << " = " << c * b << endl;
	cout << "[b * c] " << b << " * " << c << " = " << b * c << endl;
	cout << "[c / b] " << c << " / " << b << " = " << c / b << endl;
	cout << "[b / c] " << b << " / " << c << " = " << b / c << endl;
	cout << "-a = " << -a << endl;
	cout << "[a == b] " << a << " == " << b << " is " << ((a == b) ? "true" : "false") << endl;
	cout << "[a != b] " << a << " != " << b << " is " << ((a != b) ? "true" : "false") << endl;
	cout << "[a < b]  " << a << " < " << b << " is " << ((a < b) ? "true" : "false") << endl;
	cout << "[a <= b] " << a << " <= " << b << " is " << ((a <= b) ? "true" : "false") << endl;
	cout << "[a > b]  " << a << " > " << b << " is " << ((a > b) ? "true" : "false") << endl;
	cout << "[a >= b] " << a << " >= " << b << " is " << ((a >= b) ? "true" : "false") << endl;
	cout << "[c == a] " << c << " == " << a << " is " << ((c == a) ? "true" : "false") << endl;
	cout << "[c != a] " << c << " != " << a << " is " << ((c != a) ? "true" : "false") << endl;
	cout << "[c < a]  " << c << " < " << a << " is " << ((c < a) ? "true" : "false") << endl;
	cout << "[c <= a] " << c << " <= " << a << " is " << ((c <= a) ? "true" : "false") << endl;
	cout << "[c > a]  " << c << " > " << a << " is " << ((c > a) ? "true" : "false") << endl;
	cout << "[c >= a] " << c << " >= " << a << " is " << ((c >= a) ? "true" : "false") << endl;

}

