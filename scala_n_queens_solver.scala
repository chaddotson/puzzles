object ScalaNQueensSolver {

    def displayQueens(solution : List[Tuple2[Int,Int]]) = {
        var out: String = ""
        for(y <- 0 to solution.length-1) {
            for(x <- 0 to solution.length-1) {
                out = "_ "
                for( cord<-solution ) {
                    if ((cord._1 == x) && (cord._2 == y)) {
                        out = "Q "
                    }
                }
                print(out)
            }
            println()
        }
    }

    def validPosition(nQueenPositions: List[Tuple2[Int,Int]], newPosition: Tuple2[Int,Int]): Boolean = {
            
        for (exisingPosition <- nQueenPositions) {
            if((exisingPosition._2 == newPosition._2)|| (exisingPosition._1 == newPosition._1)) {
                return false
            }
            
            var rowDifference = (newPosition._2 - exisingPosition._2).abs
            var columnDifference = (newPosition._1 - exisingPosition._1).abs
            
            if(rowDifference == columnDifference) {
                return false
            }
        }
        
        return true
    }

    def solve(nQueensSize: Int, nQueenPositions: List[Tuple2[Int,Int]], currentColumn: Int) : List[List[Tuple2[Int,Int]]] = {
    
        if ((currentColumn == nQueensSize) && (nQueenPositions.length == nQueensSize)) {
            return List(nQueenPositions)
        }
    
        var solutions: List[List[Tuple2[Int,Int]]] = List()
        
        for( row <- 0 to nQueensSize-1) {
            var newPosition = (currentColumn, row)

            if(validPosition(nQueenPositions, newPosition)) {

                var newQueensPositions : List[Tuple2[Int,Int]] = nQueenPositions
                
                newQueensPositions = newQueensPositions ++ List(newPosition)
                
                var solution = solve(nQueensSize, newQueensPositions, currentColumn+1)

                if(solution.length != 0) {
                    solutions = solutions ++ solution
                }
            }
        }
        
        return solutions
    
    }

	def main( args: Array[String] ) {
        
        var boardSize: Int = args(0).toInt
        var displaySolutions: Boolean = false
        
        if((args.length == 2) && (args(1) =="-d")) {
            displaySolutions = true
        }
        
        var nQueenPositions: List[Tuple2[Int,Int]] = List[Tuple2[Int,Int]]()
        
        var startTime: Long = System.currentTimeMillis
        var solutions: List[List[Tuple2[Int,Int]]] = solve( boardSize, nQueenPositions, 0 )
        var endTime: Long = System.currentTimeMillis
                
        println("N-Queens Found " + solutions.length + " Solutions in " + (endTime-startTime)/1000.0 + "s on a " + boardSize+ "x" + boardSize + " board")
                
        if( displaySolutions ) {
            var i: Int = 1;
            for( solution<-solutions ) {
                println("Solution: " + i)
                displayQueens(solution)
                i=i+1
            }
        }
	}
}
