#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct
{
	int i;
	int j;
	double **tab;
} grille;

grille * alloc_grille(int longueur, int largeur)
{
	int i;
	longueur++;
	grille * g;
	g = (grille*)malloc(sizeof(grille)*(longueur+1)*largeur);
	g->tab = (double**)malloc(longueur * sizeof(*g->tab));
	for(i = 0; i<longueur;i++)
	{
		g->tab[i] = (double*)malloc (largeur * sizeof(**g->tab));
	}
	g->i = largeur;
	g->j = longueur;
	return g;
} 

grille * attribution_grille(grille *g, char fichier[])
{
	printf("%s \n",fichier);
	FILE * F = NULL;
	F = fopen(fichier, "r");
	if (F != NULL)
	{
		int j;
		int i;
		for(i=0;i<g->i;i++)
		{
			for(j=0;j<g->j;j++)
			{
				fscanf(F,"%lf",&g->tab[i][j]);
			}
		}
		fclose(F);
		return g;
	}
	else
	{
		assert(0);
	}
}
void afficher_grille(grille *g)
{
	int nbr = 1;
	int i;
	int j;
	for (i=0;i<g->i;i++)
	{
		printf("\t     x%d     \t",nbr);
		nbr++;
	}
	printf("\t     b     \t\n");
	for(i=0;i<((g->i)*3);i++)
	{
		for(j=0;j<g->j;j++)
		{
			if(i%3==1)
				printf("|\t%lf\t|",g->tab[i/3][j]);
			else if(i%3==0)
				printf("________________________");
			else
				printf("|\t\t\t|");
		}
		printf("\n");
	}
	
	printf("\n\n\n\n");
}
void pivot_gauss(grille *g)
{
	int lignepiv = 0;
	int i;
	int j;
	int colonnepiv = lignepiv;
	double pivot;
	double coeff;
	for(lignepiv = 0;lignepiv < g->i;lignepiv++)
		for(i=0;i<g->i;i++)
		{
			if(g->tab[lignepiv][lignepiv])
				pivot = g->tab[lignepiv][lignepiv];
			else
			{
				while (colonnepiv < g->j-1 && !pivot)		
				{
					pivot = g->tab[lignepiv][colonnepiv];
					colonnepiv++;
				}
			}
			coeff = ((double)g->tab[i][lignepiv]/(double)pivot);
/*			if (coeff < 0)
				coeff = coeff * -1*/
			for(j=0;j<g->j;j++)
			{
				if(pivot)
				{
					if (i != lignepiv)
					{
//						printf("pivot : %lf ",pivot);
//						printf("val : %lf ",i);
//						printf("autre val %lf",j);
//						printf("coeff %lf",coeff);
						g->tab[i][j] = (g->tab[i][j]) -(g->tab[lignepiv][j] * coeff);
						if(g->tab[i][j] < 0.01 && g->tab[i][j] > -0.01)
							g->tab[i][j] = 0;
					}
				}
			}
			afficher_grille(g);
//			printf("pivot : %lf ",pivot);
//			printf(" case : %d ", g->tab[i][j]);
//			printf("nouvelle case %d ",g->tab[i+1][j]);
//			printf(" coeff : %lf ",coeff);
			colonnepiv = lignepiv;
			/*	lignepiv++;
			printf(" étape %d \n",i);
			*/
		}
}
void test_impossible(grille * g)
{
int i, j, impossible = 0;
	for(i=0;i<g->i;i++)
	{
		for(j=0;j<g->j-1;j++)
		{
			if(g->tab[i][j] == 0)
				impossible++;
		}
		if (impossible == g->j-1 && g->tab[i][g->j-1] !=0)
			printf("c'est impossible, BUT CAN YOU DO THIS \n");
		impossible=0;
	}	
}
void calcul_inconnues(grille * g)
{
	double inconnues;
	int x = 0, i, j;
	for(i=0;i<g->i;i++)
	{
		for(j=0;j<g->j;j++)
		{
			if(g->tab[j][i] != 0)
			{
				inconnues = (g->tab[i][g->i])/(g->tab[j][i]);
				x++;
				printf("inconnue%d : %lf \n",x,inconnues);
			}
		}
	}
}

int main()
{
	grille * g = alloc_grille(4,4);
	char * fichier = "grilleGauss.txt";
	attribution_grille(g, fichier);
	afficher_grille(g);
	pivot_gauss(g);
	calcul_inconnues(g);
	test_impossible(g);
	return(0);
}
