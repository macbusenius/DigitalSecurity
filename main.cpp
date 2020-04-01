/*

Program Name: MainAssignment.cpp
Class: ENSE496AE Digital Security
Group: B

Author: Mckenzie Busenius
        Han Gao

Professor: Dr. Yasser Morgan

Description: This program is the driver code to preform the required task list in the
             assignment list.

 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
//Shuffle Algorithm
#include "shuffleAlgorithm.h"

using namespace std;

// Function Protoypes
void generateRandomArray(long long int array[], long long int sharedKey, long long int randomNumberRange, int arraySize);
void printArray(long long int array[], int arraySize);
void generatePrimeNumberBank(string filename, long long int inputNumber);
void publicKey(int p, int g, long long int array[]);
void secretKey(int p);

int main() {
    /*
    Description: This is the compare routing to check files are the same.

    Files:  HerculesOS_RandomArray.txt
            MacOS_RandomArray.txt

            The contents of these files were run on two different operating systems:
                Linux x86_64
                MacOS

            to produce the same random number array.
     */
    fstream file1, file2;
    file1.open("HerculesOS_RandomArray.txt", ios::in);
    file2.open("MacOS_RandomArray.txt", ios::in);

    string stringFile1 = "";
    string stringFile2 = "";
    while(file1 >> stringFile1){
        file2 >> stringFile2;
    }
    if(stringFile1 == stringFile2){
        cout << "Files are same.";
        cout << endl;
    }else
        cout << "Files are not same.";
        cout << endl;
    file2.close();
    file1.close();

    //Variables
    int arraySize = 200;
    long long int randomNumberArray[arraySize];
    long long int sharedKey = 40618597;
    long long int bigInt = 9223372036854775807;
    int p = 0;
    int g = 0;
    int pk = 0;
    int a = 0;

    /*
    First Requirement:
        * Function that generates an array of size 200 of random numbers in the of big int.
        * It used a known seed value "sharedKey"
        * The values returned are the same on different OS's

        NOTE:
            Becuase of the condition of generating same results on multiple OS's the output of the function
            is cast to size ---> unsigned int.
            This is happening because of the C++ function rand() is implmented differently of
            on different OS's so it returns different results. So We had to use the srandom()
            and random() libraries to generate same list.
     */
    generateRandomArray(randomNumberArray, sharedKey, bigInt, arraySize);
        // Visualize output on console
    // printArray(randomNumberArray, arraySize);


    /*
    Second Requirement:
        * Function that generates, prime numbers and store the output to a file "PrimeBank.csv"
        * Using the trial division approach
        * Stores the time required to calculate the prime value called discoveryTime.
     */

    /*

        ******* UNCOMMENT TO RUN PRIME NUMBER GENERATOR ******

     */
    //generatePrimeNumberBank("PrimeBank.csv", bigInt);


    /*
    Third and Fourth Requirement:
        * Using Prime bank, and the Diffie-Hellman from class create a application that negotiates
          a shared key to while denying the other party any information.

          Alice = a
          Bob = b
          Both generated from secret text passwords.


     */
    while (g != 2 && g != 5) {
        cout << "Choose your public prime base 2 or 5" << endl;
        cin >> g;
    }

    cout << "Please choose your module value: " << endl;
    cin >> p;

    cout << "Your module is : " << p << ", and your base is : " << g << endl;
    publicKey(p, g, randomNumberArray);
    secretKey(p);


    /*
    Fifth Requirement:
        Algorith is implemented in shuffleAlgorith.cpp
        Bob will shuffle
        Alice will deshuffle

     */

    //Input File
    ifstream f("textFile.txt");
    string str;
    if(f) {
        ostringstream ss;
        ss << f.rdbuf();
        str = ss.str();
    }

    ofstream shuffleFile("ShuffleFile.txt");
    ofstream unshuffledFile("Unshuffled.txt");

    int n = str.length();

    cout << "**** Original Text **** " << "Size of original string " << "= " << n << endl;
    cout << str << endl << endl << endl << endl;

    cout << "Please enter the sharedKey value: \n";
    cin >> sharedKey;
    cout << endl;

    //Bob shuffles inputText
    string bobRandomString = randomize(str, sharedKey);
    int r = bobRandomString.length();
    cout << "**** Bob's Shuffled Text **** " << "Size of random string " << " = " << r << endl;
    cout << bobRandomString << endl << endl << endl << endl ;
    shuffleFile << bobRandomString << endl << endl << endl << endl ;


    //Alice unshuffles randomText
    string aliceDeRandom = deRandomize(randomString, sharedKey);
    int dr = aliceDeRandom.length();
    cout << "**** Bob's Unshuffled Text by Alice **** " << "Size of deRandom string " << " = " << dr << endl;
    cout << aliceDeRandom << endl << endl << endl << endl << endl;
    unshuffledFile << aliceDeRandom << endl << endl << endl << endl ;


    return 0;

}


