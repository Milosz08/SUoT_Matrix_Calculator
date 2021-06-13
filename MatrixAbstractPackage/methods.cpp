#include "MatrixAbstract.h"

using namespace matrixAbstractPackage;

/**
 * @fn allocateMemory()
 * @brief Metoda alokująca dynamicznie pamięć w formie tablicy wskaźników typu M (int/double)
 * o wielkości równej ilości wierszy oraz tworząca dynamiczne tablice (ich ilość jest
 * zależna od ilości wierszy) o wielkości równej ilości kolumn w macierzy.
 * @tparam M - wzór reprezentujący typ wartości wprowadzanych do macierzy (int/double)
 */
template<class M>
void MatrixAbstract<M>::allocateMemory() {
  this->mtrx = new M* [this->mtrxHeight];
  for(unsigned int i = 0; i < this->mtrxHeight; i++) {
    this->mtrx[i] = new M [this->mtrxWidth];
  }
}

/*!
 * @fn findMaxLength(unsigned int& col)
 * @inherit Metoda tylko na potrzeby metod wirtualnych klasy abstrakcyjnej! Metoda niedziedziczona!
 * @brief Wyznaczenie, odszukanie i zwrócenie najdłużego ciągu liczbowego w jednej kolumnie macierzy.
 * @tparam M - wzór reprezentujący typ wartości wprowadzanych do macierzy (int/double)
 * @param col - aktualnie obsługiwana kolumna (indeks)
 * @return - najdłuższy ciąg liczbowy w n kolumnie (wartość n = param col)
 */
template<class M>
unsigned int MatrixAbstract<M>::findMaxLength(unsigned int& col) const {
  std::string str{""};
  unsigned int freeSpace{2}; /** Ilość spacji między kolumnami macierzy */
  std::vector<unsigned int>allLength;
  for(unsigned int i = 0; i < this->mtrxHeight; i++) {
    str = std::to_string(this->mtrx[i][col]);
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    str.erase(str.find_last_not_of(',') + 1, std::string::npos);
    allLength.push_back(str.length());
  }
  return *max_element(allLength.begin(), allLength.end()) + freeSpace;
}

/*!
 * @fn lengthOfElm(M& cell)
 * @brief Metoda tylko na potrzeby metod wirtualnych klasy abstrakcyjnej! Metoda niedziedziczona!
 * Wyznaczanie i zwrócenie długości wartości liczbowej typu "unsigned int" w pojedynczej komórce macierzy.
 * @tparam M - wzór reprezentujący typ wartości wprowadzanych do macierzy (int/double)
 * @param cell - wartość typu M przekazywana do komórki przez referencję
 * @return - długość wartości pobieranej ze zmiennej "cell" typu M przez referencję
 */
template<class M>
unsigned int MatrixAbstract<M>::lengthOfElm(M& cell) const {
  std::string elmLength{""};
  elmLength = std::to_string(cell);
  elmLength.erase(elmLength.find_last_not_of('0') + 1, std::string::npos);
  elmLength.erase(elmLength.find_last_not_of(',') + 1, std::string::npos);
  return elmLength.length();
}

/**
 * @fn pringMtrx()
 * @brief Metoda drukująca na ekran zawartość macierzy na podstawie
 * wartości zapisanych w dwuwymiarowej tablicy dynamicznej.
 * @tparam M - wzór reprezentujący typ wartości wprowadzanych do macierzy (int/double)
 * @param textMess - jeśli "true" drukuje komunikat, jeśli "false" drukuje jednynie macierz
 * @param sharpBrc - jeśli "true" drukuje "[]", jeśli false drukuje "|".
 */
template<class M>
void MatrixAbstract<M>::printMtrx(const bool textMess, const bool sharpBrc) const {
  unsigned int spaces{0}; /** Przerwa pomiędzy kolejnymi kolumnami */
  if(textMess) {
    std::cout << "\n  Zapisalem nastepujaca macierz ";
    std::cout << (this->mtrxHeight == this->mtrxWidth ? "kwadratowa:\n" : "prostokatna:\n");
  }
  for(unsigned int i = 0; i < this->mtrxHeight; i++) {
    for(unsigned int j = 0; j < this->mtrxWidth; j++) {
      if(j == 0) { /** Jeśli jest to 1 kolumna macierzy */
        std::cout << (sharpBrc ? "  [ " : "  | ");
      }
      std::cout << this->mtrx[i][j];
      if(j == this->mtrxWidth - 1) { /** Jeśli jest to ostatnia kolumna macierzy */
        spaces = findMaxLength(j) - lengthOfElm(this->mtrx[i][j]) - 2;
      } else { /** Pozostałe kolumny macierzy */
        spaces = findMaxLength(j) - lengthOfElm(this->mtrx[i][j]);
      }
      for(unsigned int k = 0; k < spaces; k++) {
        std::cout << " ";
      }
    }
    std::cout << (sharpBrc ? " ]" : " |") << "\n";
  }
}

/**
 * @fn scalarValuePush()
 * @brief Wprowadzanie przez użytkownika wartości skalara. Metoda posiada walidację pod kątem
 * strumienia wejścia. Jeśli zostaną podane nieprawidłowe wartości, program wyświetli błąd i
 * umożliwi ponowne wpisanie wartości skalara przez użytkownika.
 * @tparam M - wzór reprezentujący typ wartości wprowadzanych do macierzy (int/double)
 * @return - wartość skalara zapisaną w polu klasy.
 */
template<class M>
double MatrixAbstract<M>::scalarValuePush() {
  bool error{false}, repeatMess{false};
  std::cout << "\nAby przejsc dalej, podaj wartosc skalara, przez ktora chcesz przemnozyc macierz.\n";
  std::cout << "Uwaga! Jesli podasz wiecej elementow (po spacji), zostana one przeze mnie zignorowane!\n";
  do {
    try {
      error = false;
      std::cout << "\nWpisz tutaj" << (!repeatMess ? "" : " ponownie") << " wartosc skalara:\n";
      std::cin >> this->scalarVal;
      if(std::cin.fail()) {
        throw std::logic_error("badScalarValue");
      }
    }
    catch(std::logic_error& e) {
      std::cout << "\nError! Blad logiczny, kod bledu: " << e.what() << "!\n";
      std::cout << "Wartosc skalarna zawiera nieprawidlowe znaki!\n";
      std::cout << "Aby kontyuowac wprowadz ponownie wartosc skalara.\n";
      error = repeatMess = true;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  } while(error);
  return this->scalarVal;
}

/*!
 * @fn finalMathInfo(const std::list<std::string>& mess)
 * @brief Metoda wirtualna wyświetlająca zawartość tekstową podaną w argumencie/argumentach funkcji
 * Metoda korzysta z iteratorów, które wyświetlają całą zawartość kontenera "list".
 * @tparam M - wzór reprezentujący typ wartości wprowadzanych do macierzy (int/double)
 * @param mess - kontener "list", przechowujący listę wiadomości, jakie mają się wyświetlić w konsoli
 */
template<class M>
void MatrixAbstract<M>::finalMathInfo(const std::list<std::string>& mess) {
  for(auto pos = mess.begin(); pos != mess.end(); pos++) {
    std::cout << *pos << "\n";
  }
}

template class matrixAbstractPackage::MatrixAbstract<int>;
template class matrixAbstractPackage::MatrixAbstract<double>;