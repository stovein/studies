#include <stdio.h> //prinf gibi basit io kütüphanesi
#include <stdlib.h> // malloc focsiyonunun bulunduğu kütüphane

/* Liked listlere erişim sequentialdır. Bunun anlamı hangi elemana
ulaşmak istersek isteyelim, rootdan başlayıp o node'a giden her node'un
pointer'ını ziyaret edip, istediiğimiz node'a ulaşırız
Arraylar ise random access'dir. Yani istediğimiz elemana şötenek diye
ulaşabiliriz. eg.a[8];
*/

struct cl {
  int deger;
  cl* pointer = NULL;
};

// typedef linked* node;
/* daha sonra bu nodelara erişmemiz gerektiğinde kullanılacakmış sanırım
 şimdilik yazmayacağım hata vericeği anı bekleyeceğim.
 üstteki kodu yorumdan çıkarttıktan sonra maindeki her linked
 datatype'ını node ile değiştirmeliyim.
*/

void bastir (cl* r){
  cl* iter = r;
  while (iter -> pointer != r){
    printf("%d ", iter -> deger);
    iter = iter -> pointer;
  }
  if (iter !=  r) printf("%d ", iter -> deger);
  printf("\n\n");
}

void ekle(cl* r, int x){
  cl* iter = r;
  while (iter -> pointer != r){
    iter = iter -> pointer;
  }
  cl* node = (cl*)malloc(sizeof(int));
  iter -> pointer = node;
  node -> deger = x;
  node -> pointer = r;
}

cl* arayaEkle(cl* r, int x, int deger){
  cl* iter = r;
  while(iter -> pointer -> deger != deger && iter -> pointer != r)
    iter = iter -> pointer;
  if(iter -> pointer == r){
    if(iter -> pointer -> deger != deger){
      printf("%d degeri bulunamadi\n", deger);
      return r;
    }
    else if(iter -> pointer -> deger = deger){
      cl* node = (cl*)malloc(sizeof(int));
      node -> pointer = iter -> pointer;
      node -> deger = x;
      iter -> pointer = node;
      return node;
    }
  }
  else{
    cl* node = (cl*)malloc(sizeof(int));
    node -> pointer = iter -> pointer;
    node -> deger = x;
    iter -> pointer = node;
    return r;
  }
}

cl* siraliEkle(cl* r, int x){
    cl* iter = r;
  if(r == NULL){
    r = (cl*)malloc(sizeof(cl));
    r -> pointer = r;
    r -> deger = x;
    return r;
  }
  else if(x < iter -> deger){
    while(iter -> pointer != r) iter = iter -> pointer;
    cl* node = (cl*)malloc(sizeof(cl));
    node -> pointer = iter -> pointer;
    node -> deger = x;
    iter -> pointer = node;
    return node;
  }
  while(iter -> pointer != r && x > iter -> pointer -> deger)
    iter = iter -> pointer;
  cl* node = (cl*)malloc(sizeof(int));
  node -> pointer = iter -> pointer;
  node -> deger = x;
  iter -> pointer = node;
  return r;
}

cl* indexSilme(cl* r, int index){
  cl* iter = r;
  cl* temp;
  int i;
  if(index == 1){
    while(iter -> pointer != r)
      iter = iter -> pointer;
    temp = iter -> pointer;
    iter -> pointer = iter -> pointer -> pointer;
    free(temp);
    return iter -> pointer;
  }
  for(i = 2; i < index && iter -> pointer != r; i++)
    iter = iter -> pointer;
  if(i != index){
    printf("%d index'i bulunamadi; listenin total index sayisi: %d\n",index, i);
    return r;
  }
  temp = iter -> pointer;
  iter -> pointer = iter -> pointer -> pointer;
  free(temp);
  return r;
}

cl* degerSilme(cl* r, int deger){
  cl* iter = r;
  cl* temp;
  while(iter -> pointer != r && iter -> pointer -> deger != deger)
    iter = iter -> pointer;
  if (iter -> pointer == r){
    if (iter -> pointer -> deger != deger) {
      printf("%d degeri bulunamamkta :/", deger);
      return r;
    }
    temp = iter -> pointer;
    iter -> pointer = iter -> pointer -> pointer;
    free(temp);
    return iter -> pointer;
  }
  else {
    temp = iter -> pointer;
    iter -> pointer = iter -> pointer -> pointer;
    free(temp);
    return r;
  }
}

//  !!!!!------MAIN-------!!!!!

int main(){
  cl* root = NULL;
  root = siraliEkle(root, 10);
  root = siraliEkle(root, 5);
  root = siraliEkle(root, 35);
  root = siraliEkle(root, 15);
  root = siraliEkle(root, 25);
  root = siraliEkle(root, 20);
  root = siraliEkle(root, 30);

  bastir(root);

  root = degerSilme(root, 5);
  bastir(root);
  root = degerSilme(root, 15);
  bastir(root);
  root = degerSilme(root, 35);
  bastir(root);
  root = degerSilme(root, 330);

  return 0;
}
