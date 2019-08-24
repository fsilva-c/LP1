#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*	crie um arquivo produtos.txt antes de compilar
*	abçs
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
void rel_produtoPorGrupo();

int main(){
	cadastrarProduto();
	
	printf("\nPressione uma tecla para continuar...\n");
	getchar();
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

	//transforma td em caixa alta
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
	system("clear");
	short opInf_GpProduto = 0;
	menuGrupo_Produto();
	printf("Informe o grupo do produto: ");
	scanf(" %d", &opInf_GpProduto);

	//pontuacao do produto
	system("clear");
	printf("Informe a pontuacao do produto: ");
	scanf("%f%*c", &cadastroProduto.pontuacao);

	//valor do produto
	system("clear");
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
}//FIM function

void menuGrupo_Produto(){
	printf("1-> Acondicionamento e Embalagem\n");
	printf("2-> Alimentícios: Bebida\n");
	printf("3-> Alimentícios: Alimento\n");
	printf("4-> Alimentícios: Alimento animal\n");
	printf("5-> Ferramenta de Manutenção em Geral\n");
	printf("6-> Medicamento\n");
	printf("7-> Material de Expediente: Material de Cozinha\n");
	printf("8-> Material de Expediente: Higienização Pessoal\n");
	printf("9-> Semente, Muda de Plantas\n");
	printf("10-> Equipamento de informatica\n");
}

void rel_produtoPorGrupo(){
    //escreva daqui pra baixo
    
}//FIM function
