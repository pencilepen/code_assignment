#include "diskAPI.c"


int main(int argc, char* argv[]) {
    FILE* disk = fopen("../disk/vdisk", "rb+");
   
    unsigned char* bInode = (unsigned char*) malloc (BLOCK_SIZE);
    unsigned char indicate_inode = 0;
    int root_block_num = 10;
    unsigned char* filename = (unsigned char*)malloc(ENTRY_SIZE-1);
    filename = "helloWorld.txt\0";
    unsigned char* tInode = (unsigned char*) malloc (INODE_SIZE);
    //Deletion of "helloWorld.txt"
    //go to root directory block to find the file
    readBlock( disk,  root_block_num, bInode);//read root directory block : inode# + filename
//root_block_num
  for(int i = 0; i<16; i++){
     if(bInode[i*ENTRY_SIZE]!=0){
         readInode(disk, root_block_num, tInode, i*ENTRY_SIZE+1);//read filename
 
         if(strncmp(tInode, filename, FILE_NAME_SIZE)==0){// have found the file
              free(tInode);
              readInode(disk, root_block_num, tInode, i*ENTRY_SIZE);
         }//read inode#
              if(tInode[0]==1){//unique inode number 1 refers to first inode from Block 11
      
               //change unique inode  number to be 0
                 //indicate_inode=0;//no entry
                 fseek(disk, root_block_num * BLOCK_SIZE+i*ENTRY_SIZE, SEEK_SET);//inode# + file name
                 memcpy(tInode, &indicate_inode,1);
                 for(int j=0; j<32; j++){
                    fwrite(tInode, 1, 1, disk);//write bit 0
                 }//empty the entry 
                 free(tInode);

                 readInode(disk, 11, tInode, 0);//read the inode of "helloWorld.txt"
                                      // find the block of the file
                 int fileblock = tInode[8];
                 //fseek(disk, tInode[8]*BLOCK_SIZE, SEEK_SET);
                 fseek(disk, fileblock*BLOCK_SIZE, SEEK_SET);// seek to file block
//free(tInode);
//printf("fileblock: %d\n", fileblock);
                 memcpy(tInode, &indicate_inode,1);
                 for(int j=0; j<512; j++){
                    fwrite(tInode, 1, 1, disk);//write bit 0
                  }//empty the file 
                  fseek(disk, 11*BLOCK_SIZE, SEEK_SET);//seek to the inode of the file
                  for(int j=0; j<32; j++){
                    fwrite(tInode, 1, 1, disk);//write bit 0
                  }//empty the inode 
//printf("fileblock222: %d\n", fileblock);
                  //edit Block 1
//printf("tInode[8]: %d\n", tInode[8]);
                  recovery_bit(disk, fileblock);
      //free(tInode);
                  printf("The \"%s\" has been deleted.\n", filename);
                  break;
                }
          }
          else if(i = 15){
               printf("The Vdisk doesn't have this file or subdirectory.\n");
       }
    }
    free(bInode);


    fclose(disk);
    return 0;
}
