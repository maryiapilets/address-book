#include <iostream>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct Zapis {
    short id;
    string imie;
    string nazwisko;
    string numer;
    string email;
    string adres;
}

string wczytajLinie() {
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
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

int wczytajLiczbeCalkowita() {
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

void zapiszZapisDoPliku(Zapis zapis) {
    fstream plik;
    plik.open("ksiazka.txt",ios::app);
    if(plik.good()) {
        plik << zapis.id << '|' << zapis.imie << '|';
        plik << zapis.nazwisko << '|' << zapis.numer << '|';
        plik << zapis.email << '|' << zapis.adres << '|' << endl;
        plik.close();
    } else {
        cout << "Nie udalo sie utworzyc plik" << endl;
    }
}

void dodajZapis(vector <Zapis> &zapisy) {
    int id_najwieksze = 0;
    if (zapisy.size() > 0) {
        id_najwieksze = zapisy.back().id;
    }
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
    zapis.id = id_najwieksze + 1;
    zapisy.push_back(zapis);
    zapiszZapisDoPliku(zapis);
    system ("pause");
}

void wypiszZapis(Zapis zapis) {
    cout << "Id=" << zapis.id << endl;
    cout << "Imie = " << zapis.imie << endl;
    cout << "Nazwisko = " << zapis.nazwisko << endl;
    cout << "Numer telefonu = " << zapis.numer << endl;
    cout << "Email = " << zapis.email << endl;
    cout << "Adres = " << zapis.adres << endl;
}

void wyszukajPoImieniu(vector <Zapis> zapisy) {
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

void wyszukajPoNazwisku(vector <Zapis> zapisy) {
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
            cout << "Nie ma osoby o takim imieniu" << endl;
        }
    }

    system ("pause");
}

void wyswietlWszystko(vector <Zapis> zapisy) {
    if (zapisy.size()  == 0) {
        cout << "Na razie pusto" << endl;
    } else {
        for(Zapis zapis:zapisy) {
            wypiszZapis(zapis);
        }
    }
    system("pause");
}

void zapiszZmianyDoPliku(vector <Zapis> &zapisy) {
    fstream plik;
    plik.open("ksiazka.txt",ios::out);

    if(plik.good()) {
        for (Zapis zapis:zapisy) {
            zapiszZapisDoPliku(zapis);
        }
    } else {
        cout << "Nie udalo sie zapisac zmian" << endl;
    }
}

void usunZapis(vector <Zapis> &zapisy) {
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
                zapiszZmianyDoPliku(zapisy);
            }
        }
    }
    system ("pause");
}

void odczytZPliku(vector <Zapis> &zapisy) {
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
        getline(ss, id, '|');
        zapis.id = atoi(id.c_str());
        getline(ss, zapis.imie, '|');
        getline(ss, zapis.nazwisko, '|');
        getline(ss, zapis.email, '|');
        getline(ss, zapis.numer, '|');
        getline(ss, zapis.adres, '|');
        zapisy.push_back(zapis);

    }
    plik.close();
}

void edytujZapis(vector <Zapis> &zapisy) {
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
                int nowyNumer = wczytajLiczbeCalkowita();
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
            zapiszZmianyDoPliku(zapisy);
        }
    }
    system ("pause");
}

int main()

{
    char wybor;
    vector <Zapis> zapisy;
    odczytZPliku(zapisy);
    system("cls");

    while(true) {
        system("cls");
        cout << "Ksiazka adresowa"<<endl;
        cout << "1. Dodaj zapis"<< endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystko" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Koniec programu" << endl;
        wybor = wczytajZnak();
        switch (wybor) {
        case '1':
            dodajZapis(zapisy);
            break;
        case '2':
            wyszukajPoImieniu(zapisy);
            break;
        case '3':
            wyszukajPoNazwisku(zapisy);
            break;
        case '4':
            wyswietlWszystko(zapisy);
            break;
        case '5':
            usunZapis(zapisy);
            break;
        case '6':
            edytujZapis(zapisy);
            break;
        case '9':
            exit(0);
        default:
            cout<<"Nie ma takiej opcji"<<endl;
            system("pause");
            break;
        }
    }
    return 0;
}
