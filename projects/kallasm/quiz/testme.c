#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//Random char has a one in 10 chance of selecting one of the expected
//	char inputs or choosing a random char from ' ' to '~'
char inputChar()
{
    char inputs[9] = {'[','(','{',' ','a','x','}',')',']'};
    int r = rand()%100;
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

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?![]{}()";        
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
	    int n;
            for (n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

char *inputString()
{
    int choice = rand()%100;
    char *string = NULL;
    if (choice == 99){
	string = malloc(sizeof(char)*6);
	strcpy(string, "reset");
    }
    else{
	choice = choice % 10 + 1; //no strings longer than length 10
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
