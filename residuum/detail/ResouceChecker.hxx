#pragma once
#include <string>
#include <mutex>
#include <set>
#include <algorithm>

namespace res {
	struct ResourceChecker {
	public:
		static void declare(const std::string_view & name) {
			std::lock_guard lock{mutex};
			if(!active) return;
			declared.insert(name);
		}



		static void use(const std::string_view & name) {
			std::lock_guard lock{mutex};
			if(!active) return;
			used.insert(name);
		}



		static void set_active(bool active) {
			std::lock_guard lock{mutex};
			ResourceChecker::active = active;
		}



		static bool is_active() {
			std::lock_guard lock{mutex};
			return active;
		}



		static std::size_t count_declared() {
			std::lock_guard lock{mutex};
			return declared.size();
		}



		static std::size_t count_used() {
			std::lock_guard lock{mutex};
			return used.size();
		}



		static std::set<std::string_view> get_unused() {
			std::lock_guard lock{mutex};
			std::set<std::string_view> unused;

			std::set_difference(
				std::begin(declared), std::end(declared),
				std::begin(used), std::end(used),
				std::inserter(unused, unused.end())
			);

			return unused;
		}


		static std::set<std::string_view> get_missing() {
			std::lock_guard lock{mutex};
			std::set<std::string_view> missing;

			std::set_difference(
				std::begin(used), std::end(used),
				std::begin(declared), std::end(declared),
				std::inserter(missing, missing.end())
			);

			return missing;
		}
		
	private:
		inline static std::mutex mutex;
		inline static std::set<std::string_view> declared;
		inline static std::set<std::string_view> used;
		inline static bool active = true;
	};
}