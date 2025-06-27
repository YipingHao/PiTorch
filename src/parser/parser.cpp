#include"../src/header/Pikachu.h"
#include"../extern/header/all.h"
#include "../header/parser.h"
#include "../header/sheet.h"
using namespace Pikachu;
static bool compare(const char* str1, const char* str2);

inline bool var::compareAttri(const char* srcR)const
{
	return compare(srcR, attribute);
}

BuildInfor::BuildInfor()
{
	initial();
}
BuildInfor::~BuildInfor()
{
	clear();
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
int BuildInfor::pretreatment(const char* input, lex& output)
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
int BuildInfor::build(const char* FileName, context* dst)
{
	int error;

	dst->clear();
	dst->initial();

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
	error = buildGanalysis(LexicalSource, dst);
	if (error != 0)
	{
		errorCode = ErrorinputGrammar;
		return error;
	}
	errorCode = NoError;
	return error;
}
void BuildInfor::clear(void)
{
	MorphemePre.clear();
	LexicalSource.clear();

	errorCode = NoError;
	errorInfor1 = 0;
	errorInfor2 = 0;

	free(errorInfor3);

	errorInfor3 = NULL;
	errorInfor4 = true;

	delete ASTree;
	ASTree = NULL;
	ErrorNode = NULL;
}
void BuildInfor::initial(void)
{
	errorCode = buildUndone;
	errorInfor1 = 0;
	errorInfor2 = 0;
	errorInfor3 = NULL;
	errorInfor4 = true;
	ASTree = NULL;
	ErrorNode = NULL;
}

void BuildInfor::NeglectNullToken(lex& eme) const
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
	return;
}
int BuildInfor::buildGanalysis(const lex& eme, context* dst)
{
	int error;
	ASTree = new AST;
	error = ASTree->build<NetG>(eme);
	if (error != 0)
	{
		errorCode = ErrorinputGrammar;
		errorInfor1 = ASTree->error_record01;
		errorInfor2 = ASTree->error_record02;
		return error;
	}
	//printf("Here?!\n");
	//Tree.Demo(stdout, eme, Panel::RulesName);
	//printf("Here?!\n");
	error = buildAll(eme, *ASTree, dst);
	//printf("Here?!:%d\n", error);
	//if (error != 0) return error;
	//buildLpost();
	//printf("Here?!:%d\n", error);
	return error;
}

int BuildInfor::buildAll(const lex& eme, AST& Tree, context* dst)
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
				case Pikachu::NetG::DEF_symbolic_:
				{
					GTNode* SYMBOLIC = GT->child(0);
					iterator.state() = 1;
					error = buildSymbolic(eme, SYMBOLIC, dst);
					break;
				}
				case Pikachu::NetG::DEF_network_:
				{
					GTNode* GTarget = GT->child(0);
					iterator.state() = 1;
					error = buildNet(eme, GTarget, dst);
					break;
				}
				case Pikachu::NetG::DEF_def_:
				{
					GTNode* GTarget = GT->child(0);
					iterator.state() = 1;
					error = buildConstObj(eme, GTarget, dst);
					break;
				}
				case Pikachu::NetG::DEF_exp_:
				{
					GTNode* GTarget = GT;
					iterator.state() = 1;
					error = buildExp(eme, GTarget, dst);
					break;
				}
				case Pikachu::NetG::DEF_diff_:
				{
					GTNode* GTarget = GT->child(0);
					iterator.state() = 1;
					error = buildDiff(eme, GTarget, dst);
					break;
				}
				default:
					break;
				}
				if (error != 0) return error;
			}
		}
		iterator.next();
	}
	return error;
}

static const char* getIDname(const lex& eme, GTNode* ID)
{
	GTNode* Def = ID->child(0);
	if (Def->root().rules) return NULL;
	else return eme.GetWord(Def->root().site);
}
static bool getIDscalar(const lex& eme, GTNode* ID)
{
	NetG::rules RR = (NetG::rules)ID->root().site;
	return (RR == NetG::rules::ID_single_);
}

static ConstObj::type getType(const char* input)
{

	if (input == NULL) return ConstObj::type::_sint_;
	if (compare(input, "sint")) return ConstObj::type::_sint_;
	else if (compare(input, "unit")) return ConstObj::type::_unit_;
	else if (compare(input, "bool")) return ConstObj::type::_bool_;
	else if (compare(input, "complex")) return ConstObj::type::_complex_;
	else if (compare(input, "real")) return ConstObj::type::_real_;
	else return ConstObj::type::_unit_;
}
static ConstObj::type getType(const lex& eme, GTNode* GTarget)
{
	const char* input = eme.GetWord(GTarget->root().site);
	return getType(input);
}
int BuildInfor::GetIDdim(size_t& dim, const lex& eme, GTNode* ID, context* dst)
{
	size_t line = ID->child(0)->root().site;
	bool Scalar_ = getIDscalar(eme, ID);
	dim = 0;
	if (!Scalar_)
	{
		ConstObj* Const_;
		int error = GetAConst(Const_, eme, ID->child(1)->child(1), dst);
		if (error != 0) return error;
		if (!Const_->SorUint())
		{
			errorInfor1 = line;
			errorCode = ErrorNeedAInt;
			return 1234234;
		}
		dim = Const_->GetSint();
		if (dim < 0)
		{
			errorInfor1 = line;
			errorInfor2 = dim;
			errorCode = ErrorIndexOutofRange;
			return 1234267;
		}
	}
	else dim = 1;
}

