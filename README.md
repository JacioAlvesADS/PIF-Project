# PIF-Project

# Ship Run 🚀

## Equipe
- Jácio Alves Neto Filho - [@JacioAlvesADS](https://github.com/JacioAlvesADS)
- Mateus Felipe Cavalcanti e Silva - [@Mateus8708](https://github.com/Mateus8708/Mateus8708.github.io)
- Pierre Costa Santiago de Oliveira Neto- [@PiierreC](https://github.com/PiierreC)
- João Miguel Freitas De C. Ferrão - [@Joao-Miguel-F](https://github.com/Joao-Miguel-F)
- Thaylane Paula Silva de Sousa - [@thaylanepaula](https://github.com/Thaylanepaula)

## Disciplina
**Programação Imperativa e Funcional - 2024.2**

## Instituição de Ensino
**CESAR School**

## Nome do Jogo
**ShipRun**

## Instruções de Compilação e Execução

### Requisitos
- **Compilador C** (gcc ou clang recomendado)
- **cli-lib** instalada (certifique-se de incluir a biblioteca e suas dependências no projeto)
- Sistema compatível com **Makefile** (Unix, Linux, ou MacOS)

### Compilação
No diretório raiz do projeto, execute o seguinte comando para compilar o jogo:

O executável será gerado na pasta `build/`.

### Execução
Após a compilação, para jogar, utilize o comando:
` gcc ./src/*.c -I./include -o cli-lib-example -lsqlite3`

E logo após
`./cli-lib-example`                       


### Limpeza
Para remover os arquivos gerados durante a compilação, execute:
`make clean`


## Descrição do Jogo
**SHIP RUN** é um jogo de corrida no terminal, onde o jogador controla uma nave espacial que deve desviar de meteoros que aparecem no caminho. O objetivo é sobreviver o maior tempo possível enquanto evita as colisões. A velocidade aumenta gradualmente à medida que o jogo avança, tornando o desafio mais intenso. A pontuação do jogador aumenta conforme ele desvia dos meteoros com sucesso, e o jogo termina quando a nave colide **10 vezes** com um meteoro.

### Regras do Jogo
1.	O jogador controla a nave espacial usando as teclas de direção A e D.
2.	O objetivo é evitar colidir com os meteoros que aparecem no espaço.
3.	A pontuação aumenta a cada segundo desviado com sucesso.
4.	O jogo termina quando a nave colide 10 vezes com um meteoro.

### Como Jogar
- Use as **teclas de direção A e D** para mover a nave para a esquerda e direita.
- Mantenha-se atento aos meteoros que aparecem no caminho.
- Aumente sua pontuação evitando colisões e sobreviva o maior tempo possível!

Boa sorte e divirta-se jogando **Ship Run**!
