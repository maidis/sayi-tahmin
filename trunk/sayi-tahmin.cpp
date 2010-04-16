/************************************************************************************
 sayi-tahnin.cpp - maidis / 2010

 Daha önce Basic'te yazdığım sayı tahmin oyununun C++'laşmış hali :)
 Ekrandaki sayı silme atraksiyonunu Basic'teki sürümünden aktarmaya çalıştım
 http://anilozbek.blogspot.com/2007/11/basic-ve-gnulinux.html

 Sayı tahmin oyunun çekirdeği/temeli için Jeremy'nin kodlarından yararlandım
 http://www.scratchprojects.com/2006/06/number_guessing_game_p01.php

 Konsol üzerinde istediğim yere istediğimi yazmak için de Airam Rodríguez Rivero'nun
 söylediklerinden yararlandım, kendisinin ayrıca klavyeden girilenleri anında almak
 için de bazı çözümleri var, bakabilirsiniz
 http://airamrguez.blogspot.com/2008/02/cmo-implementar-la-funcin-gotoxy-en-c.html

 Oyun ne yazık ki platform bağımsız değil, ama biraz kurcalarsanız eminim GNU/Linux
 harici işletim sistemleri üzerinde de çalışacaktır, biraz kurcalarsanız demişim
 de nereden baksanız cygwin, mingw, gettext, ncurses, xterm, terminator filan...
 ************************************************************************************/


// Kullanacağımız fonksiyonların tanımlı olduğu kütüphaneleri oyunumuza dahil ediyoruz
// Hangi fonksiyonun hangi kütüphaneye ait olduğunu öğrenmek için başlıkları tek tek
// Yorum haline getirebilir ve aldığınız hataların sonucuna bakabilirsiniz :)
// Kısa kısa yazayım yine de:
// iostream: cin, cout...
#include <iostream>
// iomanip: setw...
#include <iomanip>
// cstdlib: system, rand, srand...
#include <cstdlib>
// ctime ve string Windows üzerinde gerekli gibi
// Bir de KDevelop şu an tam anlayamadığım bazı uyarılar veriyor bu ikisi olmayınca
// ctime'yi time için gerekiyor sanıyordum ama değil galiba ya da başka bir yerden dahil oluyor?
#include <ctime>
#include <string>
#include <sstream>
// Aşağıdaki iki başlık sayesinde oyunu ulaslararası pazara açmayı düşünüyorum
// Olmazsa de gettext'i öğrenmiş olurum
#include <libintl.h>
#include <locale.h>
// Zaman sınırlamalı kullanıcı giriş hedesi için bir başlık daha ekleyelim
#include <sys/time.h>

// İsim uzayımızı belirtiyoruz std'den başka bir şey kullanmadığımız için
// herhangi bir karışıklık olmayacaktır, ama yakında düzeltmemiz gerekebilir
using namespace std;

// Bu şablon hedesi ve aşağıdaki inline (satıriçi? kitapta yerel denmiş) fonksiyonu
// terminalde yer değiştirmek için
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
void sayilariyaz()
    {
    int i;

    system("clear");
    // Ya ben hiçbir ek şey kullanmak istemediğimden ncurses kullanmadım
    // fakat sen gel gör ki clear komutu ncurses paketinden çıkıyormuş

    cout << "         "
         << "\033[32m...::: " << gettext("Number Guess Game") << " v0.5" << " :::...\033[0m"
         << endl;

    for (i=1; i<=100; i++)
        {
        // Sayıları en düşük değerlikli basamaklarına göre hizalamak için
        cout << setw(5) << i;
        // Eğer i 10'a tam bölünebiliyorsa satır atla
        if ((i%10) == 0)
            cout << endl;
        }
    }


