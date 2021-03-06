#include "includes/config.hpp"
#include "includes/admin.hpp"
#include <fstream> // std::fstream
#include "../Cfg.hpp"
/*
Args parser, analyze and execute
*/

struct var
{
    string varname;
    string value;
};
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
class Helper
{
public:
    Helper();
};
Helper::Helper()
{
    cout << GREEN << "Commands avalaible (In Terminal and in scripts, note that both are treat the same)" << endl
         << "\"compile [Module]\"" << endl
         << "\"build [Module]\"" << endl
         << "\"link\", Link All QSRobj to build an APP" << endl
         << "\"var [varname] [varvalue]\" create new variable" << endl
         << "\"[real]|[local]-update\", update from local or from github" << endl
         << "\"init\", initialise all folders for QSR to perform" << endl
         << "\"add [Module]\", not that compile will compile the src/[Module]/main.cpp" << endl;
}
class Argser
{
public:
int AddCFnc(int (Argser::*)(),string);
    Argser(int, char **);
    int Parse();
    int Update();
    int runfile();
    int newVar(string, string);
    int DeleteVar(string);
    string getVar(string);
    int GetInsL(int);
    int GetSRCFId(string);
    //Todo
    int FncExist(string);
    int Execute(string);

private:
    struct Fnc{
        int (Argser::*CPP_Addr)();
        string Fname;
    };
    string getcurrentIns();
    int edit(string);
    int varsN = 0;
    int charstr = 0;
    int Compile();
    int Link();
    int executeFunc(string);
    int Run();
    int newFunc(string, string);
    int import();
    string getnextIns();
    vector<string> vars;
    vector<Fnc> Fncs;

    //2d xyz, x=func, y=code z=call
    int NextFNCID = 0;
    vector<string> FuncName;
    vector<string> FuncCode;
    //vector<std::string> vardata;
    Configurator Cfg = Configurator();
    int argc;
    vector<int> lines;
    vector<string> argv;
};
/*int Argser::GetSRCFId(string SrcF){
    for (int i=0;i<FuncSrc.size();i++){
        if(strcmp(SrcF.c_str(),FuncSrc[i].c_str())==0){
            return i;
        }
    }
    return -1;
}*/

int Argser::GetInsL(int Ins)
{
    return this->lines[Ins];
}
int Argser::newFunc(string funcName, string funcCode)
{

    this->FuncName.push_back(funcName);
    this->FuncCode.push_back(funcCode);
    //this->FuncSrc.push_back(funcSrc);
    //cout<<"attempting to Create function: "<<funcName<<" | "<<funcCode<<endl;
    this->NextFNCID++;

    return this->NextFNCID;
}
int Argser::executeFunc(string tFuncName)
{
    for (int i = 0; i < this->NextFNCID; i++)
    {
        if (strcmp(tFuncName.c_str(), this->FuncName[i].c_str()) == 0)
        {
            std::__1::vector<std::__1::string>::iterator it = this->argv.begin();
            vector<string> Ins;
            split(this->FuncCode[i], Ins, ' ');

            for (int j = 2; j < Ins.size(); j++)
            {
                this->argc++;
                this->argv.insert(it + charstr + j, Ins[j]);
                vector<int>::iterator itL = this->lines.begin();
                this->lines.insert(itL + charstr + j, 0);
            }
        }
    }
    return 0;
}
int Argser::DeleteVar(string)
{

    return 0;
}
string Argser::getVar(string varname)
{
    for (int i = 0; i < varsN; i++)
    {
        //cout<<this->vars[i+1]<<"?"<<endl;
        if (strcmp(this->vars[i].c_str(), varname.c_str()) == 0)
        {

            return this->vars[i + 1];
        }
        else
        {
            i++;
        }
    }
    return varname;
}

int Argser::newVar(string varname, string VarValue)
{
    if (strcmp(this->getVar(varname).c_str(), varname.c_str()) == 0)
    {
        this->vars.push_back(varname.c_str());
        this->vars.push_back(VarValue.c_str());
        varsN += 2;
    }
    else
    {

        for (int i = 0; i < varsN; i++)
        {
            //cout<<this->vars[i]<<"?"<<endl;
            //cout<<this->vars[i-1]<<"?"<<endl;
            if (strcmp(this->vars[i].c_str(), varname.c_str()) == 0)
            {
                size_t klm = i;
                //cout<<this->vars[i+1]<<endl;
                vars[i + 1] = VarValue;
                //cout<<this->vars[i+1]<<endl;
                //cout<<"\n\n"<<endl;
            }
            else
            {
                i++;
            }
        }
    }

    return 2;
}

