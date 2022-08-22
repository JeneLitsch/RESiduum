#pragma once
#include <string>
#include "ResouceChecker.hxx"

namespace res {
	template<typename ForResource>
	class Key {
	public:
		Key(const std::string & str) : str{str} {
			ResourceChecker::use(str);
		}
		operator const std::string &() const {
			return this->str;
		}
	private:
		std::string str;
	};
}