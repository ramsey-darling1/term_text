/**
 * the Command Line Interface Text program, or term text
 * @rdar
 *
 */

#include <stdio.h>
#include <curl/curl.h>

struct text_message {
    char phone_number[12];
    char message[142];

};

void get_num(char * phone_number){
    //grab the phone number we want to text
    //number has to be represented as a string
    printf("Please enter the 10 digit number you wish to text, no spaces or special characters: ");
    fgets(phone_number,12,stdin);
}

void get_text_message(char * text_message){
    //grab the message that the user wants to send
    printf("Please enter the message you wish to send, no more than 140 characters: ");
    fgets(text_message,142,stdin);
}

void res_message(char * message, char * phone_number) {
    //give the user a response message
    printf("Tried to send this message: %s, to this phone number: %s\n", message, phone_number);
}

int request(char * phone_number, char * text_message){
    CURL *curl;
    CURLcode res;
    int result;

    curl = curl_easy_init();
    phone_number[10] = 0;//remove the new line character
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL,"http://textbelt.com/text");
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,("number=%s",phone_number));
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

void main(){
    struct text_message active;
    get_num(active.phone_number);//grab the phone number from the user
    get_text_message(active.message);//grab the text message to send from the user
    request(active.phone_number,active.message);//send the text message to the number
    //printf("called from main: %s, %s\n",active.phone_number,active.message);
    res_message(active.message,active.phone_number);//give the user a response message
}


