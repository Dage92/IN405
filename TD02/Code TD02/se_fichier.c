#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "se_fichier.h"

SE_FICHIER SE_ouverture (const char * chemin, int acces)
{
	SE_FICHIER *f;
	f.chemin = chemin;
	f.acces = acces;
	f.descripteur = open(f.chemin, f.acces || O_CREAT);
	return f;
}

int SE_fermeture (SE_FICHIER fichier)
{
	return close(f.descripteur);
}

/*int SE_suppression (const char * chemin);
{
	
}*/
	
int SE_lectureCaractere (SE_FICHIER fichier, char * caractere)
{
	if (f.acces == 'r')
	{	
		return read (f.descripteur, 
	}
	else
	{
		printf("Le fichier ouvert n'a pas permission de lecture.");
	}
}
	
int SE_ecritureCaractere (SE_FICHIER fichier, const char caractere)
{
	if (f.acces == 'w')
	{	
		return write (
	}
	else
	{
		printf("Le fichier ouvert n'a pas permission d'ecriture.");
	}
	return 0;
}
