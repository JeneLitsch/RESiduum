#pragma once
#include <string>
#include <functional>
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



		const std::string_view operator*() const {
			return this->str;
		}

	private:
		std::string_view str;
	};



	template<typename ForResource>
	auto operator<(const Key<ForResource> & l, const Key<ForResource> & r) {
		return std::less<const char *>{}(l.ptr(), r.ptr());
	}

	template<typename ForResource>
	bool operator==(const Key<ForResource> & l, const Key<ForResource> & r) {
		return std::equal_to<const char *>{}(l.ptr(), r.ptr());
	}
}