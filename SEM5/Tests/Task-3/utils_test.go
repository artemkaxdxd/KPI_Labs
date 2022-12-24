package main

import (
	"bytes"
	"strings"
	"testing"
)

func TestParse(t *testing.T) {
	// Given
	input :=
		"5 6\n" +
			"..p...\n" +
			"##p.##\n" +
			"##pp##\n" +
			"##..##\n" +
			"##..##\n"

	myReader := strings.NewReader(input)

	// When
	buffer := bytes.Buffer{}
	f, _ := parse(myReader, &buffer)

	// Then
	rows := 5
	cols := 6

	if f.dimensions[0] != rows {
		t.Errorf("Rows: want %d, got %d", rows, f.dimensions[0])
	}
	if f.dimensions[1] != cols {
		t.Errorf("Columns: want %d, got %d", cols, f.dimensions[1])
	}

	firstPiece := Point{0, 2}
	lastPiece := Point{2, 3}

	if f.pieces[0] != firstPiece {
		t.Errorf("First piece coordinate: want %d, got %d", firstPiece, f.pieces[0])
	}
	if f.pieces[3] != lastPiece {
		t.Errorf("Last piece coordinate: want %d, got %d", lastPiece, f.pieces[3])
	}

	firstLand := Point{1, 0}
	fourthLand := Point{1, 5}

	if f.landscape[0] != firstLand {
		t.Errorf("First land coordinate: want %d, got %d", firstLand, f.landscape[0])
	}
	if f.landscape[3] != fourthLand {
		t.Errorf("Fourth land coordinate: want %d, got %d", fourthLand, f.landscape[3])
	}
}

func TestPrintField(t *testing.T) {
	// Given
	input :=
		"3 5\n" +
			"..p..\n" +
			"#.p..\n" +
			"#...#\n"

	myReader := strings.NewReader(input)
	buffer := bytes.Buffer{}
	f, _ := parse(myReader, &buffer)

	// When
	printField(&buffer, *f)

	// Then
	got := buffer.String()
	want :=
		"..p..\n" +
			"#.p..\n" +
			"#...#\n"

	if got != want {
		t.Errorf("Printing field:\n got:\n%s want:\n%s", got, want)
	}
}
