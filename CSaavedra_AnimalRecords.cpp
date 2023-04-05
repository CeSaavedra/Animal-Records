#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;
/**
* Cesar Saavedra
* September 22, 2022
*
* This program utilizes Vectors using a Structure. This program uses NO
* array notation. This program shows the ability of using a dynamically sized
* array known as a vector. This program utilizes selection sort and binary search
* to manipulate a vector.
*/


//Constants
//Used for validating variables
const int MENU_MIN = 1;
const int MENU_MAX = 5;
const int STRING_MAX = 20;
const int COUNT_MIN = 1;
const int ENDANGER_MAX = 100;

//Used for the loop menu
const int ADD_ANIMAL = 1;
const int DISPLAY_ANIMAL = 2;
const int SEARCH_ANIMAL = 3;
const int ENDANGERED_LIST = 4;
const int QUIT = 5;

//Used for calculations
const int ONE = 1;
const int TWO = 2;

//Structure 
struct Animal {
	char animalType[STRING_MAX] = "none";
	int animalCount = 0;
	bool endangerStatus = false;
};

//Function Prototypes
void displayTitle();
void addRecord(vector<Animal>& list);
void displayRecord(const vector<Animal> list);
bool validateName(vector<Animal> list, char animalTested[]);
void displayEndangered(const vector<Animal> list);
void selectionSort(vector<Animal>& list);
void binarySearch(vector<Animal> list);

//Functions
//Returns void, Takes no parameter. Displays title
void displayTitle() {
	cout << "\n\tWelcome to my Animal Count Vector Program\n\n" << endl;
}
//Returns void, takes vector PbR. Prompts user for animal type & count until finished.
void addRecord(vector<Animal>& list) {

	static int i = 0;		//Static integer that will hold the count of records no matter how many times the function it is in is used.
	bool loopKey = true;	//Loopkey that will be used to end while() loop
	bool repeatedValue = false; //Used to validated repeated names in vector
	bool validationKey = false; //Used for validation loop for input of animal type
	Animal tempObject;		//Temporary object to hold Animal elements

	char tempTested[STRING_MAX]; //Will hold lowercase animalTested to compare with "list.at(i).animalType"
	char animalBySubscript[STRING_MAX]; //Will hold the value of the animal type depending on the subscript of the vector

	cout << "\nYou have filled out " << i << " records.\n";		//Shows user how many records have been completed

	do {
		repeatedValue = false;
		validationKey = false;
		
		//Resets animalCount to 0 so it may pass the if() parameters
		tempObject.animalCount = 0;
		cin.ignore();

		while (!validationKey) { //Validation Loop for animal type input

			//Repeated value is set back to false - This loop only repeats if this value was set to true at one point
			repeatedValue = false;

			//Prompts user for animal type and stores in temporary object
			cout << "\nPlease enter an animal type (none to stop): ";
			cin.getline(tempObject.animalType, STRING_MAX);

			//Copies input into a cstring that will be used for testing
			strcpy_s(tempTested, tempObject.animalType);
			for (int y = 0; y < strlen(tempTested); y++) {
				tempTested[y] = tolower(tempTested[y]);
			}

		
			//Normal for loop to loop through elements within vector
			for (int i = 0; i < list.size(); i++) {

				//Copies "list.at(i).animalType" & converts to lowercase to be compared
				strcpy_s(animalBySubscript, list.at(i).animalType);
				for (int z = 0; z < strlen(animalBySubscript); z++) {
					animalBySubscript[z] = tolower(animalBySubscript[z]);
				}

				if (strcmp(tempTested, animalBySubscript) == 0) { //If the tested animal equals any other animal on the entire list
					//Prompts error message
					cout << "ERROR - You have typed an existing animal. Try again.\n";
					repeatedValue = true;
				}
			}

			if (!repeatedValue) { //If statement is responsible for ending the loop. This will only be skipped for repeated values
				//Animal type is validated for "none" and repeats
				loopKey = validateName(list, tempObject.animalType);
				validationKey = true;
			}
		}
		
		for (int y = 0; y < strlen(tempTested); y++) {
			tempTested[y] = tolower(tempTested[y]);
		}

		if (!loopKey) {
			//Invalid input was entered and it will reset the false input
			strcpy_s(tempObject.animalType, "none");
		}
		

		//If the animal type CString does NOT equal "none", the program continues as normal
		if (loopKey) {
			//While loop runs while the count is less than 1
			while (tempObject.animalCount < COUNT_MIN) {
				//Prompts user for animal count
				cout << "Please the animal type's count: ";
				cin >> tempObject.animalCount;

				//Displays error message if negative
				if (tempObject.animalCount < COUNT_MIN) {
					cout << "Invalid entry! Try again.\n";
				}
			}//End of validation loop

			//Checks IF endangered species;
			if (tempObject.animalCount < ENDANGER_MAX) {
				//Sets to true; If the IF statement is skipped, object keeps default "false"
				tempObject.endangerStatus = true;
			}else {
				tempObject.endangerStatus = false;
			}

			//Finally the object is pushed into the vector
			list.push_back(tempObject);

			//We can count this as a completed record
			i++;	

		}//End of if statement
	} while (loopKey); //End of while loop
} //End of function

