package main

import (
	"fmt"
	"lab1/data"
	"os"
	"slices"
	"sync"
	"time"
)

// Task:
// МG = МВ*MM + МС*МO - MM
// A = D*MC - min(D)*B
const SIZE = 1000
const THREAD_COUNT = 2
const PART_SIZE = SIZE / THREAD_COUNT

const RANDOM = true
const FILE_PATH = "data.txt"
const FILE_PATH_RES = "results.txt"

type Data struct {
	MB data.Matrix
	MM data.Matrix
	MC data.Matrix
	MO data.Matrix
	D  data.Vector
	B  data.Vector
}

var InputData Data

type Results struct {
	MG data.Matrix
	A  data.Vector

	muMG sync.Mutex
	muA  sync.Mutex
}

func NewResults() *Results {
	MG := make(data.Matrix, SIZE)
	for i := range MG {
		MG[i] = make(data.Vector, SIZE)
	}
	return &Results{
		MG: MG,
		A:  make(data.Vector, SIZE),
	}
}

func main() {
	generateData(FILE_PATH, SIZE, RANDOM)
	readData()

	// task1()
	// task2()
	task3()

	defer os.Remove(FILE_PATH)
}

func generateData(path string, size int, random bool) {
	MB := data.GenerateMatrix(size, random)
	data.WriteMtxToFile(path, MB)

	MM := data.GenerateMatrix(size, random)
	data.WriteMtxToFile(path, MM)

	B := data.GenerateVector(size, random)
	data.WriteVecToFile(path, B)

	MC := data.GenerateMatrix(size, random)
	data.WriteMtxToFile(path, MC)

	MO := data.GenerateMatrix(size, random)
	data.WriteMtxToFile(path, MO)

	D := data.GenerateVector(size, random)
	data.WriteVecToFile(path, D)
}

func readData() {
	matrices, err := data.ReadDataFromFile(FILE_PATH)
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	for _, matrix := range matrices {

		if len(matrix) == 1 {
			vector := matrix[0]
			if len(InputData.B) == 0 {
				InputData.B = vector
			} else {
				InputData.D = vector
			}
		} else {
			switch {
			case len(InputData.MM) == 0:
				InputData.MM = matrix
			case len(InputData.MB) == 0:
				InputData.MB = matrix
			case len(InputData.MC) == 0:
				InputData.MC = matrix
			case len(InputData.MO) == 0:
				InputData.MO = matrix
			}
		}
	}
}

func task1() {
	startTime := time.Now()

	MG := calculateMG(InputData)
	data.WriteMtxToFile(FILE_PATH_RES, MG)
	fmt.Println("Matrix MG:")
	for _, row := range MG {
		fmt.Println(row)
	}

	A := calculateA(InputData)
	data.WriteVecToFile(FILE_PATH_RES, A)
	fmt.Println("Vector A: ", A)

	finishTime := time.Since(startTime)
	fmt.Println("First example (non-parallel) time: ", finishTime)
}

func calculateA(body Data) data.Vector {
	// A = D*MC - min(D)*B
	vec1 := data.MulVecAndMtx(body.D, body.MC)
	min := slices.Min(body.D)
	vec2 := data.MulVecAndScalar(body.B, min)
	A := data.SubVecs(vec1, vec2)
	return A
}

func calculateMG(body Data) data.Matrix {
	// МG = МВ*MM + МС*МO - MM
	mtx1 := data.MulMtxs(body.MB, body.MM)
	mtx2 := data.MulMtxs(body.MC, body.MO)
	part1 := data.SumMtxs(mtx1, mtx2)
	MG := data.SubMtxs(part1, body.MM)
	return MG
}

