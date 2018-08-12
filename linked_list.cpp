#include <stdio.h> //prinf gibi basit io kütüphanesi
#include <stdlib.h> // malloc focsiyonunun bulunduğu kütüphane

/* Liked listlere erişim sequentialdır. Bunun anlamı hangi elemana
ulaşmak istersek isteyelim, rootdan başlayıp o node'a giden her node'un
pointer'ını ziyaret edip, istediiğimiz node'a ulaşırız
Arraylar ise random access'dir. Yani istediğimiz elemana şötenek diye
ulaşabiliriz. eg.a[8];
*/
struct linked {
  int deger;
  linked* pointer = NULL;
};
// typedef linked* node;
/* daha sonra bu nodelara erişmemiz gerektiğinde kullanılacakmış sanırım
 şimdilik yazmayacağım hata vericeği anı bekleyeceğim.
 üstteki kodu yorumdan çıkarttıktan sonra maindeki her linked
 datatype'ını node ile değiştirmeliyim.
*/

void bastir (linked* r){
  while(r != NULL){
    printf("%d\n", r -> deger);
    r = r -> pointer;
  }
}

void ekle (linked* r, int x){
  while(r -> pointer != NULL){
    r = r -> pointer;
  }
  r -> pointer = (linked*)malloc(sizeof(int));
  r = r -> pointer;
  r -> deger = x;
  r -> pointer = NULL;
}

linked* arayaEkle (linked* r, int x, int index){
  linked* temp = (linked*)malloc(sizeof(int));
  temp -> deger = x;
  if (r == NULL){ // LinkList Boş ise
    temp -> pointer = NULL;
    return temp;
  }
  else if (index == 1){ // Başa ekliyeceksek
    temp -> pointer = r;
    return temp;
  }
  else{  //Geri kalan durumlar
    linked* iter = r;
    int i;
    for(i = 2; i < index && iter -> pointer != NULL; i++)
      iter = iter -> pointer;
    if(iter -> pointer == NULL){
      printf("%d degeri %d tane eleman olmadigi icin %d'inci eleman olarak eklendi\n"
              , x, index, i);
    }
    temp -> pointer = iter -> pointer;
    iter -> pointer = temp;
    return r;
  }
}

linked* ekleSirali(linked* r, int x){
  if (r == NULL){  // LinkList boş ise
    r = (linked*)malloc(sizeof(int));
    r -> deger = x;
    r -> pointer = NULL;
    return r;
  }
  else if (x < r -> deger){  // İlk Eleman yerine geçicek ise
    linked* temp = (linked*)malloc(sizeof(int));
    temp -> pointer = r;
    temp -> deger = x;
    return temp;
  }
  else{ //Geri Kalan durumlar
    linked* iter = r;
    while(iter -> pointer != NULL && x > iter -> pointer -> deger)
      iter = iter -> pointer;
    linked* temp = (linked*)malloc(sizeof(int));
    temp -> pointer = iter -> pointer;
    iter -> pointer = temp;
    temp -> deger = x;
    return r;
  }
}

linked* indexSilme (linked* r, int index){
  linked* iter = r;
  if (index == 1){ // İlk Elemanı Silme Durumu
    r = r -> pointer;
    free(iter);
  }
  for(int i = 2; i < index && iter -> pointer != NULL; i++)
    iter = iter -> pointer;
  if(iter -> pointer == NULL) // Indexin Bulunmama Durumu
    printf("Bu indexte eleman bulunmamakta.\n");
  else{ // Geri Kalan Durumlar
    linked* temp = iter -> pointer;
    iter -> pointer = iter -> pointer -> pointer;
    free(temp);
  }
  return r;
}

linked* degerSilme (linked* r, int x){
  linked* iter = r;
  if(x == r -> deger){ // İlk Elemanı Silme Durumu
    r = r -> pointer;
    free(iter);
    return r;
  }
  while(iter -> pointer != NULL && iter -> pointer -> deger != x)
    iter = iter -> pointer;
  if(iter -> pointer == NULL)
    printf("Silmeye calistigin deger listede bulanmamaktadir.\n");
  else{
    linked* temp = iter -> pointer;
    iter -> pointer = iter -> pointer -> pointer;
    free(temp);
  }
  return r;
}

int main() {
  linked* root = (linked*)malloc(sizeof(int));
  root -> deger = 5;
  root -> pointer = NULL;
  linked* iter = root;

  while (iter->pointer != NULL){
    //printf("%d ", iter -> deger);
    iter = iter -> pointer;
  }
  int x;
  for(int i = 0; i < 7; i++){
    x = 5 * (2 + i);
    ekle(root, x);
  }
  root = ekleSirali(root, 37);
  root = indexSilme(root, 12);
  root = degerSilme(root, 5);
  bastir(root);
}

// !!!!!------NOTLAR-------!!!!!

/*  -1-1-1-1-1-1-1-1-
Şuan kodda bulunan while ve ekleme döngüsü sorunsuz çalışırken bu
kod anlamadığım bir hata vermekte mantığını çözene kadar burda kalsın

-----'''ÇÖZÜM'''----
kendin anlamaya çalış
cevap vy2 şadi reyiz 16' civarı

while (iter != NULL){
  //printf("%d ", iter -> deger);
  iter = iter -> pointer;
}
for(int i = 0; i < 5; i++){
  iter = (linked*)malloc(sizeof(int));
  iter -> deger = 5 * (4 + i);
  iter -> pointer = NULL;
  iter = iter -> pointer;
}
*/

/*  -2-2-2-2-2-2-2-2-
ekle donksiyonu yerine for döngüsü ile yazdığımız kod performans açısından
önemli bir derece daha hızlı olacaktır.

for(int i = 0; i < 5; i++){
  iter -> pointer = (linked*)malloc(sizeof(int));
  iter = iter -> pointer;
  iter -> deger = i*10;
  iter -> pointer = NULL;
}
*/

/* -3-3-3-3-3-3-3-3-
bunca zaman nodeları
linked* root = (linked*)malloc(sizeof(int));
kod satırı ile oluşturdum fakat şadi reyizin kaynağına göre
linked* root = (linked*)malloc(sizeof(linked));
şeklinde oluşturmam gerekiyormuş, hiçbir hata ile karşılaşmadım.
Hata ile karşılaşana kadar böyle devam ediceğim.
*/
