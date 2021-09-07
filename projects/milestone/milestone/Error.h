// --------------------------------------------------------------
// Name: Jin Sung Kim  
// SN: 153494182
// Date: 2019/08/04  
// Email: jskim29@myseneca.ca
/////////////////////////////////////////////////////////////////

#ifndef AID_ERROR_H
#define AID_ERROR_H

#include <iostream>

namespace aid {

	class Error {
		char* m_errMessage;

	public:
		explicit Error(const char* errorMessage = nullptr);
		~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};

	std::ostream& operator<<(std::ostream& os, const Error& e);
}

#endif