Úkol je zaměřen na procvičení networkingu, architektury a práce s mapou. Úkolem je vytvořit novou obrazovku s mapou, na která budou vidět všechny posty, které mají location.

## Nefunkční požadavky
- Vycházejte z **aktuálního masteru**
- Dbejte na dodržení patternu MVVM podle cvičení
- Opět dbejte na správný layout
	- dynamická délka obsahu, různé velikosti zařízení, landscape atd.
	- za všech okolností by to mělo správně fungovat
- **Odevzdání přes MS teams** (edit: stačí si vybrat jednu z variant)
	- Odevzdat zip s kompletním projektem
	- Odevzdat link na váš GitHub repozitář
		- Udělejte si nové private repo a do něj si udělejte mirror tohoto, tady návod: [Duplicating a repository - GitHub Docs](https://docs.github.com/en/free-pro-team@latest/github/creating-cloning-and-archiving-repositories/duplicating-a-repository)
		- Do vašeho private repozitáře vypracujte úkol a přidejte `@janmisar` a `@lukashromadnik`

## Mapa
- Nová obrazovka, která bude uprostřed tabbaru (mezi feed a profile)
- Obrazovka obsahuje fullscreen mapu, na které jsou zobrazeny všechny posty, které mají nějakou lat/lon
- Posty se budou stahovat z API stejně jako na feedu, akorát s použitím query stringu `?filter=lat,gt,0&filter=lon,gt,0` - tak získáme vyfiltrované posty, které mají lokaci
- Pro zobrazení postů na mapě použijte systémové piny  `MKMarkerAnnotationView`
	- jako ikonu na pin použijte SF symbol `camera`
- Po načtení postů z API se mapa zazoomuje tak, aby byly vidět všechny posty
- Při kliknutí na pin
	- mapa se vycentruje na pin (pin bude uprostřed obrazovky)
	- zobrazí se callout
		- vlevo miniatura fotky (50x50pt)
		- title je username
		- subtitle je location
		- vpravo je tlačítko s ikonou šipky (`chevron.right`)
			- toto tlačítko otevírá obrazovku s detailem postu

## Detail postu
- Má zcela totožné UI jako post ve feedu
	- Pokud bude třeba, tak upravte podle potřeby, ale **využijte stejné view pro post jako ve feedu** - nekopírujte kód
- Počítejte s tím, že post má unlimited description, takže může být teoreticky velmi dlouhý
- Data pro detail nepředávejte z mapy, ale stáhněte z API
	- za URL pro všechny posty stačí přidat `/{id_postu}`
- na obrazovce je stejně jako na feedu refreshControl, kterým můžu aktualizovat data z API