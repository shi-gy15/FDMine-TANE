#pragma once

// 存放那些凉了的代码

/*

--------------------------------------------class Solver-------------------------------
void loadInitialColumn(Database* vpdb) {
pdb = vpdb;
for (int i = 0; i < col; ++i) {
pds[i].fromTable(*pdb, i);
}
}

bool searchSingle(const AttributeSet& left, const AttributeSet& right, unordered_set<int>& sk) {


for (auto &s : sk) {
if (!((s & left.attribute_set) ^ s) )
return true;
}


if (left.attribute_set == 0)
return false;

vector<int> leftAttrs = left.toVector();
int size = leftAttrs.size();
vector<DisjointSet*> leftds;
int i, j, k;
int rv;

for (i = 0; i < size; ++i) {
if (pds[leftAttrs[i]].sizeEC == 0)
return true;
leftds.push_back(pds + leftAttrs[i]);
}

// if containing col[1]
if (!((2 & left.attribute_set) ^ 2))
sort(leftds);

bool issuper = true;

vector<array<int, collen>::iterator> visit;
for (i = 0; i < size; ++i)
visit.push_back(leftds[i]->parr->begin());


array<int, collen>::iterator rGroup = pds[right.toVector()[0]].parr->begin();

unordered_map<long long, int>::iterator itFind;
long long hashValue;
//array<int, 4> hashArg(initHashArg);

++sc;
long long *pargs = new long long[4]{ 0 };

bool pass;
for (i = 0; i < collen; ++i, ++rGroup) {
pass = false;
for (j = 0; j < size; ++j) {
pass = pass || (*(visit[j]) == -1);
//if (*(visit[j]) == -1)
//	pass = true;
// hashArg[4 - size + j] = *(visit[j]);
pargs[4 - size + j] = *(visit[j]);
++visit[j];
}
if (pass)
continue;
// hashValue = hashn(hashArg);
hashValue = hashn(pargs);
itFind = gmap.find(hashValue);
rv = *rGroup;
if (itFind == gmap.end()) {
//gmap[hashValue] = *rGroup;
gmap.insert(pair<long long, int>(hashValue, rv));
}
else {
issuper = false;
if (rv == -1 || itFind->second != rv) {
gmap.clear();
return false;
}
}
}
gmap.clear();
if (issuper)
sk.insert(left.attribute_set);

return true;
}

void sort(vector<DisjointSet*>& cand) {
DisjointSet* ptemp;
int size = cand.size();

for (int i = 0; i < size; ++i) {
for (int j = i + 1; j < size; ++j) {
if (cand[i]->sizeEC < cand[j]->sizeEC) {
ptemp = cand[i];
cand[i] = cand[j];
cand[j] = ptemp;
}
}
}
}

---------------------------------------------class DisjointSet-----------------------------
class DisjointSet {
public:
int sizeEC;
int sizeNDEC;
array<int, collen>* parr;
public:
DisjointSet() : sizeEC(0), parr(NULL) {}
~DisjointSet() {
if (parr)
delete parr;
}
void clear() {
sizeEC = 0;
}
void fromProduct(DisjointSet& ds1, DisjointSet& ds2) {
int size = collen;

// if super key
if (ds1.sizeEC == size || ds2.sizeEC == size) {
sizeEC = size;
return;
}

parr = new array<int, collen>();
hashRoots.clear();
singleRoots.clear();

int                                         i;
int                                         partitionCount = 0;
long long                                   hashValue;
array<int, collen>::iterator                it1, it2, itAsgn;
unordered_map<long long, int>::iterator     itHFind;

for (i = 0, it1 = ds1.parr->begin(), it2 = ds2.parr->begin(), itAsgn = parr->begin(); i < size; ++i, ++it1, ++it2, ++itAsgn) {
if (*it1 == -1 || *it2 == -1) {
(*itAsgn) = -1;
++partitionCount;
continue;
}
hashValue = hashRoot(*it1, *it2);
itHFind = hashRoots.find(hashValue);
if (itHFind == hashRoots.end()) {
hashRoots.insert(pair<long long, int>(hashValue, partitionCount));
singleRoots.insert(partitionCount);
(*itAsgn) = partitionCount;
++partitionCount;
}
else {
(*itAsgn) = itHFind->second;
singleRoots.erase(itHFind->second);
}
}


// let distinct element be -1
set<int>::iterator itD;
for (auto &r : *parr) {

if (r == -1)
continue;
if (singleRoots.find(r) != singleRoots.end())
r = -1;
}


sizeEC = partitionCount;
hashRoots.clear();
singleRoots.clear();
}

void fromTable(const Database& db, int index) {
parr = new array<int, util::collen>();
unordered_map<string, pair<int, int>>::iterator itFind;
const array<string, util::collen>& column = db.table[index];
array<int, util::collen>::iterator itAsgn = parr->begin();
int row = 0;
int partitionCount = 0;
pair<int, int>* pInfo;
for (auto &str : column) {
itFind = smap.find(str);
if (itFind == smap.end()) {
smap[str] = pair<int, int>(hashRow(row), 0);
*itAsgn = -1;
}
else {
pInfo = &(itFind->second);
if (pInfo->first < 0) {
pInfo->first = inverseHashRow(pInfo->first);
pInfo->second = partitionCount;
(*parr)[pInfo->first] = partitionCount;
++partitionCount;
}
*itAsgn = pInfo->second;
}

++row;
++itAsgn;
}
sizeNDEC = partitionCount;
sizeEC = smap.size();
//cout << index << ": " << sizeEC << endl;

smap.clear();
}
};

-------------------------------------------------class PartSet-------------------------------

class PartSet {
public:
vector<pair<int, int>> *pvec;
map<int, int> *pmap;
int sizeEC;
public:
PartSet() : pvec(NULL), sizeEC(0) {}
~PartSet() {
if (pvec)
delete pvec;
}

void fromDatabase(const Database& db, int index) {
pmap = new map<int, int>();
int size = collen;
int row = 0;
int originRow;
const array<string, util::collen>& column = db.table[index];
//admap.clear();
unordered_map<string, int>::iterator itFind;
for (auto &str : column) {
itFind = admap.find(str);
if (itFind == admap.end()) {
admap.insert(pair<string, int>(str, hashRow(row)));
}
else {
--size;
// inverse
if (itFind->second < 0) {
originRow = inverseHashRow(itFind->second);
itFind->second = originRow;
pmap->insert(pair<int, int>(originRow, originRow));
}
else {
originRow = itFind->second;
}
pmap->insert(pair<int, int>(row, originRow));
}
++row;
}
sizeEC = size;
admap.clear();
cout << index << ": " << sizeEC - collen + pmap->size() << endl;
}

void fromProduct(const PartSet& ps1, const PartSet& ps2) {
// fake

// p1 = ps1.begin, p2 = ps2.begin
// while p1.row != p2.row:
//   drop min(p1, p2)
//   min(p1, p2)++
// (p1 == p2)
// hash = p1.root & p2.root
// if map.find(hash):
//   this.push(p1.row, map[hash])
// else:
//   this.push(p1.row, count)
//   ++count
// (reorder)
// drop distinct row




singleRoots.clear();
}



void getPartitionFromTable(const Database& db, const AttributeSet& attr) {
// 优化：toVector返回int*，减少一次赋值
// 优化：一次取出table的列or取多次
// 优化：直接向map的end插入,*itFind = pair<>...
as = attr;
singleRoots.clear();
partition.parr = new array<int, util::collen>();

vector<int> attrVec = attr.toVector();
unordered_map<string, int>::iterator itFind;
array<int, util::collen>::iterator itAsgn = partition.parr->begin();
int partitionCount = 0;

// only when 1 attr in AttributeSet
for (auto &index : attrVec) {
const array<string, util::collen>& column = db.table[index];
partitionCount = 0;
equivalenceClass.clear();
for (auto& str : column) {
itFind = equivalenceClass.find(str);
if (itFind == equivalenceClass.end()) {
equivalenceClass.insert(pair<string, int>(str, partitionCount));
singleRoots.insert(partitionCount);
(*itAsgn) = partitionCount;
++partitionCount;
}
else {
(*itAsgn) = itFind->second;
singleRoots.erase(itFind->second);
}
++itAsgn;
}
}

for (auto &r : *partition.parr) {
if (singleRoots.find(r) != singleRoots.end())
r = -1;
}

partition.sizeEC = partitionCount;
equivalenceClass.clear();
singleRoots.clear();
}

};

----------------------------------------------------class Partition----------------------------------

class Partition {
public:
map<StringKey, IndexSet> partition;
AttributeSet * as;
public:
Partition() { as = nullptr; }
Partition(AttributeSet &k, Database &db) {
this->doPartition(k, db);
}
public:

int cardinality() {
return partition.size();
}

void doPartition(AttributeSet &k, Database &db) {
as = &k;

int records_count = db.table[0].size();

list<string>::iterator *ps = new list<string>::iterator[db.table.size()];

vector<int> kVector = k.toVector();

for (auto attr : kVector) {
ps[attr] = db.table[attr].begin();
}

int first = *kVector.begin();
int index = 0;


while (ps[first] != db.table[first].end()) {
StringKey temp;

for (auto attr : kVector) {
temp.push_back(*ps[attr]);
ps[attr] ++;
}

map<StringKey, IndexSet>::iterator it = partition.find(temp);

if (it != partition.end()) {
it->second.insert(index);
}
else {
partition.insert(pair<StringKey, IndexSet>(temp, IndexSet(index)));
}

index++;
temp.clear();
}

delete[] ps;
}

void doPartition(Partition &p1, Partition &p2) {

}
};

-----------------------------------------------class DSPartition------------------------------------
class DSPartition {
public:
DisjointSet partition;
AttributeSet as;
PartSet psp;
public:
DSPartition() : as(NULL) {}
DSPartition(const Database& db, const AttributeSet& attr) : as(attr) {
getPartitionFromTable(db, as);
}
public:

int cardinality() {
return partition.sizeEC;
}

// read lines of <db> specified by <attr>, into this <ds>
void pfromTable(const Database& db, const AttributeSet& attr) {
// 优化：toVector返回int*，减少一次赋值
// 优化：一次取出table的列or取多次
// 优化：直接向map的end插入,*itFind = pair<>...
as = attr;
singleRoots.clear();
partition.parr = new array<int, util::collen>();

vector<int> attrVec = attr.toVector();
unordered_map<string, int>::iterator itFind;
array<int, util::collen>::iterator itAsgn = partition.parr->begin();
int partitionCount = 0;

// only when 1 attr in AttributeSet
for (auto &index : attrVec) {
const array<string, util::collen>& column = db.table[index];
partitionCount = 0;
equivalenceClass.clear();
for (auto& str : column) {
itFind = equivalenceClass.find(str);
if (itFind == equivalenceClass.end()) {
equivalenceClass.insert(pair<string, int>(str, partitionCount));
singleRoots.insert(partitionCount);
(*itAsgn) = partitionCount;
++partitionCount;
}
else {
(*itAsgn) = itFind->second;
singleRoots.erase(itFind->second);
}
++itAsgn;
}
}

for (auto &r : *partition.parr) {
if (singleRoots.find(r) != singleRoots.end())
r = -1;
}

partition.sizeEC = partitionCount;
equivalenceClass.clear();
singleRoots.clear();
cout << attr.toVector()[0] << ": " << partition.sizeEC << endl;
}

void getPartitionFromTable(const Database& db, const AttributeSet& attr) {
as = attr;
//psp.fromDatabase(db, attr.toVector()[0]);
//partition.fromTable(db, attr.toVector()[0]);
//pfromTable(db, attr);
}

void getPartitionFromProduct(DSPartition& p1, DSPartition& p2) {
//partition.fromProduct(p1.partition, p2.partition);
//as = p1.as.combine(p2.as);
}
};

----------------------------------------------class ECSet-----------------------------------
void fromTable(const Database& db, int index, unordered_map<string, int>& colmap) {
const vector<string>& column = db.table[index];
unordered_map<string, int>::iterator itFind;
vector<int> *newset = NULL;
int row = 0;
c.sizeNDEC = 0;
int hashedRow;

for (auto &str : column) {
itFind = colmap.find(str);
if (itFind == colmap.end()) {
colmap[str] = hashRow(row);
}
else {
hashedRow = itFind->second;
if (hashedRow < 0) {
newset = new vector<int>();
newset->push_back(inverseHashRow(hashedRow));
newset->push_back(row);
c.equivalentClassSet->push_back(*newset);
itFind->second = c.sizeNDEC;
++c.sizeNDEC;
}
else {
//equivalentClassSet[hashedRow].push_back(row);
c.equivalentClassSet->at(hashedRow).push_back(row);
}
}

++row;
}

c.sizeEC = colmap.size();
}

*/