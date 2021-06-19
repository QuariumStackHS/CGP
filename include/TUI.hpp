#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"
#include "size.h"
using namespace std;

class View
{
protected:
    class ViewChar
    {
    public:
        friend class View;
        friend class MasterView;
        char Char;

    private:
        View *_MasterView;
        ViewChar(int, int, char);
        ViewChar(int, int, char, View *);

        int Xpos;
        int Ypos;
    };

public:
    bool Visible = 1;
    View();
    string SaveAll();
    void clear();
    void add_Horizon(string, int, int);
    void add_Vertical(string, int, int);
    void render();
    vector<ViewChar *> Chars;
    friend class MasterView;

private:
};
class MSTS
{
public:
    MSTS(string Key, string Value, string alias);
    string Save();
    string Alias;
    string _Key;
    string _Value;
};
class MSTS_Vector
{
private:
    vector<MSTS *> Mok;

public:
    MSTS_Vector();
    void push_back(MSTS *);
    MSTS *get_from_alias(string);
    MSTS *get_from_Value(string);
};

class vign : public View
{
public:
    vign(vector<string>, int, int);
    void render();
    int bigestComb = 0;
    vector<string> Comb;
    int current_index = 0;
    int x;
    int y;
};
class EditorView : public View
{
public:
    vector<MSTS *> Values;
    int current_index = 0;
    int x;
    int y;
    EditorView(int, int);
    void render();
    string SaveAll();
    void add_MSTS(MSTS *, int);
};
class dropdownlist : public View
{
protected:
    int x;
    int y;

public:
    bool isOn = 0;
    bool ischoosing = 0;
    void render();
    dropdownlist(int, int);
    string Key;
    string Alias;
    int current_index = 0;
    void add_MSTS(MSTS *, int);
    string SaveAll();
    vector<MSTS *> EA;
};
//do not use what is bellow
class Coll: public View{
    protected:
    int x;
    int y;
public:
Coll(int,int);
    void add_MSTS(MSTS *, int);
    void render();
    string SaveAll();
    vector<MSTS *> EA;
};
class DepTree:public View{
public:
        int x;
        int y;
        string name;
        string fileCFG;
        vector<DepTree*>Childs;
        DepTree(int,int);
        int AddChild(DepTree*);
        void render();
        void ChildRender(DepTree*Master,int level,int right);
        
};
class Dynamic_Property{
private:
    vector<string>Props;
public:
    void add_Prop();
    Dynamic_Property();
};
class String_S_Matrice:public View{
    protected:
    
vector<Dynamic_Property>Vectors;
public:
    int x;
    int y;
    void render();

    String_S_Matrice(int,int);
};

class MasterView
{
public:
    MasterView(int, int);
    void Render();
    void clear();
    void Display();
    void set_MSTS_Vector(MSTS_Vector*);
    void load_into_Vector();
    void addView(View *);
    void addView(EditorView *);
    void addView(dropdownlist *);
    void addView(DepTree *);
    void RemoveView(View *);
    void RemoveView(EditorView *);
    void RemoveView(dropdownlist *);
    void Save(string Filname);
    void Load(string Filname);

protected:
MSTS_Vector*dvector;
    char Buffer[MaxX][MaxY];
    vector<View *> Views;
    vector<EditorView *> DATAC;
    vector<dropdownlist *> DATAD;
    vector<DepTree *> DATAE;
    int MAXx;
    int MAXy;
};
