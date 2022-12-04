package main

import "fmt"

type Field struct {
	dimensions []int
	pieces     []point
	landscape  []point
}

func main() {
	tetris := Field{}
	tetris.Parse("input.txt")

	tetrisRes := moveBlock(tetris)
	fmt.Println(tetrisRes, tetris.dimensions)
}
