# Zoo-Verwaltungssystem (C++20)

Ein kommandozeilenbasiertes Verwaltungssystem zur Zuordnung von **Tieren zu Gehegen** mit dauerhafter Speicherung in einer Textdatei. Entwickelt mit **C++20** und **CLion** als universitäres Abschlussprojekt zur objektorientierten Programmierung an der **Universität Osnabrück**.

> **Bewertung:** Laut dem bereitgestellten Artemis-Ergebnis wurden alle sechs offenen Beispieltests und alle sieben bewerteten versteckten Tests bestanden (**42/42 Punkte**). Dies ist die Bewertung der Uni-Abgabe, keine Aussage über einen gesonderten aktuellen Testlauf.
>
> **Projektstatus:** Studienprojekt, nicht für einen produktiven Zoobetrieb vorgesehen. Der Befehl `help` ist im beigefügten Quellcode noch nicht implementiert.

## Projektidee

Für einen fiktiven Zoo soll die Software die Zuordnung von Tieren zu Gehegen verwalten. Die Kommunikation mit anderen gedachten Programmkomponenten erfolgt über **Kommandozeilenargumente**, nicht über ein interaktives Menü. Für jeden Aufruf wird der aktuelle Zustand aus der Datei `zoo` geladen, ein Befehl ausgeführt und nach einer erfolgreichen Änderung wieder gespeichert; anschließend endet das Programm.

Jedes **Tier** besitzt eine eindeutige ID, einen Namen und eine Tierart. Jedes **Gehege** besitzt eine eindeutige ID, einen Namen und eine maximale Kapazität. **Zuordnungen** verknüpfen die jeweilige Gehege-ID mit einer Tier-ID.

Dabei gelten folgende Regeln:

- Ein Tier ist **höchstens einem Gehege** zugeordnet.
- Ein Gehege darf **mehrere Tiere**, aber niemals mehr als seine festgelegte Kapazität aufnehmen.
- Zugeordnete Tiere und nicht leere Gehege dürfen nicht gelöscht werden.
- IDs werden bei der Erstellung automatisch vergeben.

## Funktionen und Kommandozeilenbefehle

Die allgemeine Syntax lautet:

```text
<Programm> <Befehl> [Parameter]
```

| Befehl | Beispiel | Bedeutung |
| --- | --- | --- |
| `add animal <Name> <Art-ID>` | `add animal Elli 2` | Tier anlegen |
| `add enclosure <Name> <Kapazität>` | `add enclosure Elefantenhaus 7` | Gehege anlegen |
| `delete animal <ID>` | `delete animal 0` | Nicht zugeordnetes Tier löschen |
| `delete enclosure <ID>` | `delete enclosure 0` | Leeres Gehege löschen |
| `list animals` | `list animals` | Alle Tiere auflisten |
| `list enclosures` | `list enclosures` | Alle Gehege auflisten |
| `list assignments` | `list assignments` | Alle Zuordnungen auflisten |
| `list assigned` | `list assigned` | Zugeordnete Tiere auflisten |
| `list unassigned` | `list unassigned` | Nicht zugeordnete Tiere auflisten |
| `show animal <ID>` | `show animal 0` | Details eines Tieres anzeigen |
| `show enclosure <ID>` | `show enclosure 0` | Details eines Geheges anzeigen |
| `assign <Gehege-ID> <Tier-ID>` | `assign 0 0` | Tier zuordnen |
| `unassign <Gehege-ID> <Tier-ID>` | `unassign 0 0` | Zuordnung aufheben |
| `help` | `help` | Laut Aufgabenstellung Hilfe anzeigen; **im Code noch nicht umgesetzt** |

Für Tierarten sind folgende Nummern definiert:

| Art-ID | Tierart |
| --- | --- |
| 0 | Affe |
| 1 | Bär |
| 2 | Elefant |
| 3 | Pinguin |
| 4 | Zebra |

**Hinweis:** Die Beispiel-IDs `0` setzen voraus, dass die entsprechenden Einträge vorhanden sind. Bei Gehegenamen mit Leerzeichen unterstützt das Projekt ein Format mit `%`-Begrenzern, z. B. `%Wald und Wiese%`.

## Ausführung

### In CLion

1. Diesen Ordner als CMake-Projekt öffnen.
2. Das CMake-Projekt laden und das Target **`Zoo_Projekt_5`** bauen.
3. Unter **Run → Edit Configurations** einen Aufruf bei **Program arguments** eintragen, z. B. `list animals`.
4. Als **Working directory** den Projektordner wählen, damit die Datei `zoo` dort gefunden bzw. erstellt wird.
5. Das Programm starten. Für weitere Aktionen die Programmargumente ändern und erneut starten.

### Mit CMake im Terminal

Voraussetzungen sind ein Compiler mit C++20-Unterstützung und **CMake 4.0 oder neuer** (entsprechend der unveränderten `CMakeLists.txt`).

```bash
cmake -S . -B build
cmake --build build
```

Beispiel unter Linux/macOS, ausgeführt **aus dem Projektordner**:

```bash
./build/Zoo_Projekt_5 add animal Elli 2
./build/Zoo_Projekt_5 add enclosure Elefantenhaus 7
./build/Zoo_Projekt_5 list animals
./build/Zoo_Projekt_5 assign 0 0
./build/Zoo_Projekt_5 list assignments
```

Unter Windows hängt der Pfad zur ausführbaren Datei vom CMake-Generator und Build-Profil ab. Das Programm ist **nicht interaktiv**: Jeder Befehl ist ein eigener Programmaufruf.

