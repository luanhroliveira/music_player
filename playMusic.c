#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "player.h"

char name_music[512];
char list_music[512];
char play_music[512];

void abertura_name_music(){
	printf("##########################################################################\n");
	printf("###                                                                    ###\n");
	printf("###                            PLAYER MUSIC                            ###\n");
	printf("###                                                                    ###\n");
	printf("##########################################################################\n");
	printf("***music: [%s]\n\n", list_music);
}

void menu(){
	/* ESSA FUNÇÃO DEFINE O MENU */

	int mod_menu;

	printf("Aleatório[1]\n");
	printf("Procurar música[2]\n");
	scanf("%i", &mod_menu);

	switch(mod_menu){
		case 1:						/* FUNÇÃO MODO ALEATÓRIO */
			aleatorio();
		case 2:						/* FUNÇÃO MODO DE BUSCA */
			busca();
	}
	if(mod_menu == 0){
		system("cls");
		printf("Comando inválido!\n");
		return menu();
	}
}

void aleatorio() {
    /* ESSA FUNÇÃO DEFINE O MODO DE BUSCA DE FORMA ALEATÓRIA */

	FILE* f = fopen("bd_nome_musica.txt", "r");

    if(f == 0) {
        printf("Banco de dados de músicas não disponível.\n\n");
        exit(1);
    }
    int qntd_palavras = 3;
    int caractere;
    
/*    do {
        caractere = fgetc(f);
        if(caractere == '\n') {
            qntd_palavras++;
        }
    }while(caractere != EOF);
    fflush(stdin);
*/   //fscanf(f, "%i", &qntd_palavras);

    srand(time(0));
    int randomico = rand() % qntd_palavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", list_music);
    }
    fclose(f);

    abertura_name_music();

    printf("***%i***\n\n\n", qntd_palavras);
	printf("**%i**\n\n", randomico);
	printf("***%s***\n\n", list_music);
   	strcpy(play_music, "mpg123 bd_music/");
	strcat(play_music, list_music);
   	system(play_music);
}

void busca(){
	/* ESSA FUNÇÃO DEFINE O TIPO DE BUSCA POR "SETAS" */

	int tecla = 0;
	int seta;
	int i = 0;
	int enter = 3;

	FILE* f = fopen("bd_nome_musica.txt", "r");

	printf("Pressione 1 ou 2 para mover-se dentro do arquivo.\n");

	while(tecla != enter){

		scanf("%i", &tecla);
		
		switch (tecla){
			case 1: 						/* SETA_CIMA */
				fseek(f, i, SEEK_SET);
				i++;
			case 2:							/* SETA-BAIXO */
				fseek(f, i, SEEK_SET);
				i--;
		}
		fscanf(f, "%s", list_music);
		printf("%s\n", list_music);
	}
	fclose(f);

    abertura_name_music();

	strcpy(play_music, "mpg123 bd_music/");
	strcat(play_music, list_music);
	system(play_music);
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	/* CHAMADO DE FUNÇÕES */
	abertura_name_music();
	menu();
	printf("%s\n\n\n", play_music);
}