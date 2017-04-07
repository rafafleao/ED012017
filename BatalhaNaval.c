/*
Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Estrutura de Dados 1/2017
Alunos: Matheus Stauffer Viana de Oliveira e Rafael Frade Leão
Matricula: 16/0071852 e 15/0145527
Turma: B
Versão do compilador: gcc (SUSE Linux) 6.1.1 20160707 [gcc-6-branch revision 238088]
Copyright (C) 2016 Free Software Foundation, Inc.
Descricao: O programa a seguir é o melhor jogo de Batalha Naval que o leitor jogará na vida.
Foi baseado em uma matriz de structs, e é modularizado em diversas funções.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	int valor;
	int ocupado;	
}BN;

void GeraMatriz(BN mat[][10]){
	int i, j;

	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			mat[i][j].valor = 0;
			mat[i][j].ocupado = 0;
		}
	}
}

void Randomizar(BN mat[][10], int* blocupados){
	int i;
	int sementei, sementej, direcao;

	sementei = rand() % 10;
	/*Semente seria um valor aleatorio para uma coordenada x, que
	posteriormente serah preenchido por uma embarcaçao que tambem
	serah sorteada, com a variavel barco. Gerando uma coordenada
	aleatoria, a variavel direçao, tambem gerada aleatoriamente, 
	seria o parametro usado para dizer onde estah o resto da embar-
	caçao. EXEMPLO: semente i sorteia 9, semente j sorteia 5. O 
	ponto (9, 5) foi selecionado como referencia. barco sorteia 2,
	que significa submarino - 1 portal, 2 sub, 3 encouraçado e 
	4 porta-avioes. direcao sorteia 2, que significa que a outra parte
	do barco, no caso um sub, ficaria `a direita da coordenada
	de referencia, ou seja, ficaria no ponto (10, 5). Colocar testes
	para nao estourar a matriz - posicionar algo que nao caiba em
	determinado ponto da matriz com determinada direçao - alem de verificar
	se tal ponto jah estah ocupado, fazendo uso do parametro da
	struct.*/

	sementej = rand() % 10;
	/*Vale lembrar que, no caso de cada coordenada, os limites dos
	valores sorteados sao dados pelas dimensoes da matriz gerada.*/

	direcao = rand() % 4;
	/*0 - esquerda, 1 - direita, 2 - acima, 3 - abaixo.*/

	(*blocupados) = 0;

	for(i=0;i<4;i++){
		if(mat[sementei][sementej].ocupado == 1){
			sementei = rand() % 10;
			sementej = rand() % 10;
		}
		else{
			mat[sementei][sementej].valor = 1;
			mat[sementei][sementej].ocupado = 1;
			(*blocupados)++;
		}
	}
	/*Esse teste serah recorrente no codigo. A ideia eh verificar
	a condiçao da coordenada sorteada: se estiver ocupada, sorteia-se
	outra. Em caso contrario, atribui-se o valor do barco correspondente
	e modifica-se o parametro 'ocupado' da struct. Para cada direçao
	diferente, a condiçao do teste 'if' serah adaptada.*/

	for(i=0;i<3;i++){
		if(mat[sementei][sementej].ocupado == 1){
			sementei = rand() % 10;
			sementej = rand() % 10;
		}
		else{
			mat[sementei][sementej].valor = 2;
			mat[sementei][sementej].ocupado = 1;
			(*blocupados)++;
		}
		/*fim sub setado coord. de referencia*/
		if(direcao == 0){
			if(sementej-1 < 0){
				direcao = rand() % 4;
			}
			else{
				if(mat[sementei - 1][sementej].ocupado == 1){
					sementei = rand() % 10;
					sementej = rand() % 10;
				}
				else{
					mat[sementei - 1][sementej].valor = 2;
					mat[sementei - 1][sementej].ocupado = 1;
					(*blocupados)++;
				}
			}
		}/*fim sub setado direçao esquerda*/
		else{
			if(direcao == 1){
				if(sementej + 1 > 10){
					direcao = rand() % 4;
				}
				else{
					if(mat[sementei][sementej+1].ocupado == 1){
						sementei = rand() % 10;
						sementej = rand() % 10;
					}
					else{
						mat[sementei][sementej+1].valor = 2;
						mat[sementei][sementej+1].ocupado = 1;
						(*blocupados)++;
					}
				}
			}/*fim sub setado direçao direita*/
			else{
				if(direcao == 2){
					if(sementei - 1 < 0){
						direcao = rand() % 4;
					}
					else{
						if(mat[sementei-1][sementej].ocupado == 1){
							sementei = rand() % 10;
							sementej = rand() % 10;
						}
						else{
							mat[sementei-1][sementej].valor = 2;
							mat[sementei-1][sementej].ocupado = 1;
							(*blocupados)++;
						}
					}
				}/*fim sub setado direçao acima*/
				else{
					if(sementei + 1 > 10){
						direcao = rand() % 4;
					}
					else{
						if(mat[sementei+1][sementej].ocupado == 1){
							sementei = rand() % 10;
							sementej = rand() % 10;
						}
						else{
							mat[sementei+1][sementej].valor = 2;
							mat[sementei+1][sementej].ocupado = 1;
							(*blocupados)++;
						}
					}
				}/*fim sub setado direçao abaixo*/
			}
		}
	}/*fim condiçoes sub*/
	for(i=0;i<3;i++){
		if(mat[sementei][sementej].ocupado == 1){
			sementei = rand() % 10;
			sementej = rand() % 10;
		}
		else{
			switch(direcao){
				case 0:
					if(sementej - 2 < 0){
						break;
					}
					else{
						if(mat[sementei][sementej-1].ocupado == 1 || mat[sementei][sementej-2].ocupado == 1){
							/*No teste acima, se todas as coordenadas adjacentes necessarias
							para o posicionamento do barco estiverem ocupadas, sorteia-se uma
							nova coordenada de referencia.*/	
							sementei = rand() % 4;
							sementej = rand() % 4;
							break;
						}
						else{
							mat[sementei][sementej].valor = 3;
							mat[sementei][sementej-1].valor = 3;
							mat[sementei][sementej-2].valor = 3;
							mat[sementei][sementej].ocupado = 1;
							mat[sementei][sementej-1].ocupado = 1;
							mat[sementei][sementej-2].ocupado = 1;
							(*blocupados) = (*blocupados) + 3;
							break;
						}
					}
				/*fim encouraçado setado esquerda*/
				case 1:
					if(sementej + 2 > 10){
						break;
					}
					else{
						if(mat[sementei][sementej+1].ocupado == 1 || mat[sementei][sementej+2].ocupado == 1){
							sementei = rand() % 4;
							sementej = rand() % 4;
							break;
						}
						else{
							mat[sementei][sementej].valor = 3;
							mat[sementei][sementej+1].valor = 3;
							mat[sementei][sementej+2].valor = 3;
							mat[sementei][sementej].ocupado = 1;
							mat[sementei][sementej+1].ocupado = 1;
							mat[sementei][sementej+2].ocupado = 1;
							(*blocupados) = (*blocupados) + 3;
							break;
						}
					}
				/*fim encouraçado setado direita*/
				case 2:
					if(sementei - 2 < 0){
						break;
					}
					else{
						if(mat[sementei-1][sementej].ocupado == 1 || mat[sementei-2][sementej].ocupado == 1){
							sementei = rand() % 4;
							sementej = rand() % 4;
							break;
						}
						else{
							mat[sementei][sementej].valor = 3;
							mat[sementei-1][sementej].valor = 3;
							mat[sementei-2][sementej].valor = 3;
							mat[sementei][sementej].ocupado = 1;
							mat[sementei-1][sementej].ocupado = 1;
							mat[sementei-2][sementej].ocupado = 1;
							(*blocupados) = (*blocupados) + 3;
							break;
						}
					}
				/* fim encouraçado setado acima*/
				case 3:
					if(sementei + 2 > 10){
						break;
					}
					else{
						if(mat[sementei+1][sementej].ocupado == 1 || mat[sementei+2][sementej].ocupado == 1){
							sementei = rand() % 4;
							sementej = rand() % 4;
							break;
						}
						else{
							mat[sementei][sementej].valor = 3;
							mat[sementei+1][sementej].valor = 3;
							mat[sementei+2][sementej].valor = 3;
							mat[sementei][sementej].ocupado = 1;
							mat[sementei+1][sementej].ocupado = 1;
							mat[sementei+2][sementej].ocupado = 1;
							(*blocupados) = (*blocupados) + 3;
							break;
						}
					}
				/*fim encouraçado setado abaixo*/
			} /*Aqui estah estabelecida a condiçao para o nao estouro das
				dimensoes da matriz, bem como a disponibilidade - ocupado ou
				nao - de cada elemento da matriz. Foi feito um switch, que 
				economiza espaço e eh mais legivel do que uma cadeia de if's
				e else's. Primeiro testa-se a coord. de referencia. Se estiver
				ocupada, sorteia-se uma nova. Caso contrario, em pelo menos uma
				das direçoes validas, as coordenadas adjacentes devem estar
				vazias para o que barco possa ser posicionado.*/

		}
	}/*fim condiçoes encouraçado.*/
	for(i=0;i<2;i++){
		if(mat[sementei][sementej].ocupado == 1){
			sementei = rand() % 10;
			sementej = rand() % 10;
		}
		else{
			switch(direcao){
				case 0:
					if(sementej - 3 < 0){
						break;
					}
					else{
						if(mat[sementei][sementej-1].ocupado == 1 || mat[sementei][sementej-2].ocupado == 1 || mat[sementei][sementej-3].ocupado ==1){
							sementei = rand() % 10;
							sementej = rand() % 10;
							break;
						}
						else{
							mat[sementei][sementej].valor = 4;
							mat[sementei][sementej-1].valor = 4;
							mat[sementei][sementej-2].valor = 4;
							mat[sementei][sementej-3].valor = 4;
							mat[sementei][sementej].ocupado = 1;
							mat[sementei][sementej-1].ocupado = 1;
							mat[sementei][sementej-2].ocupado = 1;
							mat[sementei][sementej-3].ocupado = 1;
							(*blocupados) = (*blocupados) + 4;
							break;
						}
					}
				/*fim porta-avioes setado esquerda*/
				case 1:
					if(sementej + 3 > 10){
						break;
					}
					else{
						if(mat[sementei][sementej+1].ocupado == 1 || mat[sementei][sementej+2].ocupado == 1 || mat[sementei][sementej+3].ocupado == 1){
							sementei = rand() % 10;
							sementej = rand() % 10;
							break;
						}
						else{
							mat[sementei][sementej].valor = 4;
							mat[sementei][sementej+1].valor = 4;
							mat[sementei][sementej+2].valor = 4;
							mat[sementei][sementej+3].valor = 4;
							mat[sementei][sementej].ocupado = 1;
							mat[sementei][sementej+1].ocupado = 1;
							mat[sementei][sementej+2].ocupado = 1;
							mat[sementei][sementej+3].ocupado = 1;
							(*blocupados) = (*blocupados) + 4;
							break;
						}
					}
				/*fim porta-avioes setado direita*/
				case 2:
					if(sementei - 3 < 0){
						break;
					}
					else{
						if(mat[sementei-1][sementej].ocupado == 1 || mat[sementei-2][sementej].ocupado == 1 || mat[sementei-3][sementej].ocupado == 1){
							sementei = rand() % 10;
							sementej = rand() % 10;
							break;
						}
						else{
							mat[sementei][sementej].valor = 4;
							mat[sementei-1][sementej].valor = 4;
							mat[sementei-2][sementej].valor = 4;
							mat[sementei-3][sementej].valor = 4;
							mat[sementei][sementej].ocupado = 1;
							mat[sementei-1][sementej].ocupado = 1;
							mat[sementei-2][sementej].ocupado = 1;
							mat[sementei-3][sementej].ocupado = 1;
							(*blocupados) = (*blocupados) + 4;
							break;
						}
					}
				/*fim porta-avioes setado acima*/
				case 3:
					if(sementei + 3 > 10){
						break;
					}
					else{
						if(mat[sementei+1][sementej].ocupado == 1 || mat[sementei+2][sementej].ocupado == 1 || mat[sementei+3][sementej].ocupado == 1){
							sementei = rand() % 10;
							sementej = rand() % 10;
							break;
						}
						else{
							mat[sementei][sementej].valor = 4;
							mat[sementei+1][sementej].valor = 4;
							mat[sementei+2][sementej].valor = 4;
							mat[sementei+3][sementej].valor = 4;
							mat[sementei][sementej].ocupado = 1;
							mat[sementei+1][sementej].ocupado = 1;
							mat[sementei+2][sementej].ocupado = 1;
							mat[sementei+3][sementej].ocupado = 1;
							(*blocupados) = (*blocupados) + 4;
							break;
						}
					}
				/*fim porta-avioes setado abaixo*/
			}
		}
	}/*fim condiçoes porta-avioes*/	
			
}

