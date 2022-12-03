package main

import (
	"bufio"
	"log"
	"os"
	"testing"
)

func TestParse(t *testing.T) {
	gotExpr := Parse("input_test.txt")

	wantExpr := []string{"1", "0", "0", "/", "3", "3", "="}

	for i, v := range gotExpr {
		if v != wantExpr[i] {
			t.Errorf("Parse() returned expression: %s; want %s", gotExpr, wantExpr)
		}
	}
}

func TestHandleKeyPress(t *testing.T) {
	calc := CalculatorState{0, 0, "", true}

	key1 := "1"
	want1 := 1

	calc.HandleKeyPress(key1)
	if want1 != calc.screen {
		t.Errorf("HandleKeyPress registered number on screen: %d; want %d", calc.screen, want1)
	}

	key2 := "2"
	want2 := 12
	calc.HandleKeyPress(key2)
	if want2 != calc.screen {
		t.Errorf("HandleKeyPress registered number on screen: %d; want %d", calc.screen, want2)
	}

	keyMul := "*"
	wantOp := "*"
	calc.HandleKeyPress(keyMul)
	if wantOp != calc.op {
		t.Errorf("HandleKeyPress registered operation: %s; want %s", calc.op, wantOp)
	}

	wantFirstNum := 12
	if wantFirstNum != calc.first_number {
		t.Errorf("HandleKeyPress registered first number as: %d; want %d", calc.first_number, wantFirstNum)
	}

	key3 := "3"
	want3 := 3
	calc.HandleKeyPress(key3)
	if want3 != calc.screen {
		t.Errorf("HandleKeyPress registered number on screen: %d; want %d", calc.screen, want3)
	}

	keyEquals := "="
	wantScreen := 36
	calc.HandleKeyPress(keyEquals)
	if wantScreen != calc.screen {
		t.Errorf("HandleKeyPress registered number on screen: %d; want %d", calc.screen, wantScreen)
	}
}

func TestCalculate(t *testing.T) {
	expr := []string{"1", "0", "/", "6", "="}

	gotRes := Calculate(expr)
	wantRes := 1
	if gotRes != wantRes {
		t.Errorf("Calculate returned number on screen (result): %d; want %d", gotRes, wantRes)
	}
}

func TestSaveOutput(t *testing.T) {
	saveOutput(123)

	file, err := os.Open("output.txt")
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	gotStr := ""
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		gotStr = scanner.Text()
	}

	wantNum := "123"
	if gotStr != wantNum {
		t.Errorf("Calculate returned number on screen (result): %s; want %s", gotStr, wantNum)
	}
}
