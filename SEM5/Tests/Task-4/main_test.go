package main

import (
	"bytes"
	"io"
	"strings"
	"testing"

	"github.com/stretchr/testify/mock"
)

type mockFS struct {
	mock.Mock
}

func newMockFS() *mockFS {
	return &mockFS{}
}

func (m mockFS) Open(name string) (file, error) {
	args := m.Called(name)
	return args.Get(0).(file), nil
}

type mockOut struct {
	mock.Mock
}

func newMockOut() *mockOut {
	return &mockOut{}
}

var buffer = bytes.Buffer{}

func (m mockOut) Open() output {
	args := m.Called()
	return args.Get(0).(output)
}

func TestCommunicate(t *testing.T) {
	t.Run("it should parse input file and throw an error if it is wrong", func(t *testing.T) {
		buffer.Reset()

		// Given
		mockFs := newMockFS()

		filename := "input.txt"
		wrongBody := "wrong input file body"

		myReader := strings.NewReader(wrongBody)
		myReaderCloser := io.NopCloser(myReader)

		mockFs.On("Open", filename).Return(myReaderCloser, nil)

		mockOut := newMockOut()

		mockOut.On("Open").Return(&buffer)

		// When
		communicate(mockFs, mockOut, filename)

		got := buffer.String()
		want := "invalid syntax"

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

		fileName := "input.txt"

		mockFs := newMockFS()

		want :=
			".....\n" +
				"#.p..\n" +
				"#.p.#\n"

		myReader := strings.NewReader(input)
		myReaderCloser := io.NopCloser(myReader)

		mockFs.On("Open", fileName).Return(myReaderCloser, nil)

		mockOut := newMockOut()

		mockOut.On("Open").Return(&buffer)
		// When
		communicate(mockFs, mockOut, fileName)

		got := buffer.String()

		if got != want {
			t.Errorf("Printing field:\n got:\n%s want:\n%s", got, want)
		}
	})
}
