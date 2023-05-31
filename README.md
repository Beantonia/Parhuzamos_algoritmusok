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

Módosítás az eredeti tervezethez képest:
Végül nem egy problémával foglalkoztam, hanem a random szám generálás témakörén belül három különböző feladatot készítettem el.
1. Random számok átlaga 
Elkészítettem szekvenciálisan majd a pthread technológiát használva párhuzamosítottam.
3. Lottó játék
Ezt a programot OpenMP technikával párhuzamosítottam.
5. Prímkereső
Ezt pedig fork (illetve windows beépített csomagjával hasonló elvek mentén dolgoztam, mint ahogy linuxon tettem volna) techológiával párhuzamosítottam.
