-- Generated by Oracle SQL Developer Data Modeler 4.1.3.901
--   at:        2017-05-23 16:42:17 CEST
--   site:      Oracle Database 11g
--   type:      Oracle Database 11g
 
prompt #---------------------#
prompt #- Pomocne procedury -#
prompt #---------------------#
 
create or replace procedure SMAZ_VSECHNY_TABULKY AS
-- pokud v logu bude uvedeno, ze nektery objekt nebyl zrusen, protoze na nej jiny jeste existujici objekt stavi, spust proceduru opakovane, dokud se nezrusi vse
begin
  for iRec in 
    (select distinct OBJECT_TYPE, OBJECT_NAME,
      'drop '||OBJECT_TYPE||' "'||OBJECT_NAME||'"'||
      case OBJECT_TYPE when 'TABLE' then ' cascade constraints purge' else ' ' end as PRIKAZ
    from USER_OBJECTS where OBJECT_NAME not in ('SMAZ_VSECHNY_TABULKY', 'VYPNI_CIZI_KLICE', 'ZAPNI_CIZI_KLICE', 'VYMAZ_DATA_VSECH_TABULEK')
    ) loop
        begin
          dbms_output.put_line('Prikaz: '||irec.prikaz);
        execute immediate iRec.prikaz;
        exception
          when others then dbms_output.put_line('NEPOVEDLO SE!');
        end;
      end loop;
end;
/
 
create or replace procedure VYPNI_CIZI_KLICE as 
begin
  for cur in (select CONSTRAINT_NAME, TABLE_NAME from USER_CONSTRAINTS where CONSTRAINT_TYPE = 'R' ) 
  loop
    execute immediate 'alter table '||cur.TABLE_NAME||' modify constraint "'||cur.CONSTRAINT_NAME||'" DISABLE';
  end loop;
end VYPNI_CIZI_KLICE;
/
 
 
create or replace procedure ZAPNI_CIZI_KLICE as 
begin
  for cur in (select CONSTRAINT_NAME, TABLE_NAME from USER_CONSTRAINTS where CONSTRAINT_TYPE = 'R' ) 
  loop
    execute immediate 'alter table '||cur.TABLE_NAME||' modify constraint "'||cur.CONSTRAINT_NAME||'" enable validate';
  end loop;
end ZAPNI_CIZI_KLICE;
/
 
create or replace procedure VYMAZ_DATA_VSECH_TABULEK is
begin
  -- Vymazat data vsech tabulek
  VYPNI_CIZI_KLICE;
  for v_rec in (select distinct TABLE_NAME from USER_TABLES)
  loop
    execute immediate 'truncate table '||v_rec.TABLE_NAME||' drop storage';
  end loop;
  ZAPNI_CIZI_KLICE;
  
  -- Nastavit vsechny sekvence od 1
  for v_rec in (select distinct SEQUENCE_NAME  from USER_SEQUENCES)
  loop
    execute immediate 'alter sequence '||v_rec.SEQUENCE_NAME||' restart start with 1';
  end loop;
end VYMAZ_DATA_VSECH_TABULEK;
/
 
prompt #------------------------#
prompt #- Zrusit stare tabulky -#
prompt #------------------------#
 
exec SMAZ_VSECHNY_TABULKY;
 
prompt #-------------------------#
prompt #- Vytvorit nove tabulky -#
prompt #-------------------------#
 
CREATE TABLE adresa (
    adresa_id       INTEGER NOT NULL,
    ulica           VARCHAR2(80 CHAR) NOT NULL,
    popisne_cislo   VARCHAR2(20 CHAR) NOT NULL,
    psc             VARCHAR2(20 CHAR) NOT NULL,
    krajina         VARCHAR2(50 CHAR) NOT NULL
);

ALTER TABLE adresa ADD CONSTRAINT adresa_pk PRIMARY KEY ( adresa_id );

