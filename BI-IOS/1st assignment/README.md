Úkol je zaměřen primárně na autolayout a základní práci s views a controls. Úkolem je vytvořit 2 obrazovky - přidání nového postu a profil.

## Nefunkční požadavky
- Maximálně dodržet dodaný grafický návrh a to hlavně rozmístěním prvků
- Co nejpreciznější layout
    - Počítejte s tím, že jakýkoliv text může být prakticky libovolně dlouhý, nikde nesmí nic přetékat apod.
    - Počítejte s různou velikostí zařízení a rotací displeje
    - Pokud bude na landscapu něco přetékat mimo obrazovku dolů, tak je to OK - scroll views ještě neumíme, netrapte se s tím, není to cílem úkolu
- Možno udělat layout v kódu i v interface builderu
- Ideálně začněte až po shlédnutí 5. cvičení
    - řeší se tam přechody mezi obrazovkami a po 5. cvičení budete mít obě obrazovky připravené
    - pokud to budete dělat před pětkou, stačí obě obrazovky úplně samostatně a já si je při kontrole přepnu v kódu nebo ve storyboardu
- **Odevzdání přes MS teams** (edit: stačí si vybrat jednu z variant)
    - Odevzdat zip s kompletním projektem
    - Odevzdat link na váš GitHub repozitář
        - Udělejte si nové private repo a do něj si udělejte mirror tohoto, tady návod: [Duplicating a repository - GitHub Docs](https://docs.github.com/en/free-pro-team@latest/github/creating-cloning-and-archiving-repositories/duplicating-a-repository)
        - Do vašeho private repozitáře vypracujte úkol a přidejte `@janmisar` a `@lukashromadnik`

## Nový post
- Textová tlačítka *Cancel* a *Create*
    - Na tapnutí bude *Cancel* zatím jenom printovat do konzole `cancel tapped`
    - *Create* do konzole vypíše obsah textView (viz níže) a schová klávesnici
- UITextView pro zadání textu
- Label pro zobrazení lokace
- Tlačítko pro výběr lokace
    - na tapnutí zatím pouze vypíše `location tapped`
- Image view pro obrázek, který chceme přidat
    - pokud obrázek ještě není vybrán, zobrazuje se na středu imageview tlačítko *Select photo*
    - tlačítko otevírá `UIImagePickerController`
        - Ten jsme ještě na cvičeních nezmínili, ale po cvičení 5 byste měli mít dostatek znalostí, abyste si s tím poradili
        - V simulatoru nefunguje `sourceType = .camera`, takže klidně stačí použít výběr fotky z knihovny
        - Zdroje:  [Apple Developer Documentation](https://developer.apple.com/documentation/uikit/uiimagepickercontroller), [How to take a photo using the camera and UIImagePickerController](https://www.hackingwithswift.com/example-code/uikit/how-to-take-a-photo-using-the-camera-and-uiimagepickercontroller) nebo jakýkoliv tutoriál, je jich spousta
    - Jakmile je obrázek vybrán, tak tlačítko pro výběr zmizí

## Profil uživatele
- Profilovka
    - použijte jakýkoliv statický obrázek
- Label pro zobrazení username
- Edit button
    - na tapnutí se zobrazí `UIAlertController` s textfieldem
    - v textfieldu je současný username
    - uživatel upraví username, po tapnutí na OK se nová hodnota projeví v labelu
    - Na cviku se neukazovalo, ale najdete opět spoustu zdrojů na internetu
- Label s počtem příspěvků
    - Zatím plně statický text
- Label s popisem profilu
    - Zatím plně statický text
- Grid 6 obrázků
    - použijte libovolné statické obrázky
    - na cviku se neukazovalo, ale doporučuji použít `UIStackView` (opět odkazuji prakticky kamkoliv na internet)
