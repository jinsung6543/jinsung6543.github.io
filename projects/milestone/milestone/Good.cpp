// --------------------------------------------------------------
// Name: Jin Sung Kim  
// SN: 153494182
// Date: 2019/08/04  
// Email: jskim29@myseneca.ca
/////////////////////////////////////////////////////////////////

#include <fstream>
#include <iomanip>
#include <cstring>
#include "Good.h"

using namespace std;

namespace aid {
	// PUBLIC:
	Good::Good(char type) {
		m_type = type;
		m_SKU[0] = '\0';
		m_desc[0] = '\0';
		m_name = nullptr;
		name("");
		m_onHand = 0;
		m_quantityNeeded = 0;
		m_taxable = true;
		m_price = 0.0;
		m_error = Error();
	}

	Good::Good(const char* SKU, const char* gName, const char* unit, int onHand, bool taxable, double price, int quantityNeeded) {
		if (SKU != nullptr && gName != nullptr && unit != nullptr) {
			m_type = 'N';
			strncpy(m_SKU, SKU, max_sku_length);
			m_SKU[max_sku_length] = '\0';
			m_name = nullptr;
			name(gName);
			strncpy(m_desc, unit, max_unit_length);
			m_desc[max_unit_length] = '\0';
			m_onHand = onHand;
			m_taxable = taxable;
			m_price = price;
			m_quantityNeeded = quantityNeeded;
			m_error = Error();
		} else {
			*this = Good();
		}
	}

	void Good::init(const Good& src) {
		m_type = src.m_type;
		strcpy(m_SKU, src.m_SKU);
		m_name = nullptr;
		name(src.m_name);
		strcpy(m_desc, src.m_desc);
		m_onHand = src.m_onHand;
		m_taxable = src.m_taxable;
		m_price = src.m_price;
		m_quantityNeeded = src.m_quantityNeeded;
		message(src.m_error.message());
	}

	Good::Good(const Good& src) {
		init(src);
	}

	Good& Good::operator=(const Good& src) {
		if (this != &src) {
			init(src);
		}
		return *this;
	}

	Good::~Good() {
		delete[] m_name;
	}

	fstream& Good::store(fstream& file, bool newLine) const {
		if (file.is_open()) {
			file << m_type << "," << sku() << "," << name() << "," << unit() << "," << m_taxable << "," << itemPrice() << "," << quantity() << "," << m_quantityNeeded;
			if (newLine) {
				file << endl;
			}
		}
		return file;
	}

	fstream& Good::load(fstream& file) {
		char type = this->m_type;;
		char SKU[max_sku_length + 1];
		char desc[max_unit_length + 1];
		char name[max_name_length + 1];
		int onHand;
		int quantityNeeded;
		double price;
		bool taxable;

		if (file.is_open()) {
			file.seekg(0, ios::beg);
			file.get(type);
			file.ignore();
			file.get(SKU, max_sku_length, ',');
			file.ignore();
			file.get(name, max_name_length, ',');
			file.ignore();
			file.get(desc, max_unit_length, ',');
			file.ignore();
			file >> taxable;
			file.ignore();
			file >> price;
			file.ignore();
			file >> onHand;
			file.ignore();
			file >> quantityNeeded;
			file.ignore();

			Good tmp = Good(SKU, name, desc, onHand, taxable, price, quantityNeeded);
			*this = Good(tmp);
			this->m_type = type;
		}

		return file;
	}

	ostream& Good::write(ostream& os, bool linear) const {
		if (m_error.isClear() && !isEmpty()) {
			if (linear) {
				os.fill(' ');
				os << setw(max_sku_length) << left << sku() << '|'
					<< setw(20) << left << name() << '|'
					<< setw(7) << right << fixed << setprecision(2) << itemCost() << '|'
					<< setw(4) << right << quantity() << '|'
					<< setw(10) << left << unit() << '|'
					<< setw(4) << right << qtyNeeded() << '|';
			} else {
				os << " Sku: " << sku() << endl << " Name (no spaces): " << name() << endl << " Price: " << itemPrice() << endl;
				os << " Price after tax: ";
				if (taxed()) {
					 os << itemCost() << endl;
				} else {
					os << " N/A" << endl;
				}
				os << " Quantity on Hand: " << quantity() << " " << unit() << endl << " Quantity needed: " << qtyNeeded();
			}
		} else {
			os << m_error;
		}

		return os;
	}

