/**
 * the Command Line Interface Text program, or term text
 * @rdar
 *
 */

#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>

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

size_t static write_callback_func(void *buffer,
        size_t size,
        size_t nmemb,
        void *userp);

char *send_request(char *url, int phone_number){

    /* keeps the handle to the curl object */
    CURL *curl_handle = NULL;
    /* to keep the response */
    char *response = NULL;

    /* initializing curl and setting the url */
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1);

    /* follow locations specified by the response header */
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);

    /* setting a callback function to return the data */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback_func);

    /* passing the pointer to the response as the callback parameter */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

    /* perform the request */
    curl_easy_perform(curl_handle);

    /* cleaning all curl stuff */
    curl_easy_cleanup(curl_handle);

    return response;
}

int main(){

    int phone_number;
    char *message;

    phone_number = get_num();

    switch(varify_phone_number(phone_number)){
        case 1:
            message = "Thanks, here is the number you wish to text: ";
            break;
        case 0:
            message = "Sorry, that is not a valid phone number, we can not send a text to that number.";
            break;
    }         

    res_message(message,phone_number);

    return 0;
}