// Oyunla ilgili olayların gerçekleştiği yer
void oynat()
    {
    int tahmin = 0;         // Kullanıcının tahminlerini tutmak için
    int deneme = 0;         // Kullanıcının kaçıncı denemesi olduğunu saymak için
    int denemeHakki = 7;    // Kullanıcıya kaç deneme hakkı verelim şeysi
    int can = 3;            // Kullanıcıya bir de can verelim tam olsun
    int beklemeSuresi = 15; // Kullanıcı kaç saniye içinde giriş yapacak
    int puan = 0;           // Puansız oyun mu olur hiç
    int sinirNoktasi = 100; // Bilgisiayarın hangi aralıkta sayı tutacağı 1...sinirNoktasi
                            // Bunu değiştirirseniz pek çok şeyi daha değiştirmek zorundasınız ama

    // zaman aşımlı kullanıcı girişi için gerekli hedeler
    fd_set fdset;
    struct timeval timeout;
    int  rc;

    do  {
        srand(time(0)); // Zamana göre rasgele sayı üretimi yapmazsak hep aynı sayı tutulur
        int rasgeleSayi = rand() % 100 + 1; // 1'le 100 arası rasgele sayı üretmek için

        do  {
            cout << gotoxy(2,60) << gettext("Score          : ") << puan;
            cout << gotoxy(3,60) << gettext("Remaining lives: ") << can;
            cout << gotoxy(4,60) << gettext("Remaining trys : ") << denemeHakki - deneme;

            cout << gotoxy(15,15) << gettext("What's your guess (1-") << sinirNoktasi << "): ";

            // Bu oyundaki en önemli hede aşağıdaki bir .ike yaramıyormuş gibi görünen satırdır
            // önemsiz gibi görünüşünün altında ne sırlar gizlidir, olmaması nelere sebeptir
            // yorumlarsanız görürsünüz, yerini değiştirirseniz görürsünüz
            // endl sen bizim her şeyimizsin, heydele heydele...
            cout << endl;

            // Aşağıdakileri şöyle düşünün cin >> timeout(beklemeSuresi) >> tahmin;
            // Hatta siz öyle düşünmeyin ben gotoxy'deki olayı buna uyarlamaya çalışayım
            timeout.tv_sec = beklemeSuresi;
            timeout.tv_usec = 0;
            FD_ZERO(&fdset);

            FD_SET(0, &fdset);

            rc = select(1, &fdset, NULL, NULL, &timeout);
            if (FD_ISSET(0, &fdset))
                {
                // TODO: harf girildiğinde sapıtıyor, önlem alınca da bir tuhaf oluyor
                cin >> tahmin;
                }

            // Her tahminden sonra deneme değişkenini arttırıyoruz
            // deneme her halükarda artacaktır, bence böyle de olması gerekiyor
            // kullanıcı daha önceden girdiği bir sayıyı veya sınırların dışından
            // bir sayıyı girdiğinde de bir deneme hakkı gidecektir
            deneme++;

            // TODO: bunların teker fonksiyonla olması lazım mı?
            int satir = (tahmin%10) ? tahmin/10+2 : tahmin/10+1 ;
            int sutun = (tahmin%10) ? (tahmin % 10 - 1) * 5 + 1 : 46;

            // TODO: hizalamadaki sorunların düzeltilmesi lazım
            // tek haneli sayıları silmek için
            cout << gotoxy(satir, sutun) << "     ";
            // test yaparken aşağıdaki daha kolay anlaşılır
            // cout << gotoxy(satir, sutun) << "-----";


            // tahmin bilgisarın tuttuğu sayıdan düşükse ve sınır içindeyse
            // sınırların içinde olup olmadığını kontrol ediyoruz çünkü
            // bunu yapmazsak sınırların dışında bir sayı girildiğinde
            // ekrandaki sayı renklendirme yamuluyor
            if (tahmin < rasgeleSayi && tahmin > 0)
                {
                cout << gotoxy(satir, sutun) << setw(5) << "\33[33;1m   " + ToString(tahmin) + "\33[0m";
                cout << gotoxy(5,60) << gettext("Your guess was so low.") << "     ";
                }

            // tahmin bilgisarın tuttuğu sayıdan büyükse ve sınır içindeyse
            else if (tahmin > rasgeleSayi && tahmin < (sinirNoktasi + 1))
                {
                cout << gotoxy(satir, sutun) << setw(5) << "\33[34;1m   " + ToString(tahmin) + "\33[0m";
                cout << gotoxy(5,60) << gettext("Your guess was so high.") << "     ";
                }

            else if (tahmin > sinirNoktasi || tahmin < 0) // tahmin sınırların dışındaysa
                {
                cout << gotoxy(5,60) << gettext("1 and ") << sinirNoktasi << gettext(" are frontier.") << "     ";
                }

            else if (tahmin == rasgeleSayi) // tahmin doğruysa
                {
                cout << gotoxy(satir, sutun) << setw(5) << "\33[32;1m   " + ToString(tahmin) + "\33[0m";
                cout << gotoxy(16,15)
                     << gettext("You won! You found the number in ")
                     << deneme
                     << gettext(" trys. Now next level.")
                     << endl;

                sleep(3);
                }

           if (tahmin != rasgeleSayi && deneme == denemeHakki)
                {
                can--;

                cout << gotoxy(16,15)
                     << gettext("Not good, try again.")
                     << endl;
                cout << gotoxy(17,15)
                     << gettext("By the way the number was: ")
                     << rasgeleSayi
                     << endl;

                sleep(3);
                }

            // önceki girilen sayıyı ekrandan temizlemek için
            // kullanıcın on basamaklı bir sayı girmeyi de
            // deneyebileceğini düşünerek biraz büyük alalım :)
            cout << gotoxy(16,0) << "          ";
            // bu son değişikliklerden sonra aşağı inmek zorunda kaldı
            // TODO: kullanıcının üç hanelilerden fazla girmemesini otomatikleştir
            } while (tahmin != rasgeleSayi && deneme != denemeHakki);

        // Zaman aşımını her bölüm için üç saniye düşürelim
        // Üç saniyeden sonrasına geçmemesini de sağlayalım
        if (beklemeSuresi > 3)
            beklemeSuresi--;

        // 100 puandan sonra her bölüm için ve ilk denemede bilinmesine bir can şirketten
        if (puan >= 100 || deneme==1)
            can++;

        puan = puan + (denemeHakki - deneme) * 3;
        deneme = 0;

        cout << endl;
        sayilariyaz();

        if (can == -1)
            {
            cout << gotoxy(16,15)
                 << gettext("You lost! It's not the end of world. By the way the number was: ")
                 << rasgeleSayi
                 << endl;
            }

        } while (can >= 0);
    }


int main()
    {
    // Yerelleştirmeyle (gettext) ilgili şeyler
    setlocale(LC_ALL, "");
    bindtextdomain("sayi-tahmin", ".");
    textdomain( "sayi-tahmin");

    // Kullanıcıya yeniden oynamak isteyip istemediğini...
    char cevap;

    do  {
        cevap = 'h';

        sayilariyaz();

        oynat();

        cout << gotoxy(6,17) << gettext("     Play again?     ");
        cout << gotoxy(7,17) << gettext("        (y/n)        ");

        cin >> cevap;
        } while (cevap=='e' || cevap=='y');

    system("clear");
    return 0;
    }
