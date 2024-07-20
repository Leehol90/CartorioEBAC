#include <stdio.h> 		//biblioteca de comunicacao com o usuario
#include <stdlib.h>		//biblioteca de alocacao de espaco de memoria
#include <locale.h>		//biblioteca de alocacao de texto por regiao
#include <string.h>		//biblioteca responsável por lidar com strings
#include <stdbool.h>	//biblioteca para trabalhar com variaveis booleanas

int login(){
	
	char senha[10];
	
	printf("Digite a senha: ");
	scanf("%s", senha);
	
	return strcmp("admin", senha);
	
}

int registrar(){
	
	printf("### Cadastro de nomes ###\n\n");
	
	char 	cpf[40], 
			nome[40], 
			sobrenome[40], 
			cargo[40], 
			arquivo[40];
	
	printf("Digite o CPF a ser cadastrado: ");
	scanf("%s",cpf);
	
	strcpy(arquivo, cpf);														//copia as informações da variável cpf para a variável arquivo
	//strcat(arquivo, ".txt");													//gera um arquivo com extensão .txt
	
	FILE *file;																	//Cria um arquivo que conterá as informaçõs do BD
	file = fopen(arquivo, "w");													//file recebe o retorno de uma função que irá criar um arquivo cujo nome é a variavel arquivo?
	fprintf(file, cpf);															//escreve o cpf em file
	fclose(file);																//fecha o arquivo file

	file = fopen(arquivo, "a");													//atualiza o arquivo
	fprintf(file, ",");															//escreve uma virgula em file para separar os dados
	fclose(file);																//fecha o arquivo
	
	printf("Digite o nome a ser cadastrado: ");
	fflush(stdin);																//limpa o scanf, se não for colocado o programa lê o retorno de carro no proximo scanf 
	scanf("%[^\n]", nome);														//lê até encontrar o retorno de carro, necessário para strings com espaços 
	
	file = fopen(arquivo, "a");
	fprintf(file, nome);
	fclose(file);
	
	file = fopen(arquivo, "a");										
	fprintf(file, ",");											
	fclose(file);
	
	printf("Digite o sobrenome a ser cadastrado: ");
	fflush(stdin);
	scanf("%[^\n]", sobrenome);
	
	file = fopen(arquivo, "a");
	fprintf(file, sobrenome);
	fclose(file);
	
	file = fopen(arquivo, "a");										
	fprintf(file, ",");											
	fclose(file);
	
	printf("Digite o cargo a ser cadastrado: ");
	fflush(stdin);
	scanf("%[^\n]", cargo);
	
	file = fopen(arquivo, "a");
	fprintf(file, cargo);
	fclose(file);
	
	system("pause");
}

signed int formatarConsulta(char *dados, char texto[][50]){						//Inicio da função de formatação
	
	int atualVirg = 0, proxVirg = 0, index = 0;
	bool flagFim = false;														//Flag para sinalizar o fim da variavel de dados
	
	while(!flagFim){															//Inicio do laço principal
		
		atualVirg = proxVirg;
			
		while(*(dados + proxVirg) != 0 && *(dados + proxVirg) != ','){			//Se a variavel de dados na posição atual for diferente de NULL e de ',' faça:
			proxVirg++;
		}
		 
		printf("%s: ",texto[index]);											//Imprime o texto de formatação
		
		for(;atualVirg < proxVirg; atualVirg++){
			printf("%c", *(dados + atualVirg));									//Imprime as letras da variável dados separando por inicio, entre virgulas e final
		}
		
		if(*(dados + proxVirg) == 0) flagFim = true;							//Quando chegar no fim da variavel de dados, encerre o laço while ao fim dessa iteração
		
		printf("\n");
		proxVirg++;
		index++;
		
		if(index >= 10 || index < 0 ){											//Caso a variavel de indice crescer demais, encerre a função e retorne um erro
			return -1;
			break;
		}
		
	}																			//Fim do laço principal	
	
}																				//Fim da função de formatação

