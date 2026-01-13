import tkinter as tk
from tkinter import messagebox
import random
import time
import threading
import pyautogui

# List of funny messages
messages = [
    "You have entered into the factory reset software",
    "Are you sure you want to do that?",
    "Started erasing files...",
    "Erasing contents (70% Completed)",
    "Might take some time for the files to totally disappear",
    "Self-destructing in 3... 2... 1..."
]

# Function to show random pop-ups
def show_popup():
    while True:
        time.sleep(random.randint(5, 10))  # Delay between pop-ups
        root = tk.Tk()
        root.withdraw()  # Hide the main window
        message = random.choice(messages)
        messagebox.showinfo("Surprise!", message)
        root.destroy()

# Function to move the mouse randomly
def move_mouse():
    while True:
        time.sleep(5)  # Move every 5 seconds
        screen_width, screen_height = pyautogui.size()
        x, y = random.randint(0, screen_width), random.randint(0, screen_height)
        pyautogui.moveTo(x, y, duration=0.5)

# Start both functions in separate threads
threading.Thread(target=show_popup, daemon=True).start()
threading.Thread(target=move_mouse, daemon=True).start()

# Keep the script running
while True:
    time.sleep(1)
