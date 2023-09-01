#include<iostream>

void Elevator(int floor);
int Factorial(int n);
double Power(double a, int n);
double Fibonacci(int n);

//#define ELEVATOR
//#define FACTORIAL
//#define POWER
#define FIBONACCI

void main()
{
	setlocale(LC_ALL, "");
	int n, a;

#ifdef ELEVATOR
	std::cout << "������� ����� �����: "; std::cin >> n;
	elevator(n);
#endif 

#ifdef FACTORIAL
	std::cout << "������� �����: "; std::cin >> n;
	std::cout << n << "! = " << Factorial(n);
#endif 

#ifdef  POWER
	std::cout << "������� ����� � �������: "; std::cin >> a >> n;
	std::cout << "����� " << a << " � ������� " << n << " = " << Power(a, n);
#endif

#ifdef FIBONACCI
	std::cout << "������� ������� ����� ���� ��������� ����� �������: "; std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cout << Fibonacci(i) << "\t";

	std::cout << std::endl;

	std::cout << "������� ������ ���� ���������: "; std::cin >> n;
	for (int i = 1; n >= Fibonacci(i); i++)
		std::cout << Fibonacci(i) << "\t";
#endif 

}

void Elevator(int floor)
{
	if (floor == 0)
	{
		std::cout << "�� � �������" << std::endl;
		return;
	}
	std::cout << "�� �� " << floor << " �����\n";
	Elevator(floor - 1);
	std::cout << "�� �� " << floor << " �����\n";	
}
int Factorial(int n) 
{
	if (n == 0) return 1;
	else return n * Factorial(n - 1);
}

double Power(double a, int n)
{
	if (a == 1 || a == 0) return a;
	if (n > 1) return a * Power(a, n - 1);
	if (n < 1) return 1 / a * Power(a, n + 1);
	return a;
}

double Fibonacci(int n)
{
	if (n == 1 || n == 2) return (n - 1);
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}