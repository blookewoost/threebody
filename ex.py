import tkinter as tk
from tkinter import filedialog, messagebox
import configparser

class IniEditor:
    def __init__(self, root):
        self.root = root
        self.root.title("INI File Editor")

        self.file_path = None
        self.config = configparser.ConfigParser()

        self.create_widgets()

    def create_widgets(self):
        self.load_button = tk.Button(self.root, text="Load INI File", command=self.load_file)
        self.load_button.pack(pady=10)

        self.save_button = tk.Button(self.root, text="Save Changes", command=self.save_file, state=tk.DISABLED)
        self.save_button.pack(pady=10)

        self.editor_frame = tk.Frame(self.root)
        self.editor_frame.pack(pady=10)

    def load_file(self):
        self.file_path = filedialog.askopenfilename(filetypes=[("INI files", "*.ini")])
        if self.file_path:
            self.config.read(self.file_path)
            self.render_editor()

    def render_editor(self):
        for widget in self.editor_frame.winfo_children():
            widget.destroy()

        for section in self.config.sections():
            section_label = tk.Label(self.editor_frame, text=f"[{section}]")
            section_label.pack(anchor="w")

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

    def save_file(self):
        for frame in self.editor_frame.winfo_children():
            if hasattr(frame, 'section') and hasattr(frame, 'key'):
                section = frame.section
                key = frame.key
                value = frame.value_entry.get()
                self.config.set(section, key, value)

        with open(self.file_path, 'w') as configfile:
            self.config.write(configfile)

        messagebox.showinfo("Info", "Changes saved successfully.")

if __name__ == "__main__":
    root = tk.Tk()
    app = IniEditor(root)
    root.mainloop()
