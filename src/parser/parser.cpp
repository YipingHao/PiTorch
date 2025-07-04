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
					GTNode* NETWORK = GT->child(0);
					iterator.state() = 1;
					error = buildNet(eme, NETWORK, dst);
					break;
				}
				case Pikachu::NetG::DEF_def_:
				{
					GTNode* CONSTVAR = GT->child(0);
					iterator.state() = 1;
					error = buildConstObj(eme, CONSTVAR, dst);
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
	else if (compare(input, "unit")) return ConstObj::type::_uint_;
	else if (compare(input, "bool")) return ConstObj::type::_bool_;
	else if (compare(input, "complex")) return ConstObj::type::_complex_;
	else if (compare(input, "real")) return ConstObj::type::_real_;
	else return ConstObj::type::_uint_;
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
		ConstObj* Const_ = NULL;
		int error = GetAConst(Const_, eme, ID->child(1)->child(1), dst);
		if (error != 0) return error;
		if (!Const_->SorUint())
		{
			errorInfor1 = line;
			errorCode = ErrorNeedAInt;
			return 1234234;
		}
		sint temp = Const_->GetSint();
		if (temp < 0)
		{
			errorInfor1 = line;
			errorInfor2 = temp;
			errorCode = ErrorMinusIndex;
			return 1234267;
		}
		delete Const_;
		dim = temp;
	}
	else dim = 1;
	return 0;
}
int BuildInfor::GetIDindex(size_t& index, const lex& eme, GTNode* ID, context* dst)
{
	size_t line = ID->child(0)->root().site;
	bool Scalar_ = getIDscalar(eme, ID);
	index = 0;
	if (!Scalar_)
	{
		ConstObj* Const_ = NULL;
		int error = GetAConst(Const_, eme, ID->child(1)->child(1), dst);
		if (error != 0) return error;
		if (!Const_->SorUint())
		{
			errorInfor1 = line;
			ErrorNode = ID;
			errorCode = ErrorNeedAInt;
			return 1234234;
		}
		sint temp = Const_->GetSint();
		if (temp < 0)
		{
			errorInfor1 = line;
			errorInfor2 = temp;
			ErrorNode = ID;
			errorCode = ErrorMinusIndex;
			return 1234267;
		}
		delete Const_;
		index = temp;

	}
	else index = 0;
	return 0;
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
		ErrorNode = GTarget;
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
			{
				GTNode* Right = GT->child(1);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				GTNode* op = GT->child(0);
				const char* OP = eme.GetWord(op->root().site);
				function func = parseFunction(OP);
				
				ConstObj* Lvalue = new ConstObj(func, right);
				GT->root().infor = (void*)Lvalue;
				break;
			}
			case Pikachu::NetG::CALL_call_2_:
			{
				GTNode* Left = GT->child(0);
				GTNode* Right = GT->child(2);
				ConstObj* left = (ConstObj*)(Left->root().infor);
				ConstObj* right = (ConstObj*)(Right->root().infor);


				GTNode* op = GT->child(1);
				const char* OP = eme.GetWord(op->root().site);

				function2 func2 = parseFunction2(OP);

				ConstObj* Lvalue = new ConstObj(func2, left, right);
				GT->root().infor = (void*)Lvalue;
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
					errorCode = ErrorMissingConstVarDef;
					error = 5663456;
					break;
				}
				if (!Index->SorUint())
				{
					errorInfor1 = target;
					errorCode = ErrorNeedAInt;
					error = 56336;
					break;
				}
				sint No = Index->GetInt();
				if (No < 0 || (size_t)No >= Index->GetDim())
				{
					errorInfor1 = target;
					errorInfor2 = No;
					errorCode = ErrorIndexOutofRange;
					error = 564584566;
					break;
				}
				if (Rvalue->GetState(No) != ConstObj::valued)
				{
					errorInfor1 = target;
					errorCode = ErrorMissingConstVarDef;
					error = 5667557;
				}
				ConstObj* Lvalue = new ConstObj();
				Lvalue->assign(Rvalue, No);
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
					errorCode = ErrorMissingConstVarDef;
					error = 5667556;
				}
				if (Rvalue->GetState() != ConstObj::valued)
				{
					errorInfor1 = target;
					errorCode = ErrorMissingConstVarDef;
					error = 5667557;
				}

				ConstObj* Lvalue = new ConstObj();
				Lvalue->assign(Rvalue);
				GT->root().infor = (void*)Lvalue;
				break;
			}
			case Pikachu::NetG::rules::EXP_MINUS_default_:
			case Pikachu::NetG::rules::EXP_MUL_default_:
			case Pikachu::NetG::rules::EXP_RIGHT_default_:
			case Pikachu::NetG::UNIT_call_:
			case Pikachu::NetG::UNIT_id_:
			{
				GTNode* Right = GT->child(0);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				Right->root().infor = NULL;
				GT->root().infor = (void*)right;
				//if (!right->ValuedScalarSint())
				//{
				//	errorCode = ErrorNotAConst;
				//	error = 2712312;
				//}
				break;
			}
			case Pikachu::NetG::UNIT_complex_:
			case Pikachu::NetG::INDEX_COMPUTE_single_:
			{
				GTNode* Right = GT->child(1);
				ConstObj* right = (ConstObj*)(Right->root().infor);
				Right->root().infor = NULL;
				GT->root().infor = (void*)right;
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


int BuildInfor::GetAExpres(Expres::node*& output, const lex& eme, GTNode* EXP_RIGHT, context* dst, func* Func)
{
	int error = 0;
	output = NULL;
	NetG::nonterminal RRR = (NetG::nonterminal)NetG::RulesToSymbol[EXP_RIGHT->root().site];
	if (RRR != NetG::nonterminal::_EXP_RIGHT_)
	{
		errorCode = WrongEntrance;
		errorInfor1 = EXP_RIGHT->root().site;
		ErrorNode = EXP_RIGHT;
		return 12321;
	}
	Expres* Exp = Func->Exp;
	GTiterator iterator;
	iterator.initial(EXP_RIGHT);

	while (iterator.still()) 
	{
		GTNode* GT = iterator.target();
		if (iterator.state() == 0)
		{
			NetG::rules RR = (NetG::rules)GT->root().site;
			switch (RR) {
			case Pikachu::NetG::ID_single_:
			case Pikachu::NetG::ID_array_:
			{
				GTNode* ID = GT->child(0);
				IDinfor id;
				error = id.build(eme, ID, this, dst);
				if (error != 0) return error;
				var* v = id.GetLocalVarR(error, this, dst);
				if (error != 0) return error;
				ID->root().infor = (void*)v->Getnode();
				ConstObj* obj = id.GetAllConstR(error, this, dst);
				if (error != 0) return error;
				if (obj != NULL && v != NULL)
				{
					errorCode = ErrorRepeatVarDef;
					ErrorNode = ID;
					return 18649845;
				}
				if (obj != NULL)
				{
					Expres::node* Node = NULL;
					size_t index = id.GetIndex();
					if (obj->GetType() == ConstObj::_real_)
					{
						double temp = obj->GetReal(index);
						Node = Exp->NewNode(temp);
					}
					else
					{
						sint temp = obj->GetInt(index);
						Node = Exp->NewNode((long)temp);
					}
					ID->root().infor = (void*)Node;
				}
				else
				{
					errorCode = ErrorMissingVarDef;
					ErrorNode = ID;
					return 45354654;
				}
				break;
			}
			}
			iterator.state() = 1;
		}
		else // (iterator.state() == 1) 
		{
			NetG::rules RR = (NetG::rules)GT->root().site;
			switch (RR) {
			case Pikachu::NetG::rules::EXP_RIGHT_default_:
			case Pikachu::NetG::rules::EXP_MUL_default_:
			case Pikachu::NetG::rules::EXP_MINUS_default_:
			case Pikachu::NetG::rules::UNIT_id_:
			case Pikachu::NetG::UNIT_call_:
			{
				GTNode* Right = GT->child(0);
				Expres::node* right = (Expres::node*)(Right->root().infor);
				Right->root().infor = NULL;
				GT->root().infor = (void*)right;
				output = right;
				break;
			}
			case Pikachu::NetG::EXP_RIGHT_add_:
			case Pikachu::NetG::EXP_MUL_multi_:
			{
				GTNode* Left = GT->child(0);
				GTNode* Right = GT->child(2);
				//var* left = (var*)(Left->root().infor);
				//var* right = (var*)(Right->root().infor);
				//Expres::node* SrcL = left->Getnode();
				//Expres::node* SrcR = right->Getnode();
				Expres::node* SrcL = (Expres::node*)(Left->root().infor);
				Expres::node* SrcR = (Expres::node*)(Right->root().infor);

				GTNode* op = GT->child(1);
				const char* OP = eme.GetWord(op->root().site);
				Expres::node* Node = Exp->NewNode(SrcL, OP, SrcR);
				//var* Lvalue = new var(Node);
				GT->root().infor = (void*)Node;
				break;
			}
			case Pikachu::NetG::EXP_MINUS_plus_:
			{
				GTNode* Right = GT->child(1);
				//var* right = (var*)(Right->root().infor);
				//Expres::node* SrcR = right->Getnode();
				Expres::node* SrcR = (Expres::node*)(Right->root().infor);

				GTNode* op = GT->child(0);
				const char* OP = eme.GetWord(op->root().site);
				if (compare(OP, "+"))
				{
					GT->root().infor = (void*)SrcR;
				}
				else
				{
					Expres::node* Node = Exp->NewNode(OP, SrcR);
					GT->root().infor = (void*)Node;
				}
				break;
			}
			case Pikachu::NetG::UNIT_const_:
			{
				GTNode* number = GT->child(0);
				const char* num = eme.GetWord(number->root().site);
				int accept = eme[number].accept;
				NetL::regular Type = (NetL::regular)accept;
				GTNode* op = GT->child(0);
				Expres::node* Node = NULL;
				if (Type == NetL::regular::_integer_)
				{
					sint temp = eme.GetInt(number->root().site);
					Node = Exp->NewNode((long)temp);
					
				}
				else if (Type == NetL::regular::_realC_)
				{
					double temp = eme.GetReal(number->root().site);
					Node = Exp->NewNode(temp);
				}
				else
				{
					errorCode = ErrorUnExpectedType;
					ErrorNode = GT;
					return 458458945;
				}
				//var* Lvalue = new var(Node);
				GT->root().infor = (void*)Node;
				break;
			}
			case Pikachu::NetG::CALL_call_1_:
			{
				GTNode* Right = GT->child(2);
				//var* right = (var*)(Right->root().infor);
				//Expres::node* SrcR = right->Getnode();
				Expres::node* SrcR = (Expres::node*)(Right->root().infor);

				GTNode* func1 = GT->child(0);
				const char* Func = eme.GetWord(func1->root().site);
				Expres::node* Node = Exp->NewNode(Func, SrcR);
				//var* Lvalue = new var(Node);
				GT->root().infor = (void*)Node;
				break;
			}
			case Pikachu::NetG::CALL_call_2_:
			{
				GTNode* Left = GT->child(2);
				GTNode* Right = GT->child(4);
				//var* left = (var*)(Left->root().infor);
				//var* right = (var*)(Right->root().infor);
				//Expres::node* SrcL = left->Getnode();
				//Expres::node* SrcR = right->Getnode();
				Expres::node* SrcL = (Expres::node*)(Left->root().infor);
				Expres::node* SrcR = (Expres::node*)(Right->root().infor);


				GTNode* func2 = GT->child(0);
				const char* Func = eme.GetWord(func2->root().site);
				Expres::node* Node = Exp->NewNode(Func, SrcL, SrcR);
				//var* Lvalue = new var(Node);
				GT->root().infor = (void*)Node;
				break;
			}
			case Pikachu::NetG::UNIT_complex_:
			{
				GTNode* Right = GT->child(1);
				Expres::node* SrcR = (Expres::node*)(Right->root().infor);
				//var* right = (var*)(Right->root().infor);
				Right->root().infor = NULL;
				GT->root().infor = (void*)SrcR;
				break;
			}
			default:
				// 不是变量表达式，返回空
				
				break;
			}
		}
		if (error != 0) break;
		iterator.next();
	}
	return error;
}
int BuildInfor::buildConstObj(const lex& eme, GTNode* CONSTVAR, context * dst)
{
	int error = 0;
	GTNode* GT = CONSTVAR;
	NetG::rules RR = (NetG::rules)CONSTVAR->root().site;
	ConstObj* obj = NULL;
	ConstObj::type TT;
	size_t line = GT->child(0)->root().site;
	
	if (GT->root().rules)
	{
		if (RR == Pikachu::NetG::CONSTVAR_def1_ || RR == Pikachu::NetG::CONSTVAR_def2_)
		{
			TT = getType(eme, GT->child(0));
			if (TT != ConstObj::type::_sint_ && TT != ConstObj::type::_real_)
			{
				errorCode = ErrorUnsupportType;
				errorInfor1 = line;
				return 423434;
			}
			GTNode* ID = GT->child(1);
			IDinfor id;
			error = id.build(eme, ID, this, dst);
			if (error != 0) return error;
			obj = id.SetConstL(error, this, dst, TT);
			//error = SetAConstObj(eme, GT->child(1), TT, dst);
			if (error != 0) return error;
			//obj = dst->Cobj[dst->Cobj.count() - 1];
		}
		else
		{
			errorInfor1 = CONSTVAR->root().site;
			ErrorNode = CONSTVAR;
			errorCode = WrongEntrance;
			return 123897821;
		}
	}
	else
	{
		errorInfor1 = CONSTVAR->root().site;
		ErrorNode = CONSTVAR;
		errorCode = WrongEntrance;
		return 123897822;
	}
	if (RR == Pikachu::NetG::CONSTVAR_def1_) return error;

	ValueList valueList;
	GTNode* VALUE = CONSTVAR->child(3);
	error = valueList.build(eme, VALUE, this, dst);
	if (error != 0) return error;
	if (TT != valueList.GetType())
	{
		errorCode = ErrorAssignType;
		errorInfor2 = valueList.GetType();
		ErrorNode = VALUE;
		return 48975643;
	}
	if (valueList.GetCount() != obj->GetDim() || valueList.IsScalar() != obj->GetScalar())
	{
		errorCode = ErrorAssignDim;
		ErrorNode = VALUE;
		return 48975645;
	}

	for (size_t i = 0; i < valueList.GetCount(); i++)
	{
		ConstObj* srcR = valueList.GetValue(i);
		obj->assign(i, srcR);
	}
	return error;
}
int BuildInfor::buildExp(const lex& eme, GTNode* GTarget, context * dst)
{
	int error = 0;
	
	NetG::rules RR = (NetG::rules)GTarget->root().site;
	ConstObj* obj = NULL;
	size_t line = GTarget->child(0)->root().site;


	GTNode* ID = GTarget->child(0);//exp: ID assign EXP_RIGHT semicolon;
	IDinfor id;
	error = id.build(eme, ID, this, dst);
	if (error != 0) return error;
	ConstObj* obj = id.GetLocalConstL(error, this, dst);
	if (error != 0) return error;

	GTNode* EXP_RIGHT = GTarget->child(2);//exp: ID assign EXP_RIGHT semicolon;
	ConstObj* srcR = NULL;
	int error = GetAConst(srcR, eme, EXP_RIGHT, dst);
	if (error != 0) return error;
	if (obj->GetType() != srcR->GetType())
	{
		errorCode = ErrorAssignType;
		return 48978977;
	}
	
	size_t index = id.GetIndex();
	obj->assign(srcR, index);
	delete srcR;
	return error;
}


int BuildInfor::buildRoutinePara(routine Rou, const lex& eme, GTNode* PARA, context* dst)
{
	int error = 0;
	size_t line = PARA->root().site;
	NetG::rules RR = (NetG::rules)PARA->root().site;
	size_t count = PARA->ChildCount();
	if (RR != NetG::rules::PARA_PARA_ || count % 2 != 1)
	{
		errorInfor1 = line;
		ErrorNode = PARA;
		errorCode = WrongEntrance;
		return 79858734;
	}
	
	for (size_t i = 0; i < count; i += 2)
	{
		GTNode* SYMBOLICPARA = PARA->child(i);
		GTNode* ID = SYMBOLICPARA->child(1);
		IDinfor id;
		error = id.build(eme, ID, this, dst);
		if (error != 0) return error;
		var* newVar = id.SetVarL(error, this, dst, NULL);
		if (error != 0) return error;
		size_t dim = newVar->count();

		if (Rou != routine::expression) continue;
		NetG::rules TypePara = (NetG::rules)SYMBOLICPARA->root().site;

		func* Func = dst->funcs.top();
		Expres* Exp = Func->Exp;
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
int BuildInfor::buildRoutineName(routine Rou, const lex& eme, GTNode* Nameid, context* dst)
{
	int error = 0;
	size_t site = Nameid->root().site;
	if (Nameid->root().rules)
	{
		errorInfor1 = site;
		ErrorNode = Nameid;
		errorCode = WrongEntrance;
		return 7985875;
	}
	int accept = eme[site].accept;
	if (accept != NetL::regular::_id_)
	{
		errorInfor1 = site;
		ErrorNode = Nameid;
		errorCode = WrongEntrance;
		return 7985876;
	}

	const char* Name = eme.GetWord(site);
	context* Parent = dst->parent;
	if (Parent->SearchRoutine(Name))
	{
		errorCode = SymbolicAlreadyDef;
		ErrorNode = Nameid;
		errorInfor1 = site;
		return 7985877;
	}
	switch (Rou)
	{
	case Pikachu::BuildInfor::expression:
	{
		func* Func = new func;
		Func->SetName(Name);
		Func->realm = dst;
		Parent->funcs.append(Func);
		break;
	}	
	case Pikachu::BuildInfor::network:
	{
		NetInContext* Net = new NetInContext;
		Net->SetName(Name);
		Net->realm = dst;
		Parent->nets.append(Net);
		break;
	}
	default:
		break;
	}
	

	return error;
}
int BuildInfor::buildSymbolicBody(const lex& eme, GTNode* SYMBOLICBODY, context* dst, func* Func)
{
	int error = 0;
	size_t line = SYMBOLICBODY->root().site;
	NetG::rules RR = (NetG::rules)SYMBOLICBODY->root().site;
	if (RR != NetG::rules::SYMBOLICBODY_SYMBOLICBODY_)
	{
		errorInfor1 = line;
		errorCode = WrongEntrance;
		ErrorNode = SYMBOLICBODY;
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
			IDinfor id;
			error = id.build(eme, ID, this, dst);
			if (error != 0) return error;
			var* Lvalue = id.SetVarL(error, this, dst, "var");
			if (error != 0) return error;
			break;
		}
		case Pikachu::NetG::STATEMENT_def2_:
		{
			GTNode* ID = STATEMENT->child(1);
			IDinfor id;
			error = id.build(eme, ID, this, dst);
			if (error != 0) return error;
			if (id.GetScalar() != true)
			{
				errorCode = NeedAscalar;
				ErrorNode = ID;
				return 45967;
			}
			var* Lvalue = id.SetVarL(error, this, dst, "var");
			if (error != 0) return error;
			GTNode* EXP_RIGHT = STATEMENT->child(3);
			Expres::node* Node = NULL;
			error = GetAExpres(Node, eme, EXP_RIGHT, dst, Func);
			if (error != 0) return error;
			if (Node == NULL)
			{
				errorCode = ErrorUndefined;
				ErrorNode = EXP_RIGHT;
				return 4343543;
			}
			Lvalue->SetInfor(Node);
			break;
		}
		case Pikachu::NetG::STATEMENT_exp_:
		{
			GTNode* ID = STATEMENT->child(0);
			IDinfor id;
			error = id.build(eme, ID, this, dst);
			if (error != 0) return error;
			const char* name = getIDname(eme, ID);
			var* target = id.GetLocalVarL(error, this, dst);
			if (error != 0) return error;
			ConstObj* local = dst->SearchConstLocal(name);
			ConstObj* global = dst->searchConst(name);
			if (target != NULL)
			{
				Expres::node* Node = NULL;
				GTNode* EXP_RIGHT = STATEMENT->child(2);
				error = GetAExpres(Node, eme, EXP_RIGHT, dst, Func);
				if (error != 0) return error;
				if (Node == NULL)
				{
					errorCode = ErrorUndefined;
					ErrorNode = EXP_RIGHT;
					return 4343543;
				}
				target->SetInfor(Node, id.GetIndex());
			}
			else if (local != NULL)
			{
				error = buildExp(eme, STATEMENT, dst);
				if (error != 0) return error;
			}
			else if (global != NULL)
			{
				errorCode = ShouldNotAssignGlobalConst;
				ErrorNode = ID;
				return 79858733;
			}
			else
			{
				errorCode = ErrorMissingVarDef;
				ErrorNode = ID;
				return 798545433;
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
	}
	return error;
}
int BuildInfor::buildSymbolicCheck(const lex& eme, GTNode* SYMBOLIC, context* dst, func* Func)
{
	int error = 0;
	if (Func->InputCount > 1)
	{
		errorCode = TooMuchInput;
		ErrorNode = SYMBOLIC;
		return 234789406;
	}
	if (Func->ParaCount > 1)
	{
		errorCode = TooMuchPara;
		ErrorNode = SYMBOLIC;
		return 234789407;
	}
	if (Func->OutputCount == 0 || Func->OutputCount > 1)
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
		ErrorNode = SYMBOLIC;
		errorCode = WrongEntrance;
		return 7985872;
	}
	context* subcontext = new context();
	dst->append(subcontext);
	
	
	error = buildRoutineName(routine::expression, eme, SYMBOLIC->child(1), subcontext);
	if (error != 0) return error;
	func* Func = dst->funcs.top();

	GTNode* PARA = SYMBOLIC->child(3);
	error = buildRoutinePara(routine::expression, eme, PARA, subcontext);
	if (error != 0) return error;

	GTNode* SYMBOLICBODY = SYMBOLIC->child(6);
	error = buildSymbolicBody(eme, PARA, subcontext, Func);

	
	return buildSymbolicCheck(eme, SYMBOLIC, dst, Func);
}
int BuildInfor::buildNet(const lex& eme, GTNode* NETWORK, context * dst)
{
	int error = 0;
	size_t line = NETWORK->child(0)->root().site;
	NetG::rules RR = (NetG::rules)NETWORK->root().site;
	if (RR != NetG::rules::NETWORK_NETWORK_)
	{
		errorInfor1 = line;
		ErrorNode = NETWORK;
		errorCode = WrongEntrance;
		return 79567872;
	}
	context* subcontext = new context();
	dst->append(subcontext);

	
	error = buildRoutineName(routine::network, eme, NETWORK->child(1), subcontext);
	if (error != 0) return error;
	NetInContext* Net = dst->nets.top();

	GTNode* PARA = NETWORK->child(3);
	error = buildRoutinePara(routine::network, eme, PARA, subcontext);
	if (error != 0) return error;

	GTNode* NETBODY = NETWORK->child(6);
	error = buildNETBODY(eme, NETBODY, Net);
	//context* dst

	
	return buildNETCheck(eme, NETWORK, subcontext, Net);
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

int BuildInfor::buildNETCheck(const lex& eme, GTNode* NETBODY, context* dst, NetInContext* Net)
{
	for (size_t i = 0; i < dst->global.count(); i++)
	{
		var* temp = dst->global[i];
		if (temp->compareAttri("var")) continue;
		if (temp->scalar())
		{
			if (temp->Getnode() == NULL)
			{
				ErrorNode = NETBODY;
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
					ErrorNode = NETBODY;
					errorCode = UndefineOutput;
					return 8934534346;
				}
			}
		}
	}
	return 0;
}
int BuildInfor::buildTENSOR(const lex& eme, GTNode* NET_STATEMENT, NetInContext* Net)
{
	context* dst = Net->realm;
	int error = 0;
	size_t line = NET_STATEMENT->root().site;
	NetG::rules RR = (NetG::rules)NET_STATEMENT->root().site;
	NetWork* net = Net->net;

	GTNode* TENSOR = NET_STATEMENT->child(0);
	GTNode* VALUELIST = TENSOR->child(2);

	ValueList VL;
	error = VL.build(eme, VALUELIST, this, dst);
	if (error != 0) return error;
	error = VL.checkDim(this);
	if (error != 0) return error;
	vector<size_t> dims;
	VL.GetDim(dims);

	GTNode* TENSOR_ID = NET_STATEMENT->child(1);
	GTNode* ID = TENSOR_ID->child(0);
	TensorID id;
	error = id.build(eme, ID, this, dst);
	if (error != 0) return error;
	var* Lvalue = id.GetLocalVarL(error, this, dst);
	if (error != 0) return error;

	GTNode* TENSORVALUE = NET_STATEMENT->child(3);
	NetG::rules RR = (NetG::rules)TENSORVALUE->root().site;
	GTNode* TENSORID;
	Node* newNode;
	switch (RR)
	{
	case Pikachu::NetG::TENSORVALUE_single_:
	{
		TENSORID = TENSORVALUE->child(1);
		TensorID idL;
		error = idL.build(eme, TENSORID, this, dst);
		if (error != 0) return error;
		Node* srcL = (Node*)idL.GetLocalTensorR(error, this, dst);
		if (error != 0) return error;

		GTNode* SUMSYMBOL = TENSORVALUE->child(0);
		Indexs list;
		error = list.buildSUMSYMBOL(eme, SUMSYMBOL, this, dst);
		if (error != 0) return;


		Node* newNode = net->NewNodeMonoLinear(srcL);
		break;
	}	
	case Pikachu::NetG::TENSORVALUE_multi_:
	{
		TensorID idL, idR;

		TENSORID = TENSORVALUE->child(1);
		error = idL.build(eme, TENSORID, this, dst);
		if (error != 0) return error;
		Node* srcL = (Node*)idL.GetLocalTensorR(error, this, dst);
		if (error != 0) return error;

		TENSORID = TENSORVALUE->child(3);
		error = idR.build(eme, TENSORID, this, dst);
		if (error != 0) return error;
		Node* srcR = (Node*)idR.GetLocalTensorR(error, this, dst);
		if (error != 0) return error;
		
		Node* newNode = net->NewNodeMonoLinear(srcL);
		break;
	}
	case Pikachu::NetG::TENSORVALUE_singleF_:
	{
		TENSORID = TENSORVALUE->child(4);
		TensorID idL;
		error = idL.build(eme, TENSORID, this, dst);
		if (error != 0) return error;
		Node* srcL = (Node*)idL.GetLocalTensorR(error, this, dst);
		if (error != 0) return error;

		GTNode* SUMSYMBOL = TENSORVALUE->child(0);
		Indexs list;
		error = list.buildSUMSYMBOL(eme, SUMSYMBOL, this, dst);
		if (error != 0) return;
		break;
	}
	case Pikachu::NetG::TENSORVALUE_multiF_:
	{
		TensorID idL, idR;

		TENSORID = TENSORVALUE->child(4);
		error = idL.build(eme, TENSORID, this, dst);
		if (error != 0) return error;
		Node* srcL = (Node*)idL.GetLocalTensorR(error, this, dst);
		if (error != 0) return error;

		TENSORID = TENSORVALUE->child(6);
		error = idR.build(eme, TENSORID, this, dst);
		if (error != 0) return error;
		Node* srcR = (Node*)idR.GetLocalTensorR(error, this, dst);
		if (error != 0) return error;

		GTNode* INDEXLIST = TENSORVALUE->child(1);
		Indexs list1;
		error = list1.buildINDEXLIST(eme, INDEXLIST, this, dst);
		if (error != 0) return;

		GTNode* SQ_INDEXUNITS = TENSORVALUE->child(1);
		Indexs list2;
		error = list2.buildSQ_INDEXUNITS(eme, SQ_INDEXUNITS, this, dst);
		if (error != 0) return;
	}
	default: 
	{
		errorCode = WrongEntrance;
		errorInfor1 = line;
		ErrorNode = TENSORVALUE;
		return 4237895342;
	}
		
	}
	id.AssignLocalVarL(error, this, dst, newNode);
	return error;
}

int BuildInfor::buildNETBODY(const lex& eme, GTNode* NETBODY, NetInContext* Net)
{
	context* dst = Net->realm;
	int error = 0;
	size_t line = NETBODY->root().site;
	NetG::rules RR = (NetG::rules)NETBODY->root().site;
	NetWork* net = Net->net;
	if (RR != NetG::rules::NETBODY_net_)
	{
		errorInfor1 = line;
		errorCode = WrongEntrance;
		ErrorNode = NETBODY;
		return 7923432;
	}
	for (size_t i = 0; i < NETBODY->ChildCount(); i++)
	{
		GTNode* NET_STATEMENT = NETBODY->child(i);
		NetG::rules Rule = (NetG::rules)NET_STATEMENT->root().site;
		switch (Rule)
		{
		case Pikachu::NetG::NET_STATEMENT_const_:
		{
			GTNode* CONSTVAR = NET_STATEMENT->child(0);
			error = buildConstObj(eme, CONSTVAR, dst);
			if (error != 0) return error;
			break;
		}
		case Pikachu::NetG::NET_STATEMENT_exp_:
		{
			GTNode* ID = NET_STATEMENT->child(0);
			IDinfor id;
			error = id.build(eme, ID, this, dst);
			if (error != 0) return error;
			const char* name = getIDname(eme, ID);
			ConstObj* local = dst->SearchConstLocal(name);
			ConstObj* global = dst->searchConst(name);
			if (local != NULL)
			{
				error = buildExp(eme, NET_STATEMENT, dst);
				if (error != 0) return error;
			}
			else if (global != NULL)
			{
				errorCode = ShouldNotAssignGlobalConst;
				ErrorNode = ID;
				return 79845733;
			}
			else
			{
				errorCode = ErrorMissingVarDef;
				ErrorNode = ID;
				return 79445433;
			}
			break;
		}
		case Pikachu::NetG::NET_STATEMENT_def_:
		{
			GTNode* ID = NET_STATEMENT->child(1);
			IDinfor id;
			error = id.build(eme, ID, this, dst);
			if (error != 0) return error;
			var* Lvalue = id.SetVarL(error, this, dst, "var");
			if (error != 0) return error;
			break;
		}
		case Pikachu::NetG::NET_STATEMENT_tensorDef1_:
		{
			GTNode* TENSOR = NET_STATEMENT->child(0);
			GTNode* VALUELIST = TENSOR->child(2);

			ValueList VL;
			error = VL.build(eme, VALUELIST, this, dst);
			if (error != 0) return error;
			error = VL.checkDim(this);
			if (error != 0) return error;
			vector<size_t> dims;
			VL.GetDim(dims);

			GTNode* ID = NET_STATEMENT->child(1);
			IDinfor id;
			error = id.build(eme, ID, this, dst);
			if (error != 0) return error;
			var* Lvalue = id.GetLocalTensorL(error, this, dst);
			if (error != 0) return error;
			
			Node::LeafType TTT = Node::ParseLeafType(Lvalue->GetAttri());
			Node* leaf = net->NewNodeLeaf(dims, TTT);
			Lvalue->SetInfor(leaf, id.GetIndex());
			break;
		}
		case Pikachu::NetG::NET_STATEMENT_tensorDef2_:
		{
			error = buildTENSOR(eme, NET_STATEMENT, Net);
			if (error != 0) return error;
			break;
		}
		default:
			break;
		}

	}
	return error;
}

class indiceIS
{
public:
	indiceIS();
	~indiceIS();
	void StoI(void);
	void ItoS(void);
	

	typedef long long int sint;
protected:
	vector<vector<char*>*> indiceS;
	vector<vector<sint>*> indicsI;

	void clearS(void);
	void clearI(void);
};

indiceIS::indiceIS()
{
}
indiceIS::~indiceIS()
{
	clearS();
	clearI();
}
void indiceIS::clearS(void)
{
	for (size_t i = 0; i < indiceS.count(); ++i)
	{
		vector<char*>* temp = indiceS[i];
		for (size_t j = 0; j < temp->count(); ++j)
		{
			free((*temp)[j]);
		}
		delete temp;
	}
	indiceS.clear();
}
void indiceIS::clearI(void)
{
	for (size_t i = 0; i < indicsI.count(); ++i)
	{
		vector<sint>* temp = indicsI[i];
		delete temp;
	}
	indicsI.clear();
}
void indiceIS::StoI(void)
{
	clearI();
	for (size_t i = 0; i < indiceS.count(); ++i)
	{
		vector<char*>* temp = indiceS[i];
		vector<sint>* newI = new vector<sint>();
		for (size_t j = 0; j < temp->count(); ++j)
		{
			const char* str = (*temp)[j];
			sint index = atoi(str);
			newI->append(index);
		}
		indicsI.append(newI);
	}
}
void indiceIS::ItoS(void)
{
	clearS();
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
	switch (T) {
	case _sint_: initVal.i = 0; break;
	case _uint_: initVal.u = 0; break;
	case _bool_: initVal.b = false; break;
	case _complex_: initVal.t = NULL; break; // 张量需额外初始化
	case _real_: initVal.f = 0.0; break;
	}
	for (size_t i = 0; i < dim; ++i) {
		S[i] = status::liberal; // 默认为未赋值状态
		
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
	if(!left->scalar || !right->scalar)return;
	if (left->S[0] != valued || right->S[0] != valued)return;
	S[0] = valued;
	sint Li = left->GetInt();
	sint Ri = right->GetInt();
	double Lf = left->GetReal();
	double Rf = right->GetReal();
	sint DstI = 0;
	double DstF = 0.0;

	// 根据操作符执行运算
	switch (op[0]) 
	{
	case '+':
		DstF = Lf + Rf;
		DstI = Li + Ri;
		break;
	case '-':
		DstF = Lf - Rf;
		DstI = Li - Ri;
		break;
	case '*':
		DstF = Lf * Rf;
		DstI = Li * Ri;
		break;
	case '/':
		if (Ri != 0) DstI = Li / Ri;
		else if (Rf != 0.0) DstF = Lf / Rf;
		break;
	default:
	}

	if (left->isReal() || right->isReal())
	{
		T = _real_;
		V[0].f = DstF;
	}
	else if (left->isInt() || right->isInt())
	{
		T = _sint_;
		V[0].i = DstI;
	}
	else
	{
		T = _bool_;
		V[0].b = (bool)DstI;
	}
}
ConstObj::ConstObj(function func, const ConstObj* srcR)
{
	value initVal{};
	scalar = true;
	S.append(liberal);
	V.append(initVal);

	if (!srcR) return;
	T = _real_;
	if (!srcR->scalar) return;
	if (srcR->S[0] != valued) return;
	S[0] = valued;
	double src = srcR->GetReal();
	V[0].f = ComputeFunction(src, func);
}
ConstObj::ConstObj(function2 func, const ConstObj* left, const ConstObj* srcR)
{
	value initVal{};
	scalar = true;
	S.append(liberal);
	V.append(initVal);

	// 类型和维度校验
	if (!left || !srcR) return;
	// 以左操作数类型为主
	T = _real_;
	if (!left->scalar || !srcR->scalar) return;
	if (left->S[0] != valued || srcR->S[0] != valued) return;
	S[0] = valued;

	double l = left->GetReal();
	double r = srcR->GetReal();
	V[0].f = ComputeFunction2(l, r, func);

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
	if (strcmp(op, "+") == 0) 
	{  // 不变
		V[0] = right->V[0];
	}
	else if (strcmp(op, "-") == 0) {  // 取反
		if (T == _sint_)      V[0].i = -right->V[0].i;
		else if (T == _uint_)
		{
			V[0].u = -right->V[0].u; // 无符号取反[6](@ref)

		}
		else if (T == _bool_) V[0].b = !right->V[0].b; // 布尔取反
		else if (T == _complex_) V[0].f = -right->V[0].f; // 复数取反
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
	case ConstObj::_uint_:
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
		case ConstObj::_uint_:
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
		case _uint_:
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
void ConstObj::copy(const ConstObj* src, size_t No) 
{
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
	case _uint_:
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
void ConstObj::assign(const ConstObj* srcR) 
{
	if (!srcR) return;  // 空指针检查[1](@ref)

	// 1. 自赋值检查（避免资源释放导致数据丢失）
	if (this == srcR) return;  // 防止自赋值[7,8](@ref)

	// 2. 释放当前对象资源（尤其动态内存）
	S.clear();  // 清空状态向量
	V.clear();  // 清空值向量（若含张量则需额外释放内存）

	// 3. 复制基本属性
	T = srcR->T;         // 数据类型（_sint_/_uint_等）
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
		case _uint_:
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
	case _uint_:
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
void ConstObj::assign(size_t No, const ConstObj* srcR)
{
	if (!srcR) return;  // 空指针检查[1](@ref)
	if (No >= V.count()) return; // 越界检查
	if (T != srcR->T) return;//
	S[No] = srcR->S[0];
	switch (T) {
	case _sint_:
		V[No].i = srcR->V[0].i;
		break;
	case _uint_:
		V[No].u = srcR->V[0].u;
		break;
	case _bool_:
		V[No].b = srcR->V[0].b;
		break;
	case _real_:
		V[No].f = srcR->V[0].f;
		break;
	case _complex_:
		if (srcR->V[0].t) 
		{
			V[0].t = NULL; 
		}
		else {
			V[0].t = NULL;
		}
		break;
	}
}


var::var(Expres::node* srcR)
{
	name = NULL;
	Scalar = true;
	//infor = NULL;
	infors.recount(1);
	infors[0] = (void*)srcR;
}
var::var()
{
	initial();
}
var::~var()
{
	free(attribute);
	attribute = NULL;
	//infor = NULL;
}
void var::ruin(void)
{
	free(attribute);
	attribute = NULL;
	//infor = NULL;
	ruinCO();
}
void var::initial(void)
{
	name = NULL;
	Scalar = true;
	//infor = NULL;
	infors.recount(1);
	infors[0] = NULL;
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
	realm = NULL;
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
	realm = NULL;
	ruinCO();
}


NetInContext::NetInContext()
{
	net = new NetWork;
	realm = NULL;
}
NetInContext::~NetInContext()
{
	ruin();
}
void NetInContext::ruin(void)
{
	delete net;
	net = NULL;
	realm = NULL;
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
		now = now->parent;
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
		now = now->parent;
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
		now = now->parent;
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

NetInContext* context::SearchNet(const char* name)const
{
	NetInContext* value = SearchNetLocal(name);
	if (value != NULL) return value;
	context* now = parent;
	while (now != NULL)
	{
		NetInContext* temp = now->SearchNetLocal(name);
		if (temp != NULL) return temp;
		now = now->parent;  // 修正了原始参考代码中的错误(原代码写的是parent->parent)
	}
	return NULL;
}
NetInContext* context::SearchNetLocal(const char* name)const
{
	for (size_t i = 0; i < nets.count(); i++) 
	{
		if (nets[i]->eqaul(name)) return nets[i];
	}
	return NULL;
}

bool context::SearchRoutine(const char* name) const
{
	NetInContext* net = SearchNet(name);
	if (net != NULL) return true;

	func* FF = searchFuncs(name);
	if (FF != NULL) return true;

	return false;
}
bool context::SearchRoutineLocal(const char* name) const
{
	NetInContext* net = SearchNetLocal(name);
	if (net != NULL) return true;

	func* FF = searchFuncsLocal(name);
	if (FF != NULL) return true;

	return false;
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

IDinfor::IDinfor()
{
	scalar = true;
	index = 0;
	backup = NULL;
}
IDinfor::~IDinfor()
{
}
int IDinfor::build(const lex& eme, GTNode* ID, BuildInfor* infor, context* dst)
{
	backup = ID;
	const char* temp = NULL;
	GTNode* Def = ID->child(0);
	if (!Def->root().rules)
		temp = eme.GetWord(Def->root().site);
	SetName(temp);

	NetG::nonterminal TTTT = (NetG::nonterminal)NetG::RulesToSymbol[ID->root().site];
	if (TTTT != NetG::nonterminal::_ID_)
	{
		infor->errorInfor1 = ID->root().site;
		infor->ErrorNode = ID;
		infor->errorCode = BuildInfor::WrongEntrance;
		return 534663456;
	}

	NetG::rules RR = (NetG::rules)ID->root().site;
	scalar = (RR == NetG::rules::ID_single_);
	size_t line = ID->child(0)->root().site;


	index = 0;
	if (!scalar)
	{
		ConstObj* Const_ = NULL;
		int error = infor->GetAConst(Const_, eme, ID->child(1)->child(1), dst);
		if (error != 0) return error;
		if (!Const_->SorUint())
		{
			infor->errorInfor1 = line;
			infor->ErrorNode = ID;
			infor->errorCode = BuildInfor::ErrorNeedAInt;
			return 1234234;
		}
		sint temp = Const_->GetSint();
		if (temp < 0)
		{
			infor->errorInfor1 = line;
			infor->errorInfor2 = temp;
			infor->ErrorNode = ID;
			infor->errorCode = BuildInfor::ErrorMinusIndex;
			return 1234267;
		}
		delete Const_;
		index = temp;
	}
	else index = 0;
	return 0;
}
var* IDinfor::GetLocalVarR(int& error, BuildInfor* infor, context* dst)
{
	var* temp = dst->SearchLocal(GetName());
	if (temp == NULL) return temp;
	if (scalar != temp->scalar())
	{
		infor->errorCode = BuildInfor::ErrorSAmissMatch;
		infor->ErrorNode = backup;
		error = 326785342;
		return NULL;
	}
	size_t Index = GetIndex();
	if (Index >= temp->count())
	{
		infor->errorCode = BuildInfor::ErrorIndexOutofRange;
		infor->ErrorNode = backup;
		error = 123134545;
		return NULL;
	}
	if (temp->Getnode(Index) == NULL)
	{
		infor->errorCode = BuildInfor::ErrorMissingVarDef;
		infor->ErrorNode = backup;
		error = 123134545;
		return  NULL;
	}
	return temp;
}
void* IDinfor::GetLocalTensorR(int& error, BuildInfor* infor, context* dst)
{
	var* temp = dst->SearchLocal(GetName());
	if (temp == NULL) return temp;
	if (scalar != temp->scalar())
	{
		infor->errorCode = BuildInfor::ErrorSAmissMatch;
		infor->ErrorNode = backup;
		error = 326785342;
		return NULL;
	}
	size_t Index = GetIndex();
	if (Index >= temp->count())
	{
		infor->errorCode = BuildInfor::ErrorIndexOutofRange;
		infor->ErrorNode = backup;
		error = 123134545;
		return NULL;
	}
	if (temp->Getnode(Index) == NULL)
	{
		infor->errorCode = BuildInfor::ErrorMissingVarDef;
		infor->ErrorNode = backup;
		error = 123134545;
		return  NULL;
	}
	return temp->Getnode(Index);
}
ConstObj* IDinfor::GetAllConstR(int& error, BuildInfor* infor, context* dst)
{
	ConstObj* temp = dst->searchConst(GetName());
	if (temp == NULL) return temp;
	if (scalar != temp->GetScalar())
	{
		infor->errorCode = BuildInfor::ErrorSAmissMatch;
		infor->ErrorNode = backup;
		error = 326785342;
		return NULL;
	}
	size_t Index = GetIndex();
	if (Index >= temp->GetDim())
	{
		infor->errorCode = BuildInfor::ErrorIndexOutofRange;
		infor->ErrorNode = backup;
		error = 123134545;
		return NULL;
	}
	if (temp->GetState(Index) == ConstObj::liberal)
	{
		infor->errorCode = BuildInfor::ErrorMissingConstVarDef;
		infor->ErrorNode = backup;
		error = 123134546;
		return  NULL;
	}
	return temp;
}
bool IDinfor::CheckType(int& error, BuildInfor* infor)const
{
	if (!scalar && index == 0)
	{
		infor->errorCode = BuildInfor::VarAlreadDef;
		infor->ErrorNode = backup;
		error = 128931231;
		return true;
	}
	return false;
}
var* IDinfor::SetVarL(int& error, BuildInfor* infor, context* dst, const char* attri)
{
	size_t dim = GetDim();
	const char* name = GetName();
	if (CheckType(error, infor)) return NULL;
	var* old = dst->search(name);
	ConstObj* oldC = dst->searchConst(name);
	if (old != NULL || oldC != NULL)
	{
		infor->errorCode = BuildInfor::VarAlreadDef;
		infor->ErrorNode = backup;
		error = 234789433;
		return NULL;
	}
	var* newVar = new var;
	newVar->SetName(name);
	if (attri != NULL)newVar->SetAttri(attri);

	if (!scalar)
	{
		newVar->SetCount(dim);
	}
	dst->global.append(newVar);
	return newVar;
}
ConstObj* IDinfor::SetConstL(int& error, BuildInfor* infor, context* dst, ConstObj::type TTT)
{
	size_t dim = GetDim();
	const char* name = GetName();
	if (CheckType(error, infor)) return NULL;
	var* old = dst->search(name);
	ConstObj* oldC = dst->searchConst(name);
	if (old != NULL || oldC != NULL)
	{
		infor->errorCode = BuildInfor::VarAlreadDef;
		infor->ErrorNode = backup;
		error = 23494453;
		return NULL;
	}

	ConstObj* newVar = new ConstObj(dim, scalar, TTT, name);
	dst->Cobj.append(newVar);
	return newVar;
}
void IDinfor::AssignLocalVarL(int& error, BuildInfor* infor, context* dst, void* SrcR)
{
	size_t index = GetIndex();
	const char* name = GetName();
	var* old = dst->SearchLocal(name);
	if (old == NULL)
	{
		infor->errorCode = BuildInfor::ErrorMissingVarDef;
		infor->ErrorNode = backup;
		error = 234789433;
		return;
	}
	if (index >= old->count())
	{
		infor->errorCode = BuildInfor::ErrorIndexOutofRange;
		infor->ErrorNode = backup;
		error = 123134545;
		return;
	}
	if (SrcR != NULL)
		old->SetInfor(SrcR, index);
	else
	{
		infor->errorCode = BuildInfor::ErrorInvalidRvalue;
		infor->ErrorNode = backup;
		error = 3282343234;
	}
	return;
}
var* IDinfor::GetLocalVarL(int& error, BuildInfor* infor, context* dst)
{
	size_t index = GetIndex();
	const char* name = GetName();
	var* old = dst->SearchLocal(name);
	if (old == NULL)
	{
		infor->errorCode = BuildInfor::ErrorMissingVarDef;
		infor->ErrorNode = backup;
		error = 234789433;
		return NULL;
	}
	if (old->compareAttri("para") || old->compareAttri("input"))
	{
		infor->errorCode = BuildInfor::AssignAparaOrinput;
		infor->ErrorNode = backup;
		error = 2432235343;
		return NULL;
	}
	if (index >= old->count())
	{
		infor->errorCode = BuildInfor::ErrorIndexOutofRange;
		infor->ErrorNode = backup;
		error = 123134545;
		return NULL;
	}
	return old;
}
var* IDinfor::GetLocalTensorL(int& error, BuildInfor* infor, context* dst)
{
	size_t index = GetIndex();
	const char* name = GetName();
	var* old = dst->SearchLocal(name);
	if (old == NULL)
	{
		infor->errorCode = BuildInfor::ErrorMissingVarDef;
		infor->ErrorNode = backup;
		error = 234789433;
		return NULL;
	}
	if (!old->compareAttri("para") && !old->compareAttri("input"))
	{
		infor->errorCode = BuildInfor::AssignAparaOrinput;
		infor->ErrorNode = backup;
		error = 2432235343;
		return NULL;
	}
	if (index >= old->count())
	{
		infor->errorCode = BuildInfor::ErrorIndexOutofRange;
		infor->ErrorNode = backup;
		error = 123134545;
		return NULL;
	}
	if (old->GetTensor(index) != NULL)
	{
		infor->errorCode = infor->ErrorRepeatVarDef;
		infor->ErrorNode = backup;
		error = 123134546;
		return NULL;
	}
	return old;
}
ConstObj* IDinfor::GetLocalConstL(int& error, BuildInfor* infor, context* dst)
{
	size_t index = GetIndex();
	const char* name = GetName();
	ConstObj* old = dst->SearchConstLocal(name);
	if (old == NULL)
	{
		infor->errorCode = BuildInfor::ErrorMissingConstVarDef;
		infor->ErrorNode = backup;
		error = 237894345;
		return NULL;
	}
	if (index >= old->GetDim())
	{
		infor->errorCode = BuildInfor::ErrorIndexOutofRange;
		infor->ErrorNode = backup;
		error = 121343245;
		return NULL;
	}
	return old;
}


#include<string.h>
Indexs::Indexs()
{
}
Indexs::~Indexs()
{
	for (size_t i = 0; i < Tindex.count(); i++)
	{
		free(Tindex[i]);
	}
	Tindex.clear();
}
char* Indexs::copy(const char* src) const
{
	char* dst = (char*)malloc(strlen(src) + 1);
	if (dst == NULL)
	{
		return NULL;
	}
	strcpy(dst, src);
	return dst;
}
void Indexs::append(const lex& eme, GTNode* ID2, BuildInfor* infor, context* dst)
{
	if (ID2 == NULL) return;
	NetG::rules Rule = (NetG::rules)ID2->root().site;
	if (Rule == NetG::rules::ID2_yes_)
	{
		GTNode* id = ID2->child(0);
		const char* name = eme.GetWord(id->root().site);
		char* newName = copy(name);
		Tindex.append(newName);
		return;
	}
	else
	{
		Tindex.append(NULL);
	}
}
int Indexs::buildSQ_INDEXUNITS(const lex& eme, GTNode* SQ_INDEXUNITS, BuildInfor* infor, context* dst)
{
	NetG::nonterminal NT = (NetG::nonterminal)NetG::RulesToSymbol[SQ_INDEXUNITS->root().site];
	if (NT != NetG::_SQ_INDEXUNITS_)
	{
		infor->errorInfor1 = SQ_INDEXUNITS->root().site;
		infor->ErrorNode = SQ_INDEXUNITS;
		infor->errorCode = BuildInfor::WrongEntrance;
		return 245324453;
	}
	GTNode* INDEXUNITS = SQ_INDEXUNITS->child(2);
	return buildINDEXUNITS(eme, INDEXUNITS, infor, dst);
}
int Indexs::buildINDEXLIST(const lex& eme, GTNode* INDEXLIST, BuildInfor* infor, context* dst)
{
	NetG::nonterminal NT = (NetG::nonterminal)NetG::RulesToSymbol[INDEXLIST->root().site];
	if (NT != NetG::_INDEXLIST_)
	{
		infor->errorInfor1 = INDEXLIST->root().site;
		infor->ErrorNode = INDEXLIST;
		infor->errorCode = BuildInfor::WrongEntrance;
		return 24534453;
	}
	GTNode* INDEXUNITS = INDEXLIST->child(1);
	return buildINDEXUNITS(eme, INDEXUNITS, infor, dst);
}
int Indexs::buildINDEXUNITS(const lex& eme, GTNode* INDEXUNITS, BuildInfor* infor, context* dst)
{
	NetG::nonterminal NT = (NetG::nonterminal)NetG::RulesToSymbol[INDEXUNITS->root().site];
	if (NT != NetG::_INDEXUNITS_)
	{
		infor->errorInfor1 = INDEXUNITS->root().site;
		infor->ErrorNode = INDEXUNITS;
		infor->errorCode = BuildInfor::WrongEntrance;
		return 24522343;
	}
	GTiterator iterator;
	iterator.initial(INDEXUNITS);
	while (iterator.still())
	{
		GTNode* GT = iterator.target();
		if (iterator.state() == 1)
		{
			NetG::rules Rule = (NetG::rules)GT->root().site;
			switch (Rule)
			{
			case Pikachu::NetG::INDEXUNITS_single_:
			{
				GTNode* ID2 = GT->child(0);
				if (ID2 == NULL) return 4353; // 安全检查
				append(eme, ID2, infor, dst);
				break;
			}
			case Pikachu::NetG::INDEXUNITS_multi_:
			{
				GTNode* ID2 = GT->child(1);
				if (ID2 == NULL) return 4353; // 安全检查
				append(eme, ID2, infor, dst);
				break;
			}
			}
		}
		iterator.next();
	}
	return 0;
}
int Indexs::buildSUMSYMBOL(const lex& eme, GTNode* SUMSYMBOL, BuildInfor* infor, context* dst)
{
	NetG::rules RR = (NetG::rules)SUMSYMBOL->root().site;
	if (RR == NetG::rules::SUMSYMBOL_multi_)
	{
		GTNode* INDEXUNITS = SUMSYMBOL->child(2);
		if (INDEXUNITS == NULL) return 234535345; // 安全检查
		return buildINDEXUNITS(eme, INDEXUNITS, infor, dst);
	}
	else if (RR == NetG::rules::SUMSYMBOL_single_)
	{
		GTNode* id = SUMSYMBOL->child(1);
		size_t site = id->root().site;
		const char* ID = eme.GetWord(site);
		Tindex.append(copy(ID));
		return 0;
	}
	else
	{
		infor->errorInfor1 = SUMSYMBOL->root().site;
		infor->ErrorNode = SUMSYMBOL;
		infor->errorCode = BuildInfor::WrongEntrance;
		return 245234453;
	}
	
}

TensorID::TensorID()
{
}
TensorID::~TensorID()
{
	for (size_t i = 0; i < Tindex.count(); i++)
	{
		free(Tindex[i]);
	}
	Tindex.clear();
}
int TensorID::build(const lex& eme, GTNode* TENSORID, BuildInfor* infor, context* dst)
{
	GTNode* ID = TENSORID->child(0);
	int error = IDinfor::build(eme, ID, infor, dst);
	if (error != 0)
	{
		return error;
	}
	NetG::rules RR = (NetG::rules)TENSORID->root().site;
	if (RR != NetG::rules::INDEXLIST_INDEXLIST_)
	{
		infor->errorInfor1 = TENSORID->root().site;
		infor->ErrorNode = TENSORID;
		infor->errorCode = BuildInfor::WrongEntrance;
		return 245234453;
	}
	GTNode* INDEXLIST = TENSORID->child(1);
	GTNode* INDEXUNITS = INDEXLIST->child(1);

	Indexs indexss;
	error = indexss.buildINDEXUNITS(eme, INDEXUNITS, infor, dst);
	if (error != 0)
	{
		return error;
	}
	for (size_t i = 0; i < indexss.GetCount(); i++)
	{
		append(indexss[i]);
	}
	return 0;
}
char* TensorID::copy(const char* src) const
{
	char* dst = (char*)malloc(strlen(src) + 1);
	if (dst == NULL)
	{
		return NULL;
	}
	strcpy(dst, src);
	return dst;
}
void TensorID::append(const char* src)
{
	char* newName = copy(src);
	if (newName != NULL)
	{
		Tindex.append(newName);
	}
}
void TensorID::append(const lex& eme, GTNode* ID2, BuildInfor* infor, context* dst)
{
	if (ID2 == NULL) return;
	NetG::rules Rule = (NetG::rules)ID2->root().site;
	if (Rule == NetG::rules::ID2_yes_)
	{
		GTNode* id = ID2->child(0);
		const char* name = eme.GetWord(id->root().site);
		char* newName = copy(name);
		Tindex.append(newName);
		return;
	}
	else
	{
		Tindex.append(NULL);
	}
}

ValueList::ValueList()
{
	backup = NULL;
	scalar = true;
}
ValueList::~ValueList()
{
	for (size_t i = 0; i < values.count(); i++)
	{
		delete values[i];
	}
	values.clear();
}

int ValueList::buildSA(const lex& eme, GTNode* VALUE, BuildInfor* infor, context* dst)
{
	Pikachu::NetG::rules RRR = (Pikachu::NetG::rules)VALUE->root().site;
	if (RRR == Pikachu::NetG::VALUE_single_)
	{
		scalar = true;
		backup = VALUE;
		GTNode* EXP_RIGHT = VALUE->child(0);
		ConstObj* output = NULL;
		int error = infor->GetAConst(output, eme, EXP_RIGHT, dst);
		if (error != 0) return error;
		values.append(output);
		return 0;
	}
	else
		return build(eme, VALUE, infor, dst); // 调用build函数处理多值列表
}
int ValueList::build(const lex& eme, GTNode* VALUELIST, BuildInfor* infor, context* dst)
{
	backup = VALUELIST;
	scalar = false;
	GTNode* ID = VALUELIST->child(0);
	NetG::rules RR = (NetG::rules)VALUELIST->root().site;
	if (RR != NetG::rules::VALUELIST_VALUELIST_)
	{
		infor->errorInfor1 = VALUELIST->root().site;
		infor->ErrorNode = VALUELIST;
		infor->errorCode = BuildInfor::WrongEntrance;
		return 245234453;
	}
	GTNode* EXP_RIGHT = VALUELIST->child(0);
	ConstObj* output = NULL;
	int error = infor->GetAConst(output, eme, EXP_RIGHT, dst);
	if (error != 0)
	{
		return error;
	}
	values.append(output); // 将ConstObj添加到values向量中
	GTNode* VALUES = VALUELIST->child(1);
	if (VALUES == NULL) return 4353; // 安全检查
	for (size_t i = 0; i < VALUES->ChildCount(); i++)
	{
		EXP_RIGHT = VALUES->child(i)->child(1);
		output = NULL;
		int error = infor->GetAConst(output, eme, EXP_RIGHT, dst);
		if (error != 0 || output == NULL)
		{
			return error;
		}
		values.append(output);
	}
	ConstObj::type TTT = GetType(); // 默认类型为整型
	for (size_t i = 0; i < values.count(); i++)
	{
		if (values[i]->GetType() != TTT)
		{
			infor->errorCode = BuildInfor::ErrorListTypeMismatch; // 类型不匹配错误
			infor->errorInfor1 = i; // 错误索引
			infor->ErrorNode = VALUELIST; // 错误节点
			return 43535; // 返回错误代码
		}
	}
	return 0;
}
void ValueList::append(ConstObj* srcR)
{
	if (srcR == NULL) return; // 安全检查
	values.append(srcR); // 添加到值列表中
}
int ValueList::checkInt(BuildInfor* infor) const
{
	if (GetType() != ConstObj::_sint_ && GetType() != ConstObj::_uint_)
	{
		infor->errorCode = BuildInfor::ErrorListTypeMismatch; // 类型不匹配错误
		infor->ErrorNode = backup; // 错误节点（可选）
		return 43535; // 返回错误代码
	}
	return 0;
}
int ValueList::checkIndex(BuildInfor* infor) const
{
	if (GetType() != ConstObj::_sint_ && GetType() != ConstObj::_uint_)
	{
		infor->errorCode = BuildInfor::ErrorListTypeMismatch; // 类型不匹配错误
		infor->ErrorNode = backup; // 错误节点（可选）
		return 43535; // 返回错误代码
	}
	if (GetType() == ConstObj::_sint_)
	{
		for (size_t i = 0; i < values.count(); i++)
		{
			if (values[i]->GetInt() < 0L)
			{
				infor->errorCode = BuildInfor::ErrorMinusIndex; // 负索引错误
				infor->ErrorNode = backup; // 错误节点
				return 1745227867; // 返回错误代码
			}
		}
	}
	return 0;
}
int ValueList::checkDim(BuildInfor* infor) const
{
	if (GetType() != ConstObj::_sint_ && GetType() != ConstObj::_uint_)
	{
		infor->errorCode = BuildInfor::ErrorListTypeMismatch; // 类型不匹配错误
		infor->ErrorNode = backup; // 错误节点（可选）
		return 43535; // 返回错误代码
	}
	for (size_t i = 0; i < values.count(); i++)
	{
		if (values[i]->GetInt() < 1LL)
		{
			infor->errorCode = BuildInfor::ErrorMinusIndex; // 负索引错误
			infor->ErrorNode = backup; // 错误节点
			return 1745227867; // 返回错误代码
		}
	}
	return 0;
}
void ValueList::demo(FILE* fp = stdout) const
{
	fprintf(fp, "ValueList: %s\n", backup ? "backup->GetName()" : "NULL");
	fprintf(fp, "Scalar: %s\n", scalar ? "true" : "false");
	fprintf(fp, "Values count: %zu\n", values.count());
	for (size_t i = 0; i < values.count(); i++)
	{
		if (values[i])
			values[i]->demo(fp);
		else
			fprintf(fp, "Value[%zu]: NULL\n", i);
	}
}
void ValueList::GetDim(vector<size_t>& dst) const
{
	for (size_t i = 0; i < values.count(); i++)
	{
		if (values[i])
		{
			size_t dim = values[i]->GetInt();
			dst.append(dim);
		}
		else
		{
			dst.append(0); // 如果值为NULL，添加0维度
		}
	}
}

static bool compare(const char* str1, const char* str2)
{
	size_t i;
	for (i = 0; (str1[i] != '\0') && (str1[i] == str2[i]); i++);
	return str1[i] == str2[i];
}


/*
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
*/