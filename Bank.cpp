#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Bignum    //Klasa do obslugi liczb trzydziestocyfrowych
{
private:
    int bignum[30]; //cyfry
    void reshuffle()    //przenoszenie nadwyzek ponad 10 do nastepnej cyfry
    {
        for(int i=29; i>0; i--)
            if(bignum[i]>9)
            {
                bignum[i-1]+=(bignum[i] - bignum[i]%10)/10;
                bignum[i]%=10;
            }
    }

public:
    Bignum(string k)
    {
        bignum[24]=2;
        bignum[25]=5;
        bignum[26]=2;
        bignum[27]=1;
        bignum[28]=k[0]-48;
        bignum[29]=k[1]-48;
        for(int i=2; i<26; i++)
            bignum[i-2]=k[i]-48; //-48 by zamienic cyfre ascii na cyfre int
    }

    int remainder97()
    {
        for(int i=0; i<28; i++) //odejmuje 970000...0000 tyle razy, ile sie da, by zmniejszyc liczbe cyfr naszej liczby, nie zmieniajac reszty z dzielenia
        {
            bignum[i+2]+=bignum[i]*3;   //97 = 100 - 3
            bignum[i]=0;
            reshuffle();
            if(bignum[i]>0)             //gdyby trzeba bylo odjac 97 dziesiec razy, aktualnie obslugiwana cyfra moglaby wrocic
            {
                bignum[i+2]+=bignum[i]*3;
                bignum[i]=0;
                reshuffle();
            }
        }
        if(bignum[28]==9&&bignum[29]>6) //mogloby zostac 97, 98, 99, a to nie reszta
        {
            bignum[28]=0;
            bignum[29]-=7;
        }
        return bignum[28]*10+bignum[29];
    }
};

class Account
{
private:
    string number;
public:
    Account(string n) : number(n) {} //najprostszy mozliwy konstruktor
    string getNumber() const
    {
        return number;
    }
};

class List
{
    vector <Account> tab;
public:
    void display() const
    {
        for(unsigned int i = 0; i < tab.size(); i++)
            cout<<i<<". "<< tab[i].getNumber()<<endl;
    }
    void add()
    {
        string k;
        while(true)
        {
            cout<<"Wpisz nr konta: ";
            cin>>k;

            if(k.length()!=26)
            {
                cout<<"Zla dlugosc.\n";
                continue;
            }

            for(int i=0; i<=25; i++)
                if(k[i]<48||k[i]>57) //czy same cyfry?
                {
                    cout<<k[i]<<" nie jest cyfra.\n";
                    continue;
                }


            Bignum *b = new Bignum(k);
            int rem=b->remainder97();//jaka jest reszta z dzielenia przez 97 wynikajaca z algorytmu?

            delete b;

            if(rem!=1)
            {
                cout<<"Zle cyfry kontrolne.\n";
                continue;
            }

            int bankChecksum=(k[2]-48)*3+(k[3]-48)*9+(k[4]-48)*7+(k[5]-48)*1+(k[6]-48)*3+(k[7]-48)*9+(k[8]-48)*7+(k[9]-48)*1;   //sprawdzam identyfikator banku; -48 by zamienic cyfre ascii na cyfre int
            bankChecksum%=10;

            if (bankChecksum%10!=0)
            {
                cout<<"Zla cyfra kontrolna numeru banku.\n";
                continue;
            }

            break;
        }


        Account temp(k);
        cout<<"$ Dodano\n";
        tab.push_back(temp);
    }

    void addFillers(string k)
    {
        Account temp(k);
        tab.push_back(temp);
    }


    void del()
    {
        cout<<endl<<"> Usuwamy konto nr: ";
        unsigned int u;
        cin>>u;
        if(u<tab.size())
        {
            tab.erase(tab.begin()+u);
            cout<<"Usunieto. \n\n";
        }
        else cout<<"# Nie ma takiego konta. \n\n";
    }

    int length() const
    {
        return tab.size();
    }

    void displaySome()
    {
        string k;
        int n=0;
        cout<<"Wypisac numery z banku: ";
        cin>>k;

        for(unsigned int i = 0; i < tab.size(); i++)
            if(tab[i].getNumber().substr(2,8)==k)
            {
                n++;
                cout<<i<<". "<< tab[i].getNumber()<<endl;
            }
        if(n==0) cout<<"Nie ma takich numerow kont.\n";
    }

};


int main()
{

    List l;
    while(true)
    {
        cout<< "=====================================================\n";
        cout<< "=     Liczba kont: "<< l.length()<<endl;
        cout << "=  0. Dodaj konto" << endl;
        cout << "=  1. Usun konto" << endl;
        cout << "=  2. Wyswietl liste" << endl;
        cout << "=  3. Wypisz konta z danego banku" << endl;
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
            l.displaySome();
            break;
        case '8':
            if(l.length()==0)
            {
                l.addFillers("14249000051153728835405276");
                l.addFillers("11249000058618538916431434");
                l.addFillers("81249000055884852474581324");
                l.addFillers("44249000059528646686291945");
                l.addFillers("17249000056776134369682299");
                l.addFillers("32114000007182002739165812");
                l.addFillers("28249000058962745083490588");
                l.addFillers("66249000059972888859689846");
                l.addFillers("33114000009101200854290964");
                l.addFillers("68114000000342027689508149");
                l.addFillers("39114000005950788769113519");

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
