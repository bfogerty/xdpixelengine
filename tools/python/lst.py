import os

    # getting the current work directory (cwd)
thisdir = os.getcwd()
    # r=root, d=directories, f = files
for r, d, f in os.walk(thisdir):
    for file in f:
        print(os.path.join(r, file))