#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 9999
#define MAX_LENGHT 255 

int isinteger(char buffer[]) {
  buffer[strlen(buffer) - 1] = 0;
  int i = 0;
  int str_is_number = 1;

  while (i < strlen(buffer)) {
    if (!(buffer[i] >= '0' && buffer[i] <= '9')) {
      str_is_number = 0;
      break;
    }
    ++i;
  }

  if (str_is_number == 1) {
    return 1;
  }
  else {
    return 0;
  }
}

void floyd(int vertices, float matrix[vertices][vertices], int matrix2[vertices][vertices]) {
    int i, j, k;
    for (k = 0; k < vertices; k++) {
        for (i = 0; i < vertices; i++) {
            for (j = 0; j < vertices; j++) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    matrix2[i][j] = k + 1;            
                }
            }
        }
    }
}

void shortest_path(int len, int start, int end, int matrix[len][len]) {
  if (matrix[start-1][end-1] == INF) {
    printf("There is no path from one verticle to another\n");
    return;
  }
  else {
    printf("%d ", start);
    if (matrix[start-1][end-1] == 0) {
        printf("-> %d\n",end);
    }
    else {
      printf("-> ");
      shortest_path(len, matrix[start-1][end-1], end, matrix);    
    }
  }
}

int main() {
    FILE *file;
    file = fopen("course.txt", "r");

    float num;
    char ch;
    int len = 1;
    while ((ch = fgetc(file)) != '\n') {
        if (ch == ' ') {
            len++;
        }
    }

    float a;
    fseek(file,0, SEEK_SET);
    float matrix[len][len];
    for(int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            fscanf(file, "%f", &a);
            matrix[i][j] = a;
        }
    }

    printf("Given matrix:\n");  
    for (int i = 0; i < len; i++) {  
        for (int j = 0; j < len; j++) {  
          if (matrix[i][j] == INF) {
            printf("INF ");
            continue;
          }
          printf("%0.1f ", matrix[i][j]);  
        }  
        printf("\n");  
    }  
    printf("\n");

    int mat[len][len];
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len; j++) {
        if (matrix[i][j] == INF) {
            mat[i][j] = INF;
            continue;
        }
        mat[i][j] = 0;
      }
    }

    floyd(len, matrix, mat);
    printf("Matrix after using floyd's algorithm:\n");  
    for (int i = 0; i < len; i++) {  
        for (int j = 0; j < len; j++) {  
          if (matrix[i][j] == INF) {
            printf("INF ");
            continue;
          }
            printf("%0.1f ", matrix[i][j]);
        }  
        printf("\n");  
    }
    printf("\n");

    int verticle1,verticle2;
    while (1) {
      while (1) {
        char str_verticle1[MAX_LENGHT];
        printf("Enter the vertex from which you are looking for the shortest path(0 if you want to leave): ");
        fgets(str_verticle1, MAX_LENGHT, stdin);
        if (!isinteger(str_verticle1)) {
          printf("You've entered the wrong value. Please try again.\n");
          continue;
        }
        verticle1 = strtol(str_verticle1, NULL, 10);
        if ( verticle1 > len) {
          printf("The value of a vertex is greater than the number of vertices in the matrix. Please enter the value again.\n");
          continue;        
        }
        if (verticle1 == 0) {
          exit(1);
        }
        break;
      }

      while (1) {
      char str_verticle2[MAX_LENGHT];
      printf("Enter the vertex to which you are looking for the shortest path: ");
      fgets(str_verticle2, MAX_LENGHT, stdin);
      if (!isinteger(str_verticle2)) {
          printf("You've entered the wrong value. Please try again.\n");
          continue;
        }
      verticle2 = strtol(str_verticle2, NULL, 10);
      if (verticle2 > len) {
          printf("The value of a vertex is greater than the number of vertices in the matrix. Please enter the value again.\n");
          continue;        
        }
      if (verticle2 <= 0)  {
        printf("The value of a vertex is lower than the number of vertices in the matrix. Please enter the value again.\n");
        continue;
      } 
      break;
      }

      puts("");
      puts("Shortest path: ");
      shortest_path(len, verticle1, verticle2, mat);
      puts("");
    }
    fclose(file);
    return 0;  
    }  
