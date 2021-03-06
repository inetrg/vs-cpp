# Inhalt

Dieses Repository beinhaltet alle Beispielanwendungen des Vorlesungsblocks
"Programmieren im Aktormodell mit C++".

# Aufbau

1. Simples Hello-World Programm
2. Dynamisches Array (initialisieren + anfügen)
3. Lebenszeit von Objekten im Scope einer Funktionen
4. Lebenszeit von Objekten im Scope eines Teilbereichs einer Funktion
5. Zeiger auf Objekte auf dem Stack
6. Sichere Zeiger auf Objekte im Heap
7. Referenzen auf Objekte
8. Iteratoren
9. Const-Modifier auf Referenzen und Zeigern
10. Funktions-Prototyp und -Definition am Beispiel einer Member-Funktion
11. Überladen von operator<< für std::ostream zur Ausgabe eigener Typen
12. Move-Semantik
13. Eigene Klassen und Vererbung
14. Erste (konfigurierbare) CAF Anwendung
15. Einfacher Additions-Aktor
16. Aktor für alle Grundrechenarten
17. Entfernte Aktoren
18. Eigene Datentypen in CAF
19. Aktoren mit explizitem State
20. Monitoring
21. Linking
22. Publish/Subscribe Gruppenkommunikation

# Kompilieren

Zum Kompilieren wird ein aktueller Compiler sowie CMake benötigt. Für die
Beispiele 14-21 zusätzlich CAF. Die Schritte zum kompilieren sind die üblichen
Schritte für CMake-basierte Projekte:

```
mkdir build
cd build
cmake -D ..
make
```

Wenn Sie CAF auf dem System nicht installieren möchten ist auch die Angabe des
`build`-Ordners einer kompilierten CAF Version möglich:

```
cmake -D CAF_ROOT_DIR=<path-to-caf>/build ..
```

# Ausführen

Nach dem kompilieren befinden sich im `build` Ordner die ausführbaren Dateien
`vs01` bis `vs22` und können direkt in einer Shell ausgeführt werden.
