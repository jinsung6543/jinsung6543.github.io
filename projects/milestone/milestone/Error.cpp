// --------------------------------------------------------------
// Name: Jin Sung Kim  
// SN: 153494182
// Date: 2019/08/04  
// Email: jskim29@myseneca.ca
/////////////////////////////////////////////////////////////////

#include <cstring>
#include "Error.h"

using namespace std;
namespace aid {

	Error::Error(const char* errorMessage) {
		m_errMessage = nullptr;
		if (errorMessage != nullptr) {
			message(errorMessage);
		}
	}

	Error::~Error() {
		delete[] m_errMessage;
	}

	void Error::clear() {
		delete[] m_errMessage;
		m_errMessage = nullptr;
	}

	bool Error::isClear() const {
		return m_errMessage == nullptr;
	}

	void Error::message(const char* str) {
		clear();
		if (str != nullptr) {
			int length = strlen(str);
			m_errMessage = new char[length + 1];
			strcpy(m_errMessage, str);
			m_errMessage[length] = '\0';
		}
	}

	const char* Error::message() const {
		if (!isClear()) {
			return m_errMessage;
		}
		return nullptr;
	}

	ostream& operator<<(ostream& os, const Error& e) {
		if (e.message() != nullptr) {
			os << e.message();
		}		
		return os;
	}
}