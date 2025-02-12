#include <stdbool.h>
struct batalha {
	int codigo;
	int codPokVencedor;
	int codTreinador[2];
	int codPokemon[2];
	int codGinasio;
};
typedef struct batalha Batalha;

int QuantidadeBatalhas();
Batalha* ObterBatalhaPeloIndice(int indice);
bool SalvarBatalha(Batalha b);
Batalha* ObterBatalhasTreinador (int codigo);
Batalha* ObterBatalhasGinasio (int codigo);
int ObterScorePositivoTreinador (int codigo);
int ObterScoreNegativoTreinador (int codigo);
int QuantidadeBatalhasEncontradas();
