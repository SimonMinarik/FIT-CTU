(define (problem najdenie-stastia)
        (:domain namornik)

        (:objects les reka pristav hospoda mesto namorni-akademie more majak ostrov
        nameteny opily zavisly seznameny-s-paseraky zoceleny oslnivy kapitan stastny
        zrnko mince cihla
        plavidlo clun fregata karavela
        drevo alkohol kokos medvedi-kuze pochybne-znamosti dobre-znamosti mapka zaznam-v-rejstriku perla kvetina prstynek
        kokain oslnena-divka porazeni-pirati)

        (:init (pevnina les reka)
            (pevnina reka les)
            (pevnina reka pristav)
            (pevnina pristav reka)
            (pevnina pristav hospoda)
            (pevnina hospoda pristav)
            (pevnina pristav mesto)
            (pevnina mesto pristav)
            (voda pristav more)
            (voda more pristav)
            (voda pristav majak)
            (voda majak pristav)
            (voda majak more)
            (voda more majak)
            (voda more ostrov)
            (voda ostrov more)
            (nachadza-sa-v pristav))

        (:goal (and(je stastny))))