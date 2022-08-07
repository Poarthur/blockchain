import subprocess
import platform
import shutil
import os
import sys

def install_cmake():
    if(platform.system() == "Windows"):
        path = os.path.dirname(sys.executable)
        os.system(path + "/Tools/scripts/win_add2path.py")
        subprocess.run("pip3 install cmake", shell=True)
    if(platform.system() == "Linux"):
        subprocess.run("sudo apt-get -y install cmake", shell=True)
    if(platform.system() == "Darwin"):
        subprocess.run("brew install cmake", shell=True)

#shell commands
try:
    subprocess.run("cmake --version", shell=True, check=True, capture_output=True)
except subprocess.CalledProcessError:
    print("You need to install CMake to continue: https://cmake.org/install")
    print("Install it right now? (y/n): ")
    answer = input()
    if(answer == 'y'):
        install_cmake()
    else:
        exit()
try:
    subprocess.run("conan --version", shell=True, check=True, capture_output=True)
except subprocess.CalledProcessError:
    print("You need to install Conan to continue: https://conan.io")
    print("Install it right now? (y/n): ")
    answer = input()
    if(answer == 'y'):
        subprocess.run("pip3 install conan", shell=True)
    else:
        exit()

subprocess.run("mkdir build", shell=True)
subprocess.run("conan install . --build missing", shell=True)
subprocess.run("cd ./build && cmake ..", shell=True)
print("Build the project? (y/n): ")
answer = input()
if(answer == 'y'):
    shutil.rmtree("./blockchain", ignore_errors=True)
    subprocess.run("cd ./build && cmake --build .", shell=True)
    subprocess.run("./build/bin/project_tests", shell=True)
    shutil.rmtree("./blockchain", ignore_errors=True)
else:
    exit()
