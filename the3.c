#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define doty deger.y
#define dots deger.s
#define dotp deger.p
#define dotc deger.c
#define dotf deger.f
#define dotx deger.x
#define dotz deger.z
#define sdty sample.y
#define sdts sample.s
#define sdtp sample.p
#define sdtc sample.c
#define sdtf sample.f
#define sdtx sample.x
#define sdtz sample.z

int adres=0,i=0,check=0,check2=0,array=0;
FILE *fp;
union global {
char y;
unsigned char s;
unsigned int p;
int c;
float f;
long x;
double z;}sample;
struct layout_verisi {
   char name[20];
   int type;
   int dim2;
   union {
    char y;
    unsigned char s;
    unsigned int p;
    int c;
    float f;
    long x;
    double z;} deger;
    int location;} veri[MAX] ;

int name_atayici(){
    char c;
    int sayac=0;
    while ((c=getchar()))
    {   if (c==44) break;
        else if(c==32) continue;
        else if(c==10){ check=-1;
                        break;}
        else if(c==91) {  array=55;
                          break;}
        else {((veri+i)->name)[sayac++]=c;}
    }
    ((veri+i)->name)[sayac]='\0';
return 0;
}

int index_bulucu(char index_name[20]){
  int n=0,deger=0;
  for( ; n<i ; n++){
      if(strcmp((veri+n)->name,index_name) == 0){
        switch((veri+n)->type){
        case 1:
        return deger=(veri+n)->dotc;
        case 2:
        return deger=(int)((veri+n)->dotf);
        case 3:
        return deger=(int)((veri+n)->dots);
        case 4:
        return deger=(int)((veri+n)->dotp);
        case 5:
        return deger=(int)((veri+n)->doty);
        case 6:
        return deger=(int)((veri+n)->dotx);
        case 7:
        return deger=(int)((veri+n)->dotz);}
      }}
return 0;
}

int array_dim(){
    char c,index1_name[20],index2_name[20];
    int str1len,str2len,s=0,k=0,deger1=0,deger2=0,sayac=0;
  if(array!=55) return 0;
  else{
    while ((c=getchar())!=93){
          if (c==32) continue;
          else index1_name[sayac++]=c;}
           index1_name[sayac]='\0';
           deger1=index_bulucu(index1_name);
           if (deger1==0){
             str1len = strlen(index1_name);
             for ( ; s < str1len; s++){
             k = 10 * k + (index1_name[s]-'0');}
             deger1=k;}

        while((c=getchar())!=44){
           if(c==10){ check=-1;
               break;}
          else if(c==91){
                  sayac=0;
        while ((c=getchar())!=93){
                    if (c==32) continue;
                    else index2_name[sayac++]=c;}
                    while((c=getchar())!=44){
            if(c==10){ check=-1;
            break;}}
                    index2_name[sayac]='\0';
                   deger2=index_bulucu(index2_name);
                 if (deger2==0){
                  str2len = strlen(index2_name);
                  for (s=0,k=0 ; s <str2len; s++){
                  k = 10 * k + (index2_name[s]-'0');}
                  deger2=k;}
                  (veri+i)->dim2=deger2;
                  return deger1*deger2;
                }}
    }
return deger1;
}

