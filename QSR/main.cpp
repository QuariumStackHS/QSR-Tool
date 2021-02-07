#include "includes/config.hpp"
#include <fstream> // std::fstream

#include "../Cfg.hpp"
/*
Args parser, analyze and execute
*/
class Argser
{
public:
    Argser(int, char **);
    int Parse();
    int Update();
    int runfile();

private:
    int charstr = 0;
    int Compile();
    int Link();
    int Run();

    Configurator Cfg = Configurator();
    int argc;
    vector<std::string>argv;
};
int parse(string code)
{
    return 0;
}
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
int Argser::runfile()
{
    string Code;
    
    // Read from the text file
    ifstream Src(this->argv[charstr]);
    charstr++;
    // Use a while loop together with the getline() function to read the file line by line
    int SG=0;
    while (getline(Src, Code))
    {SG++;
        // Output the text from the file
        std::vector<std::string> v;
        split( Code, v, ' ');
        cout <<"Line:"<<SG<<" "<< Code<<endl;
        //if (strcmp(Code.c_str(),"exit")==0){
            
        
        //cout << Code<<endl;
        int k=v.size();
        for (int i=0; i<k;i++){
          auto it = this->argv.begin() + 1;
            this->argv.insert( it, v[i].c_str());
            this->argc++;
        }
        //return 0;
        
    }
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

    cout << "Linking using: \"" << Cmd2 << "\" | Return: " << system(Cmd2.c_str()) << endl;
    return 0;
}
int Argser::Update()
{
    if ((strcmp(this->argv[charstr].c_str(), "local-update") == 0))
    {
        int i = system("g++ QSR/main.cpp -std=c++17 -o QSR.E");
        cout << "\nRecompiling QSR:" << endl;
        cout << "\tUpdating configuration.." << endl;
        cout << "\tCompiling QSR With Return code: " << i << endl;

        exit(0);
    }

    else if ((strcmp(this->argv[charstr].c_str(), "real-update") == 0))
    {
        int i = system("g++ QSR-Tool/QSR/main.cpp -std=c++17 -o QSR.E");
        cout << "\nRecompiling QSR:" << endl;
        cout << "\tUpdating configuration.." << endl;
        cout << "\tCompiling QSR With Return code: " << i << endl;

        exit(0);
    }
    return 1;
}
int Argser::Compile()
{
    if (NULL)
    {
        cout << "Compile need at least 2 args exemple: ./QSR compile main" << endl;
    }
    else
    {
        cout << "compiling: " << Cfg.ProgrameName << "." << this->argv[charstr] << endl;
        string Cmd01 = "g++ src/";
        string Cmd02 = this->argv[charstr];
        string Cmd03 = "/main.cpp -c -o Build/obj/";
        string Cmd = Cmd01.append(Cmd02);
        string Cmd1 = Cmd.append(Cmd03);
        string Cmd2 = Cmd1.append(Cmd02);
        string Cmd3 = Cmd2.append(".QSRobj -Iincludes -std=c++");
        string Cmd04 = to_string(Cfg.CPPLang);
        string Cmd05 = Cmd3.append(Cmd04);
        cout << "Compile using: \"" << Cmd05 << "\" | Return: " << system(Cmd3.c_str()) << endl;
    }

    return 0;
}
int Argser::Parse()
{
    while (charstr < this->argc)
    {
        charstr++;
        if (strcmp(this->argv[charstr].c_str(), "init") == 0)
        {
            system("mkdir Src");
            system("mkdir includes");
            system("mkdir Build");
            system("mkdir Build/obj");
            system("mkdir Build/exe");
        }
        else if (strcmp(this->argv[charstr].c_str(), "Link") == 0)
        {
            Link();
        }
        else if (strcmp(this->argv[charstr].c_str(), "exit") == 0)
        {
            exit(0);
        }
        else if (strcmp(this->argv[charstr].c_str(), "-QF") == 0)
        {
            charstr++;
            runfile();
        }
        else if (strcmp(this->argv[charstr].c_str(), "build") == 0)
        {
            charstr++;
            Compile();
            Link();
        }
        else if (strcmp(this->argv[charstr].c_str(), "run") == 0)
        {
            Run();
        }
        else if (strcmp(this->argv[charstr].c_str(), "add") == 0)
        {
            charstr++;

            string Cmd00 = "mkdir src/";
            string Cmd01 = this->argv[charstr];
            string Cmd02 = Cmd00.append(Cmd01);
            system(Cmd02.c_str());
            string Cmd03 = "mkdir includes/";
            string Cmd04 = this->argv[charstr];
            string Cmd05 = Cmd03.append(Cmd04);
            system(Cmd05.c_str());
            /*
        
        
        */
        }
        else if (strcmp(this->argv[charstr].c_str(), "real-update") == 0)
        {
            system("git clone https://github.com/QuariumStackHS/QSR-Tool ");
            Update();
        }
        else if (strcmp(this->argv[charstr].c_str(), "local-update") == 0)
        {
            Update();
            //system("g++ -c Cfg.hpp -o QSR/Private/Config.obj");
            //system("g++ QSR/Private/*.obj -o QSR.E");
        }
        else if (strcmp(this->argv[charstr].c_str(), "test") == 0)
        {
            Compile();
            Link();
            Run();
        }
        else if (strcmp(this->argv[charstr].c_str(), "compile") == 0)
        {
            Compile();
            //system()
        }
    }
    return 0;
}
Argser::Argser(int argc, char **argv)
{
    this->argc = argc;
    for (int i=0;i<argc;i++){
    string f=argv[i];
    this->argv.push_back(f);
    }

}

int main(int argc, char **argv)
{
    cout << "-------QSR compiler-------" << endl;

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