/************************************************************************************
 sayi-tahnin.cpp - maidis / 2010

 Daha önceden Basic'te yazdığım sayı tahmin oyununun C++'laşmış hali :)
 Ekrandaki sayı silme atraksiyonunu Basic'teki sürümünden aktarmaya çalıştım
 http://anilozbek.blogspot.com/2007/11/basic-ve-gnulinux.html

 Sayı tahmin oyunun çekirdeği/temeli için Jeremy'nin kodlarından yararlandım
 http://www.scratchprojects.com/2006/06/number_guessing_game_p01.php

 Konsol üzerinde istediğim yere istediğimi yazmak için de Airam Rodríguez Rivero'nun
 söylediklerinden yararlandım, kendisinin ayrıca klavyeden girilenleri anında almak
 için de bazı çözümleri var, bakabilirsiniz
 http://airamrguez.blogspot.com/2008/02/cmo-implementar-la-funcin-gotoxy-en-c.html

 Oyun ne yazık ki platform bağımsız değil, ama biraz kurcalarsanız eminim GNU/Linux
 harici işletim sistemleri üzerinde de çalışacaktır
 ************************************************************************************/


// Kullanacağımız fonksiyonların tanımlı olduğu kütüphaneleri oyunumuza dahil ediyoruz
// Hangi fonksiyonun hangi kütüphaneye ait olduğunu öğrenmek için başlıkları tek tek
// Yorum haline getirebilir ve aldığınız hataların sonucuna bakabilirsiniz :)
// Kısa kısa yazayım yine de:
// iostream: cin, cout...
// iomanip: setw...
// cstdlib: system, rand, srand...

#include <iostream>
#include <iomanip>
#include <cstdlib>
// ctime ve string Windows üzerinde gerekli gibi
// Bir de KDevelop şu an tam anlayamadığım bazı uyarılar veriyor bu ikisi olmayınca
// ctime'yi time için gerekiyor sanıyordum ama değil galiba ya da başka bir yerden dahil oluyor?
#include <ctime>
#include <string>
#include <sstream>

// İsim uzayımızı belirtiyoruz std'den başka bir şey kullanmadığımız için
// herhangi bir karışıklık olmayacaktır, ama yakında düzeltmemiz gerekebilir
using namespace std;


template <class T>inline string ToString(const T& t)
    {
    stringstream ss;
    ss << t;
    return ss.str();
    }

inline string gotoxy(const int& x,const int& y)
    {
    return "\33[" + ToString(x) + ";" + ToString(y) + "H";
    }

// Oyun başlarken ekrana 1'den 100'e tüm sayıları yazdırmak için
int sayilariyaz()
    {
    system("clear");

    cout << "         "
         << "\033[32m...::: Sayı Tahmin Oyunu v0.5 :::...\033[0m"
         << endl;

    int i;

    for (i=1; i<=100; i++)
        {
        // Sayıları en düşük değerlikli basamaklarına göre hizalamak için
        cout << setw(5) << i;
        // Eğer sayı 10'a tam bölünebiliyorsa satır atla
        if ((i%10) == 0) cout << endl;
        }
    }


