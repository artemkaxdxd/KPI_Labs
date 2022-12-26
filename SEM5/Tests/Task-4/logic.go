package main

import (
	"reflect"
)

type Field struct {
	dimensions []int
	pieces     []Point
	landscape  []Point
}

type Point struct {
	x int
	y int
}

func moveBlock(f Field) Field {
	// make a copy of field to modify it
	var newF Field
	newF.dimensions = append(newF.dimensions, f.dimensions...)
	newF.pieces = append(newF.pieces, f.pieces...)
	newF.landscape = append(newF.landscape, f.landscape...)

	for i := range f.pieces {
		// move every part of piece down 1 pixel
		newF.pieces[i].x = newF.pieces[i].x + 1

		for _, v2 := range f.landscape {
			//check if new piece placement doesn't intersect with land pixels
			if newF.pieces[i] == v2 || newF.pieces[i].x > f.dimensions[0]-1 {
				return f
			}
		}
	}
	return newF
}

func tetris(field Field) Field {
	for {
		newField := moveBlock(field)
		if !reflect.DeepEqual(field, newField) {
			field = newField
		} else {
			break
		}
	}
	return field
}
