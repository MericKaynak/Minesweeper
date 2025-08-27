# Minesweeper

## Wichtig vorm starten

1. Ueberpruefen Sie ob die Pfade der Images richtig sind in GameRenderer line 156 und 235
2. Das Menu kann jederzeit neu aufgerufen werden mit R
3. Wurde auf linux only programmiert und ausgefuehrt bzw. wsl
4. Installieren Sie das libgtkmm-3.0-dev paket fuer ihre Distribution

## Geaenderte Punkte nach Feeback

1. Dialog* => `unique_ptr<Dialog>`
2. Game* => `std::unique_ptr<Game>`;
3. game->IS_A_BOMB => Game::IS_A_BOMB
4. Window& window => `std::shared_ptr<Gtk::Window> window;`
5. Game.hpp angepasst in bezug auf nodiscard

## Anmerkungen

1. Glib::RefPtr ist ein nach nem RAII Prinzip und kuemmert sich um Speicher freigabe, das gleiche gilt fuer  Gtk::manage

## Ausfuehrung

Zu erst, ausgegangen davon, dass man sich in `AdvancedCPP` befindet:

```bash
mkdir build
cd build
```

Dann:

```bash
cmake ..
```

Noch `make` ausfuehren

```bash
make
```

Schliesslich das Spiel starten:

```bash
./AdvancedC
```
