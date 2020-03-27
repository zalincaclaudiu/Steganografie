from tkinter import *
from tkinter import filedialog
import subprocess
from functools import partial
from PIL import Image,ImageTk
from os import path

root = Tk()
root.geometry("450x450+450+150")

def Crypt_process():
    msg_to_crypt=entry_1.get()
    try:
        subprocess.call([r'Pi_Proiect_Criptare.exe',msg_to_crypt,img_path])
    except Exception as e:
        print(e)
        return

    fav = len(msg_to_crypt) * 24 + 3
    total = path.getsize(img_path)

    label_size = Label(root, text='Text Length:')
    label_size.grid(row=6, column=0)
    entry_size = Entry(root)
    entry_size.insert(0, len(msg_to_crypt))
    entry_size.grid(row=6, column=1)

    label_bytes = Label(root, text='Bytes changed:')
    label_bytes.grid(row=7, column=0)
    entry_bytes = Entry(root)
    entry_bytes.insert(0, fav)
    entry_bytes.grid(row=7, column=1)

    label_integrity = Label(root, text='Image Integrity:')
    label_integrity.grid(row=8, column=0)
    entry_integrity = Entry(root)
    entry_integrity.insert(0, (1-fav/total)*100)
    entry_integrity.grid(row=8, column=1)


def Decrypt_process():
    entry_2.delete(0,'end')
    msg_to_get = subprocess.run([r'Pi_Proiect_Decrypt.exe'],capture_output=True)
    entry_2.insert(0,msg_to_get.stdout)

def Browse_picture():
    root.filename = filedialog.askopenfilename(initialdir=r"C:\Users\rbucur\PycharmProjects\UI_Pi", title="Select file",
                                               filetypes=(("jpeg files", "*.jpg"), ("all files", "*.*")))
    global img_path
    img_path = root.filename
    load = Image.open(root.filename)
    load = load.resize((250,250),Image.ANTIALIAS)
    render = ImageTk.PhotoImage(load)
    image = Label(root,image=render)
    image.image = render
    image.grid(row=4,column=0)

    entry_path = Entry(root)
    entry_path.insert(0,root.filename)
    entry_path.grid(row=2,column=1)

    label_size = Label(root,text='Image Size:')
    label_size.grid(row=5,column=0)
    entry_size = Entry(root)
    entry_size.insert(0, path.getsize(root.filename))
    entry_size.grid(row=5,column=1)

message_to_crypt=StringVar()
entry_1 = Entry(root,textvariable=message_to_crypt)
entry_2 = Entry(root)

cryptButton = Button(root, text="Crypting", fg="black",command=Crypt_process)
cryptButton.config(width=34)
decryptButton = Button(root, text="Decrypting", fg="black",command=Decrypt_process)
decryptButton.config(width=34)
pathButton = Button(root,text="Path to file", fg="black",command=Browse_picture)
pathButton.config(width=34)
decryptButton.grid(row=1,sticky=W)
cryptButton.grid(row=0,sticky=W)
pathButton.grid(row=2,sticky=W)
entry_1.grid(row=0, column=1, sticky=W)
entry_2.grid(row=1, column=1, sticky=W)

root.mainloop()
