package main

import (
	"bufio"
	"log"
	"os"
	"reflect"
	"strings"
	"testing"
)

/* Test file:
3
8 5
.......x
.......x
........
........
.......x
*/

func TestReadInput(t *testing.T) {
	gens, dims, field0 := readInput("inputTest.txt")

	wantGens := 3
	if gens != wantGens {
		t.Errorf("readInput returned: %d generations; want %d", gens, wantGens)
	}

	wantDims := []int{8, 5}
	for i, v := range dims {
		if v != wantDims[i] {
			t.Errorf("readInput returned dimensions: %d; want %d", dims, wantDims)
		}
	}

	wantField := [][]string{
		{".", ".", ".", ".", ".", ".", ".", "x"},
		{".", ".", ".", ".", ".", ".", ".", "x"},
		{".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", "x"}}

	if !reflect.DeepEqual(field0, wantField) {
		t.Errorf("readInput returned field: \n%s;\n want: \n%s\n", field0, wantField)
	}
}

// not sure if i need this test tbh
func TestWriteOutput(t *testing.T) {
	wantOutput := [][]string{
		{"x", ".", ".", ".", ".", ".", "x", "x"},
		{".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", "."}}

	writeOutput(wantOutput)

	file, err := os.Open("output.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)

	var inputArr []string
	for scanner.Scan() {
		inputArr = append(inputArr, scanner.Text())
	}

	gotOutput := make([][]string, len(inputArr))
	for i := 0; i < len(inputArr); i++ {
		subField := strings.Split(inputArr[i], "")
		gotOutput[i] = append(gotOutput[i], subField...)
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
	if !reflect.DeepEqual(gotOutput, wantOutput) {
		t.Errorf("readInput returned field: \n%s;\n want: \n%s\n", gotOutput, wantOutput)
	}
}

func TestCheckAround(t *testing.T) {
	field := [][]string{
		{".", ".", ".", ".", ".", ".", ".", "x"},
		{".", ".", ".", ".", ".", ".", ".", "x"},
		{".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", "x"}}

	gotstate := checkAround(4, 7, field)
	wantState := "."

	if gotstate != wantState {
		t.Errorf("checkAround returned state: ( %s ); want: ( %s )", gotstate, wantState)
	}
}

func TestGameOfLife(t *testing.T) {
	gens, dims, field0 := readInput("inputTest.txt")

	gotField := gameOfLife(field0, gens, dims)

	wantField := [][]string{
		{"x", ".", ".", ".", ".", ".", "x", "x"},
		{".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", "."}}

	if !reflect.DeepEqual(gotField, wantField) {
		t.Errorf("gameOfLife returned field: \n%s;\n want: \n%s\n", gotField, wantField)
	}
}
