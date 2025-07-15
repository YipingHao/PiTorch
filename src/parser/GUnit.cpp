#include"../src/header/Pikachu.h"
#include"../extern/header/all.h"
#include "../header/parser.h"
#include "../header/sheet.h"
using namespace Pikachu;
static bool compare(const char* str1, const char* str2);





#include<string.h>
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
	SetName(Name); // 基类设置名称[1](@ref)
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
	V.append(initVal);
	// 类型和维度校验
	if (!left || !right) return;
	if (!left->scalar || !right->scalar)return;
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

		break;
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
	if (No >= srcR->V.count())return;  // 校验源对象及索引有效性[7,8](@ref)

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

const char* ConstObj::TypeName(type T)
{
	switch (T)
	{
	case _sint_:
		return "sint";
	case _uint_:
		return "uint";
	case _bool_:
		return "bool";
	case _complex_:
		return "complex";
	case _real_:
		return "real";
	default:
		return "unknown";
	}
}

var::var(Expres::node* srcR)
{
	name = NULL;
	Scalar = true;
	//infor = NULL;
	infors.recount(1);
	infors[0] = (void*)srcR;
	attribute = NULL;
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
	attribute = NULL;
}
void var::demo(FILE* fp) const
{
	if (attribute)
		fprintf(fp, "var[%zu](%s) ", infors.count(), attribute);
	else
		fprintf(fp, "var[%zu](???) ", infors.count());
	if (name)
		fprintf(fp, "%s ", name);
	else
		fprintf(fp, "??? = ");
}
void var::demo(FILE* fp, size_t tabs) const
{
	for (size_t i = 0; i < tabs; ++i)
		fprintf(fp, "\t");
	if (attribute)
		fprintf(fp, "var[%zu](%s) ", infors.count(), attribute);
	else
		fprintf(fp, "var[%zu](???) ", infors.count());
	if (name)
		fprintf(fp, "%s ", name);
	else
		fprintf(fp, "??? = ");
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
bool var::compareAttri(const char* srcR)const
{
	return compare(srcR, attribute);
}

func::func()
{
	Exp = new Expres;
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
	if (eme[Def->root().site].accept != NetL::regular::_id_)
	{
		infor->errorInfor1 = ID->root().site;
		infor->ErrorNode = ID;
		infor->errorCode = BuildInfor::WrongEntrance;
		return 53563456;
	}
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
		//printf("IDinfor::build %s\n", temp);
		int error = infor->GetAConst(Const_, eme, ID->child(1)->child(1), dst);
		//printf("IDinfor::build %s\n", temp);
		if (error != 0) return error;
		if (!Const_->SorUint())
		{
			infor->errorInfor1 = line;
			infor->ErrorNode = ID;
			infor->errorCode = BuildInfor::ErrorNeedAInt;
			return 1234234;
		}
		
		sint tempInt = Const_->GetSint();
		if (tempInt < 0)
		{
			infor->errorInfor1 = line;
			infor->errorInfor2 = tempInt;
			infor->ErrorNode = ID;
			infor->errorCode = BuildInfor::ErrorMinusIndex;
			return 1234267;
		}
		//printf("IDinfor::build %s\n", temp);
		delete Const_;
		index = tempInt;
	}
	else index = 0;
	return 0;
}
int IDinfor::build(const char* id, GTNode* Backup, BuildInfor* infor, context* dst)
{
	backup = Backup;
	SetName(id);
	scalar = true;
	index = 0;

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
	printf("\t??????\n");
	if (CheckType(error, infor)) return NULL;
	printf("\t??????\n");
	var* old = dst->search(name);
	ConstObj* oldC = dst->searchConst(name);
	if (old != NULL || oldC != NULL)
	{
		infor->errorCode = BuildInfor::VarAlreadDef;
		infor->ErrorNode = backup;
		error = 234789433;
		return NULL;
	}
	printf("\t??????\n");
	var* newVar = new var;
	printf("\t??????\n");
	newVar->SetName(name);
	printf("\t??????\n");
	if (attri != NULL) newVar->SetAttri(attri);
	printf("\t??????\n");
	if (!scalar)
	{
		newVar->SetCount(dim);
	}
	dst->global.append(newVar);
	printf("\t????sdf??\n");
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
	size_t index__ = GetIndex();
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
	if (index__ >= old->count())
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
func* IDinfor::GetAllFuncR(int& error, BuildInfor* infor, context* dst)
{
	if (!scalar)
	{
		infor->errorCode = BuildInfor::ErrorSAmissMatch;
		infor->ErrorNode = backup;
		error = 326785342;
		return NULL;
	}
	func* temp = dst->searchFuncs(GetName());
	if (temp == NULL)
	{
		infor->errorCode = BuildInfor::ErrorMissingFuncDef;
		infor->ErrorNode = backup;
		error = 123134545;
		return NULL;
	}
	return temp;
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
		return 24523453;
	}
	return 0;
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
		return 245237853;
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
int TensorID::BuildSingle(const lex& eme, GTNode* TENSORID, BuildInfor* infor, context* dst)
{
	int error = build(eme, TENSORID, infor, dst);
	if (error) return error;
	if (!scalar)
	{
		infor->errorCode = BuildInfor::ErrorSAmissMatch; // 错误：标量与非标量不匹配
		infor->ErrorNode = TENSORID; // 错误节点
		return 326785342; // 返回错误代码
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
		return build(eme, VALUE->child(1), infor, dst); // 调用build函数处理多值列表
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
		return 24553453;
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
	//printf("VALUES->ChildCount() %zu\n", VALUES->ChildCount());
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
void ValueList::demo(FILE* fp) const
{
	fprintf(fp, "ValueList: %s\n", backup ? "backup->GetName()" : "NULL");
	fprintf(fp, "Scalar: %s\n", scalar ? "true" : "false");
	fprintf(fp, "Values count: %zu\n", values.count());
	for (size_t i = 0; i < values.count(); i++)
	{
		if (values[i])
			values[i]->demo(fp);
		else
			fprintf(fp, "Value[%zu]: NULL", i);
		fprintf(fp, "\n");
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