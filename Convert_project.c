#include <stdio.h>
#include <ctype.h>
#define FILE_INPUT "input.txt"
#define FILE_OUTPUT "output.txt"

int main() {
    FILE *fp_in , *fp_out;
    char ch , ch_prec;
    int counter , flag , flag1,count_read , my_var;
    fp_in = fopen(FILE_INPUT , "r");
    fp_out = fopen(FILE_OUTPUT , "w");
    if(fp_in==NULL || fp_out==NULL) {
        printf("error opening file\n");
        return 1;
    }

    ch_prec = 'a';
    counter = 0;
    count_read = 0;
    flag1 = 0;
    while(!feof(fp_in)){
        flag = 0;
        ch = fgetc(fp_in);
        count_read++;
        if (!feof(fp_in)){
            if (flag == 1 && islower(ch)) {
                fprintf(fp_out, "%c", toupper(ch));
                counter++;
                flag1=0;
            }
            else{
                if (ch=='\r'){
                    my_var =42;
                    count_read--;
                    counter--;
                    continue;
                }
                if (ispunct(ch_prec)){
                    if (!isspace(ch)){
                        fputc(' ',fp_out);
                        counter++;
                        count_read++;
                    }
                    if ((ch_prec == '.' || ch_prec =='!' || ch_prec == '?') && islower(ch)){
                        fputc(toupper(ch) , fp_out);
                        counter++;
                        flag = 1 ;
                    }
                    if ((ch_prec == '.' || ch_prec =='!' || ch_prec == '?') && ch =='\n'){
                        flag = 1 ;
                    }


                }
                if (isdigit(ch)){
                    fprintf(fp_out,"*");
                    flag = 1;
                    counter++;
                }
                if (flag==0 && ch != '\n'){
                    fprintf(fp_out,"%c",ch);
                    counter++;
                }
                if(ch=='\n' && count_read<25){
                    count_read++;
                    for (;counter<25 ; counter++) {
                        fprintf(fp_out," ");
                    }
                }
                if (counter == 25){
                    fprintf(fp_out,"| c:%d\n",count_read);
                    counter = 0;
                    count_read =0;
                }
                ch_prec = ch;

            }
        } else{
            if(count_read <25){
                count_read--;
                for(;counter<25 ;counter++){
                    fprintf(fp_out," ");
                }
            }
            if(counter==25){
                fprintf(fp_out,"| c:%d\n" ,count_read);
                counter = 0;
                count_read = 0;
            }
        }
    }
    fclose(fp_in);
    fclose(fp_out);


    return 0;
}
