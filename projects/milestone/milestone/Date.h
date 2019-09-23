// --------------------------------------------------------------
// Name: Jin Sung Kim  
// SN: 153494182
// Date: 2019/08/04  
// Email: jskim29@myseneca.ca
/////////////////////////////////////////////////////////////////

#ifndef AID_DATE_H
#define AID_DATE_H

#define NO_ERROR 0
#define CIN_FAILED 1
#define DAY_ERROR 2
#define MON_ERROR 3
#define YEAR_ERROR 4
#define PAST_ERROR 5

namespace aid {
	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;

	class Date {

		int m_year;
		int m_month;
		int m_day;
		int m_comp;
		int m_error;

		void errCode(int errorCode);
		int mdays(int year, int mon) const;

	public:
		Date();
		Date(int year, int month, int day);
		bool isEmpty() const;
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};

	std::istream& operator>>(std::istream& is, Date& d);
	std::ostream& operator<<(std::ostream& os, const Date& d);
}

#endif