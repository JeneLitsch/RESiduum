#pragma once
#include <string>
#include "ResouceChecker.hxx"
#include "NameMap.hxx"
#include "Key.hxx"

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



		const std::string_view operator*() const {
			return this->str;
		}


		Key<ForResource> key() const {
			return Key<ForResource>{this->str};
		}


	private:
		std::string_view str;
	};
}