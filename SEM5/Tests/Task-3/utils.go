package main

import (
	"bufio"
	"errors"
	"fmt"
	"io"
	"strconv"
	"strings"
)

// Injecting a dependency of reading file
func parse(r io.Reader, outOs output) (*Field, error) {
	var f = Field{}
	scanner := bufio.NewScanner(r)

	var inputArr []string
	for scanner.Scan() {
		inputArr = append(inputArr, scanner.Text())
	}

	// Append dimensions of field to an int array
	dimString := strings.Split(inputArr[0], " ")

	for i, v := range dimString {
		if i > 1 {
			return nil, errors.New("too many arguments for field dimensions")
		}
		dim, err := strconv.Atoi(v)
		if err != nil {
			return nil, err
		}
		f.dimensions = append(f.dimensions, dim)
	}

	// Create a slice with field from input
	lenOfMtx := len(inputArr) - 1
	if lenOfMtx != f.dimensions[0] {
		return nil, errors.New("length of matrix doesn't match given dimensions")
	}

	piece := "p"
	land := "#"

	for i := 0; i < lenOfMtx; i++ {
		subField := strings.Split(inputArr[i+1], "")
		if len(subField) != f.dimensions[1] {
			return nil, errors.New("width of matrix doesn't match given dimensions")
		}
		for j, v := range subField {
			if v == piece {
				f.pieces = append(f.pieces, Point{i, j})
			}
			if v == land {
				f.landscape = append(f.landscape, Point{i, j})
			}
		}
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return &f, nil
}

// Injecting a dependency of printing
func printField(w io.Writer, f Field) {
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
		for _, v2 := range v1 {
			// passing in the writer and the string of field
			fmt.Fprint(w, v2)
		}
		fmt.Fprint(w, "\n")
	}
}
