# Red-Black Tree Database Simulation
## Resumo
Esse projeto tenta simular uma database com o uso de uma [Red-Black Tree](https://en.wikipedia.org/wiki/Red-black_tree).

<!-- Para a documentação especifica da estrutura Red-Black Tree clique [aqui](#) -->

## Construção
O software e' escrito em C++ com o uso do recurso ***templates*** para a construção da arvore, proporcionando assim uma flexibilização no armazenamento dos dados.

Foram utilizado, para testes da estrutura, dados da University of Minnesota sobre filmes. Você pode ler a documentação da base de dados clicando [aqui](https://github.com/Numb4r/Recomendacao-Cache-LRU/blob/master/Doc.md)

## Objetivo

O objetivo desse projeto e' criar um programa que tente simular uma database relacional simples, com vetores associativos para simular o conceito de ***"primary-key"*** de forma rudimentar. Para a construção desse programa foi utilizado a estrutura Red-Black Tree, uma Binary Search Tree balanceada. 

A Red-Black Tree foi usada ja que, em caso de busca em dados desordenados, ela se sai mais eficiente que um array comum, possuindo melhor,pior e caso médio de ``O(Log n)``; enquanto o array ganha apenas no melhor caso que e' ``O(1)`` em busca, e ela e' mais eficiente que uma Binary Search Tree convencional ja que ela e' balanceada. 

Embora os dados da base de Minnesota estarem organizados, assim uma lista sendo a mais eficiente, nosso intuito e' montar uma estrutura solida para receber qualquer tipo de dado.Para isso foi usado um recurso da linguagem chamado ***template***.

Com o ***template*** e' possível especificar um tipo com que a  estrutura trabalhe, evitando a necessidade da reescrita do código para tratar cada tipo.


Um exemplo de declaração da Red-Black Tree do tipo ``int``:
```
RBTree<int> tree;
```
Para conseguir montar uma arvore de um tipo especifico, o tipo deve possuir os operadores:

- Igualdade (``==``)
- Diferença (``!=``)
- Maior que (``>``)
- Menor que (``<``)
- Stream insertion (``<<``)
      
Para sobrecarregar o operador de ***stream*** e' necessario definir uma funcao ***friend*** para a classe:
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

Para compilar esse programa e' necessário ter o gcc >= 10.2.0 ou o clang >= 11.0.1.


### Compilação
```
$ git clone https://github.com/Numb4r/RBTree-DB-simulation.git RBDB
$ cd RBDB
$ make clean && make
```

Para compilar com o Clang, substitua no Makefile -g++ em CXX por -clang++

### Execução
Para executar esse programa e' necessário baixar a base de dados da University of Minnesota. Você pode baixar clicando [aqui](https://files.grouplens.org/datasets/movielens/ml-1m.zip).

Extraia para a raiz do programa.A estrutura do projeto ficara' assim:
```
📦CriptoTranslate
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
 ┣ 📜RBTree.md
 ┗ 📜Readme.md
 ```
Você pode retirar o arquivo users.dat ja que ele nao e necessário.
Depois disso você pode executar pelo comando:
```
$ make run
```
Lembre-se que a pasta **"ml-1m"** precisa estar na raiz do programa.Então se mover o executável ***app*** para outro lugar, você precisa mover a pasta **"ml-1m"** para o mesmo local


## Resultados e conclusões finais
Os resultados sao os esperados da estrutura arvore binaria balanceada. As considerações a seguir usam tempo como métrica para medir a eficiência do algorítimo. Embora nao seja o ideal, o tempo serve como um parâmetro razoável para descrever o que ocorre com o algorítimo. Para cada resultado, foram feitos 5 execuções e tirado a media.


Em uma operação que executa 100000 buscas aleatórias na arvore que armazena os filmes, com 3883 entradas, o tempo médio de execução do algorítimo e' de 0.07s. Isso se da pelo fato que a busca ser da ordem de ``O(Log n)``, o que torna o algorítimo extremamente eficiente para buscas.

Na inserção dos usuários,com 6040 entradas, foi feito uma verificação para que nao ocorresse uma possível duplicata nas entradas. Isso nao foi feito na inserção dos filmes, e serve apenas para fins de teste. A validação foi feita através de uma busca na arvore para verificar se o índice nao esta presente. O resultado final foi insatisfatório, com um tempo execução médio de 7.54s. Caso nao fosse feito a verificação,o tempo de execução médio seria de 3.16s. Com isso,se pode concluir que a melhor forma de evitar duplicatas e' implementando diretamente na arvore, coisa que a estrutura base da Red Black Tree nao faz.

O tempo total do algoritimo, com a insercao dos filme e usuarios(usando a verificacao e buscando todos os filmes que o usuario ja assistiu) e' de 885.20s. Com isso, pode se dizer que, embora muito eficientes, arvores binarias nao sao bons substitutos para um banco de dados convencional. Mesmo que a verificacao fosse implementada diretamente na arvore, o resultado deixa muito a desejar. Mesmo assim, a estrutura Red-Black Tree se mostrou muito eficiente que uma estrutura simples de array.