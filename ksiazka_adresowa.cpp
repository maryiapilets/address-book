#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Zapis {
    short id;
    short idAutora;
    string imie;
    string nazwisko;
    string numer;
    string email;
    string adres;
};

struct Uzytkownik {
    int id;
    string imie;
    string haslo;
};

string wczytajLinie() {
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

int wczytajLiczbeCalkowita() {
    cin.sync();
    string wejscie = "";
    int liczba = 0;
    while(true) {
        getline(cin, wejscie);
        stringstream myStream(wejscie);
        if (myStream >> liczba) {
            break;
        }
        cout << "To nie jest liczba calkowita" << endl;
    }
    return liczba;
}

char wczytajZnak() {
    string wejscie = "";
    char znak = {0};
    while(true) {
        getline(cin, wejscie);
        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak" << endl;
    }
    return znak;
}

void odczytUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik uzytkownik;
    string linia = "";
    fstream plik;

    plik.open("uzytkownicy.txt", ios::in | ios::app);
    if(plik.good() == false) {
        cout << "Nie mozna otworzyc pliku!" << endl;
    }

    while (getline(plik, linia)) {
        stringstream ss(linia);
        string id;
        getline(ss, id, '|');
        uzytkownik.id = atoi(id.c_str());
        getline(ss, uzytkownik.imie, '|');
        getline(ss, uzytkownik.haslo);
        uzytkownicy.push_back(uzytkownik);
    }
    plik.close();
}

int zalogujSie(vector <Uzytkownik> &uzytkownicy   ) {

    string imie;
    string wprowadzoneHaslo;
    string prawidloweHaslo;
    int id;
    int idZalogowanegoUzytkownika = 0;
    bool znalezione = false;

    cout << "Wprowadz imie uzytkownika" << endl;
    imie = wczytajLinie();

    for (Uzytkownik uzytkownik : uzytkownicy) {
        if (uzytkownik.imie == imie) {
            znalezione = true;
            prawidloweHaslo = uzytkownik.haslo;
            id = uzytkownik.id;
        }
    }
    if(znalezione) {
        cout << "Wprowadz haslo" << endl;
        wprowadzoneHaslo = wczytajLinie();
        if (wprowadzoneHaslo == prawidloweHaslo) {
            cout << "Logowanie pomyslne" << endl;
            idZalogowanegoUzytkownika = id;
        } else {
            cout << "Haslo jest bledne" << endl;
        }
    } else {
        cout << "Nie ma takiego uzytkownika" << endl;
    }

    system("pause");
    return idZalogowanegoUzytkownika;
}

void zapiszUzytkownikaDoPliku(Uzytkownik uzytkownik) {
    fstream plik;
    plik.open("uzytkownicy.txt",ios::app);

    if(plik.good()) {
        plik << uzytkownik.id << '|' <<uzytkownik.imie << '|';
        plik << uzytkownik.haslo << endl;
        plik.close();
    } else {
        cout << "Nie udalo sie utworzyc plik" << endl;
    }
}

void zarejestrujSie(vector <Uzytkownik> &uzytkownicy) {

    Uzytkownik uzytkownik;
    int id_najwieksze = 0;

    if (uzytkownicy.size() > 0) {
        id_najwieksze = uzytkownicy.back().id;
    }

    cout << "Wprowadz imie uzytkownika" << endl;
    uzytkownik.imie = wczytajLinie();
    cout << "Wprowadz haslo" << endl;
    uzytkownik.haslo = wczytajLinie();
    uzytkownik.id = id_najwieksze + 1;
    uzytkownicy.push_back(uzytkownik);
    cout << "Uzytkownik jest zarejestrowany" << endl;

    zapiszUzytkownikaDoPliku(uzytkownik);
    system("pause");

}

void zapiszZapisDoPliku(Zapis zapis,string nazwaPliku) {

    fstream plik;
    plik.open(nazwaPliku,ios::app);
    if(plik.good()) {
        plik << zapis.id << '|' << zapis.idAutora << '|'<<zapis.imie << '|';
        plik << zapis.nazwisko << '|' << zapis.numer << '|';
        plik << zapis.email << '|' << zapis.adres << '|' << endl;
        plik.close();
    } else {
        cout << "Nie udalo sie utworzyc plik" << endl;
    }
}

void wypiszZapis(Zapis zapis) {
    cout << "Id=" << zapis.id << endl;
    cout << "Id autora =" << zapis.idAutora << endl;
    cout << "Imie = " << zapis.imie << endl;
    cout << "Nazwisko = " << zapis.nazwisko << endl;
    cout << "Numer telefonu = " << zapis.numer << endl;
    cout << "Email = " << zapis.email << endl;
    cout << "Adres = " << zapis.adres << endl;
}

