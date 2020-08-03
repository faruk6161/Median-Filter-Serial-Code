//////////////////////////////////////////////////////////////////
//    					     			//
//                	Coded by Faruk OKSUZ			//
//                              				//
//////////////////////////////////////////////////////////////////	
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sys/time.h> //zaman hesabı için kullanılan kütüphane
// 5 * 5 penceremiz için kullandığım sabit değişmez yatay ve dikey eksen boyutu
#define pencereBoyutuYatay 5  
#define pencereBoyutuDikey 5

using namespace std;
void DiziyiSirala(int *,int ); //sıralama fonksiyonumun prototipi

int main(int argc, char* argv[])//komut satırında alınacak eleman sayısı ve bu dizi 
{
	//Geçen süre hesabını yapabilmek için kullandığım değişkenlerim
    struct timeval currentTime;
	double baslangic,bitis,gecenzaman;


    int satirSayisi, sutunSayisi; //dosyadan okunacak Matris ve yeniMatris için satır ve sutun sayisi
	const int pencereMerkezYatay = pencereBoyutuYatay / 2; //pencerenin yatay merkezi belirleniyor
	const int pencereMerkezDikey = pencereBoyutuDikey / 2; //pencerenin dikey merkezi belirleniyor
	const int sonPencereBoyutu = pencereBoyutuYatay * pencereBoyutuDikey; //pencere matrisinin eleman sayısı belirleniyor.
	const int pencereOrtasi = sonPencereBoyutu / 2; //5*5 pencerem için Matrisin merkezi sıralı olacağından ortası lazım !
    int pencereMatrisi[sonPencereBoyutu];

    ifstream dosyaoku(argv[1]); //komut satırından alınacak txt dosyası için argv[1] argumanı dosya okuma modunda
    dosyaoku >> satirSayisi >> sutunSayisi; //dosyadan satır ve sutun boyutları okunuyor.


    	
	int * yeniMatris = new int[satirSayisi*sutunSayisi];
	//Matrisin tek boyutta tanımlanıp . Dosyadan okuma işlemi bu kısımda gerçekleşiyor.
	int *matrixPtr = new int[satirSayisi * sutunSayisi];



    for (int i = 0; i < satirSayisi; i++)
    {
        for(int j = 0; j < sutunSayisi; j++)
        {
           dosyaoku >> matrixPtr[i * sutunSayisi + j]; //matris elemanlarına değer atanması tek boyutlu matrisin 2 boyutta temsili
        }
    }
    dosyaoku.close(); //dosyadan okunan matris için dosya kapanıyor 

	for (int i = 0; i < satirSayisi; i++)
    {
        for(int j = 0; j < sutunSayisi; j++)
        {
           cout<< matrixPtr[i * sutunSayisi + j]<<" "; //matris elemanlarına değer atanması tek boyutlu matrisin 2 boyutta temsili
        }
		cout<< endl ;
    }



    
	//filtreleme işlemi başlangıcı için kullanılan değişkenlerim
    gettimeofday(&currentTime,NULL); //o an ki zamanı alan baslangic fonksiyonu. currentTime aracalığıyla <-
	baslangic=currentTime.tv_sec+(currentTime.tv_usec/1000000.0);
	//Filtreleme başlıyor .
    for (int i = pencereMerkezYatay; i < (satirSayisi - pencereMerkezYatay); i++) //ilk 2 satır son 2 satırdan öncesine kadar 
    {
		for (int j = pencereMerkezDikey; j < (sutunSayisi - pencereMerkezDikey); j++) // ilk 2 sutundan son 2 sutundan öncesine kadar
		{
			//pencere başlıyor .5*5
			for (int m = 0; m < pencereBoyutuYatay; m++) //yatayda 5 
			{
				for (int n = 0; n < pencereBoyutuDikey; n++) //dikeyde 5 
				{
					//5*5 pencere matrisine elemanların atama işlemi 
					pencereMatrisi[m * pencereBoyutuDikey + n] = matrixPtr[(i - pencereMerkezYatay + m) * sutunSayisi + (j - pencereMerkezDikey + n)];
				}
			}
            DiziyiSirala(pencereMatrisi, sonPencereBoyutu); //Her bir pencere elemanları için sıralama işlemi 5*5
            matrixPtr[i * sutunSayisi +j] = pencereMatrisi[pencereOrtasi];//pencerenin ortanca elemanı her pencere sıralandıktan sonra yenimatrise kopyalanıyor.
		}
	}
	//Filtreleme bitti.
    gettimeofday(&currentTime,NULL); //o an ki zamanı alan bitiş fonksiyonu. currentTime aracalığıyla <-
	bitis=currentTime.tv_sec+(currentTime.tv_usec/1000000.0);  //gecen süre saniye cinsinden
	gecenzaman=bitis-baslangic; //geçen zaman hesabi saniye cinsinden .
    cout<<"Filtreleme islemi icin gecen zaman :"<<gecenzaman;


    ofstream DosyaYaz;
    string filtrelenecekTxt;
    for(int i = 22; i < 38; i++) // sadece dosya alımı için alt sınır ve üst sınır 
    {   
		if(i<37)
		{
			filtrelenecekTxt +=argv[1][i]; // komut satırında alınacak olan txt dosyasının formatlı yolunu belirliyoruz.
		}
		if(i==37)// 10 ve 11 . txt dosya uzantısı için şart.
		{
			//ilgili txt ler için şart belirlenirse 
			if(argv[1]=="/opt/goruntuDosyalari/GoruntuMatrisi10.txt")
			{
				//filtrelenecekTxt.push_back('0');
				filtrelenecekTxt = "GoruntuMatrisi10";
				break;
			}
			else if(argv[1]=="/opt/goruntuDosyalari/GoruntuMatrisi11.txt")
			{
				//filtrelenecekTxt.push_back('1');
				filtrelenecekTxt ="GoruntuMatrisi11";
				break;
			}
		}
	}
   
   // komut satırında alınacak olan txt dosyasının formatlı yolunu belirliyoruz.
    DosyaYaz.open(filtrelenecekTxt + "_filtered.txt");//uzantısı "_filtered.txt" şekilde dosya açıldı 
	//Dosya yazma işlemi başladı .
    for(int i = 0; i < satirSayisi; i++)
    {
        for(int j = 0; j < sutunSayisi; j++)
        {
            DosyaYaz<<matrixPtr[i *sutunSayisi +j]<<"\t";
        }
        DosyaYaz<<endl;
    }
    DosyaYaz.close(); //Dosya yazmadı işlemi bitti ve dosya kapandı .


	//Kullanılan tüm matrisler belli işlemler sonucunda Ram e geri iade ediyor . Deallocation
    delete[] matrixPtr; 
	delete[] yeniMatris; 
	
	
    return 0;
}
void DiziyiSirala(int *dizi,int n) // Sıralama Fonksiyonum . Pointer dizi için BubbleSort
{
    for (int j = 0; j < n ; j++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            if (*(dizi+i) > *(dizi+i+1))
            {
                int gecici = *(dizi+i+1);
                *(dizi+i+1) = *(dizi+i);
                *(dizi+i) = gecici;
            }
        }
    }
}
