#include "FileAccess.hpp"

int FileAccess::Apply(int size) {
	auto it = remaining_space.begin();

	// 遍历查询是否有足够大小的连续剩余空间
	while (it != remaining_space.end()) {
		int x = it->first;
		int y = it->second;
		if (y - x + 1 < size) {
			// 该连续空间不够大，接着查询下一个连续空间
			++it;
			continue;
		}
		else {
			// 该连续空间足够大
			it = remaining_space.erase(it);
			// 若大小足够的块不会被用完，则保留没用到的部分
			if (x + size <= y) {
				remaining_space.insert(std::make_pair(x, x + size));
			}
			return x;
		}
	}

	return -1;
}

void FileAccess::Del(int pos, int size) {
	// 增加剩余空间
	remaining_space.insert(std::make_pair(pos, pos + size - 1));

	// 特判新增的剩余空间是否和其他剩余空间相连，若相连则将其合并
	auto it = remaining_space.find(std::make_pair(pos, pos + size - 1));
	auto tmp = it;
	if (it != remaining_space.begin()) {
		--tmp;
		if (tmp->second + 1 == it->first) {
			int x = tmp->first;
			int y = it->second;
			remaining_space.erase(tmp);
			remaining_space.erase(it);
			remaining_space.insert(std::make_pair(x, y));
			it = remaining_space.find(std::make_pair(x, y));
		}
		tmp = it;
	}
	++tmp;
	if (tmp != remaining_space.end()) {
		if (it->second + 1 == tmp->first) {
			int x = it->first;
			int y = tmp->second;
			remaining_space.erase(tmp);
			remaining_space.erase(it);
			remaining_space.insert(std::make_pair(x, y));
		}
	}
}

void FileAccess::Read(int begin, int len) {
	// 遍历读入存储信息
	for (int i = begin; i < begin + len; ++i) {
		printf("%c", disk[i]);
	}
	printf("\n");
}

void FileAccess::Write(int begin, int len, std::string s) {
	// 遍历写入存储信息
	for (int i = 0; i < len; ++i) {
		disk[begin + i] = s[i];
	}
}