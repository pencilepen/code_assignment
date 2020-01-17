#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 4096;
const int INODE_SIZE = 32;
const int ENTRY_SIZE = 32;
const int FILE_NAME_SIZE = 31;
const unsigned char BIT_CONVERT[8] = {128, 64, 32, 16, 8, 4, 2};
const unsigned char BIT_NUMBER[9] = {255, 127, 63, 31, 15, 7, 3, 1, 0};

void readBlock(FILE* disk, int blockNum, unsigned char* buffer){
    fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
    fread(buffer, BLOCK_SIZE, 1, disk);
}
void readInode(FILE* disk, int blockNum, unsigned char* buffer, int i){
    fseek(disk, blockNum * BLOCK_SIZE + i, SEEK_SET);
    fread(buffer, INODE_SIZE, 1, disk);
}
unsigned char* write_ff() {
    unsigned char* inode = (unsigned char*)malloc(1);
    //short dataBlock1=0xff; 
    unsigned char dataBlock1=255;
    memcpy(inode, &dataBlock1, 1);
   
    return inode;
}
void writeBit(FILE* disk, int blockNum, unsigned char* data, int size, int i){
    fseek(disk, blockNum * BLOCK_SIZE+i, SEEK_SET);
    fwrite(data, size, 1, disk); 
}

void writeToFile(FILE* disk, short blockNum, char* data, unsigned long size, unsigned char* inodeBuffer) {
    //unsigned char* inodeBuffer = (unsigned char*)malloc(BLOCK_SIZE);
    readBlock(disk, blockNum, inodeBuffer);
    short fileBlockNumber;
    memcpy(&fileBlockNumber, inodeBuffer+8, 2);
    writeBit(disk, fileBlockNumber, data, size, 0);

   // free(inodeBuffer);
}

void createEmptyInode(int file_size, char* flage, int dataBlocks, short sib, short dib, unsigned char* inode) {
//flage 0 is directory; flage 1 is file
    //unsigned char* inode = (unsigned char*)malloc(32);
   //printf("file size: %d\n", file_size);
    memcpy(inode, &file_size, 4);
    memcpy(inode+4, flage, 1);
    memcpy(inode+8, &dataBlocks, 4);
    //memcpy(inode+12, name, 16);
    memcpy(inode+28, &sib,2);
    memcpy(inode+30, &dib,2);
    //return inode;
}

short editBit(unsigned char buffer, int index_byte, FILE* disk){
    short apBlock_num;
    for(int i=0; i<8; i++){
        if (buffer == BIT_NUMBER[i]){
            buffer = BIT_NUMBER[i+1];
            
            apBlock_num = index_byte*8+i;
//printf("applyedBlock_num; %d\n", apBlock_num);
		break;
        }
    }
    unsigned char* ainode= (unsigned char*)malloc(1);
    memcpy(ainode, &buffer, 1);
    fseek(disk, 1*BLOCK_SIZE+index_byte, SEEK_SET);
    fwrite(ainode, 1, 1, disk);
    free(ainode);
    return apBlock_num;
}
void recovery_bit(FILE* disk, int empBlock){
    // block 12
    //int index = atoi(empBlock);
//printf("empBlock: %d\n", empBlock);
     //index = index / 8;
    
    //read the orginal hex number
    unsigned char* bits = (unsigned char*)malloc(1);
    fseek(disk, 1*BLOCK_SIZE+(empBlock/8), SEEK_SET);
    fread(bits, 1, 1, disk);
//printf("bits[0]: %d\n", bits[0]);
       
    //index = empBlock%8;
   // index=BIT_CONVERT[index-1];
    //index = bits[0]^index;//
    bits[0] = bits[0]^BIT_CONVERT[(empBlock%8)-1];
    //memcpy (bits, &index, 1);
    fseek(disk, 1*BLOCK_SIZE+empBlock/8, SEEK_SET);
    fwrite(bits, 1, 1, disk);
   
}

short applyBlock(FILE* disk, unsigned char* buffer){
    //unsigned char* buffer = (unsigned char*)malloc(BLOCK_SIZE);
    readBlock(disk, 1, buffer);
    short apBlock_num;
    int i;
    for (i = 0; i < BLOCK_SIZE; i++){
        if(buffer[i]!=0){
            apBlock_num=editBit(buffer[i], i, disk);
            break;
        }
        if(i==BLOCK_SIZE-1){
            printf("The vdisk is full, No available block!");
        }
    }
    //free(buffer);
    return apBlock_num;
}


