#ifndef Graf_H
#define Graf_H
#include<stdexcept>
#include<cstdlib>
#include<fstream>
class GrafBase{
	public:
        GrafBase():_tab(0),_n(0){}
		virtual ~GrafBase();
         // true jeżeli graf został wygenerowany, false gdy nie.
		bool init()const;


         //Metoda zwraca macierz sąsiedztwa grafu.
        int** getTab()const;
		void zapiszGraf(const std::string str);

        static void zapiszGraf(const std::string str,int** tab,const int n,const int l);
        int getN()const{return _n;}
		int getL()const{return _l;}
	protected:
        /*
		 * Funkcja dealokuje poprzednia tablice jezeli taka istaniała. Nie nalezy zmieniać _n na nowe przed jej wykonaniem.
		 * Alokuje tablice 2D o rozmiarach n x n; Uruchamia losowość.
		 */
		void init(const int n);
        int** _tab;
		int _n,_l;
		static bool init_random;
};
class Graf:public GrafBase{
public:
        Graf() {}
        Graf(int n) {init(n);}
		virtual ~Graf(){}

        /*
         * n Ilosc wiercholkow generowanego grafu. n>0
         * l Ilosc krawedzi w grafie. Wartosc l musi być mniejsza od maksIloscKrawedzi(n).
         */
        void generujGrafKraw(const int n,const int l,const int maxi_wart);

        /*
         * n Ilosc wiercholkow generowanego grafu. n>0
         * p Prawdopodobienstwo istnienia krawedzi z przedzialu [0,1].
		 */
        void generujGrafPrawd(const int n,const double p,const int maxi_wart);

        // Tworzy graf w oparciu o plik *.graf
		void generujGrafPlik(const std::string str);
		static int maksIloscKrawedzi(const int n);

        void addTab(int** tab) {_tab = tab;}

	private:
		static int dwumianNewtona(const int n,const int k);
		static int nwd(const int a,const int b);
		static void getKrawedz(int kMax,int n,int idK,int &n1,int &n2);
};

#endif
