#include "Imenik.h"
#include <string>
#include <iostream>
using namespace std;

int main(){
    try{//jedan od nacina zadavanja konstruktora, radi..
        Imenik Novi(Kontakt("Emir", "03039393", "399393939"));


        Kontakt user_1("Selma",  "062441128");
        Kontakt user_2("Kerim",  "062441128", "033465077");
        Kontakt user_3("Zakir",  "065441159", "033465077");
        Kontakt user_x("Zakir", "064022333", "0239449");
        //konstruktor koji prima niz vektora
        vector<Kontakt> v{user_1, user_2, user_3, user_x};
        Imenik Roditelji(v);
        Roditelji.SetNaziv("Roditelji");
        cout << "Ispisani imenik roditelji: " << endl;
        Roditelji.Ispisi();
        cout << endl;
        Kontakt user_4("Selma",  "062999999", "033466077");
        Kontakt user_5("Ena", "063372167", "033465077");
        Kontakt user_6("Sekir", "065441159", "033696969");
        Kontakt user_7("Adnan", "011222333", "033110987");
        Imenik Djeca(user_4);
        Djeca.SetNaziv("Djeca");
        Djeca.Dodaj(user_5);
        Djeca.Dodaj(user_6);
        Djeca.Dodaj(user_7);
        cout << "Ispisani imenik djeca: " << endl;
        Djeca.Ispisi();
        cout << endl;

        cout << "Ispisani imenik djeca u kojem je izbrisan kontakt Ena: " << endl;
        Djeca.IzbrisiKontakt(user_5);
        Djeca.Ispisi();
        cout << endl;

        //promjena naziva kontakta iz liste, lista ostane sortirana
        cout << "Ispisani imenik djeca iz promjenu broja Sekira: " << endl;
        Djeca.PromijeniBrojKontakta(user_6, "033123456");
        Djeca.Ispisi();
        cout << endl;

        //bacanje izuzetka u slucaju dodavanja kontakta sa istim imenom
        //Kontakt user_istoimekaouser5("Ena", "061111222", "005555123");
        //Djeca.Dodaj(user_istoimekaouser5);

        //bacanje izuzetka u slucaju promjene imena kontakta a to ime u toj listi vec postoji
        //Roditelji.PromijeniNazivKontakta(user_3, "Selma");

        cout << "Ispisani svi clanovi iz imenika djeca sa imenom koji pocinje sa Se: " << endl;
        Djeca.PretrazivanjePoNazivu("Se");
        cout << endl;

        cout << "pretrazivanje imenika roditelji po broju koji pocinje sa 062: " << endl;
        Roditelji.PretrazivanjePoBroju("062");
        cout << endl;


        cout << "Pokaz da funkcija spoji dobro radi, sljedeca dva imenika cemo spojiti, i to ce biti treici koji vidite: " << endl << endl;
        Kontakt prvi("Emir", "066123456");
        Kontakt drugi("Emir", "022345123");
        Kontakt treci("Adi", "062222333", "032123033");
        Kontakt cetvrti("Azra", "064000111");
        vector<Kontakt> pomoc{prvi,drugi,treci, cetvrti};
        Imenik prvi_imenik(pomoc);
        prvi_imenik.SetNaziv("prvi_imenik");
        cout << "Ispisan prvi imenik koji se spaja: " << endl;
        prvi_imenik.Ispisi();
        cout << endl << endl;
        Kontakt peti("Emir", "066123456");
        Kontakt sesti("Adi", "063333222");
        Kontakt sedmi("Azra", "064000111", "033333333");
        Imenik drugi_imenik(peti);
        drugi_imenik.Dodaj(sesti);
        drugi_imenik.Dodaj(sedmi);
        drugi_imenik.SetNaziv("drugi_imenik");
        cout << "Ispisan drugi imenik koji se spaja: " << endl;
        drugi_imenik.Ispisi();
        cout << endl << endl;
        Imenik sve;
        sve.SetNaziv("sviImeniciZajedno");
        sve = Spoji(prvi_imenik,drugi_imenik);
        cout << "ispisuje se imenik koji je spojio imenik1 i imenik2: " << endl;
        sve.Ispisi();
    }



    catch(const char poruka []){
        cout << poruka;
        }

}
