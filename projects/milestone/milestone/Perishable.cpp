// --------------------------------------------------------------
// Name: Jin Sung Kim  
// SN: 153494182
// Date: 2019/08/04  
// Email: jskim29@myseneca.ca
/////////////////////////////////////////////////////////////////

#include "Perishable.h"

using namespace std;

namespace aid {
	// PUBLIC:
	Perishable::Perishable() : Good('P') {
		m_expiry = Date();
	}

	fstream& Perishable::store(fstream& file, bool newLine) const {
		Good::store(file, false);
		if (file.is_open()) {
			file << "," << m_expiry;
			if (newLine) {
				file << endl;
			}
		}
		return file;
	}
	fstream& Perishable::load(fstream& file) {
		Good::load(file);
		if (file.is_open()) {
			file >> m_expiry;
		}
		return file;
	}
	ostream& Perishable::write(ostream& os, bool linear) const {
		Good::write(os, linear);
		if (!m_expiry.isEmpty()) {
			if (linear) {
				os << left << expiry();
			} else {
				os << endl << " Expiry date: " << expiry();
			}
		}

		return os;
	}

	istream& Perishable::read(istream& is) {
		Good::read(is);
		if (!is.fail()) {
			Date tmpDate = Date();
			cout << " Expiry date (YYYY/MM/DD): ";
			is >> tmpDate;
			if (tmpDate.bad()) {
				is.setstate(ios::failbit);
				switch (tmpDate.errCode())
				{
					case 1:
						message("Invalid Date Entry");
						break;
					case 2:
						message("Invalid Day in Date Entry");
						break;
					case 3:
						message("Invalid Month in Date Entry");
						break;
					case 4:
						message("Invalid Year in Date Entry");
						break;
					case 5:
						message("Invalid Expiry in Date Entry");
				}
				
			} else {
				m_expiry = tmpDate;
			}
		}

		return is;
	}

	const Date& Perishable::expiry() const {
		return m_expiry;
	}

	// HELPER:
	iGood* CreateProduct(char tag) {
		iGood* tmp = nullptr;
		if (tag == 'N' || tag == 'n') {
			tmp = new Good();
		}
		
		if (tag == 'P' || tag == 'p') {
			tmp = new Perishable();
		}

		return tmp;
	}
}