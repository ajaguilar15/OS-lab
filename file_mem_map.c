#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprint(stderr, "Usage: %s filename\n", argv[]);
        return 1;
    }
    
    int fd = open(argv[1], O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    struct stat file_info;

    if (fstat(fd, &file_info) == -1)
    {
        perror("fstat");
        close(fd);
        return 1;
    }

    size_t file_size = file_info.st_size;

    char *data = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

    if (data = MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    printf("File size: %zu bytes\n, file_size");
    printf("Mapped file starts at virtual address: %p\n\n", (void *)data);

    printf("Reading file every 4096 bytes:\n\n");

    for (size_t i = 0; i < file_size; i += 4096)
    {
        printf("data[%5zu] address = %p, value = %02X\n",
            i,
            (void *)&data[i],
            (unsigned char)data[i]);
    }

    munmap(data, file_size);
    close(fd);

    return 0;
}