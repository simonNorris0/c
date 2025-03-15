#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> // https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/fcntl.h.html
#include <stdio.h>


// https://pubs.opengroup.org/onlinepubs/9799919799/functions/open.html
int open(const char *path, int oflag, ...);
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);

int main()
{
    int fdin, fdout;  // integers for file descriptors returned by open() calls
    char pathname[40];// char array for pathname of input and output files
    char buf[20];     // character buffer to read data into and write data from
    size_t nbytes;    // number of bytes to read/write into buffer at a time
    ssize_t bytes_read; 
    //ssize_t bytes_written; // optional return from write()

    printf("Enter the pathname of the file to copy from: ");
    scanf("%s", pathname); // pathname now stores path to input file
    // opens the file at the pathname provided by the string that begins at
    // the address given by pathname for reading only. 
    // The integer (file descriptor) returned and stored in fdin is used to 
    // access the input file.
    fdin = open(pathname, O_RDONLY);
    if (fdin == -1) { // input file does not exist
        printf("ERR: Input file could not be found..");
        return -1;
    }
    printf("Enter the name of the file to copy to: ");
    scanf("%s", pathname); // pathname now stores path to output file
    // creates the file at the pathname provided by the string that begins at 
    // the address given by pathname for writing only. 
    // If pathname names a symbolic link (if the file exists) open() shall 
    // fail and return -1. 
    // The integer (file descriptor) returned and stored in fdout is used to 
    // access the output file.
    fdout = open(pathname, O_WRONLY | O_CREAT | O_EXCL);      
    if (fdout == -1) { // output file already exists
        printf("ERR: Output file already exists..");
        return -1;
    }
    nbytes = sizeof(buf);
    bytes_read = read(fdin, buf, nbytes);
    while (bytes_read > 0) { // 0 indicates EOF
        write(fdout, buf, nbytes);
        bytes_read = read(fdin, buf, nbytes);
    }
    close(fdin);    // closes input file 
    close(fdout);   // closes output file
    printf("Finished copying succesfuly.");
    return 0;
}
