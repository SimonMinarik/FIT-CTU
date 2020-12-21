Prvním úkolem v implementaci hry The Drake bude vytvoření tříd pro jednotky na hracím plánu. Postupujte přesně podle následujícího zadání.

Pravidla hry, které budete v průběhu jednotlivých úkolů implementovat, najdete zde.

# Zadání úkolu

1. Vytvořte v IntelliJ Java projekt s jedním balíčkem nazvaným thedrake
2. Uvnitř tohoto balíčku vytvořte třídu Offset2D, která bude reprezentovat diskrétní posunutí ve 2D prostoru. To se nám bude hodit na mnoha místech hry pro posouvání se po hrací desce. Souřadnice reprezentujte jako dva public final atributy x, y typu int. Implementuje v této třídě následující metody:
// Konstruktor
public Offset2D(int x, int y)

// Zjištuje, zda se tento offset rovná jinému offsetu
public boolean equalsTo(int x, int y)

// Vrací nový offset, kde y souřadnice má obrácené znaménko
public Offset2D yFlipped()
3. Vytvořte výčtový typ TroopFace s hodnotami AVERS a REVERS. Tento typ určuje lícovou a rubovou stranu jednotky.
4. Vytvořte třídu Troop, která bude představovat bojovou jednotku v naší hře. Každá jednotka má svoje jméno (například "Archer") a takzvaný lícový pivot a rubový pivot. Na obrázku jednotky je pivot označený symbolem připomínajícím i. Souřadnice pivota mohou být rozdílné na lícové a rubové straně jednotky, viz obrázek. Proto potřebujeme lícový a rubový pivot.  
pivots.png 
Třída Troop nechť má všechny atributy private final a implementuje následující metody:
// Hlavní konstruktor
public Troop(String name, Offset2D aversPivot, Offset2D reversPivot)

// Konstruktor, který nastavuje oba pivoty na stejnou hodnotu
public Troop(String name, Offset2D pivot)

// Konstruktor, který nastavuje oba pivoty na hodnotu [1, 1]
public Troop(String name)

// Vrací jméno jednotky
public String name()

// Vrací pivot na zadané straně jednotky
public Offset2D pivot(TroopFace face)
5. Ověřte, že váš kód splňuje testy (stáhněte si níže "Vzorová data"). Spuštějte vždy třídu MainSuite.java.

# Odevzdání úkolu

1. Vytvořte soubor thedrake.zip s přesně touto strukturou složek a souborů
thedrake/
thedrake/Offset2D.java
thedrake/Troop.java
thedrake/TroopFace.java
2. Než budete úkol posílat, seznamte se s pravidly pro odevzdávání úkolů (viz. Moodle). Najdete zde důležité informace nezbytné k tomu, aby byl váš úkol přijat.