	istream& Good::read(istream& is) {
		char type = this->m_type;
		char SKU[max_sku_length + 1];
		char desc[max_unit_length + 1];
		char name[max_name_length + 1];
		int onHand;
		int quantityNeeded;
		double price;
		char taxInput;
		bool taxable;

		cout << " Sku: ";
		is >> SKU;
		cout << " Name (no spaces): ";
		is >> name;
		cout << " Unit: ";
		is >> desc;
		cout << " Taxed? (y/n): ";
		is >> taxInput;
		if (taxInput == 'Y' || taxInput == 'y') {
			taxable = true;
		} else if (taxInput == 'N' || taxInput == 'n') {
			taxable = false;
		} else {
			is.setstate(ios::failbit);
			m_error.message("Only (Y)es or (N)o are acceptable");
		}

		if (!is.fail()) {
			cout << " Price: ";
			is >> price;
			if (is.fail()) {
				m_error.message("Invalid Price Entry");
			}
		}

		if (!is.fail()) {
			cout << " Quantity on hand: ";
			is >> onHand;
			if (is.fail()) {
				m_error.message("Invalid Quantity Entry");
			}
		}

		if (!is.fail()) {
			cout << " Quantity needed: ";
			is >> quantityNeeded;
			if (is.fail()) {
				m_error.message("Invalid Quantity Needed Entry");
			}
		}

		if (!is.fail()) {
			*this = Good(SKU, name, desc, onHand, taxable, price, quantityNeeded);
			this->m_type = type;
		}
		return is;
	}

	bool Good::operator==(const char* SKU) const {
		return strcmp(m_SKU, SKU) == 0;
	}

	double Good::total_cost() const {
		return m_onHand * itemCost();
	}

	void Good::quantity(int units) {
		if (units > 0) {
			m_onHand = units;
		}
	}

	bool Good::isEmpty() const {
		return m_SKU[0] == '\0';
	}

	int Good::qtyNeeded() const {
		return m_quantityNeeded;
	}

	int Good::quantity() const {
		return m_onHand;
	}

	bool Good::operator>(const char* SKU) const {
		return strcmp(m_SKU, SKU) > 0;
	}

	bool Good::operator>(const Good& src) const {
		return strcmp(m_name, src.m_name) > 0;
	}

	int Good::operator+=(int units) {
		if (units > 0) {
			m_onHand += units;
		}
		return m_onHand;
	}

	bool Good::operator>(const iGood& src) const {
		return total_cost() > src.total_cost();
	}

	// PROTECTED:
	void Good::name(const char* name) {
		delete[] m_name;
		m_name = nullptr;
		if (name != nullptr) {
			m_name = new char[max_name_length + 1];
			strncpy(m_name, name, max_name_length);
			m_name[max_name_length] = '\0';
		}
	}

	const char* Good::name() const {
		return m_name;
	}

	const char* Good::sku() const {
		return m_SKU;
	}

	const char* Good::unit() const {
		return m_desc;
	}

	bool Good::taxed() const {
		return m_taxable;
	}

	double Good::itemPrice() const {
		return m_price;
	}

	double Good::itemCost() const {
		if (taxed()) {
			return itemPrice() * (1 + tax_rate);
		}
		return itemPrice();
	}

	void Good::message(const char* errMessage) {
		m_error.message(errMessage);
	}

	bool Good::isClear() const {
		return m_error.isClear();
	}

	// HELPER
	ostream& operator<<(ostream& os, const Good& src) {
		src.write(os, true);
		return os;
	}

	istream& operator>>(istream& is, Good& src) {
		src.read(is);
		return is;
	}

	double operator+=(double& cost, const Good& src) {
		return src.total_cost() + cost;
	}

	double operator+=(double& cost, const iGood& src) {
		return src.total_cost() + cost;
	}

	ostream& operator<<(ostream& os, const iGood& src) {
		src.write(os, true);
		return os;
	}

	istream& operator>>(istream& is, iGood& src) {
		src.read(is);
		return is;
	}
}