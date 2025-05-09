#!/usr/bin/env python3
import os
import sys
import json
from openai import OpenAI
import subprocess
import shutil

CONFIG_PATH = os.path.expanduser("~/config.json")
DEFAULT_FIELDS = ["name", "operating system"]

if len(sys.argv) < 2:
    print("USAGE: ./gpt.py \"MESSAGE FOR GPT\"")
    sys.exit(84)

user_message = sys.argv[2]

def print_indent_wrap(text):
    width = shutil.get_terminal_size((80, 20)).columns
    indent = "\t"
    max_width = width - len(indent)

    while text:
        print(indent + text[:max_width])
        text = text[max_width:]

def delete_input(lines=3):
    for _ in range(lines):
        sys.stdout.write("\033[F")
        sys.stdout.write("\033[K")
    sys.stdout.flush()

def input_question(mensage):
    columns = os.get_terminal_size().columns
    espaces = " " * (columns - len(mensage) - 4)
    sys.stdout.write(f"\033[1;34m{espaces}╔═════════════════════════════════════════╗\n")
    sys.stdout.write(f"{espaces}║ {mensage} ║\n")
    sys.stdout.write(f"{espaces}╚═════════════════════════════════════════╝\033[0m")
    sys.stdout.flush()
    res = input().strip()
    delete_input()
    return res

def append_to_bash_history(command):
    history_path = os.path.expanduser("~/.bash_history")
    try:
        with open(history_path, "a") as f:
            f.write(command.strip() + "\n")
    except Exception as e:
        print(f"\033[1;31m[✗]\033[0m Error writing to history: {e}")


def run_command(command):
    print(f"\n\n\033[1;33m[GarmentMaker]\033[0m :Do you want to run the following command?")
    print(f"\033[1;34m\t║ {command} ║\033[0m")
    response = input_question("[Press 'Enter' to run, 'c' to cancel]: ")
    
    if response == "":
        append_to_bash_history(command)
        sys.stdout.write("\n")
        try:
            process = subprocess.Popen(
                command,
                shell=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True
            )
            for line in process.stdout:
                print(line)
                sys.stdout.write("\033[F")
                sys.stdout.write("\033[K") 
            process.wait()
            print("\n")
        except KeyboardInterrupt:
            print("\n\033[1;31m[GarmentMaker] Program interrupted by user (Ctrl+C). Exiting ):\033[0m")
            sys.exit(0)
        except Exception as e:
            print(f"\033[1;31mError running command: {e}\033[0m")
    elif response.lower() == 'c':
        print("Command cancelled.")
    else:
        print("Invalid option. Command cancelled.")

def process_response(response):
    lines = response.split('\n')
    
    for line in lines:
        if line.startswith("[TERMINAL]"):
            command_line = line.replace("[TERMINAL]", "").strip()
            run_command(command_line)
        else:
            print_indent_wrap(line)

def load_or_create_config():
    if os.path.exists(CONFIG_PATH):
        with open(CONFIG_PATH, "r") as f:
            config = json.load(f)
    else:
        print(f"\033[1;33m[GarmentMaker]\033[0m : Creating new profile")
        config = {}
        for field in DEFAULT_FIELDS:
            value = input(f"\t\t What is your {field}?\n\t\t  > ").strip()
            config[field] = value
        with open(CONFIG_PATH, "w") as f:
            json.dump(config, f, indent=2)
        print(f"\033[1;33m[GarmentMaker]\033[0m : \033[1;32mSUCCESS\033[0m")
    return config

def build_prompt(user_question, config):
    system_prompt = (
        "Your name is GarmentMaker. You are a terminal assistant.\n"
        "Your job is to answer terminal-related questions.\n"
        "If your answer includes commands, follow this structure:\n\n"
        "1. Explanation of the command.\n"
        "2. [TERMINAL]\"command\" (Start the line with [TERMINAL], then write the command on the next line).\n"
        "3. If there are more commands, repeat from step 1.\n"
        "4. If it's the last command, end with [END] and don't include anything else related to the previous command.\n\n"
        "Example of the expected format:\n"
        "To install Python on Fedora, use the `dnf` package manager:\n"
        "[TERMINAL] sudo dnf install python3\n"
        "To create a Python file with code inside, use this command:\n"
        "[TERMINAL] echo \"print('Hello from Python!')\" > example.py\n"
        "To run the Python file:\n"
        "[TERMINAL] python3 example.py\n"
        "[END]\n\n"
        "If the user needs to install a programming language, use the following pattern:\n"
        "1. To create Java files, use `echo` to automatically generate the file with content like this:\n"
        "[TERMINAL] echo 'public class Example { public static void main(String[] args) { System.out.println(\"Hello from Java!\"); } }' > Example.java\n"
        "2. To compile and run the Java file:\n"
        "[TERMINAL] javac Example.java\n"
        "[TERMINAL] java Example\n"
        "[END]\n\n"
        "Use the same approach for other languages like C, Ruby, etc., adapting file content and corresponding commands.\n"
        "Using editors like nano, emacs, or vim to make the user write code is forbidden.\n"
        "If you want the user to create a file, you must do it yourself using `echo` and redirect the content.\n"
        "IMPORTANT: always use the `-e` flag when using `echo`.\n"
        "Never include `\\n` inside the code when printing to a file. For example, if you want to do print(\"hello\\n\"), just remove the `\\n`.\n"
    )
    user_data = f"User name: {config['name']}\nOperating system: {config['operating system']}\n\n"
    full_prompt = system_prompt + user_data + "User question: " + user_question
    return full_prompt

if __name__ == "__main__":
    config = load_or_create_config()
    prompt = build_prompt(user_message, config)
    try:
        key = sys.argv[1]
        client = OpenAI(api_key=key)
        response = client.chat.completions.create(
            model="gpt-3.5-turbo",
            messages=[
                {"role": "system", "content": "You are GarmentMaker, a Linux terminal expert."},
                {"role": "user", "content": prompt}
            ]
        )
        print("\n\033[1;33mGarmentMaker: \033[0m")
        process_response(response.choices[0].message.content)
    except KeyboardInterrupt:
        print("\n\033[1;31m[GarmentMaker] Program interrupted by user (Ctrl+C). Exiting ):\033[0m")
        sys.exit(0)
    except Exception as e:
        print("Error:", e)
        sys.exit(84)
