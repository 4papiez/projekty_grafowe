#include "w_algorytm.h"


W_algorytm::W_algorytm(vector<vector<double>> TabWagIN, int ilePodm){
    this->TabWag = TabWagIN;
    this->podm = ilePodm;
    this->MacKosztowa = generMacKosztowa(TabWag, ilePodm);
    lwierszy = MacKosztowa.size();
    lkolumn = MacKosztowa[0].size();
    liczba_elem = lwierszy * lkolumn;
    //alokacja pomocniczych macierzy
    //PokrycieKolumn = new bool[lkolumn];
    //PokrycieWierszy = new bool[lwierszy];
    PokrycieWierszy = (bool*)calloc(lwierszy, sizeof(bool));
    PokrycieKolumn = (bool*)calloc(lkolumn, sizeof(bool));
    ZaznMac = (bool*)calloc(liczba_elem, sizeof(bool));
    NowaZaznMac = (bool*)calloc(liczba_elem, sizeof(bool));
    //NowaZaznMac = new bool[liczba_elem];
    this->wynik = Wylicz();
}


vector<vector<double>> W_algorytm::generMacKosztowa (vector<vector<double>> TabWag, int ilePodm){
	int ilePrac = TabWag[0].size();
	vector<vector<double>> wynik;
	vector<double> temp;
	for(int i = 1; i < ilePodm+1; i++){
		for (int j = ilePodm+1; j < ilePrac-1; j++)
			temp.push_back(TabWag[i][j]?TabWag[i][j]:DBL_MAX);
		wynik.push_back(temp);
		temp.clear();
	}
	return wynik;
}


W_algorytm::W_algorytm() {}


W_algorytm::~W_algorytm() {
	free(PokrycieWierszy);
    //delete[] PokrycieWierszy;
    free(PokrycieKolumn);
    //delete[] PokrycieKolumn;
    free(ZaznMac);
    free(NowaZaznMac);
    free(TempMac);
    //delete[] TempMac;
}


vector<vector<bool>> W_algorytm::generMacPrzypisan() {
	vector<vector<bool>> wynik;
	vector<bool> temp;
	int rozm = this->TabWag.size();
	for (int i = 0; i < rozm; i++) {
		for (int j = 0; j < rozm; j++)
			temp.push_back(false);
		wynik.push_back(temp);
		temp.clear();
	}
    for (unsigned int x = 0; x < this->MacKosztowa.size(); x++)
        wynik[x+1][this->Przypisanie[x]+podm+1] = wynik[this->Przypisanie[x]+podm+1][x+1] = true;

	return wynik;
}

//funkcja zwracjąca wynik optymalny
double W_algorytm::Wylicz(){
	
	double *KosztMacIn = new double[lwierszy * lkolumn];
	int *tab_przypisan = new int[lwierszy];
	double koszt = 0.0;
    for (int i = 0; i < lwierszy; i++)
        for (int j = 0; j < lkolumn; j++)
            KosztMacIn[i + lwierszy * j] = MacKosztowa[i][j];
		
    rozpocznij(tab_przypisan, KosztMacIn);

	Przypisanie.clear();
    for (int r = 0; r < lwierszy; r++)
            Przypisanie.push_back(tab_przypisan[r]);

    this->PrzypisanieMac = generMacPrzypisan();
    for(unsigned int i = 0;i<TabWag.size();i++)
        for(unsigned int j = i; j<TabWag[1].size();j++)
            if (PrzypisanieMac[i][j])
                koszt += TabWag[i][j];

	delete[] KosztMacIn;
	delete[] tab_przypisan;
	return koszt;
}



// algorytm węgierski ---------------------------------------------------------------------

