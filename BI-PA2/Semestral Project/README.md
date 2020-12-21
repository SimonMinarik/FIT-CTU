# Grafické RPG

Naprogramujte engine pro grafické RPG

Váš engine:

1. ze souboru nahraje definici světa (mapu, předměty, příšery, ...)
2. umožní vytvořit herní postavu (její atributy a schopnosti) a následnou hru
3. implementuje jednoduchý soubojový systém a inventář
4. umožňuje ukládat a načítat rozehrané hry

Engine může fungovat jako real-time hra, či tahová hra.

Jak může vypadat mapa?

# označuje zeď, T označuje truhlu s pokladem, > označuje pozici (směr otočení) hráče.


###################
# T   #      #    #
#           ###   #
#     ##   #      #
#     #       # > #
###################
Kde lze využít polymorfismus? (doporučené)

* Soubojové vlastnosti: postava, příšera, stroj (např. past, bomba,...)
* Efekty akcí: souboje, události (pád ze stromu,...), přechod do jiné místnosti
* Inventář: postava, batoh, toulec, kapsa
* Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), ...

Ukázky:

* https://en.wikipedia.org/wiki/Hack_(video_game)
* https://www.mobygames.com/game/heroes-of-might-and-magic
* http://www.drd2.cz/
* Dungeons & Dragons