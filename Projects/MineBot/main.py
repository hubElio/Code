import pyautogui
import time
import random
from PIL import Image

import os
import sys

import serial

import tkinter as tk

import threading

def PythonGui():
    """
    The PythonGui function creates a simple GUI window for an AutoClicker application using Tkinter.
    """

    root = tk.Tk()
    root.geometry("500x270")
    root.title("AutoClicker")
    root.configure(bg="#181818")
    root.resizable(False, False)

    # Set icon if available
    try:
        icon = tk.PhotoImage(file=resource_path("Resources/icon.png"))
        root.iconphoto(True, icon)
    except Exception:
        pass

    # Use ttk for modern widgets
    style = tk.ttk.Style()
    style.theme_use("clam")
    style.configure("TFrame", background="#181818")
    style.configure("TLabel", background="#181818", foreground="#f3f3f3", font=("Segoe UI Variable", 18, "bold"))
    style.configure("TButton", font=("Segoe UI Variable", 12), padding=8,
                    background="#232323", foreground="#f3f3f3")
    style.map("TButton",
              background=[("active", "#222"), ("!active", "#232323")],
              foreground=[("active", "#00bfff"), ("!active", "#f3f3f3")])

    main_frame = tk.ttk.Frame(root, padding=30, style="TFrame")
    main_frame.pack(expand=True, fill="both")

    label = tk.ttk.Label(main_frame, text="AutoClicker", style="TLabel")
    label.pack(pady=(0, 20))

    button_frame = tk.ttk.Frame(main_frame, style="TFrame")
    button_frame.pack(pady=10, fill="x")


    btnOne = tk.ttk.Button(button_frame, text="Start fishing", style="TButton")
    btnTwo = tk.ttk.Button(button_frame, text="Start mining", style="TButton")
    btnThree = tk.ttk.Button(button_frame, text="Start farming", style="TButton")

    btnOne.config(command=lambda: start_or_stop_automation("fishing", auto_fishing_minecraft, btnOne))
    btnTwo.config(command=lambda: start_or_stop_automation("mining", auto_mining_minecraft, btnTwo))
    btnThree.config(command=lambda: start_or_stop_automation("farming", auto_farming_minecraft, btnThree))

    btnOne.grid(row=0, column=0, sticky="ew", padx=5)
    btnTwo.grid(row=0, column=1, sticky="ew", padx=5)
    btnThree.grid(row=0, column=2, sticky="ew", padx=5)

    button_frame.columnconfigure(0, weight=1)
    button_frame.columnconfigure(1, weight=1)
    button_frame.columnconfigure(2, weight=1)

    exit_btn = tk.ttk.Button(main_frame, text="Quit", command=root.quit, style="TButton")
    exit_btn.pack(pady=(30, 0), fill="x")

    root.mainloop()

# ...existing imports...

# Add global control for threads and stop events
automation_threads = {
    "fishing": {"thread": None, "stop_event": None},
    "mining": {"thread": None, "stop_event": None},
    "farming": {"thread": None, "stop_event": None},
}

def auto_fishing_minecraft(stop_event, check_interval=0.5, scroll_attempts=5):
    print("Starting auto fishing. Press Stop to stop.")
    try:
        while not stop_event.is_set():
            pyautogui.click(button='right')
            time.sleep(1.5)
            screen_width, screen_height = pyautogui.size()
            center_x, center_y = screen_width // 2, screen_height // 2
            initial_pixel = pyautogui.screenshot().getpixel((center_x, center_y))
            start_time = time.time()
            while time.time() - start_time < 30 and not stop_event.is_set():
                current_pixel = pyautogui.screenshot().getpixel((center_x, center_y))
                if current_pixel != initial_pixel:
                    break
                time.sleep(check_interval)
            pyautogui.click(button='right')
            time.sleep(0.7)
            hotbar_x = screen_width // 2 - 300
            hotbar_y = screen_height - 40
            slot_pixel = pyautogui.screenshot().getpixel((hotbar_x, hotbar_y))
            if sum(slot_pixel) < 60:
                print("Rod broke! Scrolling to next slot.")
                for _ in range(scroll_attempts):
                    pyautogui.scroll(-1)
                    time.sleep(0.2)
                time.sleep(1.0)
    except Exception as e:
        print(f"Error in auto_fishing_minecraft: {e}")
    print("Auto fishing stopped.")

