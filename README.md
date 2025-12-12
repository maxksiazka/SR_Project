# SR_Project
## Autonomous Robotic ENgineered Takedown Machine
---
### Opis projektu

Projekt obejmuje zrealizowanie mobilnego robota typu [mini-sumo](https://kcir.pwr.edu.pl/~mucha/Pracki/Michal_Piotrowicz_praca_inzynierska.pdf).
Mechanika projektu znajduje się w podfolderze *Mechanics/*, podczas gdy projekt KiCad elektroniki układu znajduje się w podfolderze *Electronics/*.
Oprogramowanie robota mobilnego znajduje się w podfolderze *sumo/*.

---

### Elementy składowe robota

- MCU: **Raspberry Pi Pico 2 WH**
- Time-of-Flight Sensor: **VL53L0X**
- Czujnik odbiciowy: **KTIR0711S**
- Sterownik silników (H-bridge): **TB6612FNG**
- Silniki: **N20-BT37 micro 200:1**
- Moduł Wi-Fi: zintegrowany z MCU.
- Zasilanie: **Li-Po 2S**

---

### Zadania projektowe 

**Kolejność na liście zadań nie jest wiążąca.**
 - [x] Wykonanie wstępnego projektu mechaniki robota.
 - [x] Wykonanie projektu elektroniki robota.
 - [x] Zakup elementów elektronicznych.
 - [x] Wydrukowanie wstępnego korpusu robota.
 - [x] Wydrukowanie wstępnych kół robota
 - [x] Napisanie prostego klienta TCP - 'echo'.
 - [x] Napisanie systemu kontroli silników - kontrola PWM.
 - [x] Napisanie prostego systemu sterowania: klient TCP -> PWM.
 - [x] Implementacja odbioru danych z TOF - komunikacja I^2^C.
 - [x] Implementacja odbioru danych z czujników odbiciowych - ADC.
 - [ ] Implementacja autonomicznego systemu sterowania
 - [ ] (Opcjonalnie, ale prawie na pewno) Refactoring kodu.
 - [ ] Finalizacja projektu korpusu.
 - [ ] Finalizacja projektu kół.
 - [ ] Integracja robota.
 ---
 ---


## Metodyka Pracy
Pracujemy z użyciem `git branch` - PROSŻĘ

Standardowo merge request po *weryfikacji dwuosobowej*.

Coś jak [tutaj](https://www.geeksforgeeks.org/git/best-git-practices-to-follow-in-teams/) jeżeli chodzi o zasady to by była moja propozycja.
