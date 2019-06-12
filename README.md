# robotika-2018-2019-2
2018/2019 tavaszi félév robotika

## Robot
A robot egy arduino yun vezérlővel felszerelt kör alakú robot. Két hajtott és egy támasztó kerékkel rendelkezik, akkumulátoros energiaforrás segítségével hajtható meg. Található rajta 3 távolságmérő szenzor, előre, és 45 fokos szögben a két oldalra tudunk vele távolságot mérni. A kerekek fordulatait odométer figyeli, ezzel meg tudjuk határozni, hogy az egyes meghajtott kerekek hány körbefordulást tettek az indítást követően.

## Feladat
A robot feladata, hogy bekapcsolás után feltérképezze a környezetét. Ezt úgy teszi, hogy folyamatosan korrigálva az odométer bemenetei alapján egyenesben tartja és állandó sebességgel előremenetbe vezérli magát. Abban az esetben, ha távolságérzékelői alapján úgy látja, hogy közel van valamilyen akadály, akkor eldönti, hogy milyen irányban van nagyobb esélye a kikerülésre, majd ennek megfelelően körülbelül 90 fokot fordul a saját tengelye körül, és újból megpróbál egyenes vonalban haladni. Ha nem elég a fordulat, akkor újból elfordul.

## Nehézségek
A legnagyobb nehézség az implementációval kapcsolatban az volt, hogy az odométerek adatai nem voltak konzisztensek a valódi elfordulás mértékével. Több mint 4 alkalom azzal telt, hogy ezt vizsgáltuk. Arra jutottunk, hogy mivel a kerekek tengelyei nem stabilak az egyik oldalon, ezért ezen az oldalon kis kilengés is jelzést váltott ki az odométerből, melynek hatására akkor is kb. 8-szor annyi elfordulást tapasztaltunk a hibás oldalon a jó oldalhoz képest, mikor manuálisan teljesen egyenes mozgásra kényszerítettük a robotot. Miután ezt felfedeztük, és konstan faktorok bevezetésével korrigáltuk, következhetett az akadályok kikerülése. Itt a szenzorok mérési tartományai nem egyeztek meg, ez egyik szenzor jóval nagyobb tartományban adott jeleket ugyanolyan távolság esetén, illetve a eléggé zajos volt, sokszor ugrásszerűen megnövekedett értékeket láthattunk. A szenzor érdekessége továbbá, hogy az értékek nem egyenesen, hanem fordítottan arányosak a mért távolsággal.

## Implementáció és vezérlés
A vezérlést végző program folyamatosan figyeli a kerekek körbefordulásainak mértékét. Ezt úgy valósítottuk meg, hogy egy aszinkron eseménykezelőben folyamatosan növelünk egy-egy számlálót a két kerék odométereinek jelszint-változására reagálva. Erre példa a jobb oldali kerék esetében az eseménykezelő regisztrálását megvalósító utasítás: `attachInterrupt(digitalPinToInterrupt(rightPinNum), onRightRev, CHANGE);`
A vezérlés során számon tartjuk az egy vezérési kör alatt megtett fordulatok számát, és a kumulatív, az egész futás során lezajlott fordulások számát is mindkét kerékre. Ezek aránya alapján szabályozzuk a jobb oldali kerék sebességét. Fontos, hogy csak a jobb oldali kereket szabályozzuk ilyen módon, a bal oldali konstans sebességre van állítva.
A távolságmérést, és az ez alapján történő döntéhozást minden kiértékelő ciklus elején elvégezzük, és a két lehetséges fordulási irány közül az alapján választunk egyet, hogy melyik oldali szenzor értékei nagyobbak.
