(define (domain namornik)

    (:predicates
        (voda ?x ?y)
        (pevnina ?x ?y)
        (nachadza-sa-v ?a)
        (je ?b)
        (ma ?b))

        (:action plavit-sa
            :parameters (?odkial ?kam)
            :precondition (and (ma plavidlo) (voda ?odkial ?kam) (nachadza-sa-v ?odkial))
            :effect (and (nachadza-sa-v ?kam)
                (not (nachadza-sa-v ?odkial))))

        (:action prechadzat-sa
            :parameters (?odkial ?kam)
            :precondition (and (pevnina ?odkial ?kam) (nachadza-sa-v ?odkial))
            :effect (and (nachadza-sa-v ?kam)
                (not (nachadza-sa-v ?odkial))))

        (:action postavit-clun
            :parameters ()
            :precondition (and (ma drevo))
            :effect (and (ma clun)
                (ma plavidlo)
                (not (ma drevo))))

        (:action postavit-fregatu
            :parameters ()
            :precondition (and (ma clun) (ma drevo) (ma zrnko))
            :effect (and (ma fregata)
                (not (ma clun))
                (not (ma drevo))
                (not (ma zrnko))))

        (:action postavit-karavelu
            :parameters ()
            :precondition (and (ma clun) (ma drevo) (ma mince))
            :effect (and (ma karavela)
                (not (ma drevo))
                (not (ma clun))
                (not (ma mince))))

        (:action dostat-se-do-nalady
            :parameters ()
            :precondition (and (ma alkohol) (not (je nameteny)) (not (je opily)))
            :effect (and (je nameteny)
                (not (ma alkohol))))

        (:action opit-se
            :parameters ()
            :precondition (and (ma alkohol) (je nameteny) (not (je opily)))
            :effect (and (je opily)
                (not (je nameteny))
                (not (ma alkohol))))

        (:action stat-se-zavislym
            :parameters ()
            :precondition (and (ma alkohol) (je opily))
            :effect (and (je zavisly)
                (not (ma alkohol))))

        (:action kacet-drevo
            :parameters ()
            :precondition (and (nachadza-sa-v les))
            :effect (and (ma drevo)))

        (:action trhat-kvetiny
            :parameters ()
            :precondition (and (nachadza-sa-v les))
            :effect (and (ma kvetina)))

        (:action porvat-se-s-medvedem
            :parameters ()
            :precondition (and (nachadza-sa-v les))
            :effect (and (je oslnivy)
                (je zoceleny)
                (ma medvedi-kuze)))

        (:action setkat-se-s-kouzelnym-dedeckem
            :parameters ()
            :precondition (and (nachadza-sa-v les) (ma alkohol))
            :effect (and (ma mapka)
                (ma pochybne-znamosti)
                (not (ma alkohol))))

        (:action ryzovat-zlato
            :parameters ()
            :precondition (and (nachadza-sa-v reka))
            :effect (and (ma zrnko)))

        (:action doprat-si-ledovou-koupel-v-rece
            :parameters ()
            :precondition (and (nachadza-sa-v reka))
            :effect (and (not (je nameteny))
                (not (je opily))))

        (:action pracovat
            :parameters ()
            :precondition (and (nachadza-sa-v pristav))
            :effect (and (ma zrnko)))

        (:action obchodovat-s-kokosy
            :parameters ()
            :precondition (and (nachadza-sa-v pristav) (ma kokos))
            :effect (and (not (ma kokos))
                (ma mince)))

        (:action obchodovat-s-medvedi-kuzi
            :parameters ()
            :precondition (and (nachadza-sa-v pristav) (ma medvedi-kuze))
            :effect (and (not (ma medvedi-kuze))
                (ma mince)))

        (:action seznamit-se-s-paseraky
            :parameters ()
            :precondition (and (nachadza-sa-v pristav) (ma pochybne-znamosti) (ma cihla))
            :effect (and (je seznameny-s-paseraky)))

        (:action koupit-alkohol
            :parameters ()
            :precondition (and (nachadza-sa-v hospoda) (ma zrnko))
            :effect (and (ma alkohol)
                (not (ma zrnko))))

        (:action zaplatit-rundu-hospode
            :parameters ()
            :precondition (and (nachadza-sa-v hospoda) (ma mince))
            :effect (and (ma dobre-znamosti)
                (not (ma mince))))

        (:action bitka
            :parameters ()
            :precondition (and (nachadza-sa-v hospoda) (je nameteny))
            :effect (and (je zoceleny)))

        (:action stradat-v-bance
            :parameters ()
            :precondition (and (nachadza-sa-v mesto) (ma zrnko))
            :effect (and (ma mince)
                (not (ma zrnko))
                (ma dobre-znamosti)))

        (:action investovat-v-bance
            :parameters ()
            :precondition (and (nachadza-sa-v mesto) (ma mince))
            :effect (and (ma cihla)
                (not (ma mince))
                (ma dobre-znamosti)))

        (:action pustit-se-do-zlodejiny
            :parameters ()
            :precondition (and (nachadza-sa-v mesto))
            :effect (and (ma mince)
                (ma zaznam-v-rejstriku)))

        (:action koupit-si-odpustek
            :parameters ()
            :precondition (and (nachadza-sa-v mesto) (ma zrnko))
            :effect (and (not (ma zaznam-v-rejstriku))
                (not (ma zrnko))))

        (:action venovat-se-verejnoprospesnym-pracem
            :parameters ()
            :precondition (and (nachadza-sa-v mesto))
            :effect (and (not (ma zaznam-v-rejstriku))
                (je nameteny)))

        (:action vystudovat-akademii
            :parameters ()
            :precondition (and (nachadza-sa-v namorni-akademie) (not (ma zaznam-v-rejstriku)) (ma mince))
            :effect (and (not (ma mince))
                (je kapitan)
                (je oslnivy)))

        (:action prepadeni-pirati
            :parameters ()
            :precondition (and (nachadza-sa-v more) (not (je zoceleny)))
            :effect (and (je zoceleny)
                (not (ma zrnko))
                (not (ma mince))
                (not (ma cihla))
                (not (ma fregata))
                (not (ma karavela))
                (ma clun)))

        (:action pridat-se-k-piratum
            :parameters ()
            :precondition (and (nachadza-sa-v more) (ma pochybne-znamosti))
            :effect (and (je nameteny)))

        (:action porazit-piraty
            :parameters ()
            :precondition (and (nachadza-sa-v more) (je zoceleny) (ma karavela))
            :effect (and (ma clun)
                (ma fregata)
                (ma zrnko)
                (ma mince)
                (ma cihla)
                (je oslnivy)
                (ma porazeni-pirati)))

        (:action potopit-se-pro-perlu
            :parameters ()
            :precondition (and (nachadza-sa-v more))
            :effect (and (ma perla)))

        (:action doprat-si-ledovou-koupel-v-mori
            :parameters ()
            :precondition (and (nachadza-sa-v more))
            :effect (and (not (je nameteny))
                (not (je opily))))

        (:action oslnit-divku
            :parameters ()
            :precondition (and (nachadza-sa-v majak) (je oslnivy))
            :effect (and (ma oslnena-divka)))

        (:action sbirat-kokosy
            :parameters ()
            :precondition (and (nachadza-sa-v ostrov))
            :effect (and (ma kokos)))

        (:action kacet-drivi
            :parameters ()
            :precondition (and (nachadza-sa-v ostrov))
            :effect (and (ma drevo)))

        (:action najit-a-vybrat-skrys-s-kokainem
            :parameters ()
            :precondition (and (nachadza-sa-v ostrov) (ma mapka))
            :effect (and (ma kokain)))

        (:action vyrobit-prstynek
            :parameters ()
            :precondition (and (ma cihla) (ma perla))
            :effect (and (ma prstynek)))

        (:action ozenit-se
            :parameters ()
            :precondition (and (ma oslnena-divka) (ma prstynek) (ma kvetina) (ma dobre-znamosti) (not (ma zaznam-v-rejstriku)) (nachadza-sa-v ostrov) (not (je opily)) (not (je zavisly)))
            :effect (and (je stastny)))

        (:action stat-se-admiralem
            :parameters ()
            :precondition (and (je kapitan) (ma porazeni-pirati) (nachadza-sa-v namorni-akademie) (not (je nameteny)) (not (je opily)))
            :effect (and (je stastny)))

        (:action dat-se-na-kokain
            :parameters ()
            :precondition (and (ma kokain) (je zavisly) (ma fregata) (je seznameny-s-paseraky) (ma cihla))
            :effect (and (je stastny))))