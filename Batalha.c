#include <String.h>
#include <stdlib.h>
#include "Batalha.h"
#include "Pokemon.h"
#include "Treinadores.h"

int qtdBatalhas=0;
int BatEnc=0;
Batalha* arrayBatalha;

int QuantidadeBatalhas()
{	
	return qtdBatalhas;
}
int QuantidadeBatalhasEncontradas()
{
	return BatEnc;
}
Batalha* ObterBatalhaPeloIndice(int indice)
{
		int i;
		Batalha* batalhaTemp = (Batalha*) malloc (1*sizeof(Batalha));
		if (batalhaTemp == NULL)
		{
			return NULL;
		}
		*batalhaTemp = arrayBatalha[indice];
		return batalhaTemp;

}
bool SalvarBatalha(Batalha b)
{
	int i;
	if (qtdBatalhas==0)
	{
		arrayBatalha = (Batalha*) malloc (1*sizeof(Batalha));
		if (arrayBatalha == NULL)
		{
			return false;
		}
		for (i=0; i<2;i++)
		{
			arrayBatalha[qtdBatalhas].codPokemon[i] = b.codPokemon[i];
			arrayBatalha[qtdBatalhas].codTreinador[i] = b.codTreinador[i];
		}
		arrayBatalha[qtdBatalhas].codGinasio = b.codGinasio;
		arrayBatalha[qtdBatalhas].codigo = b.codigo;
		arrayBatalha[qtdBatalhas].codPokVencedor = b.codPokVencedor;
		qtdBatalhas+=1;
		return true;
	}
	else
	{
		arrayBatalha = (Batalha*) realloc (arrayBatalha, (qtdBatalhas+1)*sizeof(Batalha));
		if (arrayBatalha == NULL)
		{
			return false;
		}
		for (i=0; i<2;i++)
		{
			arrayBatalha[qtdBatalhas].codPokemon[i] = b.codPokemon[i];
			arrayBatalha[qtdBatalhas].codTreinador[i] = b.codTreinador[i];
		}
		arrayBatalha[qtdBatalhas].codGinasio = b.codGinasio;
		arrayBatalha[qtdBatalhas].codigo = b.codigo;
		arrayBatalha[qtdBatalhas].codPokVencedor = b.codPokVencedor;
		qtdBatalhas+=1;
		return true;
	}
}
Batalha* ObterBatalhasTreinador (int codigo)
{
	int i, indice=0;
	BatEnc=0;
	Batalha* BatalhaTemp = (Batalha*) malloc (1*sizeof (Batalha));
	for (i=0;i<qtdBatalhas;i++)
	{
		if (codigo == arrayBatalha[i].codTreinador[0] || codigo == arrayBatalha[i].codTreinador[1])
		{
			BatEnc+=1;
			BatalhaTemp = (Batalha*) realloc (BatalhaTemp, BatEnc*sizeof (Batalha));
			BatalhaTemp[indice] = arrayBatalha[i];
			indice+=1;
		}
	}
	if(BatEnc==0)
	{
		free(BatalhaTemp);
		return NULL;
	}
	else
	{
		return BatalhaTemp;
	}
}
Batalha* ObterBatalhasGinasio (int codigo)
{
	int i, indice=0;
	BatEnc=0;
	Batalha* BatalhaTemp = (Batalha*) malloc (1*sizeof (Batalha));
	for (i=0;i<qtdBatalhas;i++)
	{
		if (codigo == arrayBatalha[i].codGinasio)
		{
			BatEnc+=1;
			BatalhaTemp = (Batalha*) realloc (BatalhaTemp, BatEnc*sizeof (Batalha));
			BatalhaTemp[indice] = arrayBatalha[i];
			indice+=1;
		}
	}
	if(BatEnc==0)
	{
		free(BatalhaTemp);
		return NULL;
	}
	else
	{
		return BatalhaTemp;
	}	
}
int ObterScorePositivoTreinador(int codigo)
{
	int i, venceu=0, perdeu;
	for (i=0;i<qtdBatalhas;i++)
	{
		if (ObterPokemonPeloCodigo(arrayBatalha[i].codPokVencedor)->codTreinador == codigo)
		{
			venceu++;
		}
	}
	if (venceu==0)
	{
		return 0;
	}
	else
	{
		return venceu;
	}
}
int ObterScoreNegativoTreinador(int codigo)
{
	int i, perdeu=0;
	for (i=0;i<qtdBatalhas;i++)
	{
		if (ObterPokemonPeloCodigo(arrayBatalha[i].codPokVencedor)->codTreinador == arrayBatalha[i].codPokemon[0] && arrayBatalha[i].codPokemon[1] == codigo)
		{
			perdeu++;
		}
		else if (ObterPokemonPeloCodigo(arrayBatalha[i].codPokVencedor)->codTreinador == arrayBatalha[i].codPokemon[1] && arrayBatalha[i].codPokemon[0] == codigo)
		{
			perdeu++;
		}
	}
	if (perdeu==0)
	{
		return 0;
	}
	else
	{
		return perdeu;
	}
}
