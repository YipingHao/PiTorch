#include"../src/header/Pikachu.h"
#include"../extern/header/all.h"
#include "../header/parser.h"
#include "../header/sheet.h"
using namespace Pikachu;
static bool compare(const char* str1, const char* str2);




BuildInfor::BuildInfor()
{
	PrintScreen = false;
	screen = stdout;
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
		if (PrintScreen)
			fprintf(screen, "Error PretreatOpenfail: \n");
			
		return 445624;
	}
	int error = output.Build<NetPreL>(fp);
	output.append(input);
	if (error != 0)
	{
		errorInfor1 = output.FileCount();
		errorCode = PretreatLEXICAL;
		if (PrintScreen)
			fprintf(screen, "Error in pretreatment: %d\n", error);
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

	//clear();
	//initial();
	if (PrintScreen)
	{
		fprintf(screen, "BuildInfor::build: begin: %s\n", FileName);
	}
	error = pretreatment(FileName, MorphemePre);
	
	if (PrintScreen)
	{
		fprintf(screen, "BuildInfor::build: pretreatment end.\n");
		if (error != 0)
		{
			fprintf(screen, "pretreatment error: %d\n", error);
			MorphemePre.Demo(screen);
			return error;
		}
	}
	error = LexicalSource.Build<NetL>(MorphemePre);
	if (error != 0)
	{
		errorCode = ErrorinputLEXICAL;
		if (PrintScreen)
		{
			MorphemePre.Demo(screen);
			fprintf(screen, "ErrorinputLEXICAL: % d\n", error);
		}
		return error;
	}
	if (PrintScreen) fprintf(screen, "BuildInfor::build: lexical end.\n");
	if (PrintScreen)
	{
		fprintf(screen, "BuildInfor::build: lexical end.\n");
	}
	NeglectNullToken(LexicalSource);
	if (PrintScreen)
	{
		fprintf(screen, "BuildInfor::build: NeglectNullToken end.\n");
	}
	//eme.Demo(stdout);
	error = buildGanalysis(LexicalSource, dst);
	if (PrintScreen)
	{
		fprintf(screen, "BuildInfor::build: buildGanalysis end.\n");

	}
	if (error != 0)
	{
		errorCode = ErrorinputGrammar;
		if (PrintScreen) fprintf(screen, "ErrorinputGrammar: %d\n", error);
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
	if (PrintScreen)
	{
		fprintf(screen, "ErrorinputGrammar: %d\n", error);
		ASTree->Demo(screen, eme, NetG::RulesName);
	}
	if (error != 0)
	{
		errorCode = ErrorinputGrammar;
		errorInfor1 = ASTree->error_record01;
		errorInfor2 = ASTree->error_record02;
		
		return error;
	}
	if (PrintScreen)
	{
		fprintf(screen, "ASTree->build<NetG>(eme) end.\n");
	}
	error = buildAll(eme, *ASTree, dst);
	if (PrintScreen)
	{
		fprintf(screen, "buildAll(eme, *ASTree, dst) end.\n");
	}
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
					if (PrintScreen)
					{
						fprintf(screen, "\t buildSymbolic begin\n");
					}
					error = buildSymbolic(eme, SYMBOLIC, dst);
					if (PrintScreen)
					{
						func* Func = dst->funcs.top();
						fprintf(screen, "\tbuildSymbolic %s end: %d\n", Func->GetName(), error);
						Func->Exp->demo(screen);
					}
					break;
				}
				case Pikachu::NetG::DEF_network_:
				{
					GTNode* NETWORK = GT->child(0);
					iterator.state() = 1;
					if (PrintScreen)
					{
						fprintf(screen, "\t buildNet begin\n");
					}
					error = buildNet(eme, NETWORK, dst);
					if (PrintScreen)
					{
						fprintf(screen, "\t buildNet end: %d\n", error);
					}
					break;
				}
				case Pikachu::NetG::DEF_def_:
				{
					GTNode* CONSTVAR = GT->child(0);
					iterator.state() = 1;
					if (PrintScreen)
					{
						fprintf(screen, "\t buildConstObj begin\n");
					}
					error = buildConstObj(eme, CONSTVAR, dst);
					if (PrintScreen)
					{
						fprintf(screen, "\t buildConstObj end: %d, obj:", error);
						ConstObj* obj = dst->Cobj.top();
						obj->demo(screen);
						fprintf(screen, "\n\n");
					}
					break;
				}
				case Pikachu::NetG::DEF_exp_:
				{
					GTNode* GTarget = GT;
					iterator.state() = 1;
					if (PrintScreen)
					{
						fprintf(screen, "\t buildExp begin\n");
					}
					error = buildExp(eme, GTarget, dst);
					if (PrintScreen)
					{
						fprintf(screen, "\t buildExp end: %d\n", error);
					}
					break;
				}
				case Pikachu::NetG::DEF_diff_:
				{
					GTNode* GTarget = GT->child(0);
					iterator.state() = 1;
					if (PrintScreen)
					{
						fprintf(screen, "\t buildDiff begin\n");
					}
					error = buildDiff(eme, GTarget, dst);
					if (PrintScreen)
					{
						
						fprintf(screen, "\t buildDiff end: %d\n", error);
					}
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


int BuildInfor::GetAConst(ConstObj*& output, const lex& eme, GTNode* EXP_RIGHT, context* dst)
{
	GTiterator iterator;
	int error = 0;
	output = NULL;
	iterator.initial(EXP_RIGHT);

	NetG::nonterminal RRR = (NetG::nonterminal)NetG::RulesToSymbol[EXP_RIGHT->root().site];
	if (RRR != NetG::nonterminal::_EXP_RIGHT_)
	{
		errorInfor1 = EXP_RIGHT->root().site;
		errorCode = WrongEntrance;
		ErrorNode = EXP_RIGHT;
		return 12321;
	}
	while (iterator.still())
	{
		GTNode* GT = iterator.target();
		NetG::rules RR1 = (NetG::rules)GT->root().site;
		//printf("RR1: %d, %d\n", RR1, iterator.state());
		if (iterator.state() == 1 && GT->root().rules)
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
			default:
			{
				errorCode = ErrorUnKnowEXP;
				errorInfor1 = GT->root().site;
				error = 12213312;
				ErrorNode = GT;
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
	ConstObj* target = (ConstObj*)(EXP_RIGHT->root().infor);
	output = target;
	EXP_RIGHT->root().infor = NULL;
	iterator.initial(EXP_RIGHT);
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
			//printf("hsfhsdfg\n");
			error = id.build(eme, ID, this, dst);
			if (error != 0) return error;
			//printf("15646dfg\n");
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
	if(PrintScreen)
	{
		fprintf(screen, "\t\tbuildConstObj: %s, type: %s, dim: %d, is scalar: %d\n",
			obj->GetName(), ConstObj::TypeName(TT), obj->GetDim(), obj->GetScalar());
	}
	if (RR == Pikachu::NetG::CONSTVAR_def1_) return error;

	ValueList valueList;
	GTNode* VALUE = CONSTVAR->child(3);
	error = valueList.buildSA(eme, VALUE, this, dst);
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
	//valueList.demo();
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
	size_t line = GTarget->child(0)->root().site;


	GTNode* ID = GTarget->child(0);//exp: ID assign EXP_RIGHT semicolon;
	IDinfor id;
	error = id.build(eme, ID, this, dst);
	if (error != 0) return error;
	ConstObj* obj = id.GetLocalConstL(error, this, dst);
	if (error != 0) return error;

	GTNode* EXP_RIGHT = GTarget->child(2);//exp: ID assign EXP_RIGHT semicolon;
	ConstObj* srcR = NULL;
	error = GetAConst(srcR, eme, EXP_RIGHT, dst);
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
	printf("buildRoutinePara: %d, %d\n", Rou, count);
	for (size_t i = 0; i < count; i += 2)
	{
		GTNode* SYMBOLICPARA = PARA->child(i);
		GTNode* ID = SYMBOLICPARA->child(1);
		IDinfor id;
		printf("%zu, %zu\n", i, count);
		error = id.build(eme, ID, this, dst);
		printf("%zu, %zu\n", i, count);
		if (error != 0) return error;
		printf("%zu, %zu\n", i, count);
		const char* attri = eme.GetWord(SYMBOLICPARA->child(0)->root().site);
		printf("%zu, %s\n", i, attri);
		var* newVar = id.SetVarL(error, this, dst, attri);
		printf("%zu, %zu\n", i, count);
		if (error != 0) return error;
		size_t dim = newVar->count();
		printf("%zufgdgsdg  %zu\n", i, count);
		if (Rou != routine::expression) continue;
		NetG::rules TypePara = (NetG::rules)SYMBOLICPARA->root().site;

		func* Func = dst->funcs.top();
		Expres* Exp = Func->Exp;
		printf("%zu, %zu\n", i, count);
		switch (TypePara)
		{
		case Pikachu::NetG::SYMBOLICPARA_input_:
		{
			//newVar->SetAttri("input");
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
			//newVar->SetAttri("para");
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
			//newVar->SetAttri("output");
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
	if (Func->InputCount != 1)
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
	if (Func->OutputCount != 1)
	{
		ErrorNode = SYMBOLIC;
		errorCode = NoneOutput;
		return 79858736;
	}
	Expres* Exp = Func->Exp;
	for (size_t i = 0; i < dst->global.count(); i++)
	{
		var* temp = dst->global[i];
		if (temp->compareAttri("output"))
		{
			if (temp->IfAlldefine())
			{
				ErrorNode = SYMBOLIC;
				errorCode = UndefineOutput;
				return 893534346;
			}
			for (size_t j = 0; j < temp->count(); j++)
			{
				Exp->OutputAppend(temp->Getnode(j));
			}
			if (Exp->OutputAmount() != temp->count())
			{
				ErrorNode = SYMBOLIC;
				errorCode = ErrorSelfCheck;
				return 893534346;
			}
		}
		else if (temp->compareAttri("para"))
		{
			Exp->SetParameterCount(temp->count());
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
	if(PrintScreen) fprintf(screen, "\t\t name:%s\n", Func->GetName());
	GTNode* PARA = SYMBOLIC->child(3);
	error = buildRoutinePara(routine::expression, eme, PARA, subcontext);
	fprintf(screen, "\t\t name:%s\n", Func->GetName());
	if (error != 0) return error;
	if (PrintScreen)
	{
		for (size_t i = 0; i < subcontext->global.count(); i++)
		{
			var* TempP = subcontext->global[i];
			TempP->demo(screen, 3);
		}
	}
	GTNode* SYMBOLICBODY = SYMBOLIC->child(6);
	error = buildSymbolicBody(eme, PARA, subcontext, Func);
	fprintf(screen, "\t\t buildSymbolicBody begin\n");
	
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
				return 893434345;
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
					return 893454346;
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
	NetWork* net = Net->net;
	NetG::nonterminal TTTT = (NetG::nonterminal)NetG::RulesToSymbol[NET_STATEMENT->root().site];
	if (TTTT != NetG::nonterminal::_NET_STATEMENT_)
	{
		errorInfor1 = line;
		ErrorNode = NET_STATEMENT;
		errorCode = BuildInfor::WrongEntrance;
		return 5343456;
	}
	GTNode* TENSOR = NET_STATEMENT->child(0);
	GTNode* VALUELIST = TENSOR->child(2);

	ValueList VL;
	error = VL.build(eme, VALUELIST, this, dst);
	if (error != 0) return error;
	error = VL.checkDim(this);// dim[i] mast >= 1
	if (error != 0) return error;
	vector<size_t> dims;
	VL.GetDim(dims);

	GTNode* TENSOR_ID = NET_STATEMENT->child(1);
	TensorID id;
	error = id.build(eme, TENSOR_ID, this, dst);
	if (error != 0) return error;
	var* Lvalue = id.GetLocalVarL(error, this, dst);
	if (error != 0) return error;

	GTNode* TENSORVALUE = NET_STATEMENT->child(3);
	NetG::rules RR = (NetG::rules)TENSORVALUE->root().site;
	GTNode* TENSORID;
	Node* newNode = NULL;
	switch (RR)
	{
	case Pikachu::NetG::TENSORVALUE_single_:
	case Pikachu::NetG::TENSORVALUE_single1_:
	{
		error = buildTENSORsingle(newNode, dims, id, eme, TENSORVALUE, Net);
		if (error != 0) return error;
		break;
	}
	case Pikachu::NetG::TENSORVALUE_multi_:
	{
		error = buildTENSORmulti(newNode, dims, id, eme, TENSORVALUE, Net);
		if (error != 0) return error;
		break;
	}
	case Pikachu::NetG::TENSORVALUE_singleF_:
	{
		error = buildTENSORsingleF(newNode, dims, id, eme, TENSORVALUE, Net);
		if (error != 0) return error;
		break;
	}
	case Pikachu::NetG::TENSORVALUE_multiF_:
	{
		error = buildTENSORmultiF(newNode, dims, id, eme, TENSORVALUE, Net);
		if (error != 0) return error;
		break;
	}
	default: 
	{
		errorCode = WrongEntrance;
		errorInfor1 = line;
		ErrorNode = TENSORVALUE;
		return 4237895342;
	}
		
	}
	Lvalue->SetInfor((void*)newNode, id.GetIndex());
	//id.AssignLocalVarL(error, this, dst, newNode);
	return error;
}
Node::OpType BuildInfor::ParseOpType(const lex& eme, GTNode* OPERATOR)
{
	NetG::nonterminal TTTT = (NetG::nonterminal)NetG::RulesToSymbol[OPERATOR->root().site];
	if (TTTT != NetG::nonterminal::_OPERATOR_)
	{
		hyperlex::dictionary* error = new hyperlex::dictionary;
		error->append("error", "TTTT != NetG::nonterminal::_OPERATOR_");
		throw error;
	}
	GTNode* Node_ = OPERATOR->child(0);
	const char* Op = eme.GetWord(Node_->root().site);
	return Node::ParseOpType(Op);
}

int BuildInfor::buildTENSORsingle(Node*& newNode, const vector<size_t>& dims, TensorID& id,\
	const lex& eme, GTNode* TENSORVALUE, NetInContext* Net)
{
	NetG::rules RR = (NetG::rules)TENSORVALUE->root().site;
	size_t line = TENSORVALUE->root().site;
	size_t delta = (RR == NetG::TENSORVALUE_single1_ ? 1 : 0);
	if (RR != NetG::TENSORVALUE_single_ && RR != NetG::TENSORVALUE_single1_)
	{
		errorCode = WrongEntrance;
		errorInfor1 = line;
		ErrorNode = TENSORVALUE;
		return 97895342;
	}
	context* dst = Net->realm;
	NetWork* net = Net->net;

	GTNode* TENSORID = TENSORVALUE->child(1 + delta);
	TensorID idL;
	int error = idL.build(eme, TENSORID, this, dst);
	if (error != 0) return error;
	Node* srcL = (Node*)idL.GetLocalTensorR(error, this, dst);
	if (error != 0) return error;

	GTNode* SUMSYMBOL = TENSORVALUE->child(delta);
	Indexs list;
	error = list.buildSUMSYMBOL(eme, SUMSYMBOL, this, dst);
	if (error != 0) return error;

	double alpha = 1.0;

	if (RR == NetG::TENSORVALUE_single1_)
	{
		GTNode* EXP_RIGHT = TENSORVALUE->child(0);
		ConstObj* Alpha = NULL;
		error = GetAConst(Alpha, eme, EXP_RIGHT, dst);
		if (error != 0) return error;
		alpha = Alpha->GetReal();
		delete Alpha;
	}

	indiceIS IS;
	IS.appendS(id.GetSIndex());
	IS.appendS(list.GetIndex());
	IS.appendS(idL.GetSIndex());
	IS.StoI();


	newNode = net->NewNodeMonoLinear(dims, srcL, alpha, IS);
	if (newNode == NULL)
	{
		errorCode = ErrorUnsupportType;
		errorInfor1 = line;
		ErrorNode = TENSORID;
		return 4245341;
	}
	return error;
}
int BuildInfor::buildTENSORmulti(Node*& newNode, const vector<size_t>& dims, TensorID& id, \
	const lex& eme, GTNode* TENSORVALUE, NetInContext* Net)
{
	NetG::rules RR = (NetG::rules)TENSORVALUE->root().site;
	size_t line = TENSORVALUE->root().site;
	if (RR != NetG::TENSORVALUE_multi_)
	{
		errorCode = WrongEntrance;
		errorInfor1 = line;
		ErrorNode = TENSORVALUE;
		return 97192342;
	}
	context* dst = Net->realm;
	NetWork* net = Net->net;

	TensorID idL, idR;

	GTNode* TENSORID = TENSORVALUE->child(1);
	int error = idL.build(eme, TENSORID, this, dst);
	if (error != 0) return error;
	Node* srcL = (Node*)idL.GetLocalTensorR(error, this, dst);
	if (error != 0) return error;

	TENSORID = TENSORVALUE->child(3);
	error = idR.build(eme, TENSORID, this, dst);
	if (error != 0) return error;
	Node* srcR = (Node*)idR.GetLocalTensorR(error, this, dst);
	if (error != 0) return error;

	GTNode* SUMSYMBOL = TENSORVALUE->child(0);
	Indexs list;
	error = list.buildSUMSYMBOL(eme, SUMSYMBOL, this, dst);
	if (error != 0) return error;

	GTNode* OPERATOR = TENSORVALUE->child(2);
	Node::OpType OTT = ParseOpType(eme, OPERATOR);


	indiceIS IS;
	IS.appendS(id.GetSIndex());
	IS.appendS(list.GetIndex());
	IS.appendS(idL.GetSIndex());
	IS.appendS(idR.GetSIndex());
	IS.StoI();

	//Node* newNode = net->NewNodeMonoLinear(srcL);
	newNode = net->NewNodeDiLinear(dims, srcL, srcR, OTT, IS);
	if (newNode == NULL)
	{
		errorCode = ErrorUnsupportType;
		errorInfor1 = line;
		ErrorNode = TENSORID;
		return 42423341;
	}
	return error;
}
int BuildInfor::buildTENSORsingleF(Node*& newNode, const vector<size_t>& dims, TensorID& id, \
	const lex& eme, GTNode* TENSORVALUE, NetInContext* Net)
{
	NetG::rules RR = (NetG::rules)TENSORVALUE->root().site;
	size_t line = TENSORVALUE->root().site;
	if (RR != NetG::TENSORVALUE_singleF_)
	{
		errorCode = WrongEntrance;
		errorInfor1 = line;
		ErrorNode = TENSORVALUE;
		return 97192342;
	}
	context* dst = Net->realm;
	NetWork* net = Net->net;

	GTNode* TENSORID = TENSORVALUE->child(0);
	TensorID funR;
	int error = funR.BuildSingle(eme, TENSORID, this, dst);
	if (error != 0)return error;
	func* funcR = funR.GetAllFuncR(error, this, dst);
	if (error != 0)return error;

	if(funcR->ParaCount == 1)
	{
		errorCode = TooMuchPara;
		errorInfor1 = line;
		ErrorNode = TENSORID;
		return 42445341;
	}

	GTNode* SQ_INDEXUNITS = TENSORVALUE->child(1);
	Indexs listFunc;
	error = listFunc.buildSQ_INDEXUNITS(eme, SQ_INDEXUNITS, this, dst);
	if (error != 0) return error;

	TENSORID = TENSORVALUE->child(3);
	TensorID idSrcL;
	error = idSrcL.build(eme, TENSORID, this, dst);
	if (error != 0) return error;
	Node* srcL = (Node*)idSrcL.GetLocalTensorR(error, this, dst);
	if (error != 0) return error;

	indiceIS IS;
	IS.appendS(id.GetSIndex());
	IS.appendS(funR.GetSIndex());
	IS.appendS(listFunc.GetSIndex());
	IS.appendS(idSrcL.GetSIndex());
	IS.StoI();


	newNode = net->NewNodeMonoNonlinear(dims, srcL, funcR->Exp, IS);
	if (newNode == NULL)
	{
		errorCode = ErrorUnsupportType;
		errorInfor1 = line;
		ErrorNode = TENSORID;
		return 4245341;
	}
	return 0;
}
int BuildInfor::buildTENSORmultiF(Node*& newNode, const vector<size_t>& dims, TensorID& id, \
	const lex& eme, GTNode* TENSORVALUE, NetInContext* Net)
{
	NetG::rules RR = (NetG::rules)TENSORVALUE->root().site;
	size_t line = TENSORVALUE->root().site;
	if (RR != NetG::TENSORVALUE_singleF_)
	{
		errorCode = WrongEntrance;
		errorInfor1 = line;
		ErrorNode = TENSORVALUE;
		return 97192342;
	}
	context* dst = Net->realm;
	NetWork* net = Net->net;

	GTNode* TENSORID = TENSORVALUE->child(0);
	TensorID funR;
	int error = funR.BuildSingle(eme, TENSORID, this, dst);
	if (error != 0)return error;
	func* funcR = funR.GetAllFuncR(error, this, dst);
	if (error != 0)return error;
	if (funcR->ParaCount != 1)
	{
		errorCode = TooLessPara;
		errorInfor1 = line;
		ErrorNode = TENSORID;
		return 42445331;
	}

	GTNode* SQ_INDEXUNITS = TENSORVALUE->child(1);
	Indexs listFunc;
	error = listFunc.buildSQ_INDEXUNITS(eme, SQ_INDEXUNITS, this, dst);
	if (error != 0) return error;

	TensorID idSrcL, idSrcR;

	TENSORID = TENSORVALUE->child(3);
	error = idSrcL.build(eme, TENSORID, this, dst);
	if (error != 0) return error;
	Node* srcL = (Node*)idSrcL.GetLocalTensorR(error, this, dst);
	if (error != 0) return error;

	TENSORID = TENSORVALUE->child(5);
	error = idSrcR.build(eme, TENSORID, this, dst);
	if (error != 0) return error;
	Node* srcR = (Node*)idSrcR.GetLocalTensorR(error, this, dst);
	if (error != 0) return error;

	indiceIS IS;
	IS.appendS(id.GetSIndex());
	IS.appendS(funR.GetSIndex());
	IS.appendS(listFunc.GetSIndex());
	IS.appendS(idSrcL.GetSIndex());
	IS.appendS(idSrcR.GetSIndex());
	IS.StoI();


	newNode = net->NewNodeDiNonlinear(dims, srcL, srcR, funcR->Exp, IS);
	if (newNode == NULL)
	{
		errorCode = ErrorUnsupportType;
		errorInfor1 = line;
		ErrorNode = TENSORID;
		return 4245341;
	}
	
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
	int error = builder.build(FileName, this);
	if (builder.errorCode != BuildInfor::NoError)
	{
		builder.ErrorDemo();
		clear();
		initial();
	}
	S = NoError;
	return error;
}
int context::build(const char* FileName, FILE* fp)
{
	BuildInfor builder;
	//clear();
	//initial();
	builder.PrintScreen = true;
	builder.screen = fp;
	int error = builder.build(FileName, this);
	
	if (builder.errorCode != BuildInfor::NoError)
	{
		builder.ErrorDemo();
		clear();
		initial();
	}
	S = NoError;
	return error;
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

	{
		size_t delta = (RR == NetG::TENSORVALUE_single1_ ? 1 : 0);

		TENSORID = TENSORVALUE->child(1 + delta);
		TensorID idL;
		error = idL.build(eme, TENSORID, this, dst);
		if (error != 0) return error;
		Node* srcL = (Node*)idL.GetLocalTensorR(error, this, dst);
		if (error != 0) return error;

		GTNode* SUMSYMBOL = TENSORVALUE->child(delta);
		Indexs list;
		error = list.buildSUMSYMBOL(eme, SUMSYMBOL, this, dst);
		if (error != 0) return error;

		double alpha = 1.0;

		if (RR == NetG::TENSORVALUE_single1_)
		{
			GTNode* EXP_RIGHT = TENSORVALUE->child(0);
			ConstObj *Alpha = NULL;
			error = GetAConst(Alpha, eme, EXP_RIGHT, dst);
			if (error != 0) return error;
			alpha = Alpha->GetReal();
			delete Alpha;
		}

		indiceIS IS;
		IS.appendS(id.GetSIndex());
		IS.appendS(list.GetIndex());
		IS.appendS(idL.GetSIndex());
		IS.StoI();


		Node* newNode = net->NewNodeMonoLinear(dims, srcL, alpha, IS);
		if (newNode == NULL)
		{
			errorCode = ErrorUnsupportType;
			errorInfor1 = line;
			ErrorNode = TENSORID;
			return 4245341;
		}
		Lvalue->SetInfor((void*)newNode, id.GetIndex());
		break;
	}
*/
/*

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

		GTNode* SUMSYMBOL = TENSORVALUE->child(0);
		Indexs list;
		error = list.buildSUMSYMBOL(eme, SUMSYMBOL, this, dst);
		if (error != 0) return error;

		GTNode* OPERATOR = TENSORVALUE->child(2);
		Node::OpType OTT = ParseOpType(eme, OPERATOR);


		indiceIS IS;
		IS.appendS(id.GetSIndex());
		IS.appendS(list.GetIndex());
		IS.appendS(idL.GetSIndex());
		IS.appendS(idR.GetSIndex());
		IS.StoI();

		//Node* newNode = net->NewNodeMonoLinear(srcL);
		Node* newNode = net->NewNodeDiLinear(dims, srcL, srcR, OTT, IS);
		if (newNode == NULL)
		{
			errorCode = ErrorUnsupportType;
			errorInfor1 = line;
			ErrorNode = TENSORID;
			return 42423341;
		}
		Lvalue->SetInfor((void*)newNode, id.GetIndex());
		break;
	}
*/