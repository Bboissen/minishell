# Minishell

A custom shell implementation created as part of the 42 school curriculum. This project aims to replicate a subset of the functionality of shells like bash, providing a deeper understanding of process management, file descriptors, and system calls in a Unix-like environment.

## About The Project

The Minishell project is a significant challenge in the 42 cursus, requiring students to build a command-line interpreter from scratch. It involves parsing user input, managing environment variables, handling command execution with pipes and redirections, and implementing several built-in shell commands.

## Features

* **Command Execution**: Supports executing commands from the system's `PATH`.
* **Pipes**: Chain multiple commands together using the `|` operator.
* **Redirections**:
  * Input redirection: `<`
  * Output redirection: `>`
  * Append output redirection: `>>`
  * Heredoc: `<<`
* **Built-in Commands**:
  * `echo` with the `-n` option
  * `cd` with relative or absolute paths
  * `pwd` to display the current working directory
  * `export` to manage environment variables
  * `unset` to remove environment variables
  * `env` to display the environment variables
  * `exit` to terminate the shell
* **Signal Handling**:
  * `Ctrl-C`: Interrupts the current process and displays a new prompt.
  * `Ctrl-D`: Exits the shell.
  * `Ctrl-\`: Does nothing.
* **Environment Variable Expansion**: Supports `$VAR` and `$?` expansion in command arguments.

## Getting Started

Follow these instructions to get a copy of the project up and running on your local machine.

### Prerequisites

* A C compiler (e.g., `gcc`, `clang`)
* `make`
* `readline` library

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/Bboissen/minishell.git
   ```
2. Navigate to the project directory:
   ```sh
   cd minishell
   ```
3. Compile the project:
   ```sh
   make
   ```

### Usage

To start the shell, run the executable:

```sh
./minishell
```
