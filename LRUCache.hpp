#include <list>
#include <map>
#include <string>

class LRUCache {
  public:
	LRUCache() {
		maxsize = 2;
	}
	
	int getsize() {
		return lru_manager.size();
	}

	bool put(std::string key, std::string value);
	std::string get(std::string key);

	void change_maxsize(int new_max_size);


// key , value , num

// key 
// key - value

  private:
	int maxsize;	
	std::list<std::string> lru_manager;
	std::map<std::string, std::string> data;
	bool exists(std::string key);
};
