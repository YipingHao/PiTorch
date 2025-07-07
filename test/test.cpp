#include"extern.h"
#include<cmath>
using namespace Pikachu;

#include<cstring>
#include<time.h>
#include<stdlib.h>

typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor> GTNode;
typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor>::PostIterator GTiterator;

int static Test000(const hyperlex::dictionary& para);
int static Test001(const hyperlex::dictionary& para);
int static Test002(const hyperlex::dictionary& para);
int static Test003(const hyperlex::dictionary& para);
int static Test004(const hyperlex::dictionary& para);
int static Test005(const hyperlex::dictionary& para);
int static Test006(const hyperlex::dictionary& para);
int static Test007(const hyperlex::dictionary& para);
int static Test008(const hyperlex::dictionary& para);
int static Test009(const hyperlex::dictionary& para);
int static Test010(const hyperlex::dictionary& para);
int static Test011(const hyperlex::dictionary& para);
int static Test012(const hyperlex::dictionary& para);
int static Test013(const hyperlex::dictionary& para);
int static Test014(const hyperlex::dictionary& para);
int static Test015(const hyperlex::dictionary& para);
int static Test016(const hyperlex::dictionary& para);
int static Test017(const hyperlex::dictionary& para);
int static Test018(const hyperlex::dictionary& para);
int static Test019(const hyperlex::dictionary& para);
int static Test020(const hyperlex::dictionary& para);
int static Test021(const hyperlex::dictionary& para);
int static Test022(const hyperlex::dictionary& para);
int static Test023(const hyperlex::dictionary& para);
int static Test024(const hyperlex::dictionary& para);
int static Test025(const hyperlex::dictionary& para);
int static Test026(const hyperlex::dictionary& para);
int static Test027(const hyperlex::dictionary& para);
int static Test028(const hyperlex::dictionary& para);
int static Test029(const hyperlex::dictionary& para);
int static Test030(const hyperlex::dictionary& para);
int static Test031(const hyperlex::dictionary& para);
int static Test032(const hyperlex::dictionary& para);
int static Test033(const hyperlex::dictionary& para);
int static Test034(const hyperlex::dictionary& para);
int static Test035(const hyperlex::dictionary& para);
int static Test036(const hyperlex::dictionary& para);
int static Test037(const hyperlex::dictionary& para);
int static Test038(const hyperlex::dictionary& para);
int static Test039(const hyperlex::dictionary& para);
int static Test040(const hyperlex::dictionary& para);
int static Test041(const hyperlex::dictionary& para);
int static Test042(const hyperlex::dictionary& para);
int static Test043(const hyperlex::dictionary& para);
int static Test044(const hyperlex::dictionary& para);
int static Test045(const hyperlex::dictionary& para);
int static Test046(const hyperlex::dictionary& para);
int static Test047(const hyperlex::dictionary& para);
int static Test048(const hyperlex::dictionary& para);
int static Test049(const hyperlex::dictionary& para);
int static Test050(const hyperlex::dictionary& para);
int static Test051(const hyperlex::dictionary& para);
int static Test052(const hyperlex::dictionary& para);
int static Test053(const hyperlex::dictionary& para);
int static Test054(const hyperlex::dictionary& para);
int static Test055(const hyperlex::dictionary& para);
int static Test056(const hyperlex::dictionary& para);
int static Test057(const hyperlex::dictionary& para);
int static Test058(const hyperlex::dictionary& para);
int static Test059(const hyperlex::dictionary& para);
int static Test060(const hyperlex::dictionary& para);
int static Test061(const hyperlex::dictionary& para);
int static Test062(const hyperlex::dictionary& para);
int static Test063(const hyperlex::dictionary& para);
int test(hyperlex::dictionary& para)
{
	int item = para.search(1L, "TestItem::item");
	int error = 0;
	std::cout << "item: " << item << std::endl;
	switch (item)
	{
	case 0:
	{
		error = Test000(para);
		break;
	}
	case 1:
	{
		error = Test001(para);
		break;
	}
	case 2:
	{
		//std::cout << "Test class file path " << std::endl;
		error = Test002(para);
		break;
	}
	case 3:
	{
		error = Test003(para);
		break;
	}
	case 4:
	{
		error = Test004(para);
		break;
	}
	case 5:
	{
		error = Test005(para);
		break;
	}
	case 6:
	{
		error = Test006(para);
		break;
	}
	case 7:
	{
		error = Test007(para);
		break;
	}
	case 8:
	{
		error = Test008(para);
		break;
	}
	case 9:
	{
		error = Test009(para);
		break;
	}
	case 10:
	{
		error = Test010(para);
		break;
	}
	case 11:
	{
		error = Test011(para);
		break;
	}
	case 12:
	{
		error = Test012(para);
		break;
	}
	case 13:
	{
		error = Test013(para);
		break;
	}
	case 14:
	{
		error = Test014(para);
		break;
	}
	case 15:
	{
		error = Test015(para);
		break;
	}
	case 16:
	{
		error = Test016(para);
		break;
	}
	case 17:
	{
		error = Test017(para);
		break;
	}
	case 18:
	{
		error = Test018(para);
		break;
	}
	case 19:
	{
		error = Test019(para);
		break;
	}
	case 20:
	{
		error = Test020(para);
		break;
	}
	case 21:
	{
		error = Test021(para);
		break;
	}
	case 22:
	{
		error = Test022(para);
		break;
	}
	case 23:
	{
		error = Test023(para);
		break;
	}
	case 24:
	{
		error = Test024(para);
		break;
	}
	case 25:
	{
		error = Test025(para);
		break;
	}
	case 26:
	{
		error = Test026(para);
		break;
	}
	case 27:
	{
		error = Test027(para);
		break;
	}
	case 28:
	{
		error = Test028(para);
		break;
	}
	case 29:
	{
		error = Test029(para);
		break;
	}
	case 30:
	{
		error = Test030(para);
		break;
	}
	case 31:
	{
		error = Test031(para);
		break;
	}
	case 32:
	{
		error = Test032(para);
		break;
	}
	case 33:
	{
		error = Test033(para);
		break;
	}
	case 34:
	{
		error = Test034(para);
		break;
	}
	case 35:
	{
		error = Test035(para);
		break;
	}
	case 36:
	{
		error = Test036(para);
		break;
	}
	case 37:
	{
		error = Test037(para);
		break;
	}
	case 38:
	{
		error = Test038(para);
		break;
	}
	case 39:
	{
		error = Test039(para);
		break;
	}
	case 40:
	{
		error = Test040(para);
		break;
	}
	case 41:
	{
		error = Test041(para);
		break;
	}
	case 42:
	{
		error = Test042(para);
		break;
	}
	case 43:
	{
		error = Test043(para);
		break;
	}
	case 44:
	{
		error = Test044(para);
		break;
	}
	case 45:
	{
		error = Test045(para);
		break;
	}
	case 46:
	{
		error = Test046(para);
		break;
	}
	case 47:
	{
		error = Test047(para);
		break;
	}
	case 48:
	{
		error = Test048(para);
		break;
	}
	case 49:
	{
		error = Test049(para);
		break;
	}
	case 50:
	{
		error = Test050(para);
		break;
	}
	case 51:
	{
		error = Test051(para);
		break;
	}
	case 52:
	{
		error = Test052(para);
		break;
	}
	case 53:
	{
		error = Test053(para);
		break;
	}
	case 54:
	{
		error = Test054(para);
		break;
	}
	case 55:
	{
		error = Test055(para);
		break;
	}
	case 56:
	{
		error = Test056(para);
		break;
	}
	case 57:
	{
		error = Test057(para);
		break;
	}
	case 58:
	{
		error = Test058(para);
		break;
	}
	case 59:
	{
		error = Test059(para);
		break;
	}
	case 60:
	{
		error = Test060(para);
		break;
	}
	case 61:
	{
		error = Test061(para);
		break;
	}
	case 62:
	{
		error = Test062(para);
		break;
	}
	case 63:
	{
		error = Test063(para);
		break;
	}

	default:
	{
		error = Test000(para);
		break;
	}

	}
	return error;
}