void Pipoco(int* x, int* y){
	
	printf("Informe a coordenada x na qual deseja atirar: \n");
	scanf("%d", x);
	while((*x) < 1 || (*x) > 10){
		printf("Informe uma coordenada valida, isto eh, entre 1 e 10:\n");
		scanf("%d", x);
	}
	printf("Informe a coordenada y na qual deseja atirar: \n");
	scanf("%d", y);
	while((*y) < 1 || (*y) > 10){
		printf("Informe uma coordenada valida, isto eh, entre 1 e 10:\n");
		scanf("%d", y);
	}
}

void PearlHarbor(BN mat[][10], BN mat2[][10], int x, int y, int* blocupados1, int* blocupados2, int*contagua, int* contportal, int* contsub, int* contenc, int* contpv){
	
	printf("Shhhhhhhhhhhhhhiiiiiuuu...\n");
	getchar();
	if(mat[x][y].valor == 0){
		printf("Flop. Voce acertou! Em um peixe.\n");
		(*contagua)++;
		getchar();
	}
	else{
		if(mat[x][y].valor == 1){
			printf("Voce acertou em algo...\n");
			getchar();
			printf("Mas.. como?! O que aconteceu!\n");
			getchar();
			printf("Me parece ser um.. Portal!\n");
			printf("E pra onde foi o tiro?\n");
			(*contportal)++;
			(*blocupados2)--;
			mat2[x][y].ocupado = 0;
			getchar();
			printf("OH NO! Voltou na sua propria esquadra!\n");
			/*Aqui endereçamos as coordenadas para a outra matriz,
			e contamos o acerto no proprio tabuleiro de quem
			efetuou o disparo*/
			getchar();
		}
		else{
			if(mat[x][y].valor == 2){
				printf("O tiro entrou na agua!\n");
				getchar();
				printf("Espere, ouvi uma explosao!\n");
				printf("Voce acertou um submarino!\n");
				(*contsub)++;
				(*blocupados1)--;
				mat[x][y].ocupado = 0;
				getchar();
			}
			else{
				if(mat[x][y].valor == 3){
					printf("CABUM! Voce acertou em um encouraçado!\n");
					(*contenc)++;
					(*blocupados1)--;
					mat[x][y].ocupado = 0;
					getchar();
				}
				else{
					printf("POW! Voce acertou em um aviao!\n");
					getchar();
					printf("Quer dizer, em um porta-avioes!\n");
					(*contpv)++;
					(*blocupados1)--;
					mat[x][y].ocupado = 0;
					getchar();
				}
			}
		}
	}
}

