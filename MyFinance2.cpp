#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

//Создайте систему управления персональными финансами.
//Система должна иметь следующие возможности :
//■ Наличие разных кошельков и карт(дебетовых / кредитных);
//■ Пополнение кошельков и карт;
//■ Внесение затрат.Каждая затрата относится к определенной категории;
//■ Формирование отчетов по затратам и категориям :
//• день;
//• неделя;
//• месяц.
//■ Формирование рейтингов по максимальным суммам :
//• ТОП - 3 затрат :
//	ӽ неделя;
//ӽ месяц.
//• ТОП - 3 категорий:
//ӽ неделя;
//ӽ месяц.
//■ Сохранение отчетов и рейтингов в файл.

const vector<int> month_days{ 31,28,31,30,31,30,31,31,30,31,30,31 };
const vector<string> months{ "January", "February", "March", "April",
					"May", "June", "July", "August", "September",
					"October", "November", "December" };
class Date
{
	int day;
	int month;
	int year;

public:
	Date(int dayP, int monthP, int yearP);
	Date();
	int get_day();
	int get_month();
	int get_year();
	friend ostream& operator<<(ostream& out, const Date& object);
	void set_day(int dayP);
	void set_month(int monthP);
	void set_year(int yearP);
	int week_num(const Date& object);
	bool IsLeapYear();
	bool IsCorrect();
};
Date::Date(int dayP, int monthP, int yearP) :
	day{ dayP }, month{ monthP }, year{ yearP }{}
Date::Date() : Date(1, 1, 1900) {}
int Date::get_day() { return day; }
int Date::get_month() { return month; }
int Date::get_year() { return year; }
ostream& operator<<(ostream& out, const Date& obj)
{
	out << obj.day << "." << obj.month << "." << obj.year;

	return out;
}
void Date::set_day(int dayP) {
	day = dayP;
}
void Date::set_month(int monthP) { month = monthP; }
void Date::set_year(int yearP) { year = yearP; }
bool Date::IsCorrect()
{
	bool temp = 1;

	if (year > 2022)
		temp = 0;
	else if (month < 1 || month > 12)
		temp = 0;
	else
	{
		if (month == 2 && this->IsLeapYear())
		{
			if (day > 29)
				temp = 0;
		}
		else
		{
			if (day > month_days[month - 1])
				temp = 0;
		}

	}

	return temp;
}

int Date::week_num(const Date& object)
{
	return 0;
}
bool Date::IsLeapYear()
{
	return year % 400 == 0 || (year % 100 != 0) && (year % 4 == 0);
}

//class Payment
//{
//	double balance;
//	double min_balance;
//	string name;
//};

int main()
{
	Date d{ 29,2, 1700};

	cout << d << " Is correct? Answer is: " << d.IsCorrect() << endl;

	return 0;
}