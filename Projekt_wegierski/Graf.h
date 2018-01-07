#ifndef Graf_H
#define Graf_H
#include<stdexcept>
#include<cstdlib>
#include<fstream>
class GrafBase{
	public:
        GrafBase():_tab(0),_n(0){}
		virtual ~GrafBase();

		/**
		 * @return true jeżeli graf został wygenerowany, false gdy nie.
		 */
		bool init()const;

		/**
		 * @return Metoda zwraca macierz sąsiedztwa grafu.
		 * @throws std::runtime_exception W przypadku gdy nie wygenrowano grafu funkcjami generujGraf
		 */
		bool** getTab()const;

		/**
		 * Zapisuje graf do pliku
		 * @param str Sciezka do zapisu pliku.
		 * @throws std::runtime_exception w przypadku błedu otwarcia pliku.
		 */
		void zapiszGraf(const std::string str);

		static void zapiszGraf(const std::string str,bool** tab,const int n,const int l);
        int getN()const{return _n;}
		int getL()const{return _l;}
	protected:
		/**
		 * Funkcja dealokuje poprzednia tablice jezeli taka istaniała. Nie nalezy zmieniać _n na nowe przed jej wykonaniem.
		 * Alokuje tablice 2D o rozmiarach n x n; Uruchamia losowość.
		 */
		void init(const int n);
		bool** _tab;
		int _n,_l;
		static bool init_random;
};
class Graf:public GrafBase{
public:
        Graf() {}
        Graf(int n) {init(n);}
		virtual ~Graf(){}

		/**
		 * @param n Ilosc wiercholkow generowanego grafu. n>0
		 * @param l Ilosc krawedzi w grafie. Wartosc l musi być mniejsza od maksIloscKrawedzi(n).
		 * @throws std::runtime_exception w przypadku zlych argumentow
		 */
		void generujGrafKraw(const int n,const int l);

		/**
		 * @param n Ilosc wiercholkow generowanego grafu. n>0
		 * @param p Prawdopodobienstwo istnienia krawedzi z przedzialu [0,1].
		 * @throws std::runtime_exception w przypadku zlych argumentow
		 */
		void generujGrafPrawd(const int n,const double p);

		/**
		 * Tworzy graf w oparciu o plik *.graf
		 * @param str scieżka do pliku
		 * @throws std::runtime_exception
		 */
		void generujGrafPlik(const std::string str);

        /**
         * Oblicza (n 2) - dwumian Newtona. To może być przydatne przy określaniu przedziałow z jakich bedzie sie wybierac paramatr l do generujGrafKraw.
         * Tak żeby l było mniejsze od wyniku z tej funkcji;
         * @param n Ilosc wierzcholkow analizowanego grafu.
         * @return Maksymalna ilosc krawedzi przy n wierzchołkach.
         */
		static int maksIloscKrawedzi(const int n);

        void addTab(bool** tab) {_tab = tab;}

	private:
		static int dwumianNewtona(const int n,const int k);
		static int nwd(const int a,const int b);
		static void getKrawedz(int kMax,int n,int idK,int &n1,int &n2);
};

#endif
