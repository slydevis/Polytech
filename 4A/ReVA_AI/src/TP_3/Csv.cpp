#include "Csv.hpp"

CSV::CSV(const std::string &filename) {
    file = std::fstream(filename, std::fstream::out);
}

void CSV::write(const std::string &str) { file << str << "\n"; }

void CSV::close() {}

void CSV::createHeader() {
    file << "Image; Méthode; Contours Détectés; Contours Référence; Contours "
            "correct; Faux positif; Faux négatifs; Performance; Taux de faux "
            "positif; Taux de faux négatif; Meilleur Blur; Meilleur param; "
            "Meilleur Seuil"
         << "\n";
}