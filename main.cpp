///Ksiazka adresowa z uzytkownikami
#include <iostream>
#include <list>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
struct Uzytkownik
{
    int id=0;
    string login = "", haslo = "";
};
struct Adresat
{
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};
bool porownaj(Adresat i, Adresat j)
{
    return ( i.id < j.id );
}
void rejestracja( vector <Uzytkownik> &uzytkownicy);
void logowanie ( vector <Uzytkownik> &uzytkownicy);
void zapisywanieUzytkownikowDoPliku( vector <Uzytkownik> &uzytkownicy);
void automatyczneWczytyawnieUzytkownikow( vector <Uzytkownik> &uzytkownicy);
void panelUzytkownika(string login, vector <Uzytkownik> &uzytkownicy);
void menuKsiazkiAdresowej(string login, vector <Uzytkownik> &uzytkownicy);
void wprowadzanieDanychAdresata (vector <Adresat> &adresaci);
void sprawdzaniePoImieniu ( vector <Adresat> &adresaci);
void sprawdzaniePoNazwisku (vector <Adresat> &adresaci);
void wypisanieAdresatow ( vector <Adresat> &adresaci);
void zapisywanieAdresatowDoPliku(vector <Adresat> &adresaci, string login);
void automatyczneWczytyawnieAdresatow(vector <Adresat> &adresaci, string login);
void usuwanieAdresata(vector <Adresat> &adresaci);
void zmianaDanychAdresata(vector <Adresat> &adresaci);
void zmianaHaslaUzytkownika (string login, vector <Uzytkownik> &uzytkownicy);
string zamianaNaString(int num)
{
    string str = to_string(num);
    return str;
};
int zamianaStringNaInt(string str_num)
{
    int num = stoi(str_num);
    return num;
};

