/*

Program Name: ShuffleAlgorithm.cpp
Class: ENSE496AE Digital Security
Group: B

Author: Mckenzie Busenius

Professor: Dr. Yasser Morgan

Description: The purpose of this program is to provide a shuffle algorthim for given text file.
             Additionally, the algorithm will deshuffle the shuffled string if the user provides
             the correct seed value.

 */
#include<bits/stdc++.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include "shuffleAlgorithm.h"

using namespace std;


/*
Name: randomize
Parameters: string passedString, int seed
Description:
    This function take and input string from a file and seed value to preform a
    variation of the Fisher-Yates Shuffle algorithm.

    * Use the idea of using the index of an array combinted with getting a random value
      select the next random index to swap.

Returns: Random String
 */
string randomize (string passedString, int sharedKey){
    srand (sharedKey);
    string randomSting = "";

    // declaring character array : p
    char p[passedString.length() + 1];

    for (int i = 0; i < sizeof(p); i++) {
        p[i] = passedString[i];
    }

    for (int i = sizeof(p) - 1; i > 0; i--){
        // Pick a random index from 0 to i
        int j = rand() % (i + 1);

        // Preform random swap
        char tmp = p[i];
        p[i] = p[j];
        p[j] = tmp;
        randomSting = randomSting + p[i];
    }
    return randomSting;
}


/*
Name: deRandomize
Parameters: string randomString, int seed
Description: Preform the deshuffle of the shuffled string from the randomized function.
             * The idea was to generate the same random number as the shuffle using the seed value
               to create and path in reverse order to go back to the original text.

            NOTE: ***** Currently Broken *****
                Not returning the unscarambled string

            Possible Solution: The swap is not getting the correct reverse order, or the char[] data type is dynamic
                      and is cause random index values to be returned from the random part within function.

Returns: Unscrambled String
 */
string deRandomize (string randomString, int sharedKey){
    srand (sharedKey);
    string deRandomString = "";

    // declaring character array : p
    char p[randomString.length() + 1];

    // Populate string, with chars from
    for (int i = 0; i < sizeof(p); i++) {
        p[i] = randomString[i];
    }

    for (int i = 1; i < sizeof(p); i++){
        // Pick a random index from 0 to i(same index from the random sequence)
        int j = rand() % (i + 1);

        // Preform reverse swap
        char tmp = p[i];
        p[i] = p[j];
        p[j] = tmp;

        deRandomString = deRandomString + p[i];
    }
    return deRandomString;
}
