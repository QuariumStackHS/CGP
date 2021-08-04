/*

@author QuariumStackHS

this is an exemple of what you can do using TUI.hpp and TUI.cpp in this Repository

*/
#include <Aes.hpp>
#include <CLAB.hpp>
#include <Keys.h>
#include <Main.h>
#include <SHA1.hpp>
#include <TUI.hpp>
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
namespace fs = std::filesystem;
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#ifndef contain
bool contain(string str, char c);
#endif
#include <USR.h>
#include <termios.h>
using namespace std;
#include <unistd.h>
string as_cgp(char *file)
{
        int i = 0;
        bool isinext;
        string ext;
        while (file[i] != '\0')
        {
                if (file[i] == '.')
                {
                        isinext = 1;
                }
                else if (isinext)
                {
                        ext.push_back(file[i]);
                }
                i++;
        }

        if (strcmp(ext.c_str(), "cgp") == 0)
                return file;
        return ((((string)file) + ".cgp"));
}
int forcebuild = 0;
bool exists(const std::string &name)
{
        if (FILE *file = fopen(name.c_str(), "r"))
        {
                fclose(file);
                return true;
        }
        else
        {
                return false;
        }
}
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
        size_t pos = txt.find(ch);
        size_t initialPos = 0;
        strs.clear();

        // Decompose statement
        while (pos != std::string::npos)
        {
                strs.push_back(txt.substr(initialPos, pos - initialPos));
                initialPos = pos + 1;

                pos = txt.find(ch, initialPos);
        }

        // Add the last one
        strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

        return strs.size();
}
int countsp(string i)
{
        vector<string> kl;
        int nbr = 0;
        split(i, kl, ' ');
        for (int j = 0; j < kl.size(); j++)
        {
                if ((strcmp(kl[j].c_str(), "")) != 0 && (strcmp(kl[j].c_str(), " ") != 0))
                        nbr++;
        }
        return nbr;
}
char getch()
{
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror("tcsetattr ~ICANON");
        return (buf);
}
/*
        Reltt.exe
<-|config|Objects|Linking|->





*/
void mkdir(const char *p)
{
        system((((string) "mkdir ") + p + " &>/dev/null").c_str());
}
void recursive_mkdir(const char *p)
{
        vector<string> kl;
        vector<string> Steps;
        split(p, kl, '/');
        string current;
        for (int i = 0; i < kl.size(); i++)
        {
                current += kl[i] + '/';
                mkdir(current.c_str());
        }
}

string Get_Data(string Dependancy, string Key)
{
        //Alias ='Value'\n
        vector<string> Path;
        split(Dependancy, Path, '/');
        string filename = "";
        for (int i = 0; i < Path.size() - 1; i++)
        {
                filename += Path[i] + '/';
        }
        string fname(filename + ".cgp/" + as_cgp((char *)Path[Path.size() - 1].c_str()));

        //cout<<"Data"<<(filename+".cgp/"+ as_cgp((char*)Path[Path.size()-1].c_str())).c_str()<<endl;
        //cout<<filename<<":"<<fname<<endl;
        ifstream myfile(fname);
        string line;
        if (myfile.is_open())
        {

                while (getline(myfile, line))
                {
                        if (strcmp(line.c_str(), ""))
                        {
                                //cout << line << endl;

                                //char i;
                                //cin>>i;
                                string Alias = "";
                                string Value = "";

                                for (int i = 0; i < line.size(); i++)
                                {
                                        int Stage = 0;
                                        if (Stage == 0)
                                        {
                                                if ((line[i] == '='))
                                                {
                                                        //cout << "Stage 1 enclenched" << endl;
                                                        for (int k = i; k < line.size(); k++)
                                                        {
                                                                if ((line[k] == '\'') && (Stage == 0))
                                                                {
                                                                        Stage++;
                                                                }
                                                                if (Stage == 1)
                                                                {
                                                                        if (line[k] != '\'')
                                                                        {
                                                                                Value.push_back(line[k]);
                                                                        }

                                                                        else
                                                                        {
                                                                                i = line.size() + 1;
                                                                        }
                                                                }
                                                        }
                                                }
                                                else
                                                {
                                                        if (line[i] != ' ')
                                                                Alias.push_back(line[i]);
                                                }
                                        }
                                }
                                //cout << Value << " : " << Alias << Alias.size() << endl;
                                if (strcmp(Alias.c_str(), "") == 0)
                                {
                                }
                                else
                                {
                                        if (strcmp(Alias.c_str(), Key.c_str()) == 0)
                                        {
                                                myfile.close();
                                                //cout<<Value<<endl;
                                                return Value;
                                        }
                                }
                        }
                }
                //char fd;
                //cin>>fd;
                myfile.close();
        }

        else if (Dependancy[0] != '-' && Dependancy[0] != '.' && !contain(Dependancy, '/') && (strcmp("", Dependancy.c_str()) != 0))
                cout << "Unable to Load Dependancy\"" << Dependancy << "\"" << endl;
        return "";
}
string AS(string Deps)
{
        vector<string> Path;
        split(Deps, Path, '/');
        string filename = "";
        for (int i = 0; i < Path.size() - 1; i++)
        {
                filename += Path[i] + '/';
        }
        return filename;
}
int compile(MSTS *OBJ, MSTS *SRC, MSTS *INCl, string cppV, MSTS *checkSums, MSTS *addsw, string Path, MSTS *deps)
{
        //cout<<addsw->_Value<<endl;
        //char i;
        //cin>>i;

        vector<string> Sha;
        vector<string> OBJs;
        vector<string> SRCs;
        vector<string> IN;
        vector<string> Deps;
        split(INCl->_Value, IN, ' ');
        split(OBJ->_Value, OBJs, ' ');
        split(SRC->_Value, SRCs, ' ');
        split(deps->_Value, Deps, ' ');
        split(checkSums->_Value, Sha, ' ');
        //Add_cgp()
        for (int i = 0; i < OBJs.size(); i++)
        {

                vector<string> Paths;
                split(OBJs[i], Paths, '/');
                string fpa;
                for (int j = 0; j < Paths.size() - 1; j++)
                {
                        fpa += Paths[j] + '/';
                }
                recursive_mkdir(fpa.c_str());
        }
        string includestring;
        string Checks;
        for (int i = 0; i < Deps.size(); i++)
        {
                vector<string> kl23;
                split(Get_Data(Deps[i], "source.includes"), kl23, ' ');
                for (int j = 0; j < kl23.size(); j++)
                {
                        if (!((strcmp(kl23[j].c_str(), " ") == 0) || (strcmp(kl23[j].c_str(), "") == 0)))
                                includestring += " -I" + AS(Deps[i]) + kl23[j];
                }
        }
        //for(int i=0;OBJ)

        int ret = 0;
        for (int i = 0; i < IN.size(); i++)
        {
                if (!((strcmp(IN[i].c_str(), " ") == 0) || (strcmp(IN[i].c_str(), "") == 0)))
                {
                        includestring += " -I" + IN[i];
                }
        }
        //cout<<includestring<<endl;

        /*for (int i = 0; i < Sha.size(); i++)
        {
                if (!((strcmp(Sha[i].c_str(), " ") == 0) || (strcmp(Sha[i].c_str(), "") == 0)))
                {
                        //Checks += Sha[i]+' ';
                }
        }*/
        checkSums->_Value = "";
        for (int i = 0; i < OBJs.size(); i++)
        {
                if ((!((strcmp(OBJs[i].c_str(), " ") == 0) || (strcmp(OBJs[i].c_str(), "") == 0))) && (!((strcmp(SRCs[i].c_str(), "") == 0) || (strcmp(SRCs[i].c_str(), " ") == 0))))
                {
                        string VP;
                        if (strcmp(AS(Path).c_str(), "") == 0)
                        {
                                VP = "";
                        }
                        else
                        {
                                VP = ""; /*AS(Path);
                                recursive_mkdir(VP.c_str());
                                */
                        }
                        string Shas = "";
                        Shas = SHA1::from_file(VP + SRCs[i]);
                        bool havetocompile = 0;
                        //cout<<Sha[i].c_str()<<endl;
                        if (exists("./" + VP + OBJs[i]) == false)
                        {
                                cout << BOLDRED << "Missing Object:\"" << RESET << BLUE << VP + OBJs[i] << BOLDRED << "\"!\nFall back did " << RESET;
                                havetocompile = 1;
                        }

                        else if (forcebuild == 1)
                        {
                                havetocompile = 1;
                        }
                        else if (Sha.size() < i)
                        {
                                havetocompile = 1;
                        }
                        else if ((strcmp(Sha[i].c_str(), Shas.c_str()) == 0))
                        {
                                cout << GREEN << "Object:\"" << YELLOW << VP + SRCs[i] << GREEN << "\" same checksum in the last compilation!(" << YELLOW << Shas << GREEN << ")" << endl;
                        }
                        else if ((strcmp(Sha[i].c_str(), "") == 0) || (strcmp(Sha[i].c_str(), " ") == 0))
                        {
                                Sha[i] = "Null";
                                cout << "sha=null" << endl;
                                havetocompile = 1;
                        }
                        else if ((strcmp(Sha[i].c_str(), Shas.c_str()) != 0))
                        {
                                havetocompile = 1;
                        }
                        else
                        {
                                havetocompile = 0;
                        }
                        //cout << Shas << endl;
                        checkSums->_Value += Shas + ' ';
                        if (havetocompile)
                        {

                                stringstream ss;
                                ss << "g++ -w -std=" << cppV << " -c -o " << VP << OBJs[i] << " " << VP + SRCs[i] << includestring << " " << addsw->_Value;
                                ret = system(ss.str().c_str());
                                //cout << ss.str() << endl;
                                if (ret == 0)
                                {
                                        cout << GREEN << "Compiled: \"" << YELLOW << VP + SRCs[i] << GREEN << "\"" << BLUE << " Successfully" << GREEN << "!" << RESET << endl;
                                }
                                else
                                {
                                        cout << fs::current_path() << endl;
                                        cout << RED << "Error while trying to compile \"" << YELLOW << AS(Path) + SRCs[i] << RED << "\" !" << RESET << endl;
                                        cout << ss.str() << " = " << ret / 256 << endl;
                                }
                        }
                }
                else
                {
                        //cout<<"invalid"<<endl;
                }
        }
        //cout<<checkSums->_Value<<endl;
        return ret;
}

