#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class Studentas {
public:
    Studentas();
    ~Studentas();
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);

    void ivestiDuomenis();
    void isvestiDuomenis(bool naudotiVidurki) const;
    void skaiciuotiGalutini(bool naudotiVidurki);

private:
    std::string vardas;
    std::string pavardė;
    std::vector<int> namuDarbai;
    int egzaminas;
    double galutinis;
};

Studentas::Studentas() : egzaminas(0), galutinis(0) {}

Studentas::~Studentas() {}

Studentas::Studentas(const Studentas& other) {
    vardas = other.vardas;
    pavardė = other.pavardė;
    namuDarbai = other.namuDarbai;
    egzaminas = other.egzaminas;
    galutinis = other.galutinis;
}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas = other.vardas;
        pavardė = other.pavardė;
        namuDarbai = other.namuDarbai;
        egzaminas = other.egzaminas;
        galutinis = other.galutinis;
    }
    return *this;
}

void Studentas::ivestiDuomenis() {
    std::cout << "Įveskite studento vardą ir pavardę: ";
    std::cin >> vardas >> pavardė;

    int nd;
    std::cout << "Įveskite namų darbų rezultatus (įveskite -1, kai baigsite): ";
    while (true) {
        std::cin >> nd;
        if (nd == -1) break;
        namuDarbai.push_back(nd);
    }

    std::cout << "Įveskite egzamino rezultatą: ";
    std::cin >> egzaminas;
}

void Studentas::isvestiDuomenis(bool naudotiVidurki) const {
    std::cout << std::setw(15) << pavardė << std::setw(15) << vardas;

    if (naudotiVidurki) {
        std::cout << std::setw(20) << std::fixed << std::setprecision(2) << galutinis << std::setw(10) << "(Vid.)";
    } else {
        std::cout << std::setw(20) << std::fixed << std::setprecision(2) << galutinis << std::setw(10) << "(Med.)";
    }

    std::cout << std::endl;
}

void Studentas::skaiciuotiGalutini(bool naudotiVidurki) {
    if (naudotiVidurki) {
        double vidurkis = 0.0;
        for (int nd : namuDarbai) {
            vidurkis += nd;
        }
        vidurkis /= namuDarbai.size();
        galutinis = 0.4 * vidurkis + 0.6 * egzaminas;
    } else {
        std::sort(namuDarbai.begin(), namuDarbai.end());
        int dydis = namuDarbai.size();
        if (dydis % 2 == 0) {
            double mediana = (namuDarbai[dydis / 2 - 1] + namuDarbai[dydis / 2]) / 2.0;
            galutinis = 0.4 * mediana + 0.6 * egzaminas;
        } else {
            galutinis = 0.4 * namuDarbai[dydis / 2] + 0.6 * egzaminas;
        }
    }
}

int main() {
    int studentuSkaicius;
    std::cout << "Įveskite studentų skaičių: ";
    std::cin >> studentuSkaicius;

    std::vector<Studentas> studentai;

    for (int i = 0; i < studentuSkaicius; ++i) {
        Studentas naujasStudentas;
        naujasStudentas.ivestiDuomenis();
        naujasStudentas.skaiciuotiGalutini(true); // Naudoti vidurki
        studentai.push_back(naujasStudentas);
    }

    // Išvedimas
    std::cout << std::setw(15) << "Pavardė" << std::setw(15) << "Vardas" << std::setw(20) << "Galutinis (Vid.)" << std::setw(10) << "(Med.)" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    for (const auto& studentas : studentai) {
        studentas.isvestiDuomenis(true); // Naudoti vidurki
    }

    return 0;
}
