#include "Imenik.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Konstruktor za kontakt, mora primiti ime i bar 1 od 2 telefona, drugi je prazan string.
Kontakt::Kontakt(string ime, string telefon1, string telefon2){
        if(ime == "")
            throw "morate unijeti ime ili naziv firme";
        if(telefon1 == string() && telefon2 == string())
            throw "morate unijeti 1 od teleofna";
        for(int i = 0; i < telefon1.size(); i++)
            if(telefon1[i] < '0' || telefon1[i] > '9')
                throw "u mobilnom telefou samo cifre";
        for(int i = 0; i < telefon2.size(); i++)
            if(telefon2[i] < '0' || telefon2[i] > '9')
                throw "u fiksnom telefou samo cifre";
        /*if(telefon1 == string() && telefon2 != string()){
            naziv = ime;
            mobilni = " ";
            fiksni = telefon2;
        }
        if(telefon1 != string() && telefon2 == string()){*/
            naziv = ime;
            mobilni = telefon1;
            fiksni = telefon2;
        //}
    }

//funkcija namjenjena za strukturu kontakt, cisto zbog provjere unosa kontakta, nacina itpisa i slicno.
void Kontakt::IspisiKontakt(){
    cout << naziv << " " << mobilni << " " << fiksni;
}

//opis i razlog funkcije u pdf fajlu detaljno, bilo je zamisljeno da se napravi funkcija u nlogn vremenu koja bi se pozivala pri dodavanju,
//tako bi imenik bio uvijek sortiran, a i poklapao se sa jednim od zadataka, medjutim neuspjesni pokusaj od kojeg nisam htio odustati jer mi druga
//ideja nije pala na pamet... Veliki minus... Radi u O(N^n)...
void Imenik::Sortiraj(){
    for(Imenik::Iterator it1 = Begin(); it1 != End(); it1++){
        for(Imenik::Iterator it2 = Begin(); it2 != End(); it2++){
            if(it1.Ime() < it2.Ime())
                swap(*it1, *it2);
        }
    }
}

//inicializator koji radi osnovna podesavanja imenika, umjesto da u big_five konstruktorima uvijek zapocinjem sa ove 4 linije koda lakse je pozvati
//funkciju
void Imenik::init(){
    broj_elemenata = 0;
    head = new Cvor;
    tail = new Cvor(Kontakt(), head);
    head -> sljedeci = tail;
}

//konstruktor za imenik bez parametara
Imenik::Imenik(){
    init();
}

//konstruktor za imenik kojem se kao parametar pridruzi 1 kontakt, tako da u listi ima 1 element
Imenik::Imenik(Kontakt ime){
    init();
    Dodaj(ime);
    broj_elemenata = 1;
}

//konstruktor kopije
Imenik::Imenik(const Imenik& kopija){
    init();
    for(auto it = kopija.Begin(); it != kopija.End(); it++)
        Push_Back(*it);
}
//pomjerajuci konstruktor kopije
Imenik::Imenik(Imenik&& kopija){
    head = kopija.head;
    tail = kopija.tail;
    broj_elemenata = kopija.broj_elemenata;
    kopija.head = nullptr;
    kopija.tail = nullptr;
    kopija.broj_elemenata = 0;
}
//operator dodjele
Imenik& Imenik::operator=(const Imenik& rhs){
    Clear();
    for(auto it = rhs.Begin(); it != rhs.End(); it++)
        Push_Back(*it);
    return *this;
}
//pomjerajuci operator dodjele
Imenik& Imenik::operator=(Imenik&& rhs){
    Clear();
    delete head;
    delete tail;
    head = rhs.head;
    tail = rhs.tail;
    broj_elemenata = rhs.broj_elemenata;
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.broj_elemenata = 0;
    return *this;
}

//funkcija za brisanje iz imenika, koja vraca iterator koji je ostao iza obrisanog. Radi u konstantnom vremenu jer mu saljemo iterator koji brisemo
//i ne moramo prolaziti kroz imenik da dodjemo do elementa koji brisemo.
Imenik::Iterator Imenik::Erase(Imenik::Iterator it){
    Iterator za_vracanje(it.pok -> sljedeci);
    it.pok -> prethodni -> sljedeci = it.pok -> sljedeci;
    it.pok -> sljedeci -> prethodni = it.pok -> prethodni;
    delete it.pok;
    broj_elemenata--;
    return za_vracanje;
}

