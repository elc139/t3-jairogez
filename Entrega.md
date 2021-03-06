Nome: Jairo Ferreira Gez, Disciplina: ELC1039 - Programação Paralela
----

[Link para o programa desenvolvido](OpenMPDemoABC.cpp)

1- Schedule static com especificação do chunk

```
Chunk = 20 
CCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAA
A=20 B=20 C=20 

Chunk = 30
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
A=30 B=30 C=0 

Chunk = 50
BBBBBBBBBBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
A=50 B=10 C=0 
```

Schedule static sem especificação do chunk

```
CBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCC
A=20 B=20 C=20 

BCCCCCCCCCCCCCCCCCCCCAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBB
A=20 B=20 C=20 

ABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCAAAAAAAAAAAAAAAAAAA
A=20 B=20 C=20 
```

Ao especificarmos o tamanho do chunk, as iterações são distribuidas estaticamente às threads, de modo que pelo menos uma thread vai iterar "chunk vezes" pelo loop. Quando não especificamos o chunk, o compilador parece dividir o número de iterações igualmente entre as threads. 

2- Schedule dynamic com especificação do chunk

```
Chunk = 20
ACCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAA
A=20 B=20 C=20 

Chunk = 30
AAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAAAAA
A=30 B=30 C=0 

Chunk = 50
AAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
A=10 B=50 C=0 
```

Schedule dynamic sem especificação do chunk

```
ACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCAB
A=2 B=1 C=57 

AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABC
A=58 B=1 C=1 

BCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCBA
A=1 B=2 C=57 
```

Ao agendarmos dinamicamente, a única diferença percebida é que, quando não definimos um tamanho para o chunk, quase todas as execuções se dão em apenas uma thread.

3- Schedule guided com especificação do chunk

```
Chunk = 20
ACCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAA
A=20 B=20 C=20 

Chunk = 30 5
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
A=30 B=30 C=0 

Chunk = 50
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCC
A=50 B=0 C=10 
```

Schedule guided sem especificação do chunk

```
ACCCCCCCCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAA
A=20 B=14 C=26 

ABAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBAAAAAA
A=15 B=14 C=31 

CBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCAAAAAAAAA
A=9 B=31 C=20 
```

Similar à schedule dynamic, só que os tamanhos de chunk são alterados conforme o programa executa, a fim de dividir o trabalho entre as threads.

4- Schedule runtime

```
ACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCAB
A=2 B=1 C=57 

ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAC
A=2 B=57 C=1 

ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBCA
A=2 B=57 C=1 
```

O escalonamento se dá de forma dinâmica e a execução do programa é quase serial.

5- Schedule auto

```
BCCCCCCCCCCCCCCCCCCCCAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBB
A=20 B=20 C=20 

ABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCAAAAAAAAAAAAAAAAAAA
A=20 B=20 C=20 

ACCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAA
A=20 B=20 C=20 
```

O escalonamento fica a cargo do compilador, que parece dividir a carga igualmente entre as threads.

6- Um ou mais casos sem exclusão mútua, para apresentar saídas incorretas.

```
Schedule static com especificação do chunk de tamanho 20
BABCABCABCABACABCABCABACABCABCABACABCABACABCABCABC-CBCBCBCB-
A=19 B=20 C=19 

Schedule static com especificação do chunk de tamanho 30
ABABABABABABABABABABABABABABABABABABABABABABABABABABABABABA-
A=30 B=29 C=0 

Schedule runtime:
BABCABCAABCABCABCAABCABCAABCABCABCAABCABCABACABCACBACBACBA--
A=23 B=18 C=17 

CBACBACBACBACBACBABCABCBACBACBACBACBACBACBABCBACBACBACBACA--
A=19 B=20 C=19 

CACBABCAACBACBACBAABCABCAABCABCABCAABCABCAABCABCABCABCBACB--
A=22 B=18 C=18 
```

Referências:

http://www.inf.ufsc.br/~bosco.sobral/ensino/ine5645/OpenMP_Dynamic_Scheduling.pdf

http://www.inf.ufrgs.br/~nicolas/pdf/openmp.pdf

