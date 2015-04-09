/**
 * the Command Line Interface Text program, or term text
 * @rdar
 *
 */

#include <stdio.h>
#include <curl/curl.h>

int get_num(){
    //grab the phone number we want to text
    int phone_number;
    printf("Please enter the 10 digit number you wish to text, no spaces or special characters: ");
    scanf("%d", &phone_number);
    getchar();
    return phone_number;
}

int varify_phone_number(int phone_number){
    int res;
    
    if(phone_number < 1000000000 || phone_number > 9999999999){
        res = 0;//it's not really a phone number 
    }else{
        res = 1; 
    }

    return res;
}

int res_message(char *message, int phone_number) {
    //give the user a response message
    printf("%s: %i\n", message, phone_number);
    return 0;
}

int request(){
    CURL *curl;
    CURLcode res;
    int result;

    curl = curl_easy_init();

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL,"http://textbelt.com/text");
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"number=5551551555");
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"message=text goes here");
    }else{
        result = 0; 
    }

    return result;
}

int main(){

    int phone_number;
    char *message;

    phone_number = get_num();

    switch(varify_phone_number(phone_number)){
        case 1:
            message = "Thanks, message was sent to: ";
            break;
        case 0:
            message = "Sorry, that is not a valid phone number, we can not send a text to that number.";
            break;
    }         

    res_message(message,phone_number);

    return 0;
}


