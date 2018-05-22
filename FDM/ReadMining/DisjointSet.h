#pragma once
#include "Util.h"
#include <ctime>

class DisjointSet {
	// �Ż�����array������vector
public:
	int sizeEC;
private:
	vector<int> vec;
public:
	DisjointSet() : sizeEC(0) {}
	void clear() {
		vec.clear();
		sizeEC = 0;
	}
	int* find(int i) {
		// �Ż���ʹ��ָ�뿪vector������ʱ�ͷ�
		// �Ż���ʹ��whileѹ��·��
		// �Ż�����ѹ��·��
		// �Ż����Ƿ񷵻�iterator
		vector<int*> oldElems;

		int* root;
		while (true) {
			root = &(vec[i]);

			// root found directly
			if (*root == i) {
				for (auto p : oldElems) {
					*p = i;
				}
				return root;
			}
			oldElems.push_back(root);
			i = *root;
		}
	}
	void join(int i, int j) {
		int *pRooti = find(i);
		int *pRootj = find(j);

		if (*pRooti != *pRootj) {
			--sizeEC;
			if (*pRooti < *pRootj) {
				*pRootj = *pRooti;
			}
			else {
				*pRooti = *pRootj;
			}
		}
	}
	void append(int val) {
		vec.push_back(val);
	}
	void fromProduct(DisjointSet& ds1, DisjointSet& ds2) {
		clear();
		

		int size = ds1.vec.size();
		int i;
		DisjointSet* shortSet = NULL;
		if (ds1.sizeEC == size || ds2.sizeEC == size) {
			for (i = 0; i < size; ++i) {
				vec.push_back(i);
			}
			sizeEC = size;
			return;
		}

		int root1, root2;
		int partitionCount = 0;
		long long hashValue;
		

		map<long long, int>* proots = new map<long long, int>;
		map<long long, int>::iterator itFind;
		vector<int>::iterator it1, it2;
		for (i = 0, it1 = ds1.vec.begin(), it2 = ds2.vec.begin(); i < size; ++i, ++it1, ++it2) {
			// root1 = ds1.find(i);
			// root2 = ds2.find(i);
			root1 = *it1;
			root2 = *it2;
			hashValue = util::hashRoot(root1, root2);
			itFind = proots->find(hashValue);
			if (itFind == proots->end()) {
				proots->insert(pair<long long, int>(hashValue, partitionCount));
				vec.push_back(partitionCount);
				++partitionCount;
			}
			else {
				vec.push_back(itFind->second);
			}

		}
		sizeEC = partitionCount;

		delete proots;
	}
};