void Estatisticas(BN mat[][10], BN mat2[][10], int contagua, int contportal, int contsub, int contenc, int contpv, int contagua2, int contportal2, int contsub2, int contenc2, int contpv2){
	int i, j;

	printf("\t\t\t\tESTATISTICAS DA RODADA\n");
	printf("Jogador 1:\n");
	printf("\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8 \t9 \t10\n");
	for(i=0;i<10;i++){
		printf("%d\n", i+1);
		for(j=0;j<10;j++){
			if(mat[i][j].valor == 0){
				printf("\t~");
			}
			else{
				if(mat[i][j].valor == 1 && mat[i][j].ocupado == 0){
					printf("\tP");
				}
				else{
					if(mat[i][j].valor == 1 && mat[i][j].ocupado == 1)
						printf("\t~");
				}
				if(mat[i][j].valor == 2 && mat[i][j].ocupado == 0){
					printf("\t$");
				}
				else{
					if(mat[i][j].valor == 2 && mat[i][j].ocupado == 1)
						printf("\t~");
				}
				if(mat[i][j].valor == 3 && mat[i][j].ocupado == 0){
					printf("\tE");
				}
				else{
					if(mat[i][j].valor == 3 && mat[i][j].ocupado == 1)
						printf("\t~");
				}
				if(mat[i][j].valor == 4 && mat[i][j].ocupado == 0){
					printf("\t@");
				}
				else{
					if(mat[i][j].valor == 4 && mat[i][j].ocupado == 1)
						printf("\t~");
				}
			}
		}
		printf("\n");
	}
	printf("Ate essa rodada, voce acertou %d Portal(is), %d parte(s) de Sub,\n", contportal, contsub);
	printf("%d parte(s) de encouraçado e %d parte(s) de Porta-Avioes,\n", contenc, contpv);
	printf("alem de ter assassinado %d peixe(s).\n", contagua);
	printf("Jogador 2:\n");
	printf("\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8 \t9 \t10\n");
	for(i=0;i<10;i++){
		printf("%d\n", i+1);
		for(j=0;j<10;j++){
			if(mat2[i][j].valor == 0){
				printf("\t~");
			}
			else{
				if(mat2[i][j].valor == 1 && mat2[i][j].ocupado == 0){
					printf("\tP");
				}
				else{
					if(mat2[i][j].valor == 1 && mat2[i][j].ocupado == 1)
						printf("\t~");
				}
				if(mat2[i][j].valor == 2 && mat2[i][j].ocupado == 0){
					printf("\t$");
				}
				else{
					if(mat2[i][j].valor == 2 && mat2[i][j].ocupado == 1)
						printf("\t~");
				}
				if(mat2[i][j].valor == 3 && mat2[i][j].ocupado == 0){
					printf("\tE");
				}
				else{
					if(mat2[i][j].valor == 3 && mat2[i][j].ocupado == 1)
						printf("\t~");
				}
				if(mat2[i][j].valor == 4 && mat2[i][j].ocupado == 0){
					printf("\t@");
				}
				else{
					if(mat2[i][j].valor == 4 && mat2[i][j].ocupado == 1)
						printf("\t~");
				}
			}
		}
		printf("\n");
	}
	printf("Ate essa rodada, voce acertou %d Portal(is), %d parte(s) de Sub,\n", contportal2, contsub2);
	printf("%d parte(s) de encouraçado e %d parte(s) de Porta-Avioes,\n", contenc2, contpv2);
	printf("alem de ter assassinado %d peixe(s).\n", contagua2);
}

