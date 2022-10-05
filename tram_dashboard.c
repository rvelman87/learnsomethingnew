#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ctype.h>
#include "traminfo.h"

#define DEBUG_LOW 1
#define DEBUG_ALL 1
#define DEBUG_INFO 1
#define DEBUG_ERR 1

struct Tram *global_root = NULL;
/* 
    The Tram data server (server.py) publishes messages over a custom protocol. 
    
    These messages are either:

    1. Tram Passenger Count updates (MSGTYPE=PASSENGER_COUNT)
    2. Tram Location updates (MSGTYPE=LOCATION)

    It publishes these messages over a continuous byte stream, over TCP.

    Each message begins with a 'MSGTYPE' content, and all messages are made up in the format of [CONTENT_LENGTH][CONTENT]:

    For example, a raw Location update message looks like this:

        7MSGTYPE8LOCATION7TRAM_ID7TRAMABC5VALUE4CITY

        The first byte, '7', is the length of the content 'MSGTYPE'. 
        After the last byte of 'MSGTYPE', you will find another byte, '8'.
        '8' is the length of the next content, 'LOCATION'. 
        After the last byte of 'LOCATION', you will find another byte, '7', the length of the next content 'TRAM_ID', and so on.

        Parsing the stream in this way will yield a message of:

        MSGTYPE => LOCATION
        TRAM_ID => TRAMABC
        VALUE => CITY

        Meaning, this is a location message that tells us TRAMABC is in the CITY.

        Once you encounter a content of 'MSGTYPE' again, this means we are in a new message, and finished parsing the current message

    The task is to read from the TCP socket, and display a realtime updating dashboard all trams (as you will get messages for multiple trams, indicated by TRAM_ID), their current location and passenger count.

    E.g:

        Tram 1:
            Location: Williams Street
            Passenger Count: 50

        Tram 2:
            Location: Flinders Street
            Passenger Count: 22

    To start the server to consume from, please install python, and run python3 server.py 8081

    Feel free to modify the code below, which already implements a TCP socket consumer and dumps the content to a string & byte array
*/

/*
 * Validate the input stream has the proper message contents fills tram fields 
 * */
