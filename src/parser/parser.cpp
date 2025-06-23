#include"../src/header/Pikachu.h"
#include"../extern/header/all.h"
#include "../header/sheet.h"
using namespace Pikachu;
static bool compare(const char* str1, const char* str2);
typedef hyperlex::Morpheme lex;
typedef hyperlex::GrammarTree AST;
typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor> GTNode;
typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor>::PostIterator GTiterator;


class CompilerObj
{
public:
	typedef long long int sint;
	CompilerObj();
	~CompilerObj();
	bool eqaul(const char* opR) const;
	void SetName(const char* NewName);
	inline const char* GetName(void) const { return name; }
protected:
	char* name;
	void ruinCO(void);
};
class ConstObj : public CompilerObj
{
public:

	ConstObj();
	~ConstObj();
	enum type
	{
		_sint_,
		_unit_,
		_bool_,
		_complex_,
		_real_,
	};
	union value
	{
		sint i;
		size_t u;
		void* t;//tensor
		bool b;
		double f;
	};
	enum status
	{
		valued,
		liberal,
	};
	void demo(FILE* fp = stdout) const;
	inline sint GetInt(size_t No = 0) const {
		return V[No].i;
	}
private:
	type T;
	bool scalar;
	vector<status> S;
	vector<value> V;
	void demo(FILE* fp, type TT, status SS, const value & VV) const;
};
class var : public CompilerObj
{
public:
	
	var();
	~var();
	
	enum authority
	{
		literal,
		read,
		write,
		owned,
	};
	
	
	void ruin(void);

	void demo(FILE* fp = stdout) const;
private:

	
};
class func : public CompilerObj
{
public:
	func();
	~func();

private:
	Expres* Exp;
	void ruin(void);
};
class NetInContext : public CompilerObj
{
public:
	NetInContext();
	~NetInContext();

private:
	NetWork* net;
	void ruin(void);
};
class context
{
public:
	context();
	~context();
	void ruin(void);
	var* search(const char* name)const;
	var* SearchLocal(const char* name)const;
	void demo(FILE* fp = stdout) const;
	void ErrorDemo(FILE* fp) const;

	int build(const char* FileName);
	void clear(void);
	enum errorType
	{
		NoError = 0,
		PretreatLEXICAL,
		PretreatGRAMMAR,
		PretreatRepeat,
		PretreatOpenfail,
		PretreatNone,
		ErrorinputLEXICAL,
		ErrorinputGrammar,
		buildUndone,
	};

private:

	hyperlex::Morpheme MorphemePre;
	hyperlex::Morpheme LexicalSource;

	errorType errorCode;
	size_t errorInfor1;
	size_t errorInfor2;
	char* errorInfor3;
	bool errorInfor4;


	vector<var*> global;
	vector<func*> funcs;
	vector<NetInContext*> nets;
	context* parent;
	vector<context*> childs;
	void initial(void);
	int pretreatment(const char* input, hyperlex::Morpheme& output);
	void NeglectNullToken(lex& eme) const;
	int buildGanalysis(const lex& eme);
	int buildAll(const lex& eme, AST& Tree);
};



CompilerObj::CompilerObj()
{
	name = NULL;
}
CompilerObj::~CompilerObj()
{
	ruinCO();
}
void CompilerObj::ruinCO(void)
{
	free(name);
	name = NULL;
}
bool CompilerObj::eqaul(const char* opR) const
{
	return compare(opR, name);
}
void CompilerObj::SetName(const char* NewName)
{
	size_t i;
	free(name);
	name = NULL;
	if (!NewName) return;

	size_t len = 0;
	while (NewName[len] != '\0') ++len;

	name = (char*)(malloc((len + 1) * sizeof(char)));
	for (i = 0; i <= len; ++i)
	{
		name[i] = NewName[i];
	}
}

