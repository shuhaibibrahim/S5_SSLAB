#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char bit[12]; //bitmap converted to binary

void convert(char h[12])
{
	int i, l;
	strcpy(bit, "");
	l = strlen(h);
	for (i = 0; i < l; i++)
	{
		switch (h[i])
		{
			case '0':
				strcat(bit, "0000");
				break;
			case '1':
				strcat(bit, "0001");
				break;
			case '2':
				strcat(bit, "0010");
				break;
			case '3':
				strcat(bit, "0011");
				break;
			case '4':
				strcat(bit, "0100");
				break;
			case '5':
				strcat(bit, "0101");
				break;
			case '6':
				strcat(bit, "0110");
				break;
			case '7':
				strcat(bit, "0111");
				break;
			case '8':
				strcat(bit, "1000");
				break;
			case '9':
				strcat(bit, "1001");
				break;
			case 'A':
				strcat(bit, "1010");
				break;
			case 'B':
				strcat(bit, "1011");
				break;
			case 'C':
				strcat(bit, "1100");
				break;
			case 'D':
				strcat(bit, "1101");
				break;
			case 'E':
				strcat(bit, "1110");
				break;
			case 'F':
				strcat(bit, "1111");
				break;
		}
	}
}

void main() 
{
    FILE * fp;

    int i, j, k;
    int start, add, locctr; //add strores strating  address of text record
    int iRecLength, iOperand, len;

    char line[50], staddr[10], recLength[2], opcode[3], operand[10], instr[20];

    char bitmap[12];//bitmap in hexadecimal

    int bitCounter;

    fp = fopen("objProgram.txt", "r");

    fscanf(fp, "%s", line);//header record

    printf("Enter the starting address : ");
    scanf("%d",&start);

    printf("\n");

    add=start;
    locctr=start;

    fscanf(fp, "%s", line);
    while(line[0]!='E')
    {
        add=locctr;

        for(i=9, j=0; i<11; i++, j++)
            recLength[j]=line[i];
        recLength[j]='\0';

        iRecLength=atoi(recLength);

        for(i=12, j=0; i<15; i++, j++)
            bitmap[j]=line[i];
        bitmap[j]='\0';

        convert(bitmap);

        strcpy(instr,"");

        bitCounter=0;
        for(i=16 ,j=0; j<iRecLength;)
        {
            strcpy(opcode,"");
            strcpy(operand,"");

            if(line[i]=='^')
            {
                j+=strlen(instr)/2;;
                i++;
                bitCounter++;
            }
            else
            {
                opcode[0]=line[i++];
                opcode[1]=line[i++];

                opcode[2]='\0';

                operand[0]=line[i++];
                operand[1]=line[i++];
                operand[2]=line[i++];
                operand[3]=line[i++];

                operand[4]='\0';

                // k=0;
                // while(line[i]!='^'&&line[i+1]!="^")
                // {
                //     operand[k]=line[i++];
                //     k++;
                // }
                // line[k]='\0';

                if(bit[bitCounter]=='0')
                    printf("%d\t %s%s\n",locctr,opcode,operand);
                else
                {
                    iOperand=atoi(operand);
                    printf("%d\t %s%d\n",locctr,opcode,iOperand+start);
                }

                strcpy(instr, "");

                strcat(instr,opcode);
                strcat(instr,operand);

                len=strlen(instr);
                locctr+=(len/2);

            }
        }

        fscanf(fp, "%s", line);

    }

    fclose(fp);

}