int floating_atayici(char a,char b){
    name_atayici();
    int dim=array_dim();
    if (a=='i'){
      if (dim) {adres+=(4*dim);
        (veri+i)->type=1;
      fseek(fp,4*dim,SEEK_CUR);}
      else{
      fread(&(sdtc), sizeof(int),1,fp);
      (veri+i)->dotc= sdtc;
(veri+i)->type=1;
      adres+=4;}
	}
    else if(a=='f'){
      if (dim) {adres+=(4*dim);
        (veri+i)->type=2;
      fseek(fp,4*dim,SEEK_CUR);}
      else{fread(&(sdtf), sizeof(float),1,fp);
      (veri+i)->dotf= sdtf;
(veri+i)->type=2;
      adres+=4;}
    }
    else if((a=='u') && (b=='c')){
      if (dim) {adres+=(1*dim);
        (veri+i)->type=3;
      fseek(fp,1*dim,SEEK_CUR);}
      else{
        fread(&(sdts), sizeof(unsigned char),1,fp);
      (veri+i)->dots= sdts;
(veri+i)->type=3;
      adres+=1;}
    }
    else if ((a=='u') && (b=='i')){
      if (dim) {adres+=(4*dim);
        (veri+i)->type=4;
      fseek(fp,4*dim,SEEK_CUR);}
      else{fread(&(sdtp), sizeof(unsigned int),1,fp);
      (veri+i)->dotp= sdtp;
(veri+i)->type=4;
      adres+=4;}
    }
    else if (a=='c'){
      if (dim) {adres+=(1*dim);
        (veri+i)->type=5;
      fseek(fp,1*dim,SEEK_CUR);}
      else{
        fread(&(sdty), sizeof(char),1,fp);
      (veri+i)->doty= sdty;
(veri+i)->type=5;
      adres+=1;}
    }
    else if (a=='l'){
      if (dim) {adres+=(8*dim);
        (veri+i)->type=6;
      fseek(fp,8*dim,SEEK_CUR);}
    else{
      fread(&(sdtx), sizeof(long),1,fp);
      (veri+i)->dotx= sdtx;
(veri+i)->type=6;
      adres+=8;}
    }
    else if (a=='d'){
      if (dim) {adres+=(8*dim);
        (veri+i)->type=7;
      fseek(fp,8*dim,SEEK_CUR);}
      else{fread(&(sdtz), sizeof(double),1,fp);
      (veri+i)->dotz= sdtz;
(veri+i)->type=7;
      adres+=8;}
    }
    ((veri+i+1)->location)=adres;
    i++;
    return 0;
}

int query_alici(char query_name[20]){
  char c,name[21];
  int sayac=0;
  while ((c=getchar())){
      if (c==44) break;
      else if(c==32) continue;
      else if(c==10){ check2=-1;
                      break;}
      else if(c==91) { array=55;
                        break;}
      else {name[sayac++]=c;}
  }

  name[sayac]='\0';
  strcpy(query_name, name);
return 1;
}
int scalar_basici(char index_name[20]){
  int n=0;
  for( ; n<i ; n++){
      if((strcmp((veri+n)->name,index_name)) == 0){
        if(((veri+n)->type)==1){
        printf("%d\n", (veri+n)->dotc);
        break;}
        else if(((veri+n)->type)==2){
        printf("%f\n", (veri+n)->dotf);
        break;}
        else if(((veri+n)->type)==3){
        printf("%u\n", (veri+n)->dots);
        break;}
        else if(((veri+n)->type)==4){
        printf("%u\n", (veri+n)->dotp);
        break;}
        else if(((veri+n)->type)==5){
        printf("%d\n", (veri+n)->doty);
        break;}
        else if(((veri+n)->type)==6){
        printf("%ld\n", (veri+n)->dotx);
        break;}
        else if(((veri+n)->type)==7){
        printf("%.6f\n", (veri+n)->dotz);
        break;} }
     else continue;
}}
int dim1_solver(){
  char c,index1_name[20];
  int str1len,s=0,k=0,deger1=0,sayac=0;
while ((c=getchar())!=93){
if (c==32) continue;
else index1_name[sayac++]=c;}
       index1_name[sayac]='\0';
       deger1=index_bulucu(index1_name);
       if (deger1==0){
         str1len = strlen(index1_name);
         for ( ; s < str1len; s++){
         k = 10 * k + (index1_name[s]-'0');}
         deger1=k;}
return deger1;}

