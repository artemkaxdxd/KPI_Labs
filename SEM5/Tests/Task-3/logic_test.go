package main

import (
	"reflect"
	"strings"
	"testing"
)

func TestMoveBlock(t *testing.T) {
	t.Run("It should move the block one pixel down", func(t *testing.T) {
		// Given
		var initialField Field

		input :=
			"4 5\n" +
				"..p..\n" +
				"#.p..\n" +
				"#...#\n" +
				"#...#\n"

		myReader := strings.NewReader(input)
		parse(myReader, &initialField)

		// When
		finalField := moveBlock(initialField)

		// Then
		var wantField Field

		want :=
			"4 5\n" +
				".....\n" +
				"#.p..\n" +
				"#.p.#\n" +
				"#...#\n"

		myReader = strings.NewReader(want)
		parse(myReader, &wantField)

		if !reflect.DeepEqual(finalField, wantField) {
			t.Errorf("MoveBlock: \nwant\n %v\n got\n %v", wantField, finalField)
		}
	})

	t.Run("It should return the same field after meeting land", func(t *testing.T) {
		// Given
		var initialField Field

		input :=
			"4 5\n" +
				"..p..\n" +
				"#.p..\n" +
				"#####\n" +
				"#####\n"

		myReader := strings.NewReader(input)
		parse(myReader, &initialField)

		// When
		finalField := moveBlock(initialField)

		// Then
		var wantField Field

		want :=
			"4 5\n" +
				"..p..\n" +
				"#.p..\n" +
				"#####\n" +
				"#####\n"

		myReader = strings.NewReader(want)
		parse(myReader, &wantField)

		if !reflect.DeepEqual(finalField, wantField) {
			t.Errorf("MoveBlock:\nwant\n %v\ngot\n %v", wantField, finalField)
		}
	})

	t.Run("It should return the same field after falling to the bottom", func(t *testing.T) {
		// Given
		var initialField Field

		input :=
			"4 5\n" +
				".....\n" +
				"#....\n" +
				"#.p.#\n" +
				"#.p.#\n"

		myReader := strings.NewReader(input)
		parse(myReader, &initialField)

		// When
		finalField := moveBlock(initialField)

		// Then
		var wantField Field

		want :=
			"4 5\n" +
				".....\n" +
				"#....\n" +
				"#.p.#\n" +
				"#.p.#\n"

		myReader = strings.NewReader(want)
		parse(myReader, &wantField)

		if !reflect.DeepEqual(finalField, wantField) {
			t.Errorf("MoveBlock:\nwant\n %v\ngot\n %v", wantField, finalField)
		}
	})
}

func TestTetris(t *testing.T) {
	t.Run("It should reach the bottom", func(t *testing.T) {
		// Given
		var initialField Field

		input :=
			"4 5\n" +
				"..p..\n" +
				"#.p..\n" +
				"#...#\n" +
				"#...#\n"

		myReader := strings.NewReader(input)
		parse(myReader, &initialField)

		// When
		finalField := tetris(initialField)

		// Then
		var wantField Field

		want :=
			"4 5\n" +
				".....\n" +
				"#....\n" +
				"#.p.#\n" +
				"#.p.#\n"

		myReader = strings.NewReader(want)
		parse(myReader, &wantField)

		if !reflect.DeepEqual(finalField, wantField) {
			t.Errorf("Tetris:\nwant\n %v\ngot\n %v", wantField, finalField)
		}
	})

	t.Run("It should stop when it hits land", func(t *testing.T) {
		// Given
		var initialField Field

		input :=
			"4 5\n" +
				"..ppp\n" +
				"#....\n" +
				"#....\n" +
				"#...#\n"

		myReader := strings.NewReader(input)
		parse(myReader, &initialField)

		// When
		finalField := tetris(initialField)

		// Then
		var wantField Field

		want :=
			"4 5\n" +
				".....\n" +
				"#....\n" +
				"#.ppp\n" +
				"#...#\n"

		myReader = strings.NewReader(want)
		parse(myReader, &wantField)

		if !reflect.DeepEqual(finalField, wantField) {
			t.Errorf("Tetris:\nwant\n %v\ngot\n %v", wantField, finalField)
		}
	})
}
