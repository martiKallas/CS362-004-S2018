#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//Selects a random character. 9/200 selections are guaranteed to
//	be one of the state changing characters.
char inputChar()
{
    char inputs[9] = {'[','(','{',' ','a','x','}',')',']'};
    int r = rand()%200;
    char ret = 'z';
    if(r < 9){
	//choose one of special inputs
        ret = inputs[r];
    }
    else{
	//choose char from ' ' to '~'
	ret = rand()%('~' - ' ') + ' ';
    }
    return ret;
}

//Source: https://codereview.stackexchange.com/questions/29198/random-string-generator-in-c
char *randstring(size_t length) {

    //these are the set of possible characters for use in the random string
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?![]{}()";        
    char *randomString = NULL;

    if (length) {
	//designate memory for the string
        randomString = malloc(sizeof(char) * (length +1));

	//select a random char from charset for each position in randomString
        if (randomString) {            
	    int n;
            for (n = 0;n < length;n++) {            
		//make sure key falls within range of charset
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }
	    //add the null terminator
            randomString[length] = '\0';
        }
    }

    return randomString;
}

//Has a 1 in 100 chance of selecting the correct phrase to trigger the target line
//	otherwise, returns a random string from 1 to 15 characters
char *inputString()
{
    int choice = rand()%100;
    char *string = NULL;
    if (choice == 0){
	string = malloc(sizeof(char)*6);
	strcpy(string, "reset");
    }
    else{
	choice = choice % 15 + 1; //no strings longer than length 15
	string = randstring(choice);
    }
    return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
