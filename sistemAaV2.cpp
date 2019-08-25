#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*	pode compilar direto, sem criar o arquivo produtos.txt na pasta
*	so pegar e rodar
*/

FILE *ptrArquivo;

typedef struct cliente{
	char cpf[9];
	char nome[50];
	short anoNascimento;
	float pontuacao;
}infoCliente;

typedef struct produto{
	int codigoBarras;
	char nome[50];
	char undMedida[3];
	char grupo[20];
	float pontuacao;
	float valor;
}infoProduto;

typedef struct venda{
	char codigo[10];
	char cpfCliente[9];
	char codigoBarras[5];
	unsigned int quantidade;
	char data[9];
	float valorDesconto;
	float valorTotal;
}infoVenda;

typedef struct lMedida{
    short codMedida;
    char tipoMedida[50];
    struct lMedida *next;
}lMedida;
lMedida *listaTotal = NULL;

void cadastrarProduto(void);
void menuGrupo_Produto();
void menuUnidade_Produto();
void lista_TipoMedida(short opInf_UndMedida);
void lista_tipoGrupo(short opInf_GpProduto);
void menu_cadastrarProduto();

void menu_RelProdutosPorValor();
void rel_produtoPorGrupo();
void rel_produtosPorValor();
void rel_produtosCadastrados();

int main(){
	cadastrarProduto();
	rel_produtosPorValor();
	rel_produtosCadastrados();
	system("pause");
	return 0;
}

void cadastrarProduto(void){
	infoProduto cadastroProduto;
	//variaveis auxiliares
	char v_EhVazio;
	int v_UltimoCod;
	char v_Nome[50] = {'\0'};
	char v_Grupo[50] = {'\0'};
	float v_Pontuacao;
	float v_Valor;

	//pedir o nome do produto
	printf("Informe o nome do produto: ");
	scanf("%[^\n]s", cadastroProduto.nome);
	fflush(stdin);

	//transforma td em caixa alta colocando _ nos espacos do nome
	short tamNome = strlen(cadastroProduto.nome);
	for(size_t iNome = 0; iNome < tamNome; iNome++){
		if(cadastroProduto.nome[iNome] >= 97 && cadastroProduto.nome[iNome] <= 122)
		cadastroProduto.nome[iNome] = cadastroProduto.nome[iNome] - 32;
		if(cadastroProduto.nome[iNome] == ' ') cadastroProduto.nome[iNome] = '_';
	}

	//gerar um novo cod. e validar a entrada de produtos pelo nome
	ptrArquivo = fopen("produtos.txt", "r");
	if(ptrArquivo == NULL) exit(EXIT_FAILURE);
	if((v_EhVazio = fgetc(ptrArquivo)) == EOF) v_UltimoCod = 9999;
	else{
		while((fscanf(ptrArquivo, "%d %s %s %f %f\n", &v_UltimoCod, v_Nome, v_Grupo, &v_Pontuacao, &v_Valor)) != EOF){
				if(strcmp(v_Nome, cadastroProduto.nome) == 0){
				printf("ERRO 0000x2: Jah existe um produto cadastrado com esse nome!\n");
				return;
			}
		}//FIM while
	}
	fclose(ptrArquivo);
	v_UltimoCod++;

	//agora ja pode pedir as informações
	//daqui p baixo

	//grupo do produto
	system("cls");
	short opInf_GpProduto = 0;
	menuGrupo_Produto();
	printf("Informe o grupo do produto: ");
	scanf(" %d", &opInf_GpProduto);

	//pontuacao do produto
	system("cls");
	printf("Informe a pontuacao do produto: ");
	scanf("%f%*c", &cadastroProduto.pontuacao);

	//valor do produto
	system("cls");
	printf("Informe o valor do produto: ");
	scanf("%f%*c", &cadastroProduto.valor);

	//escrever os dados no arquivo
	ptrArquivo = fopen("produtos.txt", "a");
	if(ptrArquivo == NULL) exit(EXIT_FAILURE);
	if(v_UltimoCod == 10000)
	fprintf(ptrArquivo, " %d ", v_UltimoCod); //codigo produto
	else fprintf(ptrArquivo, "%d ", v_UltimoCod);
	fprintf(ptrArquivo, "%s ", cadastroProduto.nome); //nome produto

	lista_tipoGrupo(opInf_GpProduto);

	fprintf(ptrArquivo, "%.2f ", cadastroProduto.pontuacao);
	fprintf(ptrArquivo, "%.2f\n", cadastroProduto.valor);
	fclose(ptrArquivo);
	printf("Produto cadastrado com sucesso!\n");
	return;

}//FIM function

