# sayi-tahmin

## Nedir // WTF
sayi-tahmin, daha önceden [QBasic](http://www.eksisozluk.com/show.asp?t=qbasic)'te yazdığım sayı tahmin oyununun [C++](http://tr.wikipedia.org/wiki/C%2B%2B)'laşmış halidir.

sayi-tahmin is a number guess game. I had written previously it with [QBasic](http://www.qbasic.com) and this is a [C++](http://en.wikipedia.org/wiki/C%2B%2B)'ized version of it.

## Nasıl görünüyor // How it looks
Neredeyse tam istediğim gibi, tamamladığımda bu oyunu yapma amacım olan görüntüye kavuşacağını düşünüyorum.

It's almost how i wanted it to be. When finished, I think it would be superb.

![http://i.imgur.com/1p3RD.png](http://i.imgur.com/1p3RD.png)

## Nasıl // How
  * Ekrandaki sayı silme atraksiyonunu [QBasic'teki sürümünden](http://anilozbek.blogspot.com/2007/11/basic-ve-gnulinux.html) aktarmaya çalıştım.
  * Sayı tahmin oyunun çekirdeği / temeli için [Jeremy'nin kodlarından](http://www.scratchprojects.com/2006/06/number_guessing_game_p01.php) yararlandım.
  * Konsol üzerinde istediğim yere istediğimi yazmak için de [Airam Rodríguez Rivero'nun söylediklerinden](http://airamrguez.blogspot.com/2008/02/cmo-implementar-la-funcin-gotoxy-en-c.html) yararlandım, kendisinin ayrıca klavyeden girilenleri anında almak için de bazı çözümleri var, bakabilirsiniz.

Oyun neredeyse platform bağımsız sayılır, biraz kurcalarsanız GNU/Linux harici işletim sistemleri üzerinde de çalışacaktır.

The game is nearly platform independent, with a little effort it will also work on other operating systems than GNU/Linux.

## Neden // Why
Bu elini atsan ellisine değecek sayı tahmin oyununun bir yenisini yapmaya neden ihtiyaç duyduğumu da anlatayım. Sadece öğrenmek ve eğlenmek için:
  * C++'ta nesne yönelimli oyun geliştirmek
  * [Autotools](http://www.gnu.org/software/automake)'un kullanımını öğrenmek
  * [SVN](http://subversion.tigris.org/)'de ne nedir, nasıl yapılır, bilgilenmek
  * [Seviyorum ben bu oyunu](http://www.eksisozluk.com/show.asp?t=i+love+this+game)

## Windows'ta // at Windows

Valla ben olsam hiç uğraşmam bu kadar zahmete. Ama bu oyunu oynamazsam gözlerim açık gider diyorsanız size iyi haberlerim var, oyun Windows'ta da çalışıyormuş. Aslında çalışması da gerekiyordu zaten ama oyun tamamen GNU/Linux için tasarlandığı için Windows'u GNU araçlarıyla donatmanız gerekiyor, donattım oradan biliyorum:

  * [mingw](http://www.mingw.org/): bununla derliyorum
  * [cygwin](http://www.cygwin.com/): ortamı bununla kuruyorum (bash, ncurses (clear için) ve şu anda aklıma gelmeyen bir kaç şey)
  * [terminator](http://software.jessies.org/terminator/): xterm de kullanılabilir ama bu daha güzel

![http://i.imgur.com/qI1kE.png](http://i.imgur.com/qI1kE.png)

## Diğer sayı tahmin oyunları // Other number guessing games
  * [GitHub](https://github.com/search?q=number+guess+game&type=Everything&repo=&langOverride=&start_value=1)
