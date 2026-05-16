- zrobić CRUD do reszty tabel (w cpp) (nie wiem czy na update starczy czasu, ale jak tak to super, jak nie to można jakoś owrapować funkcje delete i add)
- zrobić formularze do obsługi tychże CRUDów (w QML)
+ obsłużyć błąd przy podaniu błędnego hasła, bo póki co jest tylko obsługa czy znaleziono użytkownika czy nie, a trzeba dodać trzeci warunek (czyli poprawność hasła)
    -> zrobiłem to inaczej, teraz są dwie opcje - dobre logowanie i "błędny login LUB hasło", ale w logach jest napisane czy to hasło złe czy nie znaleziono użytkownika, żeby się łatwiej debugowało potem 
+ podzielić QML na różne strony 
    -> nie ma tego na podstawie loginSuccess, póki co jest walidacja tylko raz
    - dostęp może być na podstawie loginSuccess żeby było chociaż udawanie bezpieczeństwa
- poupiększać to (tło, odstępy, rozkminić jak to ładnie ułożyć, itd.) (nie rysujcie tylko programujcie, może być brzydko najwyżej się poprawi)
- napisać dokumentację (nie musi być komplet, ale ważne, żeby zacząć, saturday mówił, że mu to tito więc może być tex albo .md, mi to tito)
- zobaczyć gdzie można zmienić rzutowania, żeby nie było 4 przejść z jednego typu danych na drugi 
- przeflitrować funkcje z connection.cpp, bo raczej nie potrzebujemy ich tam aż tyle
- jak starczy czasu to zrobić skrócony widok i rozwijanie danego rekordu (w QML)
