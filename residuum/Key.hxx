#pragma once
#include <string>
#include "ResouceChecker.hxx"
#include "NameMap.hxx"

namespace res {
	template<typename ForResource>
	class Key {
	public:
		Key(const std::string & str) : str{ NameMap::resolve(str) } {
			ResourceChecker::use(this->str);
		}



		Key(const std::string_view & str) : str{ NameMap::resolve(str) } {
			ResourceChecker::use(this->str);
		}



		Key(const char * str) : str{ NameMap::resolve(str) } {
			ResourceChecker::use(this->str);
		}



		const char * ptr() const {
			return this->str.data();
		}



		operator const std::string_view &() const {
			return this->str;
		}



		const std::string_view operator*() const {
			return this->str;
		}

	private:
		std::string_view str;
	};
}