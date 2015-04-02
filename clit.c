/**
 * the Command Line Interface Text program, or term text
 * @rdar
 *
 */

#include<stdio.h>

main(){
    
    //first grab number for who we want to text
    int phone_number;
    printf("Please enter the number you wish to text: ");
    scanf("%d", &phone_number);
    printf("Now sending a text message to: %d", phone_number);
    getchar();

    return 0;
}
