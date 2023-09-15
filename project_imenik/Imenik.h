#ifndef IMENIK_H
#define IMENIK_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//struktura koja se koristi kao
struct Kontakt{
    public:
    string naziv;
    string mobilni;
    string fiksni;
    Kontakt():naziv(" "), mobilni("000000000"),fiksni("000000000"){}
    Kontakt(string ime, string telefon1 = string(), string telefon2 = string());
    void IspisiKontakt();
    void PromijeniIme(string drugo_ime){naziv = drugo_ime;}
    friend class Imenik;
    friend class Iterator;
};

class Imenik{
    struct Cvor{
        Kontakt podaci;
        Cvor *prethodni, *sljedeci;
        Cvor(Kontakt ime = Kontakt(), Cvor* pr = nullptr, Cvor* slj = nullptr):podaci(ime), prethodni(pr), sljedeci(slj){}
    };
    Cvor *head, *tail;
    string Naziv;
    int broj_elemenata;
    void init();
//imenici uzeti iz nase klase "Lista" i samo ih prilagodio da rade sta nam treba, uz par dodatnih nebitnih funkcija koje su mi sluzile za testiranje
public:class Const_Iterator{
        protected:
        Cvor *pok;
    public:
        Const_Iterator(Cvor *cv = nullptr): pok(cv){}
        Kontakt operator*(){return pok -> podaci;}
        Const_Iterator operator++(){ pok = pok -> sljedeci; return *this;}//prefiksna
        Const_Iterator operator++(int){Const_Iterator za_vracanje(*this); pok = pok -> sljedeci; return za_vracanje;}
        Const_Iterator operator--(){ pok = pok -> prethodni; return *this;}//prefiksna
        Const_Iterator operator--(int){Const_Iterator za_vracanje(*this); pok = pok -> prethodni; return za_vracanje;}
        friend bool operator==(Const_Iterator it1, Const_Iterator it2){return it1.pok == it2.pok;}
        friend bool operator!=(Const_Iterator it1, Const_Iterator it2){return it1.pok != it2.pok;}
        friend class Imenik;
    };
    class Iterator : public Const_Iterator{
    public:
        string& Ime(){return this -> pok -> podaci.naziv;}
        string Mobilni(){return this -> pok -> podaci.mobilni;}
        string Fiksni(){return this -> pok -> podaci.fiksni;}
        char PrvoSlovo(){return this -> pok -> podaci.naziv[0];}
        Iterator(Cvor *cvor = nullptr): Const_Iterator(cvor){}
        Kontakt& operator*(){return this -> pok -> podaci;}
        Iterator operator++(){ this ->pok = this ->pok -> sljedeci; return *this;}//prefiksna
        Iterator operator++(int){Iterator za_vracanje(*this); this ->pok = this ->pok -> sljedeci; return za_vracanje;}
        Iterator operator--(){ this ->pok = this ->pok -> prethodni; return *this;}//prefiksna
        Iterator operator--(int){Iterator za_vracanje(*this); this ->pok = this ->pok -> prethodni; return za_vracanje;}
        friend bool operator==(Iterator it1, Iterator it2){return it1.pok == it2.pok;}
        friend bool operator!=(Iterator it1, Iterator it2){return it1.pok != it2.pok;}
        friend class Imenik;
        void IspisiKontakt(){cout << this -> pok -> podaci.naziv << " ";
                             cout << this -> pok -> podaci.mobilni << " ";
                             cout << this -> pok -> podaci.fiksni << endl;
        }
    };
    Imenik();
    Imenik(Kontakt ime);
    Imenik(vector<Kontakt> &NizImena);
    Imenik(const Imenik& kopija);//big 5
    Imenik& operator=(const Imenik& rhs);//big 5
    ~Imenik(){Clear(); delete head; delete tail; Naziv = string();}//big 5
    Imenik(Imenik&& kopija);//big 5
    Imenik& operator=(Imenik&& rhs);//big 5
    void SetNaziv(string s){Naziv = s;}
    string GetNaziv(){return Naziv;}
    bool ImaIstoIme(Kontakt ime);
    Iterator Insert(Iterator it, Kontakt ime);
    Iterator Begin() {return head -> sljedeci;}
    Iterator End() {return tail;}
    Const_Iterator Begin() const {return head -> sljedeci;}
    Const_Iterator End() const{return tail;}
    void Dodaj(Kontakt ime);
    void Push_Back(Kontakt a){Insert(tail, a);}
    void Ispisi();
    void IzbrisiKontakt(Kontakt ime);
    void PromijeniNazivKontakta(Kontakt kontakt_sa_starim, string naziv);
    void PromijeniBrojKontakta(Kontakt kontakt_sa_starim, string broj);
    int Size() {return broj_elemenata;}
    void PretrazivanjePoNazivu(string pretrazivanje);
    void PretrazivanjePoBroju(string pretrazivanje);
    void Sortiraj();
    Iterator Erase(Iterator it);
    void Pop_Back(){Erase(tail -> prethodni);}
    bool Empty() const {return broj_elemenata == 0;}
    void Clear(){while(!Empty()) Pop_Back();}
    friend Imenik Spoji(Imenik &a, Imenik &b);
};

#endif //IMENIK_H
