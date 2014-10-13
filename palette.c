#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "palette.h"

#define SIZE 7


static int **tab = NULL;
static struct interval *tabDist = NULL;

int main()
{
  struct couleur *pal;
  pal = malloc(sizeof(struct couleur)*SIZE);
  init_palette(pal);
  printf("voila : %d\n",distanceMinPalette(pal,3,0,6));  
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
    tabDist = (struct interval *)calloc(k,sizeof(struct interval*));
    tab = (int **)calloc(taille,sizeof(int *));
    
    for(i=0;i< taille;i++){
      tab[i] = (int *)calloc(taille,sizeof(int));
    }
    for(i=0;i<taille;i++){
      printf("[%d - %d] ", pal[i].coul,pal[i].poids);

    }
    printf("\n");
    for(i=0;i < taille;i++){            
      for(j=i;j < taille;j++){  
        dist = distanceMin(pal,i,j);
        tab[i][j]= dist;
      }
    }
    best = tab[pre][der];
  }   
  
  if((k==1)){
    return tab[pre][der];
  }
  else{
    z = pre;
    for(i=z+1;i<der;i++){
      dist = tab[z][i];
      min = distanceMinPalette(pal,k-1,i+1,der);       
      if((min == 0) ||  (min + dist)<best){   
        best = min+dist;
        printf("[%d,%d] : \n",z,i);
        printf("%d + %d = %d\n",dist,min,best);
        printf("===============\n");
      }
    }
    return best;
  }
}
    
