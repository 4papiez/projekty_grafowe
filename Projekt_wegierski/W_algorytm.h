///////////////////////////////////////////////////////////////////////////////
#ifndef W_ALGORYTM_H
#define W_ALGORYTM_H

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <stdlib.h>
#include <cfloat>

using namespace std;

class W_algorytm{
	public:
            W_algorytm(vector<vector<double>> TabWag, int ilePodm);
            W_algorytm();
            ~W_algorytm();
            double get_wynik() { return wynik; }
            vector<vector<bool>> get_PrzypisanieMac() { return PrzypisanieMac; }

	private:
            vector<vector<double>> generMacKosztowa(vector<vector<double>> TabWag, int ilePodm);
            vector<vector<bool>> generMacPrzypisan();
			
            void rozpocznij(int *tab_przypisan, double *KosztMac);
            void sprawdz(int *tab_przypisan, double *KosztMac, int min_rozm);
            void popraw(int *tab_przypisan, double *KosztMac, int min_rozm);
            void krok_3(int *tab_przypisan, double *KosztMac, int min_rozm,
                        int wiersz, int kolumna);
            void krok_4(int *tab_przypisan, double *KosztMac, int min_rozm);
            double Wylicz();
			
            vector<vector<double>> TabWag;
            vector<vector<double>> MacKosztowa;
            vector<int> Przypisanie;
            vector<vector<bool>> PrzypisanieMac;
            double wynik;
            int podm;
            bool *PokrycieKolumn, *PokrycieWierszy, *ZaznMac, *NowaZaznMac, *TempMac;
            int lwierszy, lkolumn, liczba_elem;
};


#endif
