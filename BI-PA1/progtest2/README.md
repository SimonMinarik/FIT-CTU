# Sekvence čísel #2

Úkolem je vytvořit program, který bude zpracovávat čísla zapsaná v různých číselných soustavách v zadaném intervalu hodnot. Úloha je rozšířením jednodušší varianty, v této variantě budou zpracovávána čísla v různých číselných soustavách.

Jedna instance řešeného problému je zadaná základem číselné soustavy R, dolní mezí intervalu LO a horní mezí intervalu HI. Představme si všechna celá čísla z intervalu <LO;HI> postupně zapsaná vedle sebe v soustavě o základu R. Takto zapsaná čísla vytvoří sekvenci číslic. Program bude mít za úkol spočítat následující:

* celkovou délku této sekvence (počet cifer),
* určit počet nul v této sekvenci,
* určit nejdelší kontinuální posloupnost nul v této sekvenci.
Například pro vstup r4:<10;20> by se jednalo o sekvenci čísel 10 až 20 zapsaných ve čtyřkové soustavě, tedy:

*  22 23 30 31 32 33 100 101 102 103 110 
Taková sekvence má celkem 27 cifer, z toho 7 nul a nejdelší kontinuální sekvence nul má délku 2. Podobně pro pro vstup r13:<10;20> by se jednalo o sekvenci čísel 10 až 20 zapsaných ve třináctkové soustavě, tedy:
*  A B C 10 11 12 13 14 15 16 17 
Taková sekvence má celkem 19 cifer, z toho 1 nulu a nejdelší kontinuální sekvence nul má délku 1.
Vstupem programu je zadání problémů k vyřešení. Problémů k vyřešení může být zadáno obecně mnoho. Pro každý problém k vyřešení je zadán základ číselné soustavy, interval hodnot a požadovaná operace. Zadání má jednu ze dvou forem:

rR: <LO;HI> OP
<LO;HI> OP

kde R je celé desítkové číslo udávající základ číselné soustavy. Pokud je vynecháno (druhá zkrácená forma), bude základ soustavy R=10. Hodnoty LO a HI jsou celá desítková čísla vymezující analyzovaný interval hodnot a OP je požadovaná operace:
* l pro výpočet celkové délky sekvence (počtu cifer),
* z pro výpočet počtu nul v sekvenci,
* s pro výpočet nejdelší kontinuální sekvence nul.

Na vstupu je zadáno mnoho problémů k vyřešení, program načítá vstup a pro každý úspěšně zpracovanou instanci problému zobrazí požadovaný výsledek. Čtení a zpracovávání zadaných problémů skončí v okamžiku dosažení konce vstupu (EOF).

Výstupem programu je vypočtená informace podle problému na vstupu. Přesný formát výpisu je vidět v ukázkovém běhu programu.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

* nečíselné zadání mezí intervalu nebo základu soustavy (neplatné číslo),
* mez intervalu je záporné číslo,
* dolní mez intervalu je větší než horní mez,
* základ soustavy není z intervalu 2 až 36,
* požadovaná operace není žádná z l, z, s,
* chybí nebo přebývá nějaký oddělovač (lomená závorka, středník).