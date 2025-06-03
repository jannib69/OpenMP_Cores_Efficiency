# Primerjava paralelizacije linearne regresije z OpenMP

## Opis projekta

V tem projektu primerjamo časovno učinkovitost izvajanja linearne regresije z uporabo različnih števil **OpenMP threadov**. Namesto GPU-ja uporabimo **paralelizacijo na CPU-ju**, kar je uporabno pri sistemih brez dostopa do pospeševalnih enot.

Eksperiment sem izvedel na prenosniku MacBook Pro z Apple M3 čipom, ki nima Hyper-Threadinga – vsako izmed osmih jeder podpira le eno nit, kar pomeni, da je največje število vzporednih threadov 8. Kljub tej arhitekturi je Apple M3 izkazal visoko učinkovitost pri enojedrni in večjedrni obdelavi, kar je bilo razvidno iz rezultatov z uporabo OpenMP: čas izvajanja se je z večanjem števila threadov močno skrajšal do strojne meje.

---

## Eksperiment

- **Podatki**: Generirani linearni podatki z Gaussovim šumom (`y = 3.5x + 7 + ε`)
- **Algoritem**: Linearna regresija z metodo najmanjših kvadratov
- **Cilj**: Izvesti 100 ponovitev regresije in izmeriti:
  - Skupni čas izvajanja
  - Najboljši RMSE med vsemi ponovitvami
  - Koeficienta `a` in `b` za najboljši model

---

## Parametri

| Parameter     | Vrednost         |
|---------------|------------------|
| Število podatkov | 10,000,000    |
| Število ponovitev (`REPEAT`) | 100 |
| Threadi testirani | 1 do 8        |

---

## OpenMP

OpenMP omogoča uporabo več CPU threadov znotraj C++ kode. Program smo testirali z različnim številom niti in merili pohitritev.

---

## Rezultati

Rezultati so shranjeni v `timing_results.csv`:

![image](https://github.com/user-attachments/assets/549968be-4c67-427c-8deb-d8f68955e3dd)

![image](https://github.com/user-attachments/assets/fa96e3a3-5abc-421e-9237-b3f01a5d3fba)

![image](https://github.com/user-attachments/assets/22d8be18-afdb-4d1b-8542-f95bc6c80ef8)
