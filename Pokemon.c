#include <String.h>
#include <stdlib.h>
#include <stdio.h>
#include "Pokemon.h"

int qtdPokemons;
FILE *arqvPokemon;
int BitInicio;

bool InicializarPokemons()
{
	int i, pok;
	arqvPokemon = fopen("Pokemons.txt", "a+");
	if (arqvPokemon == NULL)
	{
		return false;
	}
	fseek(arqvPokemon, 0, SEEK_SET);
	if(fscanf(arqvPokemon, "BitInicio: %d\n", &BitInicio) == EOF)
	{
		fprintf(arqvPokemon, "BitInicio: 1\n");
		fprintf(arqvPokemon, "Indice: 0\nCodigo: 1\nNome: Picachu\nVida: 5\nDano: 3\nDefesa: 2\nCodTreinador: 1\n");
		fprintf(arqvPokemon, "Indice: 1\nCodigo: 2\nNome: Raychu\nVida: 10\nDano: 2\nDefesa: 3\nCodTreinador: 2\n");
		fprintf(arqvPokemon, "Indice: 2\nCodigo: 3\nNome: Pidioto\nVida: 15\nDano: 3\nDefesa: 2\nCodTreinador: 3\n");
		fprintf(arqvPokemon, "Indice: 3\nCodigo: 4\nNome: Mewtwo\nVida: 20\nDano: 2\nDefesa: 3\nCodTreinador: 4\n");
	}
	fclose(arqvPokemon);
	arqvPokemon = fopen("Pokemons.txt", "r");
	Pokemon pokemonTemp;
	int result;
	fseek(arqvPokemon, 14, SEEK_SET);
	while (fscanf(arqvPokemon, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", &pok, &pokemonTemp.cod,pokemonTemp.nome, &pokemonTemp.PV, &pokemonTemp.PA,&pokemonTemp.PD, &pokemonTemp.codTreinador)!=EOF)
	{
		if(pok>qtdPokemons)
		{
			qtdPokemons = pok;
		}	
	}
	fclose(arqvPokemon);
	return true;
}

bool EncerraPokemons()
{
	fclose(arqvPokemon);
}
bool SalvarPokemon(Pokemon t)
{
	arqvPokemon = fopen("Pokemons.txt", "a");
	if (arqvPokemon!=NULL)
	{
		qtdPokemons++;
		fprintf(arqvPokemon, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", qtdPokemons, t.cod,t.nome, t.PV, t.PA,t.PD, t.codTreinador);	
		fclose(arqvPokemon);
		return true;
	}
	else
	{
		fclose(arqvPokemon);
		return false;
	}
}
int QuantidadePokemons()
{
	return qtdPokemons+1;
}
Pokemon* ObterPokemonPeloIndice(int indice)
{
	Pokemon *pokemonTemp = (Pokemon*) malloc (1*sizeof(Pokemon));
	arqvPokemon = fopen("Pokemons.txt", "r");
	if (arqvPokemon == NULL)
	{
		return NULL;
	}
	int ind;
	fseek(arqvPokemon, 14, SEEK_SET);
	while (fscanf(arqvPokemon, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", &ind, &pokemonTemp->cod,pokemonTemp->nome, &pokemonTemp->PV, &pokemonTemp->PA,&pokemonTemp->PD, &pokemonTemp->codTreinador)!=EOF)
	{
		if (ind == indice)
		{
			fclose(arqvPokemon);
			return pokemonTemp;
		}
	}
	fclose(arqvPokemon);
	return false;
}
Pokemon* ObterPokemonPeloCodigo(int codigo)
{
	Pokemon *pokemonTemp = (Pokemon*) malloc (sizeof(Pokemon));
	arqvPokemon = fopen("Pokemons.txt", "r");
	if (arqvPokemon == NULL)
	{
		return NULL;
	}
	int ind;
	int fimArq;
	fseek(arqvPokemon, 14, SEEK_SET);
	do
	{
		fimArq = fscanf(arqvPokemon, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", &ind, &pokemonTemp->cod,pokemonTemp->nome, &pokemonTemp->PV, &pokemonTemp->PA,&pokemonTemp->PD, &pokemonTemp->codTreinador);
	}
	while ( pokemonTemp->cod != codigo);
	fclose(arqvPokemon);
	if (fimArq == EOF)
	{
		return NULL;
	}
	else
	return pokemonTemp;
}
Pokemon* ObterPokemonPeloNome(char* nome)
{
	arqvPokemon = fopen("Pokemons.txt", "r");
	if (arqvPokemon == NULL)
	{
		return NULL;
	}
	int ind;
	Pokemon *pokemonTemp = (Pokemon*) malloc (1*sizeof(Pokemon));
	fseek(arqvPokemon, 14, SEEK_SET);
	while (fscanf(arqvPokemon, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", &ind, &pokemonTemp->cod,pokemonTemp->nome, &pokemonTemp->PV, &pokemonTemp->PA,&pokemonTemp->PD, &pokemonTemp->codTreinador)!=EOF)
	{
		if (strcasecmp(pokemonTemp->nome, nome)==0)
		{
			fclose(arqvPokemon);
			return pokemonTemp;
		}
	}
	fclose(arqvPokemon);
	return NULL;
}
bool ApagarPokemonPeloCodigo(int codigo)
{
	int i=0;
	arqvPokemon = fopen("Pokemons.txt", "r");
	FILE *arqvTemp = fopen("Temporario.txt", "w");
	if (arqvPokemon == NULL || arqvTemp == NULL)
	{
		return false;
	}
	Pokemon pokemonTemp;
	int indice;
	//usar para pular o "BitIncio: 1\n
	fseek(arqvPokemon, 14, SEEK_SET);
	fprintf(arqvTemp, "BitInicio: 1\n");
	while (fscanf(arqvPokemon, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", &indice, &pokemonTemp.cod,pokemonTemp.nome, &pokemonTemp.PV, &pokemonTemp.PA,&pokemonTemp.PD, &pokemonTemp.codTreinador)!=EOF)
	{
		if (pokemonTemp.cod != codigo)
		{
			fprintf(arqvTemp, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", i, pokemonTemp.cod,pokemonTemp.nome, pokemonTemp.PV, pokemonTemp.PA,pokemonTemp.PD, pokemonTemp.codTreinador);
			i++;
		}
	}
	fclose(arqvPokemon);
	fclose (arqvTemp);
	remove ("Pokemons.txt");
	rename ("Temporario.txt","Pokemons.txt");
	qtdPokemons--;
	return true;
}
bool AtualizarPokemon(Pokemon* t)
{
	arqvPokemon = fopen("Pokemons.txt", "r");
	FILE *arqvTemp = fopen("Temporario.txt", "w");
	if (arqvPokemon == NULL || arqvTemp == NULL)
	{
		return false;
	}
	Pokemon pokemonTemp;
	int indice, indiceAtual;
	//usar para pular o "BitIncio: 1\n
	fseek(arqvPokemon, 14, SEEK_SET);
	fprintf(arqvTemp, "BitInicio: 1\n");
	while (fscanf(arqvPokemon, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", &indice, &pokemonTemp.cod,pokemonTemp.nome, &pokemonTemp.PV, &pokemonTemp.PA,&pokemonTemp.PD, &pokemonTemp.codTreinador)!=EOF)
	{
		if (pokemonTemp.cod == t->cod)
		{
			strcpy(t->nome,pokemonTemp.nome);
			indiceAtual = indice;
		}
		if (pokemonTemp.cod != t->cod)
		{
			fprintf(arqvTemp, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", indice, pokemonTemp.cod,pokemonTemp.nome, pokemonTemp.PV, pokemonTemp.PA,pokemonTemp.PD, pokemonTemp.codTreinador);
		}
	}
	fprintf(arqvTemp,"Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", indiceAtual, t->cod,t->nome, t->PV, t->PA,t->PD, t->codTreinador);
	fclose(arqvPokemon);
	fclose (arqvTemp);
	remove ("Pokemons.txt");
	rename ("Temporario.txt","Pokemons.txt");
	return true;
}
bool VerificaCodPoke(int cod)
{
	arqvPokemon = fopen ("Pokemons.txt", "r");
	if (arqvPokemon == NULL)
	{
		return false;
	}
	int indice;
	Pokemon pokemonTemp;
	//usar para pular o "BitIncio: 1\n
	fseek(arqvPokemon, 14, SEEK_SET);
	while (fscanf(arqvPokemon, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", &indice, &pokemonTemp.cod,pokemonTemp.nome, &pokemonTemp.PV, &pokemonTemp.PA,&pokemonTemp.PD, &pokemonTemp.codTreinador)!=EOF)
	{
		if (pokemonTemp.cod == cod)
		{
			fclose(arqvPokemon);
			return true;
		}
	}
	fclose(arqvPokemon);
	return false;
}
bool VerificaCodExistentePokemon(int cod)
{
	arqvPokemon = fopen ("Pokemons.txt", "r");
	if (arqvPokemon == NULL)
	{
		return false;
	}
	int indice;
	Pokemon pokemonTemp;
	//usar para pular o "BitIncio: 1\n
	fseek(arqvPokemon, 14, SEEK_SET);
	while (fscanf(arqvPokemon, "Indice: %d\nCodigo: %d\nNome: %s\nVida: %d\nDano: %d\nDefesa: %d\nCodTreinador: %d\n", &indice, &pokemonTemp.cod,pokemonTemp.nome, &pokemonTemp.PV, &pokemonTemp.PA,&pokemonTemp.PD, &pokemonTemp.codTreinador)!=EOF)
	{
		if (pokemonTemp.cod == cod)
		{
			fclose(arqvPokemon);
			return false;
		}
	}
	fclose(arqvPokemon);
	return true;
}