void CopyRecursive(const char *src, const char *target)
{
        try
        {
                fs::copy(src, target, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
        }
        catch (std::exception &e)
        {
                //std::cout << e.what();
        }
}
int link(MSTS *OBJ, MSTS *LIBS, MSTS *Deps, string buildname, int buildT, string thisprog)
{
        if (buildT != 2)
        {
                vector<string> Dependancys;
                string Dependancys_libs;
                split(Deps->_Value, Dependancys, ' ');
                string Objects;

                for (int i = 0; i < Dependancys.size(); i++)
                { //cout<<Dependancys[i]<<endl;
                        if (strcmp(Dependancys[i].c_str(), "") != 0)
                        {
                                string VP;
                                if (strcmp(AS(Dependancys[i]).c_str(), "") == 0)
                                {
                                        VP = "";
                                }
                                else
                                {
                                        VP = AS(Dependancys[i]);
                                        //cout<<VP<<":"<<VP+Dependancys[i]<<endl;
                                        //recursive_mkdir(VP.c_str());
                                }
                                string exename = Get_Data(Dependancys[i], "Config.Exe");
                                int buildtype;

                                try
                                {
                                        buildtype = stoi(Get_Data(Dependancys[i], "Build.Type"));

                                        string compileDepcommand = thisprog + " " + Dependancys[i];
                                        if (forcebuild == 1)
                                                compileDepcommand += " --force";

                                        compileDepcommand += " --build";
                                        string srcF = AS(Dependancys[i]) + exename;
                                        string DestF = exename;
                                        vector<string> splitedDepsOBj;
                                        switch (buildtype)
                                        {
                                        case 0:
                                                cout << "Dependancy \"" << VP + Dependancys[i] << "\" as a builtype of 0" << endl;
                                                break;
                                        case 1:

                                                system(compileDepcommand.c_str());

                                                CopyRecursive(srcF.c_str(), DestF.c_str());
                                                Dependancys_libs += (" " + srcF);
                                                break;
                                        case 2:
                                                Objects = Get_Data(Dependancys[i], "source.cppobj");
                                                system(compileDepcommand.c_str());

                                                split(Objects, splitedDepsOBj, ' ');

                                                for (int p = 0; p < splitedDepsOBj.size(); p++)
                                                {
                                                        if ((strcmp(splitedDepsOBj[p].c_str(), " ") != 0) && (strcmp(splitedDepsOBj[p].c_str(), "") != 0))
                                                        {
                                                                Dependancys_libs += (" " + AS(Dependancys[i]) + splitedDepsOBj[p]);
                                                        }
                                                }

                                                break;
                                        default:
                                                break;
                                        }
                                }
                                catch (const std::exception &e)
                                {
                                }
                        }
                }
                stringstream ss;
                ss << "g++ " << OBJ->_Value << LIBS->_Value << "-o " << buildname << Dependancys_libs;
                int sw;
                switch (buildT)
                {
                case 0:
                        /* code */
                        sw = system(ss.str().c_str());

                        break;
                case 1:
                        ss << " -shared";
                        sw = system(ss.str().c_str());

                        break;
                case 2:

                        /* code */
                        break;
                default:
                        break;
                }
                if (sw == 0)
                {
                        cout << BLUE << "Linked: \"" << YELLOW << buildname << GREEN << "\"" << BLUE << " Successfully" << GREEN << "!" << RESET << endl;
                }
                else
                {
                        cout << ss.str() << " = " << sw / 256 << endl;
                }
                vector<string> objects;
                split(OBJ->_Value, objects, ' ');
                for (int i = 0; i < objects.size(); i++)
                {
                        if (!(strcmp(objects[i].c_str(), " ") == 0) || !(strcmp(objects[i].c_str(), "") == 0))
                        {
                                //cout<<objects[i]<<endl;
                                //remove(objects[i].c_str());
                        }
                }
        }
        //ss<<" &>> Logs.GP";
}

DepTree *buildTree(string RGPFILE)
{
        vector<string> Dependancys;
        DepTree *MasterNode = new DepTree(5, 5);
        // cout<<Deps->_Value<<endl;
        //cout<<RGPFILE<<endl;
        vector<string> Fullpath;
        split(Get_Data(RGPFILE, "Config.Exe"), Fullpath, '/');
        MasterNode->name = Fullpath[Fullpath.size() - 1];
        vector<string> Dependancys_of_this;
        split(Get_Data(RGPFILE, "source.Deps"), Dependancys, ' ');
        for (int i = 0; i < Dependancys.size(); i++)
        {
                //cout<<Dependancys[i]<<endl;
                if (strcmp(Dependancys[i].c_str(), "") != 0)
                {

                        string exename = Get_Data(Dependancys[i], "Config.Exe");
                        //cout<<"c"<<exename<<endl;
                        //deps->name=exename;
                        //split(Get_Data(Dependancys[i], "source.Deps"), Dependancys_of_this, ' ');
                        DepTree *k = buildTree(Dependancys[i]);
                        MasterNode->AddChild(k);
                }
        }
        MasterNode->Visible = 1;

        return MasterNode;
}
void *Forcebuild(char **, int, MSTS_Vector *)
{
        forcebuild = 1;
}
void *build(char **argb, int argc, MSTS_Vector *DLL)
{
        //IN->get_from_alias("source.Checksum_sha1");
        //cout<<IN->get_from_alias("Build.Type")->_Value<<endl;
        //string fpl="";
        vector<string>fplp;
        split(argb[1],fplp,'/');
        string fpl=fplp[fplp.size()-1];
        //cout<<argb[1]<<fs::current_path()<<endl;
        //cout<<".cgp/" +fpl+ ".cgp"<<endl;
        Dyn_loader *IN = new Dyn_loader(".cgp/" +fpl+ ".cgp");
        compile(IN->get_from_alias("source.cppobj"), IN->get_from_alias("source.cppfiles"), IN->get_from_alias("source.includes"), IN->get_from_alias("G++.C++")->_Value, IN->get_from_alias("source.Checksum_sha1"), IN->get_from_alias("compile.Switchs"), argb[1], IN->get_from_alias("source.Deps"));
        link(IN->get_from_alias("source.cppobj"), IN->get_from_alias("source.Libs"), IN->get_from_alias("source.Deps"), IN->get_from_alias("Config.Exe")->_Value, argc, argb[0]);
        IN->Save(".cgp/" +fpl+ ".cgp");

}
void *run(char **argb, int argc, MSTS_Vector *IN)
{
        //IN->get_from_alias("source.Checksum_sha1");
        //cout<<IN->get_from_alias("Build.Type")->_Value<<endl;
        //compile(IN->get_from_alias("source.cppobj"), IN->get_from_alias("source.cppfiles"), IN->get_from_alias("source.includes"), IN->get_from_alias("G++.C++")->_Value, IN->get_from_alias("source.Checksum_sha1"), IN->get_from_alias("compile.Switchs"));
        //link(IN->get_from_alias("source.cppobj"), IN->get_from_alias("source.Libs"), IN->get_from_alias("source.Deps"), IN->get_from_alias("Config.Exe")->_Value, argc, argb[0]);
        string cmd = "./" + IN->get_from_alias("Config.Exe")->_Value;
        system(cmd.c_str());
}

void *list(char **argb, int argc, MSTS_Vector *)
{
        std::string path(".cgp/");
        std::string ext(".cgp");
        for (auto &p : fs::recursive_directory_iterator(path))
        {
                if (p.path().extension() == ext)
                        std::cout << GREEN << "Found:" << YELLOW << p.path().stem().string() << RESET << endl;
        }
}
void *_export(char **argb, int argc, MSTS_Vector *IN)
{
        string exportPath = Get_arg(argb, argc, "--export")->_Right;
        recursive_mkdir(exportPath.c_str());
        string ss = (exportPath) + "/.cgp/";
        recursive_mkdir(ss.c_str());

        string thiscfg = IN->get_from_alias("thiscfg")->_Value;
        ss = exportPath + '/' + thiscfg;
        CopyRecursive(thiscfg.c_str(), ss.c_str());

        //CopyRecursive();
        vector<string> source;
        vector<string> Objfolder;
        vector<string> Deps;
        //cout<<thiscfg<<endl;
        vector<string> dirs;
        split(IN->get_from_alias("Config.Exe")->_Value, dirs, '/');
        string patha = exportPath + "/";
        for (int j = 0; j < dirs.size() - 1; j++)
        {
                patha += dirs[j] + '/';
        }
        recursive_mkdir(patha.c_str());
        split(IN->get_from_alias("source.Deps")->_Value, Deps, ' ');
        split(IN->get_from_alias("source.cppfiles")->_Value, source, ' ');
        split(IN->get_from_alias("source.cppobj")->_Value, Objfolder, ' ');
        for (int i = 0; i < Objfolder.size(); i++)
        {
                if ((strcmp(Objfolder[i].c_str(), " ") != 0) && (strcmp(Objfolder[i].c_str(), "") != 0))
                {
                        vector<string> each;
                        string jk = "";
                        split(Objfolder[i], each, '/');
                        for (int j = 0; j < each[j].size(); j++)
                                jk += each[j] + '/';
                        //cout << jk << endl;
                        recursive_mkdir((exportPath + '/' + jk).c_str());
                }
        }
        //cout<<IN->get_from_alias("source.cppfiles")->_Value<<endl;;
        for (int i = 0; i < source.size(); i++)
        {
                //cout<<source[i]<<endl;
                if ((strcmp(source[i].c_str(), " ") != 0) && (strcmp(source[i].c_str(), "") != 0))
                {
                        vector<string> dir;
                        split(source[i], dir, '/');
                        string path = exportPath + "/";
                        for (int j = 0; j < dir.size() - 1; j++)
                        {
                                path += dir[j] + '/';
                        }
                        recursive_mkdir(path.c_str());
                        path += dir[dir.size() - 1];
                        //cout<<path<<endl;
                        CopyRecursive(source[i].c_str(), path.c_str());
                }
        }
        for (int i = 0; i < Deps.size(); i++)
        {
                if ((strcmp(Deps[i].c_str(), " ") != 0) && (strcmp(Deps[i].c_str(), "") != 0))
                {
                        string bpath=fs::current_path();
                        cout<<bpath<<endl;
                        fs::current_path(AS(Deps[i]));
                        string cmd = "cgp " + remove(Deps[i],AS(Deps[i])) + " --export " + exportPath + '/' + AS(Deps[i]);
                        cout << cmd << endl;
                        system(cmd.c_str());
                        fs::current_path(bpath);
                }
        }
        vector<string> includes;
        split(IN->get_from_alias("source.includes")->_Value, includes, ' ');
        for (int i = 0; i < includes.size(); i++)
        {
                if ((strcmp(includes[i].c_str(), " ") != 0) && (strcmp(includes[i].c_str(), "") != 0))
                {
                        CopyRecursive(includes[i].c_str(), (exportPath + "/" + includes[i]).c_str());
                }
        }
}
string show_menu()
{
        bool Lock = 0;
        string Value;
        MasterView *MF = new MasterView(MaxX, MaxY);
        EditorView *Menu = new EditorView(2, 1);
        EditorView *Menu_imp = new EditorView(2, 1);
        EditorView *Legend_imp = new EditorView(MaxX / 2, 1);
        EditorView *Legend = new EditorView(MaxX / 2, 1);
        EditorView *Menu_new = new EditorView(10, 14);
        vector<string> kgb;
        kgb.push_back("Export to");
        kgb.push_back("Import from");

        vign *SEA = new vign(kgb, 1, 1);

        Menu_new->add_MSTS(new MSTS("New project name", "", ""), 0);
        Menu_new->add_MSTS(new MSTS("=>", "", ""), 1);

        Menu->add_MSTS(new MSTS(">", ((string)BLUE) + "Create New" + RESET, ""), 0);
        MF->addView(Legend);

        //string j;

        MF->addView(Menu);
        MF->addView(SEA);
        Menu_imp->Visible = 0;
        Legend_imp->Visible = 0;
        MF->addView(Legend_imp);
        MF->addView(Menu_imp);
        std::string path(".cgp/");
        std::string ext(".cgp");
        int i = 1;
        vector<string> ksd;
        vector<string> ksd_imp;
        try
        {
                for (auto &p : fs::recursive_directory_iterator(path))
                {
                        if (p.path().extension() == ext)
                        {
                                Menu->add_MSTS(new MSTS(">", p.path().stem().string(), ""), i);
                                ksd.push_back(p.path().stem().string());
                                i++;
                        }

                        //std::cout<<"\t" << p.path().stem().string()<< ".cgp at .cgp/\n\n";
                }
                if (i >= 2)
                {
                        Legend->add_MSTS(new MSTS("Project", "none", "Projectname"), 0);
                        Legend->add_MSTS(new MSTS("press I to Add to", "CGP_BIN", "Projecti"), 1);
                        Legend->add_MSTS(new MSTS("press R to Remove from", "CGP_BIN", "Projectj"), 2);
                        Legend->add_MSTS(new MSTS("Dependancys", Get_Data(ksd[i - 1], "source.Deps"), "Deps"), 3);

                        Legend->add_MSTS(new MSTS("BuildType", Get_Data(ksd[i - 1], "source.Deps"), "build"), 4);
                        Legend->add_MSTS(new MSTS("In CGP_BIN?", "", "build"), 5);
                }
        }
        catch (...)
        {
        }
        i = 0;
        try
        {
                string LibPath = ((string)CGP_BIN) + ".CGP_LIB/";
                std::string path(LibPath);

                //std::string ext(".cgp");
                for (auto &p : fs::directory_iterator(path))
                {
                        //if (p.path().extension() == ext)
                        Menu_imp->add_MSTS(new MSTS(">", p.path().stem().string(), ""), i);
                        ksd_imp.push_back(p.path().stem().string());
                        i++;
                        //std::cout << " \"" << p.path().stem().string() << "\" in (" << p.path().string() << ")" << endl;
                }
        }
        catch (...)
        {
        }
        system("stty raw");
        char ch;
        bool exp;
        bool rmv;
        while (ch != 27)
        { //cout<<(int)ch<<endl;
                if ((ch == Left) && (Lock == 0) && (SEA->current_index > 0))
                {
                        SEA->current_index--;
                }
                else if ((ch == Right) && (Lock == 0) && (SEA->current_index < SEA->Comb.size() - 1))
                {
                        SEA->current_index++;
                }

                if (SEA->current_index == 0)
                {
                        Legend->Visible = 1;
                        Menu->Visible = 1;
                        Menu_imp->Visible = 0;
                        if (Lock == 1)
                        {

                                if (((char)ch == (char)'\r'))
                                {
                                        Lock = 0;
                                        Menu_new->clear();
                                        MF->Render();
                                        MF->RemoveView(Menu_new);
                                        MF->clear();
                                }
                                else
                                {
                                        Menu_new->Values[0]->_Value += (char)ch;
                                }
                                MF->Render();
                                Menu_new->render();
                                MF->Display();
                        }
                        else if ((int)ch == (int)105)
                        {
                                //cout<<"exp"<<endl;
                                exp = 1;
                                string cmd = "cgp " + ksd[Menu->current_index - 1] + " --add";
                                system(cmd.c_str());
                        }
                        else if ((int)ch == (int)'r')
                        {
                                //cout<<"exp"<<endl;
                                fs::remove_all(((string)CGP_BIN) + ".CGP_LIB/" + ksd[Menu->current_index - 1]);
                                //cout<<((string)CGP_BIN)+".CGP_LIB/"+ksd[Menu->current_index-1]<<endl;
                                rmv = 1;
                                //string cmd="cgp "+ksd[Menu->current_index-1]+" --add";
                                //system(cmd.c_str());
                        }
                        else if ((ch == Down) && (Menu->current_index < Menu->Values.size() - 1) && (Lock == 0))
                        {

                                Menu->current_index++;
                        }
                        else if ((ch == UP) && (Menu->current_index > 0) && (Lock == 0))
                        {
                                Menu->current_index--;
                        }
                        else if ((ch == UP) && (Menu->current_index == -1) && (Lock == 0))
                        {
                                Menu_new->current_index = 0;
                                MF->Render();
                                Menu_new->render();
                                MF->Display();
                        }
                        else if ((ch == Down) && (Menu->current_index == -1) && (Lock == 0))
                        {

                                Menu_new->current_index = 1;
                                MF->Render();
                                Menu_new->render();
                                MF->Display();
                        }
                        else if (ch == 13 && (Lock == 0))
                        {
                                if (Menu->current_index > 0)
                                {
                                        Value = (Menu->Values[Menu->current_index]->_Value);
                                        //cout<<Value<<endl;
                                        ch = '\n';
                                        system("stty cooked");
                                        string v = "cgp " + Value;
                                        system(v.c_str());
                                        system("stty raw");
                                }
                                else if (Menu->current_index == -1)
                                {
                                        Value = (Menu_new->Values[0]->_Value);
                                        system("stty cooked");
                                        string v = "cgp " + Value;
                                        system(v.c_str());
                                        system("stty raw");
                                }
                                else
                                {
                                        MF->addView(Menu_new);
                                        Lock = 1;
                                        Menu->current_index = -1;
                                }
                        }
                        else if (ch == 27)
                        {
                                system("stty cooked");
                                system("clear");
                        }
                        if (Menu->current_index >= 1)
                        {
                                Legend->Values[0]->_Value = Menu->Values[Menu->current_index]->_Value;
                                if (exp == 0)
                                        Legend->Values[1]->_Value = "CGP_BIN/" + Legend->Values[0]->_Value;
                                else
                                        Legend->Values[1]->_Value = "CGP_BIN/" + Legend->Values[0]->_Value + BLUE + "(exported)" + RESET;
                                string j = Get_Data((char *)ksd[Menu->current_index - 1].c_str(), "source.Deps");
                                j += "(" + to_string(countsp(j)) + ")";
                                string k = Get_Data((char *)ksd[Menu->current_index - 1].c_str(), "Build.Type");
                                int kfbg = -1;
                                try
                                {
                                        kfbg = stoi(k);
                                }
                                catch (...)
                                {
                                }
                                switch (kfbg)
                                {
                                case 1:
                                        Legend->Values[4]->_Value = "Dynamic Lib";
                                        break;

                                case 2:
                                        Legend->Values[4]->_Value = "Static Lib";
                                        break;

                                case 0:
                                        Legend->Values[4]->_Value = "Executable";
                                        break;

                                default:
                                        Legend->Values[4]->_Value = "Unknown";
                                        break;
                                }
                                //cout<<((string)CGP_BIN) + ".CGP_LIB/" + ksd[Menu->current_index - 1] + '/' + ".cgp/" + ksd[Menu->current_index - 1] + ".cgp"<<endl;
                                switch (exists(((string)CGP_BIN) + ".CGP_LIB/" + ksd[Menu->current_index - 1] + '/' + ".cgp/" + ksd[Menu->current_index - 1] + ".cgp"))
                                {
                                case 0:
                                        Legend->Values[5]->_Value = "No";
                                        break;

                                case 1:
                                        Legend->Values[5]->_Value = "Yes";
                                        break;
                                }
                                //cout<<j<<endl;
                                Legend->Values[3]->_Value = j;
                                if (rmv)
                                        Legend->Values[2]->_Value = "CGP_BIN/" + Legend->Values[0]->_Value + RED + "(removed)" + RESET;
                                else
                                        Legend->Values[2]->_Value = "CGP_BIN/" + Legend->Values[0]->_Value;
                                rmv = 0;
                                exp = 0;
                        }
                }
                else if (SEA->current_index == 1)
                {
                        Legend->Visible = 0;
                        Menu->Visible = 0;
                        Menu_imp->Visible = 1;
                        if ((int)ch == (int)105)
                        {
                                //cout<<"exp"<<endl;
                                exp = 1;
                                string cmd = "cgp " + ksd_imp[Menu_imp->current_index] + " --import";
                                system(cmd.c_str());
                        }
                        else if ((int)ch == (int)'r')
                        {
                                //cout<<"exp"<<endl;
                                fs::remove_all(((string)CGP_BIN) + ".CGP_LIB/" + ksd_imp[Menu_imp->current_index]);
                                //cout<<((string)CGP_BIN)+".CGP_LIB/"+ksd[Menu->current_index-1]<<endl;
                                rmv = 1;
                                //string cmd="cgp "+ksd[Menu->current_index-1]+" --add";
                                //system(cmd.c_str());
                        }
                        else if ((ch == Down) && (Menu_imp->current_index < Menu_imp->Values.size() - 1) && (Lock == 0))
                        {

                                Menu_imp->current_index++;
                        }
                        else if ((ch == UP) && (Menu_imp->current_index > 0) && (Lock == 0))
                        {
                                Menu_imp->current_index--;
                        }
                        else if (ch == 27)
                        {
                                system("stty cooked");
                                system("clear");
                        }
                }

                //Legend->clear();
                Legend->render();
                system("clear");
                MF->clear();
                Menu->render();
                SEA->render();
                Menu_imp->render();
                MF->Render();

                Menu_new->render();
                MF->Display();
                ch = getchar();
        }
        delete MF;
        delete Menu;
        //cout<<Value<<endl;
        system("stty cooked");
        return "";
}
void *BIN_at_this(char **argb, int argc, MSTS_Vector *IN)
{
        string Dest = fs::current_path();
        string import_Name;
        //bool nextis;
        for (int i = 0; i < argc; i++)
        {
                if (strcmp(argb[i], "--import") == 0)
                        //nextis = 1;
                        import_Name = argb[i - 1];

                //else if (nextis)
        }
        string LibPath = ((string)CGP_BIN) + ".CGP_LIB/";
        if (!exists(LibPath))
        {
                recursive_mkdir(LibPath.c_str());
        }
        fs::current_path(LibPath + import_Name + "/");
        string cmd = "cgp " + import_Name + " --export " + Dest;
        //cout << cmd << endl;
        system(cmd.c_str());
}
void *Add_at_Bin(char **argb, int argc, MSTS_Vector *IN)
{
        string import_Name = Get_arg(argb, argc, "--add")->_Left;
        string LibPath = ((string)CGP_BIN) + ".CGP_LIB/";
        if (!exists(LibPath))
        {
                recursive_mkdir(LibPath.c_str());
        }
        string cmd = "cgp " + import_Name + " --export " + LibPath + import_Name;
        //cout << cmd << endl;
        system(cmd.c_str());
}
void *listLib(char **argb, int argc, MSTS_Vector *)
{
        string LibPath = ((string)CGP_BIN) + ".CGP_LIB/";
        std::string path(LibPath);
        //std::string ext(".cgp");
        for (auto &p : fs::directory_iterator(path))
        {
                //if (p.path().extension() == ext)
                std::cout << " \"" << p.path().stem().string() << "\" in (" << p.path().string() << ")" << endl;
        }
}

void *Install(char **argb, int argc, MSTS_Vector *)
{
        string import_Name = Get_arg(argb, argc, "--install")->_Left;
        string Src = Get_Data(import_Name, "Config.Exe");
        CopyRecursive(Src.c_str(), CGP_BIN);
        cout << GREEN << "installed: " << BLUE << Src << GREEN << " in " << YELLOW << CGP_BIN << RESET << "!" << endl;
        //std::string ext(".cgp");
}

void *UnInstall(char **argb, int argc, MSTS_Vector *)
{
        string import_Name = Get_arg(argb, argc, "--uninstall")->_Left;
        string Src = Get_Data(import_Name, "Config.Exe");
        vector<string> K;
        split(Src, K, '/');

        remove((((string)CGP_BIN) + K[K.size() - 1]).c_str());
        cout << GREEN << "uninstalled: " << BLUE << import_Name << GREEN << " in " << YELLOW << CGP_BIN << RESET << "!" << endl;
        //std::string ext(".cgp");
}

string Add_cgp(string f1, string f2, string Caract)
{
        //cout<<"building buffer"<<endl;
        string i = Get_Data(f1, Caract);
        string j = Get_Data(f2, Caract);

        //cout<<i<<" "<<j<<endl;
        vector<string> iPj1;
        vector<string> iPj2;
        split(i, iPj1, ' ');
        split(j, iPj2, ' ');
        bool isint = 0;
        //cout<<"building buffer"<<iPj2.size()<<endl;
        for (int JI = 0; JI < iPj2.size(); JI++)
        {
                if (!((strcmp(iPj2[JI].c_str(), " ") == 0) || (strcmp(iPj2[JI].c_str(), "") == 0)))
                {
                        //cout<<iPj2[JI]<<endl;
                        for (int IJ = 0; IJ < iPj1.size(); IJ++)
                        {
                                if (!((strcmp(iPj1[IJ].c_str(), " ") == 0) || (strcmp(iPj1[IJ].c_str(), "") == 0)))
                                {

                                        if (strcmp((AS(f2) + iPj2[JI]).c_str(), iPj1[IJ].c_str()) == 0)
                                        {
                                                isint = 1;
                                        }
                                }
                        }
                        if (isint == 0)
                        {
                                iPj1.push_back(AS(f2) + iPj2[JI]);
                        }
                        isint = 0;
                }
        }
        //cout<<"building buffer"<<endl;
        string bfu = "";
        //cout<<iPj1.size()<<endl;
        for (int kl = 0; kl < iPj1.size(); kl++)
        {
                bfu += (iPj1[kl]);
                if (bfu[bfu.size() - 1] != ' ')
                {
                        bfu += ' ';
                }
                //cout<<iPj1[kl]<<endl;
        }
        //cout << bfu << endl;
        return bfu;
}

//first=cgp
//Second=AES

int is_dep_of(string first, string Second)
{
        string Deps = Get_Data(first, "source.Deps");
        vector<string> Deps_L;
        split(Deps, Deps_L, ' ');
        for (int i = 0; i < Deps_L.size(); i++)
        {
                if ((!((strcmp(Deps_L[i].c_str(), " ") == 0) || (strcmp(Deps_L[i].c_str(), "") == 0))) && (strcmp(Deps_L[i].c_str(), Second.c_str()) == 0))
                {
                        return 1;
                }
        }
        return 0;
}

//--merge some little change to do •
string foreach (string sp, char splitter, string(*Taddr)(string, int))
{
}
void *Merge(char **argb, int argc, MSTS_Vector *)
{

        EArg *iE = Get_arg(argb, argc, "--merge");
        string Dest = iE->_Left;

        string src = iE->_Right;
        for (auto &p : fs::directory_iterator(".cgp/"))
        {
                if (p.path().extension() == ".cgp")
                        if (is_dep_of(p.path().stem().string(), src) && is_dep_of(p.path().stem().string(), Dest))
                        {
                                Dyn_loader DLL(((string) ".cgp/") + p.path().stem().string() + ".cgp");
                                MSTS *Dsp = DLL.get_from_alias("source.Deps");
                                vector<string> DLP;
                                split(Dsp->_Value, DLP, ' ');
                                string New_Deps = "";
                                for (int i = 0; i < DLP.size(); i++)
                                {
                                        if (!((strcmp(DLP[i].c_str(), " ") == 0) || (strcmp(DLP[i].c_str(), "") == 0)))
                                        {
                                                if (strcmp(DLP[i].c_str(), src.c_str()) != 0)
                                                {
                                                        New_Deps += (DLP[i] + " ");
                                                }
                                        }
                                }
                                Dsp->_Value = New_Deps;
                                DLL.Save(((string) ".cgp/") + p.path().stem().string() + ".cgp");
                                //cout << p.path().stem().string() << " Depend on : " << src << " you should remove it from is Config!" << endl;
                        }
        }
        string name = ".cgp/" + Dest + ".cgp";
        /*for (int i = 0; i < argc; i++)
        {
                if (strcmp(argb[i], "--merge") == 0)
                {
                        //nextis = 1;
                        Dest = argb[i - 1];
                        src = argb[i + 1];
                        name += argb[i + 2];
                        fname = argb[i + 2];
                        name.append(".cgp");
                }

                //else if (nextis)
        }*/

        string sw = Add_cgp(Dest, src, "compile.Switchs");
        //sw.erase(sw.begin());
        string Deps = Add_cgp(Dest, src, "source.Deps");
        string includes = Add_cgp(Dest, src, "source.includes");
        string source = Add_cgp(Dest, src, "source.cppfiles");
        string obj = Add_cgp(Dest, src, "source.cppobj");
        string B_T = Add_cgp(Dest, src, "Build.Type");
        //cout<<B_T<<endl;
        vector<string> V_B_T;
        split(B_T, V_B_T, ' ');
        int ret = 3;
        //cout<<V_B_T.size()<<endl;
        vector<string> Dep_1;
        split(Deps, Dep_1, ' ');
        Deps = "";
        for (int i = 0; i < Dep_1.size(); i++)
        {
                if (strcmp(Dep_1[i].c_str(), src.c_str()) == 0)
                        Dep_1[i] = "";
                else if (strcmp(Dep_1[i].c_str(), Dest.c_str()) == 0)
                        Dep_1[i] = "";
                if (!((strcmp(Dep_1[i].c_str(), " ") == 0) || (strcmp(Dep_1[i].c_str(), "") == 0)))
                {
                        Deps += (Dep_1[i] + ' ');
                }
        }
        for (int i = 0; i < V_B_T.size(); i++)
        {
                if (!((strcmp(V_B_T[i].c_str(), " ") == 0) || (strcmp(V_B_T[i].c_str(), "") == 0)))
                {
                        string kl=V_B_T[i];
                        kl=remove(kl,AS(src));
                        try
                        {
                                if (stoi(kl) < ret)
                                {
                                        ret = stoi(kl);
                                }
                        }
                        catch (...)
                        {
                                cout << V_B_T[i] << " no conversion" << endl;
                        }
                }
        }
        //cout << ret << endl;

        MSTS *M_Deps = new MSTS("", Deps, "source.Deps");
        MSTS *M_P_N = new MSTS("", Get_Data(Dest, "Config.Exe"), "Config.Exe");
        MSTS *M_includes = new MSTS("", includes, "source.includes");
        MSTS *M_source = new MSTS("", source, "source.cppfiles");
        MSTS *M_obj = new MSTS("", obj, "source.cppobj");
        MSTS *M_B_T = new MSTS("", to_string(ret), "Build.Type");
        MSTS *M_SW = new MSTS("", sw, "compile.Switchs");
        MSTS *sha1V = new MSTS("", "", "source.Checksum_sha1");

        //Build.Type

        MasterView *MF = new MasterView(MaxX, MaxY);
        EditorView *ED = new EditorView(0, 0);
        ED->add_MSTS(M_Deps, 0);
        ED->add_MSTS(M_includes, 1);
        ED->add_MSTS(M_source, 2);
        ED->add_MSTS(M_obj, 3);
        ED->add_MSTS(M_P_N, 4);
        ED->add_MSTS(M_B_T, 5);
        ED->add_MSTS(M_SW, 6);
        ED->add_MSTS(sha1V, 7);
        MF->addView(ED);
        //cout << "Created: " << name << endl;
        MF->Save(name);
        cout<<Dest<<" << "<<src<<endl;
        delete MF;
        delete ED;
}
void *Build_all(char **argb, int argc, MSTS_Vector *)
{
        std::string path(".cgp/");
        std::string ext(".cgp");
        string nt;
        string jk;
        for (auto &p : fs::recursive_directory_iterator(path))
        {

                if (p.path().extension() == ext)
                {
                        jk = Get_Data(p.path().stem().string(), "Build.Type");
                        if (strcmp(jk.c_str(), "2") == 0)
                        {
                                //cout << GREEN << "Ignoring:\"" << YELLOW << p.path().stem().string() << GREEN << "\"(Static Lib)" << endl;
                        }
                        else
                        {
                                nt = ((string) "cgp ") + p.path().stem().string();
                                if (forcebuild)
                                        nt += " --force";
                                nt += " --build";
                                cout << BLUE << "---" << YELLOW << p.path().stem().string() << BLUE << "---" << RESET << endl;
                                system(nt.c_str());
                        }
                }
        }
}

void *Clean(char **argb, int argc, MSTS_Vector *IN)
{
        std::string path(".cgp/");
        std::string ext(".cgp");
        string nt;
        string jk;
        for (auto &p : fs::recursive_directory_iterator(path))
        {

                if (p.path().extension() == ext)
                {
                        jk = Get_Data(p.path().stem().string(), "Build.Type");
                        nt = ((string) "cgp ") + p.path().stem().string();
                        nt += " --clean";
                        //cout << BLUE << "---" << YELLOW << p.path().stem().string() << BLUE << "---" << RESET << endl;
                        system(nt.c_str());
                }
        }
}
void *clean(char **argb, int argc, MSTS_Vector *IN)
{
        string o = Get_arg(argb, argc, "--clean")->_Left;

        //cout << o << endl;
        string f = IN->get_from_alias("thiscfg")->_Value;
        vector<string> kl;
        split(Get_Data(o, "source.cppobj"), kl, ' ');
        for (int i = 0; i < kl.size(); i++)
        {
                if (!((strcmp(kl[i].c_str(), " ") == 0) || (strcmp(kl[i].c_str(), "") == 0)))
                {
                        if (remove(kl[i].c_str()) != 0)
                        {
                                // cout << "Error while delete of:" << kl[i] << endl;
                        }
                        else
                        {
                                cout << BLUE << "Deleted:" << RED << kl[i] << BLUE << " Successfully!" << RESET << endl;
                        }
                }
        }
        string targetf = Get_Data(o, "Config.Exe");
        if (exists(targetf))
        {
                if (remove(targetf.c_str()) != 0)
                {
                        // cout << "Error while delete of:" << kl[i] << endl;
                }
                else
                {
                        cout << BLUE << "Deleted:" << RED << targetf << BLUE << " Successfully!" << RESET << endl;
                }
        }
        vector<string> kl2;
        split(Get_Data(o, "source.Deps"), kl2, ' ');
        //cout<<o<<" "<<Get_Data(o,"source.Deps")<<endl;
        string cmd;
        for (int i = 0; i < kl2.size(); i++)
        {
                if (!((strcmp(kl2[i].c_str(), " ") == 0) || (strcmp(kl2[i].c_str(), "") == 0)))
                {
                        cmd = ((string) "cgp ") + kl2[i] + " --clean";
                        //cout<<cmd<<endl;
                        system(cmd.c_str());
                }
        }
}
//cgp [config] -C_S
//create build script / Force build script / run

void *Create_scripts(char **argb, int argc, MSTS_Vector *IN)
{
        string o = Get_arg(argb, argc, "-C_S")->_Left;
        ofstream _build = ofstream(o + "_Build.sh");
        ofstream _force_build = ofstream(o + "_Force_Build.sh");
        ofstream _Run = ofstream(o + "_Test.sh");
        ofstream _clean = ofstream(o + "_Clean.sh");
        _build << "cgp " << o << " --build";
        _force_build << "cgp " << o << " --force --build";
        _Run << "cgp " << o << " --build --run";
        _clean << "cgp " << o << " --clean";
        _clean.close();
        _build.close();
        _force_build.close();
        _Run.close();
}
void *Show_Parents(char **argb, int argc, MSTS_Vector *IN)
{

        std::string path(".cgp/");
        std::string ext(".cgp");
        string nt = Get_arg(argb, argc, "--Parents")->_Left;
        string jk;
        for (auto &p : fs::recursive_directory_iterator(path))
        {

                if (p.path().extension() == ext)
                {
                        //cout<<"I"<<p.path().stem().string()<<endl;
                        jk = Get_Data(p.path().stem().string(), "source.Deps");
                        vector<string> kls;
                        split(jk, kls, ' ');
                        for (int i = 0; i < kls.size(); i++)
                        {
                                if (!((strcmp(kls[i].c_str(), " ") == 0) || (strcmp(kls[i].c_str(), "") == 0)))
                                {
                                        if (strcmp(nt.c_str(), kls[i].c_str()) == 0)
                                        {
                                                cout << GREEN << "Found: " << YELLOW << p.path().stem().string() << RESET << endl;
                                        }
                                        //cout<<kls[i]<<endl;
                                }
                        }
                }
        }
}
void *Backup(char **argb, int argc, MSTS_Vector *IN)
{
        EArg *INP = Get_arg(argb, argc, "--backup");
        string nt = INP->_Left;   //Cgp to backup
        string nts = INP->_Right; //name of backup

        vector<string> Path;
        split(nt, Path, '/');
        string filename = "";
        for (int i = 0; i < Path.size() - 1; i++)
        {
                filename += Path[i] + '/';
        }
        string PathFolder(filename + ".cgp/Backup/" + as_cgp((char *)Path[Path.size() - 1].c_str()) + "/" + nts);
        //string PathFolder = (((string) ".cgp/Backup/") + nt + "/" + nts);
        recursive_mkdir(PathFolder.c_str());
        string cmd = "cgp " + nt + " --export " + PathFolder;
        system(cmd.c_str());
}
void *Backin(char **argb, int argc, MSTS_Vector *IN)
{
        EArg *INP = Get_arg(argb, argc, "--backin");
        string nt = INP->_Left+".cgp";   //Cgp to backup
        string nts = INP->_Right; //name of backup
        string PathFolder = (((string) ".cgp/Backup/") + nt + "/" + nts);
        string currentfold = fs::current_path();
        cout<<PathFolder.c_str()<<endl;
        //fs::current_path(PathFolder.c_str());
        string cmd = "cgp " + nt + " --export " + currentfold;
        system(cmd.c_str());
        //fs::current_path(currentfold.c_str());
}
bool contain(string str, char c)
{
        for (int i = 0; i < str.size(); i++)
        {
                if (str[i] == c)
                {
                        return 1;
                }
        }
        return 0;
}
/*
        bool contain(string str, string c)
        {
                for (int i = 0; i < str.size(); i++)
                {
                        if (str[i] == c)
                        {
                                return 1;
                        }
                }
                return 0;
        }*/
string remove(string str, char i)
{
        str.erase(std::remove(str.begin(), str.end(), i), str.end());
        return str;
}
string remove(string mainStr, string toErase)
{
        // Search for the substring in string
        size_t pos = mainStr.find(toErase);
        if (pos != std::string::npos)
        {
                // If found then erase it from string
                mainStr.erase(pos, toErase.length());
        }
        return mainStr;
}
void Create_declarations(const char *filename, ofstream &HPP_)
{
        ifstream CPP_(filename);
        HPP_ << "/*---" << filename << "---*/\n";
        string Buff;

        while (getline(CPP_, Buff))
        {
                string Typename = "";
                string DecName = "";
                string DecTypes = "";
                int Phase = 0;
                string smb = "";
                //cout<<(int)Buff[0]<<endl;
                if ((Buff[0] != '\n') && (Buff[0] != 32))
                {
                        for (int i = 0; i < Buff.size(); i++)
                        {
                                smb += Buff[i];
                                if ((Buff[i] == '*' || Buff[i] == ' ') && (Phase == 0))
                                {
                                        Typename = smb;
                                        smb = "";
                                        Phase++;
                                }
                                else if (Buff[i] == '(' && Phase == 1)
                                {
                                        DecName = smb;
                                        smb = "";
                                        Phase++;
                                }
                                else if (Buff[i] == ')' && Phase == 2)
                                {
                                        DecTypes = smb;
                                        smb = "";
                                }
                        }
                        if ((!contain(DecName, ':')) && (strcmp(Typename.c_str(), "unsigned ") == 0))
                        {
                                cout << "\t" << Typename << ":" << DecName << ":" << DecTypes << ";" << endl;
                                HPP_ << "#ifndef " << remove(remove(remove(DecName, '*'), '('), "char") << endl;
                                HPP_ << "\t" << Typename << DecName << DecTypes << ";" << endl;
                                HPP_ << "#endif" << endl;
                        }
                        else if (!contain(DecName, ':') && (strcmp(Typename.c_str(), "") != 0) && (strcmp(DecName.c_str(), "") != 0) && (strcmp(Typename.c_str(), "inline ") != 0) && (strcmp(Typename.c_str(), "static") != 0))
                        {
                                if (strcmp(DecName.c_str(), "main(") != 0)
                                {
                                        cout << "\t" << Typename << ":" << DecName << ":" << DecTypes << ";" << endl;
                                        HPP_ << "#ifndef " << remove(remove(DecName, '*'), '(') << endl;
                                        HPP_ << "\t" << Typename << DecName << DecTypes << ";" << endl;
                                        HPP_ << "#endif" << endl;
                                }
                        }
                }
        }
        //HPP_.close();
}
void *Create_Header(char **argb, int argc, MSTS_Vector *IN)
{
        string cfgFile = Get_arg(argb, argc, "--create-header")->_Left;
        string output = Get_arg(argb, argc, "--create-header")->_Right;

        ofstream *Hppfile = new ofstream(output);
        (*Hppfile) << ("/*\nHeader Generated By CGP\nYou should include this header file for test units\nYou should also create \"T_Config.hpp\"\n*/\n#include<T_Config.hpp>\n");
        vector<string> kld;
        split(Get_Data(cfgFile, "source.cppfiles"), kld, ' ');
        for (int i = 0; i < kld.size(); i++)
        {
                if (!((strcmp(kld[i].c_str(), " ") == 0) || (strcmp(kld[i].c_str(), "") == 0)))
                {
                        Create_declarations(kld[i].c_str(), *Hppfile);
                }
        }
        vector<string> kldeps;
        split(Get_Data(cfgFile, "source.Deps"), kldeps, ' ');
        string jkp = "";
        for (int i = 0; i < kldeps.size(); i++)
        {

                if (!((strcmp(kldeps[i].c_str(), " ") == 0) || (strcmp(kldeps[i].c_str(), "") == 0)))
                {
                        jkp = AS(kldeps[i]) + "/";
                        vector<string> kld3;
                        split(Get_Data(kldeps[i], "source.cppfiles"), kld3, ' ');
                        for (int j = 0; j < kld3.size(); j++)
                        {
                                if (!((strcmp(kld3[j].c_str(), " ") == 0) || (strcmp(kld3[j].c_str(), "") == 0)))
                                {
                                        Create_declarations((jkp + kld3[j]).c_str(), *Hppfile);
                                }
                        }
                }
        }

        Hppfile->close();
}
void *Create_Tests(char **argb, int argc, MSTS_Vector *IN)
{

        string cfgFile = Get_arg(argb, argc, "--create-tests")->_Left;
        string output = Get_arg(argb, argc, "--create-tests")->_Right + "/Headers/" + cfgFile;
        recursive_mkdir(output.c_str());
        /*
        .cgp/
                source
                        Main
                                Tests
                                        include
                                                Header.hpp
                Bin
                        obj
                                Objects.o
                

        */

        ofstream *Hppfile = new ofstream(output + '/' + cfgFile + ".hpp");
        (*Hppfile) << ("/*\nHeader Generated By CGP\nYou should include this header file for test units\nYou should also create \"T_Config.hpp\"\n*/\n#include<T_Config.hpp>\n");
        vector<string> kld;
        split(Get_Data(cfgFile, "source.cppfiles"), kld, ' ');
        for (int i = 0; i < kld.size(); i++)
        {
                if (!((strcmp(kld[i].c_str(), " ") == 0) || (strcmp(kld[i].c_str(), "") == 0)))
                {
                        Create_declarations(kld[i].c_str(), *Hppfile);
                }
        }
        cout << "Created:" << output << endl;
        Hppfile->close();
}
int main(int argc, char **argv)
{
        //Create_declarations("src/main.cpp", "include/main.hpp");
        string Fname = ".cgp/";
        bool frommenu = 0;
        if (!fs::is_directory(".cgp"))
        {
                mkdir(".cgp/");
        }

        if (argc <= 1)
        {
                show_menu(); //<<endl;
                exit(0);
                frommenu = 1;
        }
        string path;
        vector<string> dirs;

        split(argv[1], dirs, '/');

        for (int j = 0; j < dirs.size() - 1; j++)
        {
                path += dirs[j] + "/";
        }
        // cout<<"path:"<<path<<endl;
        if (strcmp(path.c_str(), "") != 0)
                fs::current_path(path.c_str());

        CLAB<MSTS_Vector *> Laboratory;
        CLAB<MSTS_Vector *> LaboratoryCmd;

        MSTS_Vector *NLV = new MSTS_Vector();
        Laboratory.add_Callable(&Forcebuild, "--force", "set a switch for forcing --build to skip sha1 signature", NLV); //1
        Laboratory.add_Callable(&build, "--build", "compile and link project", NLV);
        Laboratory.add_Callable(&run, "--run", "./APPNAME", NLV);
        Laboratory.add_Callable(&Build_all, "--Build", "compile and link every projects in Directory", NLV);
        LaboratoryCmd.add_Callable(&_export, "--export", "export project to a folder", NLV);
        LaboratoryCmd.add_Callable(&Add_at_Bin, "--add", "add project to CGP_LIB", NLV);
        LaboratoryCmd.add_Callable(&BIN_at_this, "--import", "import project from CGP_LIB", NLV);
        LaboratoryCmd.add_Callable(&listLib, "--list-lib", "list Libs in CGP_LIB", NLV);
        LaboratoryCmd.add_Callable(&list, "--list", "list project", NLV);
        LaboratoryCmd.add_Callable(&Install, "--install", "install project", NLV);
        LaboratoryCmd.add_Callable(&UnInstall, "--uninstall", "uninstall project", NLV);
        LaboratoryCmd.add_Callable(&Merge, "--merge", "merge Dest <- source [cgp Main --merge AES]", NLV);
        LaboratoryCmd.add_Callable(&clean, "--clean", "clean obj", NLV);
        LaboratoryCmd.add_Callable(&Clean, "--Clean", "clean ALL objs", NLV);
        LaboratoryCmd.add_Callable(&Create_scripts, "-C_S", "Create build scripts", NLV);
        LaboratoryCmd.add_Callable(&Show_Parents, "--Parents", "Show parents of Projects", NLV);
        LaboratoryCmd.add_Callable(&Backup, "--backup", "backup files ", NLV);
        LaboratoryCmd.add_Callable(&Backin, "--backin", "restore backup files ", NLV);
        LaboratoryCmd.add_Callable(&Create_Tests, "--create-tests", "create test in a folder ", NLV);
        LaboratoryCmd.add_Callable(&Create_Header, "--create-header", "create header file of project ", NLV); //20

        //LaboratoryCmd.add_Callable(&Build_all, "--build*", "compile and link every project!", NLV);

        //Add_cgp("cgp", "installer", "source.Deps");
        //LaboratoryCmd.add_Callable(&_import, "--import", "import project here", NLV);
        // Laboratory.add_Callable(&build, "--add-git-dep", "add a git ", NLV);
        //Laboratory.add_Callable(&update, "--update", "compile and link project", NLV);
        string circlechar = "/|\\-";
        int XXindex = 0;
        //char**FakeArgs={"Begin:","<>","TT","TTTTT"};
        //Reltt_INT *Reltt=new Reltt_INT(argc,argv);
        MasterView *MF = new MasterView(MaxX, MaxY);
        MF->set_MSTS_Vector(NLV);
        //string Fname = ".cgp/";
        string command = "";
        if (frommenu == 0)
                Fname += as_cgp((char *)dirs[dirs.size() - 1].c_str());

        //cout<<"Fname:"<<Fname<<endl;
        MSTS *thisinfo = new MSTS("", Fname, "thiscfg");
        MSTS *thisinfoargv0 = new MSTS("", argv[0], "exe");
        MSTS *currentworkingdir = new MSTS("", fs::current_path(), "cwd");
        View *I = new View();
        //I->add_Horizon("--------------------------", 0, 0);
        //I->add_Horizon("IP\t|\tDomaine\t|\tPort\t|\tName\0", 0, 0);
        //I->add_Horizon(" Home\t|\t80\t|\tThis", 1, 0);
        //I->add_Vertical("Reltt Runtime", 0, 0);
        View *IJ = new View();
        View *errors = new View();

        vector<string> Ch;
        Ch.push_back("Config");
        Ch.push_back("G++");
        Ch.push_back("Source");
        Ch.push_back("Build");
        Ch.push_back("Deps");
        Ch.push_back("Git");
        Ch.push_back("Doc");
        View *Legend = new View();
        Legend->add_Horizon("| W : ↑ | A : ← | S : ↓ | D : → | Enter : Edit | \\ : Back ", 25, 5);
        vign *IKD = new vign(Ch, 2, 1);

        EditorView *Config = new EditorView(3, 1);
        MSTS *Projectname = new MSTS("|Project name", "None", "Config.Project");
        MSTS *Exename = new MSTS("|Executable Name", "None", "Config.Exe");
        MSTS *AddLib = new MSTS("|Add Lib", "_", "");
        MSTS *AddDependancy = new MSTS("|Add Dependancy", "_", "");
        MSTS *AddInclude = new MSTS("|Add Include", "_", "");
        Config->add_MSTS(Projectname, 0); // ("|Project name:"+projectname,7,5);
        Config->add_MSTS(Exename, 1);     // ("|Project EXE :"+EXEname,8,5);
        Config->add_MSTS(AddLib, 2);
        Config->add_MSTS(AddDependancy, 3);
        Config->add_MSTS(AddInclude, 4);
        EditorView *gpp = new EditorView(3, 1);

        dropdownlist *buildtype = new dropdownlist(6, 1);
        dropdownlist *CompileBuild = new dropdownlist(6, 1);

        MSTS *CppVersion = new MSTS("|C++ Version", "c++17", "G++.C++");
        MSTS *Target = new MSTS("|Target (executable/shared/static)", "shared", "G++.Target");
        EditorView *source = new EditorView(6, 1);
        EditorView *Git = new EditorView(3, 1);
        MSTS *sourceFiles = new MSTS("|", "main.cpp", "source.files");
        MSTS *sourceTarget = new MSTS("|Add Src file", "_", "");
        source->add_MSTS(sourceTarget, 0);
        gpp->add_MSTS(CppVersion, 0);
        IKD->render();
        //IJ->add_Vertical("this is a View", 5, 5);
        //IJ->add_Horizon("Ctrl+C Compile | ESC Exit |", 18, 0);
        //IJ->add_Vertical("Reltt Editor",0,2);

        EditorView *addsrc = new EditorView(3, 1);

        EditorView *addobj = new EditorView(9, 1);
        EditorView *addDep = new EditorView(9, 1);
        EditorView *addinc = new EditorView(9, 1);

        MSTS *pathFiles = new MSTS("|Path to Source file", "_", "");
        MSTS *ObjName = new MSTS("|Obj-Name", "_", "");
        MSTS *Save = new MSTS("|", "Save", "");
        addsrc->add_MSTS(pathFiles, 0);
        addsrc->add_MSTS(ObjName, 1);
        addsrc->add_MSTS(Save, 2);
        MSTS *Objpath = new MSTS("|Path to Object(*.o/*.lib/*.so/*.dll/*.a)", "_", "");
        MSTS *SaveBtn = new MSTS("|", "Save Object", "");
        addobj->add_MSTS(Objpath, 0);
        addobj->add_MSTS(SaveBtn, 1);
        MSTS *DepPath = new MSTS("|Path to .rgp", "_", "");
        MSTS *DSaveBtn = new MSTS("|", "Save", "");
        addDep->add_MSTS(DepPath, 0);
        addDep->add_MSTS(DSaveBtn, 1);
        View *Docs = new View();
        Docs->add_Horizon("This is the Documentation about 'cgp'", 3, 1);
        Docs->add_Horizon("~In the Config section in top Right,", 4, 1);
        Docs->add_Horizon("    you can add Library, Dependancy and include path ,", 5, 1);
        Docs->add_Horizon("~In the G++ section, you can setup every thing", 7, 1);
        Docs->add_Horizon("                     that is important", 8, 1);
        Docs->add_Horizon("~In the Source section you can manage source files", 10, 1);
        Docs->add_Horizon("~In the Build section you can compile,link or build!", 12, 1);
        Docs->add_Horizon("~In the Deps section you have a tree of Dependancy(Work In Progress)", 14, 1);
        Docs->add_Horizon("~In the Git section you can commit,push or fetch ", 16, 1);
        Docs->add_Horizon("NOTE: Dependancy are Config File of cgp (.cgp)", 18, 1);
        Docs->add_Horizon("      When building the parent, cgp will build every dependancy", 19, 1);
        Docs->add_Horizon("                                and will link concidering of it", 20, 1);
        MSTS *INCPath = new MSTS("|Path to include", "_", "");
        MSTS *ISaveBtn = new MSTS("|", "Save", "");
        addinc->add_MSTS(INCPath, 0);
        addinc->add_MSTS(ISaveBtn, 1);

        addsrc->Visible = 0;
        buildtype->Visible = 0;
        CompileBuild->Visible = 0;
        MSTS *MSTS_Excutable = new MSTS("", "Executable", "");
        MSTS *MSTS_Shared = new MSTS("", "Shared", "");
        MSTS *MSTS_Static = new MSTS("", "Static", "");
        MSTS *MSTS_sourcefiles = new MSTS("|files", "", "source.cppfiles");
        MSTS *MSTS_objfiles = new MSTS("|objs", "", "source.cppobj");
        MSTS *MSTS_fileSha1 = new MSTS("|Checksum(sha1)", "", "source.Checksum_sha1");
        MSTS *MSTS_objLib = new MSTS("|Libs", "", "source.Libs");
        MSTS *MSTS_Dependancy = new MSTS("|Dependancys", "", "source.Deps");
        MSTS *MSTS_Includes = new MSTS("|includes", "", "source.includes");

        MSTS *MSTS_Git_Commit = new MSTS("|Commit", "_", "");
        EditorView *Git_Commit = new EditorView(7, 1);
        MSTS *MSTS_Git_Push = new MSTS("|Push", "_", "");
        //EditorView *Git_Push = new EditorView(9, 1);
        MSTS *MSTS_Git_Fetch = new MSTS("|Fetch", "_", "");
        EditorView *Checksums = new EditorView(0, 0);
        MSTS *compilesw = new MSTS("", "", "compile.Switchs");
        Checksums->Visible = 0;
        Checksums->add_MSTS(MSTS_fileSha1, 0);
        Checksums->add_MSTS(thisinfo, 1);
        Checksums->add_MSTS(thisinfoargv0, 2);
        Checksums->add_MSTS(currentworkingdir, 3);
        Checksums->add_MSTS(compilesw, 4);
        source->add_MSTS(MSTS_sourcefiles, 1);
        source->add_MSTS(MSTS_objfiles, 2);
        source->add_MSTS(MSTS_objLib, 3);

        source->add_MSTS(MSTS_Dependancy, 4);
        source->add_MSTS(MSTS_Includes, 5);

        MSTS *CommitMSG = new MSTS("Commit MSG", "_", "");
        MSTS *CommitButton = new MSTS("~", "Commit!", "");
        Git_Commit->add_MSTS(CommitMSG, 0);
        Git_Commit->add_MSTS(CommitButton, 1);

        Git->add_MSTS(MSTS_Git_Commit, 0);
        Git->add_MSTS(MSTS_Git_Push, 1);
        Git->add_MSTS(MSTS_Git_Fetch, 2);

        buildtype->Key = "|Build Type     ";
        buildtype->Alias = "Build.Type";
        buildtype->add_MSTS(MSTS_Excutable, 0);
        buildtype->add_MSTS(MSTS_Shared, 1);
        buildtype->add_MSTS(MSTS_Static, 2);
        View *Roue = new View();
        int Rouex = 1;
        int Rouey = 1;

        MSTS *BuildButton = new MSTS("", "Build", "");
        MSTS *CompileButton = new MSTS("", "Compile", "");
        MSTS *LinkButton = new MSTS("", "Link", "");
        CompileBuild->add_MSTS(BuildButton, 0);
        CompileBuild->add_MSTS(CompileButton, 1);
        CompileBuild->add_MSTS(LinkButton, 2);
        //MF->addView()
        addobj->Visible = 0;
        addinc->Visible = 0;
        addDep->Visible = 0;
        Git_Commit->Visible = 0;
        DepTree *Project = buildTree(argv[1]);
        Docs->Visible = 0;
        MF->addView(Checksums);
        MF->addView(Git_Commit);
        MF->addView(Docs);
        MF->addView(Git);
        MF->addView(addDep);
        MF->addView(addobj);
        MF->addView(CompileBuild);
        MF->addView(addinc);
        MF->addView(addsrc);
        MF->addView(source);
        MF->addView(I);
        MF->addView(IJ);
        MF->addView(IKD);
        MF->addView(Legend);
        MF->addView(Config);
        MF->addView(gpp);
        MF->addView(buildtype);

        Config->Visible = 0;

        //char i;
        string LargeBuffer;
        string buffer;
        char ch;

        int x, y = 0;
        x = 2;
        y = 2;
        string projectname;
        string EXEname;
        string sourcebuffer;
        string objbuffer;
        //when on zero you can navigate in menus
        int Lock = 0;
        MF->addView(Roue);
        //sourcebuffer;
        //objbuffer;
        MF->load_into_Vector();
        //cout<<(argv[1][0]!='-')<<" |"<<argv[1][0]<<endl;
        if (argc == 2)
        {
                argv[2] = new char();
        }
        bool haveto = 1;
        if ((argc >= 2))
        {
                //cout<<(argv[1][0] == '-')<<endl;
                if ((argv[1][0] == '-') || (argv[2][0] == '-'))
                {
                        haveto = 0;
                        for (int i = 0; i < argc; i++)
                        {
                                if (strcmp(argv[i], "--help") != 0)
                                {
                                        LaboratoryCmd.run(argv[i], argv, argc);
                                        MF->Load(Fname);
                                        Laboratory.run(argv[i], argv, buildtype->current_index);
                                }
                                else
                                {
                                        //vector<Deskrp>K;
                                        //K.push_back();
                                        show_Vec(Laboratory.show_desk(LaboratoryCmd.show_desk(new Deskrp())));
                                }
                        }
                        MF->Save(Fname);
                }
        }
        if (argc == 2 && haveto == 1)
        {
                MF->Load(Fname);
                system("stty raw");
                while (1)
                {
                        MF->clear();
                        string sdf = "";
                        sdf += circlechar[XXindex];
                        Roue->add_Horizon(sdf, Rouex, Rouey);
                        if (circlechar.size() - 1 == XXindex)
                        {
                                XXindex = 0;
                        }
                        else
                        {
                                XXindex++;
                        }
                        //seting the terminal in raw mode
                        //Config
                        if (IKD->current_index == 0)
                        {
                                buildtype->clear();
                                buildtype->Visible = 0;
                                //MF->addView()
                                //Projectname->_Value=to_string(Config->current_index);
                                if ((Lock) && (((Config->current_index != 2) && (Config->current_index != 3) && (Config->current_index != 4)) && Config->current_index >= 0))
                                {
                                        Config->Values[Config->current_index]->_Value = buffer;
                                }
                                else if ((Config->current_index == 2) && (Lock))
                                {
                                        addobj->Visible = 1;

                                        Config->current_index = -1;
                                        Lock = 0;
                                }
                                else if ((Config->current_index == 3) && (Lock))
                                {
                                        addDep->Visible = 1;
                                        //addDep->render();

                                        Config->current_index = -2;
                                        Lock = 0;
                                }
                                else if ((Config->current_index == 4) && (Lock))
                                {
                                        addinc->Visible = 1;
                                        //addDep->render();

                                        Config->current_index = -3;
                                        Lock = 0;
                                }
                                else if (Config->current_index == -1)
                                {
                                        if (Lock)
                                        {
                                                if (addobj->current_index == 0)
                                                        addobj->Values[addobj->current_index]->_Value = buffer;
                                                else
                                                {
                                                        MSTS_objLib->_Value += addobj->Values[0]->_Value + ' ';
                                                        Lock = 0;
                                                }
                                        }
                                }
                                else if (Config->current_index == -2)
                                {
                                        if (Lock)
                                        {
                                                if (addDep->current_index == 0)
                                                        addDep->Values[addDep->current_index]->_Value = buffer;
                                                else
                                                {
                                                        MSTS_Dependancy->_Value += " .cgp/" + addDep->Values[0]->_Value;
                                                        Lock = 0;
                                                }
                                        }
                                }
                                else if (Config->current_index == -3)
                                {
                                        if (Lock)
                                        {
                                                if (addinc->current_index == 0)
                                                        addinc->Values[addinc->current_index]->_Value = buffer;
                                                else
                                                {
                                                        MSTS_Includes->_Value += addinc->Values[0]->_Value + ' ';
                                                        Lock = 0;
                                                }
                                        }
                                }
                                if ((Config->current_index == -1) && (addobj->Visible == 0))
                                {
                                        Config->current_index = 2;
                                }
                                if ((Config->current_index == -2) && (addDep->Visible == 0))
                                {
                                        Config->current_index = 3;
                                }
                                if ((Config->current_index == -3) && (addinc->Visible == 0))
                                {
                                        Config->current_index = 4;
                                }
                                gpp->clear();
                                gpp->Visible = 0;
                                Config->Visible = 1;
                                addinc->render();
                                addDep->render();
                                addobj->render();
                                Config->render();
                        }
                        //G++
                        if (IKD->current_index == 1)
                        {
                                addDep->clear();
                                addDep->Visible = 0;
                                addobj->clear();
                                addobj->Visible = 0;
                                addsrc->clear();
                                addsrc->Visible = 0;
                                Config->clear();
                                Config->Visible = 0;
                                source->clear();
                                source->Visible = 0;
                                buildtype->Visible = 1;

                                if (Lock)
                                {
                                        if (gpp->current_index == 0)
                                        {
                                                gpp->Values[gpp->current_index]->_Value = buffer;
                                        }
                                }
                                gpp->Visible = 1;
                                if (gpp->current_index != -1)
                                {
                                        buildtype->isOn = 0;
                                }
                                buildtype->clear();
                                buildtype->render();
                                gpp->render();
                        }
                        //Source
                        if (IKD->current_index == 2)
                        {
                                CompileBuild->Visible = 0;
                                CompileBuild->clear();
                                buildtype->clear();
                                buildtype->Visible = 0;
                                gpp->clear();
                                gpp->Visible = 0;
                                if (Lock)
                                {
                                        if (source->current_index == -1)
                                        {
                                                if (ch != 13)
                                                        addsrc->Values[addsrc->current_index]->_Value = buffer;

                                                //addsrc->Values[addsrc->current_index]->_Value += buffer;
                                                addsrc->render();
                                        }
                                        else
                                        {
                                                source->Values[source->current_index]->_Value = buffer;
                                        }
                                }
                                if (addsrc->current_index == 2)
                                {
                                        if (ch == 13)
                                        {
                                                MSTS_sourcefiles->_Value += addsrc->Values[0]->_Value + " ";
                                                MSTS_objfiles->_Value += ".cgp/" + addsrc->Values[1]->_Value + " ";
                                                addsrc->current_index = 0;
                                        }
                                        //cout<<objbuffer<<sourcebuffer<<endl;
                                }
                                addsrc->render();
                                source->Visible = 1;

                                source->render();
                        }
                        //build
                        else if ((IKD->current_index == 3))
                        {
                                Project->Visible = 0;
                                Project->clear();
                                addsrc->Visible = 0;
                                addsrc->clear();
                                source->Visible = 0;
                                source->clear();
                                CompileBuild->clear();
                                CompileBuild->Visible = 1;
                                CompileBuild->ischoosing = 1;
                                if (ch == 13)
                                {
                                        int i = CompileBuild->current_index;
                                        switch (i)
                                        {
                                        case 0:
                                                //build
                                                compile(MSTS_objfiles, MSTS_sourcefiles, MSTS_Includes, gpp->Values[0]->_Value, MSTS_fileSha1, compilesw, argv[1], MSTS_Dependancy);
                                                link(MSTS_objfiles, MSTS_objLib, MSTS_Dependancy, Config->Values[1]->_Value, buildtype->current_index, argv[0]);
                                                MF->Save(Fname);
                                                /* code */
                                                break;
                                        case 1:
                                                //compile
                                                compile(MSTS_objfiles, MSTS_sourcefiles, MSTS_Includes, gpp->Values[0]->_Value, MSTS_fileSha1, compilesw, argv[1], MSTS_Dependancy);
                                                MF->Save(Fname);
                                                break;
                                        case 2:
                                                link(MSTS_objfiles, MSTS_objLib, MSTS_Dependancy, Config->Values[1]->_Value, buildtype->current_index, argv[0]);
                                                //link
                                                break;
                                        default:
                                                break;
                                        }
                                        Lock = 0;
                                }
                                CompileBuild->render();
                        }
                        else if (IKD->current_index == 4)
                        {
                                CompileBuild->Visible = 0;
                                CompileBuild->clear();

                                Project->Visible = 1;
                                Project->render();
                                Git->Visible = 0;
                                Git->clear();

                                MF->addView(Project);
                        }
                        else if (IKD->current_index == 5)
                        {
                                Docs->Visible = 0;
                                //Docs->clear();
                                Project->Visible = 0;
                                Git->Visible = 1;
                                Git->render();
                                if (Git_Commit->Visible == 1 && Lock == 1)
                                {
                                        if (Git_Commit->current_index == 1)
                                        {
                                                string cmd = "git add --all ; git commit -a -m \"";
                                                cmd += Git_Commit->Values[0]->_Value + "\"";
                                                buffer = "";
                                                system(cmd.c_str());
                                                cout << cmd << endl;
                                                char i;
                                                cin >> i;
                                                Lock = 0;
                                                Git_Commit->Visible = 0;
                                                Git->current_index = 0;
                                        }
                                        else
                                        {
                                                Git_Commit->Values[0]->_Value = buffer;
                                        }
                                        Git_Commit->render();
                                }
                                Git_Commit->render();
                        }
                        else if (IKD->current_index == 6)
                        {
                                Git->Visible = 0;
                                Git->clear();
                                Git_Commit->clear();
                                Git_Commit->Visible = 0;
                                Docs->Visible = 1;
                                Docs->render();
                        }

                        MF->Render();
                        //MF->addView(IJ);
                        MF->clear();
                        MF->Render();
                        system("clear");
                        MF->Display();

                        //sleep(1);
                        ch = getchar();
                        string V = "Last char:" + to_string(ch);

                        IJ->clear();
                        IJ->add_Horizon(V, 23, 5);
                        //for(int hd=0;hd<errors->Chars.size();)
                        //errors->Chars[hd]->Char=' ';
                        if ((int)ch == (int)27)
                        { //terminate or come out of raw mode on "~" pressed
                                system("stty cooked");
                                //while(1);//you may still run the code
                                exit(0); //or terminate
                        }
                        else if ((int)ch == (int)92)
                        {
                                if (IKD->current_index == 0)
                                {

                                        if (Config->current_index == -1)
                                                Config->current_index = 2;
                                        else if (Config->current_index == -2)
                                                Config->current_index = 3;
                                        else if (Config->current_index == -3)
                                                Config->current_index = 4;

                                        addinc->Visible = 0;
                                        addobj->Visible = 0;
                                        addDep->Visible = 0;
                                }
                                else if (IKD->current_index == 2)
                                {
                                        addsrc->Visible = 0;
                                        source->current_index = 0;
                                }
                        }
                        else if (((int)ch == (int)Left) && (Lock == 0))
                        {
                                if (IKD->current_index == 0)
                                {
                                        errors->add_Horizon("<-Max index", 15, 6);
                                }
                                else
                                {
                                        IKD->current_index--;
                                        IKD->render();
                                }
                        }
                        else if ((int)ch == (int)13)
                        {

                                if (buildtype->ischoosing == 1)
                                {
                                        buildtype->ischoosing = 0;
                                        buildtype->render();
                                        Lock = -1;
                                        gpp->current_index = 1;
                                }
                                if (Git->Visible == 1 && Git->current_index >= 0)
                                {
                                        switch (Git->current_index)
                                        {
                                        case 0:
                                                Git->current_index = -1;
                                                Git_Commit->Visible = 1;

                                                break;
                                        case 1:
                                                system("git push --all");
                                                break;
                                        case 2:
                                                system("git fetch --all ; git pull --all");
                                                break;

                                        default:
                                                break;
                                        }
                                }
                                else if ((source->current_index == 0) && (IKD->current_index == 2))
                                {
                                        addsrc->Visible = 1;
                                        addsrc->render();
                                        source->current_index = -1;
                                }
                                else if (buildtype->Visible == 1 && gpp->current_index == -1)
                                {
                                        buildtype->ischoosing = 1;
                                }
                                else if (buildtype->Visible == 0 && gpp->current_index == -1)
                                {
                                        buildtype->ischoosing = 0;
                                }
                                else if ((addsrc->current_index == 2) && (addsrc->Visible == 1))
                                {
                                        //pathFiles->_Value+' ';
                                        //ObjName->_Value+' ';
                                }
                                else if (addsrc->current_index == 0 && Lock == 0)
                                {
                                        Lock = 1;
                                }
                                else if (IKD->current_index == 3)
                                {
                                }
                                else
                                {
                                        if (Lock == 1)
                                                Lock = 0;
                                        else if (Lock == 0)
                                                Lock = 1;
                                        buffer = "";
                                }
                                if (Lock == -1)
                                {
                                        Lock = 0;
                                }
                        }
                        else if ((int)ch == (int)19)
                        {
                                MF->Save(Fname);
                        }
                        else if (((int)ch == (int)Down) && (Lock == 0))
                        {
                                if (IKD->current_index == 0)
                                {
                                        if (Config->current_index == -1)
                                        {
                                                if (!(addobj->current_index >= addobj->Values.size() - 1))
                                                        addobj->current_index++;
                                        }
                                        else if (Config->current_index == -2)
                                        {
                                                if (!(addDep->current_index >= addDep->Values.size() - 1))
                                                        addDep->current_index++;
                                        }
                                        else if (Config->current_index == -3)
                                        {
                                                if (!(addinc->current_index >= addinc->Values.size() - 1))
                                                        addinc->current_index++;
                                        }
                                        else if (!(Config->current_index >= Config->Values.size() - 1))
                                                Config->current_index++;
                                }
                                else if (IKD->current_index == 1)
                                {
                                        if (gpp->current_index == 0)
                                        {
                                                gpp->current_index = -1;
                                                buildtype->isOn = 1;
                                                buildtype->render();
                                        }
                                        else if (buildtype->ischoosing == 1)
                                        {
                                                if ((buildtype->current_index > 0))
                                                {
                                                        buildtype->current_index--;
                                                        buildtype->render();
                                                }
                                        }
                                        else if (!(gpp->current_index >= gpp->Values.size() - 1))
                                                gpp->current_index++;
                                }
                                else if (IKD->current_index == 2)
                                {
                                        if ((addsrc->Visible == 1))
                                        {
                                                if (!(addsrc->current_index >= addsrc->Values.size() - 1))
                                                        addsrc->current_index++;
                                        }
                                        else if (!(source->current_index >= source->Values.size() - 1))
                                                source->current_index++;
                                }
                                else if (IKD->current_index == 3)
                                {
                                        if (CompileBuild->ischoosing == 1)
                                        {
                                                if ((CompileBuild->current_index > 0))
                                                {
                                                        CompileBuild->current_index--;
                                                        CompileBuild->render();
                                                }
                                        }
                                }
                                else if (IKD->current_index == 5)
                                {
                                        if (Git_Commit->Visible)
                                        {
                                                if (Git_Commit->current_index < Git_Commit->Values.size())
                                                        Git_Commit->current_index++;
                                        }
                                        if (Git->Visible == 1)
                                        {
                                                if ((Git->current_index < Git->Values.size() - 1))
                                                {
                                                        Git->current_index++;

                                                        Git->render();
                                                }
                                        }
                                }
                        }
                        else if (((int)ch == (int)UP) && (Lock == 0))
                        {
                                if (IKD->current_index == 0)
                                {
                                        if (Config->current_index == -1)
                                        {
                                                if ((addobj->current_index > 0))
                                                        addobj->current_index--;
                                        }
                                        else if (Config->current_index == -2)
                                        {
                                                if ((addDep->current_index > 0))
                                                        addDep->current_index--;
                                        }
                                        else if (Config->current_index == -3)
                                        {
                                                if ((addinc->current_index > 0))
                                                        addinc->current_index--;
                                        }
                                        else if ((Config->current_index > 0))
                                                Config->current_index--;
                                }
                                if (IKD->current_index == 1)
                                {
                                        if ((gpp->current_index > 0))
                                                gpp->current_index--;
                                        else if (buildtype->ischoosing == 1)
                                        {
                                                if (!(buildtype->current_index >= buildtype->EA.size() - 1))
                                                {
                                                        buildtype->current_index++;
                                                        buildtype->render();
                                                }
                                        }
                                        else if (!(gpp->current_index >= 0))
                                        {
                                                gpp->current_index++;
                                        }
                                }
                                if (IKD->current_index == 2)
                                {
                                        if (addsrc->Visible == 1)
                                        {
                                                if ((addsrc->current_index > 0))
                                                        addsrc->current_index--;
                                        }
                                        else if ((source->current_index > 0))
                                                source->current_index--;
                                }
                                else if (IKD->current_index == 3)
                                {
                                        if (CompileBuild->ischoosing == 1)
                                        {
                                                if (!(CompileBuild->current_index >= CompileBuild->EA.size() - 1))
                                                {
                                                        CompileBuild->current_index++;
                                                        CompileBuild->render();
                                                }
                                        }
                                }
                                else if (IKD->current_index == 5)
                                {
                                        if (Git_Commit->Visible)
                                        {
                                                if (Git_Commit->current_index > 0)
                                                {
                                                        Git_Commit->current_index--;
                                                }
                                        }
                                        if (Git->Visible = 1)
                                        {
                                                if (Git->current_index > 0)
                                                        Git->current_index--;
                                        }
                                }
                        }
                        else if (((int)ch == (int)100) && (Lock == 0))
                        {
                                if (IKD->current_index == Ch.size() - 1)
                                {
                                        errors->add_Horizon("Max index->", 15, 6);
                                }
                                else
                                {
                                        IKD->current_index++;
                                        IKD->render();
                                }
                        }
                        else if ((int)ch == (int)127)
                        {
                                if (LargeBuffer.length() >= 1)
                                {
                                        LargeBuffer.pop_back();
                                }
                                if (buffer.length() >= 1)
                                        buffer.pop_back();
                        }
                        else
                        {
                                buffer.push_back(ch);
                        }

                        MF->RemoveView(IJ);
                        I->add_Horizon(buffer, y, x);
                }
        }
        return 0;
}