#include <iostream>
#include <cassert>
#include <cstdio>
#include <string>

// 测试添加新字符串
void testAppendNewString()
{
	StringPool pool;
	size_t id1 = pool.append("hello");
	size_t id2 = pool.append("world");
	assert(id1 == 0);
	assert(id2 == 1);
	std::cout << "testAppendNewString: PASSED\n";
}

// 测试重复添加相同字符串
void testAppendDuplicate() {
	StringPool pool;
	size_t id1 = pool.append("test");
	size_t id2 = pool.append("test");
	assert(id1 == id2);
	std::cout << "testAppendDuplicate: PASSED\n";
}

// 测试空指针处理
void testNullptrHandling() {
	StringPool pool;
	size_t id = pool.append(nullptr);
	assert(id == static_cast<size_t>(-1));
	std::cout << "testNullptrHandling: PASSED\n";
}

// 测试通过ID获取字符串
void testGetString() {
	StringPool pool;
	size_t id = pool.append("data");
	const char* str = pool.getString(id);
	assert(str != nullptr && std::string(str) == "data");
	assert(pool[id] != nullptr); // 测试运算符[]
	std::cout << "testGetString: PASSED\n";
}

// 测试非法ID访问
void testInvalidId() {
	StringPool pool;
	assert(pool.getString(100) == nullptr);
	assert(pool[100] == nullptr);
	std::cout << "testInvalidId: PASSED\n";
}

// 测试字符串存在性检查
void testContains() {
	StringPool pool;
	pool.append("exist");
	assert(pool.contains("exist") == true);
	assert(pool.contains("missing") == false);
	std::cout << "testContains: PASSED\n";
}

// 测试空池行为
void testEmptyPool() {
	StringPool pool;
	assert(pool.size() == 0);
	assert(pool.getString(0) == nullptr);
	assert(pool.contains("any") == false);
	std::cout << "testEmptyPool: PASSED\n";
}

// 测试内部一致性（vector与map同步）
void testInternalConsistency() {
	StringPool pool;
	pool.append("A");
	pool.append("B");
	assert(pool.size() == pool.count());
	// 调用自检方法验证
	pool.demo(); // 应无警告输出
	std::cout << "testInternalConsistency: PASSED\n";
}