int dodajZapis(vector <Zapis> &zapisy,int idZalogowanegoUzytkownika,int idNajwieksze) {

    Zapis zapis;
    cout << "Wprowadz imie" << endl;
    zapis.imie = wczytajLinie();
    cout << "Wprowadz nazwisko" << endl;
    zapis.nazwisko = wczytajLinie();
    cout << "Wprowadz numer telefonu" << endl;
    zapis.numer = wczytajLinie();
    cout << "Wprowadz email" << endl;
    zapis.email = wczytajLinie();
    cout << "Wprowadz adres" << endl;

    zapis.adres = wczytajLinie();
    zapis.id = idNajwieksze + 1;
    zapis.idAutora = idZalogowanegoUzytkownika;
    zapisy.push_back(zapis);
    zapiszZapisDoPliku(zapis,"ksiazka.txt");
    system ("pause");
    idNajwieksze++;
    return idNajwieksze;
}

int zapiszZmianyDoPliku(vector <Zapis> &zapisy,int idZalogowanegoUzytkownika,int idNajwieksze) {

    fstream plikOryginalny,plikTymczasowy;
    string linia = "";
    plikOryginalny.open("ksiazka.txt",ios::out|ios::in);
    plikTymczasowy.open("zapisyTymczasowe.txt",ios::app);

    if(plikOryginalny.good()) {

        while (getline(plikOryginalny, linia)) {

            Zapis zapis;
            stringstream ss(linia);
            string id;
            string idAutora;
            getline(ss, id, '|');
            zapis.id = atoi(id.c_str());
            getline(ss, idAutora, '|');
            zapis.idAutora = atoi(idAutora.c_str());
            getline(ss, zapis.imie, '|');
            getline(ss, zapis.nazwisko, '|');
            getline(ss, zapis.email, '|');
            getline(ss, zapis.numer, '|');
            getline(ss, zapis.adres, '|');
            idNajwieksze = zapis.id;

            if (zapis.idAutora != idZalogowanegoUzytkownika) {
                zapiszZapisDoPliku(zapis,"zapisyTymczasowe.txt");

            } else {
                for(size_t i = 0; i < zapisy.size(); i ++) {
                    if (zapisy[i].id == zapis.id) {
                        zapiszZapisDoPliku(zapisy[i],"zapisyTymczasowe.txt");
                    }
                }
            }
        }

        plikOryginalny.close();
        plikTymczasowy.close();
        remove("ksiazka.txt");
        rename("zapisyTymczasowe.txt","ksiazka.txt");

    } else {
        cout << "Nie udalo sie zapisac zmian" << endl;
    }
    return idNajwieksze;
}

void zapiszNoweHasloDoPliku(vector <Uzytkownik> &uzytkownicy) {
    fstream plik;
    plik.open("uzytkownicy.txt",ios::out);

    if(plik.good()) {
        for (Uzytkownik uzytkownik:uzytkownicy) {
            zapiszUzytkownikaDoPliku(uzytkownik);
        }

    } else {
        cout << "Nie udalo sie zapisac zmian" << endl;
    }
}


void wyszukajPoImieniu(vector <Zapis> zapisy, int idZalogowanegoUzytkownika) {
    if(zapisy.size()== 0) {
        cout << "Na razie nie ma zapisow" << endl;
    } else {
        string wejscie = "";
        bool znalezione = false;
        cout << "Wpisz imie dla wyszukiwania" << endl;
        wejscie = wczytajLinie();
        for (Zapis zapis: zapisy) {
            if (wejscie == zapis.imie) {
                wypiszZapis(zapis);
                znalezione = true;
            }
        }
        if (!znalezione) {
            cout << "Nie ma osoby o takim imieniu" << endl;
        }
    }
    system ("pause");
}

void wyszukajPoNazwisku(vector <Zapis> zapisy, int idZalogowanegoUzytkownika) {
    if(zapisy.size()== 0) {
        cout << "Na razie nie ma zapisow" << endl;
    } else {
        Zapis zapis;
        string wejscie = "";
        bool znalezione = false;
        cout << "Wpisz nazwisko dla wyszukiwania" << endl;
        wejscie = wczytajLinie();
        for (Zapis zapis : zapisy) {
            if (wejscie == zapis.nazwisko) {
                wypiszZapis(zapis);
                znalezione = true;
            }
        }
        if (!znalezione) {
            cout << "Nie ma osoby o takim nazwisku" << endl;
        }
    }

    system ("pause");
}

