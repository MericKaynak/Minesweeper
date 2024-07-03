#include <iostream>

int hauptMenu() {
    std::cout << "\n\n";
    std::cout << "+------------------------+\n";
    std::cout << "| Hauptmenü:             |\n";
    std::cout << "+------------------------+\n\n";
    std::cout << "  (1) Daten aus einer Datei einlesen\n";
    std::cout << "  (2) Daten in einer Datei abspeichern\n";
    std::cout << "  (3) Patienten Optionen anzeigen\n";
    std::cout << "  (4) Angestellten Optionen anzeigen\n";
    std::cout << "  (5) Behandlung planen\n";
    std::cout << "  (6) Behandlung ändern\n";
    std::cout << "  (7) Behandlung stornieren\n";
    std::cout << "  (9) Programm beenden\n";
    std::cout << "------------------------------------------------\n";
    std::cout << " Ihre Auswahl? ";

    int auswahl;
    std::cin >> auswahl;

    return auswahl;
}
int patientenMenue() {
    std::cout << "\n\n";
    std::cout << "+----------------------------------+\n";
    std::cout << "| Patienten Stammdaten pflegen:    |\n";
    std::cout << "+----------------------------------+\n\n";
    std::cout << " (1) Patienten anlegen\n";
    std::cout << " (2) Patienten entfernen\n";
    std::cout << " (3) Patienten ändern\n";
    std::cout << " (4) Patienten-Liste anzeigen\n";
    std::cout << " (5) Behandlungen anzeigen\n";
    std::cout << " (6) Abbruch\n";
    std::cout << " -----------------------------------------------\n";
    std::cout << " Ihre Auswahl?\n";


    int auswahl;
    std::cin >> auswahl;

    return auswahl;
}

int angestelltenMenue() {
    std::cout << "\n\n";
    std::cout << "+----------------------------------+\n";
    std::cout << "| Angestellten Stammdaten pflegen: |\n";
    std::cout << "+----------------------------------+\n\n";
    std::cout << " (1) Angestellten anlegen\n";
    std::cout << " (2) Angestellten entfernen\n";
    std::cout << " (3) Angestellten ändern\n";
    std::cout << " (4) Angestellten-Liste anzeigen\n";
    std::cout << " (5) Behandlungen anzeigen\n";
    std::cout << " (6) Abbruch\n";
    std::cout << " -----------------------------------------------\n";
    std::cout << " Ihre Auswahl?\n";


    int auswahl;
    std::cin >> auswahl;

    return auswahl;
}

int main() {
    while (1){
        int auswahl;
        auswahl = hauptMenu();
        switch (auswahl) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                auswahl= patientenMenue();
                switch (auswahl) {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                }
                break;
            case 4:
                auswahl= angestelltenMenue();
                switch (auswahl) {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                }
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                return 0;
                break;

        }
    }
}
