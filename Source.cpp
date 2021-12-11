#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{

	bool usrInputValid = true; //for user input validation
	int usrInput; //take in user's input for menu option

	//loop through menu options
	//validate usr input using boolean and try catch
	while (usrInputValid) {
		cout << "Please choose from the following options:\n\n" << "1. Produce full list of items\n" << "2. Find quantity of item purchased today\n" << "3. View chart of all items purchased today\n" << "4. Exit Program\n" << endl;
		cin >> usrInput;

		
		
		if (usrInput == 1) {
			CallProcedure("ProduceList"); //case 1 call the ProduceList function in Python
		}
		else if (usrInput == 2) { 
			string wordInput; //get user input var

			cout << "Please enter the word you wish to find" << endl; 
			cin >> wordInput; //input user input

			int x = callIntFunc("FindFrequency", wordInput); // assign result to x
			
			if (x == 0) {
				continue;
			}
			else {
				cout << x << endl; //print x to console
			}

		}
		else if (usrInput == 3) {
			CallProcedure("CreateHistogram");//call the CreateHistogram python function
			vector<string> fileList;//create a vector to hold the file inputs
			ifstream inFS; // create input stream
			string fileLine; // create file variable
			//cout << "Opening frequency.dat file" << endl;

			inFS.open("frequency.dat"); //open file

			//if file is not open, error
			if (!inFS.is_open()) {
				cout << "could not open the file frequency.dat" << endl;
			}

			//cout << "reading lines from file" << endl;
			getline(inFS, fileLine); //get the line in file

			//while the input stream has not failed
			//get new line
			while (!inFS.fail()) {
				fileList.push_back(fileLine);
				getline(inFS, fileLine);			
			}

			for (int i = 0; i < fileList.size(); i++) {
				cout << i + 1 << ": " << fileList.at(i) << endl;
			}
			cout << endl;
			//if there is a failure before EOF, print error
			if (!inFS.eof()) {
				cout << "Input failure before reaching end of file" << endl;
			}
			//cout << "closing file" << endl;

			//close the file
			inFS.close();
			
			
		}
		else if (usrInput == 4) {
			cout << "Exiting Program" << endl;
			break;
		}
		else {
			cout << "You have entered an invalid response. Please try again." << endl;
			usrInputValid = false;
		}
		
		
	}
}