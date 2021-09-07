// --------------------------------------------------------------
// Name: Jin Sung Kim  
// SN: 153494182
// Date: 2019/08/04  
// Email: jskim29@myseneca.ca
/////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "Date.h"

using namespace std;
namespace aid {
	void Date::errCode(int errorCode) {
		m_error = errorCode;
	}

	int Date::mdays(int year, int mon) const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	Date::Date() {
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_comp = 0;
		errCode(0);
	}

	Date::Date(int year, int month, int day) {
		if (year < min_year || year > max_year) {
			*this = Date();
			errCode(YEAR_ERROR);
		} else if (month < 1 || month > 12) {
			*this = Date();
			errCode(MON_ERROR);
		} else if (day < 1 || day > mdays(year, month)) {
			*this = Date();
			errCode(DAY_ERROR);
		} else if (year * 372 + month * 31 + day < min_date) {
			*this = Date();
			errCode(PAST_ERROR);
		} else {
			m_year = year;
			m_month = month;
			m_day = day;
			m_comp = m_year * 372 + m_month * 31 + m_day;
			errCode(NO_ERROR);
		}
	}

	bool Date::isEmpty() const {
		return m_year == 0;
	}

	bool Date::operator==(const Date& rhs) const {
		if (!isEmpty() && !(rhs.isEmpty())) {
			return m_comp == rhs.m_comp;
		}
		return false;
 	}

	bool Date::operator!=(const Date& rhs) const {
		if (!isEmpty() && !(rhs.isEmpty())) {
			return m_comp != rhs.m_comp;
		}
		return false;
	}

	bool Date::operator<(const Date& rhs) const {
		if (!isEmpty() && !(rhs.isEmpty())) {
			return m_comp < rhs.m_comp;
		}
		return false;
	}

	bool Date::operator>(const Date& rhs) const {
		if (!isEmpty() && !(rhs.isEmpty())) {
			return m_comp > rhs.m_comp;
		}
		return false;
	}

	bool Date::operator<=(const Date& rhs) const {
		if (!isEmpty() && !(rhs.isEmpty())) {
			return m_comp <= rhs.m_comp;
		}
		return false;
	}

	bool Date::operator>=(const Date& rhs) const {
		if (!isEmpty() && !(rhs.isEmpty())) {
			return m_comp >= rhs.m_comp;
		}
		return false;
	}

	int Date::errCode() const {
		return m_error;
	}

	bool Date::bad() const {
		return m_error != 0;
	}

	istream& Date::read(istream& istr) {

		int year;
		int month;
		int day;

		istr >> year;
		istr.ignore();
		istr >> month;
		istr.ignore();
		istr >> day;

		if (!istr.fail()) {
			*this = Date(year, month, day);
		} else {
			errCode(CIN_FAILED);
		}
		return istr;
	}

	std::ostream& Date::write(std::ostream& ostr) const {
		ostr << m_year << "/";
		ostr.width(2);
		ostr.fill('0'); 
		ostr << m_month;
		ostr << "/";
		ostr.width(2);
		ostr.fill('0');
		ostr << m_day;
		return ostr;
	}

	std::istream& operator>>(std::istream& is, Date& d) {
		d.read(is);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Date& d) {
		d.write(os);
		return os;
	}
}