func task2() {
	startTime := time.Now()
	wg := sync.WaitGroup{}
	wg.Add(1)
	go func() {
		defer wg.Done()
		MG := concurrentCalculateMG(InputData)

		wgPrint := sync.WaitGroup{}
		wgPrint.Add(1)
		go func() {
			defer wgPrint.Done()
			data.WriteMtxToFile(FILE_PATH_RES, MG)
		}()

		fmt.Println("Matrix MG:")
		for _, row := range MG {
			fmt.Println(row)
		}
		wgPrint.Wait()
	}()

	A := concurrentCalculateA(InputData)

	wgPrint := sync.WaitGroup{}
	wgPrint.Add(1)
	go func() {
		defer wgPrint.Done()
		data.WriteVecToFile(FILE_PATH_RES, A)
	}()

	fmt.Println("Vector A: ", A)
	wgPrint.Wait()
	wg.Wait()
	finishTime := time.Since(startTime)

	fmt.Println("Second task (parallel) time: ", finishTime)
}

func concurrentCalculateA(body Data) data.Vector {
	// A = D*MC - min(D)*B
	var (
		vec1 data.Vector
		vec2 data.Vector
	)

	wg := sync.WaitGroup{}
	wg.Add(1)
	go func() {
		vec1 = data.MulVecAndMtx(body.D, body.MC)
		wg.Done()
	}()

	vec2 = data.MulVecAndScalar(body.B, slices.Min(body.D))

	wg.Wait()
	A := data.SubVecs(vec1, vec2)
	return A
}

func concurrentCalculateMG(body Data) data.Matrix {
	// МG = МВ*MM + МС*МO - MM
	var (
		mtx1 data.Matrix
		mtx2 data.Matrix
	)

	wg := sync.WaitGroup{}
	wg.Add(1)
	go func() {
		mtx1 = data.MulMtxs(body.MB, body.MM)
		wg.Done()
	}()

	mtx2 = data.MulMtxs(body.MC, body.MO)

	wg.Wait()
	part1 := data.SumMtxs(mtx1, mtx2)

	MG := data.SubMtxs(part1, body.MM)
	return MG
}

func task3() {
	results := NewResults()
	startTime := time.Now()

	var (
		wgA  sync.WaitGroup
		wgMG sync.WaitGroup
		wg   sync.WaitGroup
	)

	wg.Add(1)
	go func() {
		defer wg.Done()
		results.lockCalculateA(InputData, 0, PART_SIZE, &wgA)
		go results.lockCalculateA(InputData, PART_SIZE, SIZE, &wgA)
	}()

	results.lockCalculateMG(InputData, 0, PART_SIZE, &wgMG)
	go results.lockCalculateMG(InputData, PART_SIZE, SIZE, &wgMG)

	wg.Wait()
	finishTime := time.Since(startTime)
	fmt.Println("Third example (parallel) time: ", finishTime)
}

func (r *Results) lockCalculateA(body Data, start, end int, wg *sync.WaitGroup) {
	// A = D*MC - min(D)*B
	var (
		vec1 data.Vector
		vec2 data.Vector
	)

	wg.Add(1)
	go func() {
		defer wg.Done()
		vec1 = data.MulVecAndMtx(body.D, body.MC[start:end])
	}()

	vec2 = data.MulVecAndScalar(body.B, slices.Min(body.D))

	wg.Wait()
	vec3 := data.SubVecs(vec1, vec2)

	r.muA.Lock()
	r.A = data.SaveToSubVector(r.A, vec3, start, end)
	r.muA.Unlock()
}

func (r *Results) lockCalculateMG(body Data, start, end int, wg *sync.WaitGroup) {
	// МG = МВ*MM + МС*МO - MM
	var (
		mtx1 data.Matrix
		mtx2 data.Matrix
	)

	wg.Add(1)
	go func() {
		defer wg.Done()
		mtx1 = data.MulSubMtx(body.MB, body.MM, start, end, SIZE)
	}()

	mtx2 = data.MulMtxs(body.MC, body.MO)

	wg.Wait()
	part := data.SumMtxs(mtx1, mtx2)

	res := data.SubMtxs(part, body.MM)
	r.muMG.Lock()
	r.MG = data.SaveToSubMatrix(res, r.MG, start, end)
	r.muMG.Unlock()
}
