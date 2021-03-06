/*
Header Generated By CGP
You should include this header file for test units
You should also create "T_Config.hpp"
*/
#include<T_Config.hpp>
/*---src/main.cpp---*/
#ifndef contain
	bool contain(string str, char c);
#endif
#ifndef as_cgp
	string as_cgp(char *file);
#endif
#ifndef exists
	bool exists(const std::string &name);
#endif
#ifndef split
	size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);
#endif
#ifndef countsp
	int countsp(string i);
#endif
#ifndef getch
	char getch();
#endif
#ifndef mkdir
	void mkdir(const char *p);
#endif
#ifndef recursive_mkdir
	void recursive_mkdir(const char *p);
#endif
#ifndef Get_Data
	string Get_Data(string Dependancy, string Key);
#endif
#ifndef AS
	string AS(string Deps);
#endif
#ifndef compile
	int compile(MSTS *OBJ, MSTS *SRC, MSTS *INCl, string cppV, MSTS *checkSums, MSTS *addsw, string Path, MSTS *deps);
#endif
#ifndef CopyRecursive
	void CopyRecursive(const char *src, const char *target);
#endif
#ifndef link
	int link(MSTS *OBJ, MSTS *LIBS, MSTS *Deps, string buildname, int buildT, string thisprog);
#endif
#ifndef buildTree
	DepTree *buildTree(string RGPFILE);
#endif
#ifndef Forcebuild
	void *Forcebuild(char **, int, MSTS_Vector *);
#endif
#ifndef build
	void *build(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef run
	void *run(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef list
	void *list(char **argb, int argc, MSTS_Vector *);
#endif
#ifndef _export
	void *_export(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef show_menu
	string show_menu();
#endif
#ifndef BIN_at_this
	void *BIN_at_this(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef Add_at_Bin
	void *Add_at_Bin(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef listLib
	void *listLib(char **argb, int argc, MSTS_Vector *);
#endif
#ifndef Install
	void *Install(char **argb, int argc, MSTS_Vector *);
#endif
#ifndef UnInstall
	void *UnInstall(char **argb, int argc, MSTS_Vector *);
#endif
#ifndef Add_cgp
	string Add_cgp(string f1, string f2, string Caract);
#endif
#ifndef is_dep_of
	int is_dep_of(string first, string Second);
#endif
#ifndef Merge
	void *Merge(char **argb, int argc, MSTS_Vector *);
#endif
#ifndef Build_all
	void *Build_all(char **argb, int argc, MSTS_Vector *);
#endif
#ifndef Clean
	void *Clean(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef clean
	void *clean(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef Create_scripts
	void *Create_scripts(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef Show_Parents
	void *Show_Parents(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef Backup
	void *Backup(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef Backin
	void *Backin(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef contain
	bool contain(string str, char c);
#endif
#ifndef remove
	string remove(string str, char i);
#endif
#ifndef remove
	string remove(string mainStr, string toErase);
#endif
#ifndef Create_declarations
	void Create_declarations(const char *filename, ofstream &HPP_);
#endif
#ifndef Create_Header
	void *Create_Header(char **argb, int argc, MSTS_Vector *IN);
#endif
#ifndef Create_Tests
	void *Create_Tests(char **argb, int argc, MSTS_Vector *IN);
#endif
/*---AES//src/AES.cpp---*/
#ifndef  gen_IV
	unsigned char *gen_IV(unsigned char iv[32]);
#endif
#ifndef  gen_IV
	unsigned char *gen_IV(unsigned char iv[16]);
#endif
#ifndef  Gen_Key
	unsigned char *Gen_Key(unsigned char key[32]);
#endif
#ifndef test
	int test();
#endif
/*---AES//src/AES.c---*/
/*---TUI//src/TUI.cpp---*/
#ifndef show_Vec
	void show_Vec(Deskrp *K);
#endif
#ifndef Get_arg
	EArg *Get_arg(char **argb, int argc, string k);
#endif
/*---SHA1//src/SHA1.cpp---*/
