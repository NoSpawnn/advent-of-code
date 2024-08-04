# [Advent Of Code](https://adventofcode.com)

- <https://github.com/NoSpawnn/advent-of-code>

My solutions to Advent of Code by [Eric Wastl](http://was.tl/).

## Usage

### Downloading input

- Set your session key as below
- Run `<gradle|./gradlew> download -Pdate=<YYYY/DD>`
- Inputs are saved to `./inputs/YYYY/DD.txt`

### Solve

- Ensure input is downloaded, and solver is added to [SolverMap](src/main/kotlin/adventOfCode/lib/SolverMap.kt)
- Run `<gradle|./gradlew> solve -Pdate=<YYYY/DD>`

#### Getting/Setting your session key

**Firefox**:

- Go to adventofcode.com
- Log in
- Open inspect element
- Select the "Storage" tab
- Select "<https://adventofcode.com>" under "Cookies" on the left
- Find the row with the name "session"
- Copy its value
- Set is as an environment variable named `AOC_SESSION_KEY`

```shell
$ export AOC_SESSION_KEY=<session_key>
```