void wyswietlWszystko(vector <Zapis> zapisy,int idZalogowanegoUzytkownika) {
    if (zapisy.size()  == 0) {
        cout << "Na razie pusto" << endl;
    } else {
        for(Zapis zapis:zapisy) {
            wypiszZapis(zapis);
        }
    }
    system("pause");
}

void zmienHaslo (int idZalogowanegoUzytkownika,vector <Uzytkownik> &uzytkownicy) {

    string wprowadzoneHaslo;
    string stareHaslo;
    string noweHaslo;
    int index = 0;
    cout << "Wprowadz stare haslo" << endl;
    wprowadzoneHaslo = wczytajLinie();
    for(size_t i = 0; i < uzytkownicy.size(); i ++) {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            index = i;
        }
    }
    stareHaslo = uzytkownicy[index].haslo;

    if(wprowadzoneHaslo == stareHaslo) {
        cout << "Wprowadz nowe haslo" << endl;
        noweHaslo = wczytajLinie();
        uzytkownicy[index].haslo = noweHaslo;
        zapiszNoweHasloDoPliku(uzytkownicy);
        cout << "Haslo zmienione" << endl;
    } else {
        cout << "Haslo jest bledne" << endl;
    }
    system("pause");

}

void usunZapis(vector <Zapis> &zapisy, int idZalogowanegoUzytkownika,int idNajwieksze) {

    if(zapisy.size()== 0) {
        cout << "Na razie nie ma zapisow" << endl;
    } else {
        int nrId;
        char symbol;
        string linia = "";
        int adresatDoUsuniecia = 0;

        cout << "Wprowadz id adresata ktorego chcesz usunac" << endl;
        nrId = wczytajLiczbeCalkowita();
        bool idZnalezione = false;

        for (Zapis zapis: zapisy) {
            if (zapis.id == nrId) {
                idZnalezione = true;
            }
        }
        if (!idZnalezione) {
            cout << "Nie ma zapisu z takim id" << endl;
        } else {
            cout << "Czy naprawde chcesz usunac adresata? Wprowadz \"t\" jesli tak" << endl;
            symbol = wczytajZnak();

            if (symbol == 't') {
                for(size_t i = 0; i < zapisy.size(); i ++) {
                    if (zapisy[i].id == nrId) {
                        adresatDoUsuniecia = i;
                    }
                }
                zapisy.erase(zapisy.begin() + adresatDoUsuniecia);
                zapiszZmianyDoPliku(zapisy,idZalogowanegoUzytkownika,idNajwieksze);
            }
        }
    }
    system ("pause");
}

void edytujZapis(vector <Zapis> &zapisy, int idZalogowanegoUzytkownika,int idNajwieksze) {

    if(zapisy.size()== 0) {
        cout << "Na razie nie ma zapisow" << endl;
    } else {
        int index = 0;
        int idDoEdycji = 0;
        int poleDoEdycji = 0;
        cout << "Wprowadz id zapisu ktory chcesz edytowac" << endl;
        idDoEdycji = wczytajLiczbeCalkowita();
        bool idZnalezione = false;

        for (Zapis zapis: zapisy) {
            if (zapis.id == idDoEdycji) {
                idZnalezione = true;
            }
        }

        if (!idZnalezione) {
            cout << "Nie ma zapisu z takim id" << endl;
        } else {
            for(size_t i = 0; i < zapisy.size(); i ++) {
                if (zapisy[i].id == idDoEdycji) {
                    index = i;
                }
            }

            cout << "Wybierz pole do edycji" << endl;
            cout << "1. - Imie" << endl;
            cout << "2. - Nazwisko" << endl;
            cout << "3. - Numer telefonu" << endl;
            cout << "4. - Adres" << endl;
            cout << "5. - E-mail" << endl;
            poleDoEdycji = wczytajZnak();

            switch(poleDoEdycji) {
            case '1': {
                string noweImie = wczytajLinie();
                zapisy[index].imie = noweImie;
                break;
            }
            case '2': {
                string noweNazwisko = wczytajLinie();
                zapisy[index].nazwisko = noweNazwisko;
                break;
            }
            case '3': {
                string nowyNumer = wczytajLinie();
                zapisy[index].numer = nowyNumer;
                break;
            }
            case '4': {
                string nowyEmail = wczytajLinie();
                zapisy[index].email = nowyEmail;
                break;
            }

            case '5': {
                string nowyAdres = wczytajLinie();
                zapisy[index].adres = nowyAdres;
                break;
            }
            default: {
                cout << "Nie ma takiej opcji" << endl;
                break;
            }
            }
            zapiszZmianyDoPliku(zapisy,idZalogowanegoUzytkownika,idNajwieksze);
        }
    }
    system ("pause");
}

