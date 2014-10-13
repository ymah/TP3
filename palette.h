




struct couleur
{
  int poids;
  int coul;
};

struct interval
{
  int a;
  int b;
  int dist;
};

int meilleurGris(struct couleur *pal,int pre,int der);

void init_palette(struct couleur *pal);

int distanceMin(struct couleur *pal,int pre,int der);

int distanceMinPalette(struct couleur *pal,int k,int pre,int der);