CREATE TABLE clen_kapely (
    clen_kapely_id   INTEGER NOT NULL,
    meno             VARCHAR2(80 CHAR) NOT NULL,
    mobil_cislo      VARCHAR2(14 CHAR) NOT NULL,
    email            VARCHAR2(80 CHAR) NOT NULL,
    adresa_id        INTEGER NOT NULL
);

ALTER TABLE clen_kapely ADD CONSTRAINT clen_kapely_pk PRIMARY KEY ( clen_kapely_id );

CREATE TABLE clen_kapely_hraje (
    kapela_id        INTEGER NOT NULL,
    clen_kapely_id   INTEGER NOT NULL
);

ALTER TABLE clen_kapely_hraje ADD CONSTRAINT clen_kapely_hraje_pk PRIMARY KEY ( kapela_id,
                                                                                clen_kapely_id );

CREATE TABLE divadlo (
    nazov_predstavenia   VARCHAR2(80 CHAR) NOT NULL,
    cena_vstupenky       INTEGER NOT NULL,
    event_id             INTEGER NOT NULL
);

ALTER TABLE divadlo ADD CONSTRAINT divadlo_pk PRIMARY KEY ( event_id );

CREATE TABLE event (
    event_id       INTEGER NOT NULL,
    nazov_eventu   VARCHAR2(50 CHAR) NOT NULL,
    datum          DATE NOT NULL,
    typ            VARCHAR2(20 BYTE) NOT NULL
);

ALTER TABLE event ADD CONSTRAINT event_pk PRIMARY KEY ( event_id );

CREATE TABLE hod_manazer (
    hod_manazer_id   INTEGER NOT NULL,
    meno             VARCHAR2(80 CHAR) NOT NULL,
    mobil_cislo      VARCHAR2(14 CHAR) NOT NULL,
    email            VARCHAR2(50 CHAR) NOT NULL,
    oblubeny_zaner   VARCHAR2(40 CHAR),
    adresa_id        INTEGER NOT NULL
);

ALTER TABLE hod_manazer ADD CONSTRAINT hod_manazer_pk PRIMARY KEY ( hod_manazer_id );

CREATE TABLE hotel (
    hotel_id      INTEGER NOT NULL,
    nazov         VARCHAR2(60 CHAR) NOT NULL,
    cena_za_noc   INTEGER NOT NULL,
    adresa_id     INTEGER NOT NULL
);

ALTER TABLE hotel ADD CONSTRAINT hotel_pk PRIMARY KEY ( hotel_id );

CREATE TABLE kapela (
    kapela_id      INTEGER NOT NULL,
    nazov_kapely   VARCHAR2(40 CHAR) NOT NULL,
    popis          VARCHAR2(2000 CHAR)
);

ALTER TABLE kapela ADD CONSTRAINT kapela_pk PRIMARY KEY ( kapela_id );

CREATE TABLE kapela_hotel (
    kapela_id   INTEGER NOT NULL,
    hotel_id    INTEGER NOT NULL
);

ALTER TABLE kapela_hotel ADD CONSTRAINT kapela_hotel_pk PRIMARY KEY ( kapela_id,
                                                                      hotel_id );

CREATE TABLE kapela_zaner (
    kapela_id   INTEGER NOT NULL,
    zaner_id    INTEGER NOT NULL
);

ALTER TABLE kapela_zaner ADD CONSTRAINT kapela_zaner_pk PRIMARY KEY ( kapela_id,
                                                                      zaner_id );

CREATE TABLE koncert (
    pocet_kapiel     INTEGER NOT NULL,
    cena_vstupenky   INTEGER NOT NULL,
    event_id         INTEGER NOT NULL
);

ALTER TABLE koncert ADD CONSTRAINT koncert_pk PRIMARY KEY ( event_id );

CREATE TABLE objednavka (
    objednavka_id    INTEGER NOT NULL,
    datum            DATE NOT NULL,
    cena             INTEGER NOT NULL,
    hod_manazer_id   INTEGER NOT NULL,
    event_id         INTEGER NOT NULL,
    clen_kapely_id   INTEGER NOT NULL,
    hodiny           INTEGER NOT NULL,
    popis            VARCHAR2(2000 CHAR)
);

