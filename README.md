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