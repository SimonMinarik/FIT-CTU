# Trojúhelníky #2

Úkolem je vytvořit program, který bude porovnávat dvojice trojúhelníků. Úloha je rozšířením jednodušší varianty, umožňuje zadávat vstupní trojúhelníky buď pomocí souřadnic vrcholů nebo pomocí délek stran. Doporučujeme nejprve řešit úlohu jednodušší.

V rovině jsou zadané 2 trojúhelníky. Každý trojúhelník je zadán buď pomocí trojice svých vrcholů, nebo pomocí délek svých stran:

* trojúhelník určený pomocí svých vrcholů je zadán jako trojice souřadnic oddělená čárkami a uzavřená do složených závorek. Každá souřadnice je tvořena dvojicí desetinných čísel v hranatých závorkách, složky souřadnice jsou oddělené středníkem. Např.:
* { [ 1.5; 2 ], [3;4.2], [ 0.5 ; 0.6 ] }
* trojúhelník určený pomocí délky svých stran je zadán jako trojice desetinných čísel, tato čísla jsou oddělená čárkami a celá trojice je umístěna do složených závorek. Např.:
* {2.1, 3, 3.4}
Program přečte zadané trojúhelníky ze svého standardního vstupu a rozhodne se pro jednu z variant:
* zda zadaný vstup tvoří trojúhelník (zadaná trojice bodů netvoří trojúhelník, pokud body leží na jedné přímce, strany musí splňovat trojúhelníkovou nerovnost),
* zda jsou zadané trojúhelníky shodné,
* zda jsou zadané trojúhelníky liší, ale mají stejný obvod, nebo
* zda jsou zadané trojúhelníky zcela odlišné.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

* nečíselné zadání souřadnic nebo délek stran (neplatné desetinné číslo),
* chybějící souřadnice nebo délka strany,
* chybějící nebo přebývající oddělovače (složené závorky, hranaté závorky, čárky, středníky).