int dim2_solver(){
  char c,index2_name[20];
  int str2len,s=0,k=0,deger2=0,sayac=0;
while((c=getchar())!=44){
if(c==10){ return -1;}
else if(c==91){
  while ((c=getchar())!=93){
    if (c==32) continue;
    else index2_name[sayac++]=c;}
    index2_name[sayac]='\0';
    deger2=index_bulucu(index2_name);
              if (deger2==0){
                  str2len = strlen(index2_name);
                  for (s=0,k=0 ; s <str2len; s++){
                  k = 10 * k + (index2_name[s]-'0');}
                  deger2=k;}
     return deger2; }}
return -3;
}
int okuprint(int n){
  switch ((veri+n)->type){
    case 1: fread(&(sdtc), sizeof(int),1,fp);
    printf("%d\n", sdtc);
    break;
    case 2:fread(&(sdtf), sizeof(float),1,fp);
    printf("%f\n", sdtf);
    break;
    case 3:fread(&(sdts), sizeof(unsigned char),1,fp);
    printf("%u\n", sdts);
    break;
    case 4:fread(&(sdtp), sizeof(unsigned int),1,fp);
    printf("%u\n", sdtp);
    break;
    case 5:fread(&(sdty), sizeof(char),1,fp);
    printf("%d\n", sdty);
    break;
    case 6:fread(&(sdtx), sizeof(long int),1,fp);
    printf("%ld\n",sdtx);
    break;
    case 7:fread(&(sdtz), sizeof(double),1,fp);
    printf("%.6f\n", sdtz);
    break;}}

int main(){
    char c,dosya_name[30];
    char type[6];
    char query_name[20];
    int deste,adresi,a,dim1,dim2,n;
    gets(dosya_name);
if((fp=fopen(dosya_name,"rb"))==NULL){return -1;}
else{
    rewind(fp);
    (veri+0)->location=0;
    while ((scanf(" %s ", type))!=-1) {
                    floating_atayici(type[0], type[1]);
                    array=0;
                    if ((check)==-1) {rewind(fp);
                                    break;}
                     }
    array=0;
    while(query_alici(query_name)){

      if (array!=55){
            scalar_basici(query_name);
            if ((check2)==-1) {check2=0;
                              break;}   }

      else if (array==55){
        dim1=dim1_solver();
        dim2=dim2_solver();
        if ( ((dim2)==-1) || ((dim2)==-3)){
                   for(n=0 ; n<i ; n++){
                    if(strcmp((veri+n)->name,query_name) == 0) {adresi=(veri+n)->location;
                                                                break;}}

                    switch ((veri+n)->type){
                      case 1: fseek(fp,adresi+4*dim1,SEEK_SET);
                      break;
                      case 2:fseek(fp, adresi+4*dim1,SEEK_SET);
                      break;
                      case 3:fseek(fp,adresi+1*dim1,SEEK_SET);
                      break;
                      case 4:fseek(fp, adresi+4*dim1,SEEK_SET);
                      break;
                      case 5:fseek(fp, adresi+1*dim1,SEEK_SET);
                      break;
                      case 6:fseek(fp, adresi+8*dim1, SEEK_SET);
                      break;
                      case 7:fseek(fp, adresi+8*dim1 ,SEEK_SET);
                      break;}
                    okuprint(n);
                    rewind(fp);
                    if ((dim2)==-1){ break;} }
        else{
          while((c=getchar())!=44){
                 if(c==10){ check2=-1;
                            break;}}
          for(n=0 ; n<i ; n++){
           if(strcmp((veri+n)->name,query_name) == 0) {adresi=(veri+n)->location;
                                                               deste=(veri+n)->dim2;
                                                               break; }}
                                                              switch ((veri+n)->type){
                                                                case 1:fseek(fp,adresi+4*(deste*dim1+dim2),SEEK_SET);
                                                                break;
                                                                case 2:fseek(fp, adresi+4*(deste*dim1+dim2),SEEK_SET);
                                                                break;
                                                                case 3:fseek(fp,adresi+1*(deste*dim1+dim2),SEEK_SET);
                                                                break;
                                                                case 4:fseek(fp, adresi+4*(deste*dim1+dim2),SEEK_SET);
                                                                break;
                                                                case 5:fseek(fp, adresi+1*(deste*dim1+dim2),SEEK_SET);
                                                                break;
                                                                case 6:fseek(fp, adresi+8*(deste*dim1+dim2),SEEK_SET);
                                                                break;
                                                                case 7:fseek(fp, adresi+8*(deste*dim1+dim2) ,SEEK_SET);
                                                                break;}

          okuprint(n);
          rewind(fp);
          if ((check2)==-1) {break;} }
          check2=0;
          array=0;
        }

    }
}
fclose(fp);
return 0;}
