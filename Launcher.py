import tkinter as tk
from tkinter import filedialog, messagebox
import configparser
import subprocess
import os


'''
A simple GUI for loading/editing initial conditions, and running the simulation.
'''
class Launcher:
    def __init__(self, root):
        self.root = root
        self.root.title("Simulation Control")
        self.filepath = "./data/ic.ini"
        self.runfile = "run.sh"
        self.config = configparser.ConfigParser()
        self.start()

    def start(self):
        self.load_button = tk.Button(self.root, text="Load Initial Conditions", command=self.select_file)
        self.load_button.pack(pady=10)

        self.save_button = tk.Button(self.root, text="Save Changes", command=self.save_file, state=tk.DISABLED)
        self.save_button.pack(pady=10)

        self.saveas_button = tk.Button(self.root, text="Save New Configuration", command=self.save_new_file, state=tk.DISABLED)
        self.saveas_button.pack(pady=10)

        self.save_and_run_button = tk.Button(self.root, text="Save and Run Simulation", command=self.save_and_run)
        self.save_and_run_button.pack(pady=10)

        self.editor_frame = tk.Frame(self.root)
        self.editor_frame.pack(pady=10)

        self.load_file()

    def load_file(self):
        if self.filepath:
            self.config.read(self.filepath)
            self.render_editor()

    def select_file(self):
        self.filepath = filedialog.askopenfilename(filetypes=[("INI files", "*.ini")])
        self.load_file()

    def save_new_file(self):
        filepath = filedialog.asksaveasfilename(defaultextension=".ini", initialdir="./data")
        if filepath:
            self.filepath = filepath
            self.save_file()

    def save_and_run(self):
        self.save_file()
        if os.path.isfile(self.runfile):
            try:
                result = subprocess.run(["bash", self.runfile])
            except Exception as e:
                print(e)

    def render_editor(self):
        # Reset the editor.
        for widget in self.editor_frame.winfo_children():
            widget.destroy()

        # Get each section in the .ini file and create a label
        for section in self.config.sections():
            label = tk.Label(self.editor_frame, text=f"[{section}]")
            label.pack(anchor="w")

            # Get each key, value pair from the .ini file and create an entry box for them.
            for key, value in self.config.items(section):
                frame = tk.Frame(self.editor_frame)
                frame.pack(fill="x", pady=2)

                key_label = tk.Label(frame, text=key, width=15)
                key_label.pack(side="left")

                value_entry = tk.Entry(frame)
                value_entry.insert(0, value)
                value_entry.pack(fill="x", expand=True, padx=5)
                value_entry.config(state=tk.NORMAL)

                frame.section = section
                frame.key = key
                frame.value_entry = value_entry

        self.save_button.config(state=tk.NORMAL)
        self.saveas_button.config(state=tk.NORMAL)

    def save_file(self):
        for frame in self.editor_frame.winfo_children():
            if hasattr(frame, 'section') and hasattr(frame, 'key'):
                section = frame.section
                key = frame.key
                value = frame.value_entry.get()
                self.config.set(section, key, value)

        with open(self.filepath, 'w') as ini_file:
            self.config.write(ini_file)

if __name__ == "__main__":
    root = tk.Tk()
    app = Launcher(root)
    root.mainloop()
    