int BuildInfor::SetAConstObj(const lex& eme, GTNode* GTarget, ConstObj::type Type, context* dst)
{
	int error = 0;
	const char* name = NULL;
	name = getIDname(eme, GTarget);
	size_t line = GTarget->child(0)->root().site;
	if (name == NULL)
	{
		errorCode = ErrorNameNULL;
		errorInfor1 = line;
		return 123234;
	}
	ConstObj* obj = dst->searchConst(name);
	if (obj != NULL)
	{
		errorCode = ErrorRepeatVarDef;
		errorInfor1 = line;
		return 423432234;
	}
	NetG::rules RR = (NetG::rules)GTarget->root().site;
	//Pikachu::NetG::ID_array_;
	//Pikachu::NetG::ID_single_;
	bool Scalar_ = false;
	if (RR == Pikachu::NetG::ID_single_) Scalar_ = true;
	else Scalar_ = false;
	size_t dim = 0;
	error = GetIDdim(dim, eme, GTarget, dst);
	if (error != 0) return error;
	obj = new ConstObj(dim, Scalar_, Type, name);
	dst->Cobj.append(obj);
	return error;
}
int BuildInfor::GetAConst(ConstObj*& output, const lex& eme, GTNode* GTarget, context* dst) 
{
	GTiterator iterator;
	int error = 0;
	output = NULL;
	iterator.initial(GTarget);

	NetG::nonterminal RRR = (NetG::nonterminal)NetG::RulesToSymbol[GTarget->root().site];
	if (RRR != NetG::nonterminal::_EXP_RIGHT_)
	{
		errorInfor1 = GTarget->root().site;
		errorCode = WrongEntrance;
		return 12321;
	}
	while (iterator.still())
	{
		GTNode* GT = iterator.target();
		if (iterator.state() == 1)
		{
			NetG::rules RR = (NetG::rules)GT->root().site;
			switch (RR)
			{
			case Pikachu::NetG::EXP_RIGHT_add_:
			case Pikachu::NetG::EXP_MUL_multi_:
			{
				GTNode* Left = GT->child(0);
				GTNode* Right = GT->child(2);
				ConstObj* left = (ConstObj*)(Left->root().infor);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				if (!left->ValuedScalarSint() && !right->ValuedScalarSint())
				{
					errorCode = ErrorNotAConst;
					error = 2712312;
				}

				GTNode* op = GT->child(1);
				const char* OP = eme.GetWord(op->root().site);
				ConstObj* Lvalue = new ConstObj(left, OP, right);
				GT->root().infor = (void*)Lvalue;
				break;
			}
			case Pikachu::NetG::EXP_MINUS_plus_:
			{
				GTNode* Right = GT->child(1);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				if (!right->ValuedScalarSint())
				{
					errorCode = ErrorNotAConst;
					error = 2712312;
				}
				GTNode* op = GT->child(0);
				const char* OP = eme.GetWord(op->root().site);
				ConstObj* Lvalue = new ConstObj(OP, right);
				GT->root().infor = (void*)Lvalue;

				break;
			}
			case Pikachu::NetG::CALL_call_1_:
			case Pikachu::NetG::CALL_call_2_:
			case Pikachu::NetG::UNIT_call_:
			{
				errorCode = ErrorUnsupportFunc;
				error = 23423423;
				break;
			}
			case Pikachu::NetG::UNIT_const_:
			{
				GTNode* num = GT->child(0);
				size_t token = num->root().site;
				int accept = eme[token].accept;
				if (accept == (int)NetL::regular::_integer_)
				{
					sint temp = (sint)eme.GetInt(token);
					ConstObj* Lvalue = new ConstObj(temp, ConstObj::_sint_);
					GT->root().infor = (void*)Lvalue;
				}
				else //if (accept == (int)NetL::regular::_realC_)
				{
					double temp = eme.GetReal(token);
					ConstObj* Lvalue = new ConstObj(temp);
					GT->root().infor = (void*)Lvalue;
				}
				break;
			}
			case Pikachu::NetG::ID_array_:
			{
				GTNode* ID = GT->child(0);
				GTNode* index = GT->child(1);
				size_t target = ID->root().site;
				const char* id = eme.GetWord(target);
				ConstObj* Rvalue = dst->searchConst(id);
				ConstObj* Index = (ConstObj*)(index->root().infor);
				if (Rvalue == NULL || Index == NULL)
				{
					errorInfor1 = target;
					errorCode = ErrorMissingVarDef;
					error = 5663456;
				}
				if (!Index->SorUint())
				{
					errorInfor1 = target;
					errorCode = ErrorNeedAInt;
					error = 56336;
				}
				sint No = Index->GetSint();
				if (No < 0 || (size_t)No >= Index->GetDim())
				{
					errorInfor1 = target;
					errorInfor2 = No;
					errorCode = ErrorIndexOutofRange;
					error = 564584566;
				}
				ConstObj* Lvalue = new ConstObj();
				Lvalue->copy(Rvalue, No);
				GT->root().infor = (void*)Lvalue;
				break;
			}
			case Pikachu::NetG::ID_single_:
			{
				GTNode* ID = GT->child(0);
				size_t target = ID->root().site;
				const char* id = eme.GetWord(target);
				ConstObj* Rvalue = dst->searchConst(id);
				if (Rvalue == NULL)
				{
					errorInfor1 = target;
					errorCode = ErrorMissingVarDef;
					error = 5667556;
				}
				ConstObj* Lvalue = new ConstObj();
				Lvalue->copy(Rvalue);
				GT->root().infor = (void*)Lvalue;
				break;
			}
			case Pikachu::NetG::rules::EXP_MINUS_default_:
			case Pikachu::NetG::rules::EXP_MUL_default_:
			case Pikachu::NetG::rules::EXP_RIGHT_default_:
			case Pikachu::NetG::UNIT_id_:
			{
				GTNode* Right = GT->child(0);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				Right->root().infor = NULL;
				GT->root().infor = (void*)right;
				if (!right->ValuedScalarSint())
				{
					errorCode = ErrorNotAConst;
					error = 2712312;
				}
				break;
			}
			case Pikachu::NetG::UNIT_complex_:
			case Pikachu::NetG::INDEX_COMPUTE_single_:
			{
				GTNode* Right = GT->child(1);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				Right->root().infor = NULL;
				GT->root().infor = (void*)right;
				if (!right->ValuedScalarSint())
				{
					errorCode = ErrorNotAConst;
					error = 2712312;
				}
				break;
			}

			}
		}
		if (error != 0) break;
		ConstObj* Lvalue = (ConstObj*)(GT->root().infor);
		if (Lvalue != NULL)
		{
			if (Lvalue->GetState() != ConstObj::status::valued)
			{
				error = 1221312;
				errorCode = ErrorUnKnowEXP;
			}
		}
		if (error != 0) break;
		iterator.next();
	}
	ConstObj* target = (ConstObj*)(GTarget->root().infor);
	output = target;
	GTarget->root().infor = NULL;
	iterator.initial(GTarget);
	while (iterator.still())
	{
		GTNode* GT = iterator.target();
		if (iterator.state() == 1)
		{
			if (GT->root().rules)
			{
				ConstObj* target = (ConstObj*)(GT->root().infor);
				GT->root().infor = NULL;
				delete target;
			}
		}
		iterator.next();
	}
	return error;
}
size_t BuildInfor::getValueDim(GTNode* VALUE)
{
	if ((Pikachu::NetG::rules)VALUE->root().site == Pikachu::NetG::VALUE_single_)
		return 1;
	GTNode* VALUELIST = VALUE->child(1);//multi: squareL VALUELIST squareR;
	GTNode* VALUES = VALUELIST->child(1);// VALUELIST: EXP_RIGHT VALUES;
	return VALUES->ChildCount() + 1;
}


