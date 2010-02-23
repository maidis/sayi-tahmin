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
//#include <ctime> time için gerekiyor sanıyordum ama değil galiba ya da başka bir yerden dahil oluyor
//#include <string> bu da gerekmiyormuş, yorumlayalım
#include <sstream>

// İsim uzayımızı belirtiyoruz std'den başka bir şey kullanmadığımız için
// herhangi bir karışıklık olmayacaktır
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
    do
       {
       cout << gotoxy(4,60) << "Kalan hakkınız: " << denemeHakki - deneme;

       cout << gotoxy(15,41) << "   "; //önceki girilen sayıyı ekrandan temizlemek için
       cout << gotoxy(15,15) << "Tahmininiz nedir (1-100): ";
       cin >> tahmin;

       if (tahmin < rasgeleSayi)
           cout << gotoxy(5,60) << "Tahmininiz çok düşüktü.";

       if (tahmin > rasgeleSayi)
           cout << gotoxy(5,60) << "Tahmininiz çok yüksekti.";

       if (tahmin > 100 || tahmin < 0)
           cout << gotoxy(5,60) << "Bir ve yüz diyoruz, sınır diyoruz :)";

       // Her tahminden sonra deneme değişkenini arttırıyoruz
       deneme++;

       // Yapılacak: bunların tek fonksiyonla olması lazım
       int satir = (tahmin%10) ? tahmin/10+2 : tahmin/10+1 ;
       int sutun = (tahmin%10) ? (tahmin % 10 - 1) * 5 + 1 : 46;

       // Yapılacak: hizalamadaki sorunların düzeltilmesi lazım
       cout << gotoxy(satir, sutun) << "     " << endl; // tek haneli sayıları silmek için
       //cout << gotoxy(satir, sutun) << "-----" << endl;
       if (tahmin < rasgeleSayi)
           cout << gotoxy(satir, sutun) << setw(5) << "\33[33;1m   " + ToString(tahmin) + "\33[0m" << endl;
       else if (tahmin > rasgeleSayi)
           cout << gotoxy(satir, sutun) << setw(5) << "\33[34;1m   " + ToString(tahmin) + "\33[0m" << endl;
       else
           cout << gotoxy(satir, sutun) << setw(5) << "\33[32;1m   " + ToString(tahmin) + "\33[0m" << endl;

       } while (tahmin != rasgeleSayi && deneme != denemeHakki);

       cout << gotoxy(4,60) << "Kalan hakkınız: " << denemeHakki - deneme; // bunu iki kere kullandık ama
       if (tahmin != rasgeleSayi)
           cout << gotoxy(16,15)
                << "Kaybettiniz, önemli olan oynamaktı ama. Bu arada sayı şuydu: "
                << rasgeleSayi
                << endl;

       if (tahmin == rasgeleSayi)
           cout << gotoxy(16,15)
                << "Kazandınız! Sayıyı "
                << deneme
                << " denemede tahmin ettiniz."
                << endl;

    return 0;
    }



int main()
    {
    system("clear");

    cout << "         "
         << "\033[32m...::: Sayı Tahmin Oyunu v0.4 :::...\033[0m"
         << endl;

    sayilariyaz();

    oynat();
    }