//funkcija koja pretrazuje za li postoji kontakt u listi sa ispim imenom. Mogao se napraviti da umjesto u O(n) vremenu radi u O(lgn) pomocu
//binarne pretrage medjutim ne znam kako pristupiti iteratoru u sredini...
bool Imenik::ImaIstoIme(Kontakt ime){
    for(Imenik::Iterator it = Begin(); it != End(); it++){
        if(it.Ime() == ime.naziv)
            return true;
    }
    return false;
}

////funkcija za unos novog kontakta iza iteratora koji proslijedimo funkciji, radi u konstantnom vremenu
Imenik::Iterator Imenik::Insert(Imenik::Iterator it, Kontakt ime){
    Cvor* novi = new Cvor(ime, it.pok -> prethodni, it.pok);
    it.pok -> prethodni = novi;
    novi-> prethodni -> sljedeci = novi;
    broj_elemenata++;
    return novi;
}

//funkcija za dodavanje novog kontakta, kontakt se uvijek prvo doda na kraj liste pa se lista sortira sto znaci da se ovo izvrsava u
//O(n^2) vremenu umjesto u O(n) ali nisam znao kako bih pravio konstruktore liste koji bi odmah sve stavljali u sortiranu bez fje sort(rdi u n^2)...
void Imenik::Dodaj(Kontakt ime){
    for(Imenik::Iterator it = Begin(); it != End(); it++){
        if(ime.naziv == it.Ime())
            throw "Ovo ime vec postoji u imeniku";
    }
    Insert(tail, ime);
    Sortiraj();
}

//fja za ispisivanje imenika.
void Imenik::Ispisi(){
    for(Imenik::Iterator it = Begin(); it != End(); it++)
        it.IspisiKontakt();
    }

    //fja za brisanje kontakta po imenu,ne vraca nista, mada bi mogla vracati mozda iterator, radi u O(n) vremenu, mogla je u O(lgn) vremenu...
void Imenik::IzbrisiKontakt(Kontakt ime){
    for(Imenik::Iterator it = Begin(); it != End(); it++){
        if(ime.naziv == it.Ime()){
            Erase(it);
        }
    }
}

//fja za promjenu naziva kontakta, radi u linearnom vremenu a mogla je u logaritmaskom...
void Imenik::PromijeniNazivKontakta(Kontakt kontakt_sa_starim, string ime){
    for(Imenik::Iterator it = Begin(); it != End(); it++){
            if(ime == it.Ime())
            throw "Ovo ime vec postoji u imeniku";
    }
    for(Imenik::Iterator it = Begin(); it != End(); it++){
        if(kontakt_sa_starim.naziv == it.Ime()){
            Kontakt kontakt_sa_novim(ime,kontakt_sa_starim.mobilni,kontakt_sa_starim.fiksni);
            IzbrisiKontakt(kontakt_sa_starim);
            Dodaj(kontakt_sa_novim);
        }
    }
}

//fja za promjenu broja.
void Imenik::PromijeniBrojKontakta(Kontakt kontakt_sa_starim, string broj){
    for(Imenik::Iterator it = Begin(); it != End(); it++){
        if(kontakt_sa_starim.mobilni == it.Mobilni()){
            Kontakt kontakt_sa_novim(kontakt_sa_starim.naziv,broj,kontakt_sa_starim.fiksni);
            IzbrisiKontakt(kontakt_sa_starim);
            Dodaj(kontakt_sa_novim);
        }
    }
}

//pretraga
bool DaLiPostoji(string ono_sto_trazimo, string pretraga){
    string p = "";
    for(int i = 0; i < ono_sto_trazimo.size(); i++){
        p += ono_sto_trazimo[i];
        if(p == pretraga)
            return true;
    }
    return false;
}

//fja koja trazi kontakt po nazivu, pri cemu nije potreban potpun naziv, ako postoji takav kontakt, ispisuje ga, linearno vrijeme
void Imenik::PretrazivanjePoNazivu(string pretrazivanje){
    for(Imenik::Iterator it = Begin(); it != End(); it++){
        string ImeKontakta= it.Ime();
        if(DaLiPostoji(ImeKontakta, pretrazivanje) == true){
            cout << it.Ime() << " " << it.Fiksni() << " " << it.Mobilni() << endl;
        }
    }
}