int BuildInfor::buildConstObj(const lex& eme, GTNode* GTarget, context * dst)
{
	int error = 0;
	GTNode* GT = GTarget;
	NetG::rules RR = (NetG::rules)GTarget->root().site;
	ConstObj* obj = NULL;
	size_t line = GT->child(0)->root().site;
	if (GT->root().rules)
	{
		if (RR == Pikachu::NetG::CONSTVAR_def1_ || RR == Pikachu::NetG::CONSTVAR_def2_)
		{
			ConstObj::type TT = getType(eme, GT->child(0));
			if (TT != ConstObj::type::_sint_ && TT != ConstObj::type::_real_)
			{
				errorCode = ErrorUnsupportType;
				errorInfor1 = line;
				return 423434;
			}
			error = SetAConstObj(eme, GT->child(1), TT, dst);
			if (error != 0) return error;
			obj = dst->Cobj[dst->Cobj.count() - 1];
		}
		else
		{
			errorInfor1 = GTarget->root().site;
			errorCode = WrongEntrance;
			return 123897821;
		}
	}
	else
	{
		errorInfor1 = GTarget->root().site;
		errorCode = WrongEntrance;
		return 123897822;
	}
	if (RR == Pikachu::NetG::CONSTVAR_def1_) return error;

	GTNode* VALUE = GTarget->child(3);
	bool valueScalar = ((Pikachu::NetG::rules)VALUE->root().site == Pikachu::NetG::VALUE_single_);
	size_t dim = getValueDim(VALUE);
	if (valueScalar != obj->GetScalar() || dim != obj->GetDim())
	{
		errorCode = ErrorInitialAorS;
		errorInfor1 = line;
		errorInfor2 = dim;
		errorInfor4 = obj->GetScalar();
		return 48975644;
	}
	if (valueScalar)
	{
		GTNode* EXP_RIGHT = VALUE->child(0);//single: EXP_RIGHT;
		ConstObj* srcR = NULL;
		int error = GetAConst(srcR, eme, EXP_RIGHT, dst);
		if (error != 0) return error;
		if (obj->GetType() != srcR->GetType())
		{
			errorCode = ErrorAssignType;
			return 4897895;
		}
		obj->assign(srcR);
		delete srcR;
	}
	else
	{
		GTNode* VALUELIST = VALUE->child(1);//multi: squareL VALUELIST squareR;
		GTNode* VALUES = VALUELIST->child(1);// VALUELIST: EXP_RIGHT VALUES;
		GTNode* EXP_RIGHT = VALUELIST->child(0);
		ConstObj* srcR = NULL;
		int error = GetAConst(srcR, eme, EXP_RIGHT, dst);
		if (error != 0) return error;
		if (obj->GetType() != srcR->GetType())
		{
			errorCode = ErrorAssignType;
			return 4897896;
		}
		obj->assign(srcR, 0);
		delete srcR;
		for (size_t i = 1; i < dim; i++)
		{
			GTNode* NEXTVALUE = VALUES->child(i - 1);
			EXP_RIGHT = NEXTVALUE->child(1);
			ConstObj* srcR = NULL;
			int error = GetAConst(srcR, eme, EXP_RIGHT, dst);
			if (error != 0) return error;
			if (obj->GetType() != srcR->GetType())
			{
				errorCode = ErrorAssignType;
				return 4897897;
			}
			obj->assign(srcR, i);
			delete srcR;
		}
	}
	return error;
}
int BuildInfor::buildExp(const lex& eme, GTNode* GTarget, context * dst)
{
	int error = 0;
	
	NetG::rules RR = (NetG::rules)GTarget->root().site;
	ConstObj* obj = NULL;
	size_t line = GTarget->child(0)->root().site;

	//if (RR != NetG::rules::DEF_exp_)
	//{
	//	errorInfor1 = GTarget->root().site;
	//	errorCode = WrongEntrance;
	//	return 7985871;
	//}
	GTNode* ID = GTarget->child(0);//exp: ID assign EXP_RIGHT semicolon;
	const char* name = getIDname(eme, ID);
	if (name == NULL)
	{
		errorCode = ErrorNameNULL;
		errorInfor1 = line;
		return 123235;
	}
	ConstObj* obj = dst->SearchConstLocal(name);
	if (obj == NULL)
	{
		errorCode = ErrorMissingVarDef;
		errorInfor1 = line;
		return 423432235;
	}

	GTNode* EXP_RIGHT = GTarget->child(2);//exp: ID assign EXP_RIGHT semicolon;
	ConstObj* srcR = NULL;
	int error = GetAConst(srcR, eme, EXP_RIGHT, dst);
	if (error != 0) return error;
	if (obj->GetType() != srcR->GetType())
	{
		errorCode = ErrorAssignType;
		return 48978977;
	}
	

	NetG::rules IDR = (NetG::rules)ID->root().site;
	if (IDR != Pikachu::NetG::ID_single_)
	{
		size_t dim;
		error = GetIDdim(dim, eme, ID, dst);
		if (error != 0) return error;
		obj->assign(srcR, dim);
	}
	else
	{
		obj->assign(srcR);
	}
	delete srcR;
	return error;
}

int BuildInfor::addVar(const lex& eme, GTNode* ID, context* dst, func* Func, const char* attri)
{
	size_t dim = 0;
	int error = GetIDdim(dim, eme, ID, dst);
	const char* name = getIDname(eme, ID);
	bool scalar = getIDscalar(eme, ID);

	var* old = dst->search(name);
	ConstObj* oldC = dst->searchConst(name);
	if (old != NULL || oldC != NULL)
	{
		errorCode = VarAlreadDef;
		ErrorNode = ID;
		return 234789433;
	}
	var* newVar = new var;
	newVar->SetName(name);
	if(attri != NULL)newVar->SetAttri(attri);
	if (!scalar)
	{
		if (dim == 0)
		{
			//error
			return 78924244;
		}
		newVar->SetCount(dim);
	}
	else dim = 1;
	dst->global.append(newVar);
}

