package main

import (
	"bufio"
	"log"
	"os"
	"strconv"
	"strings"
)

func readInput(inputFileName string) (int, []int, [][]string) {
	// Create a scanner for input file
	file, err := os.Open(inputFileName)
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	// Append scanned input to an array
	var inputArr []string
	for scanner.Scan() {
		inputArr = append(inputArr, scanner.Text())
	}

	// Convert number of generations to an int
	generations, err := strconv.Atoi(inputArr[0])
	if err != nil {
		log.Fatal(err)
	}

	// Append dimensions of field to an int array
	dimString := strings.Split(inputArr[1], " ")
	var dimensions []int

	for i, v := range dimString {
		if i > 1 {
			log.Fatal("Too many arguments for field dimensions")
		}
		dim, err := strconv.Atoi(v)
		if err != nil {
			log.Fatal(err)
		}
		dimensions = append(dimensions, dim)
	}

	// Create a slice with 0-th generation of field from input
	lenOfMtx := len(inputArr) - 2
	if lenOfMtx != dimensions[1] {
		log.Fatal("Length of matrix doesn't match given dimensions")
	}
	field0 := make([][]string, lenOfMtx)

	for i := 0; i < lenOfMtx; i++ {
		subField := strings.Split(inputArr[i+2], "")
		if len(subField) != dimensions[0] {
			log.Fatal("Width of matrix doesn't match given dimensions")
		}
		field0[i] = append(field0[i], subField...)
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
	return generations, dimensions, field0
}

func writeOutput(field [][]string) {
	file, err := os.Create("output.txt")
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	writer := bufio.NewWriter(file)

	for i := range field {
		for _, v2 := range field[i] {
			_, err := writer.WriteString(v2)
			if err != nil {
				log.Fatal(err)
			}
		}
		_, err := writer.WriteString("\n")
		if err != nil {
			log.Fatal(err)
		}
	}
	if err := writer.Flush(); err != nil {
		log.Fatal(err)
	}
}

// Check around a cell
func checkAround(i int, j int, field [][]string) string {
	dead := "."
	alive := "x"
	aliveCount := 0
	stateOfCell := field[i][j]
	var statesSlice []string
	lenF := len(field)
	widF := len(field[i])

	for n := 0; n < 3; n++ {
		for m := 0; m < 3; m++ {
			coordX := i - 1 + n
			coordY := j - 1 + m
			if coordX < 0 {
				coordX += lenF
			}
			if coordX > lenF-1 {
				coordX -= lenF
			}
			if coordY < 0 {
				coordY += widF
			}
			if coordY > widF-1 {
				coordY -= widF
			}
			statesSlice = append(statesSlice, field[coordX][coordY])
		}
	}
	for _, v := range statesSlice {
		if v == "x" {
			aliveCount++
		}
	}

	// if dead and 3 alive in radius, then alive
	// if alive and 2-3 alive neighbours, then alive
	// if alive and < 2 or > 3 neighbours, then dead
	if stateOfCell == alive {
		aliveCount = aliveCount - 1
		if aliveCount > 3 || aliveCount < 2 {
			return dead
		}
		if aliveCount == 2 || aliveCount == 3 {
			return alive
		}
	}
	if stateOfCell == dead && aliveCount == 3 {
		return alive
	} else {
		return dead
	}
}

func gameOfLife(field0 [][]string, gens int, dims []int) [][]string {
	columns := dims[0]
	rows := dims[1]

	endField := field0
	for i := 0; i < gens; i++ {
		midField := make([][]string, rows)
		for n := range endField {
			midField[n] = make([]string, 0, columns)
			var subField []string
			for m := range endField[n] {
				subField = append(subField, checkAround(n, m, endField))
			}
			midField[n] = append(midField[n], subField...)

		}
		endField = midField
		//Print each generation of the field:
		// fmt.Println("\nGeneration:", i+1)
		// for i := range endField {
		// 	fmt.Println(endField[i])
		// }
	}
	return endField
}

func main() {
	gens, dims, field0 := readInput("input.txt")

	//Print zero generation of the field:
	// fmt.Println("\nGeneration: 0 ")
	// for i := range field0 {
	// 	fmt.Println(field0[i])
	// }
	endField := gameOfLife(field0, gens, dims)

	writeOutput(endField)
}
