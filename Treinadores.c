#include <String.h>
#include <stdlib.h>
#include <stdio.h>
#include "Treinadores.h"

int qtdTreinadores;
FILE *arqvTreinador;
int BitInicio;

bool InicializarTreinadores()
{
	int i, trein;
	arqvTreinador = fopen("Treinadores.txt", "a+");
	if (arqvTreinador == NULL)
	{
		return false;
	}
	fseek(arqvTreinador, 0, SEEK_SET);
	if(fscanf(arqvTreinador, "BitInicio: %d\n", &BitInicio) == EOF)
	{
		fprintf(arqvTreinador, "BitInicio: 1\n");
		fprintf(arqvTreinador, "Indice: 0\nCodigo: 1\nNome: Joao\nBonusATQ: 2\nBonusDEF: 3\n");
		fprintf(arqvTreinador, "Indice: 1\nCodigo: 2\nNome: Sarah\nBonusATQ: 3\nBonusDEF: 2\n");
		fprintf(arqvTreinador, "Indice: 2\nCodigo: 3\nNome: Marcelo\nBonusATQ: 2\nBonusDEF: 3\n");
		fprintf(arqvTreinador, "Indice: 3\nCodigo: 4\nNome: Zé\nBonusATQ: 3\nBonusDEF: 2\n");
	}
	fclose(arqvTreinador);
	arqvTreinador = fopen("Treinadores.txt", "r");
	Treinador treinadorTemp;
	int result;
	fseek(arqvTreinador, 14, SEEK_SET);
	while (fscanf(arqvTreinador, "Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n", &trein, &treinadorTemp.codigo,treinadorTemp.nome, &treinadorTemp.bonusATQ, &treinadorTemp.bonusDEF)!=EOF)
	{
		if(trein>qtdTreinadores)
		{
			qtdTreinadores = trein;
		}	
	}
	fclose(arqvTreinador);
	return true;
}

bool EncerraTreinadores ()
{
	fclose(arqvTreinador);
}

bool SalvarTreinador(Treinador t)
{
	arqvTreinador = fopen("Treinadores.txt", "a");
	if (arqvTreinador!=NULL)
	{
		qtdTreinadores++;
		fprintf(arqvTreinador, "Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n", qtdTreinadores, t.codigo, t.nome, t.bonusATQ, t.bonusDEF);	
		fclose(arqvTreinador);
		return true;
	}
	else
	{
		fclose(arqvTreinador);
		return false;
	}
}

int QuantidadeTreinadores(){
	return qtdTreinadores+1;
}

Treinador* ObterTreinadorPeloIndice(int indice)
{
	Treinador *treinadorTemp = (Treinador*) malloc (1*sizeof(Treinador));
	arqvTreinador = fopen("Treinadores.txt", "r");
	if (arqvTreinador == NULL)
	{
		return NULL;
	}
	int ind;
	fseek(arqvTreinador, 14, SEEK_SET);
	while (fscanf(arqvTreinador, "Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n", &ind, &treinadorTemp->codigo, treinadorTemp->nome, &treinadorTemp->bonusATQ, &treinadorTemp->bonusDEF)!=EOF)
	{
		if (ind == indice)
		{
			fclose(arqvTreinador);
			return treinadorTemp;
		}
	}
	fclose(arqvTreinador);
	return false;
}

Treinador* ObterTreinadorPeloCodigo(int codigo)
{
	Treinador *treinadorTemp = (Treinador*) malloc (1*sizeof(Treinador));
	arqvTreinador = fopen("Treinadores.txt", "r");
	if (arqvTreinador == NULL)
	{
		return NULL;
	}
	int ind;
	int fimArq;
	fseek(arqvTreinador, 14, SEEK_SET);
	do
	{
		fimArq = fscanf(arqvTreinador, "Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n", &ind, &treinadorTemp->codigo, treinadorTemp->nome, &treinadorTemp->bonusATQ, &treinadorTemp->bonusDEF);
	}
	while ( treinadorTemp->codigo != codigo);
	if (fimArq == EOF)
	{
		fclose(arqvTreinador);
		return NULL;
	}
	else
	{
		fclose(arqvTreinador);
		return treinadorTemp;	
	}
}

