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
const vector<string> week_days{ "Monday", "Tuesday", "Wednesday",
					"Thirthday", "Friday", "Saturday", "Sunday" };

struct Week_Number
{
	int week;
	int year;
public:
	Week_Number(int weekP, int yearP) : week{weekP}, year {yearP}{}
	Week_Number() : Week_Number(1, 1900){}	
};

ostream& operator<<(ostream& out, const Week_Number& object)
{
	out << "week " << object.week << " year " << object.year;

	return out;
}

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
	Week_Number week_num() const;
	bool IsLeapYear();
	bool IsLeapYear(int yearP) const;
	bool IsCorrect();
	friend bool operator<(const Date& left, const Date& right);
	friend bool operator>(const Date& left, const Date& right);
	int convToInt() const;
	int get_weekday() const;
};
Date::Date(int dayP, int monthP, int yearP) :
	day{ dayP }, month{ monthP }, year{ yearP }
{
	if (!IsCorrect())
		throw (char*)"Wrong date!";
}
Date::Date() : Date(1, 1, 1900) {}
int Date::get_day() { return day; }
int Date::get_month() { return month; }
int Date::get_year() { return year; }
ostream& operator<<(ostream& out, const Date& obj)
{
	out << obj.day << "." << obj.month << "." << obj.year;

	return out;
}
bool operator<(const Date& left, const Date& right)
{
	bool temp;

	if (left.year < right.year)
		temp = 1;
	else if (left.year > right.year)
		temp = 0;
	else
	{
		if (left.month < right.month)
			temp = 1;
		else if (left.month > right.month)
			temp = 0;
		else
		{
			if (left.day < right.day)
				temp = 1;
			else 
				temp = 0;
		}
	}

	return temp;
}
bool operator>(const Date& left, const Date& right)
{
	return right < left;
}
void Date::set_day(int dayP) {
	day = dayP;
}
void Date::set_month(int monthP) { month = monthP; }
void Date::set_year(int yearP) { year = yearP; }
bool Date::IsCorrect()
{
	bool temp = 1;

	if (year > 2100)
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
const Date day_of_1stweek{ 2, 1, 2020 };
bool Date::IsLeapYear()
{
	return year % 400 == 0 || (year % 100 != 0) && (year % 4 == 0);
}
bool Date::IsLeapYear(int yearP) const
{
	return yearP % 400 == 0 || (yearP % 100 != 0) && (yearP % 4 == 0);
}
int Date::convToInt() const
{
	int temp = 0;

	for (int i = 1900; i < year; i++)
	{
		if (IsLeapYear(i))
			temp += 366;
		else
			temp += 365;
	}
	for (int i = 1; i < month; i++)
	{
		temp += month_days[i - 1];
	}
	temp += day;

	return temp;
}
int Date::get_weekday() const
{
	int temp = this->convToInt() + 1;
	int wd;

	wd = (temp + 5) % 7;

	return wd;
}
Week_Number Date::week_num() const
{
	int temp = this->convToInt() + 1;

	Date first_day{ 1, 1, year };
	int temp1 = first_day.convToInt() + 1;
	int week_d = first_day.get_weekday();
	int week_num;
	int week_year;

	if ((temp - temp1) >= (7 - week_d))
	{
		week_num = (temp - temp1 - (7 - week_d));

		week_num /= 7;
		week_num++;
		week_year = year;
	}
	else
	{
		week_year = year - 1;

		Date first_day2{ 1, 1, year - 1 };
		temp1 = first_day2.convToInt() + 1;
		week_d = first_day2.get_weekday();

		week_num = (temp - temp1 - (7 - week_d));
		week_num /= 7;
		week_num++;

	}

	return Week_Number(week_num, week_year);
}

int operator-(const Date& left, const Date& right)
{
	return left.convToInt() - right.convToInt();
}

//class Payment
//{
//	double balance;
//	double min_balance;
//	string name;
//};

int main()
{
	try {
		Date d1{ 3,10, 2022 };
		Date d2{ 2, 10, 2022 };

		cout << d1 << " is " << d1.convToInt() << endl;
		cout << d2 << " is " << d2.convToInt() << endl;

		
		cout << d1 << " is " << week_days[d1.get_weekday()] << endl;
		cout << d2 << " is " << week_days[d2.get_weekday()] << endl;

		cout << d1 << " is " << d1.week_num() << endl;
		cout << d2 << " is " << d2.week_num() << endl;
		
	}
	catch (char* s)
	{
		cout << "\n\n" << s << "\n\n";
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}


	return 0;
}