#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include<math.h>
#include <sstream>
using namespace std;
class Device
{
private:
    bool ip[32], subnet[32], dns[32];
    string name, domain;

    string decToBin(int n)
    {
        string t;
        while (n > 0)
        {
            if(n%2==1)t+='1';
            else t+='0';
            n = n / 2;
        }
        reverse(t.begin(),t.end());
        for(int k=8-t.length(); k>0; k--) t = '0' + t;
        return t;
    }

    string binToDec(string x)
    {
        int n=0;
        string k;
        for(int i=0; i<8; i++)
        {
            if(x[i]=='1')n+=pow(2,7-i);
        }
        ostringstream oss;
        oss  << n;
        k= oss.str();
        return k;
    }



    bool setName(string tmp)
    {
        name=tmp;
        return true;
    }
    bool setDomain(string tmp)
    {
        domain=tmp;
        return true;
    }

    bool setIp(char tmp[], bool echo)
    {

        int a[4];  //bloki adresu ip
        string t;
        sscanf(tmp, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
        if(echo) cout<<"$ Wprowadzono adres " <<a[0]<<"."<<a[1]<<"."<<a[2]<<"."<<a[3]<<endl;
        if(a[0]>255||a[0]<0) cout<<"# "<<a[0]<<" jest niepoprawnym blokiem adresu IP"<<endl;
        if(a[1]>255||a[1]<0) cout<<"# "<<a[1]<<" jest niepoprawnym blokiem adresu IP"<<endl;
        if(a[2]>255||a[2]<0) cout<<"# "<<a[2]<<" jest niepoprawnym blokiem adresu IP"<<endl;
        if(a[3]>255||a[3]<0) cout<<"# "<<a[3]<<" jest niepoprawnym blokiem adresu IP"<<endl;
        if(a[0]>255||a[1]>255||a[2]>255||a[3]>255||a[0]<0||a[1]<0||a[2]<0||a[3]<0)
        {
            cout<< "# Sprobuj ponownie. \n";
            return false;
        }
        else
        {
            t=decToBin(a[0])+decToBin(a[1])+decToBin(a[2])+decToBin(a[3]);
            for(int i=0; i<32; i++) if(t[i]=='0')ip[i]=0;
                else ip[i]=1;
            if(echo) cout<<"$ Zapisano.\n";
            return true;
        }

    }

    bool setSubnet(char tmp[], bool echo)
    {

        int a[4];
        string t;
        sscanf(tmp, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
        if(echo)cout<<"$ Wprowadzono maske " <<a[0]<<"."<<a[1]<<"."<<a[2]<<"."<<a[3];
        if(a[0]>255||a[1]>255||a[2]>255||a[3]>255||a[0]<0||a[1]<0||a[2]<0||a[3]<0)
        {
            cout<< "\n# Sprobuj ponownie. \n";
            return false;
        }
        else
        {
            t=decToBin(a[0])+decToBin(a[1])+decToBin(a[2])+decToBin(a[3]);
            if(echo) cout<<", czyli "<<t<<endl;
            bool zeroes = false;
            for(int i=0; i<32; i++)
            {
                if (t[i]=='0') zeroes=true;
                if (t[i]=='1' && zeroes==true)
                {
                    cout<< "# Sprobuj ponownie. \n";
                    return false;
                }
            }

            for(int i=0; i<32; i++) if(t[i]=='0')subnet[i]=0;
                else subnet[i]=1;
            if(echo)cout<<"$ Zapisano.\n";
            return true;
        }

    }

    bool setDns(char tmp[], bool echo)
    {

        int a[4];
        string t;
        sscanf(tmp, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
        if(echo)cout<<"$ Wprowadzono DNS " <<a[0]<<"."<<a[1]<<"."<<a[2]<<"."<<a[3]<<endl;
        if(a[0]>255||a[0]<0) cout<<"# "<<a[0]<<" jest niepoprawnym blokiem adresu DNS"<<endl;
        if(a[1]>255||a[1]<0) cout<<"# "<<a[1]<<" jest niepoprawnym blokiem adresu DNS"<<endl;
        if(a[2]>255||a[2]<0) cout<<"# "<<a[2]<<" jest niepoprawnym blokiem adresu DNS"<<endl;
        if(a[3]>255||a[3]<0) cout<<"# "<<a[3]<<" jest niepoprawnym blokiem adresu DNS"<<endl;
        if(a[0]>255||a[1]>255||a[2]>255||a[3]>255||a[0]<0||a[1]<0||a[2]<0||a[3]<0)
        {
            cout<< "# Sprobuj ponownie. \n";
            return false;
        }
        else
        {
            t=decToBin(a[0])+decToBin(a[1])+decToBin(a[2])+decToBin(a[3]);
            if(echo)cout<<t<<endl;
            for(int i=0; i<32; i++) if(t[i]=='0')dns[i]=0;
                else dns[i]=1;
            if(echo)cout<<"$ Zapisano.\n";
            return true;
        }

    }
public:
    Device()
    {

        char tmp[100];
        string temp;
        cout<<"> Wpisz nazwe: ";
        cin>>temp;
        setName(temp);
        cout<<"> Wpisz domene: ";
        cin>>temp;
        setDomain(temp);
        do
        {
            cout<<"> Wpisz adres IP: ";
            cin>>tmp;
        }
        while(!setIp(tmp,1));
        do
        {
            cout<<"> Wpisz maske podsieci: ";
            cin>>tmp;
        }
        while(!setSubnet(tmp,1));
        do
        {
            cout<<"> Wpisz adres domyslnego serwera DNS: ";
            cin>>tmp;
        }
        while(!setDns(tmp,1));
    }

    Device(int i) //dodawanie przykladowych
    {
        switch(i)
        {
        case 0:
            setName("Drukarka");
            setDomain("print.xxx");
            setIp("202.131.12.12",0);
            setSubnet("255.255.192.0",0);
            setDns("8.8.8.8",0);
            break;
        case 1:
            setName("Skaner");
            setDomain("scan.eu");
            setIp("202.131.12.94",0);
            setSubnet("255.255.192.0",0);
            setDns("1.1.1.1",0);

            break;
        default:
            setName("Toster");
            setDomain("crunchy.toasts.gov.eu");
            setIp("243.222.150.10",0);
            setSubnet("255.255.0.0",0);
            setDns("1.1.1.1",0);


            break;
        }
    }

    string getThisWeirdSubnetAndIpIdentifier()
    {
        string x;
        for(int i=0; i<32; i++) if(subnet[i]==1) if(ip[i]==0)x+='0';
                else x+='1';
            else break;
        return x;
    }

    string getName()
    {
        return name;
    }
    string getDomain()
    {
        return domain;
    }
    string getIp()
    {

        string a,b;
        for(int i=0; i<32; i++)
        {
            if(ip[i]==true)a+='1';
            else a+='0';
        }
        b=binToDec(a.substr(0,8))+'.'+binToDec(a.substr(8,8))+'.'+binToDec(a.substr(16,8))+'.'+binToDec(a.substr(24,8));
        return b;
    }
    string getSubnet()
    {

        string a,b;
        for(int i=0; i<32; i++)
        {
            if(subnet[i]==true)a+='1';
            else a+='0';
        }
        b=binToDec(a.substr(0,8))+'.'+binToDec(a.substr(8,8))+'.'+binToDec(a.substr(16,8))+'.'+binToDec(a.substr(24,8));
        return b;
    }

    string getDns()
    {

        string a,b;
        for(int i=0; i<32; i++)
        {
            if(dns[i]==true)a+='1';
            else a+='0';
        }
        b=binToDec(a.substr(0,8))+'.'+binToDec(a.substr(8,8))+'.'+binToDec(a.substr(16,8))+'.'+binToDec(a.substr(24,8));
        return b;
    }

    bool compare(char tmp[] )
    {
        int a[4];  //bloki adresu ip
        string t, ident;
        sscanf(tmp, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
        cout<<"$ Wprowadzono adres " <<a[0]<<"."<<a[1]<<"."<<a[2]<<"."<<a[3]<<endl;
        if(a[0]>255||a[0]<0) cout<<"# "<<a[0]<<" jest niepoprawnym blokiem adresu IP"<<endl;
        if(a[1]>255||a[1]<0) cout<<"# "<<a[1]<<" jest niepoprawnym blokiem adresu IP"<<endl;
        if(a[2]>255||a[2]<0) cout<<"# "<<a[2]<<" jest niepoprawnym blokiem adresu IP"<<endl;
        if(a[3]>255||a[3]<0) cout<<"# "<<a[3]<<" jest niepoprawnym blokiem adresu IP"<<endl;
        if(a[0]>255||a[1]>255||a[2]>255||a[3]>255||a[0]<0||a[1]<0||a[2]<0||a[3]<0)
        {
            cout<< "Sprobuj ponownie. \n\n";
            return false;
        }
        else
        {
            t=decToBin(a[0])+decToBin(a[1])+decToBin(a[2])+decToBin(a[3]);
            for(int i=0; i<32; i++) if(subnet[i]==1) if(t[i]=='0')ident+='0';
                    else ident +='1';
                else break;
            if (ident==getThisWeirdSubnetAndIpIdentifier()) cout<<"$ Adres jest w podsieci urzadzenia\n";
            else cout<<"$ Adres nie jest w podsieci urzadzenia\n";

        }
    }

};



class List
{
    vector <Device> tab;
public:
    void display()
    {
        for(int i = 0; i < tab.size(); i++)
        {
            cout<<"\n+++++            \n+  Urzadzenie nr "<<i<<endl
                <<"+  Nazwa: "<< tab[i].getName()<<endl
                <<"+  Domena: "<< tab[i].getDomain()<<endl
                <<"+  Adres IP: "<< tab[i].getIp()<<endl
                <<"+  Maska podsieci: "<< tab[i].getSubnet()<<endl
                <<"+  Adres DNS: "<< tab[i].getDns()<<endl<<"+++++ \n"<<endl;

        }
        cout<<endl;
    }
    void add()
    {
        Device temp;
        cout<<"$ Dodano\n";
        tab.push_back(temp);
    }

    void addFillers(int k)
    {
        Device temp(k);
        tab.push_back(temp);
    }

    void del()
    {
        cout<<endl<<"> Usuwamy urzadzenie nr: ";
        int u;
        cin>>u;
        if(u>=0&&u<tab.size())
        {
            tab.erase(tab.begin()+u);
            cout<<"Usunieto. \n\n";
        }
        else cout<<"# Nie ma takiego urzadzenia. \n\n";
    }


    int length()
    {
        return tab.size();
    }

    void compareDevices()
    {
        int a,b;
        cout<<"> Porownujemy urzadzenie nr: ";
        cin>>a;
        cout<<"> Z urzadzeniem nr:";
        cin>>b;
        if(a>=0&&a<tab.size()&&b>=0&&b<tab.size())
            if( tab[a].getThisWeirdSubnetAndIpIdentifier()==tab[b].getThisWeirdSubnetAndIpIdentifier()) cout<<"$ Urzadzenia sa w tej samej podsieci\n\n";
            else cout<<"$ Urzadzenia nie sa w tej samej podsieci\n\n";
        else cout<<"# Nie ma takiego urzadzenia. \n\n";
    }

    void compareIpToDevice()
    {
        int a;
        char tmp[100];

        cout<<"> Porownujemy urzadzenie nr: ";
        cin>>a;
        if(a<0||a>tab.size())
        {
            cout<<"# Nie ma takiego urzadzenia. \n\n";
            return;
        }
        do
        {
            cout<<"> Z adresem IP:";
            cin>>tmp;
        }
        while(!tab[a].compare(tmp));
    }
};




int main()
{

    List l;
    bool flag=true;
    while(true)
    {
        cout<< "=====================================================\n";
        cout<< "=     Liczba urzadzen: "<< l.length()<<endl;
        cout << "=  0. Dodaj urzadzenie" << endl;
        cout << "=  1. Usun urzadzenie" << endl;
        cout << "=  2. Wyswietl liste" << endl;
        cout << "=  3. Sprawdz czy urzadzenia sa w tej samej podsieci" << endl;
        cout << "=  4. Sprawdz czy IP jest w podsieci urzadzenia" << endl;
        if(l.length()==0)
            cout << "=  8. Laduj przykladowa liste" << endl;
        cout << "=  9. Zakoncz program" <<endl<<"=====================================================\n> ";

        char a;
        cin>>a;
        cout<<endl;
        switch(a)
        {
        case '0':
            l.add();
            break;
        case '1':
            l.del();
            break;
        case '2':
            l.display();
            break;
        case '3':
            l.compareDevices();
            break;
        case '4':
            l.compareIpToDevice();
            break;
        case '8':
            if(l.length()==0)
            {
                l.addFillers(0);
                l.addFillers(1);
                l.addFillers(2);
            }
            else
            {
                cout<< "\nDo widzenia.\n";
                return 0;
            }
            break;
        default:
            cout<< "\nDo widzenia.\n";
            return 0;
        }
    }
    return 0;
}
