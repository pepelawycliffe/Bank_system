# ChangeLog
All noteable changes ot this project will be documented in this file.

## [1.0.0] - 2020-06-03
### Added
- variable to hold the data file name
- account::create_account()
	- while statement to assure either checking or saving account chosen
- `int main()` function to use `do` and display project

### Changed
- modify_account(int)
	- made sure to use !kFile.eof(), not `kFile.eof()`
- must initialize booleans as false/true, not just declared
- display_sp(int)
	-read the file in the while statement, not `.eof()`