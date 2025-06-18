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
int NetL::next(int state, const char c)
{
	switch (state)
	{
	case 0:
		if (c == (char)9) return 33;
		else if (c == (char)10) return 32;
		else if (c == ' ') return 31;
		else if (c == '\"') return 53;
		else if (c == '#') return 92;
		else if (c == '(') return 40;
		else if (c == ')') return 41;
		else if (c == '*') return 48;
		else if (c == '+') return 51;
		else if (c == ',') return 37;
		else if (c == '-') return 50;
		else if (c == '.') return 36;
		else if (c == '/') return 49;
		else if ('0' <= c && c <= '9') return 2;
		else if (c == ':') return 35;
		else if (c == ';') return 34;
		else if (c == '<') return 44;
		else if (c == '=') return 52;
		else if (c == '>') return 45;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '[') return 42;
		else if (c == '\\') return 110;
		else if (c == ']') return 43;
		else if (c == '_') return 1;
		else if (c == 'a') return 1;
		else if (c == 'b') return 66;
		else if (c == 'c') return 75;
		else if (c == 'd') return 58;
		else if (c == 'e') return 72;
		else if (c == 'f') return 70;
		else if ('g' <= c && c <= 'h') return 1;
		else if (c == 'i') return 57;
		else if ('j' <= c && c <= 'k') return 1;
		else if (c == 'l') return 63;
		else if (c == 'm') return 1;
		else if (c == 'n') return 77;
		else if (c == 'o') return 84;
		else if (c == 'p') return 69;
		else if (c == 'q') return 1;
		else if (c == 'r') return 62;
		else if (c == 's') return 64;
		else if (c == 't') return 74;
		else if (c == 'u') return 79;
		else if ('v' <= c && c <= 'z') return 1;
		else if (c == '{') return 38;
		else if (c == '}') return 39;
		else return 0;
	case 1:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 2:
		if (c == '.') return 117;
		else if ('0' <= c && c <= '9') return 2;
		else return 0;
	case 3:
		if ('0' <= c && c <= '9') return 3;
		else if (c == 'E') return 104;
		else if (c == 'e') return 104;
		else return 0;
	case 4:
		return 0;
	case 5:
		if (c == ' ') return 111;
		else if (c == '!') return 93;
		else if ('#' <= c && c <= '[') return 93;
		else if (c == '\\') return 91;
		else if (']' <= c && c <= (char)127) return 93;
		else return 0;
	case 6:
		return 0;
	case 7:
		return 0;
	case 8:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 9:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 10:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 11:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 12:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 13:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 14:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 15:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 16:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 17:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 18:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 19:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 20:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 21:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 22:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 23:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 24:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 's') return 1;
		else if (c == 't') return 21;
		else if ('u' <= c && c <= 'z') return 1;
		else return 0;
	case 25:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 26:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 27:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 28:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 29:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 30:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'z') return 1;
		else return 0;
	case 31:
		if (c == ' ') return 31;
		else return 0;
	case 32:
		if (c == (char)10) return 32;
		else return 0;
	case 33:
		return 0;
	case 34:
		return 0;
	case 35:
		return 0;
	case 36:
		return 0;
	case 37:
		return 0;
	case 38:
		return 0;
	case 39:
		return 0;
	case 40:
		return 0;
	case 41:
		return 0;
	case 42:
		return 0;
	case 43:
		return 0;
	case 44:
		if (c == ' ') return 93;
		else return 0;
	case 45:
		return 0;
	case 46:
		if ((char)0 <= c && c <= (char)9) return 46;
		else if ((char)11 <= c && c <= (char)127) return 46;
		else return 0;
	case 47:
		if ((char)0 <= c && c <= ')') return 103;
		else if (c == '*') return 116;
		else if ('+' <= c && c <= (char)127) return 103;
		else return 0;
	case 48:
		return 0;
	case 49:
		if (c == '*') return 103;
		else if (c == '/') return 46;
		else return 0;
	case 50:
		if ('0' <= c && c <= '9') return 2;
		else return 0;
	case 51:
		if ('0' <= c && c <= '9') return 2;
		else return 0;
	case 52:
		return 0;
	case 53:
		if (' ' <= c && c <= '!') return 53;
		else if (c == '\"') return 4;
		else if ('#' <= c && c <= '[') return 53;
		else if (c == '\\') return 115;
		else if (']' <= c && c <= (char)127) return 53;
		else return 0;
	case 54:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if (c == 'a') return 14;
		else if ('b' <= c && c <= 'z') return 1;
		else return 0;
	case 55:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'b') return 1;
		else if (c == 'c') return 8;
		else if ('d' <= c && c <= 'z') return 1;
		else return 0;
	case 56:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'd') return 1;
		else if (c == 'e') return 18;
		else if ('f' <= c && c <= 'z') return 1;
		else return 0;
	case 57:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'e') return 1;
		else if (c == 'f') return 17;
		else if ('g' <= c && c <= 'm') return 1;
		else if (c == 'n') return 126;
		else if ('o' <= c && c <= 'z') return 1;
		else return 0;
	case 58:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'd') return 1;
		else if (c == 'e') return 94;
		else if ('f' <= c && c <= 'z') return 1;
		else return 0;
	case 59:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'f') return 1;
		else if (c == 'g') return 28;
		else if ('h' <= c && c <= 'z') return 1;
		else return 0;
	case 60:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'k') return 1;
		else if (c == 'l') return 19;
		else if ('m' <= c && c <= 'z') return 1;
		else return 0;
	case 61:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if (c == 'a') return 60;
		else if ('b' <= c && c <= 's') return 1;
		else if (c == 't') return 81;
		else if ('u' <= c && c <= 'z') return 1;
		else return 0;
	case 62:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'd') return 1;
		else if (c == 'e') return 61;
		else if ('f' <= c && c <= 'z') return 1;
		else return 0;
	case 63:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'm') return 1;
		else if (c == 'n') return 27;
		else if (c == 'o') return 59;
		else if ('p' <= c && c <= 'z') return 1;
		else return 0;
	case 64:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'h') return 1;
		else if (c == 'i') return 96;
		else if ('j' <= c && c <= 'p') return 1;
		else if (c == 'q') return 80;
		else if ('r' <= c && c <= 'z') return 1;
		else return 0;
	case 65:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'n') return 1;
		else if (c == 'o') return 95;
		else if ('p' <= c && c <= 'z') return 1;
		else return 0;
	case 66:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'n') return 1;
		else if (c == 'o') return 65;
		else if ('p' <= c && c <= 'z') return 1;
		else return 0;
	case 67:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'o') return 1;
		else if (c == 'p') return 26;
		else if ('q' <= c && c <= 'z') return 1;
		else return 0;
	case 68:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'q') return 1;
		else if (c == 'r') return 10;
		else if ('s' <= c && c <= 'z') return 1;
		else return 0;
	case 69:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if (c == 'a') return 113;
		else if ('b' <= c && c <= 'n') return 1;
		else if (c == 'o') return 85;
		else if ('p' <= c && c <= 'z') return 1;
		else return 0;
	case 70:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'n') return 1;
		else if (c == 'o') return 123;
		else if ('p' <= c && c <= 't') return 1;
		else if (c == 'u') return 122;
		else if ('v' <= c && c <= 'z') return 1;
		else return 0;
	case 71:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'r') return 1;
		else if (c == 's') return 98;
		else if ('t' <= c && c <= 'z') return 1;
		else return 0;
	case 72:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'k') return 1;
		else if (c == 'l') return 100;
		else if ('m' <= c && c <= 'w') return 1;
		else if (c == 'x') return 67;
		else if ('y' <= c && c <= 'z') return 1;
		else return 0;
	case 73:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'm') return 1;
		else if (c == 'n') return 71;
		else if ('o' <= c && c <= 'z') return 1;
		else return 0;
	case 74:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'd') return 1;
		else if (c == 'e') return 73;
		else if ('f' <= c && c <= 'z') return 1;
		else return 0;
	case 75:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'n') return 1;
		else if (c == 'o') return 99;
		else if ('p' <= c && c <= 'z') return 1;
		else return 0;
	case 76:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 's') return 1;
		else if (c == 't') return 22;
		else if ('u' <= c && c <= 'z') return 1;
		else return 0;
	case 77:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'd') return 1;
		else if (c == 'e') return 124;
		else if ('f' <= c && c <= 'z') return 1;
		else return 0;
	case 78:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'm') return 1;
		else if (c == 'n') return 76;
		else if ('o' <= c && c <= 'z') return 1;
		else return 0;
	case 79:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'h') return 1;
		else if (c == 'i') return 78;
		else if ('j' <= c && c <= 'z') return 1;
		else return 0;
	case 80:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'q') return 1;
		else if (c == 'r') return 101;
		else if ('s' <= c && c <= 'z') return 1;
		else return 0;
	case 81:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 't') return 1;
		else if (c == 'u') return 97;
		else if ('v' <= c && c <= 'z') return 1;
		else return 0;
	case 82:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'o') return 1;
		else if (c == 'p') return 102;
		else if ('q' <= c && c <= 'z') return 1;
		else return 0;
	case 83:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 's') return 1;
		else if (c == 't') return 82;
		else if ('u' <= c && c <= 'z') return 1;
		else return 0;
	case 84:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 't') return 1;
		else if (c == 'u') return 83;
		else if ('v' <= c && c <= 'z') return 1;
		else return 0;
	case 85:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'v') return 1;
		else if (c == 'w') return 30;
		else if ('x' <= c && c <= 'z') return 1;
		else return 0;
	case 86:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'w') return 1;
		else if (c == 'x') return 20;
		else if ('y' <= c && c <= 'z') return 1;
		else return 0;
	case 87:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'd') return 1;
		else if (c == 'e') return 86;
		else if ('f' <= c && c <= 'z') return 1;
		else return 0;
	case 88:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'k') return 1;
		else if (c == 'l') return 87;
		else if ('m' <= c && c <= 'z') return 1;
		else return 0;
	case 89:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'o') return 1;
		else if (c == 'p') return 88;
		else if ('q' <= c && c <= 'z') return 1;
		else return 0;
	case 90:
		if ('0' <= c && c <= '9') return 90;
		else return 0;
	case 91:
		if (c == (char)0) return 93;
		else if (c == '\"') return 93;
		else if (c == '\'') return 93;
		else if ('0' <= c && c <= '7') return 93;
		else if (c == '\?') return 93;
		else if (c == 'X') return 105;
		else if (c == '\\') return 93;
		else if ('a' <= c && c <= 'b') return 93;
		else if (c == 'f') return 93;
		else if (c == 'n') return 93;
		else if (c == 'r') return 93;
		else if (c == 't') return 93;
		else if (c == 'v') return 93;
		else if (c == 'x') return 105;
		else return 0;
	case 92:
		if (c == 'i') return 120;
		else return 0;
	case 93:
		if (c == ' ') return 111;
		else if (c == '!') return 93;
		else if ('#' <= c && c <= '[') return 93;
		else if (c == '\\') return 91;
		else if (']' <= c && c <= (char)127) return 93;
		else return 0;
	case 94:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'e') return 1;
		else if (c == 'f') return 11;
		else if ('g' <= c && c <= 'z') return 1;
		else return 0;
	case 95:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'k') return 1;
		else if (c == 'l') return 23;
		else if ('m' <= c && c <= 'z') return 1;
		else return 0;
	case 96:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'm') return 1;
		else if (c == 'n') return 24;
		else if ('o' <= c && c <= 'z') return 1;
		else return 0;
	case 97:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'q') return 1;
		else if (c == 'r') return 112;
		else if ('s' <= c && c <= 'z') return 1;
		else return 0;
	case 98:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'n') return 1;
		else if (c == 'o') return 68;
		else if ('p' <= c && c <= 'z') return 1;
		else return 0;
	case 99:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'l') return 1;
		else if (c == 'm') return 89;
		else if ('n' <= c && c <= 'r') return 1;
		else if (c == 's') return 25;
		else if ('t' <= c && c <= 'z') return 1;
		else return 0;
	case 100:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'r') return 1;
		else if (c == 's') return 56;
		else if ('t' <= c && c <= 'z') return 1;
		else return 0;
	case 101:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 's') return 1;
		else if (c == 't') return 29;
		else if ('u' <= c && c <= 'z') return 1;
		else return 0;
	case 102:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 't') return 1;
		else if (c == 'u') return 114;
		else if ('v' <= c && c <= 'z') return 1;
		else return 0;
	case 103:
		if ((char)0 <= c && c <= ')') return 103;
		else if (c == '*') return 116;
		else if ('+' <= c && c <= (char)127) return 103;
		else return 0;
	case 104:
		if (c == '+') return 127;
		else if (c == '-') return 127;
		else if ('0' <= c && c <= '9') return 90;
		else return 0;
	case 105:
		if ('0' <= c && c <= '9') return 93;
		else if ('A' <= c && c <= 'F') return 93;
		else if ('a' <= c && c <= 'f') return 93;
		else return 0;
	case 106:
		if (c == '_') return 7;
		else return 0;
	case 107:
		if (c == 'c') return 118;
		else return 0;
	case 108:
		if (c == 'd') return 109;
		else return 0;
	case 109:
		if (c == 'e') return 6;
		else return 0;
	case 110:
		if (c == 's') return 121;
		else return 0;
	case 111:
		if (c == ' ') return 111;
		else if (c == '!') return 93;
		else if ('#' <= c && c <= '=') return 93;
		else if (c == '>') return 5;
		else if ('\?' <= c && c <= '[') return 93;
		else if (c == '\\') return 91;
		else if (']' <= c && c <= (char)127) return 93;
		else return 0;
	case 112:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'm') return 1;
		else if (c == 'n') return 15;
		else if ('o' <= c && c <= 'z') return 1;
		else return 0;
	case 113:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'q') return 1;
		else if (c == 'r') return 54;
		else if ('s' <= c && c <= 'z') return 1;
		else return 0;
	case 114:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 's') return 1;
		else if (c == 't') return 13;
		else if ('u' <= c && c <= 'z') return 1;
		else return 0;
	case 115:
		if (c == (char)0) return 53;
		else if (c == '\"') return 53;
		else if (c == '\'') return 53;
		else if ('0' <= c && c <= '7') return 53;
		else if (c == '\?') return 53;
		else if (c == 'X') return 130;
		else if (c == '\\') return 53;
		else if ('a' <= c && c <= 'b') return 53;
		else if (c == 'f') return 53;
		else if (c == 'n') return 53;
		else if (c == 'r') return 53;
		else if (c == 't') return 53;
		else if (c == 'v') return 53;
		else if (c == 'x') return 130;
		else return 0;
	case 116:
		if ((char)0 <= c && c <= ')') return 103;
		else if (c == '*') return 116;
		else if ('+' <= c && c <= '.') return 103;
		else if (c == '/') return 47;
		else if ('0' <= c && c <= (char)127) return 103;
		else return 0;
	case 117:
		if ('0' <= c && c <= '9') return 3;
		else return 0;
	case 118:
		if (c == 'l') return 128;
		else return 0;
	case 119:
		if (c == 'm') return 106;
		else return 0;
	case 120:
		if (c == 'n') return 107;
		else return 0;
	case 121:
		if (c == 'u') return 119;
		else return 0;
	case 122:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'm') return 1;
		else if (c == 'n') return 55;
		else if ('o' <= c && c <= 'z') return 1;
		else return 0;
	case 123:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'q') return 1;
		else if (c == 'r') return 16;
		else if ('s' <= c && c <= 'z') return 1;
		else return 0;
	case 124:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 's') return 1;
		else if (c == 't') return 9;
		else if ('u' <= c && c <= 'z') return 1;
		else return 0;
	case 125:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 't') return 1;
		else if (c == 'u') return 129;
		else if ('v' <= c && c <= 'z') return 1;
		else return 0;
	case 126:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 'o') return 1;
		else if (c == 'p') return 125;
		else if ('q' <= c && c <= 'z') return 1;
		else return 0;
	case 127:
		if ('0' <= c && c <= '9') return 90;
		else return 0;
	case 128:
		if (c == 'u') return 108;
		else return 0;
	case 129:
		if ('0' <= c && c <= '9') return 1;
		else if ('A' <= c && c <= 'Z') return 1;
		else if (c == '_') return 1;
		else if ('a' <= c && c <= 's') return 1;
		else if (c == 't') return 12;
		else if ('u' <= c && c <= 'z') return 1;
		else return 0;
	case 130:
		if ('0' <= c && c <= '9') return 53;
		else if ('A' <= c && c <= 'F') return 53;
		else if ('a' <= c && c <= 'f') return 53;
		else return 0;
	}
	return 0;
}
int NetL::action(int state)
{
	switch (state)
	{
	case 1:
		return 1;//id: id
	case 2:
		return 2;//number: integer
	case 3:
		return 3;//number: realC
	case 4:
		return 4;//string: string
	case 5:
		return 5;//string: header
	case 6:
		return 6;//macro: include
	case 7:
		return 7;//instruct: sum
	case 8:
		return 8;//reserved: func
	case 9:
		return 9;//reserved: net
	case 10:
		return 10;//reserved: tensor
	case 11:
		return 11;//reserved: def
	case 12:
		return 12;//reserved: input
	case 13:
		return 13;//reserved: output
	case 14:
		return 14;//reserved: para
	case 15:
		return 15;//reserved: return
	case 16:
		return 16;//reserved: for
	case 17:
		return 17;//reserved: if
	case 18:
		return 18;//reserved: else
	case 19:
		return 19;//type: real
	case 20:
		return 20;//type: complex
	case 21:
		return 21;//type: sint
	case 22:
		return 22;//type: uint
	case 23:
		return 23;//type: bool
	case 24:
		return 24;//function1: sin
	case 25:
		return 25;//function1: cos
	case 26:
		return 26;//function1: exp
	case 27:
		return 27;//function1: ln
	case 28:
		return 28;//function1: log
	case 29:
		return 29;//function1: sqrt
	case 30:
		return 30;//function2: pow
	case 31:
		return 31;//format: spaces
	case 32:
		return 32;//format: enters
	case 33:
		return 33;//format: tab
	case 34:
		return 34;//division: semicolon
	case 35:
		return 35;//division: colon
	case 36:
		return 36;//division: dot
	case 37:
		return 37;//division: comma
	case 38:
		return 38;//braket: braceL
	case 39:
		return 39;//braket: braceR
	case 40:
		return 40;//braket: left
	case 41:
		return 41;//braket: right
	case 42:
		return 42;//braket: squareL
	case 43:
		return 43;//braket: squareR
	case 44:
		return 44;//braket: angleL
	case 45:
		return 45;//braket: angleR
	case 46:
		return 46;//anntation: anntationS
	case 47:
		return 47;//anntation: anntationM
	case 48:
		return 48;//operatmd: multi
	case 49:
		return 49;//operatmd: div
	case 50:
		return 50;//operatas: sub
	case 51:
		return 51;//operatas: add
	case 52:
		return 52;//assignments: assign
	case 54:
		return 1;//id: id
	case 55:
		return 1;//id: id
	case 56:
		return 1;//id: id
	case 57:
		return 1;//id: id
	case 58:
		return 1;//id: id
	case 59:
		return 1;//id: id
	case 60:
		return 1;//id: id
	case 61:
		return 1;//id: id
	case 62:
		return 1;//id: id
	case 63:
		return 1;//id: id
	case 64:
		return 1;//id: id
	case 65:
		return 1;//id: id
	case 66:
		return 1;//id: id
	case 67:
		return 1;//id: id
	case 68:
		return 1;//id: id
	case 69:
		return 1;//id: id
	case 70:
		return 1;//id: id
	case 71:
		return 1;//id: id
	case 72:
		return 1;//id: id
	case 73:
		return 1;//id: id
	case 74:
		return 1;//id: id
	case 75:
		return 1;//id: id
	case 76:
		return 1;//id: id
	case 77:
		return 1;//id: id
	case 78:
		return 1;//id: id
	case 79:
		return 1;//id: id
	case 80:
		return 1;//id: id
	case 81:
		return 1;//id: id
	case 82:
		return 1;//id: id
	case 83:
		return 1;//id: id
	case 84:
		return 1;//id: id
	case 85:
		return 1;//id: id
	case 86:
		return 1;//id: id
	case 87:
		return 1;//id: id
	case 88:
		return 1;//id: id
	case 89:
		return 1;//id: id
	case 90:
		return 3;//number: realC
	case 94:
		return 1;//id: id
	case 95:
		return 1;//id: id
	case 96:
		return 1;//id: id
	case 97:
		return 1;//id: id
	case 98:
		return 1;//id: id
	case 99:
		return 1;//id: id
	case 100:
		return 1;//id: id
	case 101:
		return 1;//id: id
	case 102:
		return 1;//id: id
	case 112:
		return 1;//id: id
	case 113:
		return 1;//id: id
	case 114:
		return 1;//id: id
	case 122:
		return 1;//id: id
	case 123:
		return 1;//id: id
	case 124:
		return 1;//id: id
	case 125:
		return 1;//id: id
	case 126:
		return 1;//id: id
	case 129:
		return 1;//id: id
	}
	return 0;
}
int NetL::GroupGet(int accept)
{
	switch (accept)
	{
	case 1:
		return 1;//id: id
	case 2:
		return 2;//number: integer
	case 3:
		return 2;//number: realC
	case 4:
		return 3;//string: string
	case 5:
		return 3;//string: header
	case 6:
		return 4;//macro: include
	case 7:
		return 5;//instruct: sum
	case 8:
		return 6;//reserved: func
	case 9:
		return 6;//reserved: net
	case 10:
		return 6;//reserved: tensor
	case 11:
		return 6;//reserved: def
	case 12:
		return 6;//reserved: input
	case 13:
		return 6;//reserved: output
	case 14:
		return 6;//reserved: para
	case 15:
		return 6;//reserved: return
	case 16:
		return 6;//reserved: for
	case 17:
		return 6;//reserved: if
	case 18:
		return 6;//reserved: else
	case 19:
		return 7;//type: real
	case 20:
		return 7;//type: complex
	case 21:
		return 7;//type: sint
	case 22:
		return 7;//type: uint
	case 23:
		return 7;//type: bool
	case 24:
		return 8;//function1: sin
	case 25:
		return 8;//function1: cos
	case 26:
		return 8;//function1: exp
	case 27:
		return 8;//function1: ln
	case 28:
		return 8;//function1: log
	case 29:
		return 8;//function1: sqrt
	case 30:
		return 9;//function2: pow
	case 31:
		return 10;//format: spaces
	case 32:
		return 10;//format: enters
	case 33:
		return 10;//format: tab
	case 34:
		return 11;//division: semicolon
	case 35:
		return 11;//division: colon
	case 36:
		return 11;//division: dot
	case 37:
		return 11;//division: comma
	case 38:
		return 12;//braket: braceL
	case 39:
		return 12;//braket: braceR
	case 40:
		return 12;//braket: left
	case 41:
		return 12;//braket: right
	case 42:
		return 12;//braket: squareL
	case 43:
		return 12;//braket: squareR
	case 44:
		return 12;//braket: angleL
	case 45:
		return 12;//braket: angleR
	case 46:
		return 13;//anntation: anntationS
	case 47:
		return 13;//anntation: anntationM
	case 48:
		return 14;//operatmd: multi
	case 49:
		return 14;//operatmd: div
	case 50:
		return 15;//operatas: sub
	case 51:
		return 15;//operatas: add
	case 52:
		return 16;//assignments: assign
	}
	return 0;
}
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
		OPERATOR_operatmd_ = 7,
		OPERATOR_operatas_ = 8,
		//[operatmd]_multi_ = 9,
		//[operatmd]_div_ = 10,
		//[operatas]_sub_ = 11,
		//[operatas]_add_ = 12,
		//EXP_RIGHT_<implicit>_ = 13,
		EXP_RIGHT_add_ = 14,
		//EXP_MUL_<implicit>_ = 15,
		EXP_MUL_multi_ = 16,
		//EXP_MINUS_<implicit>_ = 17,
		EXP_MINUS_plus_ = 18,
		UNIT_id_ = 19,
		UNIT_call_ = 20,
		UNIT_const_ = 21,
		UNIT_complex_ = 22,
		//[number]_integer_ = 23,
		//[number]_realC_ = 24,
		ID_array_ = 25,
		ID_single_ = 26,
		CALL_call_1_ = 27,
		CALL_call_2_ = 28,
		//[function1]_sin_ = 29,
		//[function1]_cos_ = 30,
		//[function1]_exp_ = 31,
		//[function1]_ln_ = 32,
		//[function1]_log_ = 33,
		//[function1]_sqrt_ = 34,
		//[function2]_pow_ = 35,
		SYMBOLIC_SYMBOLIC_ = 36,
		PARA_PARA_ = 37,
		//<SYMBOLICPARAS>_single_ = 38,
		//<SYMBOLICPARAS>_multi_ = 39,
		SYMBOLICPARA_input_ = 40,
		SYMBOLICPARA_para_ = 41,
		SYMBOLICPARA_output_ = 42,
		SYMBOLICBODY_SYMBOLICBODY_ = 43,
		//<STATEMENT*>_first_ = 44,
		//<STATEMENT*>_multi_ = 45,
		STATEMENT_def_ = 46,
		STATEMENT_exp_ = 47,
		EXPRESSION_EXPRESSION_ = 48,
		VAR_def1_ = 49,
		VAR_def2_ = 50,
		DEF_VAR_const_ = 51,
		DEF_VAR_var_ = 52,
		//[type]_real_ = 53,
		//[type]_complex_ = 54,
		//[type]_sint_ = 55,
		//[type]_uint_ = 56,
		//[type]_bool_ = 57,
		VALUE_single_ = 58,
		VALUE_multi_ = 59,
		VALUELIST_VALUELIST_ = 60,
		VALUES_VALUES_ = 61,
		//<NEXTVALUE*>_first_ = 62,
		//<NEXTVALUE*>_multi_ = 63,
		NEXTVALUE_NEXTVALUE_ = 64,
		NETWORK_NETWORK_ = 65,
		NETBODY_net_ = 66,
		//<NET_STATEMENT*>_first_ = 67,
		//<NET_STATEMENT*>_multi_ = 68,
		NET_STATEMENT_const_ = 69,
		NET_STATEMENT_exp_ = 70,
		NET_STATEMENT_def_ = 71,
		NET_STATEMENT_def2_ = 72,
		NET_STATEMENT_tensorDef1_ = 73,
		NET_STATEMENT_tensorDef2_ = 74,
		CONSTVAR_def1_ = 75,
		CONSTVAR_def2_ = 76,
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
		SUMSYMBOL_multi_ = 89
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
		_EXP_RIGHT_ = 7,
		_EXP_MUL_ = 8,
		_EXP_MINUS_ = 9,
		_UNIT_ = 10,
		//_[number]_ = 11,
		_ID_ = 12,
		_CALL_ = 13,
		//_[function1]_ = 14,
		//_[function2]_ = 15,
		_SYMBOLIC_ = 16,
		_PARA_ = 17,
		//_<SYMBOLICPARAS>_ = 18,
		_SYMBOLICPARA_ = 19,
		_SYMBOLICBODY_ = 20,
		//_<STATEMENT*>_ = 21,
		_STATEMENT_ = 22,
		_EXPRESSION_ = 23,
		_VAR_ = 24,
		_DEF_VAR_ = 25,
		//_[type]_ = 26,
		_VALUE_ = 27,
		_VALUELIST_ = 28,
		_VALUES_ = 29,
		//_<NEXTVALUE*>_ = 30,
		_NEXTVALUE_ = 31,
		_NETWORK_ = 32,
		_NETBODY_ = 33,
		//_<NET_STATEMENT*>_ = 34,
		_NET_STATEMENT_ = 35,
		_CONSTVAR_ = 36,
		_TENSORID_ = 37,
		_TENSOR_ = 38,
		_INDEXLIST_ = 39,
		_INDEXUNITS_ = 40,
		_ID2_ = 41,
		_TENSORVALUE_ = 42,
		_SUMSYMBOL_ = 43
	};
	static const size_t StateCount;
	static const size_t NonTerminalCount;
	static const size_t TerminalCount;
	static const size_t RulesCount;
	static const int GOTO[164][44];
	static const int ACTION[164][53];
	static const int RulesToSymbol[90];
	static const int RulesLength[90];
	static const char* const RulesName[90];
	static const int Implicit[90];
};
const size_t NetG::StateCount = 164;
const size_t NetG::NonTerminalCount = 44;
const size_t NetG::TerminalCount = 52;
const size_t NetG::RulesCount = 90;
const int NetG::GOTO[164][44] = { \
{1, 6, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 18, 1, 1, 1, 1, 1, 1, 1, 22, 26, 30, 1, 1, 1, 1, 1, 34, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 638, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 78, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 114, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 94, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 130, 134, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 138, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 142, 1, 1, 146, 1, 1, 1, 1, 1, 1, 1, 1, 150, 154, 1, 158, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 526, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 502, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 506, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 170, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 182, 186}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 262, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 290, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 230, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 206, 210, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 226, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 210, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 250, 210, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 262, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 266, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 286, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 262, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 278, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 294, 298, 302, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 262, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 322, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 338, 342, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 374, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 498, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 422, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 478, 482, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 434, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 418, 342, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 422, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 1, 430, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 434, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 1, 1, 438, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 450, 342, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 422, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 458, 342, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 422, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 470, 342, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 422, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 486, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 494, 342, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 422, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 286, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 514, 186}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 538, 342, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 542, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 422, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 338, 342, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 550, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 566, 342, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 422, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 586, 590, 594, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 602, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 614, 618, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 138, 1, 1, 1, 1, 1, 1, 1, 1, 1, 622, 626, 630, 26, 30, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 334, 538, 342, 346, 350, 354, 358, 362, 366, 370, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 650, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
//==============================
const int NetG::ACTION[164][53] = { \
{11, 1, 1, 1, 1, 1, 1, 1, 11, 11, 1, 11, 1, 1, 1, 1, 1, 1, 1, 11, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{7, 1, 1, 1, 1, 1, 1, 1, 38, 42, 1, 46, 1, 1, 1, 1, 1, 1, 1, 50, 54, 58, 62, 66, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{15, 1, 1, 1, 1, 1, 1, 1, 15, 15, 1, 15, 1, 1, 1, 1, 1, 1, 1, 15, 15, 15, 15, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{19, 1, 1, 1, 1, 1, 1, 1, 19, 19, 1, 19, 1, 1, 1, 1, 1, 1, 1, 19, 19, 19, 19, 19, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{27, 1, 1, 1, 1, 1, 1, 1, 27, 27, 1, 27, 1, 1, 1, 1, 1, 1, 1, 27, 27, 27, 27, 27, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 207, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{23, 1, 1, 1, 1, 1, 1, 1, 23, 23, 1, 23, 1, 1, 1, 1, 1, 1, 1, 23, 23, 23, 23, 23, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 578, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 70, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 211, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 215, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 219, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 223, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 227, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 231, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 74, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 82, 86, 90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 122, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 167, 1, 1, 1, 167, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 107, 1, 1, 107, 1, 1, 1, 107, 102, 107, 107, 1, 1, 1, 107, 107, 107, 107, 107}, \
{9, 9, 106, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, \
{173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 110, 173, 173, 173, 173, 173, 173, 173, 173, 173}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 103, 1, 1, 103, 1, 1, 1, 103, 1, 103, 103, 1, 1, 1, 103, 103, 103, 103, 103}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 171, 1, 1, 1, 171, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 163, 1, 1, 1, 163, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 126, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153}, \
{1, 271, 1, 1, 1, 1, 1, 1, 1, 1, 271, 271, 1, 1, 1, 1, 1, 1, 1, 271, 271, 271, 271, 271, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 271, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 574, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157}, \
{1, 98, 1, 1, 1, 1, 1, 1, 1, 1, 162, 166, 1, 1, 1, 1, 1, 1, 1, 50, 54, 58, 62, 66, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 267, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 562}, \
{1, 283, 1, 1, 1, 1, 1, 1, 1, 1, 283, 283, 1, 1, 1, 1, 1, 1, 1, 283, 283, 283, 283, 283, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 283, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 275, 1, 1, 1, 1, 1, 1, 1, 1, 275, 275, 1, 1, 1, 1, 1, 1, 1, 275, 275, 275, 275, 275, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 275, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 279, 1, 1, 1, 1, 1, 1, 1, 1, 279, 279, 1, 1, 1, 1, 1, 1, 1, 279, 279, 279, 279, 279, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 279, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 330, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 174, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 178}, \
{1, 287, 1, 1, 1, 1, 1, 1, 1, 1, 287, 287, 1, 1, 1, 1, 1, 1, 1, 287, 287, 287, 287, 287, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 287, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 190, 1, 1, 1, 1, 1, 194, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 326, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 234, 177, 177, 177, 177, 177, 177, 177, 177}, \
{1, 198, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 202, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 355, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 214, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 335, 1, 335, 1, 1, 1, 335, 1, 335, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 218, 1, 222, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 323, 1, 323, 1, 1, 1, 323, 1, 323, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 331, 1, 331, 1, 1, 1, 331, 1, 331, 1, 1, 1, 1, 1, 1, 1}, \
{1, 214, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 335, 1, 335, 1, 1, 1, 335, 1, 335, 1, 1, 1, 1, 1, 1, 1}, \
{5, 359, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 327, 1, 327, 1, 1, 1, 327, 1, 327, 1, 1, 1, 1, 1, 1, 1}, \
{169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 246, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169}, \
{1, 214, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 335, 1, 335, 1, 1, 1, 335, 1, 335, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 218, 1, 1, 1, 1, 1, 1, 1, 242, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 319, 1, 1, 319, 1, 1, 1, 319, 319, 1, 1, 1, 1, 1, 319, 319, 319, 319, 319}, \
{1, 214, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 335, 1, 335, 1, 1, 1, 335, 1, 335, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 218, 1, 1, 1, 1, 1, 254, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 258, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 234, 177, 177, 177, 177, 177, 177, 177, 177}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 270, 1, 1, 1, 274, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 347, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 282, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 351, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 311, 1, 1, 311, 1, 1, 1, 311, 1, 1, 1, 1, 1, 1, 311, 311, 311, 311, 311}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 339, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 306, 310, 314, 318, 1}, \
{5, 98, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 31, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 35, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 39, 39, 39, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 39, 39, 39, 39, 39, 39, 39, 1, 1, 1, 1, 1, 1, 1, 1, 1, 39, 1, 1, 1, 1, 1, 1, 1, 1, 1, 39, 39, 1}, \
{1, 43, 43, 43, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 43, 43, 43, 43, 43, 43, 43, 1, 1, 1, 1, 1, 1, 1, 1, 1, 43, 1, 1, 1, 1, 1, 1, 1, 1, 1, 43, 43, 1}, \
{1, 47, 47, 47, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 47, 47, 47, 47, 47, 47, 47, 1, 1, 1, 1, 1, 1, 1, 1, 1, 47, 1, 1, 1, 1, 1, 1, 1, 1, 1, 47, 47, 1}, \
{1, 51, 51, 51, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 51, 51, 51, 51, 51, 51, 51, 1, 1, 1, 1, 1, 1, 1, 1, 1, 51, 1, 1, 1, 1, 1, 1, 1, 1, 1, 51, 51, 1}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 343, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{1, 291, 1, 1, 1, 1, 1, 1, 1, 1, 291, 291, 1, 1, 1, 1, 1, 1, 1, 291, 291, 291, 291, 291, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 291, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 251, 1, 1, 1, 1, 1, 251, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 55, 1, 1, 55, 1, 1, 1, 55, 1, 55, 1, 1, 1, 1, 306, 310, 55, 55, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 63, 1, 1, 63, 1, 1, 1, 63, 1, 63, 1, 1, 1, 1, 63, 63, 63, 63, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 71, 1, 1, 71, 1, 1, 1, 71, 1, 71, 1, 1, 1, 1, 71, 71, 71, 71, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 87, 1, 1, 87, 1, 1, 1, 87, 1, 87, 1, 1, 1, 1, 87, 87, 87, 87, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 79, 1, 1, 79, 1, 1, 1, 79, 1, 79, 1, 1, 1, 1, 79, 79, 79, 79, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 83, 1, 1, 83, 1, 1, 1, 83, 1, 83, 1, 1, 1, 1, 83, 83, 83, 83, 1}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 466, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 446, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 442, 173, 173, 173, 173, 173, 173, 173, 173, 173}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 95, 1, 1, 95, 1, 1, 1, 95, 1, 95, 1, 1, 1, 1, 95, 95, 95, 95, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 99, 1, 1, 99, 1, 1, 1, 99, 1, 99, 1, 1, 1, 1, 99, 99, 99, 99, 1}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 119, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 123, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 127, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 131, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 135, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 139, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 143, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 426, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 91, 1, 1, 91, 1, 1, 1, 91, 1, 91, 1, 1, 1, 1, 91, 91, 91, 91, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 59, 1, 1, 59, 1, 1, 1, 59, 1, 59, 1, 1, 1, 1, 306, 310, 59, 59, 1}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 67, 1, 1, 67, 1, 1, 1, 67, 1, 67, 1, 1, 1, 1, 67, 67, 67, 67, 1}, \
{5, 315, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 454, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 462, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 115, 1, 1, 115, 1, 1, 1, 115, 1, 115, 1, 1, 1, 1, 115, 115, 115, 115, 1}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 474, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 111, 1, 1, 111, 1, 1, 1, 111, 1, 111, 1, 1, 1, 1, 111, 111, 111, 111, 1}, \
{173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 243, 173, 173, 173, 173, 173, 173, 173, 173, 173}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 490, 1, 1, 1, 1, 1, 247, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 255, 1, 1, 1, 1, 1, 255, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 259, 1, 1, 1, 1, 1, 259, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 75, 1, 1, 75, 1, 1, 1, 75, 1, 75, 1, 1, 1, 1, 75, 75, 75, 75, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 522, 1, 1, 1, 1, 1, 1, 1, 1, 1, 234, 1, 1, 1, 1, 1, 1, 1, 1}, \
{209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 510}, \
{1, 190, 1, 1, 1, 1, 1, 194, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 518, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{1, 299, 1, 1, 1, 1, 1, 1, 1, 1, 299, 299, 1, 1, 1, 1, 1, 1, 1, 299, 299, 299, 299, 299, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 299, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 295, 1, 1, 1, 1, 1, 1, 1, 1, 295, 295, 1, 1, 1, 1, 1, 1, 1, 295, 295, 295, 295, 295, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 295, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 530, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 534}, \
{1, 303, 1, 1, 1, 1, 1, 1, 1, 1, 303, 303, 1, 1, 1, 1, 1, 1, 1, 303, 303, 303, 303, 303, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 303, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 546, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 235, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 558, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 554, 173, 173, 173, 173, 173, 173, 173, 173, 173}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 239, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{1, 307, 1, 1, 1, 1, 1, 1, 1, 1, 307, 307, 1, 1, 1, 1, 1, 1, 1, 307, 307, 307, 307, 307, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 307, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 570, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{1, 195, 1, 1, 1, 1, 1, 1, 1, 1, 195, 195, 1, 1, 1, 1, 1, 1, 1, 195, 195, 195, 195, 195, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 195, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{263, 1, 1, 1, 1, 1, 1, 1, 263, 263, 1, 263, 1, 1, 1, 1, 1, 1, 1, 263, 263, 263, 263, 263, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 582, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 82, 86, 90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 606, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 598, 1, 1, 1, 151, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 155, 1, 1, 1, 155, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 82, 86, 90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 159, 1, 1, 1, 159, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 610, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153}, \
{1, 179, 1, 1, 1, 1, 1, 1, 1, 1, 1, 179, 1, 1, 1, 1, 1, 1, 1, 179, 179, 179, 179, 179, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 179, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 634, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157}, \
{1, 98, 1, 1, 1, 1, 1, 1, 1, 1, 1, 46, 1, 1, 1, 1, 1, 1, 1, 50, 54, 58, 62, 66, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 175, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 183, 1, 1, 1, 1, 1, 1, 1, 1, 1, 183, 1, 1, 1, 1, 1, 1, 1, 183, 183, 183, 183, 183, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 183, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 191, 1, 1, 1, 1, 1, 1, 1, 1, 1, 191, 1, 1, 1, 1, 1, 1, 1, 191, 191, 191, 191, 191, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 191, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 187, 1, 1, 1, 1, 1, 1, 1, 1, 1, 187, 1, 1, 1, 1, 1, 1, 1, 187, 187, 187, 187, 187, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 187, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{147, 1, 1, 1, 1, 1, 1, 1, 147, 147, 1, 147, 1, 1, 1, 1, 1, 1, 1, 147, 147, 147, 147, 147, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 642, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 646}, \
{199, 199, 1, 1, 1, 1, 1, 1, 199, 199, 1, 199, 1, 1, 1, 1, 1, 1, 1, 199, 199, 199, 199, 199, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 199, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 98, 378, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386, 390, 394, 398, 402, 406, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 1, 546, 1, 1, 1, 1, 1, 1, 1, 314, 318, 1}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 654, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{203, 203, 1, 1, 1, 1, 1, 1, 203, 203, 1, 203, 1, 1, 1, 1, 1, 1, 1, 203, 203, 203, 203, 203, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 203, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
//==============================
const int NetG::RulesToSymbol[90] = { \
0,\
1,\
2,\
2,\
3,\
3,\
3,\
4,\
4,\
5,\
5,\
6,\
6,\
7,\
7,\
8,\
8,\
9,\
9,\
10,\
10,\
10,\
10,\
11,\
11,\
12,\
12,\
13,\
13,\
14,\
14,\
14,\
14,\
14,\
14,\
15,\
16,\
17,\
18,\
18,\
19,\
19,\
19,\
20,\
21,\
21,\
22,\
22,\
23,\
24,\
24,\
25,\
25,\
26,\
26,\
26,\
26,\
26,\
27,\
27,\
28,\
29,\
30,\
30,\
31,\
32,\
33,\
34,\
34,\
35,\
35,\
35,\
35,\
35,\
35,\
36,\
36,\
37,\
38,\
39,\
40,\
40,\
41,\
41,\
42,\
42,\
42,\
42,\
43,\
43 };
//==============================
const int NetG::RulesLength[90] = { \
1,\
1,\
0,\
2,\
1,\
1,\
1,\
1,\
1,\
1,\
1,\
1,\
1,\
1,\
3,\
1,\
3,\
1,\
2,\
1,\
1,\
1,\
3,\
1,\
1,\
4,\
1,\
4,\
6,\
1,\
1,\
1,\
1,\
1,\
1,\
1,\
8,\
1,\
1,\
3,\
2,\
2,\
2,\
1,\
0,\
2,\
1,\
1,\
4,\
3,\
5,\
1,\
1,\
1,\
1,\
1,\
1,\
1,\
1,\
3,\
2,\
1,\
0,\
2,\
2,\
8,\
1,\
0,\
2,\
1,\
1,\
3,\
5,\
3,\
5,\
3,\
5,\
2,\
4,\
3,\
1,\
3,\
1,\
0,\
2,\
4,\
8,\
10,\
2,\
4 };
//==============================
const char* const NetG::RulesName[90] = { \
"all->context ",\
"context-><DEF*> ",\
"<DEF*>->epsilon ",\
"<DEF*>-><DEF*> DEF ",\
"DEF->SYMBOLIC ",\
"DEF->NETWORK ",\
"DEF->VAR ",\
"OPERATOR->[operatmd] ",\
"OPERATOR->[operatas] ",\
"[operatmd]->multi ",\
"[operatmd]->div ",\
"[operatas]->sub ",\
"[operatas]->add ",\
"EXP_RIGHT->EXP_MUL ",\
"EXP_RIGHT->EXP_RIGHT [operatas] EXP_MUL ",\
"EXP_MUL->EXP_MINUS ",\
"EXP_MUL->EXP_MUL [operatmd] EXP_MINUS ",\
"EXP_MINUS->UNIT ",\
"EXP_MINUS->[operatas] UNIT ",\
"UNIT->ID ",\
"UNIT->CALL ",\
"UNIT->[number] ",\
"UNIT->left EXP_RIGHT right ",\
"[number]->integer ",\
"[number]->realC ",\
"ID->id squareL integer squareR ",\
"ID->id ",\
"CALL->[function1] left EXP_RIGHT right ",\
"CALL->[function2] left EXP_RIGHT comma EXP_RIGHT right ",\
"[function1]->sin ",\
"[function1]->cos ",\
"[function1]->exp ",\
"[function1]->ln ",\
"[function1]->log ",\
"[function1]->sqrt ",\
"[function2]->pow ",\
"SYMBOLIC->func id left PARA right braceL SYMBOLICBODY braceR ",\
"PARA-><SYMBOLICPARAS> ",\
"<SYMBOLICPARAS>->SYMBOLICPARA ",\
"<SYMBOLICPARAS>-><SYMBOLICPARAS> comma SYMBOLICPARA ",\
"SYMBOLICPARA->input ID ",\
"SYMBOLICPARA->para ID ",\
"SYMBOLICPARA->output ID ",\
"SYMBOLICBODY-><STATEMENT*> ",\
"<STATEMENT*>->epsilon ",\
"<STATEMENT*>-><STATEMENT*> STATEMENT ",\
"STATEMENT->VAR ",\
"STATEMENT->EXPRESSION ",\
"EXPRESSION->ID assign EXP_RIGHT semicolon ",\
"VAR->DEF_VAR ID semicolon ",\
"VAR->DEF_VAR ID assign VALUE semicolon ",\
"DEF_VAR->[type] ",\
"DEF_VAR->def ",\
"[type]->real ",\
"[type]->complex ",\
"[type]->sint ",\
"[type]->uint ",\
"[type]->bool ",\
"VALUE->EXP_RIGHT ",\
"VALUE->squareL VALUELIST squareR ",\
"VALUELIST->EXP_RIGHT VALUES ",\
"VALUES-><NEXTVALUE*> ",\
"<NEXTVALUE*>->epsilon ",\
"<NEXTVALUE*>-><NEXTVALUE*> NEXTVALUE ",\
"NEXTVALUE->comma EXP_RIGHT ",\
"NETWORK->net id left SYMBOLICPARA right braceL NETBODY braceR ",\
"NETBODY-><NET_STATEMENT*> ",\
"<NET_STATEMENT*>->epsilon ",\
"<NET_STATEMENT*>-><NET_STATEMENT*> NET_STATEMENT ",\
"NET_STATEMENT->CONSTVAR ",\
"NET_STATEMENT->EXPRESSION ",\
"NET_STATEMENT->def ID semicolon ",\
"NET_STATEMENT->def ID assign TENSORVALUE semicolon ",\
"NET_STATEMENT->TENSOR ID semicolon ",\
"NET_STATEMENT->TENSOR TENSORID assign TENSORVALUE semicolon ",\
"CONSTVAR->[type] ID semicolon ",\
"CONSTVAR->[type] ID assign VALUE semicolon ",\
"TENSORID->ID INDEXLIST ",\
"TENSOR->tensor squareL VALUELIST squareR ",\
"INDEXLIST->angleL INDEXUNITS angleR ",\
"INDEXUNITS->ID2 ",\
"INDEXUNITS->INDEXUNITS comma ID2 ",\
"ID2->id ",\
"ID2->epsilon ",\
"TENSORVALUE->SUMSYMBOL TENSORID ",\
"TENSORVALUE->SUMSYMBOL TENSORID OPERATOR TENSORID ",\
"TENSORVALUE->id INDEXLIST squareL INDEXUNITS squareR left TENSORID right ",\
"TENSORVALUE->id INDEXLIST squareL INDEXUNITS squareR left TENSORID comma TENSORID right ",\
"SUMSYMBOL->sum id ",\
"SUMSYMBOL->sum braceL INDEXUNITS braceR " };
//==============================
const int NetG::Implicit[90] = { \
0, \
0, \
1, \
1, \
0, \
0, \
0, \
0, \
0, \
1, \
1, \
1, \
1, \
1, \
0, \
1, \
0, \
1, \
0, \
0, \
0, \
0, \
0, \
1, \
1, \
0, \
0, \
0, \
0, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
0, \
0, \
1, \
1, \
0, \
0, \
0, \
0, \
1, \
1, \
0, \
0, \
0, \
0, \
0, \
0, \
0, \
1, \
1, \
1, \
1, \
1, \
0, \
0, \
0, \
0, \
1, \
1, \
0, \
0, \
0, \
1, \
1, \
0, \
0, \
0, \
0, \
0, \
0, \
0, \
0, \
0, \
0, \
0, \
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