ConstObj::ConstObj()
{
	T = _sint_;
	scalar = true;
}
ConstObj::~ConstObj()
{

}
void ConstObj::demo(FILE* fp) const
{
	const char* type_ = "null";
	switch (T)
	{
	case ConstObj::_sint_:
		type_ = "sint";
		break;
	case ConstObj::_unit_:
		type_ = "unit";
		break;
	case ConstObj::_bool_:
		type_ = "bool";
		break;
	case ConstObj::_complex_:
		type_ = "complex";
		break;
	case ConstObj::_real_:
		type_ = "real";
		break;
	default:
		break;
	}
	if (scalar)
	{
		fprintf(fp, "%s %s = ", type_, name);
		demo(fp, T, S[0], V[0]);
	}
	else
	{
		fprintf(fp, "%s[%zu] %s = [", type_, V.count(), name);
		if (V.count()) demo(fp, T, S[0], V[0]);
		for (size_t i = 1; i < V.count(); i++)
		{
			fprintf(fp, ", ");
			demo(fp, T, S[i], V[i]);
		}
		fprintf(fp, "]");
	}

}
void ConstObj::demo(FILE* fp, type TT, status SS, const value& VV) const
{
	if (SS == status::liberal)
		fprintf(fp, "???");
	else
	{
		switch (TT)
		{
		case ConstObj::_sint_:
			fprintf(fp, "%lld", (long long)VV.i);
			break;
		case ConstObj::_unit_:
			fprintf(fp, "%zu", VV.u);
			break;
		case ConstObj::_bool_:
			if (VV.b)
				fprintf(fp, "true");
			else
				fprintf(fp, "false");
			break;
		case ConstObj::_complex_:
			fprintf(fp, "%lf", VV.f);
			break;
		case ConstObj::_real_:
			fprintf(fp, "%lf", VV.f);
			break;
		default:
			break;
		}
	}


}


var::var()
{
	SetName("implicit");
}
var::~var()
{
	ruin();
}
void var::ruin(void)
{
	ruinCO();
}
void var::demo(FILE* fp) const
{
	
}


func::func()
{
	Exp = NULL;
}
func::~func()
{
	ruin();
}
void func::ruin(void)
{
	delete Exp;
}


NetInContext::NetInContext()
{
	net = NULL;
}
NetInContext::~NetInContext()
{
	ruin();
}
void NetInContext::ruin(void)
{
	delete net;
}



