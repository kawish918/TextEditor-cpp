#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<iomanip>
#include<conio.h>

using namespace std;


void loadingScreen() {
    int progressBarWidth = 10;
    
    cout << setw(45) << "\n\n\n\n\n\n\n\n\n\n\n";

    cout << setw(20) << "Loading: ";
    cout.flush(); 

    for (int i = 0; i <= progressBarWidth; ++i) {
        cout << "\xDB\xDB\xDB\xDB\xDB\xDB"; 
        cout.flush();

       for (int j = 0; j < 100000000; ++j) {
            
        }
    }
}
class FileOperation {
public:
    virtual void performOperation() = 0;
};

class CreateFileOperation : public FileOperation {
public:
	
    void performOperation() override {
        cout << endl << "Enter name of file: ";
        string filename;
        cin.ignore();
        getline(cin, filename);

        ofstream myfile(filename + ".txt");
        myfile.close();
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	    
	    loadingScreen();
	    
	    system("cls");
	    
	    cout << "\n\n\n\n\n";
	    
	    cout << setw(20) << "File named " << filename << " Created Successfully.\n\n"; 
	    
        cout << setw(20) << "Press any key to continue...";
        
        system("cls");
        
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin.ignore();
        cin.get();
    }
};

class ReadFileOperation : public FileOperation {
public:
    void performOperation() override {
        cout << endl << "Enter name of file: ";
        string filename;
        cin >> filename;
        
        loadingScreen();
        system("cls");
        

        ifstream myfile(filename + ".txt");
        if (myfile.is_open()) {
            string line;
            
            cout << "Displaying content of file " << filename; 
            
            cout << "\n\n";
            
            while (getline(myfile, line)) {
                cout << line << endl;
            }
            myfile.close();
            
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

            cout << endl << "End of File. Press any key to continue...";
            
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            
            cin.ignore();
            cin.get();
            
            system("cls");
            
        } else {
        	
        	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            
            cout << "File Not Found" << endl << endl;
            cout << "Press any key to continue...";
            
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            
            cin.ignore();
            cin.get();
        }
    }
};

class EmptyFileOperation : public FileOperation {
public:
    void performOperation() override {
        cout << endl << "Enter name of file: ";
        string filename;
        cin >> filename;

        ofstream myfile((filename + ".txt"), ios::out | ios::trunc); // Open the file in truncation mode
        myfile.close();
        loadingScreen();
        
        system("cls");
        
        cout << "\n\n\n";
        
        cout << setw(20) << "File " << filename << " Emptied Successfully." << endl << endl;
        cout << setw(20) << "Press any key to continue...";
        
        cin.ignore();
        cin.get();
        system("cls");
    }
};

class DeleteFileOperation : public FileOperation {
public:
    void performOperation() override {
        cout << endl << "Enter name of file: ";
        string filename;
        cin >> filename;
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            
        loadingScreen();
        
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        
        system("cls");

        string filePath = filename + ".txt";
        if (DeleteFile(filePath.c_str())) {
        	
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            
        cout << "File Deleted Successfully" << endl;
        
        system("cls");
        
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        
        } else {
        	
        	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            
            cout << "\n\n\n";
            
        cout << setw(20) << "File " << filename << " Not Found." << endl;
        
        
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        
        }
        cout << "Press any key to continue...";
        
        system("cls");
        
        cin.ignore();
        cin.get();
        
        
    }
};

class WriteToFileOperation : public FileOperation {
public:
    void performOperation() override {
        cout << endl << "Enter name of file: ";
        string filename;
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	    
        cin >> filename;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cout << endl << "Enter text to write to file: (Enter SAVE to complete)" << endl;
        string text;
        string line;

        cin.ignore();
        
        while (getline(cin, line)) {
            if (line.size() >= 4 && line.substr(line.size() - 4) == "SAVE") {
                text += line.substr(0, line.size() - 4);
                break;
            } else {
                text += line + "\n";
            }
        }

        ofstream myfile((filename + ".txt"), ios::app);
        myfile << text;
        myfile.close();
        
		HANDLE EConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); 
	    
        cout << "File Updated Successfully" << endl << endl;
        cout << "Press any key to continue...";
        
        system("cls");
        
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        
        cin.ignore();
        cin.get();
        
        
    }
};

 class CopyFileOperation : public FileOperation {
public:
    void performOperation() override {
        cout << endl << "Enter name of file to copy from: ";
        string sourceFilename;
        cin.ignore();
        getline(cin, sourceFilename);

        ifstream sourceFile(sourceFilename + ".txt");
        if (sourceFile.is_open()) {
            string line;
            string text;
            while (getline(sourceFile, line)) {
                text += line + "\n";
            }
            sourceFile.close();

            cout << endl << "Enter name of file to copy to: ";
            string destinationFilename;
            getline(cin, destinationFilename);

            ofstream destinationFile((destinationFilename + ".txt"), ios::app);
            destinationFile << text;
            destinationFile.close();

            cout << "File Copied Successfully" << endl << endl;
            cout << "Press any key to continue...";
            
            cin.ignore();
            cin.get();
        } else {
            cout << "Source File Not Found" << endl << endl;
            cout << "Press any key to continue...";
            
            system("cls");
        
            cin.ignore();
            cin.get();
            
           
        }
    }
};

void clearScreen() {
    system("CLS");
}

void menu() {
    clearScreen();
    int choice;
    
    
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    
    cout << "\n\n\n\n" << setw(55) << "Welcome to Text Editor" << endl << endl;

    while (true) {
    	
    	cout << "\n\n\n";
        cout <<  setw(50) << "Main Menu" << endl;
        cout <<  setw(55) << "--------------------" << endl;
        cout <<  setw(50) << "1. Create File" << endl;
        cout <<  setw(52) << "2. Write to File" << endl;
        cout <<  setw(53) << "3. Read from File" << endl;
        cout <<  setw(49) << "4. Empty File" << endl;
        cout <<  setw(50) << "5. Delete File" << endl;
        cout <<  setw(48) << "6. Copy File" << endl;
        cout <<  setw(46) << "7. Exit" << endl << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		cout <<  setw(50) << "Enter Choice: ";
        
        cin >> choice;
        
        system("cls");

        FileOperation* operation = NULL;

        switch (choice) {
            case 1:
                loadingScreen();
                operation = new CreateFileOperation();
                break;
            case 2:
                operation = new WriteToFileOperation();
                break;
            case 3:
                operation = new ReadFileOperation();
                break;
            case 4:
                operation = new EmptyFileOperation();
                break;
            case 5:
                operation = new DeleteFileOperation();
                break;
            case 6:
                operation = new CopyFileOperation();
                break;
            case 7: {
			
                //exit the program
                system("cls");
                
                cout << "\n\n\n\n\n\n";
                
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		        
                cout << setw(60) << "Exiting the Program... " << endl;
                cout << setw(50) << "BYE!" << endl;
                cout << setw(55) << "**Press Enter**" << endl;
                
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                
                exit(0);
            }
                
            default:
            	system("cls");
            	
            	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		        
		        cout << "\n\n\n\n\n\n\n\n" << setw(56) << "***********************************" << endl;
		        
		        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		        
		        HANDLE eConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		        
		        
                cout << "\n" << setw(60) << "*** Invalid choice. Please try again. ***" << endl;
                
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                
                HANDLE wConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                
               	cout << "\n" << setw(56) << "***********************************" << endl;
               	
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				
                Sleep(1500);
                system("cls");
                
                menu();
                
                continue;  //restart the loop
        }

        clearScreen();
        operation->performOperation();
        delete operation;
    }
}

int main() {

    menu();
   
    return 0;
}