// Oyunla ilgili olayların gerçekleştiği yer
int oynat()
    {
    // Zamana göre rasgele sayı üretimi yapmazsak hep aynı sayı tutulur
    srand(time(0));

    int rasgeleSayi = rand() % 100 + 1; // 1'le 100 arası rasgele sayı üretmek için
    int tahmin = 0; // kullanıcının tahinlerini tutmak için
    int deneme = 0; // kullanıcının kaçıncı hakkı olduğunu saymak için
    int denemeHakki = 7; // kullanıcıya kaç hak verelim şeysi
    int sinirNoktasi = 100; // Bilgisiayarın hangi aralıkta sayı tutacağı 1...sinirNoktasi
                            // Bunu değiştirirseniz pek çok şeyi daha değiştirmek zorundasınız ama

    do
       {
       // kullanıcının canını sıkalım :)
       cout << gotoxy(4,60) << "Kalan hakkınız: " << denemeHakki - deneme;

       // önceki girilen sayıyı ekrandan temizlemek için
       // kullanıcın on basamaklı bir sayı girmeyi de
       // deneyebileceğini düşünerek biraz büyük alalım :)
       cout << gotoxy(15,41) << "          ";

       cout << gotoxy(15,15) << "Tahmininiz nedir (1-" << sinirNoktasi << "): ";
       cin >> tahmin;


       // Her tahminden sonra deneme değişkenini arttırıyoruz
       // deneme her halükarda artacaktır, bence böyle de olması gerekiyor
       // kullanıcı daha önceden girdiği bir sayıyı veya sınırların dışından
       // bir sayıyı girdiğinde de bir deneme hakkı gidecektir
       deneme++;

       // Yapılacak: bunların teker fonksiyonla olması lazım
       int satir = (tahmin%10) ? tahmin/10+2 : tahmin/10+1 ;
       int sutun = (tahmin%10) ? (tahmin % 10 - 1) * 5 + 1 : 46;

       // Yapılacak: hizalamadaki sorunların düzeltilmesi lazım
       // tek haneli sayıları silmek için
       cout << gotoxy(satir, sutun) << "     ";
       // test yaparken aşağıdaki daha kolay anlaşılır
       //cout << gotoxy(satir, sutun) << "-----";


       // tahmin bilgisarın tuttuğu sayıdan düşükse ve sınır içindeyse
       // sınırların içinde olup olmadığını kontrol ediyoruz çünkü
       // bunu yapmazsak sınırların dışında bir sayı girildiğinde
       // ekrandaki sayı renklendirme yamuluyor
       if (tahmin < rasgeleSayi && tahmin > 0)
           {
           cout << gotoxy(satir, sutun) << setw(5) << "\33[33;1m   " + ToString(tahmin) + "\33[0m" << endl;
           cout << gotoxy(5,60) << "Tahmininiz çok düşüktü.";
           }

       // tahmin bilgisarın tuttuğu sayıdan büyükse ve sınır içindeyse
       else if (tahmin > rasgeleSayi && tahmin < (sinirNoktasi + 1))
           {
           cout << gotoxy(satir, sutun) << setw(5) << "\33[34;1m   " + ToString(tahmin) + "\33[0m" << endl;
           cout << gotoxy(5,60) << "Tahmininiz çok yüksekti.";
           }

       else if (tahmin > sinirNoktasi || tahmin < 0) // tahmin sınırların dışındaysa
           {
           cout << gotoxy(5,60) << "1 ve " << sinirNoktasi << " sınırdır :)";
           }

       else if (tahmin == rasgeleSayi) // tahmin doğruysa
           {
           cout << gotoxy(satir, sutun) << setw(5) << "\33[32;1m   " + ToString(tahmin) + "\33[0m" << endl;
           cout << gotoxy(16,15)
                << "Kazandınız! Sayıyı "
                << deneme
                << " denemede tahmin ettiniz."
                << endl;
           }

       if (tahmin != rasgeleSayi && deneme == denemeHakki)
           {
           cout << gotoxy(16,15)
                << "Kaybettiniz, önemli olan oynamaktı ama. Bu arada sayı şuydu: "
                << rasgeleSayi
                << endl;
           }
       } while (tahmin != rasgeleSayi && deneme != denemeHakki);

    cout << gotoxy(4,60) << "Kalan hakkınız: " << denemeHakki - deneme; // bunu iki kere kullandık ama
    cin;
    return 0;
    }


int main()
    {
    char cevap;
    do
        {
        cevap = 'h';

        sayilariyaz();

        oynat();

        cout << gotoxy(5,7) << "                                        ";
        cout << gotoxy(6,7) << "     Tekrar oynamak ister misiniz ?     ";
        cout << gotoxy(7,7) << "                 (e/h)                  ";
        cout << gotoxy(8,7) << "                                        ";

        cin >> cevap;
        } while (cevap=='e');

    system("clear");
    return 0;
    }
