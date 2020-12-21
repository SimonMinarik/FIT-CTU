V tomto úkolu implementujeme ukládání stavu hry do formátu JSON.

# Zadání úkolu

1. Pokračujte v Java projektu, který jste vytvořili v předchozím úkolu.
2. Z přípravy (stáhněte si níže "Vzorová data") si stáhněte rozhraní JSONSerializable. Toto rozhraní obsahuje metodu, jejímž úkolem je zapsat do streamu reprezentci objektu ve formátu JSON. Budeme chtít, aby všechny třídy, které se mají uložit do JSONu, implementovaly toto rozhraní.
3. Hlavní třída, která implementuje rozhranní JSONSerializable, je třída GameState. Implementujte metodu toJSON() tak, by uložila stav hry ve formátu JSON do připraveného. Ilustraci toho, jak má formát vypadat najdete v souboru states.zip. Archiv obsahuje 20 po sobě jdoucích stavů jedné hry odehrané od začátku až do konce. Z těchto souborů můžete vypozorovat, jak má vypadat datový formát. Pozor, soubory v archivu jsou zformátovány, aby se hezky četly. Testy, kterými musí váš kód projít, používají neformátovaný JSON - bez bílých znaků.
4. Pokud je metoda přiliš dlouhá, je dobré práci rozdělit na menší, snáze spravovatelné, celky. Navíc by si každý objekt měl řešit jen svůj stav, ne stav ostatních objektů. Nevytvářejte proto veškerý kód v metodě toJSON() třídy GameState, ale implementujte rozhraní JSONSerializable i ve třídách GameResult, BoardPos, PlayingSide, TroopFace, Troop, TroopTile, BoardTroops, Army, BoardTile a Board. Každá metoda toJSON() by měla v maximální možné míře využívat metody toJSON() objektů, které chce vypsat.
5. Pozor na to, že jediné metody třídy PrintWriter, které dělají automaticky flush, jsou pouze metody println a printf. Pokud použijete pro výpis jiné metody, možná neuvidíte před uzavřením proudu žádný výstup.
6. Ověřte, že váš kód splňuje testy (stáhněte si níže "Vzorová data"). Spuštějte vždy třídu MainSuite.java.
7. Tip 1: Políčka v Board by měla být vypsána po řádcích, tj. nejdříve všechny sloupce 1. řádku, za to sloupce 2. řádku atd. U souřadnic ve formátu i,j představuje i sloupec a j řádek. U souřadnic ve formátu a1 představuje písmeno řádek číslo sloupec.
8. Tip 2: Jednotky ve třídě BoardTroops musí být vypsány v pořadí dle jejich pozice po řádkách, tedy např. a1, a3, b1, c4, d1, d2. Možností, jak toho docílit, je několik. Například můžete nejdříve získat kolekci klíčů z mapy troopMap (podívejte se na on-line dokumentaci interface Map), tyto klíče lexikograficky seřadit (nebo uložit do kolekce, ve které jsou seřazeny automaticky) a v tomto pořadí ty klíče projít a ptát se troopMap na jednotlivé položky pod těmity klíči.

# Odevzdání úkolu

1. Vytvořte soubor thedrake.zip s přesně touto strukturou složek a souborů
/thedrake/
/thedrake/Army.java
/thedrake/Board.java
/thedrake/BoardMove.java
/thedrake/BoardPos.java
/thedrake/BoardTile.java
/thedrake/BoardTroops.java
/thedrake/CaptureOnly.java
/thedrake/GameResult.java
/thedrake/GameState.java
/thedrake/JSONSerializable.java
/thedrake/Move.java
/thedrake/Offset2D.java
/thedrake/PlaceFromStack.java
/thedrake/PlayingSide.java
/thedrake/PositionFactory.java
/thedrake/ShiftAction.java
/thedrake/SlideAction.java
/thedrake/StandardDrakeSetup.java
/thedrake/StepAndCapture.java
/thedrake/StepOnly.java
/thedrake/StrikeAction.java
/thedrake/Tile.java
/thedrake/TilePos.java
/thedrake/Troop.java
/thedrake/TroopAction.java
/thedrake/TroopFace.java
/thedrake/TroopTile.java
2. Než budete úkol posílat, seznamte se s pravidly pro odevzdávání úkolů (viz. Moodle). Najdete zde důležité informace nezbytné k tomu, aby byl váš úkol přijat.