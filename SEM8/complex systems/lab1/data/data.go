package data

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"strings"
)

type Matrix [][]float64
type Vector []float64

const MIN = 1.01
const MAX = 100.98

func GenerateVector(size int, random bool) Vector {
	vec := make(Vector, size)
	for i := range size {
		if random {
			vec[i] = MIN + rand.Float64()*(MAX-MIN)
		} else {
			vec[i] = 1
		}
	}
	return vec
}

func GenerateMatrix(size int, random bool) Matrix {
	mtx := make(Matrix, size)
	for i := range mtx {
		mtx[i] = make(Vector, size)
		for j := range mtx[i] {
			if random {
				mtx[i][j] = MIN + rand.Float64()*(MAX-MIN)
			} else {
				mtx[i][j] = 1
			}
		}
	}
	return mtx
}

func OpenOrCreateFile(path string) (*os.File, error) {
	return os.OpenFile(path, os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0644)
}

func WriteVecToFile(path string, vec Vector) error {
	file, err := OpenOrCreateFile(path)
	if err != nil {
		return err
	}
	defer file.Close()

	strVec := make([]string, len(vec))
	for i, num := range vec {
		strVec[i] = fmt.Sprintf("%f", num)
	}

	line := strings.Join(strVec, " ") + "\n\n"
	_, err = file.WriteString(line)
	return err
}

func WriteMtxToFile(path string, mtx Matrix) error {
	file, err := OpenOrCreateFile(path)
	if err != nil {
		return err
	}
	defer file.Close()

	for _, row := range mtx {
		strRow := make([]string, len(row))
		for j, num := range row {
			strRow[j] = fmt.Sprintf("%f", num)
		}

		line := strings.Join(strRow, " ") + "\n"
		_, err = file.WriteString(line)
		if err != nil {
			return err
		}
	}

	_, err = file.WriteString("\n")
	return err
}

func ReadDataFromFile(path string) ([]Matrix, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanLines)

	var matrices []Matrix
	var currentData Matrix

	for scanner.Scan() {
		line := scanner.Text()

		if line == "" {
			if len(currentData) > 0 {
				matrices = append(matrices, currentData)
				currentData = nil
			}
		} else {
			var row Vector
			values := strings.Fields(line)
			for _, value := range values {
				num, err := strconv.ParseFloat(value, 64)
				if err != nil {
					return nil, err
				}
				row = append(row, num)
			}
			currentData = append(currentData, row)
		}
	}

	if len(currentData) > 0 {
		matrices = append(matrices, currentData)
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return matrices, nil
}