bool validate(char *inp, bool *islocation, char * tram_id, char *city, int *pc)  {
    int offset = 0;
    char temp[32];
    int valatoffset =0;

    /*input stream does not have any data, return*/
    if(!strlen(inp)) 
         return false;
    
    /*first character should be 0x7*/
    if (inp[0] != 0x7) {
        #if DEBUG_ERR
            printf("First char not 0x7 , offset %d \n", offset);
        #endif 
        return false;
    } else {
        #if DEBUG_LOW
            printf("Input character 0x7 \n");
        #endif 
    }
    
    /*update offset to next index */
    offset = 1;
    #if DEBUG_LOW
        printf("1:update offset %d \n", offset);
    #endif 


    /*Next content, should be MSGTYPE*/
    if(strncmp(inp+offset,"MSGTYPE", 7)) {
        #if DEBUG_ERR
            snprintf(temp, 7, "%s", inp+offset);
            printf("Not MSGTYPE %s and offset %d\n", temp, offset);
        #endif 
        return false;
    } else {
        #if DEBUG_LOW
            printf("its MSGTYPE at offset %d\n", offset);
        #endif 
    }
    offset = offset + 7; /*add 7 to offset*/

    #if DEBUG_LOW
        printf("2:update offset %d \n", offset);
    #endif 
    /*next character should be 0x8 or 0xf*/
    if(!((inp[offset] == 0x8) ||(inp[offset]==0xf))) { 
        #if DEBUG_ERR
            printf("Next value not 0x8 and not 0xf, offset %d , value %d \n",
                offset, inp[offset]);
        #endif 
        return false;
    } else {
        #if DEBUG_LOW
            printf("its either 0x8 or 0xf %d, value %d\n", offset, inp[offset]);
        #endif 
    }
    offset += 1;

    /*next string is passenger count if inp[8] == 0xf or 
     next string is if inp[8] == 0xf*/
    #if DEBUG_LOW
        printf("3:update offset %d \n", offset);
        printf("IP at offset %d , offset value %d\n", inp[offset], offset);
    #endif 

    if (inp[offset-1] == 0x8) {
        if(strncmp(inp+offset,"LOCATION", 8)) { /*Location message*/
        #if DEBUG_ERR
            temp[0]='\0'; 
            snprintf(temp, 8, "%s", inp+offset);
            printf("Next value not LOCATION , :%s: offset %d\n", temp, offset);
        #endif 
            return false;
        }else {

        #if DEBUG_LOW
            printf("its LOCATION with offset %d\n", offset);
        #endif 
        } /* This message is location update message */
        *islocation = true;
        offset += 8;
    } else { /*PC Message */
        if(strncmp(inp+offset,"PASSENGER_COUNT", 15)) {
        #if DEBUG_ERR
            temp[0]='\0'; 
            snprintf(temp, 15, "%s", inp+offset);
            printf("Next value not PASSENGER_COUNT  :%s: offset %d\n", temp, offset);
        #endif 
            return false;
        } else {
        
        #if DEBUG_LOW
            printf("its PASSENGER_COUNT with offset %d\n", offset);
        #endif 
        }
        offset += 15;
    }
    #if DEBUG_LOW
        printf("4:update offset %d \n", offset);
    #endif 

    if(inp[offset] != 0x7) {
        #if DEBUG_ERR
            printf("Tram ID  length is not 7 , offset %d\n", offset);
        #endif 
        return false;
    } else {
        #if DEBUG_LOW
            printf("tram id lenght is fine and offset %d\n", offset);
        #endif 
    }
    offset += 1;
    #if DEBUG_LOW
        printf("5:update offset %d \n", offset);
    #endif 
    
    if(strncmp(inp+offset, "TRAM_ID", 7)) {
        #if DEBUG_ERR
            printf("Next value not TRAM_ID, offset %d \n", offset);
        #endif 
        return false;
    } else {
        #if DEBUG_LOW
            printf("ITs is tram id and offset %d\n", offset);
        #endif 
    }

    /*Skip the next 7 characters for TRAM_ID*/
    offset += 7;
    
    #if DEBUG_LOW
        printf("6:update offset %d \n", offset);
    #endif 
    /*check for 0x5 to 0x7 lenght of tram id*/
    if(!(inp[offset] >= 5) && (inp[offset] <= 7)) {
        #if DEBUG_ERR
            printf("Next value not between 5 and  7 , offset %d , value %d \n", offset, inp[offset]);
        #endif 
        return false;
    } else {
        #if DEBUG_LOW
            printf("value in 5,7 offset %d value at %d\n", offset, inp[offset]);
            valatoffset = inp[offset];
        #endif 
    }
    
    offset += 1;
    #if DEBUG_LOW
        printf("7:update offset %d \n", offset);
    #endif

    /*copy the contents of tram id*/ 
    strncpy(tram_id, inp+offset, valatoffset);
    tram_id[6] = '\0'; //remove garbage
    /*Skip the next offset characters for TRAM_ID value*/
    offset  += valatoffset;

    #if DEBUG_LOW
        printf("8:update offset %d \n", offset);
    #endif 
    #if DEBUG_INFO
        printf("Incoming tram id %s\n", tram_id);
    #endif 


    /*Skip for length of value*/
    offset += 6;
    #if DEBUG_LOW
        printf("9:update offset %d \n", offset);
    #endif 
    /*if this is location, skip validation for now.*/ 
    valatoffset = inp[offset]; 
    #if DEBUG_LOW
        printf("valatoffset\n", valatoffset);
        offset += 1;
        printf("10:update offset %d , valatoffset\n", offset, valatoffset);
    #endif
    /*copy the remaining*/ 
    if(*islocation == true) {
        #if DEBUG_INFO
            strncpy(city, inp+offset, 32);
            printf("city %s \n", city);
        #endif 
    } else { /* copy the value of count to PC */
        
        temp[0]='\0'; 
        strncpy(temp, inp+offset, 32);
        *pc = atoi(temp);
        #if DEBUG_INFO
            printf("passenger count %d \n", atoi(temp));
        #endif 
    }
    #if DEBUG_INFO
        printf("validation success \n");
    #endif 
    return true;        
}

void parse_message(char * stream) {
     char tram_id[7] = "Noinfo";
     char city[32] = "Noinfo";
     int passenger_count = 0;
     bool islocation = false; 
     /*Validate the stream and avoid parsing*/ 
     if(!validate(stream, &islocation, tram_id, city, &passenger_count))
        return;
     if(islocation == false) {
        printf("Passenger count message \n");
     } else {
        printf("Location message \n");
     }
     printf("Tram ID :%s City :%s passenger count:%d \n", tram_id, city, passenger_count); 
     insert(&global_root, tram_id, city, passenger_count, islocation);
}

void error(char* msg) {
    perror(msg);
    exit(1);
}

void dump_buffer(char* name) {
    int e;
    size_t len = strlen(name);
    for (size_t i = 0; i < len; i++) {
        e = name[i];
       // printf("%-5d", e);
    }
    printf("\n\n");
    for (size_t i = 0; i < len; i++) {
        char c = name[i];
        if (!isalpha(name[i]) && !isdigit(name[i]) && (c != '_') && (c != ' '))
            c = '*';
        printf("%-5c", c);
    }
    printf("\n\n");
}


int main(int argc, char *argv[]){
    int count = 0;
	if(argc < 2){
        fprintf(stderr,"No port provided\n");
        //exit(1);
	}	
	int sockfd, portno, n;
	char buffer[255];
	
	struct sockaddr_in serv_addr;
	struct hostent* server;
	
	portno = 8081; 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		error("Socket failed \n");
	}
	
	server = gethostbyname("127.0.0.1");
	if(server == NULL){
		error("No such host\n");
	}
	
	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	
	if(connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr))<0)
		error("Connection failed\n");
	
	while(1){
		bzero(buffer, 255);
		n = read(sockfd, buffer, 255);
		if(n<0)
			error("Error reading from Server");
        //printf("%s", buffer);
		dump_buffer(buffer);
        parse_message(buffer);
        if(count++ == 100)
            break;
	}
	
     display(&global_root);
	return 0;
}
