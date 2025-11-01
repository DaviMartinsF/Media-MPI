//Davi Martins Figueiredo - 10374878
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

/**
 * @brief Cria um vetor de números aleatórios entre 0.0 e 1.0.
 *
 * @param num_elements O número de elementos a serem gerados.
 * @return float* Um ponteiro para o vetor alocado dinamicamente.
 */
float *create_random_numbers(int num_elements) {
    float *random_numbers = (float *)malloc(sizeof(float) * num_elements);
    for (int i = 0; i < num_elements; ++i) {
        random_numbers[i] = (rand() / (float)RAND_MAX); // número aleatório entre 0 e 1
    }
    return random_numbers;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Uso: mpirun -np <N_PROCESSOS> %s <N_ELEMENTOS_POR_PROCESSO>\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    int num_elems_local_array = atoi(argv[1]); // Converte o argumento para inteiro
    int rank, number_processes;
    float local_sum = 0;    // Soma dos elementos do processo atual
    float global_sum = 0;   // Soma total de todos os processos

    MPI_Init(NULL, NULL); // Inicializa o ambiente MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtém o rank do processo atual
    MPI_Comm_size(MPI_COMM_WORLD, &number_processes); // Obtém o total de processos

    // Gera números aleatórios únicos para cada processo (semente baseada no rank)
    srand(time(NULL) + rank); 
    float *random_numbers = create_random_numbers(num_elems_local_array);

    // Calcula a soma local dos elementos
    for (int i = 0; i < num_elems_local_array; ++i) {
        local_sum += random_numbers[i];
    }

    // Exibe a soma e média locais
    printf("[Processo %d] Soma local = %f, média local = %f\n", rank, local_sum,
           local_sum / num_elems_local_array);

    
    // Reduz as somas locais em uma soma global E distribui o resultado para TODOS os processos.
    MPI_Allreduce(&local_sum,     // Dado de envio (cada processo envia sua soma)
                  &global_sum,    // Buffer de recebimento (todos recebem a soma total)
                  1,              // Número de elementos a enviar/receber
                  MPI_FLOAT,      // Tipo do dado
                  MPI_SUM,        // Operação (soma)
                  MPI_COMM_WORLD); // Comunicador

    // Agora, todos os processos (não apenas o rank 0) têm a global_sum correta.
    // Todos os processos podem calcular a média global.
    float media_global = global_sum / (num_elems_local_array * number_processes);

    // Sincroniza os processos para garantir que as impressões locais
    // apareçam antes da impressão global.
    MPI_Barrier(MPI_COMM_WORLD);

    // O processo 0 exibe a média global
    if (rank == 0) {
        printf("--------------------------------------------------\n");
        printf("[Processo %d] Soma total = %f\n", rank, global_sum);
        printf("[Processo %d] Média global = %f\n", rank, media_global);
        printf("--------------------------------------------------\n");
    }

    free(random_numbers); // Libera a memória alocada

    MPI_Finalize(); 

    return 0;
}