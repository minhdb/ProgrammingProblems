#!/usr/bin/env python


"""This program is created for the purpose of moving solutions to solved
problems into its correct directory.

The program will look for
Minh Bui.
"""

# Importing libaries and modules

import os
import re

def main():
    # Looking for UVA solutions.

    # Looking for TopCoder solutions.

    # Looking for SPOJ solutions.

    # Looking for CodeForces solutions.

    # ...


    # Pseudo-code for the program:
    #   For each of the OJs:
    #       Look for all the files with the suffix of the OJs. Decide what OJ the solution belongs to.
    #       Check the files' programming languages. If C++, move to C-C++ sub-directory. If Java, move to
    #       the Java sub-directory. If the extension is unknown, create a new folder in the OJ folder.
    #       To know what kind of programming language it is, look up the file's extension in a dictionaries.

    # Defining variables.
    root = "./"

    lang_map = dict()
    lang_map[".cpp"] = "C/C++"
    lang_map[".java"] = "Java"
    lang_map[".c"] = "C/C++"

    ojs_map = dict()
    ojs_map["SRM"] = list()
    ojs_map["UVA"] = list()
    ojs_map["SPOJ"] = list()
    ojs_map["CF"] = list()

    files = os.listdir(root)
    tc = []
    uva = []
    spoj = []
    for file in files:
        if "SRM" in file:
            ojs_map["SRM"].append(file)

        # Check for the length of the file in case the file is a directory
        # containing the solutions.

        if "UVA" in file and len(file) > 3:
            ojs_map["UVA"].append(file)
        if "SPOJ" in file and len(file) > 4:
            ojs_map["SPOK"].append(file)
        if "CF" in file and len(file) > 2:
            ojs_map["CF"].append(file)

    # Regex for extracting the file's extension.
    extRegex = ""
    regexObj = re.compile(extRegex)
    for key in ojs_map:




    return

if __name__ == "__main__":
    main()