CREATE UNIQUE INDEX objednavka__idx ON
    objednavka (
        event_id
    ASC );

ALTER TABLE objednavka ADD CONSTRAINT objednavka_pk PRIMARY KEY ( objednavka_id );

CREATE TABLE tedx (
    event_id         INTEGER NOT NULL,
    tedtalker        VARCHAR2(80 CHAR) NOT NULL,
    cena_vstupenky   INTEGER NOT NULL
);

ALTER TABLE tedx ADD CONSTRAINT tedx_pk PRIMARY KEY ( event_id );

CREATE TABLE zaner (
    zaner_id   INTEGER NOT NULL,
    nazov      VARCHAR2(40 CHAR) NOT NULL
);

ALTER TABLE zaner ADD CONSTRAINT zaner_pk PRIMARY KEY ( zaner_id );

ALTER TABLE clen_kapely
    ADD CONSTRAINT clen_kapely_adresa_fk FOREIGN KEY ( adresa_id )
        REFERENCES adresa ( adresa_id );

ALTER TABLE clen_kapely_hraje
    ADD CONSTRAINT clen_kapely_hraje_ck_fk FOREIGN KEY ( clen_kapely_id )
        REFERENCES clen_kapely ( clen_kapely_id );

ALTER TABLE clen_kapely_hraje
    ADD CONSTRAINT clen_kapely_hraje_kapela_fk FOREIGN KEY ( kapela_id )
        REFERENCES kapela ( kapela_id );

ALTER TABLE divadlo
    ADD CONSTRAINT divadlo_event_fk FOREIGN KEY ( event_id )
        REFERENCES event ( event_id );

ALTER TABLE hod_manazer
    ADD CONSTRAINT hod_manazer_adresa_fk FOREIGN KEY ( adresa_id )
        REFERENCES adresa ( adresa_id );

ALTER TABLE hotel
    ADD CONSTRAINT hotel_adresa_fk FOREIGN KEY ( adresa_id )
        REFERENCES adresa ( adresa_id );

ALTER TABLE kapela_hotel
    ADD CONSTRAINT kapela_hotel_hotel_fk FOREIGN KEY ( hotel_id )
        REFERENCES hotel ( hotel_id );

ALTER TABLE kapela_hotel
    ADD CONSTRAINT kapela_hotel_kapela_fk FOREIGN KEY ( kapela_id )
        REFERENCES kapela ( kapela_id );

ALTER TABLE kapela_zaner
    ADD CONSTRAINT kapela_zaner_kapela_fk FOREIGN KEY ( kapela_id )
        REFERENCES kapela ( kapela_id );

ALTER TABLE kapela_zaner
    ADD CONSTRAINT kapela_zaner_zaner_fk FOREIGN KEY ( zaner_id )
        REFERENCES zaner ( zaner_id );

ALTER TABLE koncert
    ADD CONSTRAINT koncert_event_fk FOREIGN KEY ( event_id )
        REFERENCES event ( event_id );

ALTER TABLE objednavka
    ADD CONSTRAINT objednavka_clen_kapely_fk FOREIGN KEY ( clen_kapely_id )
        REFERENCES clen_kapely ( clen_kapely_id );

ALTER TABLE objednavka
    ADD CONSTRAINT objednavka_hod_manazer_fk FOREIGN KEY ( hod_manazer_id )
        REFERENCES hod_manazer ( hod_manazer_id );

ALTER TABLE objednavka
    ADD CONSTRAINT objednavka_koncert_fk FOREIGN KEY ( event_id )
        REFERENCES koncert ( event_id );

ALTER TABLE tedx
    ADD CONSTRAINT tedx_event_fk FOREIGN KEY ( event_id )
        REFERENCES event ( event_id );

