#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

/*
	Structure that contains the matrix, i = height and j = width
*/
typedef struct
{
	int i;
	int j;
	double **tab;
} grille;

/*
	function that malloc the required space to the matrix
*/

grille * alloc_grille(int height, int width)
{
	int i;
	height++;
	grille * g;
	g = (grille*)malloc(sizeof(grille)*(height+1)*width);
	g->tab = (double**)malloc(height * sizeof(*g->tab));

	for(i = 0; i<height;i++)
	{
		g->tab[i] = (double*)malloc (width * sizeof(**g->tab));
	}

	g->i = width;
	g->j = height;
	return g;
}

/*
	read the file and attribute the values in the matrix
*/

grille * attribution_grille(grille *g, char file[])
{
	printf("%s \n",file);
	FILE * F = NULL;
	F = fopen(file, "r");

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

/*
	function to display the matrix
*/

void display_matrix(grille *g)
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

/*
	function that apply the pivot of gauss until it cant or it is done
*/

void pivot_gauss(grille *g)
{
	int pivline = 0;
	int i;
	int j;
	int pivcol = pivline;
	double pivot;
	double coeff;
	for(pivline = 0; pivline < g->i; pivline++)
	{

		for(i=0; i<g->i; i++)
		{

			if(g->tab[pivline][pivline])
				pivot = g->tab[pivline][pivline];

			else
			{
				while (pivcol < g->j-1 && !pivot)
				{
					pivot = g->tab[pivline][pivcol];
					pivcol++;
				}
			}

			coeff = ((double)g->tab[i][pivline]/(double)pivot);

			if (coeff < 0)
				coeff = coeff * -1

			for(j=0;j<g->j;j++)
			{

				if(pivot)
				{

					if (i != pivline)
					{
						g->tab[i][j] = (g->tab[i][j]) -(g->tab[pivline][j] * coeff);

						if(g->tab[i][j] < 0.01 && g->tab[i][j] > -0.01)
							g->tab[i][j] = 0;
					}
				}
			}

			display_matrix(g);
			pivcol = pivline;
		}
	}
}

/*
	Test if there is a solution to the matrix
*/

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
			printf("There is no solutions \n");
		impossible=0;
	}
}

/*
	function used at the end to display the value of each variable
*/

void calc_unknown(grille * g)
{
	double unknow;
	int x = 0, i, j;

	for(i=0;i<g->i;i++)
	{

		for(j=0;j<g->j;j++)
		{

			if(g->tab[j][i] != 0)
			{
				unknow = (g->tab[i][g->i])/(g->tab[j][i]);
				x++;
				printf("unknow variable%d : %lf \n",x,unknow);
			}
		}
	}
}

int main()
{
	grille * g = alloc_grille(4,4);
	char * file = "grilleGauss.txt";
	attribution_grille(g, file);
	display_matrix(g);
	pivot_gauss(g);
	calc_unknown(g);
	test_impossible(g);
	return(0);
}
