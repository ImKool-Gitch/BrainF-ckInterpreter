#include <stdio.h>

int main(int argc, char** argv) {
    FILE* bf_file = fopen(argv[1], "r");
    fseek(bf_file, 0, SEEK_END)
    
    long int size = ftell(bf_file);
    char tape[30000] = {0};
    char* dp = tape;
    char bf_code[size+1];
    bf_code[size] = '\0';
    
    fseek(bf_file, 0, SEEK_SET);
    fread(bf_code, sizeof(char), size, bf_file); // reading data from the bf file and storing it in array
    fclose(bf_file);
    
    for (int i = 0; bf_code[i]; ++i) {
        if (bf_code[i] == '>')
            ++dp;
        else if (bf_code[i] == '<')
            --dp;
        else if (bf_code[i] == '+')
            ++*dp;
        else if (bf_code[i] == '-')
            --*dp;
        else if (bf_code[i] == '.')
            printf("%c", *dp);
        else if (bf_code[i] == ',')
            scanf("%c", dp);
        else if (bf_code[i] == '[') {
            if (*dp == 0) {
                //each time [ is encountered increment counter, each time ] is encountered decrement counter, when counter is 0 weve hit the matching ]; same goes for ] but just in reverse
                int counter = 1;
                while (counter != 0) {
                    ++i;
                    if (bf_code[i] == '[')
                        ++counter;
                    else if (bf_code[i] == ']')
                        --counter;
                }
            }
        }
        else if (bf_code[i] == ']') {
            if (*dp != 0) {
                int counter = 1;
                while (counter != 0) {
                    --i;
                    if (bf_code[i] == ']')
                        ++counter;
                    else if (bf_code[i] == '[')
                        --counter;
                }
            }
        }
    }
    
    return 0;
}