int consultar(){
	
	setlocale(LC_ALL, "Portuguese");
	
	char	cpf[40],
			conteudo[200],
			texto[][50] = {"CPF","Nome"
				,"Sobrenome","Profissão"},
			*pnt;		
	
	pnt = conteudo;
	
	printf("### Consulta de nomes ###\n\n");
	
	printf("Digite o cpf a ser consultado: ");
	scanf("%s", cpf);
	
	FILE *file;
	file = fopen(cpf, "r");														//lê o arquivo 
	
	if(file == NULL) printf(
		"Não foi possível abrir o arquivo, cpf não localizado!\n");				//trata a falha: arquivo não existe ou não encontrado
	
	else{																		//caso encotre o arquivo:
																			
		fgets(conteudo, 200, file);												//preenche a variável conteudo com as informações que estão no arquivo
		
		if(formatarConsulta(pnt, texto) < 0){									//Chama função para formatar texto da consulta. Caso a função retorne um erro, imprima sem formatação
			
			system("cls");	
			printf("Ocorreu um erro durante a formatação da consulta."
			"\nEssa consulta será exibida sem formatação: \n\n");
			printf("%s\n", conteudo);
		}
		
	}
	
	fclose(file);
	printf("\n");
	system("pause");
	
}

int deletar(){
	
	printf("### Deletar CPF ###\n\n");
	
	char cpf[40];
	char confirma;
	
	printf("Digite o CPF a ser deletado: ");									//digite o CPF a ser deletado
	scanf("%s",cpf);
	
	FILE *file;
	file = fopen(cpf, "r");
	
	if(file == NULL){															//caso o CPF digitado não seja encontrado na pasta, informe o usuário
		printf("\nNão foi possível encontrar o CPF no sistema\n\n");
		fclose(file);
	}
	else{																		//Caso o CPF seja encontrado:
		printf("Tem certeza que deseja deletar o CPF: %s (S/N)? ",cpf);			//Confirma que deseja deletar o CPR?
		scanf(" %c", &confirma);
		fclose(file);
		
			if(confirma == 's' || confirma == 'S'){								//Se sim, delete o CPF
			remove(cpf);
			printf("\nCPF %s deletado com sucesso\n\n",cpf);
			}
			else{																//Se não, cancele a operação
				printf("\nExclusão cancelada.\n\n");
			}
		}
	system("pause");
}


int main()
{
	
	int opcao = 0, laco = 1;													//declaração de variáveis	
	setlocale(LC_ALL, "Portuguese");											//localizando o texto para o portugues BR
	int senha = 1;
	
	while(true){																//inicio do laço
		
		system("cls");
		
		printf("### Cartório da EBAC ###\n\n");									//inicia o menu
		printf("Escolha a opção desejada do menu:\n\n");
		printf("\t1 - Registrar nomes\n");										//digite 1 para registrar nomes
		printf("\t2 - Consultar nomes\n");										//digite 2 para consultar nomes
		printf("\t3 - Deletar nomes\n");										//digite 3 para excluir um cadastro
		
		if(senha != 0) printf("\t4 - Login\n");									//caso não esteja logado, digite 4 para entrar com a senha
		else printf("\t4 - Logout\n");											//caso esteja logado, digite 4 para fazer o logout
		
		printf("\n\t5 - Sair\n\n");												//digite 5 para encerrar o programa					
		printf("Opção: ");														//fim do menu
	
		scanf("%d", &opcao);
		
		system("cls");
		
		switch(opcao)															//inicio da seleção
		{
			case 1:																//Seleciona a função para registro de clientes caso esteja logado
				if(senha == 0 ) registrar();
				else
				{
					printf("Voce precisa estar logado" 
						" para acessar esse recurso\n\n");
					system("pause");
				}
			break;
		
			case 2:																//Seleciona a função para consulta de clientes (não é necessário login)
				consultar();				
			break;
			
			case 3:																//Seleciona a função para deletar clientes caso esteja logado
				if(senha == 0) deletar();
				else
				{
					printf("Voce precisa estar logado" 
					" para acessar esse recurso\n\n");
					system("pause");
				}	
			break;
			
			case 4:
				if(senha == 0) senha = 1;										//Chama a função para fazer o login ou para o logout
				else senha = login();
			break;
			
			case 5:																//Finaliza o programa
				return 0;
			break;
			
			default:															//Se nenhum caso válido, reinicia o laço do menu
					printf("Essa opção não está disponivel\n\n");
					system("pause");
			break;
		}																		//fim da seleção
																			
	}																			//fim do laço
}																				//fim da função main
