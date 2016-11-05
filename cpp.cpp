#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { glob_init(); return yyparse(); }

Sym::Sym(string V) { val=V; }
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::head() { ostringstream os; os<<val<<" @"<<this;
	if (nest.size()) os<<" {";
	return os.str(); }
string Sym::foot(int depth) {
	if (nest.size()) return "\n"+pad(depth)+"}";
	else return ""; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S+foot(depth); }

Str::Str(string V):Sym(V){}
string Str::head() { ostringstream os; os<<"'";
	for (int i=0;i<val.length();i++) switch (val[i]) {
		case '\r':	os<<"\\r"; break;
		case '\n':	os<<"\\n"; break;
		case '\t':	os<<"\\t"; break;
		default:	os<<val[i];
	}
	os<<"' @"<<this;
	return os.str(); }

Vector::Vector():Sym("[]") {}
string Vector::head() { ostringstream os; os<<"[ @"<<this; return os.str(); }
string Vector::foot(int depth) { return "\n"+pad(depth)+"]"; }

map<string,Sym*> glob;
void glob_init() {}

