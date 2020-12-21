# Evidence výpočetní techniky I.

Úkolem je navrhnout a implementovat sadu tříd, které budou simulovat evidenci počítačového vybavení firmy. Konkrétně budeme ukládat informace o sítích (CNetwork), počítačích (CComputer), jejich procesorech (CCPU), pamětech (CMemory) a discích (CDisk).

Úkol je zaměřen na návrh tříd, kde bude využito dědičnosti, polymorfismu a abstraktních metod. Pokud jsou tyto OOP prostředky použité racionálně, není implementace příliš dlouhá. Naopak, pokud provedete návrh špatně, bude se Vám kód opakovat a implementační soubor bude velký. Zkuste identifikovat základní třídu a vhodně z ní děděním odvoďte podtřídy.

Třídy a jejich rozhraní:

CNetwork
reprezentuje síť. Její rozhraní musí obsahovat:
* konstruktor se jménem sítě,
* destruktor, kopírující konstruktor a operátor = (pokud je potřeba vlastní implementace),
* metodu AddComputer, kterou lze přidávat další počítač do sítě,
* metodu FindComputer, která vrátí odkaz na nalezený počítač zadaného jména nebo neplatný ukazatel, pokud jej nenalezne,
* výstupní operátor, který zobrazí strom počítačů a komponent, jako v ukázce. Počítače jsou vypsané v pořadí přidávání.


CComputer
reprezentuje počítač. Její rozhraní musí obsahovat:
* konstruktor s parametrem jména počítače
* destruktor, kopírující konstruktor a operátor = (pokud je potřeba vlastní implementace),
* metoda AddComponent, která přidá další komponentu počítače,
* metoda AddAddress, která přidá další adresu počítače (řetězec),
* operátor pro výstup, který zobrazí přidělená adresy a komponenty počítače, jako v ukázce. Ve výpisu jsou nejprve uvedené adresy (v pořadí zadání) a za nimi komponenty (v pořadí přidávání).


CCPU
reprezentuje CPU. Její rozhraní musí obsahovat:
* konstruktor s parametrem počtu jader (celé číslo) a frekvencí (celé číslo v MHz),
* destruktor, kopírující konstruktor a operátor = (pokud je potřeba vlastní implementace).


CMemory
reprezentuje RAM. Její rozhraní musí obsahovat:
* konstruktor s parametrem velikosti paměti (celé číslo v MiB),
* destruktor, kopírující konstruktor a operátor = (pokud je potřeba vlastní implementace).


CDisk
reprezentuje úložiště. Její rozhraní musí obsahovat:
* konstruktor s parametry typu disku (symbolická konstanta SSD nebo MAGNETIC deklarovaná ve třídě) a * velikosti disku (celé číslo v GiB),
* destruktor, kopírující konstruktor a operátor = (pokud je potřeba vlastní implementace),
* metodu AddPartition, která přidá informaci o rozdělení disku. Metoda bude mít dva parametry - velikost parcely v GiB a její identifikaci (řetězec). Výpis parcel je v pořadí zadávání.

Odevzdávejte zdrojový kód se implementací tříd CNetwork, CComputer, CCPU, CMemory a CDisk. Do odevzdávaného souboru zahrňte všechny potřebné podpůrné deklarace. Části vkládání hlaviček a Vaše testy ponechte v bloku podmíněného překladu, jak je ukázáno v přiloženém archivu.