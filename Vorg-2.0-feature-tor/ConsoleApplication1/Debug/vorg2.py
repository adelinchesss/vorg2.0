import tkinter as tk
import time
from PIL import Image, ImageTk
import os
import subprocess

class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("vorg2")
        self.geometry("1400x700")
        self.create_widgets()

    def create_widgets(self):
        # создаем поля ввода
        self.func_label = tk.Label(self, text='функция f(x):')
        self.func_entry = tk.Entry(self, width=30)
        
        # записываем функцию в строчку
        # self.func = str(self.func_entry.get()) ************************************************************************

        self.num_plots_label=tk.Label(self, text='количество графиков:')
        self.num_plots_entry = tk.Entry(self, width=10)

        # записываем количество графиков
        # self.num = int(self.num_plots_entry.get()) *******************************************************************

        self.reg_labels = [tk.Label(self, text=f'размер регистра {i} графика:') for i in range(1, 6)]
        self.reg_entries = [tk.Entry(self, width=10) for i in range(5)]

        # нужно сохранить количество регистров для каждого графика ******************************************************

        self.radio_var = tk.IntVar()
        self.radio_var.set(1)
        self.v1 = tk.Radiobutton(self,
                                 text = 'Единичный квадрат',
#                                 command = self.radio_var,
                                 variable = self.radio_var,
                                 value = 1)
        self.v2 = tk.Radiobutton(self,
                                 text = 'Тор',
#                                 command = self.radio_var,
                                 variable = self.radio_var,
                                 value = 2)
        self.v1.pack()
        self.v2.pack()

        self.radio_var2 = tk.IntVar()
        self.radio_var2.set(1)
        self.v3 = tk.Radiobutton(self,
                                 text = 'Отображение Мона',
#                                 command = self.radio_var,
                                 variable = self.radio_var2,
                                 value = 1)
        self.v4 = tk.Radiobutton(self,
                                 text = 'Другое отображение',
#                                 command = self.radio_var,
                                 variable = self.radio_var2,
                                 value = 2)
        self.v3.pack()
        self.v4.pack()

        # создаем чекбоксы
        #self.checkbox1_var = tk.BooleanVar()
        #self.checkbox2_var = tk.BooleanVar()
        #self.checkbox3_var = tk.BooleanVar()
        #self.checkbox4_var = tk.BooleanVar()
        #self.checkbox1 = tk.Checkbutton(self, text="Единичный квадрат", variable=self.checkbox1_var)
        #self.checkbox2 = tk.Checkbutton(self, text="Тор", variable=self.checkbox2_var)
        #self.checkbox3 = tk.Checkbutton(self, text="Отображение Мона", variable=self.checkbox3_var)
        #self.checkbox4 = tk.Checkbutton(self, text="Другое отображение", variable=self.checkbox4_var)

        # создаем кнопку
        self.button = tk.Button(self, text="Построить график", command=self.open_png)
        # self.button_save = tk.Button(self, text="сохранить данные", command=self.save_file) *****************************************

        # располагаем элементы на форме
        self.func_label.place(x=5, y=5)
        self.func_entry.place(x=200, y = 5)
        self.num_plots_label.place(x=5, y = 30)
        self.num_plots_entry.place(x=200, y = 30)
        for i in range(5):
            self.reg_labels[i].place(x=5, y =55 + i*30)
            self.reg_entries[i].place(x=200, y = 55 + i*30)

        self.v1.place(x=5,y=205)
        self.v2.place(x=5,y=235)
        self.v3.place(x=5,y=265)
        self.v4.place(x=5,y=295)
        self.button.place(x=5,y=325)
        # self.button_save.place(x=5,y=295) **********************************************************************************
        image = Image.open("empty.png")
        photo = ImageTk.PhotoImage(image)
        self.image_label = tk.Label(self , image=photo)
        self.image_label.image = photo
        self.image_label.pack()
    # Открываем файл и записываем в него значения полей ввода и состояния чекбоксов
    def save_file(self):
        with open("config.txt", "w") as file:
            if self.checkbox2_var.get():
                file.write(f"1\n")
            else:
                file.write(f"0\n")
        with open("number_graphs.txt", "w") as file:
            file.write(f"{self.num_plots_entry.get()}\n")

    def open_png(self):
        with open(os.getcwd()+"\pyconfig.txt", "w") as file:
            if self.radio_var.get() == 1:
                fig = 1
            else:
                fig = 2

            if self.radio_var2.get() == 1:
                otobr = 1
            else:
                otobr = 2

            file.write(self.func_entry.get())
            file.write(";")
            file.write(str(fig))
            file.write(";")
            file.write(str(otobr))
            file.write(";")
            file.write(self.num_plots_entry.get())
            file.write(";")
            for i in range(0, int(self.num_plots_entry.get())):
                file.write(self.reg_entries[i].get())
                if i != int(self.num_plots_entry.get()) - 1:
                    file.write(";")
        print(os.getcwd()+"\ConsoleApplication1.exe")
        time.sleep(0.1)
        pop1 = subprocess.Popen(os.getcwd()+"\ConsoleApplication1.exe", stdout=subprocess.PIPE)
        out1 = pop1.stdout.read()
        print(out1)
        #здесь можно использовать опции для открытия нужного изображения
        image1 = Image.open(os.getcwd()+"\image.png")
        #new_size = (Image.size[0] // 2, Image.size[1] // 2)
        resized_image = image1.resize((600,600), Image.ANTIALIAS)
        resized_image.save("resized_image.png")
        image1 = Image.open("resized_image.png")
        photo1 = ImageTk.PhotoImage(image1)
        #label = tk.Label(self, image=photo)
        #label.image = photo
        #label.pack()
        self.image_label["image"] = photo1
        self.image_label.image = photo1
        self.image_label.pack()
    
   # def run_file():
    #    os.system("g++ main.cpp -o main && ./main")


if __name__ == "__main__":
    app = App()
    app.mainloop()