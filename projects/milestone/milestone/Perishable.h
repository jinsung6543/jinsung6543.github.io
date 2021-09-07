// --------------------------------------------------------------
// Name: Jin Sung Kim  
// SN: 153494182
// Date: 2019/08/04  
// Email: jskim29@myseneca.ca
/////////////////////////////////////////////////////////////////

#ifndef AID_PERISHABLE_H
#define AID_PERISHABLE_H

#include "Good.h"
#include "Date.h"

namespace aid {

	class Perishable : public Good {
		Date m_expiry;

	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};

	iGood* CreateProduct(char tag);
}

#endif