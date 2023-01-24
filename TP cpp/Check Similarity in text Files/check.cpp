#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

    std::string file1_path, file2_path;// Declaring variables for file paths
    
    std::string line1, line2;// Declaring variables for lines of text

    std::cout << "Please enter the repository path for the first file: ";// Ask for file1 path
    std::cin >> file1_path;

    std::cout << "Please enter the repository path for the second file: ";// Ask for file2 path
    std::cin >> file2_path;

    std::ifstream file1(file1_path);// Open file1
    std::ifstream file2(file2_path);// Open file2
    
    int countSimilarLines = 0;// Initialize count of similar lines
    int countAllLines=0;// Initialize count of all lines

    if (file1.is_open() && file2.is_open()) { // Check if files are open
        

        while (std::getline(file1, line1) && std::getline(file2, line2)) { // Get lines from files
            countAllLines++; // Increase count of all lines
            if (line1 == line2) { // Compare lines
                ++countSimilarLines; // Increase count if lines are equal

            }
        }

    }
    else {
        std::cout << "Error opening one or both files" << std::endl; // Print error if files are not open
    }
    

    
    if (countSimilarLines==countAllLines){ // Check similarity of files and print result
    	cout << "The two files are similar, Total lines number is " << countAllLines << endl;
    } else 
    	
    	if ( countSimilarLines >= countAllLines/2) {
        	cout << "The tow files are not fully similar but more the 50% are similar '" << countSimilarLines<< " of " << countAllLines << " lines are similar'"<< endl;
    }
    
    

    return 0;
}