int BuildInfor::buildSymbolicPara(const lex& eme, GTNode* PARA, context* dst, func* Func)
{
	int error = 0;
	size_t line = PARA->root().site;
	NetG::rules RR = (NetG::rules)PARA->root().site;
	size_t count = PARA->ChildCount();
	if (RR != NetG::rules::PARA_PARA_ || count % 2 != 1)
	{
		errorInfor1 = line;
		errorCode = WrongEntrance;
		return 79858734;
	}
	Expres* Exp = Func->Exp;
	for (size_t i = 0; i < count; i += 2)
	{
		GTNode* SYMBOLICPARA = PARA->child(i);
		GTNode* ID = SYMBOLICPARA->child(1);
		int error = addVar(eme, ID, dst, Func, "NULL");
		var* newVar = dst->global[dst->global.count() - 1];
		size_t dim = newVar->count();

		NetG::rules TypePara = (NetG::rules)SYMBOLICPARA->root().site;

		switch (TypePara)
		{
		case Pikachu::NetG::SYMBOLICPARA_input_:
		{
			newVar->SetAttri("input");
			for (size_t j = 0; j < dim; j++)
			{
				Expres::node* Node = Exp->NewNode(Pikachu::_LeafX_, Func->InputCount, j);
				newVar->SetInfor(Node, j);
			}
			Func->InputCount += 1;
			break;
		}
		case Pikachu::NetG::SYMBOLICPARA_para_:
		{

			newVar->SetAttri("para");
			for (size_t j = 0; j < dim; j++)
			{
				Expres::node* Node = Exp->NewNode(Pikachu::_LeafPara_, Func->ParaCount, j);
				newVar->SetInfor(Node, j);
			}
			Func->ParaCount += 1;
			break;
		}
		case Pikachu::NetG::SYMBOLICPARA_output_:
		{
			newVar->SetAttri("output");
			Func->OutputCount += 1;
			break;
		}
		default:
		{
			errorInfor1 = line;
			errorCode = WrongEntrance;
			return 79858735;
		}
		}
	}

	return error;
}
int BuildInfor::buildSymbolicName(const lex& eme, GTNode* Nameid, context* dst, func* Func)
{
	int error = 0;
	size_t site = Nameid->root().site;
	if (Nameid->root().rules)
	{
		errorInfor1 = site;
		errorCode = WrongEntrance;
		return 7985875;
	}
	int accept = eme[site].accept;
	if (accept != NetL::regular::_id_)
	{
		errorInfor1 = site;
		errorCode = WrongEntrance;
		return 7985876;
	}

	const char* Name = eme.GetWord(site);
	context* Parent = dst->parent;

	func* old;
	old = Parent->searchFuncs(Name);
	if (old != NULL)
	{
		errorCode = SymbolicAlreadyDef;
		errorInfor1 = site;
		return 7985877;
	}
	Func->SetName(Name);

	Parent->funcs.append(Func);

	return error;
}
int BuildInfor::buildSymbolicBody(const lex& eme, GTNode* SYMBOLICBODY, context* dst, func* Func)
{
	int error = 0;
	int error = 0;
	size_t line = SYMBOLICBODY->root().site;
	NetG::rules RR = (NetG::rules)SYMBOLICBODY->root().site;
	if (RR != NetG::rules::SYMBOLICBODY_SYMBOLICBODY_)
	{
		errorInfor1 = line;
		errorCode = WrongEntrance;
		return 7923432;
	}
	for (size_t i = 0; i < SYMBOLICBODY->ChildCount(); i++)
	{
		GTNode* STATEMENT = SYMBOLICBODY->child(i);
		NetG::rules Rule = (NetG::rules)STATEMENT->root().site;
		switch (Rule)
		{
		case Pikachu::NetG::STATEMENT_const_:
		{
			GTNode* CONSTVAR = STATEMENT->child(0);
			error = buildConstObj(eme, CONSTVAR, dst);
			if (error != 0) return error;
			break;
		}
		case Pikachu::NetG::STATEMENT_def1_:
		{
			GTNode* ID = STATEMENT->child(1);
			error = addVar(eme, ID, dst, Func, "var");
			if (error != 0) return error;
			break;
		}
		case Pikachu::NetG::STATEMENT_def2_:
		{
			GTNode* ID = STATEMENT->child(1);
			error = addVar(eme, ID, dst, Func, "var");
			if (error != 0) return error;
			break;
		}
		case Pikachu::NetG::STATEMENT_exp_:
		{
			GTNode* ID = STATEMENT->child(0);
			const char* name = getIDname(eme, ID);
			var* target = dst->SearchLocal(name);
			ConstObj* local = dst->SearchConstLocal(name);
			ConstObj* global = dst->searchConst(name);
			if (target != NULL)
			{
				if (error != 0) return error;
			}
			else if (local != NULL)
			{
				error = buildExp(eme, STATEMENT, dst);
				if (error != 0) return error;
			}
			else
			{
				if (error != 0) return error;
			}
			
			break;
		}
		default:
		{
			ErrorNode = STATEMENT;
			errorCode = WrongEntrance;
			return 79858735;
			break;
		}

	}
	return error;
}
int BuildInfor::buildSymbolicCheck(const lex& eme, GTNode* SYMBOLIC, context* dst, func* Func)
{
	int error = 0;
	if (Func->InputCount >= 1)
	{
		errorCode = TooMuchInput;
		ErrorNode = SYMBOLIC;
		return 234789406;
	}
	if (Func->ParaCount >= 1)
	{
		errorCode = TooMuchPara;
		ErrorNode = SYMBOLIC;
		return 234789407;
	}
	if (Func->OutputCount == 0)
	{
		ErrorNode = SYMBOLIC;
		errorCode = NoneOutput;
		return 79858736;
	}
	for (size_t i = 0; i < dst->global.count(); i++)
	{
		var* temp = dst->global[i];
		if (!temp->compareAttri("output")) continue;
		if (temp->scalar())
		{
			if (temp->Getnode() == NULL)
			{
				ErrorNode = SYMBOLIC;
				errorCode = UndefineOutput;
				return 8934534345;
			}
		}
		else
		{
			for (size_t j = 0; j < temp->count(); j++)
			{
				if (temp->Getnode(j) == NULL)
				{
					ErrorNode = SYMBOLIC;
					errorCode = UndefineOutput;
					return 8934534346;
				}
			}
		}
	}



	return error;
}
int BuildInfor::buildSymbolic(const lex& eme, GTNode* SYMBOLIC, context * dst)
{
	GTiterator iterator;
	int error = 0;
	size_t line = SYMBOLIC->child(0)->root().site;
	NetG::rules RR = (NetG::rules)SYMBOLIC->root().site;
	if (RR != NetG::rules::SYMBOLIC_SYMBOLIC_)
	{
		errorInfor1 = line;
		errorCode = WrongEntrance;
		return 7985872;
	}
	context* subcontext = new context();
	dst->append(subcontext);
	
	func* Func = new func();
	error = buildSymbolicName(eme, SYMBOLIC->child(1), subcontext, Func);
	if (error != 0) return error;

	GTNode* PARA = SYMBOLIC->child(3);
	error = buildSymbolicPara(eme, PARA, subcontext, Func);
	if (error != 0) return error;

	GTNode* SYMBOLICBODY = SYMBOLIC->child(6);
	error = buildSymbolicBody(eme, PARA, subcontext, Func);

	
	return buildSymbolicCheck(eme, SYMBOLIC, dst, Func);
}
int BuildInfor::buildNet(const lex& eme, GTNode* GTarget, context * dst)
{
	GTNode* GT = NULL;
	GTiterator iterator;
	int error = 0;
	iterator.initial(GTarget);
	while (iterator.still())
	{
		GT = iterator.target();
		iterator.next();
	}
	return error;
}
int BuildInfor::buildDiff(const lex& eme, GTNode* GTarget, context * dst)
{
	GTNode* GT = NULL;
	GTiterator iterator;
	int error = 0;
	iterator.initial(GTarget);
	while (iterator.still())
	{
		GT = iterator.target();
		iterator.next();
	}
	return error;
}






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
	S.append(liberal);
	value initVal;
	V.append(initVal);
}
ConstObj::ConstObj(size_t dim, bool Scalar, ConstObj::type TTT, const char* Name)
{
	T = TTT;
	scalar = Scalar;
	SetName(name); // 基类设置名称[1](@ref)
	S.recount(dim); // 预分配状态数组
	V.recount(dim); // 预分配值数组

	// 初始化默认值
	value initVal;
	for (size_t i = 0; i < dim; ++i) {
		S[i] = status::liberal; // 默认为未赋值状态
		switch (T) {
		case _sint_: initVal.i = 0; break;
		case _unit_: initVal.u = 0; break;
		case _bool_: initVal.b = false; break;
		case _complex_: initVal.t = nullptr; break; // 张量需额外初始化
		case _real_: initVal.f = 0.0; break;
		}
		V[i] = initVal;
	}
}
ConstObj::ConstObj(ConstObj* left, const char* op, ConstObj* right)// 二元运算构造函数（left op right）
{
	value initVal{};
	scalar = true;
	S.append(liberal);
	value initVal;
	V.append(initVal);
	// 类型和维度校验
	if (!left || !right) return; 
	T = left->T;
	if( left->T != right->T || !left->scalar || !right->scalar)return;
	if (left->S[0] != valued || right->S[0] != valued)return;
	S[0] = valued;


	// 根据操作符执行运算
	switch (op[0]) {
	case '+':
		if (T == _sint_)       V[0].i = left->V[0].i + right->V[0].i;
		else if (T == _real_)  V[0].f = left->V[0].f + right->V[0].f;
		else if (T == _unit_)  V[0].u = left->V[0].u + right->V[0].u; // 无符号加法[3,6](@ref)
		break;
	case '-':
		if (T == _sint_)       V[0].i = left->V[0].i - right->V[0].i;
		else if (T == _real_)  V[0].f = left->V[0].f - right->V[0].f;
		else if (T == _unit_)  V[0].u = left->V[0].u - right->V[0].u; // 无符号减法[6](@ref)
		break;
	case '*':
		if (T == _sint_)       V[0].i = left->V[0].i * right->V[0].i;
		else if (T == _real_)  V[0].f = left->V[0].f * right->V[0].f;
		else if (T == _unit_)  V[0].u = left->V[0].u * right->V[0].u; // 无符号乘法
		break;
	case '/':
		if (T == _sint_ && right->V[0].i != 0)
			V[0].i = left->V[0].i / right->V[0].i;
		else if (T == _real_ && right->V[0].f != 0.0)
			V[0].f = left->V[0].f / right->V[0].f;
		else if (T == _unit_ && right->V[0].u != 0) V[0].u = left->V[0].u / right->V[0].u;
		//else
			//errorCode = ErrorDivideByZero;  // 除零错误
		break;
	default:
		//errorCode = ErrorInvalidOperator;   // 无效操作符
	}
}