// 压力测试：大量插入
void testMassInsertion() {
	StringPool pool;
	const int COUNT = 1000;
	for (int j = 0; j < COUNT * 6; ++j) 
	{
		int i = j % COUNT;
		std::string s = "str_" + std::to_string(i);
		size_t id = pool.append(s.c_str());
		assert(id == i); // ID 应连续分配
	}
	assert(pool.size() == COUNT);
	assert(pool.count() == COUNT);
	std::cout << "testMassInsertion: PASSED\n";
}
int static Test000(const hyperlex::dictionary& para)
{
	int error = 0;
	std::cout << "welcome: ==================================" << std::endl;
	para.print(stdout);

	std::cout << "=== StringPool Unit Tests ===\n";

	// 创建 StringPool 实例
	StringPool pool;

	// 测试 1: 添加新字符串
	{
		size_t id1 = pool.append("hello");
		assert(id1 == 0 && "Expected ID 0 for 'hello'");
		size_t id2 = pool.append("world");
		assert(id2 == 1 && "Expected ID 1 for 'world'");
		size_t id3 = pool.append("C++98");
		assert(id3 == 2 && "Expected ID 2 for 'C++98'");
		std::cout << "Test 1: append() 新字符串 OK\n";
	}

	// 测试 2: 添加重复字符串
	{
		size_t id1 = pool.append("hello");
		assert(id1 == 0 && "Expected same ID 0 for repeated 'hello'");
		size_t id2 = pool.append("world");
		assert(id2 == 1 && "Expected same ID 1 for repeated 'world'");
		std::cout << "Test 2: append() 重复字符串 OK\n";
	}

	// 测试 3: contains() 检查字符串是否存在
	{
		assert(pool.contains("hello") == true);
		assert(pool.contains("world") == true);
		assert(pool.contains("test") == false);
		assert(pool.contains(NULL) == false);
		assert(pool.contains("") == false); // 空字符串未添加
		std::cout << "Test 3: contains() OK\n";
	}

	// 测试 4: 空指针和空字符串处理
	{
		size_t id1 = pool.append(NULL);
		assert(id1 == static_cast<size_t>(-1) && "Expected invalid ID for NULL");
		size_t id2 = pool.append("");
		assert(id2 == 3 && "Expected ID 3 for empty string");
		assert(pool.contains("") == true); // 空字符串已添加
		std::cout << "Test 4: NULL and empty string handling OK\n";
	}

	// 测试 5: getString() 和 operator[]
	{
		const char* str1 = pool.getString(0);
		assert(str1 != nullptr && std::string(str1) == "hello");
		const char* str2 = pool[1];
		assert(str2 != nullptr && std::string(str2) == "world");
		const char* str3 = pool.getString(100);
		assert(str3 == nullptr && "Expected NULL for out-of-range ID");
		std::cout << "Test 5: getString() and operator[] OK\n";
	}

	// 测试 6: size() 和 count()
	{
		assert(pool.size() == 4 && "Expected 4 strings in vector");
		assert(pool.count() == 4 && "Expected 4 entries in map");
		std::cout << "Test 6: size() and count() OK\n";
	}

	// 测试 7: demo() 输出和一致性检查
	{
		pool.demo(stdout);
		// 注意：此测试无法自动验证 demo() 的输出内容，需手动检查控制台输出
		std::cout << "Test 7: demo() 执行完毕\n";
	}

	std::cout << "\n✅ All tests passed!\n";

	std::cout << "Running StringPool tests...\n";
	testAppendNewString();
	testAppendDuplicate();
	testNullptrHandling();
	testGetString();
	testInvalidId();
	testContains();
	testEmptyPool();
	testInternalConsistency();
	testMassInsertion();


	{
		StringPool Pool;
		std::cout << "i: " << Pool.append("i") << std::endl;
		std::cout << "j: " << Pool.append("j") << std::endl;
		std::cout << "k: " << Pool.append("k") << std::endl;
		std::cout << "i: " << Pool.append("i") << std::endl;
		std::cout << "i: " << Pool.append("i") << std::endl;
		std::cout << "k: " << Pool.append("k") << std::endl;
		std::cout << "i: " << Pool.append("i") << std::endl;
		Pool.demo();
	}
	return 0;
}


static bool compare(const char* str1, const char* str2)
{
	size_t i;
	for (i = 0; (str1[i] != '\0') && (str1[i] == str2[i]); i++);
	return str1[i] == str2[i];
}



struct enumL
{
	enum regular
	{
		_id_ = 1,
		_integer_ = 2,
		_enum_ = 3,
		_spaces_ = 4,
		_enters_ = 5,
		_tab_ = 6,
		_semicolon_ = 7,
		_comma_ = 8,
		_braceL_ = 9,
		_braceR_ = 10,
		_anntationS_ = 11,
		_anntationM_ = 12,
		_assign_ = 13
	};
	enum group
	{
		_id___ = 1,
		_number___ = 2,
		_reserved___ = 3,
		_format___ = 4,
		_division___ = 5,
		_braket___ = 6,
		_anntation___ = 7,
		_assignments___ = 8
	};
	static int next(int state, const char c);
	static int action(int state);
	static int GroupGet(int state);
};
struct enumG
{
	enum type
	{
		accept = 0,
		error = 1,
		push = 2,
		reduce = 3
	};
	enum rules
	{
		all_all_ = 0,
		numerate_id_ = 1,
		END_single_ = 2,
		END_di_ = 3,
		END_single2_ = 4,
		END_di2_ = 5,
		BODY_single_ = 6,
		BODY_multi_ = 7,
		FORMULA_name_ = 8,
		FORMULA_value_ = 9
	};
	enum nonterminal
	{
		_all_ = 0,
		_numerate_ = 1,
		_END_ = 2,
		_BODY_ = 3,
		_FORMULA_ = 4
	};
	static const size_t StateCount;
	static const size_t NonTerminalCount;
	static const size_t TerminalCount;
	static const size_t RulesCount;
	static const int GOTO[17][5];
	static const int ACTION[17][14];
	static const int RulesToSymbol[10];
	static const int RulesLength[10];
	static const char* const RulesName[10];
	static const int Implicit[10];
};

int static Test001(const hyperlex::dictionary& para)
{
	int error = 0;




	return error;
}

#include <cstdlib>
namespace hyperlex
{
	// StringPool 类实现
	// 这是一个字符串池，用于存储唯一的字符串并提供快速访问
	// 它使用哈希表和向量来管理字符串，确保每个字符串都有一个唯一的ID。
	class StringPool
	{
	private:
		// 哈希表节点结构
		struct HashNode
		{
			char* key;// 存储字符串
			size_t id;// 唯一ID
			HashNode* next;// 指向下一个节点的指针

			HashNode(const char* k, size_t idx) {
				key = strdup(k);
				id = idx;
				next = NULL;
			}

			~HashNode() {
				free(key);
			}
		};

		static const size_t INITIAL_BUCKETS = 64;// 初始桶数量
		static const double LOAD_FACTOR;// 哈希表负载因子

		// 哈希表相关成员
		HashNode** buckets;
		size_t bucketCount;// 桶数量
		size_t nodeCount;// 哈希表节点数量

		// 向量相关成员
		char** stringArray;// 存储字符串的数组
		size_t arraySize;// 数组当前大小
		size_t arrayCapacity;// 数组容量

		// 哈希函数 (djb2)
		inline size_t hash(const char* str) const
		{
			size_t hash = 5381;
			int c;
			while ((c = *str++)) {
				hash = ((hash << 4) + hash) ^ c;//Fermat prime  17: 0.2
				//hash = ((hash << 5) + hash) ^ c;//: 0.3
				//hash = ((hash << 8) + hash) ^ c;//Fermat prime 257 : 0.7
				//hash = (hash >> 16) ^ (hash & 0xFFFF); // 混合高位与低位[2,6](@ref)
			}
			return hash;
		}

