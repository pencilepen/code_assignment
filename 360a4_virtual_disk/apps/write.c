#include "diskAPI.c"

//malloc: tinode= temp 32, aplyInode1= applyBlock() 512, 
//			aplyInode2= applyBlock() 512 
//unsigned char* filename = (unsigned char*)malloc(ENTRY_SIZE-1);
//unsigned char indicate_inode = 0;


int main(int argc, char* argv[]) {
    FILE* disk = fopen("../disk/vdisk", "rb+");
   

//build root directory block at block 10, by applyBlock()
    unsigned char* aplyInode1 = (unsigned char*)malloc(BLOCK_SIZE);
    short applyedBlock_num = applyBlock(disk, aplyInode1);
   // printf("applyedBlock_num; %d\n", applyedBlock_num);//for root directory block
    int root_block_num=applyedBlock_num;
//printf("root_block_num: %d\n", root_block_num);

// write inode for root directory at block2
    fseek(disk, 2 * BLOCK_SIZE, SEEK_SET);
    unsigned char* tInode = (unsigned char*) malloc (INODE_SIZE);
    createEmptyInode(0, "/", root_block_num, 0, 0, tInode);
    writeBit(disk, 2, tInode, 32, 0);//at Block 2: inode of root directory
    free(tInode);

    //////root directory block at block 10;
    unsigned char indicate_inode = 0;
    strncpy(tInode, &indicate_inode,1);
    unsigned char* filename = (unsigned char*)malloc(ENTRY_SIZE-1);
    filename = "\0";
    strcat(tInode,filename);
       //  printf("strlen tInode: %ld\n", strlen(tInode));
    for(int i=0; i< 16; i++){
        fseek(disk, applyedBlock_num * BLOCK_SIZE + i*ENTRY_SIZE, SEEK_SET);
        
        fwrite(tInode, strlen(tInode), 1, disk);
    }
free(tInode);
    free(aplyInode1);
//=======================================================================================
//write a file at root directory
  // first create an inode for this file
 
 // apply blocks for content and inode
    int whereInode = applyBlock(disk, aplyInode1);
unsigned char* aplyInode2 = (unsigned char*)malloc(BLOCK_SIZE);
    int whereData = applyBlock(disk, aplyInode2);
  //  printf("where inode; %d\n", whereInode);
//printf("whereData; %d\n", whereData);
//write content
    char* fileContent = "Hello World!\n123456789\nabcdefghijklmnopqrstuvwxyz\0";
//printf("fileContent size: %ld\n", strlen(fileContent));

    createEmptyInode(strlen(fileContent), "0", whereData, 0, 0, tInode);//create an inode for the file
    writeBit(disk, whereInode, tInode, INODE_SIZE, 0);// write file inode at Block 11
    writeToFile(disk, whereInode, fileContent, strlen(fileContent), aplyInode2);

free(aplyInode2);
free(tInode);
free(aplyInode1);

    //write entry in root directory block(block 10)
        //inode# + file name
    fseek(disk, root_block_num * BLOCK_SIZE, SEEK_SET);//inode# + file name
    
    indicate_inode = 1;//unique inode number
    memcpy(tInode, &indicate_inode,1);
    fwrite(tInode, 1, 1, disk);//write bit that unique inode number 01
free(tInode);
    filename = "helloWorld.txt\0";
    
    fwrite(filename, ENTRY_SIZE-1, 1, disk);
    
    fclose(disk);
    return 0;
}