// 一元运算构造函数（op right）
ConstObj::ConstObj(const char* op, ConstObj* right)
{
	value initVal{};
	scalar = true;
	S.append(liberal);
	value initVal;
	V.append(initVal);
	// 类型和维度校验
	if (!right) return;
	T = right->T;
	if (!right->scalar)return;
	if (right->S[0] != valued)return;
	S[0] = valued;

	// 根据操作符执行运算
	if (strcmp(op, "+") == 0) {  // 不变
		if (T == _sint_)      V[0].i = right->V[0].i;
		else if (T == _real_) V[0].f = right->V[0].f;
	}
	else if (strcmp(op, "-") == 0) {  // 取反
		if (T == _sint_)      V[0].i = -right->V[0].i;
		else if (T == _real_) V[0].f = -right->V[0].f;
	}
}
ConstObj::ConstObj(sint Rvalue, ConstObj::type TTT)// 整型构造函数
{
	T = (_sint_);
	scalar = (true);
	// 初始化状态向量：单元素，标记为已赋值
	S.append(status::valued);
	// 初始化值向量：存储整型值
	value initVal;
	initVal.i = Rvalue;
	V.append(initVal);
}
ConstObj::ConstObj(double Rvalue)// 双精度浮点型构造函数
{
	T = (_real_);
	scalar = (true);
	// 初始化状态向量：单元素，标记为已赋值
	S.append(status::valued);
	// 初始化值向量：存储浮点值
	value initVal;
	initVal.f = Rvalue;
	V.append(initVal);
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
void ConstObj::copy(const ConstObj* src)
{
	if (!src) return; // 安全校验：源对象为空时直接返回

	// 1. 清除目标对象现有数据
	S.clear(); // 清空状态向量
	V.clear(); // 清空值向量

	// 2. 复制基本属性
	T = src->T;        // 复制数据类型
	scalar = src->scalar; // 复制标量标志
	SetName(src->GetName()); // 调用基类方法复制名称（深拷贝字符串）

	// 3. 深拷贝状态向量 S
	for (size_t i = 0; i < src->S.count(); ++i) {
		S.append(src->S[i]); // 逐元素复制状态值
	}

	// 4. 深拷贝值向量 V
	for (size_t i = 0; i < src->V.count(); ++i) {
		value newVal; // 新值容器
		switch (T) {  // 按数据类型选择复制策略
		case _sint_:
			newVal.i = src->V[i].i; // 整型直接赋值
			break;
		case _unit_:
			newVal.u = src->V[i].u; // 无符号整型直接赋值
			break;
		case _bool_:
			newVal.b = src->V[i].b; // 布尔型直接赋值
			break;
		case _real_:
			newVal.f = src->V[i].f; // 浮点型直接赋值
			break;
		case _complex_:
			// 张量需完全独立复制（示例伪代码）
			if (src->V[i].t) {
				//size_t byteSize = ...; // 获取张量内存大小（需实际逻辑）
				//newVal.t = malloc(byteSize);
				newVal.t = NULL;
				//memcpy(newVal.t, src->V[i].t, byteSize); // 深拷贝张量数据
			}
			else {
				newVal.t = NULL;
			}
			break;
		}
		V.append(newVal); // 添加复制后的值到向量
	}
}
void ConstObj::copy(const ConstObj* src, size_t No) {
	if (!src) return;
	if (No >= src->V.count()) return; // 校验源对象及索引有效性[6](@ref)
	// if( src->S[No]!= valued) return;
	// 1. 清除目标对象现有数据
	S.clear();
	V.clear();

	// 2. 复制基本属性（目标对象变为标量）
	T = src->T;          // 继承源元素数据类型
	scalar = true;       // 目标对象变为标量（单元素）
	SetName(src->GetName()); // 复制名称（基类深拷贝字符串）

	// 3. 深拷贝指定元素的状态和值
	S.append(src->S[No]); // 复制状态值
	value newVal;
	switch (T) {
	case _sint_:
		newVal.i = src->V[No].i;
		break;
	case _unit_:
		newVal.u = src->V[No].u;
		break;
	case _bool_:
		newVal.b = src->V[No].b;
		break;
	case _real_:
		newVal.f = src->V[No].f;
		break;
	case _complex_:
		if (src->V[No].t) {
			// 张量深拷贝（需实际内存大小计算逻辑）
			//size_t byteSize = ...; // 需补充：获取张量内存大小
			//newVal.t = malloc(byteSize);
			newVal.t = NULL;
			//memcpy(newVal.t, src->V[No].t, byteSize); // 复制数据[6](@ref)
		}
		else {
			newVal.t = NULL;
		}
		break;
	}
	V.append(newVal); // 添加复制后的值
}
// ------------ 赋值操作 ------------
void ConstObj::assign(sint right) {
	if (!scalar) return; // 非标量对象禁用此方法
	if (T != _sint_) return; // 类型检查

	V[0].i = right;
	S[0] = status::valued;
}
void ConstObj::assign(size_t NO, sint right) {
	//if (scalar || NO >= V.count()) return; // 标量或越界检查
	if (T != _sint_) return; // 类型检查

	V[NO].i = right;
	S[NO] = status::valued;
}
void ConstObj::assign(const ConstObj* srcR) {
	if (!srcR) return;  // 空指针检查[1](@ref)

	// 1. 自赋值检查（避免资源释放导致数据丢失）
	if (this == srcR) return;  // 防止自赋值[7,8](@ref)

	// 2. 释放当前对象资源（尤其动态内存）
	S.clear();  // 清空状态向量
	V.clear();  // 清空值向量（若含张量则需额外释放内存）

	// 3. 复制基本属性
	T = srcR->T;         // 数据类型（_sint_/_unit_等）
	scalar = srcR->scalar; // 标量/数组标志
	//SetName(srcR->GetName());  // 深拷贝名称（基类方法）[1](@ref)

	// 4. 深拷贝状态向量S
	for (size_t i = 0; i < srcR->S.count(); ++i) {
		S.append(srcR->S[i]);  // 逐元素复制状态值
	}

	// 5. 深拷贝值向量V（类型敏感处理）
	for (size_t i = 0; i < srcR->V.count(); ++i) {
		value newVal;
		switch (T) {  // 按数据类型选择复制策略
		case _sint_:
			newVal.i = srcR->V[i].i;  // 整型直接赋值
			break;
		case _unit_:
			newVal.u = srcR->V[i].u;  // 无符号整型直接赋值
			break;
		case _bool_:
			newVal.b = srcR->V[i].b;  // 布尔型直接赋值
			break;
		case _real_:
			newVal.f = srcR->V[i].f;  // 浮点型直接赋值
			break;
		case _complex_:
			// 张量深拷贝（需实际内存大小计算）
			if (srcR->V[i].t) {
				newVal.t = NULL; // 复制数据
			}
			else {
				newVal.t = NULL;
			}
			break;
		}
		V.append(newVal);  // 添加复制值到向量
	}
}
void ConstObj::assign(const ConstObj* srcR, size_t No)
{
	if (!srcR)return;
	if( No >= srcR->V.count())return;  // 校验源对象及索引有效性[7,8](@ref)

	// 1. 清除当前对象数据（释放旧资源）
	S.clear();
	V.clear();

	// 2. 继承源元素类型并设为标量
	T = srcR->T;
	scalar = true;
	//SetName(srcR->GetName());  // 深拷贝名称[6](@ref)

	// 3. 复制指定元素的状态
	S.append(srcR->S[No]);

	// 4. 按数据类型深拷贝值
	value newVal;
	switch (T) {
	case _sint_:
		newVal.i = srcR->V[No].i;
		break;
	case _unit_:
		newVal.u = srcR->V[No].u;
		break;
	case _bool_:
		newVal.b = srcR->V[No].b;
		break;
	case _real_:
		newVal.f = srcR->V[No].f;
		break;
	case _complex_:
		if (srcR->V[No].t) {
			newVal.t = NULL; // 深拷贝张量[8](@ref)
		}
		else {
			newVal.t = NULL;
		}
		break;
	}
	V.append(newVal);  // 添加新值
}


var::var()
{
	initial();
}
var::~var()
{
	free(attribute);
	attribute = NULL;
	infor = NULL;
}
void var::ruin(void)
{
	free(attribute);
	attribute = NULL;
	infor = NULL;
	ruinCO();
}
void var::initial(void)
{
	name = NULL;
	infor = NULL;
}
void var::demo(FILE* fp) const
{
	
}

void var::SetAttri(const char* NewName)
{
	size_t i;
	free(attribute);
	attribute = NULL;
	if (!NewName) return;

	size_t len = 0;
	while (NewName[len] != '\0') ++len;

	attribute = (char*)(malloc((len + 1) * sizeof(char)));
	for (i = 0; i <= len; ++i)
	{
		attribute[i] = NewName[i];
	}
}


func::func()
{
	Exp = NULL;

	InputCount = 0;
	OutputCount = 0;
	ParaCount = 0;
}
func::~func()
{
	delete Exp;
	Exp = NULL;
}
void func::ruin(void)
{
	delete Exp;
	Exp = NULL;
	ruinCO();
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

void BuildInfor::ErrorDemo(FILE* fp) const
{
	switch (errorCode)
	{
	case BuildInfor::NoError:
		fprintf(fp, "No Error!\n");
		break;
	case BuildInfor::ErrorinputLEXICAL:
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
	case BuildInfor::PretreatLEXICAL:
	{
		fprintf(fp, "PretreatLEXICAL: Error happenned during pretreatment.\n");
		fprintf(fp, "Lexical analysis line: %zu of No.%zu ", errorInfor2, errorInfor1);
		fprintf(fp, "source file %s made a mistake\n", MorphemePre.GetFile(errorInfor1));
		break;
	}
	case BuildInfor::PretreatGRAMMAR:
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
	case BuildInfor::PretreatRepeat:
	{
		fprintf(fp, "PretreatRepeat: Error happenned during pretreatment.\n");
		fprintf(fp, "No.%zu ", errorInfor1);
		fprintf(fp, "source file %s repeats with existed ", MorphemePre.GetFile(errorInfor1));
		fprintf(fp, "%zu file %s\n", errorInfor2, MorphemePre.GetFile(errorInfor2));
		break;
	}
	case BuildInfor::PretreatOpenfail:
	{
		fprintf(fp, "PretreatOpenfail: Error happenned during pretreatment.\n");
		fprintf(fp, "Open of No.%zu ", errorInfor1);
		fprintf(fp, "source file %s made a mistake\n", MorphemePre.GetFile(errorInfor1));
		break;
	}
	case BuildInfor::PretreatNone:
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
	case BuildInfor::ErrorinputGrammar:
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
	case BuildInfor::buildUndone:
	{
		fprintf(fp, "buildUndone: has not been built.\n");
		fprintf(fp, "\n");
		break;
	}
	default:
	{
		fprintf(fp, "Error Unknown: %d\n", (int)errorCode);
		break;
	}
	}

}


context::context()
{
	//errorInfor3 = NULL;
	initial();
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

	//free(errorInfor3);
	//errorInfor3 = NULL;
}
void context::demo(FILE* fp) const
{

}
void context::append(context* child)
{
	childs.append(child);
	child->parent = this;
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

ConstObj* context::searchConst(const char* name)const
{
	ConstObj* value = SearchConstLocal(name);
	if (value != NULL) return value;
	context* now = parent;
	while (now != NULL)
	{
		ConstObj* temp = now->SearchConstLocal(name);
		if (temp != NULL) return temp;
		now = parent->parent;
	}
	return NULL;
}
ConstObj* context::SearchConstLocal(const char* name)const
{
	for (size_t i = 0; i < Cobj.count(); i++)
	{
		if (Cobj[i]->eqaul(name)) return Cobj[i];
	}
	return NULL;
}

func* context::searchFuncs(const char* name) const
{
	func* value = searchFuncsLocal(name);
	if (value != NULL) return value;
	context* now = parent;
	while (now != NULL)
	{
		func* temp = now->searchFuncsLocal(name);
		if (temp != NULL) return temp;
		now = parent->parent;
	}
	return NULL;
}
func* context::searchFuncsLocal(const char* name) const
{
	for (size_t i = 0; i < funcs.count(); i++)
	{
		if (funcs[i]->eqaul(name)) return funcs[i];
	}
	return NULL;
}

int context::build(const char* FileName)
{
	BuildInfor builder;
	clear();
	initial();
	builder.build(FileName, this);
	if (builder.errorCode != BuildInfor::NoError)
	{
		builder.ErrorDemo();
		clear();
		initial();
	}
	S = NoError;
}



void context::clear(void)
{
	for (size_t i = 0; i < global.count(); i++)
	{
		delete global[i];
	}
	global.clear();
	childs.clear();
	S = Undone;
}
void context::initial(void)
{
	S = Undone;
	parent = NULL;
}








static bool compare(const char* str1, const char* str2)
{
	size_t i;
	for (i = 0; (str1[i] != '\0') && (str1[i] == str2[i]); i++);
	return str1[i] == str2[i];
}


/*
	MorphemePre.clear();
	LexicalSource.clear();

	errorCode = NoError;
	errorInfor1 = 0;
	errorInfor2 = 0;
	errorInfor3 = NULL;
	errorInfor4 = true;



	errorCode = buildUndone;
	errorInfor1 = 0;
	errorInfor2 = 0;
	errorInfor3 = NULL;
	errorInfor4 = true;
*/
/*
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

		ErrorUnsupportType,
		ErrorRepeatVarDef,
		ErrorMissingVarDef,
		ErrorIndexOutofRange,
		ErrorNeedAInt,
		ErrorNameNULL,
		WrongEntrance,

		ErrorInitialAorS,
		//array dim not equal, assignment between
		//scalar and array
		ErrorNotAConst,
		ErrorUnsupportFunc,
		ErrorUnKnowEXP,
		buildUndone,
	};

	hyperlex::Morpheme MorphemePre;
	hyperlex::Morpheme LexicalSource;

	errorType errorCode;
	size_t errorInfor1;
	size_t errorInfor2;
	char* errorInfor3;
	bool errorInfor4;


	int pretreatment(const char* input, hyperlex::Morpheme& output);
	void NeglectNullToken(lex& eme) const;
	int buildGanalysis(const lex& eme);
	int buildAll(const lex& eme, AST& Tree);

	int buildConstObj(const lex& eme, GTNode* GTarget);
	int buildExp(const lex& eme, GTNode* GTarget);
	int buildSymbolic(const lex& eme, GTNode* GTarget);
	int buildNet(const lex& eme, GTNode* GTarget);
	int buildDiff(const lex& eme, GTNode* GTarget);

	int SetAConstObj(const lex& eme, GTNode* GTarget, ConstObj::type Type);
	int GetAConst(ConstObj*& output, const lex& eme, GTNode* GTarget);
	size_t getValueDim(GTNode* GTarget);
*/
/*
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
				case Pikachu::NetG::DEF_symbolic_:
				{
					GTNode* GTarget = GT->child(0);
					iterator.state() = 1;
					error = buildSymbolic(eme, GTarget);
					break;
				}
				case Pikachu::NetG::DEF_network_:
				{
					GTNode* GTarget = GT->child(0);
					iterator.state() = 1;
					error = buildNet(eme, GTarget);
					break;
				}
				case Pikachu::NetG::DEF_def_:
				{
					GTNode* GTarget = GT->child(0);
					iterator.state() = 1;
					error = buildConstObj(eme, GTarget);
					break;
				}
				case Pikachu::NetG::DEF_exp_:
				{
					GTNode* GTarget = GT->child(0);
					iterator.state() = 1;
					error = buildExp(eme, GTarget);
					break;
				}
				case Pikachu::NetG::DEF_diff_:
				{
					GTNode* GTarget = GT->child(0);
					iterator.state() = 1;
					error = buildDiff(eme, GTarget);
					break;
				}
				default:
					break;
				}
				if (error != 0) return error;
			}
		}
		iterator.next();
	}
	return error;
}
 static const char * getIDname(const lex& eme, GTNode* GTarget)
{
	GTNode* Def = GTarget->child(0);
	if (Def->root().rules) return NULL;
	else return eme.GetWord(Def->root().site);
}
static ConstObj::type getType(const char* input)
{

	if (input == NULL) return ConstObj::type::_sint_;
	if( compare(input, "sint")) return ConstObj::type::_sint_;
	else if(compare(input, "unit")) return ConstObj::type::_unit_;
	else if (compare(input, "bool")) return ConstObj::type::_bool_;
	else if (compare(input, "complex")) return ConstObj::type::_complex_;
	else if (compare(input, "real")) return ConstObj::type::_real_;
	else return ConstObj::type::_unit_;
}
static ConstObj::type getType(const lex& eme, GTNode* GTarget)
{
	const char* input = eme.GetWord(GTarget->root().site);
	return getType(input);
}
int context::SetAConstObj(const lex& eme, GTNode* GTarget, ConstObj::type Type)
{
	const char* name = NULL;
	name = getIDname(eme, GTarget);
	size_t line = GTarget->child(0)->root().site;
	if (name == NULL)
	{
		errorCode = ErrorNameNULL;
		errorInfor1 = line;
		return 123234;
	}
	ConstObj* obj = searchConst(name);
	if (obj != NULL)
	{
		errorCode = ErrorRepeatVarDef;
		errorInfor1 = line;
		return 423432234;
	}
	NetG::rules RR = (NetG::rules)GTarget->root().site;
	//Pikachu::NetG::ID_array_;
	//Pikachu::NetG::ID_single_;
	bool Scalar_ = false;
	if (RR == Pikachu::NetG::ID_single_) Scalar_ = true;
	else Scalar_ = false;
	sint dim = 0;
	if (!Scalar_)
	{
		ConstObj* Const_;
		int error = GetAConst(Const_, eme, GTarget->child(1)->child(1));
		if (error != 0) return error;
		if (!Const_->SorUint())
		{
			errorInfor1 = line;
			errorCode = ErrorNeedAInt;
			return 1234234;
		}
		dim = Const_->GetSint();
		//if (dim < 0 || (size_t)dim >= Const_->GetDim())
		if (dim < 0)
		{
			errorInfor1 = line;
			errorInfor2 = dim;
			errorCode = ErrorIndexOutofRange;
			return 1234267;
		}
	}
	obj = new ConstObj(dim, Scalar_, Type, name);
	Cobj.append(obj);
}
int context::GetAConst(ConstObj* & output, const lex& eme, GTNode* GTarget)
{
	GTiterator iterator;
	int error = 0;
	output = NULL;
	iterator.initial(GTarget);

	NetG::nonterminal RRR = (NetG::nonterminal)NetG::RulesToSymbol[GTarget->root().site];
	if (RRR != NetG::nonterminal::_EXP_RIGHT_)
	{
		errorInfor1 = GTarget->root().site;
		errorCode = WrongEntrance;
		return 12321;
	}
	while (iterator.still())
	{
		GTNode* GT = iterator.target();
		if (iterator.state() == 1)
		{
			NetG::rules RR = (NetG::rules)GT->root().site;
			switch (RR)
			{
			case Pikachu::NetG::EXP_RIGHT_add_:
			case Pikachu::NetG::EXP_MUL_multi_:
			{
				GTNode* Left = GT->child(0);
				GTNode* Right = GT->child(2);
				ConstObj* left = (ConstObj*)(Left->root().infor);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				if (!left->ValuedScalarSint() && !right->ValuedScalarSint())
				{
					errorCode = ErrorNotAConst;
					error = 2712312;
				}
	
				GTNode* op = GT->child(1);
				const char* OP = eme.GetWord(op->root().site);
				ConstObj* Lvalue = new ConstObj(left, OP, right);
				GT->root().infor = (void*)Lvalue;
				break;
			}
			case Pikachu::NetG::EXP_MINUS_plus_:
			{
				GTNode* Right = GT->child(1);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				if (!right->ValuedScalarSint())
				{
					errorCode = ErrorNotAConst;
					error = 2712312;
				}
				GTNode* op = GT->child(0);
				const char* OP = eme.GetWord(op->root().site);
				ConstObj* Lvalue = new ConstObj(OP, right);
				GT->root().infor = (void*)Lvalue;
				
				break;
			}
			case Pikachu::NetG::CALL_call_1_:
			case Pikachu::NetG::CALL_call_2_:
			case Pikachu::NetG::UNIT_call_:
			{
				errorCode = ErrorUnsupportFunc;
				error = 23423423;
				break;
			}
			case Pikachu::NetG::UNIT_const_:
			{
				GTNode* num = GT->child(0);
				size_t token = num->root().site;
				int accept = eme[token].accept;
				if (accept == (int)NetL::regular::_integer_)
				{
					sint temp = (sint)eme.GetInt(token);
					ConstObj* Lvalue = new ConstObj(temp, ConstObj::_sint_);
					GT->root().infor = (void*)Lvalue;
				}
				else //if (accept == (int)NetL::regular::_realC_)
				{
					double temp = eme.GetReal(token);
					ConstObj* Lvalue = new ConstObj(temp);
					GT->root().infor = (void*)Lvalue;
				}
				break;
			}
			case Pikachu::NetG::ID_array_:
			{
				GTNode* ID = GT->child(0);
				GTNode* index = GT->child(1);
				size_t target = ID->root().site;
				const char* id = eme.GetWord(target);
				ConstObj* Rvalue = searchConst(id);
				ConstObj* Index = (ConstObj*)(index->root().infor);
				if (Rvalue == NULL || Index == NULL)
				{
					errorInfor1 = target;
					errorCode = ErrorMissingVarDef;
					error = 5663456;
				}
				if (!Index->SorUint())
				{
					errorInfor1 = target;
					errorCode = ErrorNeedAInt;
					error = 56336;
				}
				sint No = Index->GetSint();
				if (No < 0 || (size_t)No >= Index->GetDim())
				{
					errorInfor1 = target;
					errorInfor2 = No;
					errorCode = ErrorIndexOutofRange;
					error = 564584566;
				}
				ConstObj* Lvalue = new ConstObj();
				Lvalue->copy(Rvalue, No);
				GT->root().infor = (void*)Lvalue;
				break;
			}
			case Pikachu::NetG::ID_single_:
			{
				GTNode* ID = GT->child(0);
				size_t target = ID->root().site;
				const char* id = eme.GetWord(target);
				ConstObj* Rvalue = searchConst(id);
				if (Rvalue == NULL)
				{
					errorInfor1 = target;
					errorCode = ErrorMissingVarDef;
					error = 5667556;
				}
				ConstObj* Lvalue = new ConstObj();
				Lvalue->copy(Rvalue);
				GT->root().infor = (void*)Lvalue;
				break;
			}
			case Pikachu::NetG::rules::EXP_MINUS_default_:
			case Pikachu::NetG::rules::EXP_MUL_default_:
			case Pikachu::NetG::rules::EXP_RIGHT_default_:
			case Pikachu::NetG::UNIT_id_:
			{
				GTNode* Right = GT->child(0);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				Right->root().infor = NULL;
				GT->root().infor = (void*)right;
				if (!right->ValuedScalarSint())
				{
					errorCode = ErrorNotAConst;
					error = 2712312;
				}
				break;
			}
			case Pikachu::NetG::UNIT_complex_:
			case Pikachu::NetG::INDEX_COMPUTE_single_:
			{
				GTNode* Right = GT->child(1);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				Right->root().infor = NULL;
				GT->root().infor = (void*)right;
				if (!right->ValuedScalarSint())
				{
					errorCode = ErrorNotAConst;
					error = 2712312;
				}
				break;
			}

			}
		}
		if (error != 0) break;
		ConstObj* Lvalue = (ConstObj*)(GT->root().infor);
		if (Lvalue != NULL)
		{
			if (Lvalue->GetState() != ConstObj::status::valued)
			{
				error = 1221312;
				errorCode = ErrorUnKnowEXP;
			}
		}
		if (error != 0) break;
		iterator.next();
	}
	ConstObj* target = (ConstObj*)(GTarget->root().infor);
	output = target;
	GTarget->root().infor = NULL;
	iterator.initial(GTarget);
	while (iterator.still())
	{
		GTNode* GT = iterator.target();
		if (iterator.state() == 1)
		{
			if (GT->root().rules)
			{
				ConstObj* target = (ConstObj*)(GT->root().infor);
				GT->root().infor = NULL;
				delete target;
			}
		}
		iterator.next();
	}
	return error;
}
size_t context::getValueDim(GTNode* VALUE)
{
	if ((Pikachu::NetG::rules)VALUE->root().site == Pikachu::NetG::VALUE_single_)
		return 1;
	GTNode* VALUELIST = VALUE->child(1);//multi: squareL VALUELIST squareR;
	GTNode* VALUES = VALUELIST->child(1);// VALUELIST: EXP_RIGHT VALUES;
	return VALUES->ChildCount() + 1;
}
int context::buildConstObj(const lex& eme, GTNode* GTarget)
{
	int error = 0;
	GTNode* GT = GTarget;
	NetG::rules RR = (NetG::rules)GTarget->root().site;
	ConstObj* obj = NULL;
	size_t line = GT->child(0)->root().site;
	if (GT->root().rules)
	{
		if (RR == Pikachu::NetG::CONSTVAR_def1_ || RR == Pikachu::NetG::CONSTVAR_def2_)
		{
			ConstObj::type TT = getType(eme, GT->child(0));
			if (TT != ConstObj::type::_sint_ && TT != ConstObj::type::_real_)
			{
				errorCode = ErrorUnsupportType;
				errorInfor1 = line;
				return 423434;
			}
			error = SetAConstObj(eme, GT->child(1), TT);
			if (error != 0) return error;
			obj = Cobj[Cobj.count() - 1];
		}
		else
		{
			errorInfor1 = GTarget->root().site;
			errorCode = WrongEntrance;
			return 123897821;
		}
	}
	else
	{
		errorInfor1 = GTarget->root().site;
		errorCode = WrongEntrance;
		return 123897822;
	}
	if (RR == Pikachu::NetG::CONSTVAR_def1_) return error;

	GTNode* VALUE = GTarget->child(3);
	bool valueScalar = ((Pikachu::NetG::rules)VALUE->root().site == Pikachu::NetG::VALUE_single_);
	size_t dim = getValueDim(VALUE);
	if (valueScalar != obj->GetScalar() || dim != obj->GetDim())
	{
		errorCode = ErrorInitialAorS;
		errorInfor1 = line;
		errorInfor2 = dim;
		errorInfor4 = obj->GetScalar();
		return 48975644;
	}
	if (valueScalar)
	{
		GTNode* EXP_RIGHT = VALUE->child(0);//single: EXP_RIGHT;
		ConstObj* srcR = NULL;
		int error = GetAConst(srcR, eme, EXP_RIGHT);
		if (error != 0) return error;
		obj->assign(srcR);
		delete srcR;
	}
	else
	{
		GTNode* VALUELIST = VALUE->child(1);//multi: squareL VALUELIST squareR;
		GTNode* VALUES = VALUELIST->child(1);// VALUELIST: EXP_RIGHT VALUES;
	}
	return error;
}
int context::buildExp(const lex& eme, GTNode* GTarget)
{
	GTNode* GT = NULL;
	GTiterator iterator;
	int error = 0;
	iterator.initial(GTarget);
	while (iterator.still())
	{
		GT = iterator.target();
		iterator.next();
	}
	return error;
}
int context::buildSymbolic(const lex& eme, GTNode* SYMBOLIC)
{
	GTNode* GT = NULL;
	GTiterator iterator;
	int error = 0;
	iterator.initial(SYMBOLIC);
	while (iterator.still())
	{
		GT = iterator.target();
		iterator.next();
	}
	return error;
}
int context::buildNet(const lex& eme, GTNode* GTarget)
{
	GTNode* GT = NULL;
	GTiterator iterator;
	int error = 0;
	iterator.initial(GTarget);
	while (iterator.still())
	{
		GT = iterator.target();
		iterator.next();
	}
	return error;
}
int context::buildDiff(const lex& eme, GTNode* GTarget)
{
	GTNode* GT = NULL;
	GTiterator iterator;
	int error = 0;
	iterator.initial(GTarget);
	while (iterator.still())
	{
		GT = iterator.target();
		iterator.next();
	}
	return error;
}

*/

