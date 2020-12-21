# Řešení osmisměrky

Úkolem je vytvořit program, který bude řešit hlavolam - osmisměrku.

Osmisměrka je zadaná jako 2D pole znaků a seznam slov. Cílem je v poli znaků nalézt slova ze seznamu a "vyškrtnout je". Zbylá (neškrtnutá) písmena tvoří tajenku. Slova se v osmisměrce mohou nacházet kdekoliv - horizontálně, vertikálně i diagonálně, čtená zleva doprava, shora dolů i naopak. Jedno písmeno může být použito ve více vyškrtnutých slovech, škrtaná slova se mohou překrývat, slovo v seznamu může být v poli obsaženo vícekrát (pak je potřeba vyškrtat všechny výskyty).

Vstupem programu je zadání osmisměrky. Nejprve je zadané obdélníkové 2D pole s písmeny. Může obsahovat znaky malé a až z nebo znak tečka (nepoužité políčko). Pole musí mít alespoň jeden řádek a alespoň jeden sloupec. Po zadání osmisměrky následuje prázdný řádek a za ním seznam slov k vyhledání. Slova jsou zadaná po jednom na řádku. Seznam slov skončí s koncem vstupu.

Výstupem programu je nalezená tajenka. Výpis může být dlouhý, program jej proto rozdělí na řádky délky 60 znaků + případný zbytek na poslední řádce.

Program musí detekovat nesprávný vstup. Pokud je vstup nesprávný, program to zjistí, vypíše chybové hlášení a ukončí se. Za chybu je považováno:

* pole osmisměrky nemá velikost alespoň 1x1,
* pole osmisměrky není obdélníkového tvaru,
* pole osmisměrky obsahuje znaky jiné než malá písmena a tečku,
* chybí prázdný řádek za zadáním pole osmisměrky,
* slovo v seznamu není v osmisměrce obsaženo (pozor, formát chybového hlášení je zde odlišný, viz ukázka).

Dodržte přesně formát všech výpisů. Výpis Vašeho programu musí přesně odpovídat ukázkám. Testování provádí stroj, který kontroluje výpis na přesnou shodu. Pokud se výpis Vašeho programu liší od referenčního výstupu, je Vaše odpověď považovaná za nesprávnou. Záleží i na mezerách, i na odřádkování.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu a dále je omezena i velikost dostupné paměti. Počítejte s tím, že šířka/délka obdélníku může mít velké rozpětí. Není rozumné paměť pro osmisměrku alokovat staticky. Paměti je ale obecně dostatek pro případné předzpracování osmisměrky nebo hledaných slov. Časový limit je nastaven tak, aby správně implementovaný naivní algoritmus prošel všemi testy kromě testu bonusového. Pro zvládnutí bonusového testu je potřeba použít efektivní algoritmus vyhledávání.