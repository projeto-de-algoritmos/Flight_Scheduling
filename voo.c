#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AIRPLANES 100
#define MAX_LINE_LENGTH 100

typedef struct {
    int id;
    char company_name[50];
    int arrival_time;
    int departure_time;
} Airplane;

int compara(const void *a, const void *b)
{

    Airplane *airplaneA = (Airplane *)a;
    Airplane *airplaneB = (Airplane *)b;

	return (airplaneA -> arrival_time - airplaneB ->arrival_time);

}

void scheduleFlights(Airplane flights[], int num_flights) {
    
    int tempoTotal = 0;

    int tempoInicial, tempoFinal;

     qsort(flights, num_flights, sizeof(Airplane), compara);

    for (int i = 1; i < num_flights; i++) {
       
        tempoInicial= tempoTotal;
        tempoFinal= tempoTotal+flights[i].arrival_time;

        tempoTotal = tempoTotal + flights[i].arrival_time;


            }
        }

int main() {
    FILE *inputFile, *outputFile;
    char inputFilename[] = "voos.csv";
    char outputFilename[] = "voos_agendados.csv";

    Airplane flights[MAX_AIRPLANES];
    char line[MAX_LINE_LENGTH];
    int num_flights = 0;

    // Abre o arquivo de entrada
    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    // Lê os dados do arquivo de entrada
    while (fgets(line, sizeof(line), inputFile) != NULL && num_flights < MAX_AIRPLANES) {
        char *token = strtok(line, ",");
        flights[num_flights].id = atoi(token);
        token = strtok(NULL, ",");
        strncpy(flights[num_flights].company_name, token, sizeof(flights[num_flights].company_name));
        token = strtok(NULL, ",");
        flights[num_flights].arrival_time = atoi(token);
        token = strtok(NULL, ",");
        flights[num_flights].departure_time = atoi(token);
        num_flights++;
    }

    fclose(inputFile);

    // Executa o agendamento dos voos
    scheduleFlights(flights, num_flights);

    // Abre o arquivo de saída
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    // Escreve os voos agendados no arquivo de saída
    for (int i = 0; i < num_flights; i++) {
        fprintf(outputFile, "%d,%s,%d,%d\n", flights[i].id, flights[i].company_name, flights[i].arrival_time, flights[i].departure_time);
    }

    fclose(outputFile);

    printf("Agendamento de voos concluído. Verifique o arquivo '%s' para os voos agendados.\n", outputFilename);

    return 0;
}
