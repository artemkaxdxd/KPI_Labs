package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func Parse(inputFile string) []string {

	file, err := os.Open(inputFile)
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	var inputStr string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		inputStr = scanner.Text()
	}

	inputArr := strings.Split(inputStr, " ")
	return inputArr
}

type CalculatorState struct {
	screen           int
	first_number     int
	op               string
	start_new_number bool
}

func (c *CalculatorState) HandleKeyPress(key string) {
	if len(key) != 1 {
		log.Fatal("Error! Key should be len of 1. Example `1 1 + 2 2 =`. Got: ", key)
	}
	if c.start_new_number {
		num1, err := strconv.Atoi(key)
		if err != nil {
			log.Fatal(err)
		}
		c.screen = num1
		c.start_new_number = false
	} else if num2, err := strconv.Atoi(key); err == nil {
		num3, err := strconv.Atoi(fmt.Sprintf("%d%d", c.screen, num2))
		if err != nil {
			log.Fatal(err)
		}
		c.screen = num3
	} else if key == "+" || key == "-" || key == "*" || key == "/" {
		c.op = key
		c.first_number = c.screen
		c.screen = 0
		c.start_new_number = true
	} else if key == "=" {
		if c.op == "+" {
			c.screen = c.first_number + c.screen
		}
		if c.op == "-" {
			c.screen = c.first_number - c.screen
		}
		if c.op == "*" {
			c.screen = c.first_number * c.screen
		}
		if c.op == "/" {
			c.screen = c.first_number / c.screen
		}
		c.first_number = 0
		c.op = "empty"
		c.start_new_number = true
	} else {
		log.Fatal(err)
	}
}

func Calculate(keys []string) int {
	newCalc := CalculatorState{0, 0, "", true}
	for _, key := range keys {
		newCalc.HandleKeyPress(key)
	}
	return newCalc.screen
}

func saveOutput(result int) {
	file, err := os.Create("output.txt")
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	_, err1 := file.WriteString(fmt.Sprintf("%d", result))
	if err1 != nil {
		log.Fatal(err1)
	}
}

func main() {
	expr := Parse("input.txt")
	result := Calculate(expr)
	//fmt.Println(expr, result)
	saveOutput(result)
}
