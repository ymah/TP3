#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "palette.h"

#define SIZE 7


static int **tab = NULL;
static int cpt = 0;
static int **res;            
static struct interval *tabDist = NULL;
int main()
{
  int i;
  struct couleur *pal,*s;
  pal = malloc(sizeof(struct couleur)*SIZE);
  init_palette(pal);
  /* for(i=0;i<k;i++) */
  /*   printf("[%d-%d] -> %d\n",tabDist[i].a,tabDist[i].b,tabDist[i].dist); */
  /* printf("%d\n",res[0][k]); */
  s = newPalette(pal,2,0,6);
  for(i=1;i>=0;i--)
    printf("%d ",s[i].coul);
  return 0;
}


void init_palette(struct couleur *pal){

  pal[0].poids = 5;
  pal[0].coul = 0;

  pal[1].poids = 5;
  pal[1].coul = 20;

  pal[2].poids = 1;
  pal[2].coul = 100;

  pal[3].poids = 1;
  pal[3].coul = 132;

  pal[4].poids = 2;
  pal[4].coul = 164;

  pal[5].poids = 1;
  pal[5].coul = 180;

  pal[6].poids = 10;
  pal[6].coul = 255;

}


int meilleurGris(struct couleur *pal,int pre,int der){


  int moyenne,i,coef;
  
  moyenne=coef = 0;
  
  for(i = pre;i <= der;i++){
    moyenne = moyenne + pal[i].poids * pal[i].coul;    
    coef = pal[i].poids + coef;    
  }
  
  return (int)(moyenne/coef);
}


int distanceMin(struct couleur *pal,int pre,int der){

  int mg,i,dist,tmp;
  mg = meilleurGris(pal,pre,der);
  dist = 0;
  for(i = pre;i<=der;i++){
    tmp = (pal[i].coul - mg);
    dist = dist + (tmp*tmp*pal[i].poids);
    cpt++;

  }

  return dist;

}

/*


  distMinPal(p,1,pre,der) = distanceMin(p,pre,der);
  distMinPal(p,k,pre,der) = distanceMin(p,pre,0)+distanceMinPal(p,k-1,1,der);
*/

int minimum(int a,int b){

  if(a > b)
    return b;
  else
    return a;

}  
      
/*k*n2*/
int distanceMinPalette(struct couleur *pal,int k,int pre,int der){

  int best;
  int i,j,taille,dist,z,min;
  min = 0;
  if(!tab){

    taille = der - pre + 1;
    tab = (int **)calloc(taille,sizeof(int *));
    res = (int **)calloc(taille,sizeof(int *));
    tabDist = (struct interval *) calloc(k,sizeof(struct interval));
    for(i=0;i< taille;i++){
      tab[i] = (int *)calloc(taille,sizeof(int));
      res[i] = (int *)calloc(k+1,sizeof(int));
    }

    for(i=0;i<taille;i++){
      printf("[%d - %d] ", pal[i].coul,pal[i].poids);
    }
    printf("\n\n");
    for(i=0;i < taille;i++){            
      for(j=i;j < taille;j++){  
        dist = distanceMin(pal,i,j);
        tab[i][j]= dist;
      }
    }
    best = tab[pre][der];
  }   
  
  if(k == 1){
    
    tabDist[k-1].a = pre;
    tabDist[k-1].b = der;
    tabDist[k-1].dist = res[0][k] =tab[pre][der] ;

    return res[0][k];
  }
  else{
    z = pre;
    for(i=z+1;i<der;i++){
      cpt++;
      dist = tab[z][i];
      min = distanceMinPalette(pal,k-1,i+1,der);       
      if(min == 0 || min+dist < best){
        tabDist[k-1].a = z;
        tabDist[k-1].b = i;
        tabDist[k-1].dist = res[z][k] =best = min+dist;
            
        if(!z)  
          break;
      }
    }
    return best;
  }
}
    

struct couleur *newPalette(struct couleur *pal,int k,int pre,int der){

  struct couleur *sortie;
  int i;
  sortie = (struct couleur *)calloc(k,sizeof(struct couleur));
  
  distanceMinPalette(pal,k,pre,der);
  
  for(i=k-1;i>=0;i--){
    sortie[i].poids = 1;
    sortie[i].coul = meilleurGris(pal,tabDist[i].a,tabDist[i].b);
    
  }
  return sortie;
}