bool AtualizarTreinador(Treinador* t)
{
	arqvTreinador = fopen("Treinadores.txt", "r");
	FILE *arqvTemp = fopen("Temporario.txt", "w");
	if (arqvTreinador == NULL || arqvTemp == NULL)
	{
		return false;
	}
	Treinador treinadorTemp;
	int indice, indiceAtual;
	//usar para pular o "BitIncio: 1\n
	fseek(arqvTreinador, 14, SEEK_SET);
	fprintf(arqvTemp, "BitInicio: 1\n");
	while (fscanf(arqvTreinador, "Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n", &indice, &treinadorTemp.codigo,treinadorTemp.nome, &treinadorTemp.bonusATQ, &treinadorTemp.bonusDEF)!=EOF)
	{
		if (treinadorTemp.codigo == t->codigo)
		{
			strcpy(t->nome,treinadorTemp.nome);
			indiceAtual = indice;
		}
		if (treinadorTemp.codigo != t->codigo)
		{
			fprintf(arqvTemp, "Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n",indice, treinadorTemp.codigo,treinadorTemp.nome, treinadorTemp.bonusATQ, treinadorTemp.bonusDEF);
		}
	}
	fprintf(arqvTemp,"Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n", indiceAtual, t->codigo, t->nome, t->bonusATQ, t->bonusDEF);
	fclose(arqvTreinador);
	fclose (arqvTemp);
	remove ("Treinadores.txt");
	rename ("Temporario.txt","Treinadores.txt");
	return true;
}
bool ApagarTreinadorPeloCodigo(int codigo)
{
	int i=0;
	arqvTreinador = fopen("Treinadores.txt", "r");
	FILE *arqvTemp = fopen("Temporario.txt", "w");
	if (arqvTreinador == NULL || arqvTemp == NULL)
	{
		return false;
	}
	Treinador treinadorTemp;
	int indice;
	//usar para pular o "BitIncio: 1\n
	fseek(arqvTreinador, 14, SEEK_SET);
	fprintf(arqvTemp, "BitInicio: 1\n");
	while (fscanf(arqvTreinador, "Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n", &indice, &treinadorTemp.codigo,treinadorTemp.nome, &treinadorTemp.bonusATQ, &treinadorTemp.bonusDEF)!=EOF)
	{
		if (treinadorTemp.codigo != codigo)
		{
			fprintf(arqvTemp, "Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n",i, treinadorTemp.codigo,treinadorTemp.nome, treinadorTemp.bonusATQ, treinadorTemp.bonusDEF);
			i++;
		}
	}
	fclose(arqvTreinador);
	fclose (arqvTemp);
	remove ("Treinadores.txt");
	rename ("Temporario.txt","Treinadores.txt");
	qtdTreinadores--;
	return true;
}

bool VerificaCod(int cod)
{
	arqvTreinador = fopen ("Treinadores.txt", "r");
	if (arqvTreinador == NULL)
	{
		return false;
	}
	int indice;
	Treinador treinadorTemp;
	//usar para pular o "BitIncio: 1\n
	fseek(arqvTreinador, 14, SEEK_SET);
	while (fscanf(arqvTreinador, "Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n", &indice, &treinadorTemp.codigo, treinadorTemp.nome, &treinadorTemp.bonusATQ, &treinadorTemp.bonusDEF)!=EOF)
	{
		if (treinadorTemp.codigo == cod)
		{
			fclose(arqvTreinador);
			return true;
		}
	}
	fclose(arqvTreinador);
	return false;
}
bool VerificaCodExistente (int cod)
{
	arqvTreinador = fopen ("Treinadores.txt", "r");
	if (arqvTreinador == NULL)
	{
		return false;
	}
	int indice;
	Treinador treinadorTemp;
	//usar para pular o "BitIncio: 1\n
	fseek(arqvTreinador, 14, SEEK_SET);
	while (fscanf(arqvTreinador, "Indice: %d\nCodigo: %d\nNome: %s\nBonusATQ: %d\nBonusDEF: %d\n", &indice, &treinadorTemp.codigo, treinadorTemp.nome, &treinadorTemp.bonusATQ, &treinadorTemp.bonusDEF)!=EOF)
	{
		if (treinadorTemp.codigo == cod)
		{
			fclose(arqvTreinador);
			return false;
		}
	}
	fclose(arqvTreinador);
	return true;
}
