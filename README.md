# 42sh GPT – Smart Terminal Assistant

## 📋 Description

`42sh GPT` is a custom Unix shell inspired by `tcsh`, built in C, with enhanced user features. It includes:

- Core shell functionalities (job control, variables, history, aliases, etc.)
- Auto-completion using the `TAB` key
- Integrated **ChatGPT assistant**, which allows you to control your computer using natural language

---

## 🤖 ChatGPT Integration

You can ask the AI for help **directly from the terminal** by typing:

```bash
#<your question or request>
```

### 💡 Examples

```bash
#how do I install nginx?
#rename all .txt files to .md
#generate a bash script to backup my home folder
```

ChatGPT will interpret your request and **execute or suggest commands** in your shell.

---

## ⚙️ Features

- Auto-completion via `TAB`
- Natural language interface with ChatGPT
- Executes shell commands based on user queries
- Traditional shell syntax compatibility (inspired by `tcsh`)
- Support for aliases, environment variables, scripting, and more
- Robust error handling and proper exit codes

---

## 📥 Installation

### Requirements

#### Ubuntu/Debian

```bash
sudo apt update
sudo apt install python3-pip -y
```

#### Fedora

```bash
sudo dnf install python3-pip -y
```

### Python Requirements

Install the required Python packages for ChatGPT integration:

```bash
pip install -r requirements.txt
```

> The file `requirements.txt` must be present in the root directory. It should include libraries like `openai`, etc.

---

## 🔧 Compilation

Compile the shell using the Makefile provided:

```bash
make
```

Useful targets:

- `make re` — rebuild the shell
- `make clean` — remove object files
- `make fclean` — remove all compiled files and binary

---

## 🧠 Advanced Features

The enhanced version of the shell, with **ChatGPT integration** and **TAB autocompletion**, is located in the [`/Bonus`](./Bonus/) folder.

> Includes:
> - AI assistant using natural language (`#your question`)
> - Command autocompletion with `TAB`
> - Bonus Makefile and modular structure

---
