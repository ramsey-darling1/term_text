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

char *get_message(){
    //grab the message that the user wants to send
    char *message;
    printf("Please enter the message you wish to send: ");
    scanf("%s",message);
    getchar();
    return message;
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

int request(int phone_number, char *text_message){
    CURL *curl;
    CURLcode res;
    int result;

    curl = curl_easy_init();

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL,"http://textbelt.com/text");
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,("number=%i",phone_number));
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,("message=%s",text_message));
        curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1l);//follow redirection if redirected
        //preform the actual request
        res = curl_easy_perform(curl);
        result = res != CURLE_OK ? 0 : 1;
        curl_easy_cleanup(curl);
    }else{
        result = 0; 
    }

    return result;
}

int main(){

    int phone_number;
    char *message;
    char *text_message;

    phone_number = get_num();
    text_message = get_message();

    switch(varify_phone_number(phone_number)){
        case 1:
            request(phone_number,text_message);
            message = "Thanks, message was sent to: ";
            break;
        case 0:
            message = "Sorry, that is not a valid phone number, we can not send a text to that number.";
            break;
    }         

    res_message(message,phone_number);

    return 0;
}


