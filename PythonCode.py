import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

#declare function for ProduceList option 1
def ProduceList():
    f = open("CS210_Project_Three_Input_File.txt", "r") #open file
    Lines = (f.readlines()) #read the lines from the file
    
    d = {}

    #for each line
    #check to see if the line is already in dictionary
    #if so, increment line, if not create new line in dictionary
    for line in Lines:
        if line.strip() not in d:
            d[line.strip()] = 1
        else:
            d[line.strip()] += 1
        
    #for each key value pair, print the pair in dictionary
    for key, value in d.items():
        print(f"{key} : {value}")

    print("\n")

    f.close()

#declare function for FindFrequency option 2
def FindFrequency(v):
    f = open("CS210_Project_Three_Input_File.txt", "r") #open file
    Lines = (f.readlines()) #read the lines from the file
    
    d = {}

    #for each line
    #check to see if the line is already in dictionary
    #if so, increment line, if not create new line in dictionary
    for line in Lines:
        if line.strip() not in d:
            d[line.strip()] = 1
        else:
            d[line.strip()] += 1

    #check to see if v is in the list of keys
    #if not, print error
    #else loop through and print the corresponding value
    while (v.title() in d.keys()):
    
        #loop through the dictionary to match user input with a key
        for key, value in d.items():
            if (v.title() == key.title()):
                #print(value, "\n") #print the value
                return value
            else:
                continue
        break;
    #if the string is not in keys list, print error message
    if v.title() not in d.keys():
        print("\nYou have entered an invalid answer\n")
    
    f.close()
    return 0
    
#declare function for CreateHistogram
def CreateHistogram():
    f = open("CS210_Project_Three_Input_File.txt", "r") #open file
    Lines = (f.readlines()) #read the lines from the file
    
    d = {}

    #for each line
    #check to see if the line is already in dictionary
    #if so, increment line, if not create new line in dictionary
    for line in Lines:
        if line.strip() not in d:
            d[line.strip()] = 1
        else:
            d[line.strip()] += 1

    h = open("frequency.dat", "w") #open a new file to write to

    print("python function printing to new file the following:\n")
    #for each key value pair, write to the new file
    for key, value in d.items():
        h.write(f"{key} ")
        for i in range(value):
            h.write("*")
        h.write("\n")

    f.close()
    h.close()
