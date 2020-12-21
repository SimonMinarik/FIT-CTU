# Katastr nemovitostí

Úkolem je realizovat třídu CLandRegister, která bude implementovat databázi katastru nemovitostí.

Náš zjednodušený katastr si pamatuje seznam pozemků a k nim příslušných vlastníků. Pro každý pozemek si pamatujeme čtveřici údajů: katastrální území (region, řetězec), číslo pozemku v katastrálním území (ID, nezáporné číslo), město (city, řetězec) a adresu (addr, řetězec). K identifikaci pozemku je potřeba buď dvojice údajů (region, ID) nebo dvojice údajů (city, addr). Například pozemek může mít identifikaci region=Dejvice, ID=12345. Tato dvojice údajů pozemek jednoznačně určuje. Samotný údaj region=Dejvice k identifikaci nestačí (v katastrálním území Dejvice může být více pozemků s různými ID), stejně tak nestačí ani ID=12345 (může existovat více pozemků s tímto ID v různých katastrálních územích). Analogicky dvojice city, addr pozemek určuje jednoznačně, ale samotné city nebo samotná addr ne. Při porovnávání řetězců region, city a addr rozlišujeme malá a velká písmena.

Vlastník pozemku je identifikován řetězcem owner. Jeden vlastník může vlastnit mnoho různých pozemků, pozemek musí být vlastněn vždy právě jedním vlastníkem. Nově zadané pozemky jsou vlastněné státem (vlastník je prázdný řetězec). Při porovnávání jmen vlastníků nerozlišujeme malá a velká písmena.

Nad takto definovanými pozemky a vlastníky chceme vybudovat rozhraní pro přidávání a mazání pozemků, nastavování majitelů a dotazování na majitele. K tomu bude sloužit veřejné rozhraní třídy CLandRegister:

