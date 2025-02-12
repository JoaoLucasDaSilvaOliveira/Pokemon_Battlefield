#include <stdio.h>
#include <stdlib.h>
#include "Treinadores.h"
#include "Ginasio.h"
#include "Pokemon.h"
#include "Batalha.h"
#include <locale.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void listarMenu(bool primeiraVez);
void finalizar();
void subMenuTreinador();
void subMenuPokemon();
void subMenuGinasio();
void subMenuBatalha();
void listarTreinadores();
void listarPokemon();
void listarGinasio();
void listarBatalhas();
void listarDesenhoPoke(int i);
void listarBatalhasEspecial1(int cod);
void listaBatGinasio(int codG);
///////////////////////MAIN///////////////////

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	if (InicializarTreinadores() == false || InicializarPokemons() == false || IniciarGinasio() == false)
	{
		printf("Falta de memória! Erro grave!");
		exit(1);
	}
	bool atv = true;
	listarMenu (atv);
	EncerraTreinadores();
	EncerraPokemons();
	EncerrarGinasio();
	return 0;
}

///////////////////MAIN//////////////////////

void listarMenu (bool primeiraVez){
	int cod=!0, i;
	while (cod!=0)
	{
		system("cls");
		if (primeiraVez == true)
		{
			printf("Seja muito bem-vindo ao Pokemon Battlefield!");
			sleep(1);
			system("cls");
		}
		primeiraVez=false;
		printf(" ----------------MENU-----------------\n");
		printf("|               CAMPOS                |\n");
		printf("| 0. Sair                             |\n");
		printf("| 1. Treinadores                      |\n");
		printf("| 2. Pokemons                         |\n");
		printf("| 3. Ginasios                         |\n");
		printf("| 4. Batalhas                         |\n");
		printf(" -------------------------------------\n\n");
		printf("O que deseja fazer?\nOpção:  ");
		scanf("%d", &cod);
		int subCod=1;
		switch (cod)
		{
			case 0: 
				finalizar();
				break;
			
			case 1:
				while (subCod!=0)
				{
					system("cls");
					subMenuTreinador();
					scanf("%d", &subCod);
					switch (subCod)
					{
						case 0:
							system("cls");
							break;	
									
						case 1: 
							{
								system("cls");
								printf("LISTAR TREINADORES\n\n");
								listarTreinadores();
								system("pause");
							}
							break;
							
						case 2: 
							{
								system("cls");
								printf("CADASTRAR TREINADOR\n\n");
								int rep;
								Treinador t;
								do
								{
									system("cls");
									listarTreinadores();
									printf("Digite o codigo queres colocar: ");
									scanf("%d", &t.codigo);
									if (t.codigo<0)
									{
										printf("Codigo Negativo, nao pode!\n\n");
										system("pause");
										system("cls");
										rep=2;
									}
									else if (VerificaCodExistente(t.codigo) == false)
									{
										printf("Codigo ja cadastrado, nao pode!\n\n");
										system("pause");
										system("cls");
										rep=2;
									}
									else
									{
										fflush(stdin);
										printf("Digite o nome do seu treinador: ");
										scanf("%[^\n]s", t.nome);
										printf("Digite o bonus de ataque: ");
										scanf("%d", &t.bonusATQ);
										printf("Digite o bonus de defesa: ");
										scanf("%d", &t.bonusDEF);
										sleep (1);
										system ("cls");
										printf("CONFIRMAR INFORMACOES\n\n");
										printf("Listar Treinadores!\n\nCODIGO - NOME - BONUS ATQ - BONUS DEF\n");
										printf("%d - %s - %d - %d\n\nSalvar dados?\n\n1- Sim  2- Nao\n\nOpcao: ",t.codigo,t.nome,t.bonusATQ,t.bonusDEF);
										scanf("%d", &rep);
									}
								}while (rep==2);
								if (SalvarTreinador(t)==false)
								{
									printf("\n\nNao foi possivel salvar este treinador!\n\n");
									system ("pause"); system ("cls");
								}
								else
								{
									printf("\n\nJogador salvo com sucesso!\n\n");
									system ("pause"); system ("cls");
								}
							}
						break;
							
						case 3:
							system("cls");
							{
								int rep;
								Treinador* t = (Treinador*) malloc (1*sizeof(Treinador));
								int cod;
								do
								{
									printf("ATUALIZAR TREINADOR\n\n");
									listarTreinadores();
									printf("Digite o codigo do treinador que quer atualizar: ");
									scanf("%d", &cod);
									if (VerificaCod(cod)==false)
									{
										printf("Codigo Inexistente!\n\n");
										system("pause");
										system("cls");
										rep=2;
									}
									else
									{
										t->codigo = cod;
										printf("\nDigite o bonus de ataque que deseja: ");
										scanf("%d", &t->bonusATQ);
										printf("\nDigite o bonus de defesa que deseja: ");
										scanf("%d", &t->bonusDEF);
										sleep (1);
										system ("cls");
										printf("CONFIRMAR INFORMACOES\n\n");
										printf("Atualizar Treinador!\n\nCODIGO - BONUS ATQ - BONUS DEF\n\n");
										printf("%d - %d - %d\n\nSalvar dados?\n\n1- Sim  2- Nao\n\nOpcao: ",t->codigo,t->bonusATQ,t->bonusDEF);
										scanf("%d", &rep);	
									}
								}while(rep==2);
								if (AtualizarTreinador(t) == true)
								{
									system("cls");
									printf("Treinador atualizado com sucesso!\n\n");
									system("pause"); system("cls");
								}
								else 
								{
									system("cls");
									printf("Valores informados incorretamente!\n\n");
									system("pause"); system("cls");
								}
								free(t);
							}
							break;
							
						case 4:
							system("cls"); 
							{
								int rep, i;
								int codT;
									do
									{
										rep=0;
										printf("EXCLUIR TREINADOR!\n\n");
										listarTreinadores();
										printf("\nDigite o codigo do treinador que deseja excluir: ");
										scanf("%d", &codT);
										if (VerificaCod(codT)==false)
										{
											printf("Código inexistente!");
											rep=1;
										}
									}while(rep==1);
									for (i=0;i<QuantidadePokemons();i++)
									{
										Pokemon* VerificaPok = ObterPokemonPeloIndice(i);
										if (VerificaPok->codTreinador == codT)
										{
											printf("Não é possível excluir o treinador, ele possui pokemons!\n\n");
											system("pause");
											rep=-1;
											free(VerificaPok);
											break;
										}
										free(VerificaPok);
									}
									if(rep==-1)
									{
										break;
									}
									if (ApagarTreinadorPeloCodigo(codT)==true)
									{
										printf("\nTreinador excluído com sucesso!\n\n");	
									}
									else 
									{
										printf("\nNao foi possivel excluir o treinador\n\n");	
									}	
									system("pause"); system("cls");
									
								}
							break;
							
						default: 
							printf("\nCódigo invalido ou inexistente!\n\n");
							system ("pause");
					}
				}
				break;
				
			case 2: 
			{
				while (subCod!=0)
				{
					system("cls");
					subMenuPokemon();
					scanf("%d", &subCod);
					switch (subCod)
					{
						case 0:
							system("cls");
							break;
							
						case 1: 
							system("cls");
							printf("LISTAR POKEMONS\n\n");
							listarPokemon();
							system("pause");
							break;
						
						case 2:
							system("cls");
							printf("CADASTRAR POKEMON\n\n");
							{
								int rep=0;
								Pokemon poke;
								printf("Treinadores disponíves:\n\n");
								int i;
								Treinador* listar;
								Pokemon* listarP;
								do
								{
									printf(" CÓDIGO | NOME\n");
									for (i=0;i<QuantidadeTreinadores();i++)
									{
										listar = ObterTreinadorPeloIndice(i);
										printf("%d | %s\n",listar->codigo,listar->nome);
										free(listar);
									}
									printf("\n\n");
									printf("Digite o codigo do treinador que queira vincular: ");
									do
									{
										scanf("%d", &poke.codTreinador);
										if (VerificaCod(poke.codTreinador)==false)
										{
											printf("Codigo Inválido, digite outro: ");
										}
									}while (VerificaCod(poke.codTreinador)==false);
									listar = ObterTreinadorPeloCodigo(poke.codTreinador);
									do
									{
										rep=0;
										system("cls");
										printf("CÓDIGO | NOME\n");
										for (i=0 ;i<QuantidadePokemons();i++)
										{
											listarP = ObterPokemonPeloIndice(i);
											printf("%d      | %s\n", listarP->cod, listarP->nome);
											free(listarP);
										}
										printf("\nDigite o codigo do pokemon que queres colocar: ");
										scanf("%d", &poke.cod);
										if (poke.cod<0)
										{
											printf("Codigo Negativo, nao pode!\n\n");
											system("pause");
											system("cls");
											rep=1;
										}
										else if (VerificaCodExistentePokemon(poke.cod) == false)
										{
											printf("Codigo ja cadastrado, nao pode!\n\n");
											system("pause");
											system("cls");
											rep=1;
										}
									}while (rep==1);
									rep=0;
									fflush(stdin);
									printf("Digite o nome do seu pokemon: ");
									scanf("%[^\n]s", poke.nome);
									printf("Digite o valor de ataque: ");
									scanf("%d", &poke.PA);
									printf("Digite o valor de defesa: ");
									scanf("%d", &poke.PD);
									printf("Digite o valor de vida: ");
									scanf("%d", &poke.PV);
									sleep (1);
									system ("cls");
									printf("CONFIRMAR INFORMACOES\n\n");
									printf("CODIGO - NOME - ATAQUE - DEFESA - VIDA - DONO\n\n");
									printf("%d - %s - %d - %d - %d - %s\n\nSalvar dados?\n\n1- Sim  2- Nao\n\nOpcao: ",poke.cod, poke.nome, poke.PA, poke.PD, poke.PV, listar->nome);
									scanf("%d", &rep);
									if (rep == 2)
									{
										system("cls");
									}
								}while (rep==2);
								if (SalvarPokemon(poke) == false)
								{
									system("cls");
									printf("Não foi possível salvar o pokemon!");
									system ("pause");system("cls");
								}
								else
								{
									system("cls");
									printf("Pokemon cadastrado com sucesso!\n\n");
									system ("pause");system("cls");
								}
								free(listar);
							}
							break;
							
						case 3: 
						{
							system("cls");
							int rep;
							Treinador* listar;							
							Pokemon* PonteiroPoke;
							Pokemon Poke;
							do
							{
								system("cls");
								printf("OBTER POKEMON PELO NOME\n\n");
								printf("Digite o nome do pokemon: ");
								fflush(stdin);
								scanf("%[^\n]s", Poke.nome);
								PonteiroPoke = ObterPokemonPeloNome(Poke.nome);
								if (PonteiroPoke == NULL)
								{
									printf("Pokemon não encontrado!\nDeseja procurar novamente?\n\n1-Sim 2-Não\n\nOpção: ");
									scanf("%d", &rep);
								}
								else
								{
									listar = ObterTreinadorPeloCodigo(PonteiroPoke->codTreinador);
									printf("\nCODIGO - NOME - ATAQUE - DEFESA - VIDA - DONO\n\n");
									printf("%d    -  %s - %d - %d - %d - %s\n\n", PonteiroPoke->cod, PonteiroPoke->nome, PonteiroPoke->PA, PonteiroPoke->PD, PonteiroPoke->PV, listar->nome);
									system("pause");
									free (listar);
								}
							}while (rep==1);
							free (PonteiroPoke);
						}
							break;
							
						case 4: 
						{
							system("cls");
							int codPoke, rep, i,j;
							if (QuantidadePokemons()<=2)
							{
								printf("\nNão é possível ter menos de dois pokemons cadastrados!");
							}
							else
							{
								do
								{
									rep=0;
									system("cls");
									printf("EXCLUIR POKEMON\n\n");
									listarPokemon();
									printf("\nDigite o código do pokemon que queres excluir: ");
									scanf("%d", &codPoke);
									Batalha* bat;
									for (i=0;i<QuantidadeBatalhas(); i++)
									{
										bat = ObterBatalhaPeloIndice(i);
										for(j=0; j<2;j++)
										{
											if(bat->codPokemon[j] == codPoke)
											{
												printf("Não é possível excluir pokemon, ele já realizou alguma batalha!\n\n");
												system("pause");
												rep=-1;
												free(bat);
												break;
											}
										}
										if(rep==-1)
										{
											break;
										}
										free(bat);
									}
									if(rep==-1)
									{
										break;
									}
									if (VerificaCodPoke(codPoke)==false)
									{
										printf("Código Inexistente!\n\n");
										rep = 2;
										system("pause");
									}
									else
									{
										Treinador* listar;
										Pokemon* PonteiroPoke;
										PonteiroPoke = ObterPokemonPeloCodigo(codPoke);
										listar = ObterTreinadorPeloCodigo(PonteiroPoke->codTreinador);
										printf("\nCODIGO - NOME - ATAQUE - DEFESA - VIDA - DONO\n\n");
										printf("%d    -  %s - %d - %d - %d - %s\n\n", PonteiroPoke->cod, PonteiroPoke->nome, PonteiroPoke->PA, PonteiroPoke->PD, PonteiroPoke->PV, listar->nome);
										printf("Confirmar as informações?\n\n1-Sim 2-Não\n\nOpção: ");
										scanf("%d", &rep);
										free(PonteiroPoke);
										free(listar);
									}
								}while (rep == 2);
								if(rep==-1)
								{
									break;
								}
								if (ApagarPokemonPeloCodigo(codPoke)==true)
								{
									printf("Pokemon excluído com sucesso!\n\n");
									system("pause");
								}
								else
									printf("Não foi possível excluir o pokemon!\n\n");
							}		
						}
							break;
							
						default: 
							printf("\nCódigo de menu inválido!\n\n");
							system("pause");
					}
				}
			}
				
			case 3: 
				while (subCod!=0)
				{
					system("cls");
					subMenuGinasio();
					scanf("%d", &subCod);
					switch(subCod)
					{
						case 0: 
							system("cls");
							break;
							
						case 1: 
							system("cls");
							printf("LISTAR GINASIOS\n\n");
							listarGinasio();
							system("pause");
							break;
							
						case 2:
							{
								int rep=0;
								Ginasio g;
								do
								{
									system("cls");
									int i;
									printf("CADASTRAR GINASIO\n\n");
									printf("Ginasios existentes:\n\n");
									Ginasio* listar;
									printf("CÓDIGO -   NOME\n");
									for (i=0;i<QuantidadeGinasios();i++)
									{
										listar = ObterGinasioPeloIndice(i);
										printf("   %d   - %s\n",listar->codigo, listar->nome);
										free(listar);
									}
									printf("\n");
									printf("Digite o codigo que queres cadastrar no ginasio: ");
									do
									{
										scanf("%d", &g.codigo);
										if(g.codigo<0)
										{
											printf("Não pode código negativo! Tente novamente: ");
										}
									}while(g.codigo<0);
									do
									{
										if(VerificaCodGinasioExistente(g.codigo))
										{
											printf("Esse código já está em uso! Tente outro: ");
											scanf("%d", &g.codigo);
										}
									}while(VerificaCodGinasioExistente(g.codigo));
									printf("Digite o nome que queres cadastrar no ginasio: ");
									fflush(stdin);
									scanf("%[^\n]s", g.nome);
									do
									{
										if(VerificaNomeGinasio(g.nome))
										{
											fflush(stdin);
											printf("Esse nome já está em uso! Tente novamente: ");
											scanf("%[^\n]s", g.nome);
										}
									}while (VerificaNomeGinasio(g.nome));
									printf("Digite o nome do bairro do ginasio: ");
									fflush(stdin);
									scanf("%[^\n]s", g.bairro);
									printf("Digite capacidade de espectadores do ginasio: ");
									scanf("%d", &g.capacidade);
									system("cls");
									printf("%d - %s | %s | %d\n\n", g.codigo, g.nome, g.bairro, g.capacidade);
									printf("Confirmar informações?\n\n1-Sim 2-Não\n\nOpção: ");
									scanf("%d", &rep);
								}while (rep == 2);
								if(SalvarGinasio(g)==false)
								{
									printf("Não foi possível salvar o ginásio!");
									system("\n\npause");
								}
								else
								{
									printf("\n\nGinásio salvo com sucesso!");
									sleep(1);
								}
							}
							break;
							
						case 3: 
							{
								int i;
								int rep;						
								Ginasio* PonteiroGinasio;
								Ginasio ginas;
								do
								{
									system("cls");
									printf("OBTER GINASIO PELO BAIRRO\n\n");
									printf("Digite o nome do bairro: ");
									fflush(stdin);
									scanf("%[^\n]s", ginas.bairro);
									PonteiroGinasio = ObterGinasioPeloBairro(ginas.bairro);
									if (PonteiroGinasio == NULL)
									{
										free(PonteiroGinasio);
										printf("Ginasio não encontrado!\nDeseja procurar novamente?\n\n1-Sim 2-Não\n\nOpção: ");
										scanf("%d", &rep);
									}
									else
									{
										printf("CÓDIGO | NOME | BAIRRO | ESPECTADORES\n");
										for (i=0;i<QuantidadeGinasiosEncontrados();i++)
										{
											printf("%d | %s | %s | %d\n", PonteiroGinasio[i].codigo,PonteiroGinasio[i].nome, PonteiroGinasio[i].bairro, PonteiroGinasio[i].capacidade);
										}
										free(PonteiroGinasio);
									}
									printf("Pesquisar novamente?\n\n1-Sim 2-Não\n\n");
									scanf("%d", &rep);
								}while (rep==1);
							}
							break;
						
						case 4: 
							system("cls");
							if (QuantidadeGinasios()<=1)
							{
								printf("\nNão é possível ter menos de um ginasio cadastrado!");
								sleep(2);
								break;
							}
							int rep;
							printf("EXCLUIR GINASIO\n\n");
							int cod;
							rep=0;
							listarGinasio();
							printf("Digite o código do ginásio: ");
							scanf("%d", &cod);
							for (i=0;i<QuantidadeBatalhas();i++)
							{
								Batalha* listarB = ObterBatalhaPeloIndice(i);
								if (cod == listarB->codGinasio)
								{
									printf("Não é possível excluir o ginásio, já houve alguma batalha nele!\n\n");
									system("pause");
									rep=-1;
									free(listarB);
									break;
								}
								free(listarB);
							}
							if(rep==-1)
							{
								break;
							}
							if(cod<0)
							{
								do
								{
									printf("Código negativo, não pode! Tente outro: ");
									scanf("%d", &cod);
								}while (cod<0);
							}
							if(VerificaCodGinasioExistente(cod)==false)
							{
								printf("Não há ginásios cadastrados nesse código!\n");
								do
								{
									printf("Procurar novamente?\n\n1-Sim 2-Não\n\nOpção: ");
									scanf("%d", &rep);
									if (rep==1)
									{
										printf("Digite o código do ginásio: ");
										scanf("%d", &cod);
									}
									else
									break;
								}while(VerificaCodGinasioExistente(cod)==false);
							}
							if(ExcluirGinasioPeloCodigo(cod)==false)
							{
								printf("Não foi possível excluir o ginásio!\n");
							}
							else
							{
								printf("Ginasio excluído com sucesso!\n");
								sleep(2);
								}
							break;
						
						default: 
							printf("Código de menu inválido!\n\n");
							system("pause");
					}
				}
			break;
				
			case 4: 
				while (subCod!=0)
				{
					system("cls");
					subMenuBatalha();
					scanf("%d", &subCod);
					switch(subCod)
					{
						case 0: 
							system("cls");
							break;
							
						case 1: 
							{
								system("cls");
								printf("LISTAR BATALHAS\n\n");
								listarBatalhas();
								system("pause");
							}
						break;
						
						case 2: 
						{
							system("cls");
							int cod, i;
							if(QuantidadeBatalhas()==0)
							{
								printf("Não há batalhas feitas ainda!\n\n");
								sleep(2);
							}
							else
							{
								printf("LISTAR BATALHA POR TREINADOR\n\n");
								listarTreinadores();
								printf("Digite o código do treinador: ");
								scanf("%d" ,&cod);
								listarBatalhasEspecial1(cod);
								system("\npause");
							}
						}
						break;
							
						case 3: 
							{
								system("cls");
								int cod, i;
								if(QuantidadeBatalhas()==0)
								{
									printf("Não há batalhas feitas ainda!\n\n");
									sleep(2);
								}
								else
								{
									printf("LISTAR BATALHA POR GINASIO\n\n");
									listarGinasio();
									printf("Digite o código do ginásio: ");
									scanf("%d",&cod);
									listaBatGinasio(cod);
									system("\n\npause");
								}
							}
							break;
						
						case 4:
							{
								system("cls");
								int i, j, rep;
								Batalha batalhaOficial;
								Treinador* Treinadores[2];
								Pokemon* Pokemons[2]; 
								Pokemon*listarP;
								Treinador* listarT;
								Ginasio* ginasio;
								int codTreinUsado=-1, codPokUsado=-1;
								printf("REALIZAR BATALHA!");
								if (QuantidadeTreinadores()==2)
								{
									printf("EXCLUIR TREINADOR\n\n");
									printf("É necessário ter no mínimo 2 treinadores cadastrados!\n\n");
									system("pause"); system("cls");
								}
								else
								{
										do
										{
											if (rep==2)
											{
												system("cls");
												i=0;
												codTreinUsado=-1;
											}
											for (i=0; i<2; i++)
											{
												listarTreinadores(codTreinUsado);
												printf("Digite o código do");
												if (i==1)
												{
													printf(" outro");
												}
												printf(" treinador que deseja usar: ");
												scanf("%d", &batalhaOficial.codTreinador[i]);
												if(i==0)
												{
													codTreinUsado = batalhaOficial.codTreinador[i];
												}
												else
												{
													if (codTreinUsado == batalhaOficial.codTreinador[i])
													{
														do
														{
															printf("Código já foi usado! Tente novamente: ");
															scanf("%d", &batalhaOficial.codTreinador[i]);
														}while(codTreinUsado = batalhaOficial.codTreinador[i]);
													}
												}
												system("cls");
												listarT = ObterTreinadorPeloCodigo(batalhaOficial.codTreinador[i]);
												printf("POKEMONS DE %s\n\nCÓDIGO - NOME | ATAQUE | DEFESA | VIDA\n", listarT->nome);
												for (j=0; j<QuantidadePokemons(); j++)
												{
													listarP = ObterPokemonPeloIndice(j);
													if(listarP->codTreinador==batalhaOficial.codTreinador[i])
													{
														printf("%d - %s | %d | %d | %d\n",listarP->cod, listarP->nome, listarP->PA, listarP->PD, listarP->PV);
													}
													free(listarP);
												}
												printf("\nDigite o codigo do pokemon que deseja usar para o treinador %s?: ", listarT->nome);
												scanf("%d", &batalhaOficial.codPokemon[i]);
												if(batalhaOficial.codTreinador[i]!=ObterPokemonPeloCodigo(batalhaOficial.codPokemon[i])->codTreinador)
												{
													do
													{
														printf("Código não pertence a %s! Tente novamente: ", listarT->nome);
														scanf("%d", &batalhaOficial.codPokemon[i]);
													}while(batalhaOficial.codTreinador[i]!=ObterPokemonPeloCodigo(batalhaOficial.codPokemon[i])->codTreinador);
												}
												Treinadores[i] = ObterTreinadorPeloCodigo(batalhaOficial.codTreinador[i]);
												Pokemons[i] = ObterPokemonPeloCodigo(batalhaOficial.codPokemon[i]);
												system("cls");
												printf("Salvo!");
												sleep(1);
												free(listarT);
											}
											system("cls");
											listarGinasio();
											printf("Digite o código do ginásio onde acontecerá a batalha: ");
											scanf("%d", &batalhaOficial.codGinasio);
											if(VerificaCodGinasioExistente(batalhaOficial.codGinasio)==false)
											{
												do
												{
													printf("Não há ginásios cadastrados nesse código! Tente outro: ");
													scanf("%d", &batalhaOficial.codGinasio);
												}while(VerificaCodGinasioExistente(batalhaOficial.codGinasio)==false);
											}
											ginasio = ObterGinasioPeloCodigo(batalhaOficial.codGinasio);
											batalhaOficial.codigo = QuantidadeBatalhas()+1;
											system("cls");
											printf("CONFIRMAR INFORMAÇÕES\n\n");
											sleep(1);
											printf("Treinadores e seus pokemons:\n");
											sleep(1);
											for(i=0;i<2;i++)
											{
												printf("%s - %s\n", Treinadores[i]->nome, Pokemons[i]->nome);
												sleep(1);	
											}
											printf("\nGinasio: %s - %d espectadores\n\nBatalhar?",ginasio->nome, ginasio->capacidade);
											sleep(1);
											printf("\n\n1-Sim 2-Não\n\nOpção: ");
											scanf("%d",&rep);
										}while(rep==2);
										system("cls");
										printf("PREPARADOS?");
										sleep(1);
										printf(" Hora da Batalha!");
										sleep(1);
										system("cls");
										int PD[2] = {Pokemons[0]->PD,Pokemons[1]->PD};
										rep=0;
										do
										{
											system("cls");
											for (i=0; i<2; i++)
											{
												if (Pokemons[0]->PV <= 0.0)
												{
													rep=1;
													break;
												}
												else if (Pokemons[1]->PV <= 0.0)
												{
													rep=1;
													break;
												}
												int cod;
												Pokemons[i]->PD = PD[i];
												printf("TURNO DE %s\n\n", Pokemons[i]->nome);
												listarDesenhoPoke(i);
												printf("Status : Vida %d - Ataque %d - Defesa %d\nBônus do treinador : Ataque %d - Defesa %d\n\n", Pokemons[i]->PV, Pokemons[i]->PA, Pokemons[i]->PD, Treinadores[i]->bonusATQ, Treinadores[i]->bonusDEF);
												printf("1-Ataque 2-Defesa\nOpção: ");
												scanf("%d", &cod);
												printf("\n");
												switch (cod)
												{
													int subCod;
													case 1:
														if(i==0)
														{
															printf("1- Ataque chocante: Dano +3\n");
															printf("2- Ataque veloz: 2x Dano\n");
															printf("Defesa de %s: %d\nOpção: ",Pokemons[1]->nome,Pokemons[1]->PD);
															scanf("%d", &subCod);
															switch (subCod)
															{
																case 1:
																	{
																		int vidaList = Pokemons[1]->PV;
																		Pokemons[1]->PV = Pokemons[1]->PV - (((Pokemons[0]->PA + Treinadores[0]->bonusATQ)+3)-Pokemons[1]->PD);
																		if(Pokemons[1]->PV>=vidaList)
																		{
																			printf("1 de Dano (mínimo)\n");
																			Pokemons[1]->PV = vidaList-1;
																		}
																		else
																		printf("%d de Dano\n", vidaList - Pokemons[1]->PV);
																	}
																	break;
																	
																case 2:
																	{
																		int vidaList = Pokemons[1]->PV;
																		Pokemons[1]->PV = Pokemons[1]->PV - (((Pokemons[0]->PA + Treinadores[0]->bonusATQ)*2)-Pokemons[1]->PD);
																		if(Pokemons[1]->PV>=vidaList)
																		{
																			printf("1 de Dano (mínimo)\n");
																			Pokemons[1]->PV = vidaList-1;
																		}
																		else
																		printf("%d de Dano\n", vidaList - Pokemons[1]->PV);
																	}
																	break;
																	
																default: 
																	printf("Código Inválido, perdeu a vez!");
															}
														}
														else
														{
															printf("1- Ataque terroso: Dano verdadeiro\n");
															printf("2- Terremoto: Dois ataques iguais melhorados(+2)\n");
															printf("Defesa de %s: %d\nOpção: ",Pokemons[0]->nome,Pokemons[0]->PD);
															scanf("%d", &subCod);
															switch (subCod)
															{
																case 1:
																	{
																		int vidaList = Pokemons[0]->PV;
																		Pokemons[0]->PV = Pokemons[0]->PV - (Pokemons[1]->PA + Treinadores[1]->bonusATQ);
																		printf("%d de Dano\n", vidaList - Pokemons[0]->PV);
																	}
																	break;
																	
																case 2:
																	{
																		int vidaList = Pokemons[0]->PV;
																		Pokemons[0]->PV = Pokemons[0]->PV - (((Pokemons[1]->PA + Treinadores[1]->bonusATQ+2)*2)-Pokemons[0]->PD);
																		if(Pokemons[0]->PV>=vidaList)
																		{
																			printf("1 de Dano (mínimo)\n");
																			Pokemons[0]->PV = vidaList-1;
																		}
																		else
																		printf("%d de Dano\n", vidaList - Pokemons[0]->PV);
																	}
																	break;
																	
																default: 
																	printf("Código Inválido, perdeu a vez!");
															}
														}
														break;
														
													case 2:
														if(i==0)
														{
															printf("1- Bloquear: Defesa +2\n");
															printf("2- Esquivar: x2 Defesa\n");
															printf("Defesa de %s: %d\nOpção: ",Pokemons[1]->nome,Pokemons[1]->PD);
															scanf("%d", &subCod);
															switch (subCod)
															{
																case 1:
																	{
																		Pokemons[0]->PD = (Pokemons[0]->PD + Treinadores[0]->bonusDEF)+2;
																		printf("%d de Defesa",Pokemons[0]->PD);
																		break;
																	}
																	
																case 2:
																	{
																		Pokemons[0]->PD = (Pokemons[0]->PD+Treinadores[0]->bonusDEF)*2;
																		printf("%d de Defesa",Pokemons[0]->PD);
																		break;
																	}
																	
																default: 
																	printf("Código Inválido, perdeu a vez!");
															}
														}
														else
														{
															printf("1- Entrar na terra: Defesa +2\n");
															printf("2- Desviar: Defesa x2\n");
															printf("Defesa de %s: %d\nOpção: ",Pokemons[0]->nome,Pokemons[0]->PD);
															scanf("%d", &subCod);
															switch (subCod)
															{
																case 1:
																	{
																		Pokemons[1]->PD = (Pokemons[1]->PD+Treinadores[1]->bonusDEF)+2;
																		printf("%d de Defesa",Pokemons[1]->PD);
																		break;
																	}
																	
																case 2:
																	{
																		Pokemons[1]->PD = (Pokemons[1]->PD+Treinadores[1]->bonusDEF)*2;
																		printf("%d de Defesa",Pokemons[1]->PD);
																		break;
																	}
																	
																default: 
																	printf("Código Inválido, perdeu a vez!");
															}
														}
														break;
														
													default: 
														printf("Código Inválido, perdeu a vez!");	
												}
												sleep(1);
												system("cls");
											}
										}while (rep==0);
										if (Pokemons[0]->PV <= 0)
										{
											printf("FIM DE TURNO\n");
											sleep(1);
											printf("Vitória de %s", Pokemons[1]->nome);
											Treinadores[1]->bonusATQ = Treinadores[1]->bonusATQ*2;
											Treinadores[1]->bonusDEF = Treinadores[1]->bonusDEF*2;
											AtualizarTreinador(Treinadores[1]);
											Pokemons[1]->PA = Pokemons[1]->PA+5;
											Pokemons[1]->PD = Pokemons[1]->PD+5;
											Pokemons[1]->PV = Pokemons[1]->PV+20;
											AtualizarPokemon(Pokemons[1]);
											batalhaOficial.codPokVencedor = Pokemons[1]->cod;
											listarDesenhoPoke(1);
											system("pause");
										}
										else
										{
											printf("FIM DE TURNO\n");
											sleep(1);
											printf("Vitória de %s", Pokemons[0]->nome);
											Treinadores[0]->bonusATQ = Treinadores[0]->bonusATQ*2;
											Treinadores[0]->bonusDEF = Treinadores[0]->bonusDEF*2;
											AtualizarTreinador(Treinadores[0]);
											Pokemons[0]->PA = Pokemons[0]->PA+5;
											Pokemons[0]->PD = Pokemons[0]->PD+5;
											Pokemons[0]->PV = Pokemons[0]->PV+20;
											AtualizarPokemon(Pokemons[0]);
											batalhaOficial.codPokVencedor = Pokemons[0]->cod;
											listarDesenhoPoke(0);
											system("pause");	
										}
										for (i=0;i<2;i++)
										{
											free(Treinadores[i]);
											free(Pokemons[i]);	
										}
										free(ginasio);
										if (SalvarBatalha(batalhaOficial)==false)
										{
											printf("Algum erro ocorreu na batalha!");
										}
										else
										{
											system("cls");
											printf("O treinador vencedor ganha 100%% em todos os seus atributos\ne o Pokemon vendedor evolui (ganha 5 de dano e defesa, e 20 de vida)!");
											sleep(2);
										}
									}
								}
						break;
							
						case 5: 
							system("cls");
							printf("OBTER SCORE DO TREINADOR\n\n");
							listarTreinadores();
							printf("Digite o código do treinador: ");
							{
								int cod;
							}
							scanf("%d", &cod);
							printf("\n");
							if (ObterScorePositivoTreinador(cod) == 0 &&  ObterScoreNegativoTreinador(cod)==0)
							{
								printf("Esse treinador não realizou nenhuma batalha!\n\n");
							}
							else
							printf("Esse treinador tem %d vitórias e %d derrotas\n\n",ObterScorePositivoTreinador(cod),ObterScoreNegativoTreinador(cod));
							system("pause");
							break;
							
						default: 
						printf("\n\nCódigo Invalido!\nTente Novamente\n\n");
						system("pause");
						system("cls");
					}
				}
				break;
				
			default: 
				printf("\n\nCódigo Invalido!\nTente Novamente\n\n");
				system("pause");
				system("cls");
		}
	}
	
}

