import pyautogui
import random
import time
import string

# Some settings
MIN_DELAY = 0.5  # minimum delay in seconds between actions
MAX_DELAY = 3.0  # maximum delay in seconds between actions
SCREEN_WIDTH, SCREEN_HEIGHT = pyautogui.size()  # screen resolution

# List of characters to simulate keyboard inputs
CHARS = string.ascii_letters + string.digits


def random_mouse_movement():
    x = random.randint(0, SCREEN_WIDTH - 1)
    y = random.randint(0, SCREEN_HEIGHT - 1)
    pyautogui.moveTo(x, y, duration=random.uniform(0.1, 1.0))


def random_mouse_click():
    button = random.choice(['left', 'right'])
    pyautogui.click(button=button)


def random_keyboard_input():
    character = random.choice(CHARS)
    pyautogui.typewrite(character)


# List of actions
ACTIONS = [random_mouse_movement, random_mouse_click, random_keyboard_input]

# Infinite loop to continuously perform random actions
while True:
    # Select a random action from the list
    action = random.choice(ACTIONS)

    # Perform the action
    action()

    # Sleep for a random amount of time between actions
    time.sleep(random.uniform(MIN_DELAY, MAX_DELAY))
