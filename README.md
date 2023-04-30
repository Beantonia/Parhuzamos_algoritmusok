Berecz Antónia – Párhuzamos algoritmusok beadandó

1. Program:
Több random szám egyszerre történő generálása

2. Megvalósítás:
•	Szekvenciális módszer
•	Pthreads segítségével párhuzamosítást használva
•	OpenMP-vel szintén párhuzamosítva
•	Fork-Join technológiával

3. Mérés: 
Mivel a kérdéskörben a leglényegesebb kérdésnek az időfaktort gondolom, így azt szeretném lemérni, hogy az egyes programok lefutása mennyi időt vesz igénybe. 
A futási idő mérésére a time.h könyvtár függvényeit szeretném használni.
