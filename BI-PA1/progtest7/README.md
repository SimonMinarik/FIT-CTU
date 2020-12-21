# Počítání I

Úkolem je vytvořit program, který bude kontrolovat příklady z matematiky.

Při procvičování základních početních operací může velmi pomoci počítač. Předpokládáme, že počítač dostane ke kontrole oskenované vypočtené příklady, které procvičují operace sčítání. Úkolem počítače je zkontrolovat, zda je příklad správně. Bohužel, úloha není tak úplně snadná. Při skenování se může část příkladu špatně rozpoznat. OCR pak na dané místo vyplní znak otazník.

Program tedy na vstupu dostane jeden příklad na sčítání s vyplněným výsledkem. Máme jistotu, že operátory + a = se naskenovaly správně. Čísla se buď rozpoznala správně, nebo jsou nahrazena znakem otazník. Úkolem programu je takový příklad načíst, vyhodnotit a určit, zda je výsledek správně. Pokud je výsledek správně, může existovat více správných náhrad otazníků za číslice. V takovém případě program zobrazí jednu libovolnou takovou možnou náhradu a dále dopočítá i celkový počet existujících možností náhrad. Pokud je výsledek špatně nebo pokud otazníky nelze nahradit tak, aby vznikl správný výsledek, je výsledkem oznámení o špatně vyřešeném příkladu (viz ukázka).

Vstupem je jeden příklad k analýze. Příklad se skládá z několika sčítanců, které jsou oddělené znakem +. Za sčítanci je znak rovnítko a vypočtený výsledek. Sčítance i výsledek jsou desítková čísla, ve kterých se může objevit jeden nebo i více znaků otazník. Za vstupní řádkou je odřádkování, ale jinak řádka neobsahuje žádné bílé znaky.

Výstupem programu je buď oznámení o chybně vypočteném příkladu, nebo je zobrazen zadaný příklad s nahrazenými znaky ? tak, aby byl výsledek správně. Pokud existuje více možných náhrad, program zobrazí libovolnou jednu z nich. Dále je pak zobrazen počet možných náhrad, kterými se dá dostat ke správně vypočtenému příkladu.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

* na vstupu jsou neplatné sčítance nebo výsledek (musí obsahovat pouze číslice 0 až 9 nebo znak ?),
* chybí operátor =,
* mezi dvojicí operátorů + není žádný sčítanec,
* chybí sčítanec před operátorem = nebo výsledek za operátorem =,
* na pravé straně za operátorem = jsou operátory +,
* zadání obsahuje bílé znaky.