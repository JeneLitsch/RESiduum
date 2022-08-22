#pragma once
#include <string>
#include "ResouceChecker.hxx"

namespace res {
	template<typename ForResource>
	class Id {
	public:
		
		Id(const std::string & str) : str{str} {
			ResourceChecker::declare(str);
		}	
		


		operator const std::string &() const {
			return this->str;
		}



		const std::string & operator*() const {
			return this->str;
		}

	private:
		std::string str;
	};
}