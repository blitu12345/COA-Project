#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct NODE
{
	struct NODE* child[26];
	int leaf;
	char binarycode[16];
}node;

node* getnode();
node* insertKeyword(node* root, char* keyword, char* binaryCodeOfKeyword);
void convertDecimalToBinary(int number, char* binaryRepresentationOfDecimal);
void getBinaryCodeOfKeyword(node* root, char* keyword, char* machineCode);
void appendBinaryCodeOfOperand(char* machineCode, int operand_value, int start_from);


int main(int argc, char const *argv[])
{
	/* code */
	node* root = NULL;
	FILE* fp1;
	fp1 = fopen("opcode.txt","r");
	char opcode[100];
	char binarycode[100];

	while(fscanf(fp1,"%s %s",opcode,binarycode)!=EOF) {
		root = insertKeyword(root, opcode, binarycode);
	}	
	FILE* fp2;
	FILE* fp3;
	fp2 = fopen("instructions.txt","r");
	fp3 = fopen("machineCodes.txt","w");
	char current_instruction[100];
	int operand1;
	int operand2;
	int operand3;
	while(fscanf(fp2,"%s",current_instruction) != EOF) {
		char machineCode[50];
		getBinaryCodeOfKeyword(root, current_instruction, machineCode);
		int lenOfInstruction = strlen(machineCode);
		switch(lenOfInstruction) {
			case (4) :
				fscanf(fp2,"%d %d %d",&operand1,&operand2,&operand3);
				getBinaryCodeOfKeyword(root, current_instruction, machineCode);
				appendBinaryCodeOfOperand(machineCode,operand1,4);
				appendBinaryCodeOfOperand(machineCode,operand2,8);
				appendBinaryCodeOfOperand(machineCode,operand1,12);
				fprintf(fp3, "%s\n", machineCode);
				break;
			case (8) :
				fscanf(fp2,"%d %d",&operand1,&operand2);
				getBinaryCodeOfKeyword(root, current_instruction, machineCode);
				appendBinaryCodeOfOperand(machineCode,operand1,8);
				appendBinaryCodeOfOperand(machineCode,operand2,12);
				fprintf(fp3, "%s\n", machineCode);
				break;
			case (12) :
				fscanf(fp2,"%d",&operand1);
				getBinaryCodeOfKeyword(root, current_instruction, machineCode);
				appendBinaryCodeOfOperand(machineCode,operand1,12);
				fprintf(fp3, "%s\n", machineCode);
				break;
			case (16) :
				getBinaryCodeOfKeyword(root, current_instruction, machineCode);
				fprintf(fp3, "%s\n", machineCode);
				break;
			default:
				break;
		}
	}
	return 0;
}

node* getnode() {
	node* new_node;
	new_node = (node*)malloc(sizeof(node));
	new_node->leaf = 0;
	return new_node;
}

node* insertKeyword(node* root, char* keyword, char* binaryCodeOfKeyword)
{
	if(root == NULL){
		root = getnode();
	}
	node* v = root;
	int i = 0;
	while(keyword[i] != '\0'){
		node* temp = v->child[keyword[i] - 'A'];
		if(temp == NULL){
			temp = v->child[keyword[i] - 'A'] = getnode();
		}
		v = temp;
		i++;
	}
	v->leaf = 1;
	strcpy(v->binarycode, binaryCodeOfKeyword);
	return root;
}

void convertDecimalToBinary(int number, char* binaryRepresentationOfDecimal)
{
	int ind = 0;
	while(number > 0){
		binaryRepresentationOfDecimal[ind] = (number % 2) + '0';
		number >>= 1;
		ind++;
	}
	binaryRepresentationOfDecimal[ind] = '\0';
	
	int i = 0;
	int j = ind - 1;
	for(;i < j; i++,j--){
		char temp = binaryRepresentationOfDecimal[i];
		binaryRepresentationOfDecimal[i] = binaryRepresentationOfDecimal[j];
		binaryRepresentationOfDecimal[j] = temp;
	}
	int len = strlen(binaryRepresentationOfDecimal);
	char bin[4];
	i = 0;
	int k=0;
	for(i = 0;i < 4 - len;i++){
		bin[i] = '0';
	}
	for(i = 4 - len,k = 0;i < 4; i++,k++){
		bin[i] = binaryRepresentationOfDecimal[k];
	}
	strcpy(binaryRepresentationOfDecimal,bin);
}

void getBinaryCodeOfKeyword(node* root, char* keyword, char* machineCode)
{
	node* v = root;
	int i = 0;
	while(keyword[i] != '\0'){
		node* temp = v->child[keyword[i] - 'A'];
		v = temp;
		i++;
	}
	strcpy(machineCode,v->binarycode);
}

void appendBinaryCodeOfOperand(char* machineCode, int operand_value, int start_from)
{
	char BinarycodeOfDecimal[100];
	convertDecimalToBinary(operand_value,BinarycodeOfDecimal);
	int ind = 0;
	for(ind = 0;ind < 4;ind++,start_from++){
		machineCode[start_from] = BinarycodeOfDecimal[ind];
	}
	machineCode[start_from] = '\0';
	printf("%s\n",machineCode);
}