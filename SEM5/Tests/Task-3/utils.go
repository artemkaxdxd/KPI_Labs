package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func parse(f *Field, inputFileName string) {
	file, err := os.Open(inputFileName)
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	var inputArr []string
	for scanner.Scan() {
		inputArr = append(inputArr, scanner.Text())
	}

	// Append dimensions of field to an int array
	dimString := strings.Split(inputArr[0], " ")

	for i, v := range dimString {
		if i > 1 {
			log.Fatal("Too many arguments for field dimensions")
		}
		dim, err := strconv.Atoi(v)
		if err != nil {
			log.Fatal(err)
		}
		f.dimensions = append(f.dimensions, dim)
	}

	// Create a slice with field from input
	lenOfMtx := len(inputArr) - 1
	if lenOfMtx != f.dimensions[0] {
		log.Fatal("Length of matrix doesn't match given dimensions")
	}

	piece := "p"
	land := "#"

	for i := 0; i < lenOfMtx; i++ {
		subField := strings.Split(inputArr[i+1], "")
		if len(subField) != f.dimensions[1] {
			log.Fatal("Width of matrix doesn't match given dimensions")
		}
		for j, v := range subField {
			//fmt.Println(i, j, v)
			if v == piece {
				f.pieces = append(f.pieces, Point{i, j})
			}
			if v == land {
				f.landscape = append(f.landscape, Point{i, j})
			}
		}
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}

func printField(f Field) {
	rows := f.dimensions[0]
	cols := f.dimensions[1]

	finalField := make([][]string, rows)

	for i := 0; i < rows; i++ {
		finalField[i] = make([]string, 0, cols)
		var subField []string

		for j := 0; j < cols; j++ {
			subField = append(subField, ".")

			tempPoint := Point{i, j}

			for _, v := range f.landscape {
				if tempPoint == v {
					subField[j] = "#"
				}
			}

			for _, v := range f.pieces {
				if tempPoint == v {
					subField[j] = "p"
				}
			}
		}
		finalField[i] = append(finalField[i], subField...)
	}

	for _, v1 := range finalField {
		fmt.Println(v1)
	}
}