Konstruktor bez parametrů.
Tento konstruktor inicializuje instanci třídy tak, že vzniklá instance je zatím prázdná (neobsahuje žádné záznamy).
Destruktor.
Uvolňuje prostředky, které instance alokovala.
Add(city, addr, region, id)
metoda přidá do existující databáze další pozemek. Parametry city a addr reprezentují město a adresu pozemku, parametry region a id udávají identifikaci katastrálního území a číslo pozemku v katastrálním území. Metoda vrací hodnotu true, pokud byl záznam přidán, nebo hodnotu false, pokud přidán nebyl (protože již v databázi existoval záznam se stejnou dvojicí (city,addr) nebo záznam se stejnou dvojicí (region,id(.
Del (city, addr) / Del (region,id)
odstraní záznam z databáze. Parametrem je jednoznačná identifikace pomocí města a dresy (první varianta) nebo pomocí katastrálního území a ID(druhá varianta). Pokud byl záznam skutečně odstraněn, vrátí metoda hodnotu true. Pokud záznam odstraněn nebyl (protože neexistoval pozemek s touto identifikací), vrátí metoda hodnotu false. Vlastnictví pozemku nemá na odstranění vliv. Případný majitel měl špatný den.
GetOwner (city, addr, owner) / GetOwner (region, id, owner)
zjistí majitele zadaného pozemku. Varianty jsou dvě - pozemek je identifikován buď svojí adresou, nebo katastrálním územím a ID. Parametr owner je výstupní, metoda no něj umístí jméno vlastníka. Pokud metoda uspěje, vrací hodnotu true a nastaví výstupní parametr owner. Pokud metoda neuspěje (pozemek neexistuje), vrací hodnotu false a parametr owner ponechá beze změn. Pokud je dotazovaný pozemek vlastněn státem (vlastník je prázdný řetězec), chová se metoda stejně jako u jakéhokoliv jiného vlastníka (vrací true a nastavuje hodnotu owner, zde na prázdný řetězec). Přestože při porovnávání nerozlišujeme malá a velká písmena ve jménu vlastníka, metoda vrátí jméno vlastníka přesně v podobě, v jaké byl zadaný (nelze si tedy interně převést vlastníky např. na malá písmena).
NewOwner (city, addr, owner) / NewOwner (region, id, owner)
nastaví pro zadaný pozemek nového majitele owner (původní majitel je přepsán). Varianty jsou dvě - pozemek je identifikován buď svojí adresou, nebo katastrálním územím a ID. Pokud metoda uspěje, vrací hodnotu true. Pokud metoda neuspěje (pozemek neexistuje, zadaný pozemek je již vlastněn zadaným majitelem), nic v záznamech nemění a vrací hodnotu false.
Count (owner)
zjistí počet pozemků vlastněných zadaným vlastníkem owner. Výsledkem je celé číslo, 0 pokud zadaný vlastník nevlastní žádný z pozemků.
ListByAddr ()
vrátí iterátor (viz níže), kterým půjde procházet seznam všech existujících pozemků. Navrácený iterátor zpřístupní pozemky seřazené vzestupně podle města, pozemky ve stejném městě budou řazené podle adresy.
ListByOwner (owner)
metoda vrátí iterátor (viz níže), kterým půjde procházet seznam pozemků vlastněných zadaným majitelem owner. Navrácený iterátor zpřístupní seznam takto vybraných pozemků v pořadí, ve kterém majitel pozemky získal (od nejdříve získaného). Pokud majitel nevlastní žádné pozemky, bude výsledkem prázdný iterátor (bude okamžitě hlásit AtEnd(), viz níže).
kopírující konstruktor, přiřazení
testovací prostředí nekopíruje instance CLandRegister, tedy není potřeba je implementovat. Můžete je pro dobrý pocit ve zdrojovém kódu zakázat (C++11 konstrukce =delete).
Třída CIterator slouží k procházení seznamu pozemků. V seznamu pozemků vždy pracujeme s jedním vybraným pozemkem, ze kterého můžeme zjišťovat jeho vlastnosti. V seznamu se můžeme pohybovat vpřed a můžeme testovat, zda jsem v seznamu na konci. Jedná se o nejjednodušší variantu iterátoru (forward iterator). Rozhraní iterátoru je:

AtEnd
Metoda zjistí, zda jsme v seznamu došli na poslední položku. Pokud vrací true, pak žádný další záznam již není k dispozici. Pokud vrací false, lze používat metody pro zjišťování vlastností pozemků a můžeme se pohybovat na další záznam. Typické použití iterátoru v podmínce while cyklu testuje podmínku while ( ! it . AtEnd () ), v těle cyklu zpřístupňuje vlastnosti pozemku a na konci těla cyklu volá it . Next() k posunu na další záznam.
Next
Metoda posune iterátor na další pozemek v seznamu.
City
Metoda zjistí jméno města aktuálně vybraného pozemku.
Addr
Metoda zjistí adresu aktuálně vybraného pozemku.
Region
Metoda zjistí katastrální území vybraného pozemku.
ID
Metoda zjistí číslo pozemku v katastrálním území.
Owner
Metoda zjistí vlastníka vybraného pozemku.
konstruktor, destruktor, kopírující konstruktor
testovací prostředí iterátory nekopíruje, používá je pouze pro jednorázový průchod seznamem vrácených pozemků. Instance iterátoru jsou vyráběné pouze Vašimi metodami, tyto instance jsou vracené jako návratové hodnoty metod ListByAddr / ListByOwner. Při navracení z těchto hodnot mohou být volané kopírující nebo přesouvací konstruktory, záleží na implementaci. Obecně je lepší v iterátoru neukládat dynamicky alokovaná data. Pro implementaci stačí mít v iterátoru dvě hodnoty (pozici v poli a odkaz na CLandRegister). Implementací kopírujícího konstruktoru se pak nemusíte zdržovat.
modifikace
testovací prostředí neprovádí žádné modifikace instance CLandRegister v době, kdy používá CIterator. Tedy můžete se spolehnout, že nejprve iterátor dosáhne AtEnd a teprve následně může být měněna instance CLandRegister. Díky tomu si iterátor nemusí data kopírovat z CLandRegister, ale může na ně pouze odkazovat.
Odevzdávejte soubor, který obsahuje implementovanou třídy CLandRegister a CIterator. Třídy musí splňovat veřejné rozhraní podle ukázky - pokud Vámi odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. Do tříd si ale můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. Dále si do odevzdávaného souboru můžete doplnit další podpůrné funkce nebo třídy. Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní), tak i definice metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline nebo odděleně. Odevzdávaný soubor nesmí obsahovat vkládání hlavičkových souborů a funkci main (funkce main a vkládání hlavičkových souborů může zůstat, ale pouze obalené direktivami podmíněného překladu). Za základ implementace použijte přiložený zdrojový soubor.

Rozhraní třídy obsahuje řadu metod ve dvou variantách, které se liší pouze způsobem identifikace pozemku. Je vhodné věnovat nenulový čas návrhu třídy tak, abyste všechen výkonný kód nekopírovali 2x (např. realizujte privátní metody, které budete volat z více veřejných metod).

Implementace třídy musí být efektivní z hlediska nároků na čas i nároků na paměť. Jednoduché lineární řešení nestačí (pro testovací data vyžaduje čas přes 5 minut). Předpokládejte, že vkládání a mazání pozemků jsou řádově méně časté než ostatní operace. Častá jsou volání NewOwner a hlavně GetOwner, jejich časová složitost musí být lepší než lineární (např. logaritmická nebo amortizovaná konstantní). Dále, metody pro vytvoření iterátorů a práci se seznamem pozemků by též měly být efektivní.

V povinných testech se metody Count a ListByOwner volají málo často, tedy nemusí být příliš efektivní (pro úspěch v povinných testech stačí složitost lineární nebo n log n, pro bonusový test je potřeba složitost lepší než lineární. Pokud nechcete vymýšlet efektivní algoritmus pro bonusový test, zaměřte se spíše na to, aby volání NewOwner byla efektivní i za cenu méně efektivní metody Count.

Bonusový test lze vyřešit několika způsoby. Při návrhu řešení můžete využít znalosti, že vlastníci se často opakují.

Pro uložení hodnot alokujte pole dynamicky případně použijte STL. Pozor, pokud budete pole alokovat ve vlastní režii, zvolte počáteční velikost malou (např. tisíc prvků) a velikost zvětšujte/zmenšujte podle potřeby. Při zaplnění pole není vhodné alokovat nové pole větší pouze o jednu hodnotu, takový postup má obrovskou režii na kopírování obsahu. Je rozumné pole rozšiřovat s krokem řádově tisíců prvků, nebo geometrickou řadou s kvocientem ~1.5 až 2.

Pokud budete používat STL, nemusíte se starat o problémy s alokací. Pozor - k dispozici máte pouze část STL (viz hlavičkové soubory v přiložené ukázce). Tedy například kontejnery map / unordered_map / set / unordered_set / ... nejsou k dispozici.

V přiloženém zdrojovém kódu jsou obsažené základní testy. Tyto testy zdaleka nepokrývají všechny situace, pro odladění třídy je budete muset rozšířit. Upozorňujeme, že testy obsažené v odevzdaných zdrojových kódech považujeme za nedílnou součást Vašeho řešení. Pokud v odevzdaném řešení necháte cizí testy, může být práce vyhodnocena jako opsaná.

Správné řešení této úlohy, které splní závazné a nepovinné testy na 100%, může být odevzdáno k code review. (Tedy pro code review nemusíte zvládnout bonusový test.)