#!/usr/bin/env python3
import sys
from openai import OpenAI

if len(sys.argv) < 3:
    print("USE: ./gpt.py API_KEY \"MSG TO GPT\"")
    sys.exit(84)

api_key = sys.argv[1]
user_message = " ".join(sys.argv[2:])
client = OpenAI(api_key = api_key)

try:
    response = client.chat.completions.create (
        model = "gpt-3.5-turbo",
        messages = [{"role": "user", "content": user_message}]
    )
    print("\n\033[1;33mGarmentMaker: \033[0m")
    print(response.choices[0].message.content)
except Exception as e:
    print("Error:", e)
