Po hezky strávených prázdninách jste se opět vrátili do školy. Bohužel se vám však nepodařilo sestavit dobrý rozvrh, a tak valnou část týdne nemáte příliš času skočit si na oběd. Počítali jste ovšem s tím, že rychlá otočka v menze vám nezabere více než pár minut. Jaké však bylo vaše překvapení, když jste při první návštěvě menzy strávili hodinu ve frontě, neboť celý kampus je přeplněný zmateně pobíhajícími prváky. Vy už naštěstí vyjukaní bažanti nejste, a tak si můžete při bitvě o výdejní okénko pomoci špinavými triky.

Budete se pohybovat v menze, kde jsou dvě fronty, které se vůbec nehýbou, a vaším úkolem bude dostat se k výdejnímu okénku za co nejkratší čas. Za jednu jednotku času můžete vykonat jednu z následujících akcí:

1. buď se předběhnout v rámci fronty, ve které stojíte (tj. posunout se o jedno místo dopředu),
2. přepustit své místo a posunout se opět v téže frontě o jedno místo dozadu,
3. nebo můžete využít svých známostí a vyměnit si místa s kamarádem, který stojí ve vedlejší frontě o na vstupu zadaný počet míst před vámi.


V obou frontách samozřejmě stojí pro vás nevhodní lidé, se kterými byste se neradi dostali do křížku — např. profesoři, či spolužáci, kteří v rámci tělocviku pravidelně navštěvují posilovnu. Na tato místa ve frontě se proto přemístit nemůžete (a to ani tehdy, pokud byste se tam dostali přepuštěním svého lepšího místa). Navíc je zapotřebí jednat rychle, neboť podlahu v menze brzy začne vytírat uklízečka. Na již vytřené podlaze se v žádném případě nesmíte vyskytnout.


K dispozici máte na vstupu délku front (ta je stejná pro obě), konkrétní počet míst, o který můžete přeskakovat do vedlejší fronty, a mapu front s vyznačenými místy, kde stojí pro výměnu nevhodní lidé. Za dosažení výdejního okénka se počítá dosažení libovolného místa za koncem libovolné fronty. Pohyb za konec fronty k výdejnímu okénku je vždy možný, a to na libovolnou pozici za koncem fronty. Přeskakování do vedlejší fronty lze pouze právě o zadaný počet míst na vstupu, nikoliv o méně. To znamená, že lze-li přeskakovat do vedlejší fronty o K míst, můžete se z pozice X v jedné frontě přesunout na pozici X + K ve druhé frontě. Po vykonání libovolné akce zůstává délka front stále stejná (vždy dojde k prohození dvou lidí) a stejně tak se nemění pozice, na kterých stojí nevhodní lidé (prohození vždy probíhá mezi vámi na pozici, kam se dalo dostat a mezi člověkem vhodným pro výměnu pozice). Uklízečka vytírá podlahu v menze tím způsobem, že v čase i vytře podlahu na i-tých pozicích od začátků obou front. Nikdy se tak v čase i nesmíte vyskytnout na i-té, či nižší, pozici od začátku fronty. Čas začíná na hodnotě 0 a zvyšuje se o 1 vždy poté, co vykonáte jednu akci. Jako první tedy vykonáte jednu akci, poté uklízečka vytře podlahu na pozicích 1. Poté opět vykonáte akci a následně uklízečka vytře na pozicích 2 atd... Začínáte vždy v levé frontě na první pozici (na té nikdy nebude stát nevhodný člověk). Může se stát, že k výdejnímu okénku se nebude žádnou posloupností kroků možné dostat.

### Formát vstupu:

* Na prvním řádku jsou dvě čísla; číslo N udávající délku front a číslo K udávající počet míst, o které můžete přeskakovat do vedlejší fronty. Můžete se spolehnout, že platí 1 ≤ K ≤ N.
* Na druhém řádku a třetím řádku jsou postupně popisy levé a pravé fronty (v tomto pořadí). Popis jedné fronty je řetězec délky N složený ze znaků '.' (místo kam se můžete přesunout) a ze znaků 'x' (místo, kde stojí nevhodný člověk a kam se tedy nemůžete přesunout).
* Pozice ve frontách jsou číslovány od jedničky, a mají tedy čísla 1, ..., N. Za dosažení výdejního okénka se tedy počítá dosažení pomyslné pozice N + 1 či vyšší v libovolné z front.
* Můžete předpokládat, že vstup je korektní.

### Formát výstupu:

Výstup sestává z jediného řádku. Existuje-li řešení jak se dostat za konec front, vypište nejmenší počet akcí, který je k tomu potřeba. Neexistuje-li řešení, vypište -1.

### Bodové podmínky:

1. Pro splnění povinných testů (test základními a malými daty) je zapotřebí, aby program fungoval korektně pro fronty o délce nejvýše 20.
2. Pro splnění testu středními daty musí program splnit časový a paměťový limit pro fronty o délce nejvýše 1 000.
3. Pro splnění testu velkými daty musí program splnit časový a paměťový limit pro fronty o délce nejvýše 100 000.

### Ukázka práce programu:

### Příklad vstupu 1:
5 2
....x
.xx.x

### Příklad výstupu 1:
3

### Příklad vstupu 2:
10 4
.xx.x...xx
x.x....x..

### Příklad výstupu 2:
4

### Příklad vstupu 3:
5 1
..x..
..xx.

### Příklad výstupu 3:
-1