#include <stdio.h> 		//biblioteca de comunicacao com o usuario
#include <stdlib.h>		//biblioteca de alocacao de espaco de memoria
#include <locale.h>		//biblioteca de alocacao de texto por regiao
#include <string.h>		//biblioteca respons�vel por lidar com strings
#include <stdbool.h>	//biblioteca para trabalhar com variaveis booleanas

int registrar(){
	
	printf("### Cadastro de nomes ###\n\n");
	
	char 	cpf[40], 
			nome[40], 
			sobrenome[40], 
			cargo[40], 
			arquivo[40];
	
	printf("Digite o CPF a ser cadastrado: ");
	scanf("%s",cpf);
	
	strcpy(arquivo, cpf);														//copia as informa��es da vari�vel cpf para a vari�vel arquivo
	//strcat(arquivo, ".txt");													//gera um arquivo com extens�o .txt
	
	FILE *file;																	//cria um ponteiro para uma variavel do tipo FILE? - Cria um arquivo que conter� as informa��s do BD
	file = fopen(arquivo, "w");													//file recebe o retorno de uma fun��o que ir� criar um arquivo cujo nome � a variavel arquivo?
	fprintf(file, cpf);															//escreve o cpf em file
	fclose(file);																//fecha o arquivo file

	file = fopen(arquivo, "a");													//atualiza o arquivo
	fprintf(file, ",");															//escreve uma virgula em file para separar os dados
	fclose(file);																//fecha o arquivo
	
	printf("Digite o nome a ser cadastrado: ");
	fflush(stdin);																//limpa o scanf, se n�o for colocado o programa l� o retorno de carro no proximo scanf 
	scanf("%[^\n]", nome);														//l� at� encontrar o retorno de carro, necess�rio para strings com espa�os 
	
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

signed int formatarConsulta(char *dados, char texto[][50]){						//Inicio da fun��o de formata��o
	
	int atualVirg = 0, proxVirg = 0, index = 0;
	bool flagFim = false;														//Flag para sinalizar o fim da variavel de dados
	
	while(!flagFim){															//Inicio do la�o principal
		
		atualVirg = proxVirg;
			
		while(*(dados + proxVirg) != 0 && *(dados + proxVirg) != ','){			//Se a variavel de dados na posi��o atual for diferente de NULL e de ',' fa�a:
			proxVirg++;
		}
		
		if(*(dados + proxVirg) == 0) flagFim = true;							//Quando chegar no fim da variavel de dados, encerre o la�o while ao fim dessa itera��o
		 
		printf("%s: ",texto[index]);											//Imprime o texto de formata��o
		
		for(;atualVirg < proxVirg; atualVirg++){
			printf("%c", *(dados + atualVirg));									//Imprime as letras da vari�vel dados separando por inicio, entre virgulas e final
		}
		
		printf("\n");
		proxVirg++;
		index++;
		
		if(index >= 10 || index < 0 ){											//Caso a variavel de indice crescer demais, encerre a fun��o e retorne um erro
			return -1;
			break;
		}
		
	}																			//Fim do la�o principal	
	
}																				//Fim da fun��o de formata��o

int consultar(){
	
	setlocale(LC_ALL, "Portuguese");
	
	char	cpf[40],
			conteudo[200],
			texto[][50] = {"CPF","Nome"
				,"Sobrenome","Profiss�o"},
			*pnt;		
	
	pnt = conteudo;
	int i=0;
	
	printf("### Consulta de nomes ###\n\n");
	
	printf("Digite o cpf a ser consultado: ");
	scanf("%s", cpf);
	
	FILE *file;
	file = fopen(cpf, "r");														//l� o arquivo 
	
	if(file == NULL) printf(
		"N�o foi poss�vel abrir o arquivo, cpf n�o localizado!\n");				//trata a falha: arquivo n�o existe ou n�o encontrado
	
	else{																		//caso encotre o arquivo:
																			
		fgets(conteudo, 200, file);												//preenche a vari�vel conteudo com as informa��es que est�o no arquivo
		printf("\n");
		
		if(formatarConsulta(pnt, texto) < 0){									//Chama fun��o para formatar texto da consulta. Caso a fun��o retorne um erro, imprima sem formata��o
			
			system("cls");	
			printf("Ocorreu um erro durante a formata��o da consulta."
			"\nEssa consulta ser� exibida sem formata��o: \n\n");
			printf("%s\n", conteudo);
		}
		printf("\n");
		
	}
	
	fclose(file);
	system("pause");
	
}

int deletar(){
	
	printf("### Deletar CPF ###\n\n");
	
	char cpf[40];
	
	printf("Digite o CPF a ser deletado: ");
	scanf("%s",cpf);
	
	FILE *file;
	file = fopen(cpf, "r");
	
	if(file == NULL){
		printf("\nN�o foi poss�vel encontrar o CPF no sistema\n\n");
		fclose(file);
	}
	else{
		fclose(file);
		remove(cpf);
		printf("\nCPF %s deletado com sucesso\n\n",cpf);
		
	}
	system("pause");
}


int main()
{
	
	int opcao = 0, laco = 1;													//declara��o de vari�veis	
	setlocale(LC_ALL, "Portuguese");											//localizando o texto para o portugues BR
	
	for(laco = 1; laco = 1;){													//inicio do la�o
		
		system("cls");
		
		printf("### Cart�rio da EBAC ###\n\n");									//inicia o menu
		printf("Escolha a op��o desejada do menu:\n\n");
		printf("\t1 - Registrar nomes\n");
		printf("\t2 - Consultar nomes\n");
		printf("\t3 - Deletar nomes\n");
		printf("\t4 - Sair\n\n");						
		printf("Op��o: ");														//fim do menu
	
		scanf("%d", &opcao);
		
		system("cls");
		
		switch(opcao)															//inicio da sele��o
		{
			case 1:
				registrar();				
			break;
		
			case 2:
				consultar();				
			break;
			
			case 3:
				deletar();	
			break;
			
			default:
				if(opcao != 4){
				
					printf("Essa op��o n�o est� disponivel\n\n");
					system("pause");
				}
			break;
		}																		//fim da sele��o
		
		if(opcao == 4) break;
																			
	}																			//fim do la�o
}																				//fim da fun��o main