void W_algorytm::rozpocznij(int *tab_przypisan, double *KosztMacIn){

	double *KosztMac, *KosztMacTemp, *KosztMacEnd, *kolumnaumnEnd, value, minValue;
	int min_rozm, wiersz, kolumna;

	//inicjalizacja

    for (wiersz = 0; wiersz < lwierszy; wiersz++)
		tab_przypisan[wiersz] = -1;

	// kopia macierzy KosztMac

    KosztMac = new double[liczba_elem];
	KosztMacEnd = KosztMac + liczba_elem;

	for (wiersz = 0; wiersz < liczba_elem; wiersz++){
		value = KosztMacIn[wiersz];
		if (value < 0)
			cerr << "Koszta muszą być nieujemne!" << endl;
		KosztMac[wiersz] = value;
	}

    //TempMac = new bool[liczba_elem];
    TempMac = (bool*)calloc(liczba_elem, sizeof(bool));// macierz położenia zer

	if (lwierszy <= lkolumn){
		min_rozm = lwierszy;
		//Krok 1
		for (wiersz = 0; wiersz < lwierszy; wiersz++){
			KosztMacTemp = KosztMac + wiersz;
			minValue = *KosztMacTemp;
			KosztMacTemp += lwierszy;
			while (KosztMacTemp < KosztMacEnd){
				value = *KosztMacTemp;
				if (value < minValue)
					minValue = value;
				KosztMacTemp += lwierszy;
			}

			KosztMacTemp = KosztMac + wiersz;
			while (KosztMacTemp < KosztMacEnd){
				*KosztMacTemp -= minValue;
				KosztMacTemp += lwierszy;
			}
		}

		//Krok 3
		for (wiersz = 0; wiersz<lwierszy; wiersz++)
			for (kolumna = 0; kolumna<lkolumn; kolumna++)
				if (fabs(KosztMac[wiersz + lwierszy*kolumna]) < 1e-10)
					if (!PokrycieKolumn[kolumna]){
						ZaznMac[wiersz + lwierszy*kolumna] = true;
						PokrycieKolumn[kolumna] = true;
						break;
					}
	}
	else{
		min_rozm = lkolumn;
		//krok 2
		for (kolumna = 0; kolumna<lkolumn; kolumna++){
			KosztMacTemp = KosztMac + lwierszy*kolumna;
			kolumnaumnEnd = KosztMacTemp + lwierszy;

			minValue = *KosztMacTemp++;
			while (KosztMacTemp < kolumnaumnEnd){
				value = *KosztMacTemp++;
				if (value < minValue)
					minValue = value;
			}
			KosztMacTemp = KosztMac + lwierszy*kolumna;
			while (KosztMacTemp < kolumnaumnEnd)
				*KosztMacTemp++ -= minValue;
		}

		//Krok 3
		for (kolumna = 0; kolumna<lkolumn; kolumna++)
			for (wiersz = 0; wiersz<lwierszy; wiersz++)
				if (fabs(KosztMac[wiersz + lwierszy*kolumna]) < 1e-10)
					if (!PokrycieWierszy[wiersz]){
						ZaznMac[wiersz + lwierszy*kolumna] = true;
						PokrycieKolumn[kolumna] = true;
						PokrycieWierszy[wiersz] = true;
						break;
					}
		for (wiersz = 0; wiersz<lwierszy; wiersz++)
			PokrycieWierszy[wiersz] = false;

	}
	//sprawdz czy koniec
    sprawdz(tab_przypisan
            ,KosztMac
            ,min_rozm);

    int nwiersz, nkolumna;

	//czyszczenie pamięci
    delete[] KosztMac;
    
	return;
}


void W_algorytm::sprawdz(int *tab_przypisan, double *KosztMac, int min_rozm){
    int l_pokrytych_kolumn;

	l_pokrytych_kolumn = 0;
    for (int kolumna = 0; kolumna<lkolumn; kolumna++)
		if (PokrycieKolumn[kolumna])
			l_pokrytych_kolumn++;

	if (l_pokrytych_kolumn == min_rozm){
		//koniec algorytmu
        for (int wiersz = 0; wiersz<lwierszy; wiersz++)
            for (int kolumna = 0; kolumna<lkolumn; kolumna++)
                if (ZaznMac[wiersz + lwierszy*kolumna]){
					tab_przypisan[wiersz] = kolumna;
					break;
				}
	}
	else{
		//popraw
        popraw(tab_przypisan
               ,KosztMac
               ,min_rozm);
	}

}