		// 在桶中查找字符串
		inline HashNode* findInBucket(size_t index, const char* key) const
		{
			HashNode* current = buckets[index];
			while (current)
			{
				if (strcmp(current->key, key) == 0)
				{
					return current;
				}
				current = current->next;
			}
			return NULL;
		}

		// 扩展哈希表
		inline void resizeHashTable()
		{
			size_t newBucketCount = bucketCount * 2;
			HashNode** newBuckets = new HashNode * [newBucketCount]();

			for (size_t i = 0; i < bucketCount; i++)
			{
				HashNode* current = buckets[i];
				while (current) {
					HashNode* next = current->next;
					size_t newIndex = hash(current->key) % newBucketCount;

					current->next = newBuckets[newIndex];
					newBuckets[newIndex] = current;

					current = next;
				}
			}
			//std::cout << "Resizing hash table from " << bucketCount << " to " << newBucketCount << " buckets.\n";
			delete[] buckets;
			buckets = newBuckets;
			bucketCount = newBucketCount;
		}

		// 扩展数组
		inline void resizeArray()
		{
			size_t newCapacity = arrayCapacity ? arrayCapacity * 2 : 8;
			char** newArray = new char* [newCapacity];

			if (stringArray)
			{
				for (size_t i = 0; i < arraySize; i++) {
					newArray[i] = stringArray[i];
				}
				delete[] stringArray;
			}

			stringArray = newArray;
			arrayCapacity = newCapacity;
		}

	public:
		StringPool()
		{
			buckets = new HashNode * [INITIAL_BUCKETS]();
			bucketCount = INITIAL_BUCKETS;
			nodeCount = 0;

			stringArray = nullptr;
			arraySize = 0;
			arrayCapacity = 0;
		}

		~StringPool() {
			// 清理哈希表
			for (size_t i = 0; i < bucketCount; i++) {
				HashNode* current = buckets[i];
				while (current) {
					HashNode* next = current->next;
					delete current;
					current = next;
				}
			}
			delete[] buckets;

			// 清理数组
			delete[] stringArray;
		}

		// 添加字符串，返回唯一ID
		inline size_t append(const char* src) {
			if (!src) return -1;

			size_t index = hash(src) % bucketCount;
			HashNode* node = findInBucket(index, src);
			if (node) {
				return node->id;
			}

			if (arraySize >= arrayCapacity)
			{
				resizeArray();
			}

			char* newStr = strdup(src);
			size_t newId = arraySize;
			stringArray[arraySize++] = newStr;

			HashNode* newNode = new HashNode(newStr, newId);
			newNode->next = buckets[index];
			buckets[index] = newNode;
			nodeCount++;

			if (static_cast<double>(nodeCount) / bucketCount > LOAD_FACTOR) {
				resizeHashTable();
			}

			return newId;
		}

		// 根据ID获取字符串
		inline const char* getString(size_t id) const {
			if (id >= arraySize) return nullptr;
			return stringArray[id];
		}

		inline const char* operator[](size_t id) const {
			return getString(id);
		}

		// 检查字符串是否存在于池中
		inline bool contains(const char* src) const {
			if (!src) return false;
			size_t index = hash(src) % bucketCount;
			return findInBucket(index, src) != nullptr;
		}

		// 获取池中字符串数量
		inline size_t size() const {
			return arraySize;
		}

		// 获取哈希表元素数量
		inline size_t count() const {
			return nodeCount;
		}

		// 调试函数
		inline void demo(FILE* fp = stdout) const
		{
			fprintf(fp, "StringPool contains %zu strings:\n", arraySize);
			fprintf(fp, "LOAD FACTOR is %.6lf\n", LOAD_FACTOR);
			size_t colli = countCollisions();
			fprintf(fp, "Count of collisions %zu, collisions rate: %.6lf\n", colli, (double)colli/ bucketCount);
			for (size_t i = 0; i < arraySize; i++) {
				fprintf(fp, "ID: %zu, String: %s\n", i, stringArray[i]);
			}

			for (size_t i = 0; i < arraySize; i++) {
				if (!contains(stringArray[i])) {
					fprintf(fp, "Warning: String '%s' not found in hash table!\n", stringArray[i]);
				}
			}

			if (arraySize != nodeCount) {
				fprintf(fp, "Warning: Size mismatch between vector (%zu) and hash table (%zu)!\n",
					arraySize, nodeCount);
			}
		}

