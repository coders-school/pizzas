# Pizzas

## Praca na zajęciach z debugowania

Znajdź i popraw błędy w programie przy użyciu debuggera gdb/lldb. Po poprawkach wszystkie testy powinny przechodzić.

* +10 XP za poprawienie błędów w programie
* +3 XP za wykonanie tej pracy domowej do 22.09.2021 do końca dnia

## Praca na zajęciach z testowania

* Popraw klasę PizzaMock, aby była napisana z użyciem nowszej wersji GMocka.
* Usuń zależność od czasu w testach za pomocą dummy lub stuba.

## Praca domowa

1. (10 XP) Napisz klasę TimeMock, którą zastąpisz dummy/stuba napisanego podczas zajęć. Używaj go poprzez StrictMock. Dodaj właściwe `EXPECT_CALL` w kodzie testów.
2. (15 XP) Dopisz nowy przypadek testowy, w którym powielasz działanie funkcji main.cpp, ale zamawiasz 3 pizze: `StubPizza` oraz 2 różne `MockPizza` (różne nazwy, ceny i czas pieczenia; jedna jako StrictMock, druga jako NiceMock). Ustaw właściwe `EXPECT_CALL`.
3. (5 XP) Utwórz własny plik .github/workflows/module3.yml, który spowoduje, że GitHub automatycznie uruchomi testy.

+3 XP za każdy z 3 punktów dostarczony do 20.09 23:59.

Możecie pracować w parach 🙂

