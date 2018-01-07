#include <ctime>
#include "Graf.h"
bool GrafBase::init_random=false;
//------------------------------------------------
void Graf::generujGrafKraw(const int n,const int l){
    int kMax=dwumianNewtona(n,2);
    _l=l;
    if(kMax<l||l<0)
        throw std::runtime_error("Graf::generujGrafKraw : Błedna ilosc krawedzi");
    if(n<=0)
        throw std::runtime_error("Graf::generujGrafKraw : Błedna liczba wierzcholkow");
    if(n==1&&l==1)
        throw std::runtime_error("Graf::generujGrafKraw : Błedna ilosc krawedzi");
    init(n);
    bool grafRzadki=(kMax/2>l);
    if(grafRzadki==false){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                _tab[i][j]=(i!=j)?true:false;
        }
    }
    int tl=grafRzadki?(l):(kMax-l);
    int n1=0,n2=0;
    for(int i=0;i<tl;i++){
        if(n==1)
          break;
        do{
        getKrawedz(kMax,n,std::rand()%kMax,n1,n2);
          }while(_tab[n1][n2]==grafRzadki);

        _tab[n1][n2]=grafRzadki;
        _tab[n2][n1]=grafRzadki;
    }
}
void Graf::generujGrafPrawd(const int n,const double p){
	if(p<0||p>1)
		throw std::runtime_error("Graf::generujGrafPrawd : Błedne prawd");
	if(n<=0)
		throw std::runtime_error("Graf::generujGrafPrawd : Błedna liczba wierzcholkow");
	init(n);
	_l=0;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(((double)(std::rand()%1000))/1000<p){
				_tab[i][j]=true;
				_tab[j][i]=true;
				_l++;
			}
		}
	}
}
void GrafBase::zapiszGraf(const std::string str){
  if(init()==false)
    throw  std::runtime_error("Graf::zapiszGraf : Bład inicjalizacji");
  zapiszGraf(str,_tab,_n,_l);
}
void GrafBase::zapiszGraf(const std::string str,bool** tab,const int n,const int l){
  std::fstream plik;
  plik.open(str.c_str(),std::ios::out);
  if(tab==0||tab==NULL||n<=0||l<0||l>Graf::maksIloscKrawedzi(n))
      throw  std::runtime_error("Graf::zapiszGraf : Bład argumentu");
  if( plik.good() == false)
      throw std::runtime_error("Graf::zapiszGraf : Bład pliku");
  plik<<n<<" "<<l<<std::endl;
  for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
          if(tab[i][j]==true){
              plik<<i<<" "<<j<<std::endl;
            }
        }
    }
  plik.close();
}
//------------------------------------------------
void Graf::generujGrafPlik(const std::string str){
  if(str.find(".graf")==std::string::npos)
    throw std::runtime_error("Graf::generujGrafPlik : Błedny format pliku");
   std::fstream plik;
  plik.open(str.c_str(),std::ios::in);
  if( plik.good() == false)
      throw std::runtime_error("Graf::generujGrafPlik : Bład odczytu pliku");
  int n,n1,n2;
  plik>>n>>_l;
  if(n<=0||_l<0||_l>maksIloscKrawedzi(n))
                throw std::runtime_error("Graf::generujGrafPlik : Bład pliku");
  init(n);
  for(int i=0;i<_l;i++){
      plik>>n1>>n2;
      _tab[n1][n2]=true;
      _tab[n2][n1]=true;
    }
  plik.close();
}

//------------------------------------------------
GrafBase::~GrafBase(){
	for(int i=0;i<_n;i++)
		delete[] _tab[i];
	delete[] _tab;
}
//------------------------------------------------
int Graf::maksIloscKrawedzi(const int n){
	return dwumianNewtona(n,2);
}
bool** GrafBase::getTab() const{
	if(_tab==0)
        throw std::runtime_error("Graf::getTab : Pobierasz macierz sąsiedztwa bez wczesniejszego zainicjalizowania");
	return _tab;
}

bool GrafBase::init()const{
	return (_n>0&&_tab!=0);
}
//////////////////////////////////////////////////
void GrafBase::init(const int n){
	for(int i=0;i<_n;i++)
		delete[] _tab[i];
	delete[] _tab;
	_tab=new bool*[n];
	for(int i=0;i<n;i++){
		_tab[i]=new bool[n];
		for(int j=0;j<n;j++)
			_tab[i][j]=false;
	}
	_n=n;
	if(init_random==false){
		std::srand(time(NULL));
		init_random=true;
	}
}
//------------------------------------------------
int Graf::dwumianNewtona(const int n,const int k){
	int licznik=1,mianownik=1,kT=(n-k>k)?(n-k):(k),temp;
	for(int i=kT+1;i<=n;i++){
		licznik*=i;
		mianownik*=(i-kT);
		temp=Graf::nwd(licznik,mianownik);
		licznik/=temp;
		mianownik/=temp;
	}
	return licznik;
}
//------------------------------------------------
int Graf::nwd(const int a,const int b){
	int temp,at=a,bt=b;
	while(bt!=0){
		temp=bt;
		bt=at%bt;
		at=temp;
	}
	return at;
}
//------------------------------------------------
void Graf::getKrawedz(int kMax,int n,int idK,int &n1,int &n2){
	int i=0;
	while(kMax!=0){
		kMax-=(n-1);
		if(idK>=kMax){
			n1=i;
			n2=idK-kMax+1+i;
			break;
		}
		n--;
		i++;
	}
}
