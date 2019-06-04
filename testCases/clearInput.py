import os

folder = "input/"
for file in os.listdir(folder):
    file_path = os.path.join(folder, file)
    os.unlink(file_path)












