#pragma once
#include <string>
#include <functional>
#include "ResouceChecker.hxx"
#include "NameMap.hxx"

namespace res {
	template<typename R>
	class Storage;
	
	template<typename Resource>
	class Key {
	public:
		template<typename R>
		friend class Storage;
		
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
		mutable const Resource * cached = nullptr;
	};



	template<typename Resource>
	auto operator<(const Key<Resource> & l, const Key<Resource> & r) {
		return std::less<const char *>{}(l.ptr(), r.ptr());
	}

	template<typename Resource>
	bool operator==(const Key<Resource> & l, const Key<Resource> & r) {
		return std::equal_to<const char *>{}(l.ptr(), r.ptr());
	}
}