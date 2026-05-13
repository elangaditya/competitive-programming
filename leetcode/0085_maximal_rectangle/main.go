package main

import "fmt"

type pair struct {
	top, left uint8
}

func maximalRectangle(matrix [][]byte) int {
	printMatrix(matrix)
	maxArea := 0
	my := len(matrix)
	mx := len(matrix[0])

	matrixMap := make([][]pair, my+1)
	matrixMap[0] = make([]pair, mx+1)
	// get dimension of matrix
	for i, row := range matrix {
		matrixMap[i+1] = make([]pair, mx+1)
		for j, x := range row {
			if x == '0' {
				matrixMap[i+1][j+1] = pair{top: 0, left: 0}
				continue
			}

			adjTop := matrixMap[i][j+1]
			adjLeft := matrixMap[i+1][j]
			adjDiag := matrixMap[i][j]
			top := min(adjDiag.top, adjTop.top) + 1
			left := min(adjDiag.left, adjLeft.left) + 1
			matrixMap[i+1][j+1] = pair{top: top, left: left}

			fmt.Println(top, left)
			area := int(top) * int(left)
			maxArea = max(area, maxArea)
		}
	}

	printMatrixMap(matrixMap)

	return maxArea
}

func printMatrixMap(arr [][]pair) {
	for _, row := range arr {
		for _, v := range row {
			fmt.Printf("%d-%d\t", v.left, v.top)
		}
		fmt.Println("")
	}
}

func printMatrix(arr [][]byte) {
	for _, row := range arr {
		for _, v := range row {
			fmt.Printf("%c\t", v)
		}
		fmt.Println("")
	}
}

func main() {
	input := [][]byte{{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}}
	fmt.Println(maximalRectangle(input))
}
