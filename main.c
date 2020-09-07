#include <stdio.h>
#include <ctype.h>
#include <string.h>

void shiftStr(char str[], int shift);
void encipher(FILE* inFile, FILE* outFile, int key);
int validFileSuffix(char str[]);

const int BUFFER_SIZE = 2048;

int main()
{
    char inName[BUFFER_SIZE];


    char outName[BUFFER_SIZE];
    char outPrefix[BUFFER_SIZE];

    int key;

    printf("Read file name(*.txt):"); //read file name
    scanf("%s", inName);

    while(validFileSuffix(inName) != 1)//return 1 if true
    {
        //error if filename is wrong
        printf("Error.  *.txt required.\n");
        printf("Read file name (*.txt):");
        scanf("%s", inName);
    }

    FILE* inFile = fopen(inName, "r"); //read file

    //if the input file is null, error and exit program
    if(inFile == NULL)
    {
        printf("Error: Failed to open %s\n", inName);
        return -1;
    }

    //outfile prefix
    printf("Please enter an output file prefix: ");
    scanf("%s", outPrefix);

    ///TODO(6):  Copy prefix to output file string, concatenate input file name
    strcpy(outName, outPrefix);
    strcat(outName, inName);

    //Open output file.
    //If fail, exit the program.
    FILE* outFile = fopen(outName, "w");
    if(outFile == NULL)
    {
        printf("Could not open file %s", outName);
        return -1;
    }

    //read key
    printf("Key?");
    scanf("%d", &key);
    printf("Encrypting...\n");
    encipher(inFile, outFile, key);
    printf("Complete.\n");
}

//is this a valid suffix?
int validFileSuffix(char str[])
{
    char* valid = strstr(str, ".txt");

    if(valid)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void encipher(FILE* inFile, FILE* outFile, int key)
{
    char inName[BUFFER_SIZE];
    char encr[BUFFER_SIZE];
    int shift;

    while(fgets(inName, BUFFER_SIZE, inFile)) //read until file is not null
    {
        shiftStr(inName, key); //shift buffer
        fprintf(outFile, "%s", inName); //output string to out file

    }
    fclose(inFile);
    fclose(outFile); //dont forget to close
}

void shiftStr(char str[], int shift)
{
    shift = shift%26;
    for(int i =0; i < strlen(str); i++)
    {
        if(isalpha(str[i]) != 0)
        {
            if(islower(str[i]) != 0 && str[i] + shift > 'z' || isupper(str[i]) != 0 && str[i] + shift > 'Z')
            {
                shift = shift - 26; //shift
            }
            else if((islower(str[i])!= 0 && str[i]+shift < 'a') || (isupper(str[i]) !=0 && str[i]+shift < 'A'))
            {
                shift = shift+ 26; //shift
            }
            str[i] = shift + str[i];

        }

    }
}

