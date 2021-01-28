/*
    Autor : Matheus Yasuo Ribeiro Utino

    Trata-se de um algoritmo genético para encontrar UMA raiz real de uma função de uma variável, ou seja, busca o zero da função. Essa pode ser uma boa estratégia caso seja uma função
    em que suas derivadas apresentam "problemas", como descontinuidade, inexistência, ou elevada desordem, em que algoritmos tradicionais, como o Newton-Raphson teria problema caso 
    a derivada fosse nula, dentre outros métodos que apresentariam "problemas" similares. 
    Para exemplificação foram utilizadas  funções para testar seu funcionamento, os valores foram comparados com os obtidos no WolframAlpha.

    Obs1 : Como trata-se de um algoritmo genético diversos parâmetros podem ser alterados para um maior eficiência ou precisão do algorimo, como por exemplo, o erro, tamanho da
    população, tamanho do intervalo analisado, taxa de mutação, o tipo de reprodução, o tipo de crossover, mutação, ademais. Como trata-se de um algoritmo inicial, não maximizaremos
    todos esses parâmetros, uma vez que se busca inicialmente apenas o aprendizado dos conceitos

    Obs2 : Por trata-se de um algoritmo genético em que não foi comprovado matemáticamente sua eficácia pode ser que algum caso muito complexo ou atípico possa acarretar na divergência
    do algoritmo (nos casos que eu testei todos funcionaram) 

    Obs3 : Sinta-se livre para ir modificando todos os parâmetros e ir vendo os efeitos que cada um deles causa, isso será de grande aprendizado. Bons estudos a todos!!!
*/

//Importando as bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Definindo o tamanho do intervalo(nesse caso será simétrico) [-TAMANHO_INTERVALO,TAMANHO_INTERVALO[
#define TAMANHO_INTERVALO 100

#define TAM_POP 100 //Definindo o tamanho da população (Quanto maior, mais rápida a convergência)

#define ERRO 0.0001 //Definindo o valor que o melhor indivíduo deve assumir (quanto menor melhor será a precisão do valor da raiz)

double TaxMut;   // 10.0 = 10%

double ind[TAM_POP]; //Represeta o gene (nesse caso a coordenada x)
double fit[TAM_POP]; //Representa o fitness do indivíduo
double maxfit ; //Guarda o fitness do melhor indivíduo
int indice_melhor; //Guarda o indíce do melhor indivíduo
int geracao; //O número de gerações até a convergência

void iniciaVariaveis(){ //Inicializa as variáveis
    TaxMut = 60.0;
    maxfit = 1.0;
    indice_melhor = 0;
    geracao = 0;
}
void iniciaPopulacao(){ //Inicializa o gene no intervalo [LIMITE_INFERIOR,LIMITE_SUPERIOR[
    for (int i = 0; i < TAM_POP; i++)
        ind[i] = (double) (rand() % TAMANHO_INTERVALO);
}

void avaliacao(int operacao){ //Calcula o fitness da população
    double x,y;
    for (int i = 0; i < TAM_POP; i++){
        x = ind[i];
        //Serão definidas 4 funções diferentes para teste
        if(operacao == 1)
            y= x * x - 5 * x + 3; //Raízes : x ≈ 0.697224362268005 e x ≈ 4.30277563773199
        else if(operacao == 2)
            y = tanh(x*x*x) + sin(2*x) + 10 - x * x; //Raízes : x ≈ -3.0350435109354462362 e x ≈ 3.3869152808038111123
        else if(operacao == 3)
            y = cos(2*x) + sin(x)*sin(x) -3 + sin(3*x) + x*x*x; //Raízes : x ≈ 1.5872051680933553068
        else if(operacao == 4)
		    y = sin(5*x) + 20 - x*x + 10*x - cos(0.5 * x); //Raízes : x ≈ -1.58006 e x ≈ 11.7084
        else if(operacao == 5)
            y = x * x - x - 2; //Raízes : x = -1 e x = 2
	    fit[i] = y;
    }
}

void elitismo() // Melhor reproduz com todos os indivíduos da população
{
    maxfit = fit[0];
    indice_melhor = 0;
    
    //Alterando a taxa de mutação
    if (geracao % 60 == 0) {
        TaxMut = TaxMut == 60 ? 2 : 60;
    }
    
    

    for (int i = 1; i < TAM_POP; i++){  // Busca pelo melhor individuo
        if (fabs(fit[i]) < fabs(maxfit)){
            maxfit = fabs(fit[i]);
            indice_melhor = i;
        }
    }

    for (int i = 0; i < TAM_POP; i++){
        if (i == indice_melhor) // Protege o melhor individuo
            continue;

        // Crossover (Faz a média aritmética entre o indivíduo i e do melhor)
        ind[i] = (ind[i] + ind[indice_melhor])/ 2.0;

        // Mutacao (Pequena alteração no gene para garantir variabilidade e convergência em caso de estagnação)
        ind[i] = ind[i] + ((double) (rand()%TAMANHO_INTERVALO)-TAMANHO_INTERVALO/2)*TaxMut/100.0f;
        //ind[i] += (double) (rand()%(TAMANHO_INTERVALO - 100));
		if(ind[i] > TAMANHO_INTERVALO)
			ind[i] -= TAMANHO_INTERVALO;
		if(ind[i] < 0)
			ind[i] += TAMANHO_INTERVALO;
    }
}


int main(int argc, char *argv[]){

	srand((unsigned)time(NULL)); //Inicializando com seed aleatória
    
    for(int i = 1; i < 6; i++){
        iniciaVariaveis();
        iniciaPopulacao(); 
        while(fabs(maxfit) > ERRO) {
            avaliacao(i);   
            elitismo();
            geracao++;
        }
        printf("A raiz eh %lf com fitness %lf na geracao %d\n",ind[indice_melhor],maxfit,geracao);
    }
    
	return 0;
}