void menu_cadastrarProduto(){
	printf("\n=================================================\n");

	printf("\n=================================================\n");
}

void lista_tipoGrupo(short opInf_GpProduto){
	if(opInf_GpProduto == 1) fprintf(ptrArquivo, "%s", "Embalagem ");
	else if(opInf_GpProduto == 2) fprintf(ptrArquivo, "%s", "Bebida ");
	else if(opInf_GpProduto == 3) fprintf(ptrArquivo, "%s", "Alimento ");
	else if(opInf_GpProduto == 4) fprintf(ptrArquivo, "%s", "Alimento_Animal ");
	else if(opInf_GpProduto == 5) fprintf(ptrArquivo, "%s", "Manutencao_em_Geral ");
	else if(opInf_GpProduto == 6) fprintf(ptrArquivo, "%s", "Medicamento ");
	else if(opInf_GpProduto == 7) fprintf(ptrArquivo, "%s", "Material_de_Cozinha ");
	else if(opInf_GpProduto == 8) fprintf(ptrArquivo, "%s", "Higienização_Pessoal ");
	else if(opInf_GpProduto == 9) fprintf(ptrArquivo, "%s", "Semente,_Muda_de_Plantas ");
	else if(opInf_GpProduto == 10) fprintf(ptrArquivo, "%s", "Equipamento_de_informatica ");
	else if(opInf_GpProduto == 11) fprintf(ptrArquivo, "%s", "Material_de_Escritorio ");
	else if(opInf_GpProduto == 12) fprintf(ptrArquivo, "%s", "Material_de_Limpeza ");
}//FIM function

void menuGrupo_Produto(){
	printf("1-> Acondicionamento e Embalagem\n");
	printf("2-> Bebida\n");
	printf("3-> Alimento\n");
	printf("4-> Alimento animal\n");
	printf("5-> Ferramenta de Manutencao em Geral\n");
	printf("6-> Medicamento\n");
	printf("7-> Material de Cozinha\n");
	printf("8-> Higienizacao Pessoal\n");
	printf("9-> Semente, Muda de Plantas\n");
	printf("10-> Equipamento de Informatica\n");
	printf("11-> Material de Escritorio\n");
	printf("12-> Material de limpeza\n");
}//FIM function

void rel_produtoPorGrupo(){
    //escreva daqui pra baixo
    
}//FIM function 

void menu_RelProdutosPorValor(){
	system("cls");	
	printf("========== RELATORIO DE PRODUTOS POR VALOR ==========\n\n");
	printf("1-> Maior ou igual ao valor informado\n");
	printf("2-> Menor ou igual ao valor informado\n");
	printf("3-> Igual ao valor informado\n");
	printf("4-> Entre um intervalo informado\n");
}//FIM funtion

