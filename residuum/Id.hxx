#pragma once
#include <string>
#include "ResouceChecker.hxx"
#include "NameMap.hxx"

namespace res {
	template<typename ForResource>
	class Id {
	public:
		
		Id(const std::string & str) : str{ NameMap::resolve(str) } {
			ResourceChecker::declare(this->str);
		}



		Id(const char * str) : str{ NameMap::resolve(str) } {
			ResourceChecker::declare(this->str);
		}



		Id(const std::string_view & str) : str{ NameMap::resolve(str) } {
			ResourceChecker::declare(this->str);
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