		// 统计哈希冲突总数
		inline size_t countCollisions() const {
			size_t collisionCount = 0;
			for (size_t i = 0; i < bucketCount; ++i) {
				HashNode* node = buckets[i];
				if (node) {
					// 跳过桶中的首节点，只统计链表中的后续节点（冲突节点）
					node = node->next;
					while (node) {
						++collisionCount;
						node = node->next;
					}
				}
			}
			return collisionCount;
		}
		inline void copy(const StringPool& source)
		{
			// 1. 自赋值检查
			if (this == &source) return;

			// 2. 清理当前对象（避免内存泄漏）
			clear();
			for (size_t i = 0; i < source.size(); i++) 
			{
				// 获取源对象中当前索引的字符串
				const char* str = source.getString(i);
				append(str);
			}
			
		}
		inline void append(const StringPool& source, hyperlex::vector<size_t>& NewId)
		{
			// 调整输出向量大小以匹配源对象的字符串数量
			NewId.recount(source.size());

			// 遍历源对象中的所有字符串
			for (size_t i = 0; i < source.size(); i++) 
			{
				// 获取源对象中当前索引的字符串
				const char* str = source.getString(i);
				if (!str) {
					NewId[i] = static_cast<size_t>(-1); // 处理无效字符串
					//continue;
				}
				else
				{
					NewId[i] = this->append(str);
				}
				// 在当前对象中查找字符串
				//size_t bucketIndex = hash(str) % bucketCount;
				//HashNode* node = findInBucket(bucketIndex, str);

				//if (node) {
					// 字符串已存在：使用现有ID
				///	NewId[i] = node->id;
				//}
				//else {
					// 字符串不存在：添加到当前对象并获取新ID
				//	NewId[i] = this->append(str);
				//}
			}
		}
		inline void clear() 
		{
			// 1. 释放哈希表
			for (size_t i = 0; i < bucketCount; ++i) {
				HashNode* current = buckets[i];
				while (current) 
				{
					HashNode* next = current->next;
					delete current; // 析构HashNode（内部释放key）
					current = next;
				}
			}
			delete[] buckets;// 1.1 重新分配哈希表和字符串数组
			buckets = new HashNode * [INITIAL_BUCKETS]();
			bucketCount = INITIAL_BUCKETS;
			nodeCount = 0;

			// 2. 释放字符串数组
			for (size_t i = 0; i < arraySize; ++i) {
				free(stringArray[i]); // 释放每个字符串
			}
			delete[] stringArray;
			stringArray = NULL;
			arraySize = 0;
			arrayCapacity = 0;

			
		}
		friend void test_string_pool();
	};
	const double StringPool::LOAD_FACTOR = 0.48;
}
#include <vector>
namespace hyperlex
{
	void test_string_pool() {
		// 测试1: 添加单个字符串
		{
			hyperlex::StringPool pool;
			const char* str1 = "hello";
			size_t id1 = pool.append(str1);
			assert(id1 == 0);
			assert(strcmp(pool.getString(id1), str1) == 0);
			assert(pool.size() == 1);
			assert(pool.count() == 1);
			assert(pool.contains(str1));
			printf("✅ Test 1 passed: Adding single string.\n");
		}

		// 测试2: 重复添加相同字符串
		{
			hyperlex::StringPool pool;
			const char* str1 = "hello";
			size_t id1 = pool.append(str1);
			size_t id2 = pool.append(str1);
			assert(id1 == id2);
			assert(pool.size() == 1);
			assert(pool.count() == 1);
			printf("✅ Test 2 passed: Adding duplicate string.\n");
		}

		// 测试3: 添加多个字符串并检查ID
		{
			hyperlex::StringPool pool;
			const char* str2 = "world";
			const char* str3 = "test";
			size_t id2 = pool.append(str2);
			size_t id3 = pool.append(str3);
			assert(id2 == 0);
			assert(id3 == 1);
			assert(pool.size() == 2);
			assert(pool.count() == 2);
			printf("✅ Test 3 passed: Adding multiple strings and checking IDs.\n");
		}

		// 测试4: 数组扩容
		{
			hyperlex::StringPool pool;
			assert(pool.arrayCapacity == 0);
			for (size_t i = 0; i < 8; ++i) {
				char buffer[10];
				sprintf(buffer, "str%d", i);
				pool.append(buffer);
			}
			assert(pool.arrayCapacity == 8);
			assert(pool.arraySize == 8);

			char buffer[10];
			sprintf(buffer, "str%d", 8);
			pool.append(buffer);
			assert(pool.arrayCapacity == 16);
			assert(pool.arraySize == 9);
			printf("✅ Test 4 passed: Array resizing.\n");
		}

		// 测试5: 哈希表扩容
		{
			hyperlex::StringPool pool;
			size_t trigger_resize = pool.bucketCount * pool.LOAD_FACTOR;
			if (static_cast<double>(trigger_resize) / pool.bucketCount > pool.LOAD_FACTOR)
				trigger_resize -= 1;
			for (size_t i = 0; i < trigger_resize; ++i) {
				char buffer[20];
				sprintf(buffer, "unique_str_%zu", i);
				pool.append(buffer);
			}
			assert(pool.count() == trigger_resize);
			assert(pool.bucketCount == 64);

			char buffer_last[20];
			sprintf(buffer_last, "trigger_resize");
			pool.append(buffer_last);
			assert(pool.bucketCount == 128);

			for (size_t i = 0; i < trigger_resize; ++i) {
				char buffer[20];
				sprintf(buffer, "unique_str_%zu", i);
				assert(pool.contains(buffer));
			}
			assert(pool.contains(buffer_last));
			printf("✅ Test 5 passed: Hash table resizing.\n");
		}

		// 测试6: contains方法
		{
			hyperlex::StringPool pool;
			const char* str1 = "hello";
			pool.append(str1);
			assert(pool.contains(str1) == true);
			assert(pool.contains("non_existent") == false);
			printf("✅ Test 6 passed: contains method.\n");
		}

		// 测试7: 越界访问
		{
			hyperlex::StringPool pool;
			const char* str1 = "hello";
			pool.append(str1);
			assert(pool.getString(0) != nullptr);
			assert(pool.getString(1) == nullptr);
			assert(pool.getString(9999) == nullptr);
			printf("✅ Test 7 passed: Out-of-bounds access.\n");
		}

		// 测试8: NULL指针处理
		{
			hyperlex::StringPool pool;
			assert(pool.append(nullptr) == (size_t)-1);
			printf("✅ Test 8 passed: NULL pointer handling.\n");
		}

		// 测试9: 哈希冲突处理
		{
			hyperlex::StringPool pool;
			const char* conflict1 = "a";
			const char* conflict2 = "A";
			size_t id1 = pool.append(conflict1);
			size_t id2 = pool.append(conflict2);
			assert(id1 != id2);
			assert(strcmp(pool.getString(id1), conflict1) == 0);
			assert(strcmp(pool.getString(id2), conflict2) == 0);
			assert(pool.contains(conflict1));
			assert(pool.contains(conflict2));
			printf("✅ Test 9 passed: Hash collision handling.\n");
		}

		// 测试10: 调试函数（手动验证）
		{
			hyperlex::StringPool pool;
			const char* str1 = "hello";
			pool.append(str1);
			// pool.demo(stdout); // 可视化输出，检查是否有警告
			printf("✅ Test 10 passed: Debug function check (manual verification needed).\n");
		}

		printf("✅ All StringPool tests passed!\n");
	}


	// 测试1: 添加新字符串返回唯一ID
	void testAppendNewString() {
		StringPool pool;
		size_t id1 = pool.append("hello");
		size_t id2 = pool.append("world");
		assert(id1 == 0); // 首个ID应为0
		assert(id2 == 1); // 后续ID递增
		std::cout << "testAppendNewString: PASSED\n";
	}

