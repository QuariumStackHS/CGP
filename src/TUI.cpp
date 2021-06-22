#include "TUI.hpp"
#include <cstring>
#include <sstream>
int Debug = 0;
struct winsize s;
View::ViewChar::ViewChar(int X, int Y, char C)
{
    this->Char = C;
    this->Xpos = X;
    this->Ypos = Y;
}
View::View()
{
}
void View::render()
{
}
string View::SaveAll()
{
    return "";
}
View::ViewChar::ViewChar(int X, int Y, char C, View *Master)
{
    this->Char = C;
    this->Xpos = X;
    this->Ypos = Y;
    this->_MasterView = Master;
}
void View::add_Vertical(string str, int y, int x)
{
    int iY = y;
    int IX = 0;
    int iscalc = 0;
    for (int iX = x; iX < x + strlen(str.c_str()); iX++)
    {
        bool is = 0;
        for (int i = 0; i < this->Chars.size(); i++)
        {
            if ((this->Chars[i]->Ypos == iX) && (this->Chars[i]->Xpos == iY))
            {
                this->Chars[i]->Char = str[iX - x];
                this->Chars[i]->_MasterView = this;
                is = 1;
            }
        }
        if (is == 0)
        {

            ViewChar *C = new View::ViewChar(iY, iX, str[iX - x], this);
            this->Chars.push_back(C);
        }
    }
}
void View::add_Horizon(string str, int y, int x)
{
    int iY = y;
    int IX = 0;
    int iscalc = 0;
    for (int iX = x; iX < x + strlen(str.c_str()); iX++)
    {
        if ((int)str[iX - x] == (int)'\n')
        {
            iscalc = iX - x + 1;
            iY++;
        }
        else
        {
            bool is = 0;
            for (int i = 0; i < this->Chars.size(); i++)
            {
                if ((this->Chars[i]->Xpos == iX) && (this->Chars[i]->Ypos == iY))
                {
                    this->Chars[i]->Char = str[iX - x];
                    this->Chars[i]->_MasterView = this;
                    is = 1;
                }
            }
            if (is == 0)
            {
                ViewChar *C = new View::ViewChar(iX - iscalc, iY, str[iX - x], this);
                this->Chars.push_back(C);
            }
        }
    }
}

void MasterView::Display()
{
    for (int i = 0; i < MAXx; i++)
    {
        if (Debug)
        {
            cout << i << "|";
        }
        cout << this->Buffer[i] << "\n\r";
    }
}

