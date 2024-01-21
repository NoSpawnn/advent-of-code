package main

import (
	"errors"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"strconv"
)

const (
	EnvVarName       = "AOC_SESSION_KEY"                                          // Environment variable that holds the session key
	InputBaseUrl     = "https://adventofcode.com/%d/day/%d/input"                 // Format with year then day
	InputDir         = "%d/input"                                                 // Input directory, format with year
	InputFileNameFmt = "day_%02d.txt"                                             // Format with day
	UserAgentStr     = "github.com/NoSpawnn/advent-of-code by nospawnn@skiff.com" // Contact info so I can get shouted at for spamming
)

func getSessionKey() (string, error) {
	sessionKey := os.Getenv(EnvVarName)

	if len(sessionKey) == 0 {
		return "", errors.New("session key environment variable is unset")
	}

	return sessionKey, nil
}

func buildRequest(sessionKey string, year, day int) *http.Request {
	reqUrlStr := fmt.Sprintf(InputBaseUrl, year, day)

	req, err := http.NewRequest(http.MethodGet, reqUrlStr, nil)
	if err != nil {
		log.Fatal(err)
	}
	req.Header.Add("User-Agent", UserAgentStr)
	req.AddCookie(&http.Cookie{
		Name:  "session",
		Value: sessionKey,
	})

	return req
}

func download(sessionKey string, year, day int) {
	req := buildRequest(sessionKey, year, day)
	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		log.Fatal(err)
	}

	if resp.StatusCode == http.StatusNotFound {
		fmt.Printf("DOWNLOAD ERROR %d - requested input does not exist (%d day %d)\n", http.StatusNotFound, year, day)
		return
	} else if resp.StatusCode == http.StatusBadRequest {
		fmt.Printf("DOWNLOAD ERROR %d - is your session key correct?\n", http.StatusBadRequest)
		return
	}

	defer resp.Body.Close()
	body, err := io.ReadAll(resp.Body)
	if err != nil {
		log.Fatal(err)
	}

	dir := fmt.Sprintf(InputDir, year)
	if _, err := os.Stat(dir); errors.Is(err, os.ErrNotExist) {
		os.Mkdir(dir, os.ModePerm)
	}

	f := filepath.Join(dir, fmt.Sprintf(InputFileNameFmt, day))
	if _, err := os.Stat(f); err == nil {
		fmt.Println("!! input file already exists !!")
		return
	}

	os.WriteFile(f, body, os.ModePerm)
}

func main() {
	sessionKey, err := getSessionKey()
	if err != nil {
		log.Fatal(err)
	}

	year, err := strconv.Atoi(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}

	day, err := strconv.Atoi(os.Args[2])
	if err != nil {
		log.Fatal(err)
	}

	download(sessionKey, year, day)
}