int main()
{
    vector <Uzytkownik> uzytkownicy;
    automatyczneWczytyawnieUzytkownikow(uzytkownicy);
    char wybor;
    while(1)
    {

        system("cls");
        cout << "Podaj cyfre odpowiadajaca wybranej opcji" << endl;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "3. Zakoncz" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            rejestracja(uzytkownicy);
        }
        else if (wybor == '2' )
        {
            logowanie (uzytkownicy);
        }

        else if (wybor == '3' )
        {
            exit(0);
        }
    }


    return 0;
}
void zapisywanieUzytkownikowDoPliku( vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    string daneUzytkownika="";
    // fstream ksiazkaAdresowa;
    ofstream listaUzytkownikow;
    if (uzytkownicy.size()==0)
    {
        /* listaUzytkownikow.open("listaUzytkownikow.txt",ios::out | ios::trunc);
         listaUzytkownikow.close();*/
    }
    else if(uzytkownicy.size()>0)
    {
        listaUzytkownikow.open("listaUzytkownikow.txt",ios::out | ios::trunc);
        listaUzytkownikow.close();
        listaUzytkownikow.open("listaUzytkownikow.txt",ios::out| ios::app);
        for(int i=0; i<=uzytkownicy.size()-1; i++)
        {


            daneUzytkownika+=zamianaNaString(uzytkownicy[i].id);
            daneUzytkownika+="|";
            daneUzytkownika+=uzytkownicy[i].login;
            daneUzytkownika+="|";
            daneUzytkownika+=uzytkownicy[i].haslo;
            daneUzytkownika+="|";
            listaUzytkownikow << daneUzytkownika << endl;
            daneUzytkownika="";


        }

    }
    listaUzytkownikow.close();
}
void automatyczneWczytyawnieUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    int liczebnikDlaWprowadzaniaTypuDanychUzytkownika=1;
    string linia, skladowaDanychUzytownika="";
    fstream listaUzytkownikow;
    listaUzytkownikow.open ("listaUzytkownikow.txt",ios::in);
    if (listaUzytkownikow.good()== true)
    {

        while (getline(listaUzytkownikow, linia))
        {
            for( int i=0; i<=linia.size(); i++)
            {
                if(linia[i]!='|' & i!=linia.size())
                {
                    skladowaDanychUzytownika+=linia[i];

                }
                else if (linia[i]=='|' && liczebnikDlaWprowadzaniaTypuDanychUzytkownika==1)
                {
                    uzytkownik.id=zamianaStringNaInt(skladowaDanychUzytownika);
                    skladowaDanychUzytownika="";
                    liczebnikDlaWprowadzaniaTypuDanychUzytkownika=2;
                }
                else if (linia[i]=='|' & liczebnikDlaWprowadzaniaTypuDanychUzytkownika==2)
                {
                    uzytkownik.login=skladowaDanychUzytownika;
                    skladowaDanychUzytownika="";
                    liczebnikDlaWprowadzaniaTypuDanychUzytkownika=3;
                }
                else if (linia[i]=='|' & liczebnikDlaWprowadzaniaTypuDanychUzytkownika==3)
                {
                    uzytkownik.haslo=skladowaDanychUzytownika;
                    skladowaDanychUzytownika="";
                    liczebnikDlaWprowadzaniaTypuDanychUzytkownika=1;
                    uzytkownicy.push_back(uzytkownik);
                }

            }
        }
    }
}
void panelUzytkownika(string login, vector <Uzytkownik> &uzytkownicy)
{
    char wybor;
  while(1)
    {

        system("cls");
        cout << "Podaj cyfre odpowiadajaca wybranej opcji" << endl;
        cout << "1. Ksiazka Adresowa" << endl;
        cout << "2. Zmiana Hasla" << endl;
        cout << "3. Zakoncz" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            menuKsiazkiAdresowej(login, uzytkownicy);
        }
        else if (wybor == '2' )
        {
            zmianaHaslaUzytkownika(login, uzytkownicy);
            zapisywanieUzytkownikowDoPliku(uzytkownicy);
        }

        else if (wybor == '3' )
        {
            main();
        }
    }
}
void rejestracja( vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    string sprawdzenieHasla, haslo;
    int PorownanieHasel=0;
    cout<<"Podaj login: ";
    cin >> uzytkownik.login;
    cout << "Podaj haslo: ";
    cin >> haslo;
    cout << "Podaj ponownie haslo: ";
    cin >> sprawdzenieHasla;
    while(PorownanieHasel==0)
    {
        if(haslo==sprawdzenieHasla)
        {
            uzytkownik.haslo=haslo;
            PorownanieHasel=1;
        }
        else
        {
            cout << "Hasla niepoprawne"<<endl;
            cout << "Podaj ponownie haslo: ";
            cin >> sprawdzenieHasla;
        }
    }
    if (uzytkownicy.size()==0 || (uzytkownicy.size()==1 && uzytkownicy[0].id>1) )
    {
        uzytkownik.id=1;
    }
    else if(uzytkownicy.size()>=1)
    {
        uzytkownik.id=uzytkownicy[uzytkownicy.size()-1].id+1;

    }

    uzytkownicy.push_back(uzytkownik);

    zapisywanieUzytkownikowDoPliku(uzytkownicy);
}
void logowanie ( vector <Uzytkownik> &uzytkownicy)
{
    string login, haslo;
    int indeksUzytkownika=0, proba=0;

    do
    {
        cout<<"Podaj login: ";
        cin >> login;
        cout << "Podaj haslo: ";
        cin >> haslo;
        if(uzytkownicy.size()>0)
        {
            for(int i=0; i<uzytkownicy.size(); i++)
            {
                if(uzytkownicy[i].login==login)
                {
                    indeksUzytkownika=i+1;
                }
            }
        }
        if (indeksUzytkownika==0)
        {
            cout<<"Bledne dane"<<endl;
            proba+=1;
        }
        else
        {
            if(uzytkownicy[indeksUzytkownika-1].login==login && uzytkownicy[indeksUzytkownika-1].haslo==haslo)
            {
                panelUzytkownika(login,uzytkownicy);
            }
            else
            {
                cout<<"Bledne dane"<<endl;
                proba+=1;
            }
        }

    }
    while(proba!=3);


}