## Datenpersistenz und Austauschformat

Das Programm verwendet die lokale Textdatei **`zoo`** als permanenten Speicher. Sie wird bei fehlender Datei angelegt. Eine Beispieldatei liegt als **`zoo.example`** bei und kann zu Testzwecken nach `zoo` kopiert werden. Die zur Laufzeit erzeugte Datei `zoo` ist in `.gitignore` ausgeschlossen.

Die Datei besteht aus drei Blöcken:

```ini
[animals]
0 Elli 2
1 Pingu 3

[enclosures]
0 %Wald und Wiese% 5

[assignments]
0 0
```

- **Tiere:** `<ID> <Name> <Art-ID>`; Tiernamen enthalten keine Leerzeichen.
- **Gehege:** `<ID> %<Name>% <Kapazität>`; Gehegenamen dürfen Leerzeichen enthalten.
- **Zuordnung:** `<Gehege-ID> <Tier-ID>`.

Die Blöcke können gemäß Aufgabenstellung in beliebiger Reihenfolge stehen. Beim Einlesen werden Format und referenzierte IDs geprüft; Fehler werden als Meldungen mit numerischen Codes ausgegeben.

## Fehlerbehandlung

Das Aufgabenformat sieht standardisierte Meldungen für erfolgreiche bzw. fehlerhafte Operationen vor:

| Code | Bedeutung |
| --- | --- |
| `100` | Erfolgreiche Operation |
| `101` | Unbekannter Befehl |
| `102` | Ungültiger oder nicht lesbarer Parameter |
| `201` / `202` | Gehege / Tier kann wegen vorhandener Zuordnung nicht gelöscht werden |
| `301` / `302` | Zuordnung existiert nicht / bereits |
| `401` / `402` | Gehege / Tier existiert nicht |
| `501` | Gehege ist voll |
| `502` | Tier gehört bereits zu einem anderen Gehege |
| `601` / `602` / `603` | Datei kann nicht geöffnet werden / unbekanntes Dateiformat / Datei kann nicht geschrieben werden |

**Achtung:** Dies sind die in der Aufgabenstellung definierten Codes. Bei reinen Listen- und Detailabfragen wird üblicherweise direkt der Inhalt ausgegeben. Die Bezeichnung „Rückgabe-Code“ in der Aufgabe meint insbesondere die **textuelle Programmausgabe**, nicht zwangsläufig den Exit-Status des Betriebssystems.

## Technische Umsetzung

Das Projekt demonstriert insbesondere:

- **Objektorientierte Modellierung** von Tieren, Gehegen und Zuordnungen in getrennten Klassen.
- **Modularisierung** mit Header- (`.h`) und Implementierungsdateien (`.cpp`).
- **C++-Streams** (`std::istream`, `std::ostream`, Datei- und Stringstreams) sowie überladene Ein-/Ausgabeoperatoren.
- **Datenverwaltung** und Suche mit Containern der C++-Standardbibliothek.
- **Validierung und Fehlerbehandlung** für ungültige Eingaben, Zuordnungen und Dateizugriffe.
- **CMake** zur Konfiguration und Übersetzung des Projekts.

### Dateistruktur

| Dateien | Zweck |
| --- | --- |
| `main.cpp` | Programmstart, Befehlsverarbeitung sowie Lade-/Speicherablauf |
| `animal.h/.cpp` | Datenmodell Tier |
| `enclosure.h/.cpp` | Datenmodell Gehege |
| `spezie.h/.cpp` | Modellierung der Tierarten |
| `assignment.h/.cpp` | Tier-Gehege-Zuordnung |
| `zoodb.h/.cpp` | Verwaltung der Datenbestände und Suche nach IDs |
| `befehle.h/.cpp` | Implementierung der Kommandozeilenbefehle |
| `zooio.h/.cpp` | Einlesen und Schreiben der Datei `zoo` |
| `errorfall.h` | Textausgabe der Fehlercodes |
| `parameter_reader.h`, `std_lib_inc.h` | Hilfs-Header aus dem Projekt-/Lehrkontext |
| `CMakeLists.txt` | Build-Konfiguration |
| `zoo.example` | Beispieldaten für lokale Tests |

## Tests und Grenzen

Die mit der Aufgabenstellung bereitgestellte Artemis-Auswertung meldet:

- **6/6 offene Tests bestanden** (Kompilation und Beispielabläufe).
- **7/7 versteckte Tests bestanden**, insgesamt **42/42 Punkte**.

Bekannte Einschränkung der beigefügten Implementierung: Die Methode für `help` besitzt noch keinen Funktionskörper. Die hier bereitgestellte Version wurde für die Veröffentlichung **dokumentiert und bereinigt**, der eigentliche C++-Quellcode wurde **nicht verändert**. Es wurde kein neuer umfassender Funktionstest für diese ZIP-Version durchgeführt.

## Herkunft und Hinweise zur Veröffentlichung

Das Projekt basiert auf einer universitären Programmieraufgabe **„Zooverwaltung“** (Universität Osnabrück / Artemis, Januar 2026). Aufgabenstellung: [Artemis-Kursseite](https://artemis.informatik.uni-osnabrueck.de/courses/2/exercises/27) (möglicherweise nur mit Universitätszugang erreichbar).

Die Implementierung ist als **Studienprojekt** zu verstehen und nicht als offizielle Software des Zoo Osnabrück. Vor einer öffentlichen Veröffentlichung müssen die Kursregeln sowie Nutzungs- und Veröffentlichungsrechte an den mitgelieferten Hilfs-Headern geprüft werden.