context::context()
{
	errorInfor3 = NULL;
}
context::~context()
{
	ruin();
}
void context::ruin(void)
{
	for (size_t i = 0; i < global.count(); i++)
	{
		delete global[i];
	}
	global.clear();
	childs.clear();

	free(errorInfor3);
	errorInfor3 = NULL;
}
void context::demo(FILE* fp) const
{

}
void context::ErrorDemo(FILE* fp) const
{
	switch (errorCode)
	{
	case context::NoError:
		fprintf(fp, "No Error!\n");
		break;
	case context::ErrorinputLEXICAL:
	{
		fprintf(fp, "ErrorinputLEXICAL: \n");
		size_t record = 0;
		for (size_t i = 0; i < LexicalSource.GetCount(); i++)
		{
			if (LexicalSource[i].accept < 0)
			{
				record = LexicalSource[i].line;
				break;
			}
		}
		fprintf(fp, "line[%zu]: ", record + 1);
		for (size_t i = 0; i < LexicalSource.GetCount(); i++)
		{
			size_t  uintTemp = LexicalSource[i].line;
			if (record == uintTemp)
			{
				fprintf(fp, "%s", LexicalSource.GetWord(i));
			}
		}
		break;
	}
	case context::PretreatLEXICAL:
	{
		fprintf(fp, "PretreatLEXICAL: Error happenned during pretreatment.\n");
		fprintf(fp, "Lexical analysis line: %zu of No.%zu ", errorInfor2, errorInfor1);
		fprintf(fp, "source file %s made a mistake\n", MorphemePre.GetFile(errorInfor1));
		break;
	}
	case context::PretreatGRAMMAR:
	{
		fprintf(fp, "PretreatGRAMMAR: Error happenned during pretreatment.\n");
		fprintf(fp, "Grammar analysis of No.%zu ", errorInfor1);
		fprintf(fp, "source file %s made a mistake ", MorphemePre.GetFile(errorInfor1));

		size_t RLine = MorphemePre[errorInfor2].line;
		size_t RFile = MorphemePre[errorInfor2].file;

		fprintf(fp, "in line %zu, file: %zu, unit: %zu\n", RLine, RFile, errorInfor2);

		//fprintf(fp, "%zu\n", record);
		for (size_t i = 0; i < MorphemePre.GetCount(); i++)
		{
			size_t uintTemp1 = MorphemePre[i].line;
			size_t uintTemp2 = MorphemePre[i].file;
			if ((RLine == uintTemp1 || uintTemp1 + 1 == RLine) && uintTemp2 == RFile)
			{
				if (i == errorInfor1)
					fprintf(fp, "| %s |", MorphemePre.GetWord(i));
				else
					fprintf(fp, "%s", MorphemePre.GetWord(i));
			}
		}
		break;
	}
	case context::PretreatRepeat:
	{
		fprintf(fp, "PretreatRepeat: Error happenned during pretreatment.\n");
		fprintf(fp, "No.%zu ", errorInfor1);
		fprintf(fp, "source file %s repeats with existed ", MorphemePre.GetFile(errorInfor1));
		fprintf(fp, "%zu file %s\n", errorInfor2, MorphemePre.GetFile(errorInfor2));
		break;
	}
	case context::PretreatOpenfail:
	{
		fprintf(fp, "PretreatOpenfail: Error happenned during pretreatment.\n");
		fprintf(fp, "Open of No.%zu ", errorInfor1);
		fprintf(fp, "source file %s made a mistake\n", MorphemePre.GetFile(errorInfor1));
		break;
	}
	case context::PretreatNone:
	{
		fprintf(fp, "PretreatNone: Error happenned during pretreatment.\n");
		fprintf(fp, "%s is not a standard lib\n", errorInfor3);
		size_t RLine = MorphemePre[errorInfor1].line;
		size_t RFile = MorphemePre[errorInfor1].file;

		fprintf(fp, "in line %zu, file: %zu, unit: %zu\n", RLine, RFile, errorInfor1);

		//fprintf(fp, "%zu\n", record);
		for (size_t i = 0; i < MorphemePre.GetCount(); i++)
		{
			size_t uintTemp1 = MorphemePre[i].line;
			size_t uintTemp2 = MorphemePre[i].file;
			if ((RLine == uintTemp1 || uintTemp1 + 1 == RLine) && uintTemp2 == RFile)
			{
				if (i == errorInfor1)
					fprintf(fp, "| %s |", MorphemePre.GetWord(i));
				else
					fprintf(fp, "%s", MorphemePre.GetWord(i));
			}
		}
		break;
		break;
	}
	case context::ErrorinputGrammar:
	{
		fprintf(fp, "ErrorinputGrammar: Something was wrong when parsing of line:");
		size_t RLine = LexicalSource[errorInfor1].line;
		size_t RFile = LexicalSource[errorInfor1].file;
		fprintf(fp, "%zu", RLine);
		fprintf(fp, " of No.%zu file %s\n", RFile, LexicalSource.GetFile(RFile));
		for (size_t i = 0; i < LexicalSource.GetCount(); i++)
		{
			size_t uintTemp1 = LexicalSource[i].line;
			size_t uintTemp2 = LexicalSource[i].file;
			if ((RLine == uintTemp1 || uintTemp1 + 1 == RLine) && uintTemp2 == RFile)
			{
				if (i == errorInfor1)
					fprintf(fp, "| %s |", LexicalSource.GetWord(i));
				else
					fprintf(fp, "%s", LexicalSource.GetWord(i));
			}
		}
		break;
	}
	case context::buildUndone:
	{
		fprintf(fp, "buildUndone: has not been built.\n");
		fprintf(fp, "\n");
		break;
	}
	default:
	{
		fprintf(fp, "Error Unknown: \n");
		break;
	}
	}

}



var* context::search(const char* name)const
{
	var* value = SearchLocal(name);
	if (value != NULL) return value;
	context* now = parent;
	while (now != NULL)
	{
		var* temp = now->SearchLocal(name);
		if (temp != NULL) return temp;
		now = parent->parent;
	}
	return NULL;
}
var* context::SearchLocal(const char* name)const
{
	for (size_t i = 0; i < global.count(); i++)
	{
		if (global[i]->eqaul(name)) return global[i];
	}
	return NULL;
}

