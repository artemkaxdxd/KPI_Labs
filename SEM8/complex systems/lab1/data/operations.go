package data

func MulMtxs(mtx1, mtx2 Matrix) Matrix {
	rows := len(mtx1)
	cols := len(mtx1[0])

	res := make(Matrix, rows)
	for i := range res {
		res[i] = make(Vector, cols)
		for j := range res[i] {
			var temp []float64
			for k := range rows {
				cur := mtx1[i][k] * mtx2[k][j]
				temp = append(temp, cur)
			}
			res[i][j] = SumByKahan(temp)
		}
	}
	return res
}

func MulVecAndMtx(vec Vector, mtx Matrix) Vector {
	rows := len(mtx)
	cols := len(mtx[0])

	res := make(Vector, cols)
	for i := range rows {
		var sum float64
		for j := range cols {
			cur := mtx[i][j] * vec[i]
			sum = SumByKahan([]float64{sum, cur})
		}
		res[i] = sum
	}
	return res
}

func MulVecAndScalar(vec Vector, scalar float64) Vector {
	res := make(Vector, len(vec))
	for i := range len(res) {
		res[i] = vec[i] * scalar
	}
	return res
}

func SumMtxs(mtx1, mtx2 Matrix) Matrix {
	rows := len(mtx1)
	cols := len(mtx1[0])

	res := make(Matrix, rows)
	for i := range res {
		res[i] = make(Vector, cols)
		for j := range res[i] {
			res[i][j] = mtx1[i][j] + mtx2[i][j]
		}
	}
	return res
}

func MulSubMtx(mtx1, mtx2 Matrix, start, end, size int) Matrix {
	res := make(Matrix, size)
	for i := range res {
		res[i] = make(Vector, end-start)
		x := 0
		for j := start; j < end; j++ {
			var temp []float64
			for k := 0; k < size; k++ {
				cur := mtx1[i][k] * mtx2[k][j]
				temp = append(temp, cur)
			}
			res[i][x] = SumByKahan(temp)
			x++
		}
	}

	return res
}

func SubMtxs(mtx1, mtx2 Matrix) Matrix {
	rows := len(mtx1)
	cols := len(mtx1[0])

	res := make(Matrix, rows)
	for i := range res {
		res[i] = make(Vector, cols)
		for j := range res[i] {
			res[i][j] = mtx1[i][j] - mtx2[i][j]
		}
	}
	return res
}

func SubVecs(vec1, vec2 Vector) Vector {
	res := make(Vector, len(vec1))
	for i := range res {
		res[i] = vec1[i] - vec2[i]
	}
	return res
}

func SumByKahan(vec Vector) float64 {
	var sum float64
	var x float64
	for i := range len(vec) {
		y := vec[i] - x
		z := sum + y
		x = (z - sum) - y
		sum = z
	}
	return sum
}

func SaveToSubVector(A, B Vector, start, end int) Vector {
	index := 0
	for i := start; i < end; i++ {
		A[i] = B[index]
		index++
	}
	return A
}

func SaveToSubMatrix(fromMtx, toMtx Matrix, start, end int) Matrix {
	for i := 0; i < len(fromMtx); i++ {
		k := 0
		for j := start; j < end; j++ {
			toMtx[i][j] = fromMtx[i][k]
			k++
		}
	}
	return toMtx
}
