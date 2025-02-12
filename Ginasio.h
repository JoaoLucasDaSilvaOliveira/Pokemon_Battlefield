#include <stdbool.h>
#define MAX_CARACTERES 50
struct ginasio {
	int codigo;
	char nome[MAX_CARACTERES];
	int capacidade;
	char bairro [MAX_CARACTERES];
};

typedef struct ginasio Ginasio;

bool IniciarGinasio();
bool EncerrarGinasio();
int QuantidadeGinasios();
int QuantidadeGinasiosEncontrados();
Ginasio* ObterGinasioPeloIndice(int indice);
Ginasio* ObterGinasioPeloCodigo(int codigo);
bool SalvarGinasio(Ginasio g);
bool ExcluirGinasioPeloCodigo(int codigo);
Ginasio* ObterGinasioPeloBairro(char* bairro);
bool VerificaCodGinasio(int codigo);
bool VerificaCodGinasioExistente(int codigo);
bool VerificaNomeGinasio(char* nome);
