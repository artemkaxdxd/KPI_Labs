package main

import (
	"io"
	"log"
	"os"
)

func communicate(w io.Writer, r io.Reader, field Field) Field {
	parse(r, &field)

	field = tetris(field)

	printField(w, field)
	//fmt.Println(field)
	return field
}

func main() {
	field := Field{}

	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	communicate(os.Stdout, file, field)
}
