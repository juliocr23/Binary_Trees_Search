/*
 * Main.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: julio
 *     Purpose: The purpose of this program is to analyse a text document
 *               and perform some statistic on it.
 *     NOTE: Professor I figured out why the error was happening, 
             for some reason when you go to the next line it just goes wrong.
			 Try running the program with somethig like
			
			 Hello cookie
			 hello my friend
			 I just want friend
			 totally crazy ha!
			 I just want to say something.

			 But if you do the following it work!

			 Hello cookie hello my friend I just want friend totally crazy ha! I just want to say something.

			 I fixed it by having a range, since the unicode for letters that are lower case goes from
			 x >= 97 && x <=122, I will append that letter inside the if. My guess is that
			 it was reading the enter key because that's what you use to go to the next line. 
 */

#include <iostream>
#include <fstream>
#include <string>
#include "BSearchTree.h"
#include "BSearchTree.cpp"


int numberOfWords = 0;
int numberOfUniqueWords = 0;
int uniqueWordsGreaterThn3 = 0;
int totalLength = 0;
int numberOfSentences = 0;
int numberOfWordsGreaterThn3 = 0;
char index;
bool flag = false;
bool usedOften = false;
std::ofstream outputFile;

void    putWordsIntoTree(std::ifstream&,BSearchTree<std::string>&); //Read the file and put all the words into the tree and return the number of sentence
void    analyzeText(std::string&, int&);
void    printStaticalSummary();
void    printIndexOfUniqueWords(std::string&,int&);
void    printWordsUsedTooOften(std::string&, int&);
void    printStyleWarning();

int main() {

	//Get the file that the user wants to analyze
	std::string fileName;
	std::cout << "Enter file's name for analysing text\n";
	std::cout << "Example: file.txt\n";
	std::cin >> fileName;

	std::ifstream inputFile(fileName);
	BSearchTree<std::string> tree;

	//Check that the file was found
	if (!inputFile)
		std::cout << "CANNOT FIND FILE";
	else {
		//Get the name of the file for writing the analysis
		std::string analysisFile;
		std::cout << "\n\nEnter a name for output file\n";
		std::cout << "Example: file.txt\n";
		std::cin >> analysisFile;

		//Create and open file for writing
	    outputFile.open(analysisFile);     

		//Check that the file was created successfully
		if (!outputFile)
			std::cout << "CANNOT CREATE FILE";
		else {
			putWordsIntoTree(inputFile, tree);
			tree.inorder(analyzeText);

			printStaticalSummary();

			outputFile << "INDEX OF UNIQUE WORDS\n\n";
			tree.inorder(printIndexOfUniqueWords);

			printStyleWarning();
			tree.inorder(printWordsUsedTooOften);
		
			//Check if words were not used often 
			if (!usedOften)
				outputFile << "NONE\n";

			//Make sure that the denominator is never 0
			if (numberOfSentences != 0) {
				if ((numberOfWords / numberOfSentences) > 10) {
					outputFile << "AVERAGE SENTENCE LENGTH TOO LONG – "
						       << (numberOfWords / numberOfSentences) << "\n";
				}
			}

			//Make sure that the denominator is never 0
			if (numberOfWords != 0) {
				if ((totalLength / numberOfWords) > 5) {
					outputFile << "AVERAGE WORD LENGTH TOO LONG – "
						<< (totalLength / numberOfWords) << "\n";
				}
			}

			std::cout << "Done writing analysis!";
			inputFile.close();
			outputFile.close();
		}
	}


	//Prevent visual studio from closing output
	while (true);
	return 0;
}

void putWordsIntoTree(std::ifstream& file, BSearchTree<std::string>& tree) {

	//Put the words into the tree
	std::string word = "";
	char temp;

	//While it is not the end of the file keep reading
	while (file.get(temp)) {

		//If character is a dot increase number of sentences
		if (temp == '.' || temp == '?' ||
			temp == ',' || temp == ';' ||
			temp == ':' || temp == '!') {
			numberOfSentences++;
		}
		//If it is a letter or a ' insert
		else if ( temp == '’' || ((int)temp >= 97 && (int)temp <=122))
			word += tolower(temp);
		//otherwise insert word in to the tree and empty word
		else {
			tree.insert(word);
			word = "";
		}
	}
	//Insert last word into the tree.
	tree.insert(word);
}

void analyzeText(std::string& info, int& count) {

	numberOfWords += count;			  //Get the number of words
	totalLength += info.length();     //Get the total length of all the words.
	numberOfUniqueWords++;		     //Get the number of unique words

	if (info.length() > 3) {
		uniqueWordsGreaterThn3++;    //Get the number of unique words greater than 3.
		numberOfWordsGreaterThn3 += count;
	}
}

void printStaticalSummary() {

	outputFile << "STATICAL SUMMARY:\n\n";

	outputFile << "Number of words: "
			   << numberOfWords << "\n";

	outputFile << "Number of unique words: "
			   << numberOfUniqueWords << "\n";

	outputFile << "Number of unique words greater than three: "
		<< uniqueWordsGreaterThn3 << "\n";

	if (numberOfWords != 0) {
		outputFile << "Average word length:"
			       << (totalLength / numberOfWords)
			       << " characters " << "\n";
	}

	if (numberOfSentences != 0) {
		outputFile << "Average Sentence length:"
			       << (numberOfWords / numberOfSentences)
			       << " words" << "\n";
	}
		outputFile << "\n\n";
	
}

void printIndexOfUniqueWords(std::string& info, int& count) {

		if (!flag && index != info[0]) {
			char c = toupper(info[0]);
			outputFile << "\n\n" << c << "\n";
			outputFile<< "---------------\n";
			flag = true;
			index = info[0];
		}
		else if (index != info[0]) {
			char c = toupper(info[0]);
			index = info[0];
			outputFile << "\n\n" << c << "\n";    //Print index
			outputFile << "---------------\n";
			flag = false;
		}
			outputFile << info << "\n";		//Print word
}

void printStyleWarning() {
	outputFile << "\n\nSTYLE WARNINGS\n";
	outputFile << "-------------------\n\n";
	outputFile << "WORDS USED TOO OFTEN:\n\n";
}

void    printWordsUsedTooOften(std::string& info, int& count) {

	if (numberOfWordsGreaterThn3 != 0 && numberOfWordsGreaterThn3 != 1) {
		int percent = (count / numberOfWordsGreaterThn3) * 100;
		
		//Print the word if the percent usage is greater than 5
		if (percent > 5) {
			outputFile << info << "\n";
			usedOften = true;
		}
	}
}