size_t static pretreat_begin(GTNode* GT)
{
	return GT->child(0)->root().site;
}
size_t static pretreat_count(GTNode* GT)
{
	size_t infor = GT->root().site;
	if (infor == (size_t)NetPreG::MACRO_single_)
		return 2;
	return 3;
}

int context::pretreatment(const char* input, hyperlex::Morpheme& output)
{
	FILE* fp = fopen(input, "r");
	if (fp == NULL)
	{
		errorCode = PretreatOpenfail;
		return 445624;
	}
	int error = output.Build<NetPreL>(fp);
	output.append(input);
	if (error != 0)
	{
		errorInfor1 = output.FileCount();
		errorCode = PretreatLEXICAL;
		return error;
	}
	bool include;
	bool customized;
	do
	{
		customized = false;
		include = false;
		size_t begin = 0;
		size_t count = 0;
		size_t file = 0;
		size_t site = 0;
		char* name = NULL;
		hyperlex::GrammarTree Tree;
		error = Tree.build<NetPreG>(output);
		if (error != 0)
		{
			errorInfor1 = output.FileCount() - 1;
			errorInfor2 = Tree.error_record01;
			//std::cout << "Tree.error_record01: " << Tree.error_record01 << std::endl;
			//std::cout << "Tree.error_record02: " << Tree.error_record02 << std::endl;
			errorCode = PretreatGRAMMAR;
			return error;
		}
		GTiterator iterator;
		iterator.initial(Tree.GT);
		while (iterator.still())
		{
			GTNode* GT = iterator.target();
			if (iterator.state() == 0)
			{
				size_t infor = GT->root().site;

				if (GT->root().rules)
				{
					if (infor == (size_t)NetPreG::INCLUDE_include2_)
					{//include2: MACRO header;
						site = GT->child(1)->root().site;
						include = true;
						begin = pretreat_begin(GT->child(0));
						count = pretreat_count(GT->child(0));
						name = output.GetHeader(site);
						file = output[site].file;
						for (size_t i = 0; i < count; i++)
						{
							output.valid(begin + i) = false;
						}
						break;
					}
					else if (infor == (size_t)NetPreG::INCLUDE_include_)
					{
						site = GT->child(1)->root().site;
						include = true;
						customized = true;
						begin = pretreat_begin(GT->child(0));
						count = pretreat_count(GT->child(0));
						//std::cout << "2begin: " << begin << std::endl;
						name = output.GetString(site);
						//std::cout << "2name: " << name << std::endl;
						file = output[site].file;
						break;
					}
				}
			}
			iterator.next();
		}
		if (customized)
		{
			hyperlex::Morpheme eme;
			hyperlex::FilePath left, here;
			here.build(name);
			//std::cout << "file: " << file << std::endl;
			//std::cout << "output.GetFile(file): " << output.GetFile(file) << std::endl;
			left.build(output.GetFile(file));
			//here.demo();
			//left.demo();
			//std::cout << "begin: " << begin << std::endl;
			//std::cout << "name: " << name << std::endl;
			//std::cout << "count: " << count << std::endl;
			left.RearCutAppend(here);

			//left.demo();
			//std::cout << "=============" << std::endl;
			char* newFile = left.print();
			FILE* fp2 = fopen(newFile, "r");
			output.append(newFile);
			free(newFile);
			if (fp2 == NULL)
			{
				errorCode = PretreatOpenfail;
				return 445625;
			}
			int error = eme.Build<NetPreL>(fp2);
			fclose(fp2);
			if (error != 0)
			{
				errorInfor1 = output.FileCount() - 1;
				errorInfor2 = eme[eme.GetCount() - 2].line;
				errorCode = PretreatLEXICAL;
				return error;
			}
			eme.SetFile(output.FileCount() - 1);

			for (size_t i = 0; i + 1 < output.FileCount(); i++)
			{
				hyperlex::FilePath right;
				right.build(output.GetFile(i));
				if (left == right)
				{
					errorInfor1 = output.FileCount() - 1;
					errorInfor2 = i;
					errorCode = PretreatRepeat;
					return 12345678;
				}
			}
			//eme.Demo(stdout);
			//output.Demo(stdout);
			output.insert(begin, count, eme);
			//std::cout << "=============" << std::endl;
			//output.Demo(stdout);
		}
		else if (include)
		{
			if (compare(name, "activ.h"))
			{

			}
			else
			{
				errorCode = PretreatNone;
				errorInfor1 = site;
				errorInfor3 = name;
				name = NULL;
				return 2345345;
			}
			
		}
		free(name);
		name = NULL;
	} while (include);

	return error;
}
int context::build(const char* FileName)
{
	int error;

	clear();
	initial();
	error = pretreatment(FileName, MorphemePre);
	if (error != 0) return error;

	error = LexicalSource.Build<NetL>(MorphemePre);
	if (error != 0)
	{
		errorCode = ErrorinputLEXICAL;
		return error;
	}
	NeglectNullToken(LexicalSource);
	//eme.Demo(stdout);
	error = buildGanalysis(LexicalSource);
	if (error != 0)
	{
		errorCode = ErrorinputGrammar;
		return error;
	}
	errorCode = NoError;
	return error;
}
void context::clear(void)
{
	MorphemePre.clear();
	LexicalSource.clear();

	errorCode = NoError;
	errorInfor1 = 0;
	errorInfor2 = 0;
	errorInfor3 = NULL;
	errorInfor4 = true;
}
void context::initial(void)
{
	errorCode = buildUndone;
	errorInfor1 = 0;
	errorInfor2 = 0;
	errorInfor3 = NULL;
	errorInfor4 = true;
}