int Argser::runfile()
{
    string Code;

    string RQFS = "-----Running QF Script: ";
    string SKN = getVar(getcurrentIns());
    cout << RQFS << RESET << RED << SKN << RESET << "-----";
    cout << endl;
    // Read from the text file
    ifstream Src(getVar(getcurrentIns()).c_str());
    charstr++;
    int SG = 0;
    while (getline(Src, Code))
    {
        SG++;
        std::vector<std::string> v;
        split(Code, v, ' ');
        //cout << Code<<endl;
        int k = v.size();
        for (int i = 0; i < k; i++)
        {
            if (strcmp(v[i].c_str(), ""))
            {
                this->argv.push_back(v[i].c_str());
                this->argc++;
            }
            this->lines.push_back(SG);
        }

        if (this->Cfg.debug)
            cout << BOLDGREEN << "Line: " << BOLDCYAN << SG << RESET << " \t|" << Code;
        int Termwidth = this->Cfg.Termwidth - Code.size() * 2;
        for (int i = 0; i < Termwidth / 2; i++)
        {
            if (this->Cfg.debug)
                cout << " ";
        }
        if (Termwidth % 2 != 0)
        {
            if (this->Cfg.debug)
                cout << " ";
        }
        if (this->Cfg.debug)
            cout << "|" << BOLDYELLOW << ";" << RESET << endl;

        //cout << "Line: " << SG<< " " << Code << endl;
        //return 0;
    }
    cout << endl;
    string EOFD = "End Of File";

    int Termwidth = this->Cfg.Termwidth - EOFD.size() * 2;
    for (int i = 0; i < Termwidth / 2; i++)
    {
        if (this->Cfg.debug)
            cout << "-";
    }
    cout << RESET << RED << EOFD << RESET;
    for (int i = 0; i < Termwidth / 2; i++)
    {
        if (this->Cfg.debug)
            cout << "-";
    }
    if (Termwidth % 2 != 0)
    {
        if (this->Cfg.debug)
            cout << "-";
    }
    cout << endl
         << endl;
    // Close the file
    Src.close();
    return 0;
}
int Argser::Run()
{
    string Cmd01 = "./Build/exe/";
    string Cmd02 = Cfg.ProgrameName;
    string Cmd03 = ".exe";
    string Cmd = Cmd01.append(Cmd02);
    string Cmd1 = Cmd.append(Cmd03);

    cout << "Running using: \"" << Cmd << "\" | Return: " << system(Cmd1.c_str()) << endl;
    return 0;
}
int Argser::Link()
{
    string Cmd01 = "g++ Build/obj/*.QSRobj -o Build/exe/";
    string Cmd02 = Cfg.ProgrameName;
    string Cmd03 = ".exe -std=c++";
    string Cmd = Cmd01.append(Cmd02);
    string Cmd1 = Cmd.append(Cmd03);
    string Cmd04 = to_string(Cfg.CPPLang);
    string Cmd2 = Cmd1.append(Cmd04);
    int result = system(Cmd2.c_str());
    cout << BOLDBLUE << "Linking using: \"" << BOLDMAGENTA << Cmd2 << BLUE << "\" | Return: " << GREEN << result / 256 << RESET << endl;
    return 0;
}
int Argser::Update()
{
    if ((strcmp(getcurrentIns().c_str(), "local-update") == 0))
    {
        cout << "\nRecompiling QSR:" << endl;
        cout << "\tUpdating configuration.." << endl;
        int i = system("g++ QSR/main.cpp -std=c++17 -o QSR.E");
        if (i == 0)
        {
            cout << "\tCompiled QSR With Return code: " << i << endl;
        }
        else
        {
            cout << BOLDRED "Error while Compiling QSR With Return code: " << i / 256 << RESET << endl;
        }

        exit(0);
    }

    else if ((strcmp(getcurrentIns().c_str(), "real-update") == 0))
    {
        int i = system("g++ QSR-Tool/QSR/main.cpp -std=c++17 -o QSR.E");
        cout << "\nRecompiling QSR:" << endl;
        cout << "\tUpdating configuration.." << endl;
        cout << "\tCompiling QSR With Return code: " << i / 256 << endl;

        exit(0);
    }
    return 1;
}
int Argser::Compile()
{
    charstr++;
    cout << BOLDGREEN << "compiling: " << BOLDCYAN << Cfg.ProgrameName << "." << getVar(getcurrentIns()) << RESET << " as: " << BOLDYELLOW << getVar(getcurrentIns()) << ".QSRobj" << endl;
    string Cmd01 = "g++ src/";
    string Cmd02 = getVar(getcurrentIns());
    string Cmd03 = "/main.cpp -c -o Build/obj/";
    string Cmd = Cmd01.append(Cmd02);
    string Cmd1 = Cmd.append(Cmd03);
    string Cmd2 = Cmd1.append(Cmd02);
    string Cmd3 = Cmd2.append(".QSRobj -Iincludes -std=c++");
    string Cmd04 = to_string(Cfg.CPPLang);
    string Cmd05 = Cmd3.append(Cmd04);
    int result = system(Cmd3.c_str());
    cout << BOLDYELLOW << "Compile using: \"" << BOLDMAGENTA << Cmd05 << YELLOW << "\" | Return: " << GREEN << result / 256 << RESET << endl;

    return 0;
}
string Argser::getcurrentIns()
{
    return this->argv[charstr];
}
string Argser::getnextIns()
{
    charstr++;
    return getcurrentIns();
}
int Argser::edit(string FN)
{

    return 0;
}
int Argser::import()
{

    string SKN = getVar(getnextIns());
    cout<<"importing: "<<SKN<<endl;
    ifstream Src(getVar(getcurrentIns()).c_str());
    string Code;

    int SG = 0;
    while (getline(Src, Code))
    {
        SG++;
        std::vector<std::string> v;
        split(Code, v, ' ');
        //cout<<Code<<endl;
        auto it = argv.begin() + charstr+1;
        for (int i = 0; i < v.size(); i++)
        {
                this->argc ++;
                this->argv.insert(it + i, v[i]);
                cout<<v[i]<<endl;
        }


        //this->argc++;

        //cout << Code<<endl;
    }
    getnextIns();
    charstr++;
    cout << "klol" << endl;

    return 0;
}
int Argser::Parse()
{
    while (charstr < this->argc)
    {

        charstr++;

        //cout << charstr << getcurrentIns() << endl;
        //if ()
        if (strcmp(getcurrentIns().c_str(), "init") == 0)
        {
            system("mkdir Src");
            system("mkdir includes");
            system("mkdir Build");
            system("mkdir Build/obj");
            system("mkdir Build/exe");
            system("mkdir scripts");
        }
        else if (strcmp(getcurrentIns().c_str(), "import") == 0)
        {
            import();
        }
        else if (strcmp(getcurrentIns().c_str(), "link") == 0)
        {
            Link();
        }
        else if (strcmp(getcurrentIns().c_str(), "exit") == 0)
        {
            cout << "---Exiting!---" << endl;
            exit(0);
        }
        else if (strcmp(getcurrentIns().c_str(), "Admin") == 0)
        {
            Frame ad = Frame();
            //ad.setChar(3,3,'p');
            //ad.draw();
        }
        else if (strcmp(getcurrentIns().c_str(), "-QF") == 0)
        {
            charstr++;
            runfile();
        }
        else if (strcmp(getcurrentIns().c_str(), "build") == 0)
        {
            //charstr++;
            Compile();
            Link();
        }
        else if (strcmp(getcurrentIns().c_str(), "dump") == 0)
        {
            cout << CYAN << "Address\t" << GREEN << "instruction" << endl;
            int lastL = 0;
            for (int i = 0; i < this->argv.size(); i++)
            {
                int L = GetInsL(i);

                if ((L == 0) || (strcmp(this->argv[i].c_str(), "") == 0))
                {
                }
                else
                {
                    if (lastL == L)
                    {
                        cout << "|\t"
                             << ":" << BOLDCYAN << i << RESET << "\t" << BOLDGREEN << "\"" << this->argv[i] << "\"" << RESET;
                    }
                    else
                    {
                        cout << endl
                             << "" << L + 1;
                    }
                }
                lastL = L;
            }
        }
        else if (strcmp(getcurrentIns().c_str(), "run") == 0)
        {
            Run();
        }
        else if (strcmp(getcurrentIns().c_str(), "del") == 0)
        {
            //charstr++;
        }
        else if (strcmp(getcurrentIns().c_str(), "var") == 0)
        {

            charstr++;
            newVar(getcurrentIns(), this->argv[charstr + 1]);
            if (this->Cfg.debug)
            {
                cout << "DEBUG: new variable named: \"" << getcurrentIns() << "\" with value: " << this->argv[charstr + 1] << endl;
                //if()
            }
            charstr++;
        }
        else if (strcmp(getcurrentIns().c_str(), "add") == 0)
        {
            charstr++;

            string Cmd00 = "mkdir src/";
            string Cmd01 = getcurrentIns();
            string Cmd02 = Cmd00.append(Cmd01);
            system(Cmd02.c_str());
            string Cmd03 = "mkdir includes/";
            string Cmd04 = getcurrentIns();
            string Cmd05 = Cmd03.append(Cmd04);
            system(Cmd05.c_str());
            /*
        
        
        */
        }
        else if (strcmp(getcurrentIns().c_str(), "real-update") == 0)
        {
            system("git clone https://github.com/QuariumStackHS/QSR-Tool ");
            Update();
        }
        else if (strcmp(getcurrentIns().c_str(), "local-update") == 0)
        {
            Update();
            //system("g++ -c Cfg.hpp -o QSR/Private/Config.obj");
            //system("g++ QSR/Private/*.obj -o QSR.E");
        }
        else if (strcmp(getcurrentIns().c_str(), "pause") == 0)
        {
            system("pause");
        }
        else if (strcmp(getcurrentIns().c_str(), "export") == 0)
        {
            if (strcmp(getcurrentIns().c_str(), "export") == 0)
            {
            }
            else
            {
                cout << RED << "Syntaxe error expected \"as\" keyword after export exemple: export as filname.qf" << RESET << endl;
            }
            //charstr++;
        }
        else if (strcmp(getcurrentIns().c_str(), "/*") == 0)
        {
            while (strcmp(getcurrentIns().c_str(), "*/") != 0)
            {
                charstr++;
            }
        }
        else if (strcmp(getcurrentIns().c_str(), "test") == 0)
        {
            Compile();
            Link();
            Run();
        }
        else if (strcmp(getcurrentIns().c_str(), "compile") == 0)
        {
            Compile();
            //system()
        }
        /*else if (strcmp(getVar(getcurrentIns()).c_str(), getcurrentIns().c_str()))
        {
            
            cout <<GREEN<< getVar(getcurrentIns())<<RESET << endl;
        }*/
        else if (strcmp(getcurrentIns().c_str(), "func") == 0)
        {
            charstr++;
            string FucName = getcurrentIns();
            //cout<<"Adding Func name: "<<FucName<<endl;
            string FncCode;
            bool EndOFFunc = 0;
            while (!EndOFFunc)
            {
                charstr++;
                //cout<<getcurrentIns()<<endl;
                string InStr = getcurrentIns();
                if (strcmp(InStr.c_str(), "end;") == 0)
                {
                    EndOFFunc = 1;
                }
                else
                {
                    FncCode.append(InStr.c_str());
                    FncCode.append(" ");
                }
            }

            this->newFunc(FucName, FncCode);
            //cout << "analized Func properly" << endl;
            //charstr--;
        }
        else if (strcmp(getcurrentIns().c_str(), "call") == 0)
        {
            bool isexist = 0;
            //cout<<this->FuncName.size()<<endl;
            for (int i = 0; i < this->FuncName.size(); i++)
            {
                if (strcmp(this->FuncName[i].c_str(), this->argv[charstr + 1].c_str()) == 0)
                {
                    isexist = 1;
                }
            }
            if (isexist)
            {
                cout << GREEN << "executing Function" << RESET << " \"" << YELLOW << this->argv[charstr + 1] << RESET << "\":\n";

                this->executeFunc(this->argv[charstr + 1]);
            }
            else
            {
                cout << "Unknown Function:\"" << this->argv[charstr + 1] << "\"" << endl;
            }
            //charstr++;
            charstr++;
            //charstr++;
        }
        else if (strcmp(getcurrentIns().c_str(), "-help") == 0)
        {
            Helper();
            exit(0);
        }
        else if (strcmp(getcurrentIns().c_str(), "") == 0)
        {
        }
        else
        {
            bool isexist = 0;
            //cout<<this->FuncName.size()<<endl;
            for (int i = 0; i < this->FuncName.size(); i++)
            {
                if (strcmp(this->FuncName[i].c_str(), getcurrentIns().c_str()) == 0)
                {
                    isexist = 1;
                }
            }
            if (isexist == 0)
            {
                cout << "Unknown Instruction: \"" << getcurrentIns() << "\"  at: " <<GetInsL(charstr)<<":"<< charstr << endl;
            }
        }
        //cout<<getVar(getcurrentIns())<<endl;
        //cout<<"isvar??"<<getcurrentIns()<<"->"<<(strcmp(getVar(getcurrentIns()).c_str(),"Null") == 1)<<endl;
    }
    return 0;
}
int Argser::AddCFnc(int (Argser::*CPP_Addrs)(),string Fnames){
    Fnc I;
    I.CPP_Addr=CPP_Addrs;
    I.Fname=Fnames;

    Fncs.push_back(I);
}
Argser::Argser(int argc, char **argv)
{


    this->argc = argc;
    for (int i = 0; i < argc; i++)
    {
        string f = argv[i];
        this->argv.push_back(f);
    }
}

int main(int argc, char **argv)
{
    cout << "---------QSR compiler---------" << endl;

    try
    {
        Argser Args = Argser(argc, argv);

        Args.Parse();

        Args.Update();
    }
    catch (const std::exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
