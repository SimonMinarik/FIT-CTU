# Billboardy II

Úkolem je vytvořit program, který bude plánovat rozmístění billboardů na dálnici. Úloha je drobnou modifikací jednodušší varianty.

Chceme plánovat billboardy podél dálnice. Podle dálnice jsou vybraná místa, kde by bylo možné umístit billboardy (jinam je umístit nelze). Tato místa jsou určena vzdáleností od počátku dálnice, tato hodnota je celé číslo. Celkem je takto vybráno nejvýše 1000000 míst.

Do některých takových míst je potřeba umístit billboardy. Máme zadaný celkový počet billboardů, ty všechny musíme umístit. Zároveň je chceme podle dálnice rozmístit tak, aby mezi dvojicí sousedních billboardů byla co největší vzdálenost. Program billboardy rozmístí a určí, která dvojice z takto umístěných billboardů je nejblíže k sobě.

Vstupem programu je seznam míst vhodných pro umístění billboardů. Pozice pro umístění billboardů jsou celá čísla, jsou zapsaná ve složených závorkách a oddělená čárkami. Za seznamem pozic následují dotazy. Každý dotaz je zadán jako celé číslo cnt, toto číslo udává počet billboardů k umístění. Zadávání dotazů končí po dosažení konce vstupu (EOF).

Výstupem programu je vypočtená vzdálenost dvojice nejblíže umístěných billboardů pro každý zadaný vstupní dotaz. Pro některé vstupy může vycházet výsledek "nekonečno" případně "nelze dosáhnout". Přesný formát výpisu pro tyto situace je vidět v ukázkovém běhu programu.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

* možná umístění billboardů nebo počty billboardů nejsou platná celá čísla,
* pozice pro umístěni billboardů je záporné číslo,
* nejsou zadané žádné pozice pro umístění billboardů,
* je zadáno více než 1000000 pozic pro umístění billboardů,
* požadovaný počet billboardů v dotazu je záporný,
* chybí nebo přebývá nějaký oddělovač (složená závorka, čárka).