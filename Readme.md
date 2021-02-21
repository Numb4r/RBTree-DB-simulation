# Red-Black Tree Database Simulation
## Resumo
Esse projeto tenta simular uma database com o uso de uma [Red-Black Tree](https://en.wikipedia.org/wiki/Red-black_tree).



<!-- É é -->
## Construção
O software é escrito em C++ com o uso do recurso ***templates*** para a construção da árvore, proporcionando assim uma flexibilização no armazenamento dos dados.

Foi utilizado, para testes da estrutura, dados da University of Minnesota sobre filmes. Você pode ler a documentação da base de dados clicando [aqui](https://github.com/Numb4r/Recomendacao-Cache-LRU/blob/master/Doc.md)

## Objetivo

O objetivo desse projeto é criar um programa que tente simular uma database relacional simples, com vetores associativos para simular o conceito de ***"primary-key"*** de forma rudimentar. Para a construção desse programa foi utilizado a estrutura Red-Black Tree, uma Binary Search Tree balanceada. 

A Red-Black Tree foi usada já que, em caso de busca em dados desordenados, ela se sai mais eficiente que um array comum, possuindo melhor, pior e caso médio de ``O(Log n)``; enquanto o array ganha apenas no melhor caso que é ``O(1)`` em busca, e ela é mais eficiente que uma Binary Search Tree convencional já que ela é balanceada. 

Embora os dados da base de Minnesota estarem organizados, assim uma lista sendo a mais eficiente, nosso intuito é montar uma estrutura solida para receber qualquer dado. Para isso foi usado um recurso de linguagem chamado ***template***.

Com o ***template*** é possível especificar um tipo com que a estrutura trabalhe, evitando a necessidade da reescrita do código para tratar cada tipo.


Um exemplo de declaração da Red-Black Tree do tipo ``int``:
```
RBTree<int> tree;
```
Para conseguir montar uma árvore de um tipo específico, o tipo deve possuir os operadores:

- Igualdade (``==``)
- Diferença (``!=``)
- Maior que (``>``)
- Menor que (``<``)
- Stream insertion (``<<``)
      
Para sobrecarregar o operador de ***stream*** é necessário definir uma função ***friend*** para a classe:
```
//foo.hpp
#include <iostream>
struct foo{
    int bar;
    friend std::ostream &operator<<(std::ostream& os,const foo &f);
}
friend std::ostream &operator<<(std::ostream& os,const foo &f){
    os<<f.bar;
    return os;
}
//main.cpp
RBTree<foo> tree;
```


## Instalação

Para compilar esse programa é necessário ter o gcc >= 10.2.0 ou o clang >= 11.0.1.


### Compilação
```
$ git clone https://github.com/Numb4r/RBTree-DB-simulation.git RBDB
$ cd RBDB
$ make clean && make
```

Para compilar com o Clang, substitua no Makefile -g++ em CXX por -clang++

### Execução
Para executar esse programa é necessário baixar a base de dados da University of Minnesota. Você pode baixar clicando [aqui](https://files.grouplens.org/datasets/movielens/ml-1m.zip).

Extraia para a raiz do programa. A estrutura do projeto ficará assim:
```
📦RBDB
 ┣ 📂build
 ┣ 📂ml-1m
 ┃ ┣ 📜README
 ┃ ┣ 📜movies.dat
 ┃ ┣ 📜ratings.dat
 ┃ ┗ 📜users.dat
 ┣ 📂src
 ┃ ┣ 📜Database.cpp
 ┃ ┣ 📜Database.hpp
 ┃ ┣ 📜RBTree.cpp
 ┃ ┣ 📜RBTree.hpp
 ┃ ┗ 📜main.cpp
 ┣ 📜.gitignore
 ┣ 📜Makefile
 ┗ 📜Readme.md
 ```
Você pode retirar o arquivo users.dat já que ele não e necessário.
Depois disso você pode executar pelo comando:
```
$ make run
```
Lembre-se que a pasta **"ml-1m"** precisa estar na raiz do programa. Então se mover o executável ***app*** para outro lugar, você precisa mover a pasta **"ml-1m"** para o mesmo local.
   

## Funcionamento  

O algorítimo tem como objetivo uma simulação de uma database relacional de forma rudimentar. Para isso se utiliza da estrutura de árvore rubro-preta.

A estrutura da árvore rubro-preta é uma implementação da árvore binária de busca, mas seguindo certas regras:

- Todo nó possui uma cor, vermelho ou preta.
- A raiz é preta, independentemente.
- Todos as folhas nulas são pretas.
- Se um nó é vermelho, os seus dois filhos serão pretos.
- Todo caminho de um determinado nó para qualquer um de seus nós folha descendentes contem o mesmo numero de nós pretos.

Essas regras asseguram o ponto principal das árvores rubro-negra:
** O caminho mais longo da raiz a qualquer folha não seja mais que duas vezes o caminho mais curto da raiz a qualquer outra folha naquela árvore**

Com essas características, as árvores rubro-negras são consideras árvores binárias balanceadas.


### Simulação
Vamos simular a inserção de 8 itens com índices numéricos:
(P) = Preto.
(V) = Vermelho.
```
                                            7 (P)
```
```
                                            7 (P)
                                                \
                                                 10(V)

```
```
                                            10 (P)
                                            /    \
                                        07(V)    11(V)

```
```
                                            10 (P)
                                            /    \
                                        07(P)    11(P)
                                                   \
                                                    12(V) 

```
```
                                            10 (P)
                                            /    \
                                        07(P)    12(P)
                                                /   \
                                            11(V)    13(V) 

```
```
                                            10 (P)
                                            /    \
                                        07(P)    12(V)
                                                /   \
                                            11(P)    13(P) 
                                                        \
                                                         14(V)       
```
```
                                            10 (P)
                                            /    \
                                        07(P)    12(V)
                                                /   \
                                            11(P)    14(P) 
                                                    /   \
                                                13(V)   15(V)
                                                                   
```
```
                                              12 (P)
                                            /        \
                                        10(V)         14(V)
                                       /    \         /   \
                                    07(P)   11(P)  13(P)  15(P) 
                                                            \
                                                             16(V)
                                                                   
```
Como podemos perceber, além de usar cores nos nós para manipulação da árvore, ela também se faz uso de rotações simples.

O uso da estrutura no algoritmo será semelhante ao mostrado acima, já que todos os dados possuem id único de identificação. 



## Resultados e conclusões finais
Os resultados são os esperados da estrutura árvore binária balanceada. As considerações a seguir usam tempo como métrica a eficiência do algorítimo. Embora não seja o ideal, o tempo serve como um parâmetro razoável para um estudo do algorítimo. Para cada resultado, foram feitas 5 execuções e feito a média aritmética.


Em uma operação que executa 100 000 buscas aleatórias na árvore que armazena os filmes, com 3883 entradas, o tempo médio de execução do algorítimo é de 0.07s. Isso se da pelo fato que a busca ser da ordem de ``O(Log n)``, o que demostra a eficiência da estrutura Red-Black Tree nessa operação.

Na inserção dos usuários, com 6 040 entradas, foi feito uma verificação para que não ocorresse uma possível duplicata nas entradas. Isso não foi feito na inserção dos filmes, e serve apenas para fins de teste. A validação foi feita através de uma busca na árvore para verificar se o índice não esta presente. O resultado foi insatisfatório, com um tempo de execução médio de 8.66s. Caso não fosse feito a verificação, o tempo de execução médio seria de 3.04s. Com isso, se pode concluir que a melhor forma de evitar duplicatas é implementando diretamente na árvore, coisa que a estrutura base da Red Black Tree não faz.

O tempo médio total do algorítimo, com a inserção dos filme e usuários (usando a verificação e buscando todos os filmes que o usuário já assistiu) é de 1317.20s. Com isso, pode se dizer que, embora muito eficientes, árvores binárias não são bons substitutos para um banco de dados convencional. Mesmo que a verificação fosse implementada diretamente na árvore, o resultado deixa muito a desejar. Assim, a estrutura Red-Black Tree se mostrou muito eficiente que uma estrutura simples de array.

## Referências

- ⌨ [Wikipedia: Red-Black Tree](https://en.wikipedia.org/wiki/Red-black_tree)

- 📔[Cormen, Thomas H, et al. Introduction to Algorithms. 2009.](https://www.amazon.com/Introduction-Algorithms-3rd-MIT-Press/dp/0262033844/ref=sr_1_1?dchild=1&keywords=Introduction+to+Algorithms&qid=1613858932&sr=8-1)
