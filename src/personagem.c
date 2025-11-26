#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "personagem.h"

typedef struct personagem {
	char nome[50];
	int nivel;
	char dado[4];
	int iniciativa;
} Personagem;

/*
 * pelo menos por enquanto, nao vamos usar isso aqui,
 * vai depender da forma que vamos inicializar o personagem
 *
 * #define PERSONAGEM_PADRAO = {"S/N", 0, "S/D", 0};
*/

/* tive que arrumar a forma que eu passava as strings para as variáveis
 * como eu coloquei pra criar o ponteiro do personagem antes da verificao dos
 *  parametros, faltava mandar limpar a memoria caso desse errado
 */
Personagem* criarPersonagem(char nome[50], int nivel, int idDado) {
	Personagem* novo_personagem = malloc((Personagem*) sizeof(Personagem));
	if(novo_personagem == NULL) {
		return NULL;
	}
	if(strlen(nome) < 50 && nivel > 0 && nivel <= 20 && idDado > 0 && idDado <= 6) {
	        strcpy(novo_personagem->nome, nome);
	        novo_personagem->nivel = nivel;
	        novo_personagem->iniciativa = 0;

	        switch(idDado) {
	            case 1:
	            	strcpy(novo_personagem->dado, "D04");
	            	break;
	            case 2:
	            	strcpy(novo_personagem->dado, "D06");
	            	break;
	            case 3:
	            	strcpy(novo_personagem->dado, "D08");
	            	break;
	            case 4:
	            	strcpy(novo_personagem->dado, "D10");
	            	break;
	            case 5:
	            	strcpy(novo_personagem->dado, "D12");
	            	break;
	            case 6:
	            	strcpy(novo_personagem->dado, "D20");
	            	break;
	        }
	    } else {
	        free(novo_personagem);
	        return NULL;
	    }
	    return novo_personagem;
}

/* como a propria estrutura do personagem é um ponteiro por si só,
 * tive que colocar ponteiro de ponteiro pra poder apagar a referencia na main
 */
void apagarPersonagem(Personagem** p) {
	if(p != NULL && *p != NULL) {
		free(*p);
		*p = NULL;
	}
}

int uparNivel(Personagem* p) {
	if (p->nivel == 20) {
		printf("Personagem %s já está no nível máximo.", p->nome);
		return -1;
	} else {
		p->nivel++;
		printf("Personagem %s subiu de nível com sucesso.", p->nome);
		return 1;
	}
}

/* pelo que pesquisei, toda string tem que ter o terminador nulo
 * '\0' na ultima posicao
 */
int converteDado(Personagem* p) {
	char tipo_dado[3];
	tipo_dado[0] = p->dado[1];
	tipo_dado[1] = p->dado[2];
	tipo_dado[2] = '\0';
	int dado = atoi(tipo_dado);
	return dado;
}

int novaRolagem(Personagem* p) {
	int valor_min = 1;
	int valor_max = converteDado(p);
	int rolagem = (rand()%(valor_max-valor_min+1))+(valor_min);
	return rolagem;
}

/* como iamos sobrescrever a iniciativa de qualquer forma,
 * nao fazia sentido zerar antes
 * fazer uma funçao na lista de personagens para zerar a iniciativa de todos os personagens
 */
int calcularIniciativa(Personagem* p) {
	int rolagem = novaRolagem(p);
	int nova_iniciativa = (p->nivel+rolagem);
	p->iniciativa = nova_iniciativa;
	return nova_iniciativa;
}

void printPersonagem(Personagem* p) {
	printf("Nome: %s;\nNivel: %d;\nDado: %s;\nIniciativa: %d.", p->nome, p->nivel, p->iniciativa);
}

int alterarDado(Personagem* p, int idDado) {
	printf("Você realmente deseja alterar o dado do personagem?\n");
	printf("Para confirmar, digite 1. Para cancelar, digite 0.");
	int c;
	scanf("%d", &c);
	if(c==1) {
		if(idDado>0 && idDado<=6) {
			switch(idDado) {
				case 1:
					strcpy(p->dado,"D04");
					break;
				case 2:
					strcpy(p->dado,"D06");
					break;
				case 3:
					strcpy(p->dado,"D08");
					break;
				case 4:
					strcpy(p->dado,"D10");
					break;
				case 5:
					strcpy(p->dado,"D12");
					break;
				case 6:
					strcpy(p->dado,"D20");
					break;
			}
			printf("Alteração realizada com sucesso.\n");
			return 1;
		} else {
            printf("ID de dado invalido.\n");
            return 0;
        }
	} else {
		printf("Nenhuma alteração realizada.\n");
		return -1;
	}
}
