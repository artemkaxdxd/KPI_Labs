package main

import (
	"fmt"
	"io"
	"os"
)

// File System interface
var fs fileSystem = osFS{}

type fileSystem interface {
	Open(name string) (file, error)
}

type file interface {
	io.Closer
	io.Reader
}

// osFS implements fileSystem using the local disk.
type osFS struct{}

func (osFS) Open(name string) (file, error) { return os.Open(name) }

// Writer interface
var outOs mainOutput = osOut{}

type mainOutput interface {
	Open() output
}

type output interface {
	io.Writer
}

type osOut struct{}

func (osOut) Open() output { return os.Stdout }

func communicate(fs fileSystem, outOs mainOutput, str string) {
	opener := outOs.Open()

	file, err := fs.Open(str)
	if err != nil {
		fmt.Fprintln(opener, err.Error())
		return
	}

	field, err := parse(file, opener)
	if err != nil {
		fmt.Fprintln(opener, err.Error())
		return
	}
	newField := *field
	newField = tetris(newField)

	printField(opener, newField)

	defer file.Close()
}

func main() {
	if len(os.Args) > 1 {
		fmt.Println(os.Args[1:])
	}
	fileName := "input.txt"

	communicate(fs, outOs, fileName)
}
