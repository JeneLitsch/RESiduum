#pragma once
#include <string>
#include <mutex>
#include <set>

namespace res {
	class NameMap {
	public:
		static std::string_view resolve(const std::string & str) {
			std::lock_guard lock{mutex};
			const auto [it, set] = names.insert(str);
			return *it;
		} 



		static std::string_view resolve(const std::string_view & str) {
			return resolve(std::string{str});
		} 



		static std::string_view resolve(const char * str) {
			return resolve(std::string{str});
		} 

	private:
		inline static std::set<std::string> names;
		inline static std::mutex mutex;
	};
}