void context::NeglectNullToken(lex& eme) const
{
	NetL::regular T;
	NetL::group G;
	//site = 0;
	for (size_t i = 0; i < eme.GetCount(); i++)
	{
		T = (NetL::regular)(eme[i].accept);
		G = (NetL::group)(eme[i].category);
		if (G == NetL::_format___ || G == NetL::_anntation___)
			eme.valid(i) = false;
	}
	//eme.CountReset(site);
	//vector<bool> line;
	//line.recount(256);
	//line.value(false);
	//line[(size_t)(Reg::_enters_)] = true;
	//line[(size_t)(Reg::_anntationS_)] = true;
	//eme.SetLine(line.ptr());
	return;
}
int context::buildGanalysis(const lex& eme)
{
	int error;
	AST Tree;
	error = Tree.build<NetG>(eme);
	if (error != 0)
	{
		errorCode = ErrorinputGrammar;
		errorInfor1 = Tree.error_record01;
		errorInfor2 = Tree.error_record02;
		return error;
	}
	//printf("Here?!\n");
	//Tree.Demo(stdout, eme, Panel::RulesName);
	//printf("Here?!\n");
	error = buildAll(eme, Tree);
	//printf("Here?!:%d\n", error);
	//if (error != 0) return error;
	//buildLpost();
	//printf("Here?!:%d\n", error);
	return error;
}

