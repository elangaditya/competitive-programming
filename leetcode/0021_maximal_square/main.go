package main

import "fmt"

func minZero(a int) int {
	if a < 0 {
		return 0
	}

	return a
}

func maximalSquare(matrix [][]byte) int {
	maxSquare := 0
	// get matrix dimensions
	x := len(matrix[0])
	y := len(matrix)

	fmt.Println(x, y)

	dp := make([][]int, y+1)
	dp[0] = make([]int, x+1)

	for i, row := range matrix {
		dp[i+1] = make([]int, x+1)
		for j, each := range row {
			if each == '0' {
				dp[i+1][j+1] = 0
				continue
			}

			size := min(dp[i][j], dp[i][j+1], dp[i+1][j]) + 1
			dp[i+1][j+1] = size

			maxSquare = max(maxSquare, size)
		}
	}

	return maxSquare * maxSquare
}

func main() {
	grid := [][]byte{
		{'1', '0', '1', '1', '1'},
		{'1', '0', '1', '1', '1'},
		{'1', '1', '1', '1', '1'},
		{'1', '1', '1', '1', '1'},
		{'1', '1', '1', '1', '1'},
		{'1', '1', '1', '1', '1'},
		{'1', '1', '1', '1', '1'},
		{'1', '0', '0', '1', '0'},
	}
	fmt.Println(maximalSquare(grid))
}
