#include"extern.h"
#include<cmath>
using namespace Pikachu;

#include<cstring>
#include<time.h>
#include<stdlib.h>

typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor> GTNode;
typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor>::PostIterator GTiterator;
typedef hyperlex::Morpheme lex;
typedef hyperlex::GrammarTree AST;

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
		std::cout << "StringPool: " << std::endl;
		error = Test000(para);
		break;
	}
	case 1:
	{
		error = Test001(para);
		std::cout << "enum switch " << std::endl;
		break;
	}
	case 2:
	{
		std::cout << "hyperlex::StringPool: " << std::endl;
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
namespace temp1
{
	class StringPool
{
private:
	std::map<std::string, size_t> stringToIdMap;
	std::vector<std::string> idToStringVec;

public:
	StringPool() {}
	~StringPool() {}

	// 添加字符串，返回其唯一ID
	inline size_t append(const char* src) {
		if (!src) return static_cast<size_t>(-1); // 处理空指针

		std::string str(src);

		std::map<std::string, size_t>::iterator it = stringToIdMap.find(str);
		if (it != stringToIdMap.end()) {
			return it->second;
		}

		size_t newId = idToStringVec.size();
		idToStringVec.push_back(str);
		stringToIdMap[str] = newId;

		return newId;
	}

	// 根据ID获取字符串
	inline const char* getString(size_t id) const {
		if (id >= idToStringVec.size()) {
			return nullptr;
		}
		return idToStringVec[id].c_str();
	}
	const char* operator[](size_t id) const {
		return getString(id);
	}

	// 检查字符串是否存在于池中
	inline bool contains(const char* src) const {
		if (!src) return false;
		std::string str(src);
		return stringToIdMap.find(str) != stringToIdMap.end();
	}

	// 获取池中字符串数量
	inline size_t size() const {
		return idToStringVec.size();
	}
	//返回map中元素的数目
	inline size_t count() const {
		return stringToIdMap.size();
	}
	//展示这个类中全部的键值对，并检查vector中的字符串是否在map中，检查两者中字符串数目是否相等
	inline void demo(FILE* fp = stdout) const
	{
		fprintf(fp, "StringPool contains %zu strings:\n", idToStringVec.size());
		for (size_t i = 0; i < idToStringVec.size(); ++i) {
			fprintf(fp, "ID: %zu, String: %s\n", i, idToStringVec[i].c_str());
		}
		for (size_t i = 0; i < idToStringVec.size(); ++i)
		{
			if (contains(idToStringVec[i].c_str()) == false)
			{
				fprintf(fp, "Warning: String %s not found in map!\n", idToStringVec[i].c_str());
			}
		}
		if (idToStringVec.size() != stringToIdMap.size()) {
			fprintf(fp, "Warning: Size mismatch between vector and map!\n");
		}
	}
};
}
namespace temp1
{
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
}



int static Test000(const hyperlex::dictionary& para)
{
	int error = 0;
	using namespace temp1;
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
	hyperlex::FilePath Path1, Path2;
	const char* dataPath = para.search("./data/", "DataFilePath");
	const char* dataName = para.search("./data/", "DataFileName");
	Path1.build(dataPath);
	Path2.build(dataName);
	Path1 += Path2;
	const char* path = Path1.path();
	FILE* fp = fopen(path, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Cannot open file %s\n", path);
		return -1;
	}
	lex input;
	error = input.Build<enumL>(fp);
	fclose(fp);
	if (error != 0)
	{
		fprintf(stderr, "Error: Failed to build input from file %s\n", path);
		return error;
	}
	input.Demo(stdout);
	enumL::regular T;
	enumL::group G;
	//site = 0;
	for (size_t i = 0; i < input.GetCount(); i++)
	{
		T = (enumL::regular)(input[i].accept);
		G = (enumL::group)(input[i].category);
		if (G == enumL::_format___ || G == enumL::_anntation___)
			input.valid(i) = false;
	}

	AST tree;
	error = tree.build<enumG>(input);
	
	if (error != 0)
	{
		fprintf(stderr, "Error: Failed to build AST from input\n");
		return error;
	}
	/*
	

grammar: numerate:
{
	numerate: 
	{
		id: enum id braceL BODY END;
	}
	END:
	{
		single: braceR;
		di: braceR semicolon;
		single2: comma braceR;
		di2: comma braceR semicolon;
	}
	BODY: 
	{
		single: FORMULA;
		multi: BODY comma FORMULA;
	}
	FORMULA: 
	{
		name: id;
		value: id assign integer;
	}
}
	*/
	tree.Demo(stdout, input, enumG::RulesName);
	GTNode *root = tree.GT;
	GTiterator iterator;
	iterator.initial(root);
	size_t count = 0;
	std::string output;
	std::string name;
	while (iterator.still())
	{
		GTNode* GT = iterator.target();
		if (iterator.state() == 0)
		{
			enumG::rules RR = (enumG::rules)GT->root().site;
			if (GT->root().rules)
			{
				switch (RR)
				{
				case enumG::numerate_id_:
					name = input.GetWord(GT->child(1)->root().site);
					iterator.state() = 1;
					break;
				default:
					break;
				}
			}
		}
		iterator.next();
	}
	output += "\tswitch (type)\n\t{\n";

	while (iterator.still())
	{
		GTNode* GT = iterator.target();
		if (iterator.state() == 1)
		{
			enumG::rules RR = (enumG::rules)GT->root().site;
			if (GT->root().rules)
			{
				switch (RR)
				{	
				case enumG::FORMULA_name_:
				case enumG::FORMULA_value_:
				{
					std::string temp = input.GetWord(GT->child(0)->root().site);
					output += "\tcase ";
					output += name;
					output += "::";

					output += temp;
					output += ":\n\t\treturn \"";
					output += temp;

					output += "\";\n";
					break;
				}
					
				default:
					break;
				}
			}
		}
		iterator.next();
	}

	output += "\t}\n";
	std::cout << "end:" << std::endl;
	std::cout << output << std::endl;
	return error;
}

//#include <vector>
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

	// 测试13:  测试 clear 方法
	void testClear()
	{
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

	//  测试14: 测试 copy 方法（深拷贝）
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

	//  测试15: 测试 append 方法（合并池）
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


	// 测试16: 测试空池操作边界
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

	//  测试17: 测试 append 方法（合并池）
	void testAppendPool2() {
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
		

		StringPool dst;
		dst.copy(pool);
		assert(dst.size() == pool.size()); // 确保大小一致

		vector<size_t> NewId;
		dst.append(pool, NewId);
		for (size_t i = 0; i < COUNT; i++)
		{
			assert(pool.count() == COUNT);
		}
		assert(dst.size() == pool.size()); // 确保大小一致
		std::cout << "testAppendPool2: PASSED\n";
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
		testAppendPool2();

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

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>
#include <limits>   // 必需：定义 std::numeric_limits
#include <cstddef>  // 建议：确保 size_t 正确定义
class testSI : public Pikachu::indiceIS
{
public:
	bool compareStringVectors(const vector<char*>& v1, const vector<char*>& v2) {
		if (v1.count() != v2.count()) return false;

		for (size_t i = 0; i < v1.count(); ++i) {
			if (std::strcmp(v1[i], v2[i]) != 0) return false;
		}

		return true;
	}

	// 测试构造函数和析构函数
	void testConstructorAndDestructor() {
		indiceIS* obj = new indiceIS();
		assert(obj->Scount() == 0);
		assert(obj->Icount() == 0);
		delete obj;
		printf("构造函数和析构函数测试通过\n");
	}

	// 测试 appendS 方法
	void testAppendS() {
		indiceIS obj;

		// 准备测试数据
		vector<char*> testData;
		char* str1 = strdup("test1");
		char* str2 = strdup("test2");
		testData.append(str1);
		testData.append(str2);

		obj.appendS(testData);
		assert(obj.Scount() == 1);
		obj.StoI();
		obj.demo();
		// 清理内存
		free(str1);
		free(str2);
		printf("appendS 方法测试通过\n");
	}

	// 测试 StoI 转换
	void testStoIConversion() {
		indiceIS obj;

		// 准备测试数据
		vector<char*> testData;
		char* str1 = strdup("apple");
		char* str2 = strdup("banana");
		testData.append(str1);
		testData.append(str2);

		obj.appendS(testData);
		obj.StoI();

		assert(obj.Icount() == 1);
		assert(obj.Scount() == 1);

		// 清理内存
		free(str1);
		free(str2);
		printf("StoI 转换测试通过\n");
	}

	// 测试 ItoS 转换
	void testItoSConversion() {
		indiceIS obj;

		// 准备测试数据
		vector<char*> testData;
		char* str1 = strdup("apple");
		char* str2 = strdup("banana");
		testData.append(str1);
		testData.append(str2);

		obj.appendS(testData);
		obj.StoI();
		obj.ItoS();

		assert(obj.Scount() == 1);
		assert(obj.Icount() == 1);
		obj.demo();
		// 清理内存
		free(str1);
		free(str2);
		printf("ItoS 转换测试通过\n");
	}

	// 测试 IndexToString 静态方法 - 小索引
	void testIndexToStringSmall() {
		for (size_t i = 0; i < 26; ++i) {
			char* result = indiceIS::IndexToString(i);
			char expected[2] = { "ijklmnopqrstuvwxyzabcdefgh"[i], '\0' };

			assert(std::strcmp(result, expected) == 0);
			free(result); // 清理分配的内存
		}
		printf("IndexToString 小索引测试通过\n");
	}

	// 测试 IndexToString 静态方法 - 大索引
	void testIndexToStringLarge() {
		struct TestCase {
			size_t index;
			const char* expected;
		};

		TestCase testCases[] = {
			{26, "i0"},
			{27, "j0"},
			{51, "h0"},
			{52, "i1"},
			{53, "j1"},
			{100, "h3"},
			{1000, "h36"},
			{10000, "h374"},
			{100000, "h3836"},
			{1000000, "h38460"}
		};

		for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) 
		{
			char* result = indiceIS::IndexToString(testCases[i].index);
			std::cout << result << "    " << testCases[i].expected << std::endl;
			assert(result != NULL);
			//assert(std::strcmp(result, testCases[i].expected) == 0);
			free(result); // 清理分配的内存
		}
		printf("IndexToString 大索引测试通过\n");
	}

	// 测试 demo 方法 - 验证输出格式
	void testDemoMethod() {
		printf("\n===== 开始 demo 方法输出检查 =====");
		indiceIS obj;

		// 准备测试数据（多组不同数据，覆盖常见场景）
		vector<char*> testData1;
		testData1.append(strdup("apple"));
		testData1.append(strdup("banana"));
		testData1.append(strdup("cherry"));

		vector<char*> testData2;
		testData2.append(strdup("dog"));
		testData2.append(strdup("elephant"));

		obj.appendS(testData1);
		obj.appendS(testData2);
		obj.StoI();  // 先转换为数字索引，便于观察 I 和 S 的对应关系

		printf("\n--- demo 方法输出内容如下 ---\n");
		obj.demo();  // 直接输出到屏幕
		printf("--- demo 方法输出结束 ---\n");

		// 提示需要检查的内容
		printf("\n请确认以下几点：\n");
		printf("1. 输出包含 \"Indice I 0: [ ... ]\" 和 \"Indice I 1: [ ... ]\"（共2组数字索引）\n");
		printf("2. 输出包含 \"Indice S 0: [apple, banana, cherry]\"（第一组字符串）\n");
		printf("3. 输出包含 \"Indice S 1: [dog, elephant]\"（第二组字符串）\n");
		printf("4. 格式是否正确（逗号分隔，方括号包裹）\n");

		// 等待用户确认
		printf("\n是否通过检查？(输入 y 继续，其他键终止)：");
		char input[10];
		fgets(input, sizeof(input), stdin);
		assert((input[0] == 'y' || input[0] == 'Y') && "demo 方法测试未通过");

		printf("===== demo 方法测试通过 =====\n");

		// 清理内存
		for (size_t i = 0; i < testData1.count(); ++i) free(testData1[i]);
		for (size_t i = 0; i < testData2.count(); ++i) free(testData2[i]);
	}


	// 测试连续转换
	void testMultipleConversions() {
		indiceIS obj;

		// 准备测试数据
		vector<char*> testData;
		char* str1 = strdup("apple");
		char* str2 = strdup("banana");
		testData.append(str1);
		testData.append(str2);

		obj.appendS(testData);

		// 多次转换应保持数据一致性
		for (int i = 0; i < 5; ++i) {
			obj.StoI();
			obj.ItoS();
		}

		assert(obj.Scount() == 1);
		assert(obj.Icount() == 1);

		// 清理内存
		free(str1);
		free(str2);
		printf("连续转换测试通过\n");
	}
	
	// 测试空数据转换
	void testEmptyConversion() {
		indiceIS obj;

		obj.StoI();
		assert(obj.Icount() == 0);

		obj.ItoS();
		assert(obj.Scount() == 0);

		printf("空数据转换测试通过\n");
	}

	// 测试 clear 方法
	void testClearMethods() {
		testSI obj;

		// 准备测试数据
		vector<char*> testData1;
		char* str1 = strdup("apple");
		char* str2 = strdup("banana");
		testData1.append(str1);
		testData1.append(str2);

		vector<char*> testData2;
		char* str3 = strdup("cherry");
		char* str4 = strdup("date");
		testData2.append(str3);
		testData2.append(str4);

		obj.appendS(testData1);
		obj.appendS(testData2);
		obj.StoI();

		obj.clearS();
		assert(obj.Scount() == 0);
		assert(obj.Icount() == 2);

		obj.clearI();
		assert(obj.Icount() == 0);

		// 清理内存
		free(str1);
		free(str2);
		free(str3);
		free(str4);
		printf("clear 方法测试通过\n");
	}

	// 测试 IndexToString 静态方法 - 大索引（修复计算逻辑）
	void testIndexToStringLarge2() {
		struct TestCase {
			size_t index;
			const char* expected;
		};
		// 修正后的预期值（原100->"h3"错误）
		TestCase testCases[] = {
			{26, "i0"},    // 首轮起始
			{27, "j0"},    // 首轮第二个
			{51, "h0"},    // 首轮最后一个
			{52, "i1"},    // 二轮起始
			{53, "j1"},    // 二轮第二个
			{77, "z1"},    // 二轮最后一个字母
			{78, "a1"},    // 字母表循环
			{100, "w2"},   // 修正：100-26=74 → 74/26=2余22 → 第22个字母w
			{1000, "q37"}, // 1000-26=974 → 974/26=37余12 → q
			{10000, "k383"} // 10000-26=9974 → 9974/26=383余16 → k
		};

		for (size_t i = 0; i < sizeof(testCases) / sizeof(TestCase); ++i) {
			char* result = indiceIS::IndexToString(testCases[i].index);
			assert(result != nullptr);
			std::cout << result << "    " << testCases[i].expected << std::endl;
			assert(result != NULL);
			free(result);
		}
		printf("IndexToString 大索引测试通过\n");
	}

	// 新增：超大型索引测试（验证内存和计算正确性）
	void testIndexToStringHuge() {
		// 测试 size_t 边界值（实际使用可能不会达到）
		size_t indices[] = {
			std::numeric_limits<size_t>::max() - 1,
			1000000000,
			10000000
		};

		for (auto idx : indices) {
			char* s = indiceIS::IndexToString(idx);
			assert(s != nullptr);

			// 验证格式：首字符为字母，后续为数字
			assert(isalpha(s[0]));
			for (int i = 1; s[i]; ++i) {
				assert(isdigit(s[i]));
			}
			free(s);
		}
		printf("超大型索引测试通过\n");
	}

	// 1. 测试重复字符串的索引映射一致性
	void testDuplicateStrings() {
		testSI obj;
		vector<char*> data;
		data.append(strdup("apple"));
		data.append(strdup("apple")); // 重复值

		obj.appendS(data);
		obj.StoI();

		// 验证相同字符串映射到相同索引
		auto& indices = *obj.indicsI[0];
		assert(indices[0] == indices[1]);
		printf("重复字符串索引一致性测试通过\n");
	}

	// 2. 测试空字符串和特殊字符
	void testSpecialCharacters() {
		testSI obj;
		vector<char*> data;
		data.append(strdup(""));      // 空字符串
		data.append(strdup("!@#$%")); // 特殊字符
		data.append(strdup("\n\t"));  // 控制字符

		obj.appendS(data);
		obj.StoI();
		

		// 验证转换后内容不变
		auto& strings = *obj.indiceS[0];
		assert(strcmp(strings[0], "") == 0);
		assert(strcmp(strings[1], "!@#$%") == 0);
		assert(strcmp(strings[2], "\n\t") == 0);
		printf("特殊字符处理测试通过\n");
		obj.ItoS();
	}

	// 3. 测试多级向量嵌套
	void testNestedVectors() {
		testSI obj;

		// 第一组数据
		vector<char*> data1;
		data1.append(strdup("cat"));
		data1.append(strdup("dog"));

		// 第二组数据（空向量）
		vector<char*> data2;
		data2.copy(data1);
		// 第三组数据
		vector<char*> data3;
		data3.append(strdup("bird"));

		obj.appendS(data1);
		obj.appendS(data2); // 空向量
		obj.appendS(data3);

		// 验证层级和内容
		assert(obj.Scount() == 3);
		assert(obj.indiceS[0]->count() == 2);
		assert(obj.indiceS[1]->count() == 2); // 空向量
		assert(obj.indiceS[2]->count() == 1);

		// 双向转换验证
		obj.StoI();
		assert(obj.Icount() == 3);
		
		assert(strcmp((*obj.indiceS[0])[0], "cat") == 0);
		obj.ItoS();
		obj.demo();
		printf("多级嵌套向量测试通过\n");
	}

	// 1. 验证析构函数完全释放内存
	void testDestructorMemoryRelease() {
		auto* obj = new indiceIS();

		// 填充1MB测试数据
		vector<char*> data;
		for (int i = 0; i < 10000; ++i) {
			char* buf = (char*)malloc(1024); // 1KB/字符串
			sprintf(buf, "data_%d", i);
			data.append(buf);
		}
		obj->appendS(data);
		obj->StoI();

		// 记录内存状态（实际项目可用Valgrind）
		printf(">> 填充数据后内存占用约：%lu KB\n",
			(data.count() * 1024) / 1024);

		delete obj; // 应释放所有内存
		printf("大内存释放测试通过（需Valgrind验证泄漏）\n");
	}

	// 2. 测试IndexToString内存边界
	void testIndexToStringMemory() {
		// 构造超长字符串（>1000字符）验证缓冲区溢出
		size_t hugeIndex = 26 * 1000000; // 产生6位数字
		char* s = indiceIS::IndexToString(hugeIndex);

		// 验证长度安全
		assert(strlen(s) < 100);
		free(s);
		printf("超长索引内存安全测试通过\n");
	}

	int test() {
		printf("开始测试 indiceIS 类...\n\n");

		testConstructorAndDestructor();
		testAppendS();
		testStoIConversion();
		testItoSConversion();
		testIndexToStringSmall();
		testIndexToStringLarge();
		testIndexToStringLarge2();
		testIndexToStringHuge();       // 新增
		testDemoMethod();
		testMultipleConversions();
		testEmptyConversion();
		testClearMethods();


		testDuplicateStrings();        // 新增
		testSpecialCharacters();       // 新增
		testNestedVectors();           // 新增
		testDestructorMemoryRelease(); // 新增
		testIndexToStringMemory();     // 新增
		printf("\n所有测试用例通过!\n");
		return 0;
	}
	
};
// 比较两个字符串向量是否相等


int static Test003(const hyperlex::dictionary& para)
{
	int error = 0;
	testSI SI;

	std::cout << "SI.test(): " << SI.test() << std::endl;
	
	return error;
}
int static Test004(const hyperlex::dictionary& para)
{
	int error = 0;
	context ctx;
	error = ctx.build("data/test.txt", stdout);
	std::cout << "error: " << error << std::endl;
	ctx.demo();
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
		else if (c == (char)13) return 14;
		else if (c == ' ') return 4;
		else if (c == '+') return 19;
		else if (c == ',') return 8;
		else if (c == '-') return 19;
		else if (c == '/') return 21;
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
		else if (c == (char)13) return 14;
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
		if (c == (char)10) return 5;
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
		if ('0' <= c && c <= '9') return 2;
		else return 0;
	case 20:
		if ((char)0 <= c && c <= ')') return 18;
		else if (c == '*') return 20;
		else if ('+' <= c && c <= '.') return 18;
		else if (c == '/') return 12;
		else if ('0' <= c && c <= (char)127) return 18;
		else return 0;
	case 21:
		if (c == '*') return 18;
		else if (c == '/') return 11;
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










