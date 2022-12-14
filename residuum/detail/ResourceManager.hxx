#pragma once
#include <unordered_map>
#include <mutex>
#include <memory>
#include "Id.hxx"
#include "Key.hxx"

namespace res {

	template<typename ResT>
	concept resource_type = std::same_as<decltype(ResT::id), res::Id<ResT>>;
	
	// Central interface for accessing shared and preloaded Resources
	template<resource_type ResourceType>
	// Internal Storage for ResourceManager
	class Storage {
		// Only Resources are storable 
	public:

		// Checks if resource exists
		static bool contains(const res::Key<ResourceType> & key) {
			const std::scoped_lock<std::mutex> lock(mutex);
			return look_up_table.contains(key);
		}

		// Returns Resourec reference 
		// or throws if the Resouce does not exists in this Storage unit
		static const ResourceType & get(const res::Key<ResourceType> & key) {
			if(auto obj = find(key)) {
				return *obj;
			}
			throw std::runtime_error("Cannot find object: \"" + std::string(*key) + "\"");
		}

		// Returns pointer to resource or nullptr if not found
		static const ResourceType * find(const res::Key<ResourceType> & key) {
			const std::scoped_lock<std::mutex> lock(mutex);
			if(look_up_table.contains(key.ptr())) {
				return look_up_table.at(key.ptr()).get();
			}
			else return nullptr;
		}

		// Inserts new Resource
		static void insert(const ResourceType & resource) {
			const std::scoped_lock<std::mutex> lock(mutex);
			look_up_table.insert({resource.id.ptr(), std::make_unique<ResourceType>(resource)});
		}



		// Inserts new Resource
		static void insert(ResourceType && resource) {
			const std::scoped_lock<std::mutex> lock(mutex);
			look_up_table.insert({resource.id.ptr(), std::make_unique<ResourceType>(std::move(resource))});
		}

	private:
		Storage() = delete;
		Storage(const Storage &) = delete;
		Storage & operator =(const Storage &) = delete;
		Storage(Storage &&) = delete;
		Storage & operator =(Storage &&) = delete;


		using Table = std::unordered_map<const char *, std::unique_ptr<ResourceType>>;
		inline static Table look_up_table;
		inline static std::mutex mutex;
	};

	// Insert new Resource of specified Type into corresponding Storage<...> 
	template<class ResourceType>
	void insert(const ResourceType & resource) {
		Storage<ResourceType>::insert(resource);
	}



	// Insert new Resource of specified Type into corresponding Storage<...> 
	template<class ResourceType>
	void insert(ResourceType && resource) {
		Storage<ResourceType>::insert(std::move(resource));
	}



	// Returns true if a Resource of given Type and Id is stored
	template<class ResourceType>
	bool contains(const res::Key<ResourceType> & resourceId) {
		return Storage<ResourceType>::contains(resourceId);
	}

	// Returns const pointer to Resource of given Type
	// Returns nullptr if it does not exists   
	template<class ResourceType>
	const ResourceType * find(const res::Key<ResourceType> & resourceId) {
		return Storage<ResourceType>::find(resourceId);
	}

	// Returns const pointer to Resource of given Type
	// Throws std::runtime_error if it does not exists   
	template<class ResourceType>
	const ResourceType & get(const res::Key<ResourceType> & resourceId) {
		return Storage<ResourceType>::get(resourceId);
	}

}
