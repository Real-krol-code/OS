#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

void brute(const char* alph, int alph_len, int n, char* current, int pos, const char* target_hash, const char* salt){
    if (pos == n) {
        current[n] = '\0';

        char *hash = crypt(current, salt);

        if (strcmp(hash, target_hash) == 0) {
            printf("%s\n", current);
            exit(0);
        }
        return;
    }
    for (int i = 0; i < alph_len; i++) {
        current[pos] = alph[i];
        brute(alph, alph_len, n, current, pos + 1, target_hash, salt);
    }
}

int main(int argc, char* argv[]) {
    int opt;
    char* alphabet = NULL;
    char* hash = NULL;
    char* salt = NULL;
    int n = 0;
    while ((opt = getopt(argc, argv, "a:n:h:s:")) != -1) {
        switch(opt) {
            case 'a':
                alphabet = optarg;
                break;
            case 'n':
                n = atoi(optarg);
                break;
            case 'h':
                hash = optarg;
                break;
            case 's':
                salt = optarg;
                break;
            default:
                fprintf(stderr,"unknown argument\n");
                return 1;
        }
    }

    if (!alphabet || n <= 0 || !hash || !salt) {
        fprintf(stderr, "Missing arguments\n");
        return 1;
    }
    int alph_len = strlen(alphabet);
    char current[n + 1];
    brute(alphabet, alph_len, n, current, 0, hash, salt);
    fprintf(stderr, "Hash not found\n");
    return 1;
}