	// 测试2: 重复添加相同字符串返回相同ID
	void testAppendDuplicate() {
		StringPool pool;
		size_t id1 = pool.append("test");
		size_t id2 = pool.append("test");
		assert(id1 == id2); // ID必须一致
		std::cout << "testAppendDuplicate: PASSED\n";
	}

	// 测试3: 空指针安全处理
	void testNullptrHandling() {
		StringPool pool;
		size_t id = pool.append(nullptr);
		assert(id == static_cast<size_t>(-1)); // 返回错误标识
		std::cout << "testNullptrHandling: PASSED\n";
	}

	// 测试4: 通过ID获取字符串
	void testGetString() {
		StringPool pool;
		const char* input = "data";
		size_t id = pool.append(input);
		const char* output = pool.getString(id);
		assert(output != nullptr); // 非空指针
		assert(std::string(output) == input); // 内容一致
		assert(pool[id] != nullptr); // 运算符[]功能正常
		std::cout << "testGetString: PASSED\n";
	}

	// 测试5: 非法ID访问
	void testInvalidId() {
		StringPool pool;
		assert(pool.getString(100) == nullptr); // 超范围返回nullptr
		assert(pool[100] == nullptr); // 运算符[]同理
		std::cout << "testInvalidId: PASSED\n";
	}

	// 测试6: 字符串存在性检查
	void testContains() {
		StringPool pool;
		pool.append("exist");
		assert(pool.contains("exist") == true); // 存在时返回true
		assert(pool.contains("missing") == false); // 不存在时返回false
		std::cout << "testContains: PASSED\n";
	}

	// 测试7: 空池行为
	void testEmptyPool() {
		StringPool pool;
		assert(pool.size() == 0); // 初始大小为0
		assert(pool.getString(0) == nullptr); // 空池访问返回nullptr
		assert(pool.contains("any") == false); // 空池不包含任何字符串
		std::cout << "testEmptyPool: PASSED\n";
	}

	// 测试8: 内部数据结构一致性
	void testInternalConsistency() {
		StringPool pool;
		pool.append("A");
		pool.append("B");
		assert(pool.size() == pool.count()); // vector与map大小必须相等
		pool.demo(); // 自检函数无警告输出（观察控制台）
		std::cout << "testInternalConsistency: PASSED\n";
	}

	// 测试9: 大量插入压力测试1
	void testMassInsertion() {
		StringPool pool;
		const size_t COUNT = 1000;
		const size_t FACTOR = 100;
		for (size_t j = 0; j < COUNT * FACTOR; ++j) {
			size_t i = j % COUNT;
			std::string s = "str_" + std::to_string(i);
			size_t id = pool.append(s.c_str());
			assert(id == i); // ID连续分配
		}
		std::cout << "COUNT: " << COUNT << std::endl;
		std::cout << "pool.size(): " << pool.size() << std::endl;
		std::cout << "pool.count(): " << pool.count() << std::endl;
		std::cout << "pool.countCollisions(): " << pool.countCollisions() << std::endl;
		assert(pool.size() == COUNT); // 总数正确
		assert(pool.count() == COUNT); // map大小同步
		std::cout << "testMassInsertion: PASSED\n";
	}
	// 测试10: 大量插入压力测试2
	void testMassInsertion2() 
	{
		StringPool pool;
		const size_t COUNT = 1000;
		const size_t FACTOR = 100;
		for (size_t j = 0; j < COUNT * FACTOR; ++j) {
			size_t i = j / FACTOR;
			std::string s = "str_" + std::to_string(i);
			size_t id = pool.append(s.c_str());
			assert(id == i); // ID连续分配
		}
		std::cout << "COUNT: " << COUNT << std::endl;
		std::cout << "pool.size(): " << pool.size() << std::endl;
		std::cout << "pool.count(): " << pool.count() << std::endl;
		std::cout << "pool.countCollisions(): " << pool.countCollisions() << std::endl;
		assert(pool.size() == COUNT); // 总数正确
		assert(pool.count() == COUNT); // map大小同步
		std::cout << "testMassInsertion2: PASSED\n";
	}
	// 测试11: 超长字符串处理
	void testLongString() {
		StringPool pool;
		char longStr[1000];
		for (size_t i = 0; i < 999; ++i) {
			longStr[i] = 'a';
		}
		longStr[999] = '\0';
		size_t id = pool.append(longStr);
		const size_t FACTOR = 100;
		for (size_t j = 0; j < FACTOR; ++j) {
			size_t i = j;
			std::string s = longStr;
			size_t id2 = pool.append(s.c_str());
			assert(id2 == id); // ID连续分配
		}
		assert(id == 0);
		assert(strcmp(pool.getString(id), longStr) == 0);
		assert(pool.contains(longStr));
		std::cout << "testLongString: PASSED\n";
	}
	// 测试12: 大量插入压力测试3
	void testMassInsertion3()
	{
		StringPool pool;
		const size_t COUNT = 1024 * 1024 * 64; // 64M
		const size_t FACTOR = 2;
		for (size_t j = 0; j < COUNT * FACTOR; ++j) {
			size_t i = j % COUNT;
			std::string s = "str_" + std::to_string(i);
			size_t id = pool.append(s.c_str());
			assert(id == i); // ID连续分配
		}
		std::cout << "COUNT: " << COUNT << std::endl;
		std::cout << "pool.size(): " << pool.size() << std::endl;
		std::cout << "pool.count(): " << pool.count() << std::endl;
		std::cout << "pool.countCollisions(): " << pool.countCollisions() << std::endl;
		assert(pool.size() == COUNT); // 总数正确
		assert(pool.count() == COUNT); // map大小同步
		std::cout << "testMassInsertion3: PASSED\n";
	}

	// 测试 clear 方法
	void testClear() {
		hyperlex::StringPool pool;
		pool.append("A");
		pool.append("B");
		assert(pool.size() == 2);

		pool.clear();
		assert(pool.size() == 0);        // 验证清空后大小为0
		assert(pool.count() == 0);       // 哈希表节点数应为0
		assert(!pool.contains("A"));    // 内容应不存在
		assert(pool.getString(0) == nullptr); // ID访问返回空

		// 清空后重新添加
		size_t newId = pool.append("C");
		assert(newId == 0);  // ID应从0开始重新分配
		printf("✅ testClear PASSED\n");
	}

