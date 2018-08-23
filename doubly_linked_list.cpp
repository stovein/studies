#include<stdio.h> //printf scanf
#include<stdlib.h> //malloc

//NOT FULLY TESTED

/* Liked listlere erişim sequentialdır. Bunun anlamı hangi elemana
ulaşmak istersek isteyelim, rootdan başlayıp o node'a giden her node'un
pointer'ını ziyaret edip, istediiğimiz node'a ulaşırız
Arraylar ise random access'dir. Yani istediğimiz elemana şötenek diye
ulaşabiliriz. eg.a[8];
*/

struct dl {
  int val;
  dl* prev = NULL;
  dl* next = NULL;
};

// typedef linked* node;
/* daha sonra bu nodelara erişmemiz gerektiğinde kullanılacakmış sanırım
 şimdilik yazmayacağım hata vericeği anı bekleyeceğim.
 üstteki kodu yorumdan çıkarttıktan sonra maindeki her linked
 datatype'ını node ile değiştirmeliyim.
*/

void bastir(dl* r){
  while (r != NULL){
    printf("%d ", r-> val);
    r = r -> next;
  }
  printf("\n\n");
}

void ekle(dl* r, int x){
  if (r == NULL) {
    dl* node = (dl*)malloc(sizeof(dl));
    r = node;
    node -> prev = NULL;
    node -> next = NULL;
    node -> val = x;
  }
  while (r -> next != NULL) r = r -> next;
  dl* node = (dl*)malloc(sizeof(dl));
  r -> next = node;
  node -> next = NULL;
  node -> val = x;
  node -> prev = r;
}

dl* arayaEkle(dl* r, int x, int deger){
  dl* iter = r;
  if (r -> val == deger) {
    dl* node = (dl*)malloc(sizeof(dl));
    node -> prev = r -> prev;
    r -> prev = node;
    node -> next = r;
    node -> val = x;
    return node;
  }
  while (iter -> next != NULL && iter -> next -> val != deger)
    iter = iter -> next;
  if (iter -> next == NULL) {
    printf("%d degeri yok", deger);
  }
  dl* node = (dl*)malloc(sizeof(dl));
  iter -> next -> prev = node;
  node -> next = iter -> next;
  node -> prev = iter;
  iter -> next = node;
  node -> val = x;
  return r;

}

dl* siraliEkle(dl* r, int x){
  dl* iter = r;
  if (r == NULL) { //listenin bos olmasi
    dl* node = (dl*)malloc(sizeof(dl));
    node -> val = x;
    node -> next = NULL;
    node -> prev = NULL;
    return node;
  }
  else if (x < r -> val) { // ilk elemandan kucuk olmasi
      dl* node = (dl*)malloc(sizeof(dl));
      node -> prev = r -> prev;
      r -> prev = node;
      node -> next = r;
      node -> val = x;
      return node;
  }
  while (iter -> next != NULL && x > iter -> next -> val)
    iter = iter -> next;
  if(iter -> next == NULL){// listenin sonuna eklenmesi
    dl* node = (dl*)malloc(sizeof(dl));
    node -> next = iter -> next;
    node -> prev = iter;
    iter -> next = node;
    node -> val = x;
    return r;
  }
  dl* node = (dl*)malloc(sizeof(dl)); // diger durumlar
  iter -> next -> prev = node;
  node -> next = iter -> next;
  node -> prev = iter;
  iter -> next = node;
  node -> val = x;
  return r;
}

dl* indexSilme(dl* r, int index){
  dl* iter = r;
  if(index == 1){ // ilk index
    r = r -> next;
    r -> prev = r -> prev -> prev;
    free(iter);
    return r;
  }
  int i;
  dl* temp;
  for(int i = 2; iter -> next != NULL && i < index; i++)
    iter = iter -> next;
  if(iter -> next == NULL){ // index'in bulunamamasi
    printf("%d bulunamadı total index sayısı %d", index, i);
    return r;
  }
  else if (iter -> next -> next == NULL) { // son index
    temp = iter -> next;
    iter -> next = temp -> next;
    free(temp);
    return r;
  }
  temp = iter -> next;  // diger durumlar
  iter -> next = temp -> next;
  temp -> next -> prev = iter;
  free(temp);
  return r;
}

dl* degerSilme(dl* r, int x){
  dl* iter = r;
  if (r -> val == x){
    r = r -> next;
    r -> prev = r -> prev -> prev;
    free(iter);
    return r;
  }
  while(iter -> next != NULL && iter -> next -> val != x)
    iter = iter -> next;
  if (iter -> next == NULL) {
    printf("%d degeri yok\n\n", x);
    return r;
  }
  else if (iter -> next -> next == NULL) {
    dl* temp = iter -> next;
    iter -> next = temp -> next;
     free(temp);
     return r;
  }
  dl* temp = iter -> next;
  iter -> next = temp -> next;
  temp -> next -> prev = iter;
  free(temp);
  return r;
}

//  !!!!!------MAIN-------!!!!!

int main(){
  dl* root = NULL;

  root = siraliEkle(root, 25);
  root = siraliEkle(root, 335);
  root = siraliEkle(root, 55);
  root = siraliEkle(root, 580);
  root = siraliEkle(root, 5);
  root = siraliEkle(root, 75);

  bastir(root);

  root = degerSilme(root, 335);
  bastir(root);

  root = degerSilme(root, 580);
  bastir(root);

  root = degerSilme(root, 5);
  bastir(root);

  root = degerSilme(root, 9999);
  bastir(root);

  return 0;
}
