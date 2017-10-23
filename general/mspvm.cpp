#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scripts.hpp"

using namespace std;

//string exec(string command);
string restartService();
string runScript();

int ac;
char ** av;
int main(int argc, char* argv[])
{
    ac = argc;
    av = argv;
    if(argc > 1)
    {
	    setuid(0);
        if(strcmp(argv[1], "--restartservice") == 0)
        {
            cout << restartService() <<endl;
        }
        else if(strcmp(argv[1], "--runscript") == 0)
        {
            cout << runScript() <<endl;
        }
        else
        {
            cout << "function not found: " << argv[1] <<endl;
        }

    }
    else
    {
        cout << "No Commands." << endl;
    }
    return 0;

}

string restartService()
{
    if(ac >= 3 && av[2] != "")
    {
        string command = "/sbin/service " + std::string(av[2]) +" restart";
        system(command.c_str());
        return "done";
    }
    return "No Service given";
}

string runScript()
{
    //todo implement lock file. (transfer most of php functions in AdminToolsController here.)
    if(ac >= 3 && av[2] != "")
    {
        string command = "chmod +x " + std::string(av[2]) +"; " + std::string(av[2]);
        system(command.c_str());
        return "done";
    }
    return "Invalid arguments";
}

/*
string exec(string command)
{
    const char* cmd = command.c_str();
    FILE *pipe = popen(cmd, "r");
    if (!pipe) {
        string ret = "~mspvm-error~ Error opening pipe";
        return ret;
    }
    char* buffer = new char[512];

    string result;
    while ((fgets(buffer, sizeof(buffer), pipe)) != NULL) {
        result += buffer;
    }
    
    int retCode = pclose(pipe);
    if (retCode != 0) {
        // Program ends with error, and result has the error message
        string ret =  "~mspvm-error~ retCode: " + retCode +std::string("\nMessage") + result;
        return ret;
    } else {
        // Program ends normally, prints: streams_stream_0_nb_read_frames="xxx"
        return result;
    }

    delete buffer; // free memory
    return "Ouch!!";
}
*/