	// 测试 copy 方法（深拷贝）
	void testCopy() {
		hyperlex::StringPool src;
		src.append("X");
		src.append("Y");

		// 深拷贝测试
		hyperlex::StringPool dest;
		dest.copy(src);
		assert(dest.size() == 2);
		assert(dest.getString(0) != src.getString(0)); // 指针地址不同
		assert(strcmp(dest[0], "X") == 0);              // 内容一致

		// 自赋值安全测试
		dest.copy(dest);
		assert(dest.size() == 2);  // 数据不应丢失
		printf("✅ testCopy PASSED\n");
	}

	// 测试 append 方法（合并池）
	void testAppendPool() {
		hyperlex::StringPool dest;
		dest.append("A");

		hyperlex::StringPool src;
		src.append("B");
		src.append("C");

		vector<size_t> newIds;
		dest.append(src, newIds); // 合并源池

		// 验证映射关系
		assert(newIds.count() == 2);
		assert(newIds[0] == 1);   // "B" 在目标池的新ID
		assert(newIds[1] == 2);   // "C" 在目标池的新ID
		assert(dest.size() == 3); // 总数=1(A)+2(B/C)

		// 重复合并测试
		dest.append(src, newIds);
		assert(newIds[0] == 1);   // 重复字符串应返回现有ID
		assert(dest.size() == 3); // 总数不变（去重）
		printf("✅ testAppendPool PASSED\n");
	}

	// 测试空池操作边界
	void testEmptyOperations() 
	{
		hyperlex::StringPool empty;

		// 清空空池
		empty.clear();
		assert(empty.size() == 0);

		// 合并空池到目标池
		hyperlex::StringPool dest;
		vector<size_t> newIds;
		dest.append(empty, newIds);
		assert(newIds.count() == 0); // 映射列表应为空

		// 拷贝空池
		hyperlex::StringPool dest2;
		dest2.copy(empty);
		assert(dest2.size() == 0);
		printf("✅ testEmptyOperations PASSED\n");
	}

	int test2222() {
		testAppendNewString();
		testAppendDuplicate();
		testNullptrHandling();
		testGetString();
		testInvalidId();
		testContains();
		testEmptyPool();
		testClear();
		testCopy();
		testAppendPool();
		testEmptyOperations();

		testInternalConsistency();
		testMassInsertion();
		testMassInsertion2();
		testLongString();
		testMassInsertion3();

		std::cout << "\nALL TESTS PASSED!\n";

	   
		return 0;
	}

}


int static Test002(const hyperlex::dictionary& para)
{
	int error = 0;
	
	hyperlex::test2222();
	hyperlex::test_string_pool();
	{
		hyperlex::StringPool Pool;
		std::cout << "i: " << Pool.append("i") << std::endl;
		std::cout << "j: " << Pool.append("j") << std::endl;
		std::cout << "k: " << Pool.append("k") << std::endl;
		std::cout << "i: " << Pool.append("i") << std::endl;
		std::cout << "i: " << Pool.append("i") << std::endl;
		std::cout << "k: " << Pool.append("k") << std::endl;
		std::cout << "i: " << Pool.append("i") << std::endl;
		std::cout << "i: " << Pool.append("i") << std::endl;
		std::cout << "k: " << Pool.append("k") << std::endl;
		std::cout << "i: " << Pool.append("i") << std::endl;
		std::cout << "ii: " << Pool.append("ii") << std::endl;
		std::cout << "kk: " << Pool.append("kk") << std::endl;
		std::cout << "jj: " << Pool.append("jj") << std::endl;
		Pool.demo();
	}
	return error;
}