void finalizar(){
	printf("\nFINALIZAR:");	
	printf("\n\nObrigado por jogar!");
}
void subMenuTreinador(){
	system("cls");
	printf(" ----------------MENU-----------------\n");
	printf("|            TREINADORES              |\n");
	printf("| 0. Sair                             |\n");
	printf("| 1. Listar                           |\n");
	printf("| 2. Cadastrar                        |\n");
	printf("| 3. Atualizar                        |\n");
	printf("| 4. Excluir                          |\n");
	printf(" -------------------------------------\n\n");
	printf("O que deseja fazer?\nOpção:  ");
}
void subMenuPokemon(){
	system("cls");
	printf(" ----------------MENU-----------------\n");
	printf("|              POKEMONS               |\n");
	printf("| 0. Sair                             |\n");
	printf("| 1. Listar                           |\n");
	printf("| 2. Cadastrar                        |\n");
	printf("| 3. Pesquisa pelo nome               |\n");
	printf("| 4. Excluir                          |\n");
	printf(" -------------------------------------\n\n");
	printf("O que deseja fazer?\nOpção: ");
}
void subMenuGinasio(){
	system("cls");
	printf(" ----------------MENU-----------------\n");
	printf("|              GINASIOS               |\n");
	printf("| 0. Sair                             |\n");
	printf("| 1. Listar                           |\n");
	printf("| 2. Cadastrar                        |\n");
	printf("| 3. Pesquisar                        |\n");
	printf("| 4. Excluir                          |\n");
	printf(" -------------------------------------\n\n");
	printf("O que deseja fazer?\nOpção: ");
}
void subMenuBatalha(){
	system("cls");
	printf(" ----------------MENU-----------------\n");
	printf("|              BATALHA!               |\n");
	printf("| 0. Sair                             |\n");
	printf("| 1. Listar                           |\n");
	printf("| 2. Listar batalhas do treinador     |\n");
	printf("| 3. Listar batalhas no ginasio       |\n");
	printf("| 4. Realizar uma batalha!            |\n");
	printf("| 5. Procurar score do treinador      |\n");
	printf(" -------------------------------------\n\n");
	printf("O que deseja fazer?\nOpção: ");
}
void listarTreinadores(int cod){
	int i;
	Treinador* listar;
	printf("CÓDIGO - NOME | BONUS ATQ | BONUS DEF\n");
	for (i=0;i<QuantidadeTreinadores();i++)
	{
		listar = ObterTreinadorPeloIndice(i);
		if(listar->codigo != cod)
		printf("%d - %s | %d | %d\n", listar->codigo,listar->nome, listar->bonusATQ, listar->bonusDEF);
		free(listar);
	}
	printf("\n");
}
void listarPokemon(int cod){
	int i;
	Treinador* listarDono;
	Pokemon* listar;
	printf("CÓDIGO - NOME | ATAQUE | DEFESA | VIDA | DONO\n");
	for (i=0;i<QuantidadePokemons();i++)
	{
		listar = ObterPokemonPeloIndice(i);
		listarDono = ObterTreinadorPeloCodigo(listar->codTreinador);
		if(listar->cod != cod)
		{
			printf("%d - %s | %d | %d | %d | %s\n",listar->cod, listar->nome, listar->PA, listar->PD, listar->PV,listarDono->nome);
		}
		free(listar);
		free(listarDono);
	}
	printf("\n");
}
void listarGinasio(){
	int i;
	Ginasio* listar;
	printf("CÓDIGO -   NOME    | BAIRRO | ESPECTADORES\n");
	for (i=0;i<QuantidadeGinasios();i++)
	{
		listar = ObterGinasioPeloIndice(i);
		
//		for (j = 0 ; j < 10-strlen(listar->nome); j++)
//			printf(" ");
		printf("   %d   - %s | %s | %d \n",listar->codigo, listar->nome, listar->bairro, listar->capacidade);
		free(listar);
	}
	printf("\n");
}
void listarBatalhas()
{
	int i;
	Batalha* listarB;
	Treinador* TreinadorVencedor;
	Treinador* Treinador2;
	Pokemon* PokemonVencedor;
	Pokemon* Pokemon2;
	Ginasio* ginasio;
	if(QuantidadeBatalhas()==0)
	{
		printf("Não há batalhas feitas ainda!\n\n");
	}
	else
	{
		printf("CÓDIGO - TREINADORES - POKEMONS - GINASIO - VENCEDORES\n");
		for (i=0;i<QuantidadeBatalhas();i++)
		{
			listarB = ObterBatalhaPeloIndice(i);
			TreinadorVencedor = ObterTreinadorPeloCodigo(ObterPokemonPeloCodigo(listarB->codPokVencedor)->codTreinador);
			if (TreinadorVencedor->codigo == listarB->codTreinador[0])
			{
				Treinador2 = ObterTreinadorPeloCodigo(listarB->codTreinador[1]);
			}
			else
			{
				Treinador2 = ObterTreinadorPeloCodigo(listarB->codTreinador[0]);
			}
			PokemonVencedor = ObterPokemonPeloCodigo(listarB->codPokVencedor);
			if (PokemonVencedor->cod == listarB->codPokemon[0])
			{
				Pokemon2 = ObterPokemonPeloCodigo(listarB->codPokemon[1]);
			}
			else
			{
				Pokemon2 = ObterPokemonPeloCodigo(listarB->codPokemon[0]);
			}
			ginasio =  ObterGinasioPeloCodigo(listarB->codGinasio);
			if (listarB == NULL)
			{
				printf("Erro");
			}
			printf("   %d  - %s vs %s - %s | %s - %s - %s com %s\n",listarB->codigo,TreinadorVencedor->nome,Treinador2->nome,PokemonVencedor->nome, Pokemon2->nome, ginasio->nome, TreinadorVencedor->nome, PokemonVencedor->nome);
			free(listarB);
			free(TreinadorVencedor);
			free(Treinador2);
			free(PokemonVencedor);
			free(Pokemon2);
			free(ginasio);
		}
		printf("\n");
	}
}
void listarBatalhasEspecial1(int cod)
{
	int i;
	Batalha* listarB = ObterBatalhasTreinador(cod);
	if (listarB == NULL)
	{
		printf("Treinador não encontrado!");
		free(listarB);
	}
	else
	{
		Treinador* TreinadorVencedor;
		Treinador* Treinador2;
		Pokemon* PokemonVencedor;
		Pokemon* Pokemon2;
		Ginasio* ginasio;
		printf("CÓDIGO - TREINADORES - POKEMONS - GINASIO - VENCEDORES\n");
		for (i=0;i<QuantidadeBatalhasEncontradas();i++)
		{
			TreinadorVencedor = ObterTreinadorPeloCodigo(ObterPokemonPeloCodigo(listarB[i].codPokVencedor)->codTreinador);
			if (TreinadorVencedor->codigo == listarB[i].codTreinador[0])
			{
				Treinador2 = ObterTreinadorPeloCodigo(listarB[i].codTreinador[1]);
			}
			else
			{
				Treinador2 = ObterTreinadorPeloCodigo(listarB[i].codTreinador[0]);
			}
			PokemonVencedor = ObterPokemonPeloCodigo(listarB[i].codPokVencedor);
			if (PokemonVencedor->cod == listarB[i].codPokemon[0])
			{
				Pokemon2 = ObterPokemonPeloCodigo(listarB[i].codPokemon[1]);
			}
			else
			{
				Pokemon2 = ObterPokemonPeloCodigo(listarB[i].codPokemon[0]);
			}
			ginasio =  ObterGinasioPeloCodigo(listarB[i].codGinasio);
			printf("   %d  - %s vs %s - %s | %s - %s - %s com %s\n",listarB->codigo,TreinadorVencedor->nome,Treinador2->nome,PokemonVencedor->nome, Pokemon2->nome, ginasio->nome, TreinadorVencedor->nome, PokemonVencedor->nome);
			}
			free(listarB);
			free(TreinadorVencedor);
			free(Treinador2);
			free(PokemonVencedor);
			free(Pokemon2);
			free(ginasio);
	}
}

