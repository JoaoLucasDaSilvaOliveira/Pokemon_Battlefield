#include <stdbool.h>
#define MAX_CARACTERES 50
struct treinadores {
	char nome [MAX_CARACTERES];
	int codigo;
	int bonusATQ;
	int bonusDEF;
};

typedef struct treinadores Treinador;
bool InicializarTreinadores();
bool EncerraTreinadores();
bool SalvarTreinador(Treinador t);
int QuantidadeTreinadores();
Treinador* ObterTreinadorPeloIndice(int indice);
Treinador* ObterTreinadorPeloCodigo(int codigo);
bool AtualizarTreinador(Treinador* t);
bool ApagarTreinadorPeloCodigo(int codigo);
bool ApagarTreinadorPeloNome(char* nome);
bool VerificaCod (int cod);
bool VerificaCodExistente (int cod);
