A program állapotgépet képes építeni egy adott reguláris kifejezésből. 
Ezek után a programnak kifejezéseket lehet megadni, amelyekről eldönti, 
hogy illeszkednek-e a reguláris kifejezésre.

A reguláris kifejezés tartalmazhat betűket és néhány egyéb speciális 
karaktert. Ezek jelentése alább látható.
+: legalább 1 (1 vagy több)
*: bármennyi (0 vagy 1 vagy több)
|: vagy
(): a többi speciális karakter hatókörére van hatása

Példák:
1. a+: legalább egy darab "a" betű
2. a*: bármennyi "a" betű (lehet nulla darab is)
3. a: pontosan egy darab "a" betű
4. a|b: egy "a" vagy egy "b" betű 
5. (ab)*|(cd)+: vagy bármennyi "ab" vagy legalább egy "cd"

Futtatás:
1. Fordítás a make paranccsal.
2. ./program
3. A kívánt reguláris kifejezést kell beírni.
4. A kifejezésket kell beírni, amiről a program eldönti, hogy illeszkednek-e.
5. Az "exit" beírásával lehet kilépni a programból.


A program beépített tesztek is tartalmaz, ezek futtatásához az alábbiakat 
kell tenni:
1. make test
2. ./test