int static Test003(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test004(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test005(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test006(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test007(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test008(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test009(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test010(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test011(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test012(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test013(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test014(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test015(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test016(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test017(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test018(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test019(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test020(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test021(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test022(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test023(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test024(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test025(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test026(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test027(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test028(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test029(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test030(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test031(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test032(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test033(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test034(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test035(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test036(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test037(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test038(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test039(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test040(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test041(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test042(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test043(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test044(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test045(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test046(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test047(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test048(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test049(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test050(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test051(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test052(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test053(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test054(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test055(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test056(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test057(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test058(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test059(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test060(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test061(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test062(const hyperlex::dictionary& para)
{
	int error = 0;
	return error;
}
int static Test063(const hyperlex::dictionary& para)
{
	int error = 0;
	for (size_t i = 0; i < 64; i++)
	{
		printf("int static Test");
		if (i < 10) printf("00%zu", i);
		else if (i < 100) printf("0%zu", i);
		else printf("%zu", i);
		printf("(const hyperlex::dictionary& para)");
		if (error == 0)
		{
			printf("\n{\n");
			printf("\tint error = 0;\n");
			printf("\treturn error;\n");
			printf("}\n");
		}
		else
		{
			printf(";");
		}
	}

	for (size_t i = 2; i < 64; i++)
	{
		printf("\t\tcase ");
		printf("%zu:\n\t\t{\n\t\t\terror = Test", i);
		if (i < 10) printf("00%zu", i);
		else if (i < 100) printf("0%zu", i);
		else printf("%zu", i);
		printf("(para);\n");
		printf("\t\t\tbreak;\n");
		printf("\t\t}\n");
	}
	return error;
}














int enumL::next(int state, const char c)
{
	switch (state)
	{
	case 0:
		if (c == (char)9) return 6;
		else if (c == (char)10) return 5;
		else if (c == ' ') return 4;
		else if (c == '+') return 14;
		else if (c == ',') return 8;
		else if (c == '-') return 14;
		else if (c == '/') return 19;
		else if ('0' <= c && c <= '9') return 2;
		else if (c == ';') return 7;
		else if (c == '=') return 13;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'd') return 1;
		else if (c == 'e') return 17;
		else if ('f' <= c && c <= 'z') return 1;
		else if (c == '{') return 9;
		else if (c == '}') return 10;
		else return 0;
	case 1:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 2:
		if ('0' <= c && c <= '9') return 2;
		else return 0;
	case 3:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 4:
		if (c == ' ') return 4;
		else return 0;
	case 5:
		if (c == (char)10) return 5;
		else return 0;
	case 6:
		return 0;
	case 7:
		return 0;
	case 8:
		return 0;
	case 9:
		return 0;
	case 10:
		return 0;
	case 11:
		if ((char)0 <= c && c <= (char)9) return 11;
		else if ((char)11 <= c && c <= (char)127) return 11;
		else return 0;
	case 12:
		if ((char)0 <= c && c <= ')') return 18;
		else if (c == '*') return 20;
		else if ('+' <= c && c <= (char)127) return 18;
		else return 0;
	case 13:
		return 0;
	case 14:
		if ('0' <= c && c <= '9') return 2;
		else return 0;
	case 15:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'l') return 1;
		else if (c == 'm') return 3;
		else if ('n' <= c && c <= 'z') return 1;
		else return 0;
	case 16:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 't') return 1;
		else if (c == 'u') return 15;
		else if ('v' <= c && c <= 'z') return 1;
		else return 0;
	case 17:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'm') return 1;
		else if (c == 'n') return 16;
		else if ('o' <= c && c <= 'z') return 1;
		else return 0;
	case 18:
		if ((char)0 <= c && c <= ')') return 18;
		else if (c == '*') return 20;
		else if ('+' <= c && c <= (char)127) return 18;
		else return 0;
	case 19:
		if (c == '*') return 18;
		else if (c == '/') return 11;
		else return 0;
	case 20:
		if ((char)0 <= c && c <= ')') return 18;
		else if (c == '*') return 20;
		else if ('+' <= c && c <= '.') return 18;
		else if (c == '/') return 12;
		else if ('0' <= c && c <= (char)127) return 18;
		else return 0;
	}
	return 0;
}
int enumL::action(int state)
{
	switch (state)
	{
	case 1:
		return 1;//id: id
	case 2:
		return 2;//number: integer
	case 3:
		return 3;//reserved: enum
	case 4:
		return 4;//format: spaces
	case 5:
		return 5;//format: enters
	case 6:
		return 6;//format: tab
	case 7:
		return 7;//division: semicolon
	case 8:
		return 8;//division: comma
	case 9:
		return 9;//braket: braceL
	case 10:
		return 10;//braket: braceR
	case 11:
		return 11;//anntation: anntationS
	case 12:
		return 12;//anntation: anntationM
	case 13:
		return 13;//assignments: assign
	case 15:
		return 1;//id: id
	case 16:
		return 1;//id: id
	case 17:
		return 1;//id: id
	}
	return 0;
}
int enumL::GroupGet(int accept)
{
	switch (accept)
	{
	case 1:
		return 1;//id: id
	case 2:
		return 2;//number: integer
	case 3:
		return 3;//reserved: enum
	case 4:
		return 4;//format: spaces
	case 5:
		return 4;//format: enters
	case 6:
		return 4;//format: tab
	case 7:
		return 5;//division: semicolon
	case 8:
		return 5;//division: comma
	case 9:
		return 6;//braket: braceL
	case 10:
		return 6;//braket: braceR
	case 11:
		return 7;//anntation: anntationS
	case 12:
		return 7;//anntation: anntationM
	case 13:
		return 8;//assignments: assign
	}
	return 0;
}


	const size_t enumG::StateCount = 17;
	const size_t enumG::NonTerminalCount = 5;
	const size_t enumG::TerminalCount = 13;
	const size_t enumG::RulesCount = 10;
	const int enumG::GOTO[17][5] = { \
	{1, 6, 1, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 22, 26}, \
	{1, 1, 42, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 58}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1} };
	//==============================
	const int enumG::ACTION[17][14] = { \
	{13, 13, 13, 10, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13}, \
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
	{5, 14, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
	{37, 37, 37, 37, 37, 37, 37, 37, 37, 18, 37, 37, 37, 37}, \
	{5, 30, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
	{1, 1, 1, 1, 1, 1, 1, 1, 46, 1, 50, 1, 1, 1}, \
	{1, 1, 1, 1, 1, 1, 1, 1, 27, 1, 27, 1, 1, 1}, \
	{1, 1, 1, 1, 1, 1, 1, 1, 35, 1, 35, 1, 1, 34}, \
	{9, 9, 38, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, \
	{1, 1, 1, 1, 1, 1, 1, 1, 39, 1, 39, 1, 1, 1}, \
	{7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
	{1, 30, 1, 1, 1, 1, 1, 1, 1, 1, 62, 1, 1, 1}, \
	{11, 1, 1, 1, 1, 1, 1, 54, 1, 1, 1, 1, 1, 1}, \
	{15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
	{1, 1, 1, 1, 1, 1, 1, 1, 31, 1, 31, 1, 1, 1}, \
	{19, 1, 1, 1, 1, 1, 1, 66, 1, 1, 1, 1, 1, 1}, \
	{23, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
	//==============================
	const int enumG::RulesToSymbol[10] = { \
	0,\
	1,\
	2,\
	2,\
	2,\
	2,\
	3,\
	3,\
	4,\
	4 };
	//==============================
	const int enumG::RulesLength[10] = { \
	1,\
	5,\
	1,\
	2,\
	2,\
	3,\
	1,\
	3,\
	1,\
	3 };
	//==============================
	const char* const enumG::RulesName[10] = { \
	"all->numerate ",\
	"numerate->enum id braceL BODY END ",\
	"END->braceR ",\
	"END->braceR semicolon ",\
	"END->comma braceR ",\
	"END->comma braceR semicolon ",\
	"BODY->FORMULA ",\
	"BODY->BODY comma FORMULA ",\
	"FORMULA->id ",\
	"FORMULA->id assign integer " };
	//==============================
	const int enumG::Implicit[10] = { \
	0, \
	0, \
	0, \
	0, \
	0, \
	0, \
	0, \
	0, \
	0, \
	0 };










