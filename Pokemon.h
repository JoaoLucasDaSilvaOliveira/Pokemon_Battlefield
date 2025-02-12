#include <stdbool.h>
#define MAX_CARACTERES 50
struct pokemon{
	int cod;
	int codTreinador;
	int PV;
	int PA;
	int PD;
	char nome [MAX_CARACTERES];
};

typedef struct pokemon Pokemon;
bool InicializarPokemons();
bool EncerraPokemons();
bool SalvarPokemon(Pokemon t);
int QuantidadePokemons();
Pokemon* ObterPokemonPeloIndice(int indice);
Pokemon* ObterPokemonPeloCodigo(int codigo);
Pokemon* ObterPokemonPeloNome(char* nome);
bool AtualizarPokemon(Pokemon* t);
bool ApagarPokemonPeloCodigo(int codigo);
bool ApagarPokemonPeloNome(char* nome);
bool VerificaCodPoke(int cod);
bool VerificaCodExistentePokemon(int cod);
