#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iomanip>

using namespace std;

struct Tsorozat {
int ev;
int honap;
int nap;
string s_nev;
int evad;
int epizod;
int hossz;
int megnezve;
};

string hetnapja (int ev, int ho, int nap)
{
    string napok[7] = {"v", "h", "k", "sze", "cs", "p", "szo"};
    int honapok[12] = {0,3,2,5,0,3,5,1,4,6,2,4};
    if (ho < 3)
        ev--;
    return napok[(ev + ev / 4 - ev / 100 + ev / 400 + honapok[ho-1]+ nap) % 7];
}


int main()
{
    Tsorozat sorozat[400];
    int szaml = 0;
    string seged;
    ifstream  be ("lista.txt");
    while (!be.eof())
    {
        getline(be,seged);

        if (seged == "NI")
        {
            sorozat[szaml].ev = 9999;
            sorozat[szaml].honap = 0;
            sorozat[szaml].nap = 0;
        }
        else
            sscanf(seged.c_str(),"%d.%d.%d",&(sorozat[szaml].ev),&(sorozat[szaml].honap),&(sorozat[szaml].nap));

        getline(be,sorozat[szaml].s_nev);
        getline(be,seged);
        sscanf(seged.c_str(),"%dx%d",&(sorozat[szaml].evad),&(sorozat[szaml].epizod));
        getline(be,seged);
        sscanf(seged.c_str(),"%d",&(sorozat[szaml].hossz));
        getline(be,seged);
        sscanf(seged.c_str(),"%d",&(sorozat[szaml].megnezve));
        szaml++;
    }


    cout<<"2. feladat"<<endl;

    int i = 0;
    int szaml_2 = 0;

    for (i=0;i<szaml;i++)
    {
        if (sorozat[i].ev != 0)
            szaml_2++;
    }
    cout<<"A listaban "<<szaml_2<<" db vetitesi datummal rendelkezo epizod van."<<endl<<endl;

    cout<<"3. feladat"<<endl;

    szaml_2 = 0;
    for (i=0;i<szaml;i++)
    {
        if (sorozat[i].megnezve == 1)
        {
            szaml_2++;
        }
    }
    float szazalek = szaml_2;
    szazalek /= szaml;

    cout<<"A listaban levo epizodok "<<fixed<<setprecision(2)<<szazalek*100<<" %-at latta."<<endl<<endl;


    cout<<"4. feladat"<<endl;

    szaml_2 = 0;
    for (i=0;i<szaml;i++)
    {
        if (sorozat[i].megnezve != 0)
        {
            szaml_2 += sorozat[i].hossz;
        }
    }

    int p = szaml_2 % 60;
    int seged_2 = szaml_2/60;
    int o = seged_2 % 24;
    int n = seged_2 / 24;

    cout<<"Sorozatnezessel "<<n<<" napot "<<o<<" orat es "<<p<<" percet toltott."<<endl<<endl;

    cout<<"5. feladat"<<endl;
    int ev;
    int ho;
    int nap;
    cout<<"Adjon meg egy datumot! Datum= ";
    scanf("%d.%d.%d",&ev,&ho,&nap);
    //cout<<ev<<" "<<ho<<" "<<nap;


    for (i=0;i<szaml;i++)
    {
        if ((sorozat[i].megnezve == 0) && (sorozat[i].ev*10000+sorozat[i].honap*100+sorozat[i].nap <= ev*10000+ho*100+nap))
        {
            cout<<sorozat[i].evad<<"x"<<sorozat[i].epizod<<"\t"<<sorozat[i].s_nev<<endl;
        }
    }


    //6. feladat

    //cout<< hetnapja(2020,12,17)<<endl;

    cout<<endl<<"7. feladat"<<endl;

    string benap;

    cout<<"Adj meg egy napot";
    cin>>benap;
    string tomb[500];
    int tomszaml = 0;
    int j;

    for (i=0;i<szaml;i++)
    {
        if (hetnapja(sorozat[i].ev,sorozat[i].honap,sorozat[i].nap) == benap)
        {
            int volte = 0;
            for (j=0;j<tomszaml;j++)
            {
                if (tomb[j]==sorozat[i].s_nev)
                    volte = 1;
            }
            if (volte==0)
            {
                cout<<sorozat[i].s_nev<<endl;
                tomb[tomszaml] = sorozat[i].s_nev;
                tomszaml++;
            }
        }
    }
    if (tomszaml == 0)
        cout<<"Nem volt a napon semmi"<<endl;

    //7. feladat
    int vido = sorozat[0].hossz;
    int vszaml = 1;
    string aktualisnev = sorozat[0].s_nev;

    for (i=1;i<szaml;i++)
    {
        if(aktualisnev == sorozat[i].s_nev)
        {
            vido += sorozat[i].hossz;
            vszaml++;
        }
        else
        {
            cout<<aktualisnev<<" "<<vido<<" "<<vszaml<<endl;
            aktualisnev= sorozat[i].s_nev;
            vido = sorozat[i].hossz;
            vszaml = 1;
        }
    }
    cout<<aktualisnev<<" "<<vido<<" "<<vszaml<<endl;

    return 0;
}
