#include <String.h>
#include <stdlib.h>
#include "Ginasio.h"

int qtdGinasios = 3;
int tamArrayGinasios=4;
Ginasio* arrayGinasio;
int qtdGinasiosEncontrados=0;

bool IniciarGinasio()
{
	int i;
	arrayGinasio = (Ginasio*) malloc (tamArrayGinasios * sizeof (Ginasio));
	if (arrayGinasio == NULL)
	{
		return false;
	}
	for (i=0;i<qtdGinasios;i++)
	{
		arrayGinasio[i].codigo= i+1;
		arrayGinasio[i].capacidade = ((i+1)*1000)/2;
	}
	strcpy(arrayGinasio[0].nome, "PokeStop");
	strcpy(arrayGinasio[1].nome, "CampFire");
	strcpy(arrayGinasio[2].nome, "DarkRoom");
	strcpy(arrayGinasio[0].bairro, "South");
	strcpy(arrayGinasio[1].bairro, "North");
	strcpy(arrayGinasio[2].bairro, "East");
	return true;
}
bool EncerrarGinasio()
{
	free(arrayGinasio);
}
int QuantidadeGinasios()
{
	return qtdGinasios;
}
int QuantidadeGinasiosEncontrados()
{
	return qtdGinasiosEncontrados;
}
Ginasio* ObterGinasioPeloIndice(int indice)
{
	Ginasio* ginasioTemp = (Ginasio*) malloc(1*sizeof(Ginasio));
	*ginasioTemp = arrayGinasio[indice];
	return ginasioTemp;
}
Ginasio* ObterGinasioPeloCodigo(int codigo)
{
	int i;
	Ginasio* ginasioTemp = (Ginasio*) malloc(1*sizeof(Ginasio));
	for (i=0;i<qtdGinasios;i++)
	{
		if (arrayGinasio[i].codigo == codigo)
		{
			*ginasioTemp = arrayGinasio[i];
			return ginasioTemp;
		}	
	} 
	return NULL;
}
bool SalvarGinasio(Ginasio g)
{
	if (tamArrayGinasios>=0)
	{
		if (tamArrayGinasios == qtdGinasios)
		{
			tamArrayGinasios +=1;
			arrayGinasio = (Ginasio*) realloc (arrayGinasio, tamArrayGinasios*sizeof(Ginasio));
			arrayGinasio[qtdGinasios] = g;
		}
		else
		{
			arrayGinasio[qtdGinasios] = g;
		}
		qtdGinasios++;	
		return true;
	}
	else
	return false;
}
bool ExcluirGinasioPeloCodigo(int codigo)
{
	int i;
	for (i=0;i<qtdGinasios;i++)
	{
		if (arrayGinasio[i].codigo == codigo)
		{
			arrayGinasio[i] = arrayGinasio[qtdGinasios-1];
			strcpy(arrayGinasio[i].nome,arrayGinasio[qtdGinasios-1].nome);
			strcpy(arrayGinasio[i].bairro,arrayGinasio[qtdGinasios-1].bairro);
			strcpy(arrayGinasio[qtdGinasios-1].nome, "");
			strcpy(arrayGinasio[qtdGinasios-1].bairro, "");
			arrayGinasio[qtdGinasios-1].capacidade= -1;
			arrayGinasio[qtdGinasios-1].codigo = -1;
			qtdGinasios--;
			if (qtdGinasios == tamArrayGinasios/2)
			{
				arrayGinasio = (Ginasio*) realloc (arrayGinasio, qtdGinasios*sizeof(Ginasio));
			}
			return true;
		}
	}
	return false;
}
Ginasio* ObterGinasioPeloBairro(char* bairro)
{
	int i, indice=0;
	qtdGinasiosEncontrados=0;
	char VerificaNome[MAX_CARACTERES];
	Ginasio* GinasioTemp = (Ginasio*) malloc (1*sizeof (Ginasio));
	for (i=0;i<qtdGinasios;i++)
	{
		strcpy(VerificaNome, arrayGinasio[i].bairro);
		if (strcmp(strlwr(bairro),strlwr(VerificaNome))==0)
		{
			qtdGinasiosEncontrados++;
			GinasioTemp = (Ginasio*) realloc (GinasioTemp, qtdGinasiosEncontrados*sizeof (Ginasio));
			GinasioTemp[indice] = arrayGinasio[i];
			indice++;
		}
	}
	if(qtdGinasiosEncontrados==0)
	{
		free(GinasioTemp);
		return NULL;
	}
	else
	{
		return GinasioTemp;
	}
}
bool VerificaCodGinasio(int codigo)
{
	int i;
	for (i=0;i<qtdGinasios;i++)
	{
		if (arrayGinasio[i].codigo == codigo)
		{
			return false;
		}
	}
	return true;
}
bool VerificaCodGinasioExistente(int codigo)
{
	int i;
	for (i=0;i<qtdGinasios;i++)
	{
		if (arrayGinasio[i].codigo == codigo)
		{
			return true;
		}
	}
	return false;
}
bool VerificaNomeGinasio(char* nome)
{
	int i;
	char VerificaNome[MAX_CARACTERES];
	strcpy(VerificaNome, nome);
	for (i=0;i<qtdGinasios;i++)
	{
		if (strcmp(strlwr(arrayGinasio[i].nome), strlwr(VerificaNome))==0)
		{
			return true;
		}
	}
	return false;
}
