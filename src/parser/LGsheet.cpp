#include<stdlib.h>
#include "sheet.h"

using namespace Pikachu;


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

const size_t NetG::StateCount = 175;
const size_t NetG::NonTerminalCount = 47;
const size_t NetG::TerminalCount = 52;
const size_t NetG::RulesCount = 94;
const int NetG::GOTO[175][47] = { \
{1, 6, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 14, 1, 1, 1, 18, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 22, 1, 1, 1, 1, 1, 1, 1, 1, 1, 26, 1, 1, 1, 1, 1, 30, 1, 1, 1, 34, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 682, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 74, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 86, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 246, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 178, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 190, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 206, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 174, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 178, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 1, 186, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 190, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 1, 1, 202, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 214, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 178, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 222, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 178, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 234, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 178, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 258}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 290}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 266, 270, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 286, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 306, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 330, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 326, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 322, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 342, 346, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 350, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 354, 1, 1, 26, 1, 1, 1, 1, 1, 1, 1, 1, 358, 362, 1, 366, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 534, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 538, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 378, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 390, 394, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 446, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 474, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 422, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 414, 270, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 438}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 430, 270, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 446, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 450, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 470, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 446, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 462, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 478, 482, 486, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 446, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 490, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 502, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 506, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 178, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 514, 518, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 522, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 530, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 178, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 470, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 546, 394, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 562, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 178, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 582, 586, 590, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 598, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 610, 614, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 350, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 618, 622, 626, 630, 634, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 642, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 654, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 658, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 178, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 502, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 666, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 82, 1, 654, 90, 94, 98, 102, 106, 1, 110, 114, 118, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 694, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
//==============================
const int NetG::ACTION[175][53] = { \
{11, 1, 1, 1, 1, 1, 1, 1, 11, 11, 1, 11, 1, 1, 1, 1, 1, 1, 1, 11, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{7, 1, 1, 1, 1, 1, 1, 1, 38, 42, 1, 46, 1, 1, 1, 1, 1, 1, 1, 50, 54, 58, 62, 66, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{15, 1, 1, 1, 1, 1, 1, 1, 15, 15, 1, 15, 1, 1, 1, 1, 1, 1, 1, 15, 15, 15, 15, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{31, 1, 1, 1, 1, 1, 1, 1, 31, 31, 1, 31, 1, 1, 1, 1, 1, 1, 1, 31, 31, 31, 31, 31, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{19, 1, 1, 1, 1, 1, 1, 1, 19, 19, 1, 19, 1, 1, 1, 1, 1, 1, 1, 19, 19, 19, 19, 19, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{23, 1, 1, 1, 1, 1, 1, 1, 23, 23, 1, 23, 1, 1, 1, 1, 1, 1, 1, 23, 23, 23, 23, 23, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{27, 1, 1, 1, 1, 1, 1, 1, 27, 27, 1, 27, 1, 1, 1, 1, 1, 1, 1, 27, 27, 27, 27, 27, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 574, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 298, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 70, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 227, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 231, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 235, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 239, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 243, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 78, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169}, \
{209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 250}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 63, 1, 1, 63, 1, 1, 1, 63, 1, 63, 1, 1, 1, 1, 194, 198, 63, 63, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 71, 1, 1, 71, 1, 1, 1, 71, 1, 71, 1, 1, 1, 1, 71, 71, 71, 71, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 79, 1, 1, 79, 1, 1, 1, 79, 1, 79, 1, 1, 1, 1, 79, 79, 79, 79, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 95, 1, 1, 95, 1, 1, 1, 95, 1, 95, 1, 1, 1, 1, 95, 95, 95, 95, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 87, 1, 1, 87, 1, 1, 1, 87, 1, 87, 1, 1, 1, 1, 87, 87, 87, 87, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 91, 1, 1, 91, 1, 1, 1, 91, 1, 91, 1, 1, 1, 1, 91, 91, 91, 91, 1}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 230, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 210, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 115, 1, 1, 115, 1, 1, 1, 115, 78, 115, 115, 1, 1, 1, 115, 115, 115, 115, 115}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 103, 1, 1, 103, 1, 1, 1, 103, 1, 103, 1, 1, 1, 1, 103, 103, 103, 103, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 107, 1, 1, 107, 1, 1, 1, 107, 1, 107, 1, 1, 1, 1, 107, 107, 107, 107, 1}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 131, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 135, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 139, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 143, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 147, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 151, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 155, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 51, 51, 51, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 51, 51, 51, 51, 51, 51, 51, 1, 1, 1, 1, 1, 1, 1, 1, 1, 51, 1, 1, 1, 1, 1, 1, 1, 1, 1, 51, 51, 1}, \
{1, 55, 55, 55, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 55, 55, 55, 55, 55, 55, 55, 1, 1, 1, 1, 1, 1, 1, 1, 1, 55, 1, 1, 1, 1, 1, 1, 1, 1, 1, 55, 55, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 182, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 99, 1, 1, 99, 1, 1, 1, 99, 1, 99, 1, 1, 1, 1, 99, 99, 99, 99, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 67, 1, 1, 67, 1, 1, 1, 67, 1, 67, 1, 1, 1, 1, 194, 198, 67, 67, 1}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 43, 43, 43, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 43, 43, 43, 43, 43, 43, 43, 1, 1, 1, 1, 1, 1, 1, 1, 1, 43, 1, 1, 1, 1, 1, 1, 1, 1, 1, 43, 43, 1}, \
{1, 47, 47, 47, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 47, 47, 47, 47, 47, 47, 47, 1, 1, 1, 1, 1, 1, 1, 1, 1, 47, 1, 1, 1, 1, 1, 1, 1, 1, 1, 47, 47, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 75, 1, 1, 75, 1, 1, 1, 75, 1, 75, 1, 1, 1, 1, 75, 75, 75, 75, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 111, 1, 1, 111, 1, 1, 1, 111, 1, 111, 111, 1, 1, 1, 111, 111, 111, 111, 111}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 218, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 226, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 127, 1, 1, 127, 1, 1, 1, 127, 1, 127, 1, 1, 1, 1, 127, 127, 127, 127, 1}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 123, 1, 1, 123, 1, 1, 1, 123, 1, 123, 1, 1, 1, 1, 123, 123, 123, 123, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 119, 1, 1, 119, 1, 1, 1, 119, 1, 119, 119, 1, 1, 1, 119, 119, 119, 119, 119}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 83, 1, 1, 83, 1, 1, 1, 83, 1, 83, 1, 1, 1, 1, 83, 83, 83, 83, 1}, \
{5, 254, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 262, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169}, \
{169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 262, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169}, \
{1, 274, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 347, 1, 347, 1, 1, 1, 347, 1, 347, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 278, 1, 1, 1, 1, 1, 282, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 335, 1, 335, 1, 1, 1, 335, 1, 335, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 343, 1, 343, 1, 1, 1, 343, 1, 343, 1, 1, 1, 1, 1, 1, 1}, \
{1, 274, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 347, 1, 347, 1, 1, 1, 347, 1, 347, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 375, 1, 1, 1, 1, 1, 375, 1, 375, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 339, 1, 339, 1, 1, 1, 339, 1, 339, 1, 1, 1, 1, 1, 1, 1}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 294, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{59, 1, 1, 1, 1, 1, 1, 1, 59, 59, 1, 59, 1, 1, 1, 1, 1, 1, 1, 59, 59, 59, 59, 59, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 302, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 310, 314, 318, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 334, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 179, 1, 1, 1, 179, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 183, 1, 1, 1, 183, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 175, 1, 1, 1, 175, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 338, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153}, \
{1, 283, 1, 1, 1, 1, 1, 1, 1, 1, 283, 283, 1, 1, 1, 1, 1, 1, 1, 283, 283, 283, 283, 283, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 283, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 570, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157}, \
{1, 122, 1, 1, 1, 1, 1, 1, 1, 1, 370, 374, 1, 1, 1, 1, 1, 1, 1, 50, 54, 58, 62, 66, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 279, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 558}, \
{1, 295, 1, 1, 1, 1, 1, 1, 1, 1, 295, 295, 1, 1, 1, 1, 1, 1, 1, 295, 295, 295, 295, 295, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 295, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 287, 1, 1, 1, 1, 1, 1, 1, 1, 287, 287, 1, 1, 1, 1, 1, 1, 1, 287, 287, 287, 287, 287, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 287, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 291, 1, 1, 1, 1, 1, 1, 1, 1, 291, 291, 1, 1, 1, 1, 1, 1, 1, 291, 291, 291, 291, 291, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 291, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 498, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 382, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 386}, \
{1, 299, 1, 1, 1, 1, 1, 1, 1, 1, 299, 299, 1, 1, 1, 1, 1, 1, 1, 299, 299, 299, 299, 299, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 299, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 398, 1, 1, 1, 1, 1, 402, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 494, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 426, 177, 177, 177, 177, 177, 177, 177, 177}, \
{1, 406, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 410, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 367, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 274, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 347, 1, 347, 1, 1, 1, 347, 1, 347, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 278, 1, 418, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 371, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 262, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169}, \
{1, 274, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 347, 1, 347, 1, 1, 1, 347, 1, 347, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 278, 1, 1, 1, 1, 1, 1, 1, 434, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 331, 1, 1, 331, 1, 1, 1, 331, 331, 1, 1, 1, 1, 1, 331, 331, 331, 331, 331}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 442, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 426, 177, 177, 177, 177, 177, 177, 177, 177}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 454, 1, 1, 1, 458, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 359, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 466, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 363, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 323, 1, 1, 323, 1, 1, 1, 323, 1, 1, 1, 1, 1, 1, 323, 323, 323, 323, 323}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 351, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 194, 198, 166, 170, 1}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 35, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 39, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 355, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{1, 303, 1, 1, 1, 1, 1, 1, 1, 1, 303, 303, 1, 1, 1, 1, 1, 1, 1, 303, 303, 303, 303, 303, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 303, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 263, 1, 1, 1, 1, 1, 263, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 510, 173, 173, 173, 173, 173, 173, 173, 173, 173}, \
{5, 327, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 255, 173, 173, 173, 173, 173, 173, 173, 173, 173}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 526, 1, 1, 1, 1, 1, 259, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 267, 1, 1, 1, 1, 1, 267, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 271, 1, 1, 1, 1, 1, 271, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 554, 1, 1, 1, 1, 1, 1, 1, 1, 1, 426, 1, 1, 1, 1, 1, 1, 1, 1}, \
{209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 542}, \
{1, 398, 1, 1, 1, 1, 1, 402, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 550, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{1, 311, 1, 1, 1, 1, 1, 1, 1, 1, 311, 311, 1, 1, 1, 1, 1, 1, 1, 311, 311, 311, 311, 311, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 311, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 307, 1, 1, 1, 1, 1, 1, 1, 1, 307, 307, 1, 1, 1, 1, 1, 1, 1, 307, 307, 307, 307, 307, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 307, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 566, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 207, 1, 1, 1, 1, 1, 1, 1, 1, 207, 207, 1, 1, 1, 1, 1, 1, 1, 207, 207, 207, 207, 207, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 207, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{275, 1, 1, 1, 1, 1, 1, 1, 275, 275, 1, 275, 1, 1, 1, 1, 1, 1, 1, 275, 275, 275, 275, 275, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 578, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 310, 314, 318, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 602, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 594, 1, 1, 1, 163, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 167, 1, 1, 1, 167, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 310, 314, 318, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 171, 1, 1, 1, 171, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 606, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153}, \
{1, 191, 1, 1, 1, 1, 1, 1, 1, 1, 1, 191, 1, 1, 1, 1, 1, 1, 1, 191, 191, 191, 191, 191, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 191, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 678, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157}, \
{1, 122, 1, 1, 1, 1, 1, 1, 1, 1, 1, 638, 1, 1, 1, 1, 1, 1, 1, 50, 54, 58, 62, 66, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 187, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 195, 1, 1, 1, 1, 1, 1, 1, 1, 1, 195, 1, 1, 1, 1, 1, 1, 1, 195, 195, 195, 195, 195, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 195, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 203, 1, 1, 1, 1, 1, 1, 1, 1, 1, 203, 1, 1, 1, 1, 1, 1, 1, 203, 203, 203, 203, 203, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 203, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 199, 1, 1, 1, 1, 1, 1, 1, 1, 1, 199, 1, 1, 1, 1, 1, 1, 1, 199, 199, 199, 199, 199, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 199, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 122, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 219, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{5, 223, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 646, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 650}, \
{1, 211, 1, 1, 1, 1, 1, 1, 1, 1, 1, 211, 1, 1, 1, 1, 1, 1, 1, 211, 211, 211, 211, 211, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 211, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 662, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 247, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 674, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 670, 173, 173, 173, 173, 173, 173, 173, 173, 173}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 251, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{1, 215, 1, 1, 1, 1, 1, 1, 1, 1, 1, 215, 1, 1, 1, 1, 1, 1, 1, 215, 215, 215, 215, 215, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 215, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{159, 1, 1, 1, 1, 1, 1, 1, 159, 159, 1, 159, 1, 1, 1, 1, 1, 1, 1, 159, 159, 159, 159, 159, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 686, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 690}, \
{315, 315, 1, 1, 1, 1, 1, 1, 315, 315, 315, 315, 1, 1, 1, 1, 1, 1, 1, 315, 315, 315, 315, 315, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 315, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 122, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 138, 142, 146, 150, 154, 158, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 662, 1, 1, 1, 1, 1, 1, 1, 166, 170, 1}, \
{137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 698, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
{319, 319, 1, 1, 1, 1, 1, 1, 319, 319, 319, 319, 1, 1, 1, 1, 1, 1, 1, 319, 319, 319, 319, 319, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 319, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
//==============================
const int NetG::RulesToSymbol[94] = { \
0,\
1,\
2,\
2,\
3,\
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
8,\
8,\
9,\
9,\
10,\
10,\
11,\
11,\
11,\
11,\
12,\
12,\
13,\
13,\
14,\
15,\
15,\
16,\
16,\
16,\
16,\
16,\
16,\
17,\
18,\
19,\
20,\
20,\
21,\
21,\
21,\
22,\
23,\
23,\
24,\
24,\
25,\
26,\
26,\
27,\
27,\
28,\
28,\
28,\
28,\
28,\
29,\
29,\
30,\
31,\
32,\
32,\
33,\
34,\
35,\
36,\
36,\
37,\
37,\
37,\
37,\
37,\
37,\
38,\
38,\
39,\
40,\
41,\
42,\
42,\
43,\
43,\
44,\
44,\
44,\
44,\
45,\
45,\
46 };
//==============================
const int NetG::RulesLength[94] = { \
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
8,\
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
2,\
1,\
3,\
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
6,\
8,\
2,\
4,\
3 };
//==============================
const char* const NetG::RulesName[94] = { \
"all->context ",\
"context-><DEF*> ",\
"<DEF*>->epsilon ",\
"<DEF*>-><DEF*> DEF ",\
"DEF->SYMBOLIC ",\
"DEF->NETWORK ",\
"DEF->CONSTVAR ",\
"DEF->DIFF_NET ",\
"OPERATOR->[operatmd] ",\
"OPERATOR->[operatas] ",\
"[operatmd]->multi ",\
"[operatmd]->div ",\
"[operatas]->sub ",\
"[operatas]->add ",\
"DIFF_NET->def id INDEX_COMPUTE assign id SQ_INDEXUNITS SQ_INDEXUNITS semicolon ",\
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
"ID->id INDEX_COMPUTE ",\
"ID->id ",\
"INDEX_COMPUTE->squareL EXP_RIGHT squareR ",\
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
"TENSORVALUE->id INDEXLIST SQ_INDEXUNITS left TENSORID right ",\
"TENSORVALUE->id INDEXLIST SQ_INDEXUNITS left TENSORID comma TENSORID right ",\
"SUMSYMBOL->sum id ",\
"SUMSYMBOL->sum braceL INDEXUNITS braceR ",\
"SQ_INDEXUNITS->squareL INDEXUNITS squareR " };
//==============================
const int NetG::Implicit[94] = { \
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
1, \
1, \
1, \
1, \
0, \
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
0, \
0 };

int NetPreL::next(int state, const char c)
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
int NetPreL::action(int state)
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
int NetPreL::GroupGet(int accept)
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
const size_t NetPreG::StateCount = 75;
const size_t NetPreG::NonTerminalCount = 21;
const size_t NetPreG::TerminalCount = 52;
const size_t NetPreG::RulesCount = 74;
const int NetPreG::GOTO[75][21] = { \
{1, 6, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66, 70, 74, 78, 82}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
//==============================
const int NetPreG::ACTION[75][53] = { \
{11, 11, 11, 11, 11, 1, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}, \
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{7, 86, 90, 94, 98, 1, 102, 106, 110, 114, 118, 122, 126, 130, 134, 138, 142, 146, 150, 154, 158, 162, 166, 170, 174, 178, 182, 186, 190, 194, 198, 202, 206, 210, 214, 218, 222, 226, 230, 234, 238, 242, 246, 250, 254, 258, 262, 266, 270, 274, 278, 282, 286}, \
{15, 15, 15, 15, 15, 1, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15}, \
{19, 19, 19, 19, 19, 1, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19}, \
{27, 27, 27, 27, 27, 1, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27}, \
{1, 1, 1, 1, 294, 298, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{23, 23, 23, 23, 23, 1, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23}, \
{55, 55, 55, 55, 55, 1, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55}, \
{59, 59, 59, 59, 59, 1, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59}, \
{67, 67, 67, 67, 67, 1, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67}, \
{71, 71, 71, 71, 71, 1, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71}, \
{75, 75, 75, 75, 75, 1, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75}, \
{79, 79, 79, 79, 79, 1, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79}, \
{83, 83, 83, 83, 83, 1, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83}, \
{87, 87, 87, 87, 87, 1, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87}, \
{91, 91, 91, 91, 91, 1, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91}, \
{95, 95, 95, 95, 95, 1, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95}, \
{99, 99, 99, 99, 99, 1, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}, \
{103, 103, 103, 103, 103, 1, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103}, \
{107, 107, 107, 107, 107, 1, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107}, \
{111, 111, 111, 111, 111, 1, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111}, \
{115, 115, 115, 115, 115, 1, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115}, \
{119, 119, 119, 119, 119, 1, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119}, \
{63, 63, 63, 63, 63, 1, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63}, \
{1, 1, 1, 1, 47, 47, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 290, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{123, 123, 123, 123, 123, 1, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123}, \
{127, 127, 127, 127, 127, 1, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127}, \
{131, 131, 131, 131, 131, 1, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131}, \
{135, 135, 135, 135, 135, 1, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135}, \
{139, 139, 139, 139, 139, 1, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 139}, \
{143, 143, 143, 143, 143, 1, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143}, \
{147, 147, 147, 147, 147, 1, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147}, \
{151, 151, 151, 151, 151, 1, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151}, \
{155, 155, 155, 155, 155, 1, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155}, \
{159, 159, 159, 159, 159, 1, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159}, \
{163, 163, 163, 163, 163, 1, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163}, \
{167, 167, 167, 167, 167, 1, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167}, \
{171, 171, 171, 171, 171, 1, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171}, \
{175, 175, 175, 175, 175, 1, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175}, \
{179, 179, 179, 179, 179, 1, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179}, \
{183, 183, 183, 183, 183, 1, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183}, \
{187, 187, 187, 187, 187, 1, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187}, \
{191, 191, 191, 191, 191, 1, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191}, \
{195, 195, 195, 195, 195, 1, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195}, \
{199, 199, 199, 199, 199, 1, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199}, \
{203, 203, 203, 203, 203, 1, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203}, \
{207, 207, 207, 207, 207, 1, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207}, \
{211, 211, 211, 211, 211, 1, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211}, \
{215, 215, 215, 215, 215, 1, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215}, \
{219, 219, 219, 219, 219, 1, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}, \
{223, 223, 223, 223, 223, 1, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223}, \
{227, 227, 227, 227, 227, 1, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227}, \
{231, 231, 231, 231, 231, 1, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231}, \
{235, 235, 235, 235, 235, 1, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235}, \
{239, 239, 239, 239, 239, 1, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239}, \
{243, 243, 243, 243, 243, 1, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243}, \
{247, 247, 247, 247, 247, 1, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247}, \
{251, 251, 251, 251, 251, 1, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251}, \
{255, 255, 255, 255, 255, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255}, \
{259, 259, 259, 259, 259, 1, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259, 259}, \
{263, 263, 263, 263, 263, 1, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263, 263}, \
{267, 267, 267, 267, 267, 1, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267, 267}, \
{271, 271, 271, 271, 271, 1, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271}, \
{275, 275, 275, 275, 275, 1, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275, 275}, \
{31, 31, 31, 31, 31, 1, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, \
{35, 35, 35, 35, 35, 1, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35}, \
{279, 279, 279, 279, 279, 1, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279}, \
{283, 283, 283, 283, 283, 1, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283}, \
{287, 287, 287, 287, 287, 1, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287, 287}, \
{291, 291, 291, 291, 291, 1, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291, 291}, \
{295, 295, 295, 295, 295, 1, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295, 295}, \
{1, 1, 1, 1, 51, 51, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{39, 39, 39, 39, 39, 1, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39}, \
{43, 43, 43, 43, 43, 1, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43} };
//==============================
const int NetPreG::RulesToSymbol[74] = { \
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
7,\
7,\
7,\
7,\
7,\
7,\
7,\
7,\
7,\
7,\
7,\
7,\
8,\
9,\
9,\
10,\
11,\
11,\
11,\
11,\
11,\
11,\
11,\
11,\
11,\
11,\
11,\
12,\
12,\
12,\
12,\
12,\
13,\
13,\
13,\
13,\
13,\
13,\
14,\
15,\
15,\
15,\
16,\
16,\
16,\
16,\
17,\
17,\
17,\
17,\
17,\
17,\
17,\
17,\
18,\
18,\
19,\
19,\
20 };
//==============================
const int NetPreG::RulesLength[74] = { \
1,\
1,\
0,\
2,\
1,\
1,\
1,\
1,\
1,\
2,\
2,\
1,\
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
1 };
//==============================
const char* const NetPreG::RulesName[74] = { \
"all->pretreat ",\
"pretreat-><DEF*> ",\
"<DEF*>->epsilon ",\
"<DEF*>-><DEF*> DEF ",\
"DEF->[anntation] ",\
"DEF->ANY ",\
"DEF->INCLUDE ",\
"[anntation]->anntationS ",\
"[anntation]->anntationM ",\
"INCLUDE->MACRO string ",\
"INCLUDE->MACRO header ",\
"MACRO->include ",\
"MACRO->include spaces ",\
"ANY->[id] ",\
"ANY->[number] ",\
"ANY->string ",\
"ANY->[instruct] ",\
"ANY->[reserved] ",\
"ANY->[type] ",\
"ANY->[function1] ",\
"ANY->[function2] ",\
"ANY->[format] ",\
"ANY->[division] ",\
"ANY->[braket] ",\
"ANY->[operatmd] ",\
"ANY->[operatas] ",\
"ANY->[assignments] ",\
"[id]->id ",\
"[number]->integer ",\
"[number]->realC ",\
"[instruct]->sum ",\
"[reserved]->func ",\
"[reserved]->net ",\
"[reserved]->tensor ",\
"[reserved]->def ",\
"[reserved]->input ",\
"[reserved]->output ",\
"[reserved]->para ",\
"[reserved]->return ",\
"[reserved]->for ",\
"[reserved]->if ",\
"[reserved]->else ",\
"[type]->real ",\
"[type]->complex ",\
"[type]->sint ",\
"[type]->uint ",\
"[type]->bool ",\
"[function1]->sin ",\
"[function1]->cos ",\
"[function1]->exp ",\
"[function1]->ln ",\
"[function1]->log ",\
"[function1]->sqrt ",\
"[function2]->pow ",\
"[format]->spaces ",\
"[format]->enters ",\
"[format]->tab ",\
"[division]->semicolon ",\
"[division]->colon ",\
"[division]->dot ",\
"[division]->comma ",\
"[braket]->braceL ",\
"[braket]->braceR ",\
"[braket]->left ",\
"[braket]->right ",\
"[braket]->squareL ",\
"[braket]->squareR ",\
"[braket]->angleL ",\
"[braket]->angleR ",\
"[operatmd]->multi ",\
"[operatmd]->div ",\
"[operatas]->sub ",\
"[operatas]->add ",\
"[assignments]->assign " };
//==============================
const int NetPreG::Implicit[74] = { \
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
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1, \
1 };








