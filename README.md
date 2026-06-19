# B-Stablo - Konzolna Aplikacija u C++-u

Konzolna implementacija **B-stabla** (B-tree) u C++-u za čuvanje i pretragu stringova. Stablo podržava konfigurabilan red i implementira sve standardne operacije uključujući prelivanje i prelamanje čvorova pri ubacivanju.

# Struktura podataka

**B-stablo reda n** je uravnoteženo stablo pretrage u kome svaki čvor (osim korena) sadrži između `⌈n/2⌉ - 1` i `n - 1` ključeva. Koren ima poseban kapacitet: `2 * ⌊(2n-2)/3⌋` ključeva.

Svaki čvor (`Cvor`) sadrži:
- `kljuc[]` - sortirani niz stringova (ključeva), sa sentinel vrednostima `"aaaaa"` i `"zzzzz"` na granicama
- `pok[]` - niz pokazivača na decu
- `otac` - pokazivač na roditeljski čvor
- `br` - trenutni broj ključeva u čvoru

# Operacije

| Opcija | Opis |
|--------|------|
| `1` | Kreiranje stabla zadatog reda i učitavanje ključeva iz tekstualnog fajla |
| `2` | Pretraga ključa u stablu (binarna pretraga po nivou) |
| `3` | Vizuelni ispis stabla nivo po nivo |
| `4` | Dodavanje novog ključa u stablo |
| `5` | Brisanje ključa iz stabla |
| `6` | Broj ključeva leksikografski manjih od zadatog ključa |
| `0` | Kraj programa |

# Algoritam ubacivanja

Pri ubacivanju novog ključa koriste se dve strategije za rešavanje prepunjenosti čvorova:

- **Prelivanje** - ako susedni čvor ima slobodnog mesta, ključevi se preraspoređuju između dva susedna čvora i roditelja
- **Prelamanje** - ako nema slobodnog mesta, čvor se deli na dva nova čvora, a srednji ključ se propagira naviše ka roditelju

# Format ulaznog fajla

Svaki red fajla sadrži jedan ključ (string):
```
nesto
nar
narandza
limun
malina
jabuka
ananas
```

Priložen primer: `nesto.txt`

# Pokretanje

# Zahtevi
- Windows operativni sistem
- Visual Studio (preporučuje se 2022)

# Koraci
1. Otvori `dz2.sln` u Visual Studio-u
2. Kompajliraj projekat (`Ctrl+Shift+B`)
3. Pokreni sa `Ctrl+F5`
4. Unesi red stabla (3-10) i naziv fajla (npr. `nesto.txt`)

# Struktura projekta

```
dz2/
├── dz2.sln
└── dz2/
    ├── stablo.h        # Definicija klase Stablo i Cvor
    ├── stablo.cpp      # Implementacija svih operacija
    ├── main.cpp        # Konzolni interfejs
    └── nesto.txt       # Primer ulaznih podataka
```


