# [Advent Of Code](https://adventofcode.com)

- <https://github.com/NoSpawnn/advent-of-code>

My solutions to Advent of Code by [Eric Wastl](http://was.tl/).

### Getting/Setting your session key

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
