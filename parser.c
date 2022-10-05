#include"traminfo.h"
struct msg_loc{
        int tram_len;
        char tramid[7];
        int city_len;
        char city[32];
};
struct msg_pc{
        int tram_len;
        char tramid[7];
        int pc_len;
        char pc[4];
};

bool validate(char *inp) {
    int offset = 0;
    bool islocation = false;
    /*input stream does not have any data, return*/
    if(!strlen(inp)) 
         return false;
    
    /*first character should be 0x7*/
    if (inp[0] != 0x7) {
        printf("First char not 0x7 \n");
        return false;
    }
    offset = 7;
    /*Next content, should be MSGTYPE*/
    if(strcmp(inp+ offset,"MSGTYPE")) {
        printf("Not MSGTYPE \n");
        return false;
    }
    offset +=1;
    /*next character should be 0x8 or 0xf*/
    if(!((inp[offset] == 0x8) ||(inp[offset]==0xf))) { 
        printf("Next value not 0x8 and not 0xf \n");
        return false;
    }
    
    /*next string is passenger count if inp[8] == 0xf or 
     next string is if inp[8] == 0xf*/
    offset+=1;
    if (inp[offset] == 0x8) {
        if(strcmp(inp+offset,"LOCATION")) {
            printf("Next value not LOCATION \n");
            return false;
        }
        islocation = true;
        offset+=8;
    } else {
        if(strcmp(inp+offset,"PASSENGER_COUNT")) {
            printf("Next value not PASSENGER_COUNT \n");
            return false;
        }
        offset+=15;
    }

    if(inp[offset] != 0x7) {
        printf("Tram ID  length is not 7 \n");
    }
    offset+=1;
    
    if(strcmp(inp+offset, "TRAM_ID")) {
        printf("Next value not TRAM_ID \n");
        return false;
    }

    /*Skip the next 7 characters for TRAM_ID*/
    offset+=7;

    /*check for 0x5 to 0x7 lenght of tram id*/
    if(!(inp[offset] >= 5) && (inp[offset] <= 7)) {
        printf("Next value not between 5 and  7 \n");
        return false;
    }
    
    /*Skip the next offset characters for TRAM_ID value*/
    offset+=inp[offset];

    if(inp[offset] != 0x5) {
        printf("Value  length is not 5 \n");
    }
    /*Skip for length of value*/
    offset+=5;

    /*if this is location, skip validation for now.*/ 
    /*skip the last portion for now*/
    
    return true;        
}

void parse_message(char * stream) {
    
     /*Validate the stream and avoid parsing*/ 
     if(!validate(stream))
        return;


}
struct Tram * gl_root = NULL;
int main() {
           
        
    return 0;
}
         