int odczytZPliku(vector <Zapis> &zapisy,int idZalogowanegoUzytkownika,int idNajwieksze) {

    Zapis zapis;
    string linia = "";
    fstream plik;

    plik.open("ksiazka.txt", ios::in | ios::app);
    if(plik.good() == false) {
        cout << "Nie mozna otworzyc pliku!" << endl;
    }

    while (getline(plik, linia)) {
        stringstream ss(linia);
        string id;
        string idAutora;
        getline(ss, id, '|');
        zapis.id = atoi(id.c_str());
        getline(ss, idAutora, '|');
        zapis.idAutora = atoi(idAutora.c_str());
        getline(ss, zapis.imie, '|');
        getline(ss, zapis.nazwisko, '|');
        getline(ss, zapis.email, '|');
        getline(ss, zapis.numer, '|');
        getline(ss, zapis.adres, '|');
        idNajwieksze = zapis.id;
        if (zapis.idAutora == idZalogowanegoUzytkownika) {
            zapisy.push_back(zapis);
        }

    }
    plik.close();

    return idNajwieksze;
}

int menuGlowne(int idZalogowanegoUzytkownika,vector <Uzytkownik> &uzytkownicy) {

    char wybor;
    system("cls");
    cout << "Ksiazka adresowa"<<endl;
    cout << "1. Logowanie"<< endl;
    cout << "2. Rejestracja" << endl;
    cout << "9. Koniec programu" << endl;
    wybor = wczytajZnak();

    switch (wybor) {
    case '1':
        idZalogowanegoUzytkownika = zalogujSie(uzytkownicy);
        break;
    case '2':
        zarejestrujSie(uzytkownicy);
        break;
    case '9':
        exit(0);
    default:
        cout << "Nie ma takiej opcji" << endl;
        system("pause");
        break;
    }

    return idZalogowanegoUzytkownika;
}

int main() {

    int idZalogowanegoUzytkownika = 0;
    vector <Uzytkownik> uzytkownicy;
    bool powtor = true;
    int idNajwieksze = 0;

    odczytUzytkownikowZPliku(uzytkownicy);

    while (true) {
        powtor = true;
        if (idZalogowanegoUzytkownika == 0) {
            idZalogowanegoUzytkownika = menuGlowne(idZalogowanegoUzytkownika,uzytkownicy);
        }

        else {
            vector <Zapis> zapisy;
            char wybor;
            idNajwieksze = odczytZPliku(zapisy, idZalogowanegoUzytkownika,idNajwieksze);

            while(powtor) {
                system("cls");
                cout << "Ksiazka adresowa"<<endl;
                cout << "1. Dodaj zapis"<< endl;
                cout << "2. Wyszukaj po imieniu" << endl;
                cout << "3. Wyszukaj po nazwisku" << endl;
                cout << "4. Wyswietl wszystko" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "7. Zmien haslo" << endl;
                cout << "8. Wyloguj sie" << endl;
                cout << "9. Koniec programu" << endl;
                wybor = wczytajZnak();

                switch (wybor) {
                case '1':
                    idNajwieksze = dodajZapis(zapisy,idZalogowanegoUzytkownika,idNajwieksze);
                    break;
                case '2':
                    wyszukajPoImieniu(zapisy,idZalogowanegoUzytkownika);
                    break;
                case '3':
                    wyszukajPoNazwisku(zapisy, idZalogowanegoUzytkownika);
                    break;
                case '4':
                    wyswietlWszystko(zapisy,idZalogowanegoUzytkownika);
                    break;
                case '5':
                    usunZapis(zapisy,idZalogowanegoUzytkownika,idNajwieksze);
                    break;
                case '6':
                    edytujZapis(zapisy, idZalogowanegoUzytkownika,idNajwieksze);
                    break;
                case '7':
                    zmienHaslo(idZalogowanegoUzytkownika, uzytkownicy);
                    break;
                case '8':
                    idZalogowanegoUzytkownika = 0;
                    zapisy.clear();
                    powtor = false;
                    break;
                case '9':
                    exit(0);
                default:
                    cout<<"Nie ma takiej opcji"<<endl;
                    system("pause");
                    break;
                }
            }
        }
    }
    return 0;

}

