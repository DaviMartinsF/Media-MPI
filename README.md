# Média Global com MPI

Este é um projeto acadêmico para a disciplina de Computação Distribuída. O objetivo é implementar um programa em C com MPI (Message Passing Interface) que calcula a soma e a média global de um conjunto de números aleatórios distribuídos entre múltiplos processos.

## 🚀 Funcionalidades

O programa executa os seguintes passos:

1.  **Inicialização:** Inicializa o ambiente MPI e determina o *rank* (ID) de cada processo e o número total de processos.
2.  **Geração de Dados:** Cada processo gera um vetor local com `N` números aleatórios (entre 0.0 e 1.0).
3.  **Cálculo Local:** Cada processo calcula a soma e a média dos *seus próprios* números aleatórios e os exibe no console.
4.  **Cálculo Global:** A função `MPI_Allreduce` é usada para coletar a soma local de cada processo, somá-las e distribuir o resultado (`global_sum`) de volta para **todos** os processos.
5.  **Resultado Final:** O processo de `rank 0` é responsável por calcular a média global final e exibi-la.

## 🛠️ Tecnologias Utilizadas

* **Linguagem C**
* **MPI** (Message Passing Interface)
* **Open MPI** (como implementação de referência)

## 📦 Pré-requisitos

Antes de começar, você precisará ter uma implementação do MPI instalada. Para sistemas baseados em Debian/Ubuntu, você pode instalar o Open MPI com:

```bash
sudo apt update
sudo apt install openmpi-bin libopenmpi-dev
```

## 🛠️ Como Compilar e Executar
1. **Compilaçao** Use o compilador mpicc, que é um "wrapper" para o gcc e linka automaticamente as bibliotecas MPI.
```bash
# Onde:
# -o media_global  -> Define o nome do arquivo executável
# MediaMPI.c       -> O seu arquivo de código-fonte

mpicc -o media_global MediaMPI.c

```

2. **Execução**
* `-np <N>`: O número de processos que você deseja usar.
* `./media_global`: O nome do seu executável.
* `<M>`: O número de elementos aleatórios que cada processo deve gerar (o argumento argv[1] esperado pelo main).

**Formato do comando:**
```bash
mpirun -np `<N_PROCESSOS> ./media_global <N_ELEMENTOS_POR_PROCESSO>

```
**Exemplo Pratico**
```bash
mpirun -np 4 ./media_global 10000

```
**Exemplo de Saida**
```bash
[Processo 1] Soma local = 4987.123456, média local = 0.498712
[Processo 3] Soma local = 5012.456789, média local = 0.501246
[Processo 0] Soma local = 4999.987654, média local = 0.499999
[Processo 2] Soma local = 5001.654321, média local = 0.500165
--------------------------------------------------
[Processo 0] Soma total = 20001.222220
[Processo 0] Média global = 0.500031
--------------------------------------------------

```

## ✒️ Como Compilar e Executar
* Davi Martins Figueiredo - 10374878
