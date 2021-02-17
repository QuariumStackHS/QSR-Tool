
#include "includes/Argser.hpp"
#include "../Cfg.hpp"

#include "Modules.hpp"
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
Helper::Helper(Argser *HTL)
{
    string Module = HTL->argv[HTL->charstr + 1];
    if (strcmp(Module.c_str(), "Base") == 0)
    {
        // Argser::QSRcModule M = HTL->;
        cout << BOLDCYAN << "┌";
        for (float i = 0; i < 11 - 4; i++)
        {
            cout << "─";
        }
        //cout
        cout << "Function────────"
             << "┬───────"
             << "Description";
        for (float i = 1; i < (HTL->Cfg.Termwidth / 2.1); i++)
        {
            cout << BOLDCYAN << "─";
        }
        cout << "┐" << RESET << endl;
        for (int i = 0; i < HTL->__Tasks.size(); i++)
        {

            cout << BOLDCYAN << "│\t" << BOLDBLUE << HTL->__Tasks[i].Name << BOLDCYAN << "\t\t|\t" << GREEN << HTL->__Tasks[i].Desk << endl;
        }
    }
    else
    {
        Argser::QSRcModule M = HTL->getModule(Module);
        if (M.__Tasks.size() == 0)
        {
            cout << "No Module named: " << Module << endl;
            exit(0);
        }
        else
        {

            cout << BOLDCYAN << "┌";
            for (float i = 0; i < 11 - 4; i++)
            {
                cout << "─";
            }
            //cout
            cout << "Function────────┬"
                 << "Module name────┬───"
                 << "Description";
            for (float i = 1; i < (HTL->Cfg.Termwidth / 2.1); i++)
            {
                cout << BOLDCYAN << "─";
            }
            cout << "┐" << RESET << endl;
            for (int i = 0; i < M.__Tasks.size(); i++)
            {

                cout << BOLDCYAN << "│\t" << BOLDBLUE << M.__Tasks[i].Name << BOLDCYAN << "\t|" << MAGENTA << M.Module_Name << BOLDCYAN << "\t\t|\t" << GREEN << M.__Tasks[i].Desk << endl;
                /*for (float i = 0; i < HTL->Cfg.Termwidth + (strlen(HTL->__Tasks[i].Name.c_str()) - strlen("|\t\t|\t") - strlen(HTL->__Tasks[i].Desk.c_str()) / 2); i++)
        {
            cout << " ";
        }*/
                //cout << "│" << endl;
            }
        }
    }
    cout << BOLDCYAN << "└";
    for (float i = 1; i < (HTL->Cfg.Termwidth + 4); i++)
    {
        cout << BOLDCYAN << "─";
    }
    cout << "┘" << endl;
    exit(0);
}
int Argser::GetInsL(int Ins)
{
    return this->lines[Ins];
}
int Argser::newFunc(string funcName, string funcCode)
{

    this->FuncName.push_back(funcName);
    this->FuncCode.push_back(funcCode);
    //this->Func
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
void *Run(Argser *IN)
{
    string Cmd01 = "./Build/exe/";
    string Cmd02 = IN->Cfg.ProgrameName;
    string Cmd03 = ".exe";
    string Cmd = Cmd01.append(Cmd02);
    string Cmd1 = Cmd.append(Cmd03);

    cout << "Running using: \"" << Cmd << "\" | Return: " << system(Cmd1.c_str()) << endl;
    return 0;
}
void *Link(Argser *IN)
{
    string Cmd01 = "g++ Build/obj/*.QSRobj -o Build/exe/";
    string Cmd02 = IN->Cfg.ProgrameName;
    string Cmd03 = ".exe -std=c++";
    string Cmd = Cmd01.append(Cmd02);
    string Cmd1 = Cmd.append(Cmd03);
    string Cmd04 = to_string(IN->Cfg.CPPLang);
    string Cmd2 = Cmd1.append(Cmd04);
    int result = system(Cmd2.c_str());
    cout << BOLDBLUE << "Linking using: \"" << BOLDMAGENTA << Cmd2 << BLUE << "\" | Return: " << GREEN << result / 256 << RESET << endl;
    return 0;
}
void *Update(Argser *IN)
{
    if ((strcmp(IN->getcurrentIns().c_str(), "App-RCP") == 0))
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

    else if ((strcmp(IN->getcurrentIns().c_str(), "App-RUP") == 0))
    {
        system("git clone https://github.com/QuariumStackHS/QSR-Tool ");
        int i = system("g++ QSR-Tool/QSR/main.cpp -std=c++17 -o QSR.E");
        cout << "\nRecompiling QSR:" << endl;
        cout << "\tUpdating configuration.." << endl;
        cout << "\tCompiling QSR With Return code: " << i / 256 << endl;

        exit(0);
    }
    //return 1;
}
void *Compile(Argser *In)
{
    In->charstr++;
    cout << BOLDGREEN << "compiling: " << BOLDCYAN << In->Cfg.ProgrameName << "." << In->getVar(In->getcurrentIns()) << RESET << " as: " << BOLDYELLOW << In->getVar(In->getcurrentIns()) << ".QSRobj" << endl;
    string Cmd01 = "g++ src/";
    string Cmd02 = In->getVar(In->getcurrentIns());
    string Cmd03 = "/main.cpp -c -o Build/obj/";
    string Cmd = Cmd01.append(Cmd02);
    string Cmd1 = Cmd.append(Cmd03);
    string Cmd2 = Cmd1.append(Cmd02);
    string Cmd3 = Cmd2.append(".QSRobj -Iincludes -std=c++");
    string Cmd04 = to_string(In->Cfg.CPPLang);
    string Cmd05 = Cmd3.append(Cmd04);
    int result = system(Cmd3.c_str());
    cout << BOLDYELLOW << "Compile using: \"" << BOLDMAGENTA << Cmd05 << YELLOW << "\" | Return: " << GREEN << result / 256 << RESET << endl;

    //return 0;
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
    cout << "importing: " << SKN << endl;
    ifstream Src(getVar(getcurrentIns()).c_str());
    string Code;

    int SG = 0;
    while (getline(Src, Code))
    {
        SG++;
        std::vector<std::string> v;
        split(Code, v, ' ');
        //cout<<Code<<endl;
        auto it = argv.begin() + charstr + 1;
        for (int i = 0; i < v.size(); i++)
        {
            this->argc++;
            this->argv.insert(it + i, v[i]);
            cout << v[i] << endl;
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
        if (this->try_task(getcurrentIns()))
        {
        }
        else if (strcmp(getcurrentIns().c_str(), "init") == 0)
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
        else if (strcmp(getcurrentIns().c_str(), "exit") == 0)
        {
            cout << "---Exiting!---" << endl;
            exit(0);
        }
        else if (strcmp(getcurrentIns().c_str(), "Admin") == 0)
        {
            //Frame ad = Frame();
            //ad.setChar(3,3,'p');
            //ad.draw();
        }
        else if (strcmp(getcurrentIns().c_str(), "-QF") == 0)
        {
            charstr++;
            runfile();
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
        }
        else if (strcmp(getcurrentIns().c_str(), "del") == 0)
        {
            //charstr++;
        }
        else if (strcmp(getcurrentIns().c_str(), "var") == 0)
        {
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
        else if (strcmp(getcurrentIns().c_str(), "pause") == 0)
        {
            system("pause");
        }
        else if (strcmp(getcurrentIns().c_str(), "/*") == 0)
        {
            while (strcmp(getcurrentIns().c_str(), "*/") != 0)
            {
                charstr++;
            }
        }
        /*else if (strcmp(getVar(getcurrentIns()).c_str(), getcurrentIns().c_str()))
        {
            
            cout <<GREEN<< getVar(getcurrentIns())<<RESET << endl;
        }*/
        else if (strcmp(getcurrentIns().c_str(), "func") == 0)
        {
        }
        else if (strcmp(getcurrentIns().c_str(), "call") == 0)
        {
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
                cout << "Unknown Instruction: \"" << getcurrentIns() << "\"  at: " << GetInsL(charstr) << ":" << charstr << endl;
            }
        }
        //cout<<getVar(getcurrentIns())<<endl;
        //cout<<"isvar??"<<getcurrentIns()<<"->"<<(strcmp(getVar(getcurrentIns()).c_str(),"Null") == 1)<<endl;
    }
    return 0;
}
/*int Argser::AddCFnc(int (Argser::*CPP_Addrs)(), string Fnames)
{
    Fnc I;
    I.CPP_Addr = CPP_Addrs;
    I.Fname = Fnames;

    Fncs.push_back(I);
}*/
void *Call(Argser *IN)
{
    bool isexist = 0;
    //cout<<this->FuncName.size()<<endl;
    for (int i = 0; i < IN->FuncName.size(); i++)
    {
        if (strcmp(IN->FuncName[i].c_str(), IN->argv[IN->charstr + 1].c_str()) == 0)
        {
            isexist = 1;
        }
    }
    if (isexist)
    {
        cout << GREEN << "executing Function" << RESET << " \"" << YELLOW << IN->argv[IN->charstr + 1] << RESET << "\":\n";

        IN->executeFunc(IN->argv[IN->charstr + 1]);
    }
    else
    {
        cout << "Unknown Function:\"" << IN->argv[IN->charstr + 1] << "\"" << endl;
    }
    //charstr++;
    IN->charstr++;
    //charstr++;
}
void *Var(Argser *IN)
{

    //IN->charstr++;
    int VarI = IN->charstr + 1;
    IN->newVar(IN->getnextIns(), IN->argv[VarI + 1]);
    if (IN->Cfg.debug)
    {
        cout << "DEBUG: new variable named: \"" << IN->getcurrentIns() << "\" with value: " << IN->argv[VarI] << endl;
        //if()
    }
    IN->charstr++;
}
void *Export(Argser *IN)
{
}
void *import_Module(Argser *IN)
{
    string N = IN->getnextIns();
    cout << N << endl;
    for (int i = 0; i < IN->QS.size(); i++)
    {

        if (strcmp(IN->QS[i].Module_Name.c_str(), N.c_str()) == 0)
        {
            for (int j = 0; j < IN->QS[i].__Tasks.size(); j++)
            {
                IN->__Tasks.push_back(IN->QS[i].__Tasks[j]);
            }
            cout << "Module: " << N << " imported" << endl;
        }
    }

    //IN->add_Cask();
}
void *func(Argser *IN)
{
    IN->charstr++;
    string FucName = IN->getcurrentIns();
    //cout<<"Adding Func name: "<<FucName<<endl;
    string FncCode;
    bool EndOFFunc = 0;
    while (!EndOFFunc)
    {
        IN->charstr++;
        //cout<<getcurrentIns()<<endl;
        string InStr = IN->getcurrentIns();
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

    IN->newFunc(FucName, FncCode);
    //cout << "analized Func properly" << endl;
    //charstr--;
}
void *HelperI(Argser *TLM)
{
    Helper H = Helper(TLM);
}
int Argser::init_Func()
{
    //&Compile;
    add_Cask("compile", "Build+run", &Compile);
    add_Cask("link", "Link", &Link);
    add_Cask("App-RCP", "Recompile app from local source", &Update);
    add_Cask("App-RUP", "Update from master-Github and recompile", &Update);
    add_Cask("run", "Update from master-Github and recompile", &Run);
    add_Cask("import", "import [Module], note those are c++ import", &import_Module);
    add_Cask("var", "[Varname] [Value], note those are Strings", &Var);
    add_Cask("func", "[Fname] as begin: {Code} end; create new function", &func);
    add_Cask("call", "[Func]", &Call);
    add_Cask("-help", "[module]", &HelperI);

    
    Init_Modules(this);
    

    return 0;
}

int main(int argc, char **argv)
{
    cout << "---------QSR compiler---------" << endl;
    char ch;
    /*while(true){
    cin>>ch;
    //cout<<ch;
    }*/
    try
    {
        Argser Args = Argser(argc, argv);

        Args.Parse();

        //Args.Update();
    }
    catch (const std::exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