void rel_produtosPorValor(){
	int v_UltimoCod;
	char v_Nome[50] = {'\0'};
	char v_Grupo[50] = {'\0'};
	float v_Pontuacao;
	float v_Valor;
	short tipoConsulta = 0;
	float valorInf1, valorInf2;
	menu_RelProdutosPorValor();
	printf("Informe o tipo de consulta: ");
	scanf(" %d", &tipoConsulta);
	
	if(tipoConsulta == 1){
		printf("Informe um valor: ");
		scanf(" %f", &valorInf1);
		ptrArquivo = fopen("produtos.txt", "r");
		if(ptrArquivo == NULL) exit(EXIT_FAILURE);
		system("cls");
		printf("========================================================\n\n");
		while((fscanf(ptrArquivo, "%d %s %s %f %f\n", &v_UltimoCod, v_Nome, v_Grupo, &v_Pontuacao, &v_Valor)) != EOF){
			if(v_Valor >= valorInf1){
				short tamV_Nome = strlen(v_Nome);
				for(size_t iNome = 0; iNome < tamV_Nome; iNome++)
				if(v_Nome[iNome] == '_') v_Nome[iNome] = ' ';
				printf("%d - %s ---------- R$%.2f\n", v_UltimoCod, v_Nome, v_Valor);
			} 	
		}
		printf("\n========================================================\n");
	}//FIM consulta1
	
		if(tipoConsulta == 2){
		printf("Informe um valor: ");
		scanf(" %f", &valorInf1);
		ptrArquivo = fopen("produtos.txt", "r");
		if(ptrArquivo == NULL) exit(EXIT_FAILURE);
		system("cls");
		printf("========================================================\n\n");
		while((fscanf(ptrArquivo, "%d %s %s %f %f\n", &v_UltimoCod, v_Nome, v_Grupo, &v_Pontuacao, &v_Valor)) != EOF){
			if(v_Valor <= valorInf1){
				short tamV_Nome = strlen(v_Nome);
				for(size_t iNome = 0; iNome < tamV_Nome; iNome++)
				if(v_Nome[iNome] == '_') v_Nome[iNome] = ' ';
				printf("%d - %s ---------- R$%.2f\n", v_UltimoCod, v_Nome, v_Valor);
			} 	
		}
		printf("\n========================================================\n");
	}//FIM consulta2
	
		if(tipoConsulta == 3){
		printf("Informe um valor: ");
		scanf(" %f", &valorInf1);
		ptrArquivo = fopen("produtos.txt", "r");
		if(ptrArquivo == NULL) exit(EXIT_FAILURE);
		system("cls");
		printf("========================================================\n\n");
		while((fscanf(ptrArquivo, "%d %s %s %f %f\n", &v_UltimoCod, v_Nome, v_Grupo, &v_Pontuacao, &v_Valor)) != EOF){
			if(v_Valor == valorInf1){
				short tamV_Nome = strlen(v_Nome);
				for(size_t iNome = 0; iNome < tamV_Nome; iNome++)
				if(v_Nome[iNome] == '_') v_Nome[iNome] = ' ';
				printf("%d - %s ---------- R$%.2f\n", v_UltimoCod, v_Nome, v_Valor);
			} 	
		}
		printf("\n========================================================\n");
	}//FIM consulta3
	
		if(tipoConsulta == 4){
		printf("Maior que: ");
		scanf(" %f", &valorInf1);
		printf("Menor que: ");
		scanf(" %f", &valorInf2);
		ptrArquivo = fopen("produtos.txt", "r");
		if(ptrArquivo == NULL) exit(EXIT_FAILURE);
		system("cls");
		printf("========================================================\n\n");
		while((fscanf(ptrArquivo, "%d %s %s %f %f\n", &v_UltimoCod, v_Nome, v_Grupo, &v_Pontuacao, &v_Valor)) != EOF){
			if(v_Valor >= valorInf1 && v_Valor <= valorInf2){
				short tamV_Nome = strlen(v_Nome);
				for(size_t iNome = 0; iNome < tamV_Nome; iNome++)
				if(v_Nome[iNome] == '_') v_Nome[iNome] = ' ';
				printf("%d - %s ---------- R$%.2f\n", v_UltimoCod, v_Nome, v_Valor);
			} 	
		}
		printf("\n========================================================\n");
	}//FIM consulta4
	system("pause");
}//FIM function

void rel_produtosCadastrados(){
	int v_UltimoCod;
	char v_Nome[50] = {'\0'};
	char v_Grupo[50] = {'\0'};
	float v_Pontuacao;
	float v_Valor;
	ptrArquivo = fopen("produtos.txt", "r");
	if(ptrArquivo == NULL) exit(EXIT_FAILURE);
	system("cls");
	printf("============ LISTAGEM DE PRODUTOS CADASTRADOS ===========\n\n");
	printf("\nCOD   = PRODUTO ================================= VALOR\n\n");
	while((fscanf(ptrArquivo, "%d %s %s %f %f\n", &v_UltimoCod, v_Nome, v_Grupo, &v_Pontuacao, &v_Valor)) != EOF){
		short tamV_Nome = strlen(v_Nome);
		short dif = 40 - tamV_Nome;
		char v_Hifen[dif + 1] = {'\0'};
			for(size_t iNome = 0; iNome < tamV_Nome; iNome++)
			if(v_Nome[iNome] == '_') v_Nome[iNome] = ' ';
			for(size_t iNome = 0; iNome < dif; iNome++)
			v_Hifen[iNome] = 32;
			printf("%d - %s %s R$%.2f\n", v_UltimoCod, v_Nome, v_Hifen, v_Valor);	
		}
		printf("\n========================================================\n");
		fclose(ptrArquivo);
		system("pause");
}//FIM function
