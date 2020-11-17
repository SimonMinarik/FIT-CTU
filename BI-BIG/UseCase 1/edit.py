import pandas as pd


def main():
    df = pd.read_csv("logstash/data/covid_old.csv")
    df['pocet_nakazenych'] = df['kumulativni_pocet_nakazenych']
    for i in range(1, len(df)):
        df.loc[i, 'pocet_nakazenych'] = df.loc[i, 'pocet_nakazenych'] - df.loc[i - 1, 'kumulativni_pocet_nakazenych']
    df['pocet_vylecenych'] = df['kumulativni_pocet_vylecenych']
    for i in range(1, len(df)):
        df.loc[i, 'pocet_vylecenych'] = df.loc[i, 'pocet_vylecenych'] - df.loc[i - 1, 'kumulativni_pocet_vylecenych']
    df['pocet_umrti'] = df['kumulativni_pocet_umrti']
    for i in range(1, len(df)):
        df.loc[i, 'pocet_umrti'] = df.loc[i, 'pocet_umrti'] - df.loc[i - 1, 'kumulativni_pocet_umrti']
    df['pocet_testu'] = df['kumulativni_pocet_testu']
    for i in range(1, len(df)):
        df.loc[i, 'pocet_testu'] = df.loc[i, 'pocet_testu'] - df.loc[i - 1, 'kumulativni_pocet_testu']
    df.to_csv("logstash/data/covid.csv", index=False)


if __name__ == "__main__":
    main()
