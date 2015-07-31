#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int position_t;               /* the y-position of the queen */
typedef position_t* solution_t;       /* a solution is an array of positions */
typedef solution_t* solution_list_t;  /* a solution list is an array of solutions */

void deleteSolutions(solution_list_t solutions, int numberOfSolutions);
solution_t createSolution(int nQueenSize);
void deleteSolution(solution_t solution);
bool isValidPosition(solution_t nQueensPositions, int numberOfQueens);
bool copySolution(solution_t solution, solution_t *newSolution, int maxSizeOfSolution);
bool copyToSolutions(solution_list_t *solutions, int *numberOfSolutions, solution_t newSolution, int maxSolutionSize);
void solve( int nQueensSize, solution_list_t *solutions, int *numberOfSolutions, solution_t workingSolution, int currentColumn);

void printUsageAndExit();
void displaySolutions( solution_list_t solutions, int numberOfSolutions, int numberOfQueens) ;
void displayQueens();


int main( int argc, char *argv[]) {
    
    solution_list_t solutions = NULL;
    int numberOfSolutions = 0;
    
    clock_t start, end;
    unsigned long durationInMilliseconds;
    
    int i;
    int sizeOfBoard;
    bool displayQueens = false;
    
    if(argc == 2) {
        sizeOfBoard = atoi(argv[1]);
    } else if( argc == 3) {
        
        if(strcmp(argv[1], "-d") == 0) {
            sizeOfBoard = atoi(argv[2]);
            displayQueens = true;
        } else if(strcmp(argv[2], "-d") == 0) {
            sizeOfBoard = atoi(argv[1]);
            displayQueens = true;
        } else {
            printUsageAndExit();
        }
        
    } else {
        printUsageAndExit();
    }
    
    
    
    printf("%d\n", sizeOfBoard);
    solution_t working = createSolution(sizeOfBoard);  
    
    start = clock();
    solve( sizeOfBoard, &solutions, &numberOfSolutions, working, 0);
    end = clock();
    
    durationInMilliseconds = (end-start) * 1000 / CLOCKS_PER_SEC;
    
    
    printf("N-Queens Found %d Solutions in %.6fs on a %dx%d board.\n", numberOfSolutions, durationInMilliseconds/1000.0, sizeOfBoard, sizeOfBoard);
    
    if(displayQueens) {
        displaySolutions(solutions, numberOfSolutions, sizeOfBoard);
    }
    
    deleteSolutions(solutions,numberOfSolutions);
    deleteSolution(working);
    return 0;
}


void printUsageAndExit() {
    printf("usage: ./c_n_queens [-d] board_size\n");
    exit(1);
}

void solve( int nQueensSize, solution_list_t *solutions, int *numberOfSolutions, solution_t workingSolution, int currentColumn) {
    int row = 0;
    
    if(currentColumn == nQueensSize) {
        copyToSolutions(solutions, numberOfSolutions, workingSolution, nQueensSize);
        return;
    }

    for(row = 0; row < nQueensSize; row++) {
        workingSolution[currentColumn] = row;
        
        if(isValidPosition(workingSolution, currentColumn)) {
 
            solve(nQueensSize, solutions, numberOfSolutions, workingSolution, currentColumn+1);
            
        }
    }
    
    return;
}



bool isValidPosition(solution_t nQueensPositions, int numberOfQueens) {
    int queenIndex = 0;
    int rowDifference = 0;
    int columnDifference = 0;
    
    const position_t new_y = nQueensPositions[numberOfQueens];

    for( queenIndex = 0; queenIndex < numberOfQueens; queenIndex++) {
        if( nQueensPositions[queenIndex] == new_y) {
            return false;
        }
        
        rowDifference = abs(new_y - nQueensPositions[queenIndex]);
        columnDifference = abs(numberOfQueens - queenIndex);
        
        if( rowDifference == columnDifference ) {
            return false;
        }
    }
    
    return true;
}


bool copyToSolutions(solution_list_t *solutions, int *numberOfSolutions, solution_t newSolution, int maxSolutionSize) {
    const size_t CHUNK_SIZE = 10000;   /* how many to allocate each time we realloc */    

    if( (*numberOfSolutions % CHUNK_SIZE) == 0) {
        size_t numChunks = (*numberOfSolutions) / CHUNK_SIZE + 1;
        *solutions = (solution_list_t)realloc(*solutions, numChunks * CHUNK_SIZE * sizeof(solution_t));
    }  

    if(solutions == NULL) {
        return false;
    }

    solution_t copy = NULL;
    copySolution(newSolution, &copy, maxSolutionSize);
    
    (*solutions)[(*numberOfSolutions)] = copy;

    (*numberOfSolutions)+=1;
    return true;
}


bool copySolution(solution_t solution, solution_t *newSolution, int maxSizeOfSolution) {
    int i = 0;
    
    *newSolution = createSolution(maxSizeOfSolution);
    memcpy(*newSolution, solution, maxSizeOfSolution*sizeof(position_t) );
    return true;
}

void deleteSolutions(solution_list_t solutions, int numberOfSolutions) {

    int i = 0;
    for(i = 0; i < numberOfSolutions; i++) {
        deleteSolution(solutions[i]);
    }
    free(solutions);
    solutions = NULL;
}

solution_t createSolution(int nQueensSize) {
   return (solution_t)malloc(nQueensSize*sizeof(position_t));
}

void deleteSolution(solution_t solution) {
   free(solution);
} 

void displaySolutions( solution_list_t solutions, int numberOfSolutions, int numberOfQueens) {
    int i;
    
    for(i=0; i < numberOfSolutions; i++) {
        printf("Solution %d\n", i+1);
        displayQueens(solutions[i], numberOfQueens);
    }
    
}

void displayQueens(solution_t solution, int numberOfQueens) {
    int x, y, z;
    char out;
    
    for(y=0; y < numberOfQueens; y++) {
        for(x=0; x < numberOfQueens; x++) {
            putchar( (solution[x]==y)?'Q':'_' );
            putchar( ' ' );
        }
        putchar('\n');
    }
    
}