int main(){
	int x, y, rodada;
	int blocupados1 = 0;
	int blocupados2 = 0;
	int contportal, contsub, contenc, contpv, contagua;
	int contportal2, contsub2, contenc2, contpv2, contagua2;
	BN mat1[10][10], mat2[10][10];
	int continuar;

	GeraMatriz(mat1);
	Randomizar(mat1, &blocupados1);
	GeraMatriz(mat2);
	Randomizar(mat2, &blocupados2);

	contagua = 0;
	contportal = 0;
	contsub = 0;
	contenc = 0;
	contpv = 0;
	contagua2 = 0;
	contportal2 = 0;
	contsub2 = 0;
	contenc2 = 0;
	contpv2 = 0;

	/*Bloco para correçao. OBS: declarar i e j na main.
	printf("Sua matriz eh:\n");
	for (i = 0; i < 10; ++i){
		for (j = 0; j < 10; ++j){
			printf("%d\t", mat1[i][j].valor);
		}
		printf("\n");
	}
	printf("Sua matriz eh:\n");
	for (i = 0; i < 10; ++i){
		for (j = 0; j < 10; ++j){
			printf("%d\t", mat2[i][j].valor);
		}
		printf("\n");
	}
	printf("%d\n", blocupados1);
	printf("%d\n", blocupados2);*/
	
	do{
		printf("\t\tBATALHA NAVAL!\n");
		printf("\n");
		printf("1.Jogar\n");
		printf("2.Como Jogar\n");
		printf("3.Sair\n");
		scanf("%d", &continuar);
		printf("\n");
		switch(continuar){
			case 1:	
				rodada = 1;
				do{
					printf("Rodada %d\n", rodada);
					Pipoco(&x, &y);
					srand(time(NULL));
					PearlHarbor(mat2, mat1, (x-1), (y-1), &blocupados1, &blocupados2, &contagua, &contportal, &contsub, &contenc, &contpv);
					Pipoco(&x, &y);
					srand(time(NULL));
					PearlHarbor(mat1, mat2, (x-1), (y-1), &blocupados2, &blocupados1, &contagua2, &contportal2, &contsub2, &contenc2, &contpv2);
					rodada++;
					Estatisticas(mat1, mat2, contagua, contportal, contsub, contenc, contpv, contagua2, contportal2, contsub2, contenc2, contpv2);
				}while(blocupados1 != 0 || blocupados2 != 0);
				if(blocupados2 == 0 && blocupados1 != 0)
					printf("Parabens Jogador 1! Voce venceu!\n");
				if(blocupados1 == 0 && blocupados2 != 0)
					printf("Parabens Jogador 2! Voce venceu!\n");
				printf("Deseja jogar novamente? Se sim, digite 1. Se nao, digite 3: \n");
				scanf("%d", &continuar);
				break;
			case 2:
				printf("Batalha naval eh um jogo muito bacana.\n");
				printf("Dois jogadores jogam atirando alternadamente\n");
				printf("em seus tabuleiros, nos quais podem haver\n");
				printf("Submarinos, Encouraçados e Porta-avioes. Tambem\n");
				printf("existem Portais, que endereçam o tiro dado por um\n");
				printf("jogador para seu proprio tabuleiro. Cada tiro\n");
				printf("eh dado digitando coordenadas x e y. A cada\n");
				printf("rodada, estatisticas sobre o andamento do jogo\n");
				printf("serao dadas. Bom divertimento!\n");
				getchar();
				getchar();
				break;
			case 3:
				break;
		}
	}while(continuar != 3);

	return 0;
}
