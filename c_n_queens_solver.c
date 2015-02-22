#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} position_t;

typedef position_t* position_ptr_t;
typedef position_ptr_t* solution_ptr_t;
typedef solution_ptr_t* solution_ptr_ref_t;
typedef solution_ptr_t* solutions_ptr_t;
typedef solutions_ptr_t* solutions_ptr_ref_t;

void deleteSolutions(solutions_ptr_t solutions, int numberOfSolutions, int maxSizeOfSolution);
void deleteSolution(solution_ptr_t solution, int maxSizeOfSolution);
bool isValidPosition(solution_ptr_t nQueensPositions, int numberOfQueens, position_ptr_t newPosition);
bool copySolution(solution_ptr_t solution, solution_ptr_ref_t newSolution, int maxSizeOfSolution);
bool copyToSolutions(solutions_ptr_ref_t solutions, int *numberOfSolutions, solution_ptr_t newSolution, int maxSolutionSize);
bool solve( int nQueensSize, solutions_ptr_ref_t solutions, int *numberOfSolutions, solution_ptr_t currentSolution, int sizeOfCurrentSolution, int currentColumn);

void printUsageAndExit();
void displaySolutions( solutions_ptr_t solutions, int numberOfSolutions, int numberOfQueens) ;
void displayQueens();


int main( int argc, char *argv[]) {
    
    solution_ptr_t solution = NULL;
    solutions_ptr_t solutions = NULL;
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
    
    
    solution = (solution_ptr_t)malloc(sizeof(position_ptr_t) * sizeOfBoard);
    
    
    for(i=0; i < sizeOfBoard; i++) {
        solution[i] = NULL;
    }
    
    start = clock();
    solve( sizeOfBoard, &solutions, &numberOfSolutions, solution, 0, 0);
    end = clock();
    
    durationInMilliseconds = (end-start) * 1000 / CLOCKS_PER_SEC;
    
    
    printf("N-Queens Found %d Solutions in %.6fs on a %dx%d board.\n", numberOfSolutions, durationInMilliseconds/1000.0, sizeOfBoard, sizeOfBoard);
    
    if(displayQueens) {
        displaySolutions(solutions, numberOfSolutions, sizeOfBoard);
    }
    
    return 0;
}


void printUsageAndExit() {
    printf("usage: ./c_n_queens [-d] board_size\n");
    exit(1);
}

bool solve( int nQueensSize, solutions_ptr_ref_t solutions, int *numberOfSolutions, solution_ptr_t workingSolution, int sizeOfCurrentSolution, int currentColumn) {
    position_ptr_t newPosition = NULL;
    solution_ptr_t newPossibleSolution = NULL;
    int row = 0;
    
    if((currentColumn == nQueensSize) && (sizeOfCurrentSolution == nQueensSize)) {
        copyToSolutions(solutions, numberOfSolutions, workingSolution, nQueensSize);
        return true;
    }
    
    for(row = 0; row < nQueensSize; row++) {
        newPosition = (position_ptr_t) malloc(sizeof(position_t));
        newPosition->x = currentColumn;
        newPosition->y = row;
        
        if(isValidPosition(workingSolution, sizeOfCurrentSolution, newPosition)) {
            
            copySolution(workingSolution, &newPossibleSolution, nQueensSize);
            newPossibleSolution[sizeOfCurrentSolution] = newPosition;
 
            solve(nQueensSize, solutions, numberOfSolutions, newPossibleSolution, sizeOfCurrentSolution+1, currentColumn+1);
            
       
        } else {
            free(newPosition);
            newPosition = NULL;
        }
    }
    
    deleteSolution(workingSolution, nQueensSize);
    return true;
}



bool isValidPosition(solution_ptr_t nQueensPositions, int numberOfQueens, position_ptr_t newPosition) {
    int queenIndex = 0;
    int rowDifference = 0;
    int columnDifference = 0;
    
    for( queenIndex = 0; queenIndex < numberOfQueens; queenIndex++) {
        if( (nQueensPositions[queenIndex]->x == newPosition->x) || (nQueensPositions[queenIndex]->y == newPosition->y) ) {
            return false;
        }
        
        rowDifference = abs(newPosition->y - nQueensPositions[queenIndex]->y);
        columnDifference = abs(newPosition->x - nQueensPositions[queenIndex]->x);
        
        if( rowDifference == columnDifference ) {
            return false;
        }
    }
    
    return true;
}


bool copyToSolutions(solutions_ptr_ref_t solutions, int *numberOfSolutions, solution_ptr_t newSolution, int maxSolutionSize) {
    (*numberOfSolutions)+=1;
    
    if(*solutions == NULL) {
        *solutions = (solutions_ptr_t)malloc(sizeof(solutions_ptr_t));
    } else {
        *solutions = (solutions_ptr_t)realloc(*solutions, sizeof(solutions_ptr_t) * (*numberOfSolutions));
    }

    if(solutions == NULL) {
        return false;
    }
    solution_ptr_t copy = NULL;
    
    copySolution(newSolution, &copy, maxSolutionSize);
    
    (*solutions)[(*numberOfSolutions)-1] = copy;

    return true;
}


bool copySolution(solution_ptr_t solution, solution_ptr_ref_t newSolution, int maxSizeOfSolution) {
    int i = 0;
    
    *newSolution = (solution_ptr_t)malloc(sizeof(position_ptr_t) * maxSizeOfSolution);
    
    for(i=0; i < maxSizeOfSolution; i++) {
        if(solution[i] != NULL) {
            (*newSolution)[i] = (position_ptr_t)malloc((sizeof(position_ptr_t)));
            memcpy((*newSolution)[i], solution[i], sizeof(position_t));
        } else {
            (*newSolution)[i] = NULL;
        }
    }
    
    return true;
}

void deleteSolutions(solutions_ptr_t solutions, int numberOfSolutions, int maxSizeOfSolution) {

    int i = 0;
    for(i = 0; i < numberOfSolutions; i++) {
        deleteSolution(solutions[i], maxSizeOfSolution);
    }
    free(solutions);
    solutions = NULL;
}

void deleteSolution(solution_ptr_t solution, int maxSizeOfSolution) {
   
    int i = 0;
    for(i=0; i < maxSizeOfSolution; i++) {
        if(solution[i] != NULL) {
            free(solution[i]);
            solution[i] = NULL;
        } else {
            break;
        }
    }
    free(solution);
    solution = NULL;
}

void displaySolutions( solutions_ptr_t solutions, int numberOfSolutions, int numberOfQueens) {
    int i;
    
    for(i=0; i < numberOfSolutions; i++) {
        printf("Solution %d\n", i+1);
        displayQueens(solutions[i], numberOfQueens);
    }
    
}

void displayQueens(solution_ptr_t solution, int numberOfQueens) {
    int x, y, z;
    char out;
    
    for(y=0; y < numberOfQueens; y++) {
        for(x=0; x < numberOfQueens; x++) {
            out = '_';
            for(z=0; z < numberOfQueens; z++) {
                if((solution[z]->x == x) && (solution[z]->y == y)) {
                    out = 'Q';
                }
            }
            
            printf("%c ", out);
        }
        printf("\n");
    }
    
}
