#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>
int main(int argc, char **argv)
{
    //*argv[1]: url
    //*argv[2]: name of outputfile
    char *url = argv[1];
    char *nameOfOututFile = argv[2];
    CURL *curl;
    CURLcode response;
    FILE *output_file = fopen(nameOfOututFile, "w");
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

         /* enable TCP keep-alive for this transfer */
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        //request to fetch header from url
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
        // curl_easy_setopt(curl, CURLOPT_CHUNK_DATA, 1L);
        
        /* create an output file and prepare to write the responseponse */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);
	for(int i = 1; i < 1000; i++){
        /* Perform the request, response will get the return code */
        response = curl_easy_perform(curl);

        /* Check for errors */
        if(response != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %sn", 
                curl_easy_strerror(response));
        }
     }
        fclose(output_file);
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return 0;
}