//--------------------------------------------------------------------------------------------------------------
void W_algorytm::popraw(int *tab_przypisan, double *KosztMac, int min_rozm){
	bool zerosFound;
    int zaznKolumna;

	zerosFound = true;
	while (zerosFound){
		zerosFound = false;
        for (int kolumna = 0; kolumna<lkolumn; kolumna++)
			if (!PokrycieKolumn[kolumna])
                for (int wiersz = 0; wiersz<lwierszy; wiersz++)
					if ((!PokrycieWierszy[wiersz]) && (fabs(KosztMac[wiersz + lwierszy*kolumna]) < 1e-10)){
						TempMac[wiersz + lwierszy*kolumna] = true;
						for (zaznKolumna = 0; zaznKolumna<lkolumn; zaznKolumna++)
							if (ZaznMac[wiersz + lwierszy*zaznKolumna])
								break;
						//jeśli nie ma zer:
						if (zaznKolumna == lkolumn){
							//Krok 3
                            krok_3(tab_przypisan
                                   ,KosztMac
                                   ,min_rozm
                                   ,wiersz
                                   ,kolumna);
							return;
						}
						else{
							PokrycieWierszy[wiersz] = true;
							PokrycieKolumn[zaznKolumna] = false;
							zerosFound = true;
							break;
						}
					}
	}
	//Krok 4
    krok_4(tab_przypisan
           ,KosztMac
           ,min_rozm);
}

//------------------------------------------------------------------------------------------------------
void W_algorytm::krok_3(int *tab_przypisan, double *KosztMac, int min_rozm, int wiersz, int kolumna){

	int n, zaznWiersz, zaznKolumna, polWiersz, polKolumna;
	int liczba_elem = lwierszy*lkolumn;

	//kopia macierzy oznaczeń zer
	for (n = 0; n<liczba_elem; n++)
		NowaZaznMac[n] = ZaznMac[n];
	
	NowaZaznMac[wiersz + lwierszy*kolumna] = true;
	zaznKolumna = kolumna;
	for (zaznWiersz = 0; zaznWiersz<lwierszy; zaznWiersz++)
		if (ZaznMac[zaznWiersz + lwierszy*zaznKolumna])
			break;

	while (zaznWiersz<lwierszy){
		NowaZaznMac[zaznWiersz + lwierszy*zaznKolumna] = false;
		polWiersz = zaznWiersz;
		for (polKolumna = 0; polKolumna<lkolumn; polKolumna++)
			if (TempMac[polWiersz + lwierszy*polKolumna])
				break;

		NowaZaznMac[polWiersz + lwierszy*polKolumna] = true;

		zaznKolumna = polKolumna;
		for (zaznWiersz = 0; zaznWiersz<lwierszy; zaznWiersz++)
			if (ZaznMac[zaznWiersz + lwierszy*zaznKolumna])
				break;
	}

	for (n = 0; n<liczba_elem; n++)
	{
		TempMac[n] = false;
		ZaznMac[n] = NowaZaznMac[n];
	}
	for (n = 0; n<lwierszy; n++)
		PokrycieWierszy[n] = false;

	//ukryj kolumny (wykreśl)
	bool *ZaznMacTemp, *kolumnaumnEnd;

	for (kolumna = 0; kolumna<lkolumn; kolumna++)
	{
		ZaznMacTemp = ZaznMac + lwierszy*kolumna;
		kolumnaumnEnd = ZaznMacTemp + lwierszy;
		while (ZaznMacTemp < kolumnaumnEnd) {
			if (*ZaznMacTemp++){
				PokrycieKolumn[kolumna] = true;
				break;
			}
		}
	}

	//sprawdz czy koniec algorytmu
    sprawdz(tab_przypisan
            ,KosztMac
            ,min_rozm);
}

//--------------------------------------------------------------------------------------------------
void W_algorytm::krok_4(int *tab_przypisan, double *KosztMac, int min_rozm){

	double h, value;
	int wiersz, kolumna;

	h = DBL_MAX;
	for (wiersz = 0; wiersz<lwierszy; wiersz++)
		if (!PokrycieWierszy[wiersz])
			for (kolumna = 0; kolumna<lkolumn; kolumna++)
				if (!PokrycieKolumn[kolumna]){
					value = KosztMac[wiersz + lwierszy*kolumna];
					if (value < h)
						h = value;
				}

	for (wiersz = 0; wiersz<lwierszy; wiersz++)
		if (PokrycieWierszy[wiersz])
			for (kolumna = 0; kolumna<lkolumn; kolumna++)
				KosztMac[wiersz + lwierszy*kolumna] += h;

	for (kolumna = 0; kolumna<lkolumn; kolumna++)
		if (!PokrycieKolumn[kolumna])
			for (wiersz = 0; wiersz<lwierszy; wiersz++)
				KosztMac[wiersz + lwierszy*kolumna] -= h;

	//popraw
    popraw(tab_przypisan
           ,KosztMac
           ,min_rozm);
}