//Returns void, takes constant vector; Displays records to user.
void displayRecord(vector<Animal> list) {
	
	//Local cstring used to validate
	char noneChecker[STRING_MAX];

	selectionSort(list);

	//For loop iterates through each element within the vector
	for (int i = 0; i < list.size(); i++) {
		
		cout << "\n";
		// Copies animal type into another separate Cstring that is then converted to all lowercase and
		// used to validate whether the record about to be displayed is "none" or not.
		strcpy_s(noneChecker, list.at(i).animalType); //Copy function
		for (int x = 0; x < strlen(noneChecker); x++) { //Sets entire cstring to lower case
			noneChecker[x] = tolower(noneChecker[x]);
		}

		//The record will be displayed as long as the animal type is anything BUT none.
		if (strcmp(noneChecker, "none") != 0) {

			//Displays animal type & count
			cout << "\nAnimal: " << list.at(i).animalType;
			cout << "\nHas a count of: " << list.at(i).animalCount;

			//Checks whether to display an endanger warning or not
			if (list.at(i).endangerStatus) {
				cout << "\nThis animal is endangered!\n";
			}
			else {
				cout << "\nThis animal is NOT endangered!\n";
			}
		}
	}
}
//Returns boolean value, Takes vector & cstring within parameters. Validates for "none" & repeated values
bool validateName(vector<Animal> list, char animalTested[]) {

	char noneChecker[STRING_MAX]; //Will hold lowercase animalTested to compare with "none"

	//Copies animalTested & converts to lowercase to be compared
	strcpy_s(noneChecker, animalTested); 
	for (int x = 0; x < strlen(noneChecker); x++) { 
		noneChecker[x] = tolower(noneChecker[x]);
	}

	//Normal for loop to loop through elements within vector
	for (int i = 0; i < list.size(); i++) {
		//If the tested animal equals "none"
		if (strcmp(noneChecker, "none") == 0) {
			
			cout << "You have typed none. Returning to menu.\n";
			return false;
		}else {
		}
	}
	//Animal Type can now be validated since it has not stopped at the other if statements
	return true;
}
//Returns void; Uses vector within parameters; Selection Sort algorithm; All Array notation is from C-Strings
void selectionSort(vector<Animal>& list) {
	//2 Cstring local variables
	char maxValue[STRING_MAX];
	char currentValue[STRING_MAX];

	//For loop goes through array until second to last element
	for (int i = 0; i < list.size() - ONE; i++) {

		//Max variable within first for loop
		int max = i;

		//For loop that goes through each element to the next
		for (int x = i + ONE; x < list.size(); x++) {

			//Duplicate procedures of turning list.at( ).animalType to lowercase JUST for this test
			//Reasoning: " a < Z " Upper case characters are prioritized over lower case in comparisons.
			strcpy_s(maxValue, list.at(max).animalType);
			for (int y = 0; y < strlen(maxValue); y++) { //Max value animal type
				maxValue[y] = tolower(maxValue[y]);
			}
			strcpy_s(currentValue, list.at(x).animalType);
			for (int z = 0; z < strlen(currentValue); z++) { //Iterated animal type based on for loop counter
				currentValue[z] = tolower(currentValue[z]);
			}

			//If the max is greater than the x subscript
			if (currentValue[0] < maxValue[0]) {
				//New Max
				max = x;
			}
		}
		//If the max is not the same as i
		if (max != i) {
			//Swaps elements using a temp int C-String
			char tempInt[STRING_MAX];
			strcpy_s(tempInt, list.at(max).animalType);
			strcpy_s(list.at(max).animalType, list.at(i).animalType);
			strcpy_s(list.at(i).animalType, tempInt);
		}
	}
}
//Returns void; Uses vector within parameters; Binary Search; All Array notation is from C-Strings
void binarySearch(vector<Animal> list) {

	//C-Strings to hold animal types from objects within the vector
	char inputSearch[STRING_MAX];
	char currentAnimal[STRING_MAX];

	//Local variables to control range of the vector size the binary search wishes to focus on
	int mid = 0;
	int begin = 0;
	int end = list.size() - ONE;

	//Holds the index where the binary search located the target
	int indexFound = 0;

	//Controls the while loop
	bool searched = false;

	//Prompts user to input their search value
	cin.ignore();
	cout << "\nPlease enter the name of the animal you are looking for: ";
	cin.getline(inputSearch, STRING_MAX);

	selectionSort(list); //Vector must be sorted before binary search can be performed

	//Sets input to lowercase
	for (int x = 0; x < strlen(inputSearch); x++) {
		inputSearch[x] = tolower(inputSearch[x]);
	}
	//While loop representing the Binary Search algorithm
	while (end >= begin && !searched) {

		//Median subscript within the vector is located each iteration
		mid = (begin + end) / TWO;

		//Current Animal CString is copied; This represents the cstring within the object in the "mid" subscript
		strcpy_s(currentAnimal, list.at(mid).animalType);
		for (int y = 0; y < strlen(currentAnimal); y++) {	//Set to lowercase to be compared
			currentAnimal[y] = tolower(currentAnimal[y]);
		}

		//If the search key has been found
		if (strcmp(inputSearch, currentAnimal) == 0) {
			indexFound = mid; //Store the index in which it has been found
			searched = true; //Exit while loop
		}//If Search key is greater than middle value
		else if (strcmp(currentAnimal, inputSearch) < 0) {
			begin = mid + ONE;
		}//If Search key is less than middle value
		else if (strcmp(inputSearch, currentAnimal) < 0) {
			end = mid - ONE;
		}
	}//Exit binary search

	if (searched) { //If the animal has been found using binary search
		cout << "Your animal, " << list.at(indexFound).animalType << " , has been found!\n";

		//Displays animal type, count, and endangered status
		cout << "\nAnimal: " << list.at(indexFound).animalType;

		cout << "\nHas a population of: " << list.at(indexFound).animalCount;
		if (list.at(indexFound).endangerStatus) {
			cout << "\nThis animal is endangered!\n";
		}
		else {
			cout << "\nThis animal is NOT endangered!\n";
		}
	}
}