void MasterView::Render()
{

    for (int i = 0; i < this->Views.size(); i++)
    {
        if (this->Views[i]->Visible)
        {
            this->Views[i]->render();
            for (int j = 0; j < this->Views[i]->Chars.size(); j++)
            {
                for (int k = 0; k < this->Views[i]->Chars[j]->Xpos; k++)
                {
                    if (this->Buffer[this->Views[i]->Chars[j]->Ypos][k] == '\0')
                        this->Buffer[this->Views[i]->Chars[j]->Ypos][k] = ' ';
                }
                this->Buffer[this->Views[i]->Chars[j]->Ypos][this->Views[i]->Chars[j]->Xpos] = this->Views[i]->Chars[j]->Char;
                if (Debug)
                    cout << this->Views[i]->Chars[j]->Char << "|[" << this->Views[i]->Chars[j]->Xpos << "][" << this->Views[i]->Chars[j]->Ypos << "]" << endl;
            }
        }
    }
}
void MasterView::RemoveView(View *SD)
{
    for (int i = 0; i < this->Views.size(); i++)
    {
        if (this->Views[i] == SD)
        {
            for (int j = 0; j < this->Views[i]->Chars.size(); j++)
            {
                this->Buffer[this->Views[i]->Chars[j]->Ypos][this->Views[i]->Chars[j]->Xpos] = ' ';
            }
            this->Views.erase(this->Views.begin() + i);
        }
    }
}
void MasterView::RemoveView(EditorView *SD)
{
    for (int i = 0; i < this->DATAC.size(); i++)
    {
        if (this->DATAC[i] == SD)
        {
            for (int j = 0; j < this->DATAC[i]->Chars.size(); j++)
            {
                this->Buffer[this->DATAC[i]->Chars[j]->Ypos][this->DATAC[i]->Chars[j]->Xpos] = ' ';
            }
            this->DATAC.erase(this->DATAC.begin() + i);
        }
    }
}
void View::clear()
{
    this->Chars.erase(this->Chars.begin(), this->Chars.end());
}
MasterView::MasterView(int maxX, int maxY)
{
    //this->IN=;
    this->MAXx = maxX;
    this->MAXy = maxY;
}
void MasterView::Save(string Filename)
{
    if(Filename[5]!='-'){
    vector<string> Did;
    ofstream myfile;
    myfile.open(Filename.c_str(), ios_base::out);
    stringstream ss;
    ss << "";
    //cout<<"Begin"<<endl;
    for (int i = 0; i < this->DATAC.size(); i++)
    {
        string current = this->DATAC[i]->SaveAll();
        bool good = 1;
        for (int j = 0; j < Did.size(); j++)
        {
            if (strcmp(Did[j].c_str(), current.c_str()) == 0)
            {
                good = 0;
            }
            else
            {
                Did.push_back(current);
            }
        }
        if (good == 1)
            ss << current;
    }
    for (int i = 0; i < this->DATAD.size(); i++)
    {
        string current = this->DATAD[i]->SaveAll();
        bool good = 1;
        for (int j = 0; j < Did.size(); j++)
        {
            if (strcmp(Did[j].c_str(), current.c_str()) == 0)
            {
                good = 0;
            }
            else
            {
                Did.push_back(current);
            }
        }
        if ((good == 1) && (current[0] != ' '))
            ss << current;
    }
    myfile << ss.str();
    myfile.close();
    }
}
void MasterView::addView(View *IN)
{

    this->Views.push_back(IN);
}
void MasterView::clear()
{
    for (int i = 0; i < MaxY - 1; i++)
    {
        for (int j = 0; j < MaxX - 1; j++)
        {
            this->Buffer[j][i] = ' ';
        }
    }
}
void MasterView::addView(DepTree *IN)
{
    this->DATAE.push_back(IN);
    Views.push_back(IN);
}
string MSTS::Save()
{
    return '\n' + Alias + " = '" + _Value + "'";
}
MSTS::MSTS(string Key, string Value, string alias)
{
    this->_Key = Key;
    this->Alias = alias;
    this->_Value = Value;
}
string EditorView::SaveAll()
{
    string Chunk = "";
    for (int i = 0; i < this->Values.size(); i++)
    {

        if ((strcmp(this->Values[i]->Alias.c_str(), "") == 0) || (this->Values[i]->Alias[0] == ' '))
        {
        }
        else
            Chunk += this->Values[i]->Save();
    }
    //cout<<Chunk<<endl;
    //char i;
    //cin>>i;
    return Chunk;
}
void EditorView::render()
{
    this->clear();
    for (int i = 0; i < Values.size(); i++)
    {
        string Data = "";
        if (this->current_index == i)
        {
            if(Values[i]->_Key.size()<=2)
            Data = GREEN+ Values[i]->_Key +RESET+ " : " + RED + Values[i]->_Value + RESET;
            else
             Data = Values[i]->_Key + " : " + RED + Values[i]->_Value + RESET;
        }
        else
        {
            Data = Values[i]->_Key + " : " + Values[i]->_Value;
        }

        this->add_Horizon(Data, this->x + i, this->y);
    }
}
void MasterView::addView(dropdownlist *IN)
{
    bool exist = 0;
    for (int i = 0; i < DATAD.size(); i++)
    {
        if (DATAD[i] == IN)
        {
            exist = 1;
        }
    }
    if (exist == 0)
        DATAD.push_back(IN);
    Views.push_back(IN);
}
void MasterView::addView(EditorView *IN)
{
    bool exist = 0;
    for (int i = 0; i < DATAC.size(); i++)
    {
        if (DATAC[i] == IN)
        {
            exist = 1;
        }
    }
    if (exist == 0)
        DATAC.push_back(IN);
    Views.push_back(IN);
}
void EditorView::add_MSTS(MSTS *data, int index)
{
    Values.insert(Values.begin() + index, data);
}
EditorView::EditorView(int XX, int YY)
{
    this->x = XX;
    this->y = YY;
}
vign::vign(vector<string> comb, int xX, int yY)
{
    for (int i = 0; i < comb.size(); i++)
    {
        int nyt = comb[i].size();
        if (nyt > this->bigestComb)
        {
            this->bigestComb = nyt;
        }
        this->Comb.push_back(comb[i]);
    }
    this->x = xX;
    this->y = yY;
}
void vign::render()
{
    string vignette = "";

    for (int i = 0; i < this->Comb.size(); i++)
    {
        if (i == this->current_index)
        {
            vignette.append(((string) "|").append(BOLDBLUE) + this->Comb[i] + RESET);
        }
        else
        {
            vignette.append(((string) "|") + this->Comb[i]);
        }
    }
    vignette.append("|");
    this->add_Horizon(vignette, this->x, this->y);
}
void MasterView::Load(string Filename)
{
    //Alias ='Value'\n

    string line;
    ifstream myfile(Filename);
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

                    for (int i = 0; i < this->DATAC.size(); i++)
                    {
                        for (int j = 0; j < this->DATAC[i]->Values.size(); j++)
                        {
                            //cout << this->DATAC[i]->Values[j]->Alias << this->DATAC[i]->Values[j]->Alias.size() << endl;
                            if (strcmp(this->DATAC[i]->Values[j]->Alias.c_str(), Alias.c_str()) == 0)
                            {
                                this->DATAC[i]->Values[j]->_Value = Value;
                            }
                        }
                    }
                    for (int i = 0; i < this->DATAD.size(); i++)
                    {
                        if (strcmp(this->DATAD[i]->Alias.c_str(), Alias.c_str()) == 0)
                        {
                            this->DATAD[i]->current_index = stoi(Value);
                        }
                    }
                }
            }
        }
        //char fd;
        //cin>>fd;
        myfile.close();
    }

   // else
        //cout << "Unable to Load file\"" << Filename << "\"" << endl;
}
dropdownlist::dropdownlist(int X, int Y)
{
    this->x = X;
    this->y = Y;
}
void dropdownlist::add_MSTS(MSTS *data, int index)
{
    EA.insert(EA.begin() + index, data);
}
string dropdownlist::SaveAll()
{
    return "\n" + this->Alias + " = '" + to_string(this->current_index) + "'";
}
void dropdownlist::render()
{
    add_Horizon(this->Key, x, y);
    if (ischoosing == 1)
    {
        for (int i = 0; i < this->EA.size(); i++)
        {
            if (i == this->current_index)
            {
                this->add_Horizon(((string)RED) + this->EA[i]->_Value + RESET, x - i, y + this->Key.size());
            }
            else
            {
                this->add_Horizon(this->EA[i]->_Value, x - i, y + this->Key.size());
            }
        }
    }
    else
    {
        if (isOn)
        {
            this->add_Horizon(((string)RED) + this->EA[this->current_index]->_Value + RESET, x, y + this->Key.size());
        }
        else
        {
            this->add_Horizon(this->EA[this->current_index]->_Value, x, y + this->Key.size());
        }
    }
}
Coll::Coll(int x, int y)
{
    this->x = x;
    this->y = y;
}
void Coll::add_MSTS(MSTS *I, int j)
{
    EA.insert(EA.begin() + j, I);
}
/*
void Coll::render(){
    for(int i=0;i<EA.size();i++){
        string s=EA[i]->
    }
}
*/
void DepTree::render()
{
    this->add_Horizon(this->name, 3, 14);
    for (int i = 0; i < this->Childs.size(); i++)
    {
        Childs[i]->ChildRender(this, 5, i + 1);
        this->add_Horizon("/", 4, (i + 1) * 10);
    }
}
void DepTree::ChildRender(DepTree *This, int Level, int right)
{
    This->add_Horizon(this->name, Level, right * 10);
    Level++;
    for (int i = 0; i < this->Childs.size(); i++)
    {
        Childs[i]->ChildRender(This, Level + 1, i + right);
        This->add_Horizon("\\", Level, (i + right) * 10);
    }
}
int DepTree::AddChild(DepTree *IN)
{
    this->Childs.push_back(IN);
}
DepTree::DepTree(int X, int Y)
{
    this->x = X;
    this->y = Y;
}
void MSTS_Vector::push_back(MSTS *Boddy)
{
    this->Mok.push_back(Boddy);
}
MSTS *MSTS_Vector::get_from_alias(string al)
{
    for (int i = 0; i < this->Mok.size(); i++)
    {
        if (strcmp(this->Mok[i]->Alias.c_str(), al.c_str()) == 0)
            return this->Mok[i];
    }
    return new MSTS("", "", "");
}
MSTS *MSTS_Vector::get_from_Value(string al)
{
    for (int i = 0; i < this->Mok.size(); i++)
    {
        if (strcmp(this->Mok[i]->_Value.c_str(), al.c_str()) == 0)
            return this->Mok[i];
    }
    return new MSTS("", "", "");
}
MSTS_Vector::MSTS_Vector()
{
}
void MasterView::set_MSTS_Vector(MSTS_Vector *thatvector)
{
    this->dvector = thatvector;
}
void MasterView::load_into_Vector()
{
    for (int i = 0; i < this->DATAC.size(); i++)
    {
        for (int j = 0; j < DATAC[i]->Values.size(); j++)
            this->dvector->push_back(DATAC[i]->Values[j]);
    }
    for (int i = 0; i < this->DATAD.size(); i++)
    {
        for (int j = 0; j < DATAD[i]->EA.size(); j++)
            this->dvector->push_back(DATAD[i]->EA[j]);
    }
}
