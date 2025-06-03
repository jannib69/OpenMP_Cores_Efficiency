# Primerjava paralelizacije linearne regresije z OpenMP

## 🧠 Opis projekta

V tem projektu primerjamo časovno učinkovitost izvajanja linearne regresije z uporabo različnih števil **OpenMP threadov**. Namesto GPU-ja uporabimo **paralelizacijo na CPU-ju**, kar je uporabno pri sistemih brez dostopa do pospeševalnih enot.

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
