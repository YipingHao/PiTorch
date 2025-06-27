#ifndef sheet_h_fhasdufhqweioq34ryh8iouertgfhouiaerfghiouerwfghuio
#define sheet_h_fhasdufhqweioq34ryh8iouertgfhouiaerfghiouerwfghuio
namespace Pikachu
{
	struct NetL
	{
		enum regular
		{
			_id_ = 1,
			_integer_ = 2,
			_realC_ = 3,
			_string_ = 4,
			_header_ = 5,
			_include_ = 6,
			_sum_ = 7,
			_func_ = 8,
			_net_ = 9,
			_tensor_ = 10,
			_def_ = 11,
			_input_ = 12,
			_output_ = 13,
			_para_ = 14,
			_return_ = 15,
			_for_ = 16,
			_if_ = 17,
			_else_ = 18,
			_real_ = 19,
			_complex_ = 20,
			_sint_ = 21,
			_uint_ = 22,
			_bool_ = 23,
			_sin_ = 24,
			_cos_ = 25,
			_exp_ = 26,
			_ln_ = 27,
			_log_ = 28,
			_sqrt_ = 29,
			_pow_ = 30,
			_spaces_ = 31,
			_enters_ = 32,
			_tab_ = 33,
			_semicolon_ = 34,
			_colon_ = 35,
			_dot_ = 36,
			_comma_ = 37,
			_braceL_ = 38,
			_braceR_ = 39,
			_left_ = 40,
			_right_ = 41,
			_squareL_ = 42,
			_squareR_ = 43,
			_angleL_ = 44,
			_angleR_ = 45,
			_anntationS_ = 46,
			_anntationM_ = 47,
			_multi_ = 48,
			_div_ = 49,
			_sub_ = 50,
			_add_ = 51,
			_assign_ = 52
		};
		enum group
		{
			_id___ = 1,
			_number___ = 2,
			_string___ = 3,
			_macro___ = 4,
			_instruct___ = 5,
			_reserved___ = 6,
			_type___ = 7,
			_function1___ = 8,
			_function2___ = 9,
			_format___ = 10,
			_division___ = 11,
			_braket___ = 12,
			_anntation___ = 13,
			_operatmd___ = 14,
			_operatas___ = 15,
			_assignments___ = 16
		};
		static int next(int state, const char c);
		static int action(int state);
		static int GroupGet(int state);
	};
	struct NetG
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
			context_defs_ = 1,
			//<DEF*>_first_ = 2,
			//<DEF*>_multi_ = 3,
			DEF_symbolic_ = 4,
			DEF_network_ = 5,
			DEF_def_ = 6,
			DEF_exp_ = 7,
			DEF_diff_ = 8,
			OPERATOR_operatmd_ = 9,
			OPERATOR_operatas_ = 10,
			//[operatmd]_multi_ = 11,
			//[operatmd]_div_ = 12,
			//[operatas]_sub_ = 13,
			//[operatas]_add_ = 14,
			DIFF_NET_diff_ = 15,
			EXP_RIGHT_default_ = 16,
			EXP_RIGHT_add_ = 17,
			EXP_MUL_default_ = 18,
			EXP_MUL_multi_ = 19,
			EXP_MINUS_default_ = 20,
			EXP_MINUS_plus_ = 21,
			UNIT_id_ = 22,
			UNIT_call_ = 23,
			UNIT_const_ = 24,
			UNIT_complex_ = 25,
			//[number]_integer_ = 26,
			//[number]_realC_ = 27,
			ID_array_ = 28,
			ID_single_ = 29,
			INDEX_COMPUTE_single_ = 30,
			CALL_call_1_ = 31,
			CALL_call_2_ = 32,
			//[function1]_sin_ = 33,
			//[function1]_cos_ = 34,
			//[function1]_exp_ = 35,
			//[function1]_ln_ = 36,
			//[function1]_log_ = 37,
			//[function1]_sqrt_ = 38,
			//[function2]_pow_ = 39,
			SYMBOLIC_SYMBOLIC_ = 40,
			PARA_PARA_ = 41,
			//<SYMBOLICPARAS>_single_ = 42,
			//<SYMBOLICPARAS>_multi_ = 43,
			SYMBOLICPARA_input_ = 44,
			SYMBOLICPARA_para_ = 45,
			SYMBOLICPARA_output_ = 46,
			SYMBOLICBODY_SYMBOLICBODY_ = 47,
			//<STATEMENT*>_first_ = 48,
			//<STATEMENT*>_multi_ = 49,
			STATEMENT_const_ = 50,
			STATEMENT_def1_ = 51,
			STATEMENT_def2_ = 52,
			STATEMENT_exp_ = 53,
			VALUE_single_ = 54,
			VALUE_multi_ = 55,
			VALUELIST_VALUELIST_ = 56,
			VALUES_VALUES_ = 57,
			//<NEXTVALUE*>_first_ = 58,
			//<NEXTVALUE*>_multi_ = 59,
			NEXTVALUE_NEXTVALUE_ = 60,
			NETWORK_NETWORK_ = 61,
			NETBODY_net_ = 62,
			//<NET_STATEMENT*>_first_ = 63,
			//<NET_STATEMENT*>_multi_ = 64,
			NET_STATEMENT_const_ = 65,
			NET_STATEMENT_exp_ = 66,
			NET_STATEMENT_def_ = 67,
			NET_STATEMENT_tensorDef1_ = 68,
			NET_STATEMENT_tensorDef2_ = 69,
			CONSTVAR_def1_ = 70,
			CONSTVAR_def2_ = 71,
			//[type]_real_ = 72,
			//[type]_complex_ = 73,
			//[type]_sint_ = 74,
			//[type]_uint_ = 75,
			//[type]_bool_ = 76,
			TENSORID_TENSORID_ = 77,
			TENSOR_TENSOR_ = 78,
			INDEXLIST_INDEXLIST_ = 79,
			INDEXUNITS_single_ = 80,
			INDEXUNITS_multi_ = 81,
			ID2_yes_ = 82,
			ID2_no_ = 83,
			TENSORVALUE_single_ = 84,
			TENSORVALUE_multi_ = 85,
			TENSORVALUE_singleF_ = 86,
			TENSORVALUE_multiF_ = 87,
			SUMSYMBOL_single_ = 88,
			SUMSYMBOL_multi_ = 89,
			SQ_INDEXUNITS_single_ = 90
		};
		enum nonterminal
		{
			_all_ = 0,
			_context_ = 1,
			//_<DEF*>_ = 2,
			_DEF_ = 3,
			_OPERATOR_ = 4,
			//_[operatmd]_ = 5,
			//_[operatas]_ = 6,
			_DIFF_NET_ = 7,
			_EXP_RIGHT_ = 8,
			_EXP_MUL_ = 9,
			_EXP_MINUS_ = 10,
			_UNIT_ = 11,
			//_[number]_ = 12,
			_ID_ = 13,
			_INDEX_COMPUTE_ = 14,
			_CALL_ = 15,
			//_[function1]_ = 16,
			//_[function2]_ = 17,
			_SYMBOLIC_ = 18,
			_PARA_ = 19,
			//_<SYMBOLICPARAS>_ = 20,
			_SYMBOLICPARA_ = 21,
			_SYMBOLICBODY_ = 22,
			//_<STATEMENT*>_ = 23,
			_STATEMENT_ = 24,
			_VALUE_ = 25,
			_VALUELIST_ = 26,
			_VALUES_ = 27,
			//_<NEXTVALUE*>_ = 28,
			_NEXTVALUE_ = 29,
			_NETWORK_ = 30,
			_NETBODY_ = 31,
			//_<NET_STATEMENT*>_ = 32,
			_NET_STATEMENT_ = 33,
			_CONSTVAR_ = 34,
			//_[type]_ = 35,
			_TENSORID_ = 36,
			_TENSOR_ = 37,
			_INDEXLIST_ = 38,
			_INDEXUNITS_ = 39,
			_ID2_ = 40,
			_TENSORVALUE_ = 41,
			_SUMSYMBOL_ = 42,
			_SQ_INDEXUNITS_ = 43
		};
		static const size_t StateCount;
		static const size_t NonTerminalCount;
		static const size_t TerminalCount;
		static const size_t RulesCount;
		static const int GOTO[176][44];
		static const int ACTION[176][53];
		static const int RulesToSymbol[91];
		static const int RulesLength[91];
		static const char* const RulesName[91];
		static const int Implicit[91];
	};
	struct NetPreL
	{
		enum regular
		{
			_id_ = 1,
			_integer_ = 2,
			_realC_ = 3,
			_string_ = 4,
			_header_ = 5,
			_include_ = 6,
			_sum_ = 7,
			_func_ = 8,
			_net_ = 9,
			_tensor_ = 10,
			_def_ = 11,
			_input_ = 12,
			_output_ = 13,
			_para_ = 14,
			_return_ = 15,
			_for_ = 16,
			_if_ = 17,
			_else_ = 18,
			_real_ = 19,
			_complex_ = 20,
			_sint_ = 21,
			_uint_ = 22,
			_bool_ = 23,
			_sin_ = 24,
			_cos_ = 25,
			_exp_ = 26,
			_ln_ = 27,
			_log_ = 28,
			_sqrt_ = 29,
			_pow_ = 30,
			_spaces_ = 31,
			_enters_ = 32,
			_tab_ = 33,
			_semicolon_ = 34,
			_colon_ = 35,
			_dot_ = 36,
			_comma_ = 37,
			_braceL_ = 38,
			_braceR_ = 39,
			_left_ = 40,
			_right_ = 41,
			_squareL_ = 42,
			_squareR_ = 43,
			_angleL_ = 44,
			_angleR_ = 45,
			_anntationS_ = 46,
			_anntationM_ = 47,
			_multi_ = 48,
			_div_ = 49,
			_sub_ = 50,
			_add_ = 51,
			_assign_ = 52
		};
		enum group
		{
			_id___ = 1,
			_number___ = 2,
			_string___ = 3,
			_macro___ = 4,
			_instruct___ = 5,
			_reserved___ = 6,
			_type___ = 7,
			_function1___ = 8,
			_function2___ = 9,
			_format___ = 10,
			_division___ = 11,
			_braket___ = 12,
			_anntation___ = 13,
			_operatmd___ = 14,
			_operatas___ = 15,
			_assignments___ = 16
		};
		static int next(int state, const char c);
		static int action(int state);
		static int GroupGet(int state);
	};
	struct NetPreG
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
			pretreat_meow_ = 1,
			//<DEF*>_first_ = 2,
			//<DEF*>_multi_ = 3,
			DEF_anntation_ = 4,
			DEF_anything_ = 5,
			DEF_include_ = 6,
			//[anntation]_anntationS_ = 7,
			//[anntation]_anntationM_ = 8,
			INCLUDE_include_ = 9,
			INCLUDE_include2_ = 10,
			MACRO_single_ = 11,
			MACRO_multi_ = 12,
			ANY_identifier_ = 13,
			ANY_number_ = 14,
			ANY_string_ = 15,
			ANY_instruct_ = 16,
			ANY_reserved_ = 17,
			ANY_type_ = 18,
			ANY_function1_ = 19,
			ANY_function2_ = 20,
			ANY_format_ = 21,
			ANY_division_ = 22,
			ANY_braket_ = 23,
			ANY_operatmd_ = 24,
			ANY_operatas_ = 25,
			ANY_assignments_ = 26,
			//[id]_id_ = 27,
			//[number]_integer_ = 28,
			//[number]_realC_ = 29,
			//[instruct]_sum_ = 30,
			//[reserved]_func_ = 31,
			//[reserved]_net_ = 32,
			//[reserved]_tensor_ = 33,
			//[reserved]_def_ = 34,
			//[reserved]_input_ = 35,
			//[reserved]_output_ = 36,
			//[reserved]_para_ = 37,
			//[reserved]_return_ = 38,
			//[reserved]_for_ = 39,
			//[reserved]_if_ = 40,
			//[reserved]_else_ = 41,
			//[type]_real_ = 42,
			//[type]_complex_ = 43,
			//[type]_sint_ = 44,
			//[type]_uint_ = 45,
			//[type]_bool_ = 46,
			//[function1]_sin_ = 47,
			//[function1]_cos_ = 48,
			//[function1]_exp_ = 49,
			//[function1]_ln_ = 50,
			//[function1]_log_ = 51,
			//[function1]_sqrt_ = 52,
			//[function2]_pow_ = 53,
			//[format]_spaces_ = 54,
			//[format]_enters_ = 55,
			//[format]_tab_ = 56,
			//[division]_semicolon_ = 57,
			//[division]_colon_ = 58,
			//[division]_dot_ = 59,
			//[division]_comma_ = 60,
			//[braket]_braceL_ = 61,
			//[braket]_braceR_ = 62,
			//[braket]_left_ = 63,
			//[braket]_right_ = 64,
			//[braket]_squareL_ = 65,
			//[braket]_squareR_ = 66,
			//[braket]_angleL_ = 67,
			//[braket]_angleR_ = 68,
			//[operatmd]_multi_ = 69,
			//[operatmd]_div_ = 70,
			//[operatas]_sub_ = 71,
			//[operatas]_add_ = 72,
			//[assignments]_assign_ = 73
		};
		enum nonterminal
		{
			_all_ = 0,
			_pretreat_ = 1,
			//_<DEF*>_ = 2,
			_DEF_ = 3,
			//_[anntation]_ = 4,
			_INCLUDE_ = 5,
			_MACRO_ = 6,
			_ANY_ = 7,
			//_[id]_ = 8,
			//_[number]_ = 9,
			//_[instruct]_ = 10,
			//_[reserved]_ = 11,
			//_[type]_ = 12,
			//_[function1]_ = 13,
			//_[function2]_ = 14,
			//_[format]_ = 15,
			//_[division]_ = 16,
			//_[braket]_ = 17,
			//_[operatmd]_ = 18,
			//_[operatas]_ = 19,
			//_[assignments]_ = 20
		};
		static const size_t StateCount;
		static const size_t NonTerminalCount;
		static const size_t TerminalCount;
		static const size_t RulesCount;
		static const int GOTO[75][21];
		static const int ACTION[75][53];
		static const int RulesToSymbol[74];
		static const int RulesLength[74];
		static const char* const RulesName[74];
		static const int Implicit[74];
	};




}



#endif // 