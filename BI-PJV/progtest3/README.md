V tomto úkolu implementujeme pohyb jednotek na hracím plánu.

Pravidla hry, které budete v průběhu jednotlivých úkolů implementovat, najdete zde.

# Zadání úkolu

## 1. Třída BoardTroops

Třída BoardTroops je nejdůležitější třída celé hry, neboť se stará o jednotky nacházející se na hracím plánu. Stav hry si udržuje instanci této třídy pro každého hráče. Tedy jedna instance této třídy drží jednotky pouze jedné strany (modré nebo oranžové).

Stáhněte si šablonu třídy BoardTroops z přípravy (stáhněte si níže "Vzorová data"). Třída obsahuje tyto atributy.

* Barvu jednotek, za kterou hráč hraje: playingSide,
* mapu, která mapuje pozice na hrací desce na konkrétní dlaždice typu TroopTile: troopMap,
* pozici vůdce na hracím plánu: leaderPosition,
* počet už položených stráží: guards.
Třída má dva konstruktory, jeden primární, který obdrží všechny nezbytné parametry a sekundární konstruktor

public BoardTroops(PlayingSide playingSide)
který vytvoří instanci, která nemá žádné jednotky (můžete použít Collections.emptyMap), žádné stráže a pozice vůdce je TilePos.OFF_BOARD.

Metody této třídy umožňují s jednotkami hýbat po hracím plánu podle pravidel hry. Při hýbání s jednotkami musíme sledovat pozici vůdce, protože podle ní pak poznáme, jestli vůdce někdo vyhodil.

public Optional<TroopTile> at(TilePos pos)
Vrací dlaždici na zadané pozici, nebo Optional.empty(), pokud na této pozici žádné dlaždice není.

public PlayingSide playingSide()
Vrací barvu hráče

public TilePos leaderPosition()
Vrací aktální pozici vůdce. Pokud vůdce ještě není nasazen, vrací TilePos.OFF_BOARD.

public int guards()
Vrací počet nasazených stráží. Stráží je vždy buď 0, 1 nebo 2.

public boolean isLeaderPlaced()
Vrací True pokud je vůdce již nasazen, jinak False.

public boolean isPlacingGuards()
Vrací True pokud se zrovna nasazují stráže. Stráže se nasazují, pokud je již nasazen vůdce. Vůdce je vždy první jednotka nasazená do hry, druhá a třetí jsou stráže. Jakmile je nasazena třetí jednotka, fáze nasazování stráží končí.

public Set<Board.Pos> troopPositions()
Vrací množinu všech pozic, které jsou obsazené nějakou dlaždicí s jednotkou.

public BoardTroops placeTroop(Troop troop, BoardPos target)
Vrací novou instanci BoardTroops s novou dlaždicí TroopTile na pozici target obsahující jednotku troop lícovou stranou nahoru. Tato metoda vyhazuje výjimku IllegalArgumentException, pokud je již zadaná pozice obsazena jinou dlaždicí.

Pokud pomocí této metody stavíme úplně první jednotku, bere se tato jednotka jako vůdce a je potřeba nastavit pozici leaderPosition. Tímto hra přechází do fáze stavění stráží.

Pokud pomocí této metody stavíme druhou a třetí jednotku, jsme ve fázi stavění stráží. Tato fáze konči ve chvíli, kdy jsou obě stráže postaveny.

public BoardTroops troopStep(BoardPos origin, BoardPos target)
Vrací novou instanci BoardTroops s dlaždicí TroopTile na pozici origin posunutou na pozici target a otočenou na opačnou stranu. Tato metoda vyhazuje výjimku IllegalStateException pokud jsme ve stavu stavění vůdce, nebo stavění stráží, neboť v těchto fázích nelze ješte s dlaždicemi pohybovat. Metoda dále vyhazuje výjimku IllegalArgumentException pokud je pozice origin prázdná nebo pozice target již obsazená.

Pozor, že pokud pomocí této metody pohybujeme s vůdce, je třeba aktualizovat jeho pozici.

public BoardTroops troopFlip(BoardPos origin)
Vrací novou instanci BoardTroops s novou dlaždicí TroopTile na pozici origin otočenou na obrácenou stranu. Tato metoda je již implementována pro vaši inspiraci. Podobně jako metoda troopStep vyhazuje výjimku IllegalStateException, pokud jsme ve stavu stavění vůdce, nebo stavění střáží. Dále vyhazuje výjimku IllegalArgumentException pokud je pozice origin prázdná.

public BoardTroops removeTroop(BoardPos target)
Vrací novou instanci BoardTroops s odstraněnou dlaždicí z pozice target Podobně jako metoda troopStep vyhazuje výjimku IllegalStateException, pokud jsme ve stavu stavění vůdce, nebo stavění střáží. Dále vyhazuje výjimku IllegalArgumentException pokud je pozice target prázdná.

Pozor, pokud pomocí této metody odstraňujeme vůdce, je třeba jeho pozici nastavit zpět na TilePos.OFF_BOARD.

## 2. Třída Army

Třída Army představuje celou armádu jednoho hráče, tedy nejen jednotky na hracím plánu, ale též zajaté jednotky a jednotky na zásobníku. Zajaté jednotky a zásobník jsou reprezentované jako seznamy. Jednotky na hracím plánu spravuje instance třídy BoardTroops.

## 3. Testy

Ověřte, že váš kód splňuje testy (stáhněte si níže "Vzorová data"). Spuštějte vždy třídu MainSuite.java.

# Odevzdání úkolu

1. Vytvořte soubor thedrake.zip s přesně touto strukturou složek a souborů
/thedrake/
/thedrake/Army.java
/thedrake/Board.java
/thedrake/BoardPos.java
/thedrake/BoardTile.java
/thedrake/BoardTroops.java
/thedrake/Offset2D.java
/thedrake/PlayingSide.java
/thedrake/PositionFactory.java
/thedrake/Tile.java
/thedrake/TilePos.java
/thedrake/Troop.java
/thedrake/TroopFace.java
/thedrake/TroopTile.java
2. Než budete úkol posílat, seznamte se s pravidly pro odevzdávání úkolů (viz. Moodle). Najdete zde důležité informace nezbytné k tomu, aby byl váš úkol přijat.