void menuKsiazkiAdresowej(string login, vector <Uzytkownik> &uzytkownicy)
{
    char wybor;
    vector <Adresat> adresaci;
    string daneAdresoweZnajomego, skladowaDanychAdresowychZnajomego;


    automatyczneWczytyawnieAdresatow(adresaci, login);

    while(1)
    {
        system("cls");
        cout << "Podaj cyfre odpowiadajaca wybranej opcji" << endl;
        cout << "1. Dodaj Adresata" << endl;
        cout << "2. Szukaj Adresatow po imieniu" << endl;
        cout << "3. Szukaj Adresatow po nazwisku" << endl;
        cout << "4. Wypisz dane wszystkich Adresatow" << endl;
        cout << "5. Usun wybranego Adresata" << endl;
        cout << "6. Edytuj Adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            wprowadzanieDanychAdresata(adresaci);
            zapisywanieAdresatowDoPliku(adresaci, login);

        }
        else if (wybor == '2' )
        {
            sprawdzaniePoImieniu (adresaci);
        }
        else if (wybor == '3' )
        {
            sprawdzaniePoNazwisku (adresaci);
        }
        else if (wybor == '4' )
        {
            wypisanieAdresatow(adresaci);
        }
        else if (wybor == '5' )
        {
            usuwanieAdresata(adresaci);
            zapisywanieAdresatowDoPliku(adresaci, login);
        }
        else if (wybor == '6' )
        {
            zmianaDanychAdresata(adresaci);
            zapisywanieAdresatowDoPliku(adresaci, login);
        }

        else if (wybor == '9' )
        {
            zapisywanieAdresatowDoPliku(adresaci, login);
            main();
        }
    }
}
void wprowadzanieDanychAdresata (vector <Adresat> &adresaci)
{
    int liczbaSprawdzajacaDojscieDoKoncaPetli=0;
    Adresat adresat;
    cout << "Podaj imie Adresata: ";
    cin >> adresat.imie;
    cout << "Podaj nazwisko Adresata: ";
    cin >> adresat.nazwisko;
    cout << "Podaj numer Telefonu Adresata: ";
    cin >> adresat.numerTelefonu;
    cout << "Podaj email Adresata: ";
    cin >> adresat.email;
    cout << "Podaj adres Adresata: ";
    cin >> adresat.adres;
    if (adresaci.size()==0 || (adresaci.size()==1 && adresaci[0].id>1) )
    {
        adresat.id=1;
    }
    else if(adresaci.size()>=1)
    {
        adresat.id=adresaci[adresaci.size()-1].id+1;
        /*for(int i=0; i<=adresaci.size()-1; i++)
        {
            if(adresaci[i].id!=adresaci[i+1].id)
            {
                adresat.id=adresaci[i].id+1;
            }
            else
            {
                liczbaSprawdzajacaDojscieDoKoncaPetli++;
            }
            if(liczbaSprawdzajacaDojscieDoKoncaPetli==adresaci.size())
            {
                adresat.id=adresaci[liczbaSprawdzajacaDojscieDoKoncaPetli+1].id+1;
            }
        }*/
    }


    adresaci.push_back(adresat);
    sort(adresaci.begin(), adresaci.end(), porownaj);
}
void sprawdzaniePoImieniu (vector <Adresat> &adresaci)
{
    string imie;
    cout << "Podaj imie znajomego: ";
    cin >> imie;
    for (int i=0; i< adresaci.size(); i++)
    {
        if ( adresaci[i].imie == imie)
        {
            cout << "ID Adresata: " << adresaci[i].id << endl;
            cout << "Imie Adresata: " <<adresaci[i].imie << endl;
            cout << "nazwisko Adresata: " <<adresaci[i].nazwisko << endl;
            cout << "Numer Telefonu Adresata: " <<adresaci[i].numerTelefonu << endl;
            cout << "Adres Adresata: " <<adresaci[i].adres << endl;
            cout << "E-mail Adresata: " <<adresaci[i].email << endl;
            cout << endl << endl;

        }
    }
}
void sprawdzaniePoNazwisku (vector <Adresat> &adresaci)
{
    string nazwisko;
    cout << "Podaj nazwisko znajomego: ";
    cin >> nazwisko;
    for (int i=0; i< adresaci.size(); i++)
    {
        if ( adresaci[i].nazwisko == nazwisko)
        {
            cout << "ID Adresata: " << adresaci[i].id << endl;
            cout << "Imie Adresata: " <<adresaci[i].imie << endl;
            cout << "nazwisko Adresata: " <<adresaci[i].nazwisko << endl;
            cout << "Numer Telefonu Adresata: " <<adresaci[i].numerTelefonu << endl;
            cout << "Adres Adresata: " <<adresaci[i].adres << endl;
            cout << "E-mail Adresata: " <<adresaci[i].email << endl;
            cout << endl << endl;

        }
    }
}
void wypisanieAdresatow (vector <Adresat> &adresaci)
{

    for (int i=0; i< adresaci.size(); i++)
    {
        cout << "ID Adresata: " << adresaci[i].id << endl;
        cout << "Imie Adresata: " <<adresaci[i].imie << endl;
        cout << "nazwisko Adresata: " <<adresaci[i].nazwisko << endl;
        cout << "Numer Telefonu Adresata: " <<adresaci[i].numerTelefonu << endl;
        cout << "Adres Adresata: " <<adresaci[i].adres << endl;
        cout << "E-mail Adresata: " <<adresaci[i].email << endl;
        cout << endl << endl;
    }
    system("PAUSE");
}
void zapisywanieAdresatowDoPliku(vector <Adresat> &adresaci, string login)
{
    string nazwaPliku="";
    Adresat adresat;
    string daneAdresata="";
    // fstream ksiazkaAdresowa;
    nazwaPliku+="KsiazkaAdresowa";
    nazwaPliku+=login;
    nazwaPliku+=".txt";
    ofstream ksiazkaAdresowa;
    if (adresaci.size()==0)
    {
        ksiazkaAdresowa.open(nazwaPliku,ios::out | ios::trunc);
        ksiazkaAdresowa.close();
    }
    else if(adresaci.size()>0)
    {
        ksiazkaAdresowa.open(nazwaPliku,ios::out | ios::trunc);
        ksiazkaAdresowa.close();
        ksiazkaAdresowa.open(nazwaPliku,ios::out| ios::app);
        for(int i=0; i<=adresaci.size()-1; i++)
        {
            daneAdresata+=zamianaNaString(adresaci[i].id);
            daneAdresata+="|";
            daneAdresata+=adresaci[i].imie;
            daneAdresata+="|";
            daneAdresata+=adresaci[i].nazwisko;
            daneAdresata+="|";
            daneAdresata+=adresaci[i].numerTelefonu;
            daneAdresata+="|";
            daneAdresata+=adresaci[i].email;
            daneAdresata+="|";
            daneAdresata+=adresaci[i].adres;
            daneAdresata+="|";
            ksiazkaAdresowa << daneAdresata << endl;
            daneAdresata="";

        }
    }
    ksiazkaAdresowa.close();
}
void automatyczneWczytyawnieAdresatow(vector <Adresat> &adresaci, string login)
{
    Adresat adresat;
    int liczebnikDlaWprowadzaniaTypuDanychAdresata=1;
    string linia, skladowaDanychAdresta="", nazwaPliku="";
    nazwaPliku+="KsiazkaAdresowa";
    nazwaPliku+=login;
    nazwaPliku+=".txt";
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open (nazwaPliku,ios::in);
    if (ksiazkaAdresowa.good()== true)
    {

        while (getline(ksiazkaAdresowa, linia))
        {
            for( int i=0; i<=linia.size(); i++)
            {
                if(linia[i]!='|' & i!=linia.size())
                {
                    skladowaDanychAdresta+=linia[i];

                }
                else if (linia[i]=='|' && liczebnikDlaWprowadzaniaTypuDanychAdresata==1)
                {
                    adresat.id=zamianaStringNaInt(skladowaDanychAdresta);
                    skladowaDanychAdresta="";
                    liczebnikDlaWprowadzaniaTypuDanychAdresata=2;
                }
                else if (linia[i]=='|' & liczebnikDlaWprowadzaniaTypuDanychAdresata==2)
                {
                    adresat.imie=skladowaDanychAdresta;
                    skladowaDanychAdresta="";
                    liczebnikDlaWprowadzaniaTypuDanychAdresata=3;
                }
                else if (linia[i]=='|' & liczebnikDlaWprowadzaniaTypuDanychAdresata==3)
                {
                    adresat.nazwisko=skladowaDanychAdresta;
                    skladowaDanychAdresta="";
                    liczebnikDlaWprowadzaniaTypuDanychAdresata=4;
                }
                else if (linia[i]=='|' & liczebnikDlaWprowadzaniaTypuDanychAdresata==4)
                {
                    adresat.numerTelefonu=skladowaDanychAdresta;
                    skladowaDanychAdresta="";
                    liczebnikDlaWprowadzaniaTypuDanychAdresata=5;
                }
                else if (linia[i]=='|' & liczebnikDlaWprowadzaniaTypuDanychAdresata==5)
                {
                    adresat.email=skladowaDanychAdresta;
                    skladowaDanychAdresta="";
                    liczebnikDlaWprowadzaniaTypuDanychAdresata=6;
                }
                else if (linia[i]=='|' & liczebnikDlaWprowadzaniaTypuDanychAdresata==6)
                {
                    adresat.adres=skladowaDanychAdresta;
                    skladowaDanychAdresta="";
                    liczebnikDlaWprowadzaniaTypuDanychAdresata=1;
                    adresaci.push_back(adresat);
                }

            }
        }
    }

    ksiazkaAdresowa.close();

}
void usuwanieAdresata(vector <Adresat> &adresaci)
{
    int idDoUsunieciaAdresata, liczbaPorzadkowaDlaUsunieciaAdresata=0;
    char potwierdzenie;
    cout<< "Podaj numer ID Adresata do usuniecia: ";
    cin >> idDoUsunieciaAdresata;
    cout <<"Czy na pewno chcesz usunac adresata?('t' na tak, 'n' na nie): ";
    cin >> potwierdzenie;
    if (potwierdzenie=='t')
    {
        if (adresaci.size()==1)
        {
            adresaci.clear();
        }
        else if(adresaci.size()>1)
            for(int i=0; i<=adresaci.size(); i++)
            {
                if (adresaci[i].id==idDoUsunieciaAdresata)
                {
                    liczbaPorzadkowaDlaUsunieciaAdresata=i;
                    adresaci.erase(adresaci.begin()+liczbaPorzadkowaDlaUsunieciaAdresata);
                }
            }

        else
        {
            adresaci.erase(adresaci.begin()+liczbaPorzadkowaDlaUsunieciaAdresata);
        }
        // sort(adresaci.id.begin(), adresaci.id.end());
    }
}
void zmianaDanychAdresata(vector <Adresat> &adresaci)
{
    int idDoZmianyDanychAdresata, liczbaPorzadkowaDlaZmianyDanychAdresata, zmiennaOtwierajacaMenu=0;
    char wybor;
    cout<< "Podaj numer ID Adresata do zmiany danych: ";
    cin >> idDoZmianyDanychAdresata;
    for(int i=0; i<adresaci.size(); i++)
    {
        if ( adresaci[i].id==idDoZmianyDanychAdresata)
        {
            liczbaPorzadkowaDlaZmianyDanychAdresata=i;
            zmiennaOtwierajacaMenu=1;
            zmiennaOtwierajacaMenu=1;
        }
    }
    if (zmiennaOtwierajacaMenu!=0)
        while(1)
        {
            system("cls");
            cout << "Podaj cyfre odpowiadajaca wybranej opcji" << endl;
            cout << "1. Zmien imie" << endl;
            cout << "2. Zmien nazwisko" << endl;
            cout << "3. Zmien numer telefonu" << endl;
            cout << "4. Zmien email" << endl;
            cout << "5. Zmien adres" << endl;
            cout << "9. Powrot do menu " << endl;
            cin >> wybor;

            if (wybor == '1')
            {
                cout<<"Podaj nowe imie: ";
                cin >> adresaci[liczbaPorzadkowaDlaZmianyDanychAdresata].imie;
                cout <<"zmienione!"<< endl;
                system("PAUSE");
            }
            else if (wybor == '2' )
            {
                cout<<"Podaj nowe nazwisko: ";
                cin >> adresaci[liczbaPorzadkowaDlaZmianyDanychAdresata].nazwisko;
                cout <<"zmienione!"<< endl;
                system("PAUSE");
            }
            else if (wybor == '3' )
            {
                cout<<"Podaj nowy numer telefonu: ";
                cin >>adresaci[liczbaPorzadkowaDlaZmianyDanychAdresata].numerTelefonu;
                cout <<"zmienione!"<< endl;
                system("PAUSE");
            }
            else if (wybor == '4' )
            {
                cout<<"Podaj nowy emial: ";
                cin >> adresaci[liczbaPorzadkowaDlaZmianyDanychAdresata].email;
                cout <<"zmienione!"<< endl;
                system("PAUSE");
            }
            else if (wybor == '5' )
            {
                cout<<"Podaj nowy adres: ";
                cin >>adresaci[liczbaPorzadkowaDlaZmianyDanychAdresata].adres;
                cout <<"zmienione!"<< endl;
                system("PAUSE");
            }
            else if (wybor == '9' )
            {
                break;
            }
        }

}
void zmianaHaslaUzytkownika (string login, vector <Uzytkownik> &uzytkownicy)
{
    int indeksDoZmianyHasla=0,liczebnikDlaPodawaniaHasla=0;
    string haslo, hasloDoPorownania;
    for(int i=0; i<uzytkownicy.size(); i++)
    {
        if(uzytkownicy[i].login==login)
        {
            indeksDoZmianyHasla=i;
        }
    }
    while(liczebnikDlaPodawaniaHasla==0)
    {
        cout<<"Podaj nowe haslo: ";
        cin>>haslo;
        cout<<"Podaj ponownie haslo: ";
        cin >> hasloDoPorownania;
        if(haslo==hasloDoPorownania)
        {
            if(uzytkownicy[indeksDoZmianyHasla].haslo==haslo)
            {
                cout<<"Nowe haslo nie moze byc identyczne do poprzedniego"<<endl;
            }
            else
            {
                uzytkownicy[indeksDoZmianyHasla].haslo=haslo;
                //zapisywanieUzytkownikowDoPliku(uzytkownicy);
                liczebnikDlaPodawaniaHasla=1;

            }
        }
        else
        {
            cout<<"Hasla nie sa identyczne"<<endl;

        }
    }
}


