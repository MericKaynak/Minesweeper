//
// Created by meric on 14/06/2024.
//

#ifndef DATUM_H
#define DATUM_H

#include <stdexcept>
#include <iomanip>
#include <sstream>

class Datum {
private:
    int tag;
    int monat;
    int jahr;

    bool istGueltigesDatum(int t, int m, int j) const {
        if (j < 1 || m < 1 || m > 12 || t < 1 || t > 31) return false;

        // Prüfen der Tage im Monat
        if (m == 2) {
            if (istSchaltjahr(j)) return t <= 29;
            else return t <= 28;
        }

        if (m == 4 || m == 6 || m == 9 || m == 11) return t <= 30;

        return true;
    }

    bool istSchaltjahr(int j) const {
        return (j % 4 == 0 && j % 100 != 0) || (j % 400 == 0);
    }

public:
    // Konstruktor
    Datum(int t, int m, int j) {
        if (!istGueltigesDatum(t, m, j)) {
            throw std::invalid_argument("Ungültiges Datum");
        }
        tag = t;
        monat = m;
        jahr = j;
    }

    // Getter-Methoden
    int getTag() const { return tag; }
    int getMonat() const { return monat; }
    int getJahr() const { return jahr; }

    // Setter-Methoden
    void setTag(int t) {
        if (!istGueltigesDatum(t, monat, jahr)) {
            throw std::invalid_argument("Ungültiger Tag");
        }
        tag = t;
    }

    void setMonat(int m) {
        if (!istGueltigesDatum(tag, m, jahr)) {
            throw std::invalid_argument("Ungültiger Monat");
        }
        monat = m;
    }

    void setJahr(int j) {
        if (!istGueltigesDatum(tag, monat, j)) {
            throw std::invalid_argument("Ungültiges Jahr");
        }
        jahr = j;
    }

    // Methode zum Formatieren des Datums als String
    std::string toString() const {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << tag << "/"
            << std::setfill('0') << std::setw(2) << monat << "/"
            << jahr;
        return oss.str();
    }

    // Vergleichsmethoden
    bool operator==(const Datum& anderes) const {
        return tag == anderes.tag && monat == anderes.monat && jahr == anderes.jahr;
    }

    bool operator!=(const Datum& anderes) const {
        return !(*this == anderes);
    }

    bool operator<(const Datum& anderes) const {
        if (jahr != anderes.jahr) return jahr < anderes.jahr;
        if (monat != anderes.monat) return monat < anderes.monat;
        return tag < anderes.tag;
    }

    bool operator<=(const Datum& anderes) const {
        return *this < anderes || *this == anderes;
    }

    bool operator>(const Datum& anderes) const {
        return !(*this <= anderes);
    }

    bool operator>=(const Datum& anderes) const {
        return !(*this < anderes);
    }
};



#endif //DATUM_H