def auto_mining_minecraft(stop_event, duration=60, interval=0.1):
    print(f"Starting auto mining. Press Stop to stop early.")
    start_time = time.time()
    try:
        while time.time() - start_time < duration and not stop_event.is_set():
            pyautogui.mouseDown(button='left')
            time.sleep(interval)
            pyautogui.mouseUp(button='left')
            time.sleep(0.05)
    except Exception as e:
        print(f"Error in auto_mining_minecraft: {e}")
    finally:
        pyautogui.mouseUp(button='left')
        print("Auto mining finished.")

def auto_farming_minecraft(stop_event, duration=60, interval=0.2, move_interval=2.0):
    print(f"Starting auto farming. Press Stop to stop early.")
    start_time = time.time()
    try:
        while time.time() - start_time < duration and not stop_event.is_set():
            pyautogui.mouseDown(button='right')
            time.sleep(interval)
            pyautogui.mouseUp(button='right')
            if int((time.time() - start_time) // move_interval) != int((time.time() - start_time - interval) // move_interval):
                pyautogui.keyDown('w')
                time.sleep(0.3)
                pyautogui.keyUp('w')
            time.sleep(0.05)
    except Exception as e:
        print(f"Error in auto_farming_minecraft: {e}")
    finally:
        pyautogui.mouseUp(button='right')
        pyautogui.keyUp('w')
        print("Auto farming finished.")

def start_or_stop_automation(name, func, button):
    state = automation_threads[name]
    if state["thread"] is not None and state["thread"].is_alive():
        # Stop the thread
        state["stop_event"].set()
        button.config(text=f"Start {name}")
    else:
        # Start the thread
        stop_event = threading.Event()
        thread = threading.Thread(target=func, args=(stop_event,))
        thread.daemon = True
        state["thread"] = thread
        state["stop_event"] = stop_event
        thread.start()
        button.config(text=f"Stop {name}")


def ConvJpegPng(InitPath,EndPath):
    """
    The function `ConvJpegPng` converts a JPEG image to a PNG image.
    
    :param InitPath: The `InitPath` parameter in the `ConvJpegPng` function is the file path of the
    initial image in JPEG format that you want to convert to PNG format
    :param EndPath: The `EndPath` parameter in the `ConvJpegPng` function represents the file path where
    the converted PNG image will be saved
    """
    img = Image.open(InitPath)
    img.save(EndPath, "PNG")

def resource_path(relative_path):
    """ Get absolute path to resource, works for dev and for PyInstaller """
    if hasattr(sys, '_MEIPASS'):
        return os.path.join(sys._MEIPASS, relative_path)
    # Utilise le dossier du script comme base
    base_path = os.path.dirname(os.path.abspath(__file__))
    return os.path.join(base_path, relative_path)

def run_in_thread_with_ui(target_func, buttons, *args, **kwargs):
    def wrapper():
        try:
            target_func(*args, **kwargs)
        except Exception as e:
            print(f"Error: {e}")
            tk.messagebox.showerror("Error", f"An error occurred:\n{e}")
        finally:
            for btn in buttons:
                btn.config(state="normal")
    # Disable buttons while running
    for btn in buttons:
        btn.config(state="disabled")
    thread = threading.Thread(target=wrapper)
    thread.daemon = True  # <-- This line ensures threads exit with the main program
    thread.start()
    return thread

def serial_communication(port='COM3', baudrate=9600, timeout=1):
    """
    The function `serial_communication` establishes a serial connection to a specified port and
    continuously reads and prints incoming data until interrupted.
    
    :param port: The `port` parameter in the `serial_communication` function specifies the serial port
    to which the function will connect. In this case, it is set to 'COM3' by default, which is a common
    port name for Windows systems. If you are using a different operating system or a different port,
    you may need to change this value accordingly
    :param baudrate: The `baudrate` parameter in the `serial_communication` function specifies the
    communication speed for the serial connection. It is set to 9600 bits per second (bps) by default,
    which is a common baud rate for many serial devices. This parameter determines how fast data is
    transmitted between the computer and the connected device
    :param timeout: The `timeout` parameter in the `serial_communication` function specifies the maximum
    amount of time (in seconds) that the function will wait for data to be received from the serial port
    before timing out. In this case, it is set to 1 second by default. If no data is received within this
    time frame, the function will return an empty byte string
    """
    try:
        ser = serial.Serial(port, baudrate, timeout=timeout)
        print(f"Connected to {port} at {baudrate} baud.")
        
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').rstrip()
                print(line)
                
    except serial.SerialException as e:
        print(f"Error: {e}")
    except KeyboardInterrupt:
        print("Serial communication stopped by user.")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Serial port closed.")

if __name__ == "__main__":
    print("AutoClicker Starts")
    #serial_communication(port='COM3', baudrate=9600, timeout=1)
    PythonGui()
    print("AutoClicker Ends.")

