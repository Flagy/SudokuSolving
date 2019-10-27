import subprocess
import os

subprocess.call(["gcc", os.getcwd() + "/sudoku.c"])
subprocess.call(os.getcwd() + "/a.out")