void listaBatGinasio(int codG)
{
	int i;
	Batalha* listarB = ObterBatalhasGinasio(codG);
	if (listarB == NULL)
	{
		printf("Batalha não encontrada nesse ginásio!");
		free(listarB);
	}
	else
	{
		Treinador* TreinadorVencedor;
		Treinador* Treinador2;
		Pokemon* PokemonVencedor;
		Pokemon* Pokemon2;
		Ginasio* ginasio;
		printf("CÓDIGO - TREINADORES - POKEMONS - GINASIO - VENCEDORES\n");
		for (i=0;i<QuantidadeBatalhasEncontradas();i++)
		{
			TreinadorVencedor = ObterTreinadorPeloCodigo(ObterPokemonPeloCodigo(listarB[i].codPokVencedor)->codTreinador);
			if (TreinadorVencedor->codigo == listarB[i].codTreinador[0])
			{
				Treinador2 = ObterTreinadorPeloCodigo(listarB[i].codTreinador[1]);
			}
			else
			{
				Treinador2 = ObterTreinadorPeloCodigo(listarB[i].codTreinador[0]);
			}
			PokemonVencedor = ObterPokemonPeloCodigo(listarB[i].codPokVencedor);
			if (PokemonVencedor->cod == listarB[i].codPokemon[0])
			{
				Pokemon2 = ObterPokemonPeloCodigo(listarB[i].codPokemon[1]);
			}
			else
			{
				Pokemon2 = ObterPokemonPeloCodigo(listarB[i].codPokemon[0]);
			}
			ginasio =  ObterGinasioPeloCodigo(listarB[i].codGinasio);
			printf("   %d  - %s vs %s - %s | %s - %s - %s com %s\n",listarB->codigo,TreinadorVencedor->nome,Treinador2->nome,PokemonVencedor->nome, Pokemon2->nome, ginasio->nome, TreinadorVencedor->nome, PokemonVencedor->nome);
			free(listarB);
			free(TreinadorVencedor);
			free(Treinador2);
			free(PokemonVencedor);
			free(Pokemon2);
			free(ginasio);
		}
		
	}	
}
void listarDesenhoPoke(int i)
{
	if (i==0)
	{
		printf("\n                    ______\n");
		printf("|\\                /::::::/\n");
		printf("| \\  _________   /::::::/\n");
		printf("|  \\/         \\/       /\n");
		printf("|                _____/\n");
		printf(" \\   __      __  \\      \n");
		printf("  | |  |    |  | |  \n");
		printf(" /        .       \\  \n");
		printf(" | ++          ++ |\n"); 
		printf(" | ++          ++ |\n");
		printf("  \\              /\n");
		printf("   --------------\n\n");
	}
	else
	{
		printf("\n    ___________\n");
		printf("   /           \\\n");
		printf("  /   _     _   \\\n");
		printf(" |   | |   | |   |\n");
		printf(" |   | |   | |   |\n");
		printf(" |    -     -    |\n");
		printf(" |     _____     |\n");
		printf(" |    (_____)    |\n");
		printf(" |               |\n"); 
		printf(" |               |\n");
		printf(" |:::::::::::::::|\n");
		printf("-------------------\n\n");
	}
}

/*				  5. Listar Pokemons                                                            |\n");
		printf("| 6. Cadastrar pokemon pelo Código                                              |\n");
		printf("| 7. Pesquisar pokemon pelo nome                                                |\n");
		printf("| 8. Excluir pokemon pelo Código                                                |\n");
		printf("| 9. Listar Ginasios                                                            |\n");
		printf("| 10. Cadastrar Ginasio pelo Código                                             |\n");
		printf("| 11. Pesquisar Ginasio pelo bairro                                             |\n");
		printf("| 12. Excluir Ginasio pelo Código                                               |\n");
		printf("| 13. Listar batalhas do Treinador                                              |\n");
		printf("| 14. Listar batalhas no Ginasio                                                |\n");
		printf("| 15. Realizar uma batalha                                                      |\n");
		printf("| 16. Procurar quantidade de vitorias e de derrotas do treinador */

