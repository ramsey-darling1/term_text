/**
 * the Command Line Interface Text program, or term text
 * @rdar
 *
 */

#include<stdio.h>

int get_num(){
    //grab the phone number we want to text
    int phone_number;
    printf("Please enter the number you wish to text: ");
    scanf("%d", &phone_number);
    getchar();
    return phone_number;
}

int res_message(char *message, int phone_number) {
    //give the user a response message
    printf("%s: %i\n", message, phone_number);
    return 0;
}

int main(){

    int phone_number;
    
    phone_number = get_num();

    res_message("Here is the number you want to text",phone_number);
    
    return 0;
}


