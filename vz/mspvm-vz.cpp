#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void createVM();
void removeTemplate();

bool checkArgs(int total, string message = "Invalid Params")

int ac;
char ** av;
int main(int argc, char* argv[])
{
    ac = argc;
    av = argv;
    if(argc > 1)
    {
	setuid(0);
        if(strcmp(argv[1], "--createvm") == 0)
        {
            createVM();
        }
        else if(strcmp(argv[1], "--removetemplate") == 0)
        {
            undeployTemplates();
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

void createVM()
{
    system(string("whoami").c_str());
    if(checkArgs(14, "createvm: invalid params") !== false)
    {
        string command = "/usr/sbin/vzctl create  "+std::string(av[2])+" --ostemplate "+std::string(av[3])+" --config basic --hostname "+std::string(av[4])+";"
        "/usr/sbin/vzctl set  "+std::string(av[2])+" --diskspace "+std::string(av[5])+"g:"+std::string(av[5])+"g --save;"
        "/usr/sbin/vzctl set  "+std::string(av[2])+" --diskinodes "+std::string(av[6])+":"+std::string(av[6])+" --save;"
        "/usr/sbin/vzctl set  "+std::string(av[2])+"  --vmguarpages "+std::string(av[7])+"M --oomguarpages "+std::string(av[7])+"M --privvmpages "+std::string(av[7])+"M:"+std::string(av[8])+"M --swap "+std::string(av[9])+"M --save;"
        "/usr/sbin/vzctl set  "+std::string(av[2])+" --nameserver "+std::string(av[10])+"  --nameserver "+std::string(av[11])+" --save;"
        "/usr/sbin/vzctl set  "+std::string(av[2])+" --userpasswd root:"+std::string(av[12])+" --save;"
        "/usr/sbin/vzctl set  "+std::string(av[2])+" --onboot yes --save;"
        "/usr/sbin/vzctl set  "+std::string(av[2])+" --cpuunits "+std::string(av[13])+" --save;"
        "/usr/sbin/vzctl set  "+std::string(av[2])+" --cpulimit "+std::string(av[14])+" --cpus "+std::string(av[15])+" --save;"
        "modprobe iptables_module ipt_helper ipt_REDIRECT ipt_TCPMSS ipt_LOG ipt_TOS iptable_nat ipt_MASQUERADE ipt_multiport xt_multiport ipt_state xt_state ipt_limit xt_limit ipt_recent xt_connlimit ipt_owner xt_owner iptable_nat ipt_DNAT iptable_nat ipt_REDIRECT ipt_length ipt_tcpmss iptable_mangle ipt_tos iptable_filter ipt_helper ipt_tos ipt_ttl ipt_SAME ipt_REJECT ipt_helper ipt_owner ip_tables;"
        "/usr/sbin/vzctl set  "+std::string(av[2])+" --iptables ipt_REJECT --iptables ipt_tos --iptables ipt_TOS --iptables ipt_LOG --iptables ip_conntrack --iptables ipt_limit --iptables ipt_multiport --iptables iptable_filter --iptables iptable_mangle --iptables ipt_TCPMSS --iptables ipt_tcpmss --iptables ipt_ttl --iptables ipt_length --iptables ipt_state --iptables iptable_nat --iptables ip_nat_ftp --save;"
        "/usr/sbin/vzctl start "+std::string(av[2])+"; ";
        system(command.c_str());
        //return 1;            
    }
    //return 0;
}

void destroyVM()
{
    if(checkArgs(1, "destroyVM: invalid params") !== false)
    {
        string command = "sudo /usr/sbin/vzctl stop "+std::string(av[2])+";"
                        "sudo /usr/sbin/vzctl destroy "+std::string(av[2])+";"

        system(command.c_str());               
    }
}

void removeTemplate()
{
    if(checkArgs(1, "removeTemplate: invalid params") !== false)
    {
        string command = "/usr/sbin/vzpkg remove template " + std::string(av[2]);
        system(command.c_str());
    }
}

bool checkArgs(int total, string message = "Invalid Params")
{
    total = total + 2; //add two args to the total args as arg[0] and arg[1] are used in calling the function.

    if(ac >= total)
    {
        for(int i=2; i<(total-2); i++)
        {
            if(av[i] == "")
            {
                cout << message <<endl;
                return false;
            }
        }
        return true;
    }
    cout << 'not enough parguments' <<endl;
    return false;
}
