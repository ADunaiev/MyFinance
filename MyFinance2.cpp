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
	Date(const Date& dateP);
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
Date::Date(const Date& dateP)
{
	day = dateP.day;
	month = dateP.month;
	year = dateP.year;
}
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


class Payment_type
{
protected:
	string name;
	double balance;
	double min_balance;
public:
	Payment_type(string nameP, double balanceP, double min_balanceP);
	Payment_type();
	string get_name() const;
	double get_balance() const;
	double get_min_balance() const;
	void set_name(string nameP);
	void top_up(double top_upP);
	void write_off(double write_offP);
	void show() const;
};
Payment_type::Payment_type(string nameP, double balanceP, double min_balanceP) :
	name{ nameP }, balance{ balanceP }, min_balance{ min_balanceP } {}
Payment_type::Payment_type():Payment_type("", 0, 0){}
string Payment_type::get_name() const
{
	return name;
}
double Payment_type::get_balance() const
{
	return balance;
}
double Payment_type::get_min_balance() const
{
	return min_balance;
}
void Payment_type::set_name(string nameP)
{
	name = nameP;
}
void Payment_type::top_up(double top_upP)
{
	if (top_upP > 0)
		balance += top_upP;
	else
		throw (char*)"Error! Negative top up!";
}
void Payment_type::write_off(double write_offP)
{
	if (balance - write_offP < min_balance)
		throw (char*)"Unsufficient balance to perfom operation!";

	balance -= write_offP;
}
void Payment_type::show() const
{
	cout << "This is payment type: " << name << endl;
	cout << "Available balance is: " << balance << endl;
	cout << endl;
}

class Wallet : public Payment_type
{
public:
	Wallet(double balanceP):Payment_type("Wallet", balanceP,0){}
	void show()
	{
		cout << "This is payment type: " << name << endl;
		cout << "Available balance is: " << balance << endl;
		cout << "Minimum balance is: " << min_balance << endl;
		cout << endl;
	}
};
class Debet_Card : public Payment_type
{
	Date valid_till;
public:
	Debet_Card(double balanceP, Date valid_dateP) :
		Payment_type("Debet_Card", balanceP, 0), valid_till{valid_dateP}{}
	void show()
	{
		cout << "This is payment type: " << name << endl;
		cout << "Available balance is: " << balance << endl;
		cout << "Minimum balance is: " << min_balance << endl;
		cout << "Valid till: " << valid_till << endl;
		cout << endl;
	}
};
class Credit_Card : public Payment_type
{
	Date valid_till;
public:
	Credit_Card(double balanceP, Date valid_tillP) :
		Payment_type("Credit_Card", balanceP, -1000), valid_till{valid_tillP} {}
	void show()
	{
		cout << "This is payment type: " << name << endl;
		cout << "Available balance is: " << balance << endl;
		cout << "Minimum balance is: " << min_balance << endl;
		cout << "Valid till: " << valid_till << endl;
		cout << endl;
	}
};

vector<string> Exp_Groups{ "Sport", "Health", "Food", "Wear", "Transport",
						"Entertainment", "Education" };

class Exp_Counter
{
	int count;
public:
	Exp_Counter(int countP);
	Exp_Counter();
	int get_count();
	void operator()();
};
Exp_Counter::Exp_Counter(int countP):count{countP}{}
Exp_Counter::Exp_Counter() : Exp_Counter(0){}
int Exp_Counter::get_count()
{
	return count;
}
void Exp_Counter::operator()()
{
	count++;
}
Exp_Counter exp_count;

class Expense
{
	int exp_number;
	string exp_group;
	double amount;
	Date date;
	vector<Payment_type>::iterator paym_type;
public:
	Expense(string exp_groupP, 
		double amountP, Date dateP, vector<Payment_type>::iterator paym_typeP);
	Expense();
	void show();
	int get_exp_number();
	string get_exp_group();
	double get_amount();
	Date get_date();
	vector<Payment_type>::iterator get_paym_type();
};
Expense::Expense(string exp_groupP, 
	double amountP, Date dateP, vector<Payment_type>::iterator paym_typeP) :
	exp_group {exp_groupP}, amount{ amountP },
	date{ dateP }, paym_type{ paym_typeP }
{	
	exp_count();
	exp_number = exp_count.get_count(); 
	paym_type->write_off(amount);
}
Expense::Expense() : 
	Expense("", 0, {1,1,1990}, vector<Payment_type>::iterator()) {}
void Expense::show()
{
	cout << exp_number << "\t" << date << "\t" << exp_group << "\t" 
		<< amount << "\t" << paym_type->get_name() << endl;
}
int Expense::get_exp_number()
{
	return exp_number;
}
string Expense::get_exp_group()
{
	return exp_group;
}
double Expense::get_amount()
{
	return amount;
}
Date Expense::get_date()
{
	return date;
}
vector<Payment_type>::iterator Expense::get_paym_type()
{
	return paym_type;
}


int main()
{
	try {

		Wallet my_wallet(100);
		my_wallet.top_up(150);
		Debet_Card my_dc(1000, { 31,10,2027 });	
		Credit_Card my_cc(1500, {30, 9, 2025});

		vector<Payment_type> MyPaymTypes;
		MyPaymTypes.push_back(my_wallet);
		MyPaymTypes.push_back(my_cc);
		MyPaymTypes.push_back(my_dc);

		for (auto var : MyPaymTypes)
			var.show();

		auto it1 = MyPaymTypes.begin();
		Expense e1{Exp_Groups[0], 130, {1,1,2022}, it1};
		e1.show();

		Expense e2{ Exp_Groups[1], 105, {10,1,2022}, it1+1 };
		e2.show();

		Expense e3{ Exp_Groups[2], 300, {20,4,2022}, it1+2 };
		e3.show();
		cout << endl;

		for (auto var : MyPaymTypes)
			var.show();
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