CREATE OR REPLACE TRIGGER arc_arc_1_tedx BEFORE
    INSERT OR UPDATE OF event_id ON tedx
    FOR EACH ROW
DECLARE
    d VARCHAR2(20 BYTE);
BEGIN
    SELECT
        a.typ
    INTO d
    FROM
        event a
    WHERE
        a.event_id = :new.event_id;

    IF ( d IS NULL OR d <> 'TEDX' ) THEN
        raise_application_error(-20223, 'FK TEDX_EVENT_FK in Table TEDX violates Arc constraint on Table EVENT - discriminator column TYP doesn''t have value ''TEDX'''
        );
    END IF;

EXCEPTION
    WHEN no_data_found THEN
        NULL;
    WHEN OTHERS THEN
        RAISE;
END;
/

CREATE OR REPLACE TRIGGER arc_arc_1_koncert BEFORE
    INSERT OR UPDATE OF event_id ON koncert
    FOR EACH ROW
DECLARE
    d VARCHAR2(20 BYTE);
BEGIN
    SELECT
        a.typ
    INTO d
    FROM
        event a
    WHERE
        a.event_id = :new.event_id;

    IF ( d IS NULL OR d <> 'KONCERT' ) THEN
        raise_application_error(-20223, 'FK KONCERT_EVENT_FK in Table KONCERT violates Arc constraint on Table EVENT - discriminator column TYP doesn''t have value ''KONCERT'''
        );
    END IF;

EXCEPTION
    WHEN no_data_found THEN
        NULL;
    WHEN OTHERS THEN
        RAISE;
END;
/

CREATE OR REPLACE TRIGGER arc_arc_1_divadlo BEFORE
    INSERT OR UPDATE OF event_id ON divadlo
    FOR EACH ROW
DECLARE
    d VARCHAR2(20 BYTE);
BEGIN
    SELECT
        a.typ
    INTO d
    FROM
        event a
    WHERE
        a.event_id = :new.event_id;

    IF ( d IS NULL OR d <> 'DIVADLO' ) THEN
        raise_application_error(-20223, 'FK DIVADLO_EVENT_FK in Table DIVADLO violates Arc constraint on Table EVENT - discriminator column TYP doesn''t have value ''DIVADLO'''
        );
    END IF;

EXCEPTION
    WHEN no_data_found THEN
        NULL;
    WHEN OTHERS THEN
        RAISE;
END;
/



-- Oracle SQL Developer Data Modeler Summary Report: 
-- 
-- CREATE TABLE                            14
-- CREATE INDEX                             1
-- ALTER TABLE                             29
-- CREATE VIEW                              0
-- ALTER VIEW                               0
-- CREATE PACKAGE                           0
-- CREATE PACKAGE BODY                      0
-- CREATE PROCEDURE                         0
-- CREATE FUNCTION                          0
-- CREATE TRIGGER                           3
-- ALTER TRIGGER                            0
-- CREATE COLLECTION TYPE                   0
-- CREATE STRUCTURED TYPE                   0
-- CREATE STRUCTURED TYPE BODY              0
-- CREATE CLUSTER                           0
-- CREATE CONTEXT                           0
-- CREATE DATABASE                          0
-- CREATE DIMENSION                         0
-- CREATE DIRECTORY                         0
-- CREATE DISK GROUP                        0
-- CREATE ROLE                              0
-- CREATE ROLLBACK SEGMENT                  0
-- CREATE SEQUENCE                          0
-- CREATE MATERIALIZED VIEW                 0
-- CREATE MATERIALIZED VIEW LOG             0
-- CREATE SYNONYM                           0
-- CREATE TABLESPACE                        0
-- CREATE USER                              0
-- 
-- DROP TABLESPACE                          0
-- DROP DATABASE                            0
-- 
-- REDACTION POLICY                         0
-- 
-- ORDS DROP SCHEMA                         0
-- ORDS ENABLE SCHEMA                       0
-- ORDS ENABLE OBJECT                       0
-- 
-- ERRORS                                   0
-- WARNINGS                                 0