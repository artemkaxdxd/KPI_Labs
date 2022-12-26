package main

import (
	"bytes"
	"io"
	"strings"
	"testing"
)

type mockFS struct{}

func (mockFS) Open(s string) (file, error) {
	myReader := strings.NewReader(s)
	myReaderCloser := io.NopCloser(myReader)
	return myReaderCloser, nil
}

type mockOut struct{}

var buffer = bytes.Buffer{}

func (mockOut) Open() output {
	return &buffer
}

func TestCommunicate(t *testing.T) {
	t.Run("it should parse input file and throw an error if it is wrong", func(t *testing.T) {
		buffer.Reset()

		// Given
		input := "wrong input file body"

		var fs fileSystem = mockFS{}
		var out mainOutput = mockOut{}

		// When
		communicate(fs, out, input)

		got := buffer.String()
		want := "strconv.Atoi:"

		// Then
		if !strings.Contains(got, want) {
			t.Errorf("Parsing input:\n got:\n%s want:\n%s", got, want)
		}
	})

	t.Run("it should print final board state", func(t *testing.T) {
		buffer.Reset()
		// Given
		input :=
			"3 5\n" +
				"..p..\n" +
				"#.p..\n" +
				"#...#\n"

		var fs fileSystem = mockFS{}
		var out mainOutput = mockOut{}

		// When
		communicate(fs, out, input)

		got := buffer.String()
		want :=
			".....\n" +
				"#.p..\n" +
				"#.p.#\n"
		if got != want {
			t.Errorf("Printing field:\n got:\n%s want:\n%s", got, want)
		}
	})
}