/*
Name: generateRandomArray
Parameters: long long int array[], long long int sharedKey, long long int randomNumberRange
Description:
    This generates an array of specified values between 1 and bigInt with random values that can be run on multiple
    different os and return the same list depending on the seed that is passed to the fucntion.

Returns: None
 */
void generateRandomArray(long long int array[], long long int sharedKey, long long int randomNumberRange, int arraySize){
    srandom(sharedKey);
    for (int i = 0; i <= arraySize; i++){
        array[i] = (random() % randomNumberRange) + 1;
    }
}


/*
Name: printArray
Parameters: long long int array[], int arraySize
Description:
    This prints a array of any size

Returns: None
 */
void printArray(long long int array[], int arraySize){
    for (int i = 0; i <= arraySize; i++){
        cout << array[i];
        cout << endl;
    }
}


/*
Name: generatePrimeNumberBan
Parameters: string fileName, long long int inputNumber
Description:
    This functions generates prime numbers and stores the output in a file.

    Notes:
        * Using Trial Division
        * Also stores the the time to find the prime (Discovery Time)
        * Program stops if the time required to find a prime is longer than 1 hour(3.6e9)

    * Function uses work from --> Aticle World
        https://aticleworld.com/find-all-prime-numbers-up-to-n
Returns: None

 */
void generatePrimeNumberBank(string fileName, long long int inputNumber){
    ofstream file;
    file.open(fileName.c_str(), ios_base::app);
    //file << "Prime Numbers" << "," << "Discovery Time";
    cout << endl;

    long long int i = 0;
    long long int j = 0;
    long long int limit = 0;
    long long int primeFlag = 0;

    for(i=19776959 ; i <= inputNumber; i++){
        primeFlag = 0;

        clock_t begin = clock();

        limit = i/2;
        for(j = 2; j <= limit; j++) {
            if((i % j) == 0) {
                primeFlag = 1;
                break;
            }
        }

        if(primeFlag == 0) {
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            double discoveryTime = elapsed_secs / 60;

            //cout << "Prime Number: " << i << " Time to find: " << discoveryTime;
            //cout << endl;

            file << i << "," << discoveryTime << endl;

            if(discoveryTime >= 3.6e9){
                exit(0);
            }
        }
    }
    file.close();
}


/*
Name: publicKey
Parameters: int p, int g, long long int array[]
Description:
    Generate a public key for Alice and Bob

Returns: None
 */
void publicKey(int p, int g, long long int array[]) {

    long long int privateKey;
    long long int publicKey;

    srand((unsigned)time(NULL));

    int loc = rand()% 200;

    privateKey = array[loc];

    long long int temp = pow(g, privateKey);
    /*might be overflow when generate a temp value£ºg^a,
    Caused by large value of generated "randomNumberArray[]"
    */

    publicKey =  temp % p;

    cout << loc << endl;
    cout << privateKey << endl;
    cout << temp << endl;
    cout << "Your private key is :" << privateKey << endl;
    cout << "Your public key is :" << publicKey << endl;
}


/*
Name: secret
Parameters : int p
Description :
        Creat a shared secret key for both Alice and Bob

Returns : None
*/
void secretKey(int p) {
    int B;
    int a;
    int s;

    cout << "Enter the received public Key" << endl;
    cin >> B;
    cout << "Enter the your private Key" << endl;
    cin >> a;

    long long int temp = pow(B, a);
    s = temp % p;
    cout << "Shared Secret Key is : " << s << endl;

}
