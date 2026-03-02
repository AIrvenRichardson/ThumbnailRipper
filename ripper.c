#include <stdio.h>
#include <string.h>

static const char *allowed_extensions[] = {".wav", ".mp3", ".flac", ".m4a"};

void process_wav_file(FILE *fp);
void process_flac_file(FILE *fp);

int main(int argc, char *argv[]) {

    // Check if the arguments and file are valid
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    
    // Ensure the file type is acceptable
    int valid_extension = 0;
    const char *ext = strrchr(argv[1], '.');
    if (ext == NULL) {
        return 0; // No extension found
    }

    for (size_t i = 0; i < sizeof(allowed_extensions) / sizeof(allowed_extensions[0]); i++) {
        if (strcmp(ext, allowed_extensions[i]) == 0) {
            valid_extension = 1;
            break;
        }
    }

    if (!valid_extension) {
        printf("Error: Unsupported file type. Allowed extensions are: .wav, .mp3, .flac, .m4a\n");
        fclose(fp);
        return 1;
    }

    if (strcmp(ext, ".wav") == 0) {
        process_wav_file(fp);
    }
    else if (strcmp(ext, ".flac") == 0) {
        process_flac_file(fp);
    }
    else {
        printf("NOT YET IMPLEMENTED, SORRY :(\n");
    }
    return 0;
}

void process_wav_file(FILE *fp) {
    
    // Iterate over the header, it's exactly 44 bytes long, and print it out in hex
    // Ok so wav files don't actually have thumbnails, oops, keeping this code for reference though.

    int i = 0;
    int data = 0;
    printf("Master RIFF chunk\n");
    while (i < 44) {
        if (i == 3*4) {
            printf("\n Data Format Chunk\n");
        }
        if (i == 9*4) {
            printf("\n Sampled data Chunk \n");
        }
        data = fgetc(fp);
        if (data == EOF) {
            break;
        }
        printf("%x ", data);
        i++;
    }
    printf("\nEND HEADER\n");

    return;
}

void process_flac_file(FILE *fp) {
    // Pull out the metadata block containing the thumbnail if it exists.
    
    int i = 0;
    int data = 0;
    printf("BEGIN\n");
    while (i < 4) {
        data = fgetc(fp);
        if (data == EOF) {
            break;
        }
        printf("%x ", data);
        i++;
    }
    printf("\nEND HEADER\n");

    return;
}