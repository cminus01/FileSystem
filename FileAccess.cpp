#include "FileAccess.hpp"

int FileAccess::Apply(int size) {
	auto it = remaining_space.begin();
	while (it != remaining_space.end()) {
		int x = it->first;
		int y = it->second;
		if (y - x + 1 < size) {
			++it;
			continue;
		}
		else {
			it = remaining_space.erase(it);
			index.emplace_back(0, x, size);
			if (x + size <= y) {
				remaining_space.emplace(x, s + size);
			}
			return x;
		}
	}
	return -1;
}