//Returns void, Takes constant vector parameters. Displays ONLY endangered animals from vector.
void displayEndangered(const vector<Animal> list) {
	
	cout << "\n";
	//Range based for-loop
	for (const Animal i: list) {
		//IF the endangered status = true
		if (i.endangerStatus) {
			//Display animal
			cout << "Animal: " << i.animalType << " is endangered!!" << endl;
		}
	}
	cout << "\n";

}


int main() { // MAIN FUNCTION

	//Local variables
	int menuChoice = 0;

	//Vector of Animal type containing 6 Animal objects
	vector<Animal> animals = {
		{"California Puma", 2005,false},
		{"Bengal Tiger", 97,true},
		{"White Rhino",45,true},
		{"California Condor",275,false},
		{"Grey Wolf",77,true},
		{"Three Toed Sloth",1725,false}
	};

	displayTitle();

	//Menu loop
	while (menuChoice != QUIT) { // Loop runs as long as the user does not select the Quit option.

		//While loop runs while the menuChoice integer is out of range.
		while (menuChoice < MENU_MIN || MENU_MAX < menuChoice) {
			//Prompts menu
			cout << "\n" << ADD_ANIMAL << ". Add animals\n" << DISPLAY_ANIMAL << ". Display animals\n" << SEARCH_ANIMAL << ". Search for animal\n" <<
				ENDANGERED_LIST << ". Display endangered animals\n" << QUIT << ". Quit\n\nEnter the menu choice: ";
			cin >> menuChoice;

			//Displays error message if not within range
			if (menuChoice < MENU_MIN || MENU_MAX < menuChoice) {
				cout << "Invalid entry! Try again.\n";
			}
		}//End of validation loop


		//When menu option is verified - Program moves onto this switch statement.
		switch (menuChoice) {
		case ADD_ANIMAL:
			addRecord(animals);
			menuChoice = 0; //Set to 0 to allow user to enter in a new menu option
			break;
		case DISPLAY_ANIMAL:
			displayRecord(animals);
			menuChoice = 0; //Set to 0 to allow user to enter in a new menu option
			break;
		case SEARCH_ANIMAL:
			binarySearch(animals);
			menuChoice = 0; //Set to 0 to allow user to enter in a new menu option
			break;
		case ENDANGERED_LIST:
			displayEndangered(animals);
			menuChoice = 0; //Set to 0 to allow user to enter in a new menu option
			break;

		case QUIT:
			//Clears vector before exiting the program
			animals.clear();
			break;
			
		default:
			//Program should not need to go here as menuChoice is verified - Added for extra precaution
			break;
		} // End of switch statement

	}//End of menu loop


	cout << "\n\nThank you for using my program!\n";
}
