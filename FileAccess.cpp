#include "FileAccess.hpp"

int FileAccess::Apply(int size) {
	auto it = remaining_space.begin();

	// ������ѯ�Ƿ����㹻��С������ʣ��ռ�
	while (it != remaining_space.end()) {
		int x = it->first;
		int y = it->second;
		if (y - x + 1 < size) {
			// �������ռ䲻���󣬽��Ų�ѯ��һ�������ռ�
			++it;
			continue;
		}
		else {
			// �������ռ��㹻��
			it = remaining_space.erase(it);
			// ����С�㹻�Ŀ鲻�ᱻ���꣬����û�õ��Ĳ���
			if (x + size <= y) {
				remaining_space.insert(std::make_pair(x, x + size));
			}
			return x;
		}
	}

	return -1;
}

void FileAccess::Del(int pos, int size) {
	// ����ʣ��ռ�
	remaining_space.insert(std::make_pair(pos, pos + size - 1));

	// ����������ʣ��ռ��Ƿ������ʣ��ռ�����������������ϲ�
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
	// ��������洢��Ϣ
	for (int i = begin; i < begin + len; ++i) {
		printf("%c", disk[i]);
	}
	printf("\n");
}

void FileAccess::Write(int begin, int len, std::string s) {
	// ����д��洢��Ϣ
	for (int i = 0; i < len; ++i) {
		disk[begin + i] = s[i];
	}
}