int context::buildAll(const lex& eme, AST& Tree)
{
	GTNode* GT = NULL;
	GTiterator iterator;
	int error = 0;
	iterator.initial(Tree.GT);
	while (iterator.still())
	{
		GT = iterator.target();
		if (iterator.state() == 0)
		{
			NetG::rules RR = (NetG::rules)GT->root().site;
			if (GT->root().rules)
			{
				switch (RR)
				{
				case Pikachu::NetG::all_all_:
					break;
				case Pikachu::NetG::context_defs_:
					break;
				case Pikachu::NetG::DEF_symbolic_:
					break;
				case Pikachu::NetG::DEF_network_:
					break;
				case Pikachu::NetG::DEF_def_:
					break;
				case Pikachu::NetG::DEF_diff_:
					break;
				case Pikachu::NetG::OPERATOR_operatmd_:
					break;
				case Pikachu::NetG::OPERATOR_operatas_:
					break;
				case Pikachu::NetG::DIFF_NET_diff_:
					break;
				case Pikachu::NetG::EXP_RIGHT_add_:
					break;
				case Pikachu::NetG::EXP_MUL_multi_:
					break;
				case Pikachu::NetG::EXP_MINUS_plus_:
					break;
				case Pikachu::NetG::UNIT_id_:
					break;
				case Pikachu::NetG::UNIT_call_:
					break;
				case Pikachu::NetG::UNIT_const_:
					break;
				case Pikachu::NetG::UNIT_complex_:
					break;
				case Pikachu::NetG::ID_array_:
					break;
				case Pikachu::NetG::ID_single_:
					break;
				case Pikachu::NetG::INDEX_COMPUTE_single_:
					break;
				case Pikachu::NetG::CALL_call_1_:
					break;
				case Pikachu::NetG::CALL_call_2_:
					break;
				case Pikachu::NetG::SYMBOLIC_SYMBOLIC_:
					break;
				case Pikachu::NetG::PARA_PARA_:
					break;
				case Pikachu::NetG::SYMBOLICPARA_input_:
					break;
				case Pikachu::NetG::SYMBOLICPARA_para_:
					break;
				case Pikachu::NetG::SYMBOLICPARA_output_:
					break;
				case Pikachu::NetG::SYMBOLICBODY_SYMBOLICBODY_:
					break;
				case Pikachu::NetG::STATEMENT_def_:
					break;
				case Pikachu::NetG::STATEMENT_exp_:
					break;
				case Pikachu::NetG::EXPRESSION_EXPRESSION_:
					break;
				case Pikachu::NetG::VAR_def1_:
					break;
				case Pikachu::NetG::VAR_def2_:
					break;
				case Pikachu::NetG::DEF_VAR_const_:
					break;
				case Pikachu::NetG::DEF_VAR_var_:
					break;
				case Pikachu::NetG::VALUE_single_:
					break;
				case Pikachu::NetG::VALUE_multi_:
					break;
				case Pikachu::NetG::VALUELIST_VALUELIST_:
					break;
				case Pikachu::NetG::VALUES_VALUES_:
					break;
				case Pikachu::NetG::NEXTVALUE_NEXTVALUE_:
					break;
				case Pikachu::NetG::NETWORK_NETWORK_:
					break;
				case Pikachu::NetG::NETBODY_net_:
					break;
				case Pikachu::NetG::NET_STATEMENT_const_:
					break;
				case Pikachu::NetG::NET_STATEMENT_exp_:
					break;
				case Pikachu::NetG::NET_STATEMENT_def_:
					break;
				case Pikachu::NetG::NET_STATEMENT_def2_:
					break;
				case Pikachu::NetG::NET_STATEMENT_tensorDef1_:
					break;
				case Pikachu::NetG::NET_STATEMENT_tensorDef2_:
					break;
				case Pikachu::NetG::CONSTVAR_def1_:
					break;
				case Pikachu::NetG::CONSTVAR_def2_:
					break;
				case Pikachu::NetG::TENSORID_TENSORID_:
					break;
				case Pikachu::NetG::TENSOR_TENSOR_:
					break;
				case Pikachu::NetG::INDEXLIST_INDEXLIST_:
					break;
				case Pikachu::NetG::INDEXUNITS_single_:
					break;
				case Pikachu::NetG::INDEXUNITS_multi_:
					break;
				case Pikachu::NetG::ID2_yes_:
					break;
				case Pikachu::NetG::ID2_no_:
					break;
				case Pikachu::NetG::TENSORVALUE_single_:
					break;
				case Pikachu::NetG::TENSORVALUE_multi_:
					break;
				case Pikachu::NetG::TENSORVALUE_singleF_:
					break;
				case Pikachu::NetG::TENSORVALUE_multiF_:
					break;
				case Pikachu::NetG::SUMSYMBOL_single_:
					break;
				case Pikachu::NetG::SUMSYMBOL_multi_:
					break;
				case Pikachu::NetG::SQ_INDEXUNITS_single_:
					break;
				default:
					break;
				}
			}
		}
		iterator.next();
	}
	return error;
}




static bool compare(const char* str1, const char* str2)
{
	size_t i;
	for (i = 0; (str1[i] != '\0') && (str1[i] == str2[i]); i++);
	return str1[i] == str2[i];
}






