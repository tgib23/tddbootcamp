#include "LRUCache.hpp"
#include <string>
#include <list>


void LRUCache::change_maxsize(int new_max_size) {
  if (new_max_size < maxsize ) {
    
    for (int i = 0 ; i < maxsize - new_max_size ; ++i ) {
      std::string rm_key;
      rm_key = lru_manager.front();
      lru_manager.pop_front();
      data.erase(rm_key);
    }
    maxsize = new_max_size;
  }
}
bool LRUCache::

exists(std::string key) {
  std::list<std::string>::iterator it = lru_manager.begin();
  while( it != lru_manager.end() )  // listの末尾まで
  {
    if (key == *it)
      return true;
  }
  return false;
}

bool LRUCache::
put(std::string key, std::string value) {
  if (!exists(key)) {
    if (lru_manager.size() < maxsize) {
      lru_manager.push_back(key);
      data[key] = value;
    } else {
      const std::string erase_key = lru_manager.front();
      lru_manager.pop_front();
      data.erase(erase_key);
      
      lru_manager.push_back(key);
      data[key] = value;
    }
  }
    
}

std::string LRUCache::
get(std::string key) {
  if (exists(key)) {
    lru_manager.remove(key);
    lru_manager.push_back(key);
    return data[key];
  } else {
    return "";
  }
}
