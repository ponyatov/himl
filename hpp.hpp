#ifndef _H_HPP
#define _H_HPP

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

struct Sym {
	string val;
	Sym(string);
	vector<Sym*> nest; void push(Sym*);
	virtual string dump(int=0); virtual string head(); string pad(int);
};
extern map<string,Sym*> glob;
extern void glob_init();

struct Str:Sym { Str(string); string head(); };

struct Vector:Sym { Vector(); };

extern int yylex();
extern int yylineno;
extern char* yytext;

#define TOC(C,X) { \
	if (glob[yytext]) { yylval.o = glob[yytext]; } \
	else { yylval.o = new C(yytext); glob[yytext] = yylval.o; } \
	return X; }
#define TOS(C,X) { \
	if (glob[LexString]) { yylval.o = glob[LexString]; } \
	else { yylval.o = new C(LexString); glob[LexString] = yylval.o; } \
	return X; }

extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_HPP

