#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 4096;
const int INODE_SIZE = 32;
const int ENTRY_SIZE = 32;
const unsigned char BIT_CONVERT[8] = {128, 64, 32, 16, 8, 4, 2};
const unsigned char BIT_NUMBER[9] = {255, 127, 63, 31, 15, 7, 3, 1, 0};

void readBlock(FILE* disk, int blockNum, unsigned char* buffer){
    fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
    fread(buffer, BLOCK_SIZE, 1, disk);
}
//////////////////////////////////////////////////////////////////////////////
unsigned char* createEmptyInode(int file_size, int flage, int dataBlocks, short sib, short dib) {
//flage 0 is directory; flage 1 is file
    unsigned char* inode = malloc(32);
   
    memcpy(inode, &file_size, 4);
    memcpy(inode+4, &flage, 4);
    memcpy(inode+8, &dataBlocks, 4);
    //memcpy(inode+12, name, 16);
    memcpy(inode+28, &sib,2);
    memcpy(inode+30, &dib,2);
    return inode;
}

void writeBit(FILE* disk, int blockNum, unsigned char* data, int size, int i){
    fseek(disk, blockNum * BLOCK_SIZE+i, SEEK_SET);
    fwrite(data, size, 1, disk); 
}

unsigned char* write_ff() {
    unsigned char* inode = (unsigned char*)malloc(1);
    //short dataBlock1=0xff; 
    unsigned char dataBlock1=255;
    memcpy(inode, &dataBlock1, 1);
   
    return inode;
}

int main() {

    FILE* disk = fopen("../disk/vdisk", "rb+");
    
//Block 0: 0000 4096 4096 0000 0000.....
    /*fseek(disk, 0,SEEK_SET);
    fwrite("000040964096", 12, 1, disk);*/
    int num_blocks=6666;//Magic number
    unsigned char* ainode = (unsigned char*)malloc(4);
    memcpy(ainode, &num_blocks, 4);
    fseek(disk, 0, SEEK_SET);
    fwrite(ainode, sizeof(ainode), 1, disk);
    num_blocks=4069;//number of blocks
    memcpy(ainode, &num_blocks, 4);
    fseek(disk, 4, SEEK_SET);
    fwrite(ainode, sizeof(ainode), 1, disk);
    num_blocks=255;//number of inodes
    memcpy(ainode, &num_blocks, 4);
    fseek(disk, 8, SEEK_SET);
    fwrite(ainode, sizeof(ainode), 1, disk);
  
//Block 1
    //first 8 blocks are 0's; second 8 blocks are 0011 1111 => 0x3f
    unsigned char* inode = (unsigned char*)malloc(1);
    short dataBlock1=0x3f;
     
    memcpy(inode, &dataBlock1, 1);
    fseek(disk, 1 * BLOCK_SIZE+1, SEEK_SET);
    fwrite(inode, 1, 1, disk); 
    free(inode);
 
//other blocks are 1's => 0xff
unsigned char* myInode = write_ff();

    // Maybe add more things to the inode
int i=2;
writeBit(disk, 1, myInode, 1, i);
while(i<512){
    writeBit(disk, 1, myInode, 1, i);
    i++;
}
    free(myInode);
    
    
    fclose(disk);
    return 0;
}
