package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

const (
	// Prompt templates
	promptAltCount = "Введіть кількість альтернатив: "
	promptAltName  = "Введіть назву альтернативи %d: "
	promptExpCount = "Введіть кількість експертів: "
	promptExpName  = "Введіть ім'я експерта %d: "
	promptMaxScore = "Введіть максимальне значення бальної системи (наприклад, 10): "
	promptScore    = "Оцінка для альтернативи '%s' (від 1 до %d): "

	// Error messages
	errInvalidCount = "Некоректне число %s"
	errInvalidScore = "Некоректне значення системи балів"
	errInvalidValue = "Некоректне значення. Будь ласка, спробуйте ще раз."

	// Table formats
	headerFormat     = "%-30s"
	altHeaderFormat  = "%-20s"
	scoreFormat      = "%-20.2f"
	resultRankFormat = "%-5s %-20s %-15s\n"
	resultItemFormat = "%-5d %-20s %-15.4f\n"
)

type (
	// Alternative saves the name and average normalized score of an alternative
	Alternative struct {
		name     string
		avgScore float64
	}

	// Score maps
	alternativeScores map[string]float64
	expertScores      map[string]alternativeScores

	// DecisionSystem encapsulates the core logic of the decision support system
	DecisionSystem struct {
		alternatives []string
		experts      []string
		maxScore     int
		scores       expertScores
	}

	// inputReader encapsulates input reading operations
	inputReader struct {
		reader *bufio.Reader
	}
)

// newInputReader creates a new input reader
func newInputReader() *inputReader {
	return &inputReader{bufio.NewReader(os.Stdin)}
}

// readString reads a string from input
func (ir *inputReader) readString(prompt string) (string, error) {
	fmt.Print(prompt)
	input, _ := ir.reader.ReadString('\n')
	return strings.TrimSpace(input), nil
}

// readInt reads and parses an integer
func (ir *inputReader) readInt(prompt string) (int, error) {
	input, _ := ir.readString(prompt)
	return strconv.Atoi(input)
}

// readStringArray reads multiple strings
func (ir *inputReader) readStringArray(count int, promptTemplate string) []string {
	items := make([]string, count)
	for i := range count {
		prompt := fmt.Sprintf(promptTemplate, i+1)
		items[i], _ = ir.readString(prompt)
	}
	return items
}

// readScore reads and validates a score
func (ir *inputReader) readScore(alt string, maxScore int) float64 {
	for {
		prompt := fmt.Sprintf(promptScore, alt, maxScore)
		scoreStr, _ := ir.readString(prompt)
		score, err := strconv.ParseFloat(scoreStr, 64)
		if err == nil && score >= 1 && score <= float64(maxScore) {
			return score
		}
		fmt.Println(errInvalidValue)
	}
}

// newDecisionSystem creates and initializes a new DecisionSystem
func newDecisionSystem(ir *inputReader) (*DecisionSystem, error) {
	// Read alternatives
	altCount, err := ir.readInt(promptAltCount)
	if err != nil || altCount <= 0 {
		return nil, fmt.Errorf(errInvalidCount, "альтернатив")
	}
	alternatives := ir.readStringArray(altCount, promptAltName)

	// Read experts
	expCount, err := ir.readInt(promptExpCount)
	if err != nil || expCount <= 0 {
		return nil, fmt.Errorf(errInvalidCount, "експертів")
	}
	experts := ir.readStringArray(expCount, promptExpName)

	// Read scoring system
	maxScore, err := ir.readInt(promptMaxScore)
	if err != nil || maxScore <= 0 {
		return nil, fmt.Errorf(errInvalidScore)
	}

	return &DecisionSystem{
		alternatives: alternatives,
		experts:      experts,
		maxScore:     maxScore,
		scores:       make(expertScores),
	}, nil
}

// CollectScores collects scores from all experts
func (ds *DecisionSystem) CollectScores(ir *inputReader) {
	for _, expert := range ds.experts {
		fmt.Printf("\nВведення оцінок експерта %s:\n", expert)
		ds.scores[expert] = make(alternativeScores)
		for _, alt := range ds.alternatives {
			ds.scores[expert][alt] = ir.readScore(alt, ds.maxScore)
		}
	}
}

// PrintScoresTable prints the table of original scores
func (ds *DecisionSystem) PrintScoresTable() {
	fmt.Println("\nТаблиця початкових оцінок:")
	fmt.Printf(headerFormat, "Експерт/Альтернатива")
	for _, alt := range ds.alternatives {
		fmt.Printf(altHeaderFormat, alt)
	}
	fmt.Println()

	for _, expert := range ds.experts {
		fmt.Printf(headerFormat, expert)
		for _, alt := range ds.alternatives {
			fmt.Printf(scoreFormat, ds.scores[expert][alt])
		}
		fmt.Println()
	}
}

// NormalizeScores normalizes the scores
func (ds *DecisionSystem) NormalizeScores() expertScores {
	normalized := make(expertScores)

	for _, expert := range ds.experts {
		normalized[expert] = make(alternativeScores)
		sum := 0.0

		for _, alt := range ds.alternatives {
			sum += ds.scores[expert][alt]
		}

		if sum == 0 {
			for _, alt := range ds.alternatives {
				normalized[expert][alt] = 0
			}
		} else {
			for _, alt := range ds.alternatives {
				normalized[expert][alt] = ds.scores[expert][alt] / sum
			}
		}
	}

	return normalized
}

// CalculateAverageScores calculates average normalized scores
func (ds *DecisionSystem) CalculateAverageScores(normalized expertScores) []Alternative {
	avgScores := make([]Alternative, 0, len(ds.alternatives))

	for _, alt := range ds.alternatives {
		sumNorm := 0.0
		for _, expert := range ds.experts {
			sumNorm += normalized[expert][alt]
		}

		avg := sumNorm / float64(len(ds.experts))
		avgScores = append(avgScores, Alternative{
			name:     alt,
			avgScore: avg,
		})
	}

	return avgScores
}

// SortAlternatives sorts alternatives by average score (descending)
func (ds *DecisionSystem) SortAlternatives(avgScores []Alternative) {
	sort.Slice(avgScores, func(i, j int) bool {
		return avgScores[i].avgScore > avgScores[j].avgScore
	})
}

// PrintRankings prints the final rankings
func (ds *DecisionSystem) PrintRankings(avgScores []Alternative) {
	fmt.Println("\nНормовані середні оцінки альтернатив та їх ранжування:")
	fmt.Printf(resultRankFormat, "Ранг", "Альтернатива", "Середня оцінка")

	for i, alt := range avgScores {
		fmt.Printf(resultItemFormat, i+1, alt.name, alt.avgScore)
	}
}

// Run executes the full decision support process
func (ds *DecisionSystem) Run(ir *inputReader) {
	// Collect scores
	ds.CollectScores(ir)

	// Print original scores
	ds.PrintScoresTable()

	// Calculate normalized scores
	normalized := ds.NormalizeScores()

	// Calculate average scores
	avgScores := ds.CalculateAverageScores(normalized)

	// Sort alternatives
	ds.SortAlternatives(avgScores)

	// Print rankings
	ds.PrintRankings(avgScores)
}

func main() {
	ir := newInputReader()

	ds, err := newDecisionSystem(ir)
	if err != nil {
		fmt.Println(err)
		return
	}

	ds.Run(ir)
}