//fja koja trazi kontakt po broju, pri cemu nije potreban potpun broj, ako postoji takav kontakt, ispisuje ga, linearno vrijeme
void Imenik::PretrazivanjePoBroju(string pretrazivanje){
    for(Imenik::Iterator it = Begin(); it != End(); it++){
        string MobilniBrojKontakta = it.Mobilni();
        string FiksniBrojKontakta = it.Fiksni();
        if(DaLiPostoji(MobilniBrojKontakta, pretrazivanje) == true){
            cout << it.Ime() << " " << it.Fiksni() << " " << it.Mobilni() << endl;
        }
        else if(DaLiPostoji(FiksniBrojKontakta, pretrazivanje) == true){
            cout << it.Ime() << " " << it.Fiksni() << " " << it.Mobilni() << endl;
        }
    }
}

//funkcija koja spaja dva imenika kao sto se trazi u samom projektu, mislim da radi u p+q vremenu... Mozda je malo nepregledno, ali sam zagrade
//uvlacio i pratio bar to...
Imenik Spoji(Imenik &Prvi_imenik_koji_saljem, Imenik &Drugi_imenik_koji_saljem){
    Imenik k;
    Imenik::Iterator it1 = Prvi_imenik_koji_saljem.Begin();
    Imenik::Iterator it2 = Drugi_imenik_koji_saljem.Begin();
    while(it1 != Prvi_imenik_koji_saljem.End() && it2 != Drugi_imenik_koji_saljem.End()){
        if(it1.Ime() < it2.Ime()){
            k.Insert(k.End(), *it1);
            it1++;
        }
        else{
            if(it2.Ime() < it1.Ime()){
                k.Insert(k.End(), *it2);
                it2++;
            }
            if(it2.Ime() == it1.Ime() && it2.Fiksni() == it1.Fiksni() && it2.Mobilni() == it1.Mobilni()){
                k.Insert(k.End(), *it1);
                it1++;
                it2++;
            }
            if(it2.Ime() == it1.Ime() && it2.Mobilni() == it1.Mobilni()){
                if(it2.Fiksni() != "" && it1.Fiksni() == ""){
                    k.Insert(k.End(), *it2);
                    it1++;
                    it2++;
                }
                if(it1.Fiksni() != "" && it2.Fiksni() == ""){
                    k.Insert(k.End(), *it1);
                    it1++;
                    it2++;
                }
            }
            if(it2.Ime() == it1.Ime() && it2.Fiksni() == it1.Fiksni()){
                if(it2.Mobilni() != "" && it1.Mobilni() == ""){
                    k.Insert(k.End(), *it2);
                    it1++;
                    it2++;
                }
                if(it1.Mobilni() != "" && it2.Mobilni() == ""){
                    k.Insert(k.End(), *it1);
                    it1++;
                    it2++;
                }
            }


            if(it1.Ime() == it2.Ime() && it2.Mobilni() != it1.Mobilni()){//razliciti brojevi
                it1.Ime() = it1.Ime() +" -" + Prvi_imenik_koji_saljem.GetNaziv();
                it2.Ime() = it2.Ime() + " -" + Drugi_imenik_koji_saljem.GetNaziv();
                k.Insert(k.End(), *it1);
                k.Insert(k.End(), *it2);
                it1++;
                it2++;
            }
        }
    }

    if(it1 == Prvi_imenik_koji_saljem.End()){
        while(it2 != Drugi_imenik_koji_saljem.End()){
            k.Insert(k.End(), *it2);
            it2++;
        }
    }


    if(it2 == Drugi_imenik_koji_saljem.End()){
        while(it1 != Prvi_imenik_koji_saljem.End()){
            k.Insert(k.End(), *it1);
            it1++;
        }
    }
    return k;
}

//trazeni konstruktor koji prima vektor imena(podrazumijevao sam da mozemo koristiti vektor iz c++, jer ne pise da ne mozemo, kao u drugim temama)
Imenik::Imenik(vector<Kontakt> &NizImena){
    init();
    for(int i = 0; i < NizImena.size(); i++){
        if(!ImaIstoIme(NizImena[i])){
            Insert(tail, NizImena[i]);
        }
    }
    Sortiraj();
}



