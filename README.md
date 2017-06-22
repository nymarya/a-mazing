# SNAZE

## Sobre o projeto

O jogo Snaze (Snake Trapped in a Maze) funciona.

## Como executar

|  Comando           | Descrição  |
| :-----| :-------------|
| ```$ make``` | Compilar | 
| ```$ ./snaze <arquivo>``` | Executar | 

Para que o arquivo seja válido, é necessário usar os símbolos listados abaixo:

| Símbolo     | Significado           |
| :------------- |:-------------|
| #      | Parede do labirinto |
| .      | Parede "invisível" do labirinto   | 
| *      | Posição inicial da cobra   |

Lembrando que um arquivo pode possuir mais de um labirinto e que os 
níveis que não possuem a posição da cobra são ignorados.

#### Exemplo de arquivo válido
```
5 7
#######
#     #
#*    #
#..   #
.###.##
8 10
##########
#       *#
#        #
#   .#.  #
#   .#.  #
#        #
#        #
####..####
```

## Possíveis erros


`Level(n): Dimensions out of range!!`

O nível *n* possui dimensões fora do intervalo permitido. Para se considerado como válido, o número de linhas 
deve estar entre 1 e 100. O mesmo vale para o número de colunas.<br/>


`Level(n): Invalid maze!!` 

O labirinto *n* não está configurado corretamente.<br/>


## Autoria

Desenvolvido por Gabriel Araújo de Souza (<gabriel_feg@hotmail.com >) e Mayra Dantas de Azevedo (<mayradazevedo@gmail.com >)

2017.1

&copy; IMD/UFRN 2017.
