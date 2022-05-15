#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
ifstream f("date.in");

int noduri, tranzitii, stare1, stare2, stare_initiala, numar_stari_finale, stare_finala, stari_finale[1000], numar_inputuri, litera;
char matrice_adiacenta[1000][1000], caracter;
string input;
queue <int> coada;

int verificare_stare_finala(int stare)
{
    for(int i=0; i<numar_stari_finale; i++)
        if(stare==stari_finale[i])
            return 1;
    return 0;
}

int df(int stare_curenta, string input, int &litera)
{
    //adaug mereu starea curenta in coada pentru a putea construi traseul final (in caz ca exista)
    coada.push(stare_curenta);
    //verific daca am ajuns la o stare finala si am parcurs tot input-ul
    //in caz afirmativ returnez 1, altfel continui algoritmul
    if(verificare_stare_finala(stare_curenta)==1 && input[litera]==NULL)
        return 1;
    for(int i=0; i<noduri; i++)
        //verific daca exista o tranzitie cu litera respectiva de la starea curenta la starea i
        if(matrice_adiacenta[stare_curenta][i]==input[litera])
        {
            //trec la urmatoarea litera din input
            litera++;
            //actualizez starea curenta cu starea i
            stare_curenta=i;
            //parcurg recursiv restul automatului
            return df(stare_curenta, input, litera);
        }
    //returnez 0 daca nu exista un traseu care sa satisfaca input-ul respectiv
    return 0;
}

void afisare()
{
    //afisez traseul
    cout<<"DA"<<'\n'<<"Traseu: ";
    while(!coada.empty())
    {
        cout<<coada.front()<<" ";
        coada.pop();
    }
}
int main()
{
    f>>noduri>>tranzitii;
    for(int i=0; i<tranzitii; i++)
    {
        f>>stare1>>stare2>>caracter;
        matrice_adiacenta[stare1][stare2]=caracter;
    }
    f>>stare_initiala;
    f>>numar_stari_finale;
    for(int i=0; i<numar_stari_finale; i++)
    {
        f>>stare_finala;
        stari_finale[i]=stare_finala;
    }
    f>>numar_inputuri;
    for(int i=0; i<numar_inputuri; i++)
    {
        f>>input;
        litera=0;
        if(df(stare_initiala, input, litera)==1)
            afisare();
        else
            cout<<"NU";
        cout<<'\n';
    }
    return 0;
}
