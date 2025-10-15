# CPP Based ESP32 Embedded Development Template.

> **Note:**  
> After cloning this template repository, follow these steps:
>
> 1. Delete the `.git` directory in the cloned repository.  
> 2. In VS Code, open the **ESP‑IDF Explorer** panel (on the left primary side bar).  
> 3. Click the **Advanced** dropdown menu, then choose **“Add .vscode subdirectory files”**.

# _ESP32-CPP-TEMPLATE_

## Project Structure:

The project **ESP32-CPP-TEMPLATE** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   ├── main.cpp               This file contains the main function
│   └── app_common.h           This file contains initialisation macros and base imports
└── README.md                  This is the file you are currently reading
```

The given template enforces C++ v20.