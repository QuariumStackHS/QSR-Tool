#ifndef Argser_Hpp
#define Argser_Hpp 1
#include "config.hpp"
#include "admin.hpp"
#include <fstream> // std::fstream



class Argser
{
public:
Argser(int argc, char **argv)
{

    this->argc = argc;
    for (int i = 0; i < argc; i++)
    {
        string f = argv[i];
        this->argv.push_back(f);
    }
    this->init_Func();
    Cfg=Configurator();
}
    struct CallableObj
    {
        void *(*Taddr)(Argser *);
        string Name;
        string Desk;
    };
    class QSRcModule
    {
    public:
    /*
        QSRcModule(string ModuleName)
        {
            this->Module_Name = ModuleName;
        }
        QSRcModule()
        {
            
        }*/
        int Set_Name(string name){
            this->Module_Name=name;
        }
    
        int add_Cask(string fname, string desk, void *(taddr)(Argser *))
        {
            CallableObj NCO;
            NCO.Desk = desk;
            NCO.Name = fname;
            NCO.Taddr = taddr;
            __Tasks.push_back(NCO);
            return 0;
        }
        vector<CallableObj> __Tasks;
        string Module_Name;
    };
    //typedef void *(*TaskAddr)(Argser*);

    //int AddCFnc(TaskAddr, string);

    
    int Parse();
    //int Update();
    int runfile();
    int newVar(string, string);
    int DeleteVar(string);
    string getVar(string);
    int GetInsL(int);
    int GetSRCFId(string);
    //Todo
    int FncExist(string);
    int Execute(string);

    //private:
    vector<QSRcModule> QS;
    int add_Module(QSRcModule MD)
    {
        QS.push_back(MD);
        return 0;
    }
    int add_Cask(string fname, string desk, void *(taddr)(Argser *))
    {
        CallableObj NCO;
        NCO.Desk = desk;
        NCO.Name = fname;
        NCO.Taddr = taddr;
        __Tasks.push_back(NCO);
        return 0;
    }
    int RunTask()
    {

        //return Taddr();
        return 0;
    }
    bool is_Name(CallableObj Obj, string Test_Name)
    {
        return (strcmp(Obj.Name.c_str(), Test_Name.c_str()) == 0);
    }
    /*string getname()
        {
            return Name;
        }
*/
    int init_Func();

    int try_task(string tname)
    {
        for (int i = 0; i < this->__Tasks.size(); i++)
        {
            if (is_Name(this->__Tasks[i], tname))
            {

                auto Tadr = __Tasks[i].Taddr;
                Tadr(this);
                return 1;
            }
        }
        return 0;
    }
    QSRcModule getModule(string name){
    for (int i = 0; i < this->QS.size(); i++)
        {
            if (strcmp(this->QS[i].Module_Name.c_str(), name.c_str())==0)
            {

                //auto Tadr = __Tasks[i].Taddr;
                //Tadr(this);
                return this->QS[i];
            }
        }
        QSRcModule M;
        return M;
    }

    vector<CallableObj> __Tasks;
    struct Fnc
    {
        int (Argser::*CPP_Addr)();
        string Fname;
    };
    string getcurrentIns();
    int edit(string);
    int varsN = 0;
    int charstr = 0;
    //int Compile();
    //int Link();
    int executeFunc(string);
    //int Run();
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
    Configurator Cfg;
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
class Helper
{
public:
    Helper(Argser *);
};
#else

#endif
