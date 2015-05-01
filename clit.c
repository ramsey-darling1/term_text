/**
 * the Command Line Interface Text program, or term text
 * @rdar
 *
 */

#include <stdio.h>
#include <curl/curl.h>

struct text_message {
    char phone_number[12];
    char message[141];

};

char * get_num(char * phone_number){
    //grab the phone number we want to text
    //number has to be represented as a string
    printf("Please enter the 10 digit number you wish to text, no spaces or special characters: ");
    getchar();
    fgets(phone_number,11,stdin);
    return phone_number;
}

char * get_text_message(char * text_message){
    //grab the message that the user wants to send
    printf("Please enter the message you wish to send, no more than 140 characters: ");
    getchar();
    fgets(text_message,140,stdin);
    return text_message;
}

int res_message(char * message, char * phone_number) {
    //give the user a response message
    printf("%s: %s\n", message, phone_number);
    return 0;
}

int request(char * phone_number, char * text_message){
    CURL *curl;
    CURLcode res;
    int result;

    curl = curl_easy_init();

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL,"http://textbelt.com/text");
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,("number=%s",phone_number));
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,("message=%s",text_message));
        //curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"number=7342395992");
        //curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"message=this is just a test");
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

    struct text_message active;
    //char * response_message;

    get_num(active.phone_number);
    get_text_message(active.message);

    //request(active.phone_number,active.message);

    //response_message = "just a test";

    printf("called from main: %s, %s\n",active.phone_number,active.message);
    //res_message(message,phone_number);

    return 0;
}


