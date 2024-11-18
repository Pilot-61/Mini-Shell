# Mini-Shell Project

## 🐚 Overview
Mini-Shell is a custom implementation of a Unix shell, designed to mimic core functionality of bash while providing a deep understanding of process management, file descriptors, and system interactions.

## ✨ Features

### Mandatory Requirements
- Interactive command-line interface with prompt
- Command history management
- Executable search and launch capabilities
- Signal handling
- Quote processing (single and double quotes)
- Input/Output redirections
  - `<` input redirection
  - `>` output redirection
  - `<<` heredoc input
  - `>>` append output
- Pipe (`|`) support for command chaining
- Environment variable expansion
- Exit status tracking (`$?`)

### Built-in Commands
- `echo` (with `-n` option)
- `cd` (relative/absolute path)
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Signal Handling
- `Ctrl-C`: Display new prompt
- `Ctrl-D`: Exit shell
- `Ctrl-\`: No action

## 🛠 Requirements
- C Programming Language
- Readline Library
- Make

## 📦 Installation

### Prerequisites
- gcc/cc compiler
- Make
- Readline library (installed via Homebrew: `brew install readline`)

### Compilation
```bash
# Clone the repository
git clone <repository-url>

# Navigate to project directory
cd Mini-Shell

# Compile the project
make
```

## 🚀 Usage
```bash
# Run the shell
./minishell
```

## 🎯 Project Goals
- Learn process management
- Understand file descriptors
- Implement shell mechanics
- Practice low-level system programming

## 📋 Bonus Features
- Logical operators `&&` and `||`
- Parenthesis for priority
- Wildcard (`*`) support in current directory

## 📝 Notes
- Memory leaks from `readline()` are expected and acceptable
- Reference bash behavior for ambiguous requirements

## 🤝 Contributing
1. Fork the repository
2. Create your feature branch
3. Commit changes
4. Push to the branch
5. Create a Pull Request

## 📜 License
[Specify your license here]

## 👥 Authors
- [mes-salh]
- [aennaqad]# Mini-Shell
