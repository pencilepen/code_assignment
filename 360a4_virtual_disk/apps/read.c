    #include "diskAPI.c"



int main(int argc, char* argv[]) {
    FILE* disk = fopen("../disk/vdisk", "rb+");

    unsigned char* aplyInode1 = (unsigned char*)malloc(BLOCK_SIZE);
    int root_block_num = 10;
    unsigned char* filename = (unsigned char*)malloc(ENTRY_SIZE-1);
    filename = "helloWorld.txt\0";
    unsigned char* tInode = (unsigned char*) malloc (INODE_SIZE);

     unsigned char* bInode = (unsigned char*) malloc (BLOCK_SIZE);
    readBlock( disk,  root_block_num, bInode);//read root directory block : inode# + filename
    for(int i = 0; i<16; i++){
         if(bInode[i*ENTRY_SIZE]!=0){
              readInode(disk, root_block_num, tInode, i*ENTRY_SIZE+1);//read filename
 
              if(strncmp(tInode, filename, FILE_NAME_SIZE)==0){
                      free(tInode);
                      readInode(disk, root_block_num, tInode, i*ENTRY_SIZE);}//read inode#
                      if(tInode[0]==1){//unique inode number 1 refers to first inode from Block 11
                            free(tInode);
                            readInode(disk, 11, tInode, 0);//read the inode of "helloWorld.txt"
                            readBlock(disk, tInode[8], aplyInode1);//,tInode[9]
                            printf("The content of \"%s\" is:\n", filename);
                            printf("%s\n", aplyInode1);
                            free(aplyInode1);
                            free(tInode);
                            break;
                            }
            }
          else if(i = 15){
               printf("The Vdisk doesn't have this file or subdirectory.\n");}
    }
    free(bInode);

   fclose(disk);
    return 0;
}
