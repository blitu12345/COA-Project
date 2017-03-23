#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define registers_count 8
#define flag_count 9
#define number_Of_Images 16

int reg[registers_count] = {0}; // declared 8 registers
int flag[flag_count] = {0};  // declared flag
int image_status[number_Of_Images] = {0}; // status of images in glallery

typedef struct NODE
{
	struct NODE* child[2];
	int leaf;
	int type;
	int flag_id;
	int command_id;
}node;


node* getnode();
node* getBinaryCodesTrie();
int* getDetailsOfInstruction(node* root, char* binaryCodeOfInstruction);
<<<<<<< HEAD
void getOperand(char* binaryCodeOfInstruction, char* operand, int start);
=======
int check_pow();
void getOperand(char* binaryCodeOfInstruction, char* opernad, int start);
>>>>>>> origin/master
int convertBinaryToDecimal(char* binaryCodeForOperand);
int check_binary_code(char* binaryCode);
void GAL(char* binaryCodeOfInstruction, FILE* fpstatus);
void MFS(char* binaryCodeOfInstruction, FILE* fpstatus);
void SHS(char* binaryCodeOfInstruction, FILE* fpstatus);
void ISO(char* binaryCodeOfInstruction, FILE* fpstatus);
void ZOM(char* binaryCodeOfInstruction, FILE* fpstatus);
void MOD(char* binaryCodeOfInstruction, FILE* fpstatus);
void APR(char* binaryCodeOfInstruction, FILE* fpstatus);
void SLT(char* binaryCodeOfInstruction, FILE* fpstatus);
void POW(char* binaryCodeOfInstruction, FILE* fpstatus);
void FLS(char* binaryCodeOfInstruction, FILE* fpstatus);
void CLP(char* binaryCodeOfInstruction, FILE* fpstatus);
void MME(char* binaryCodeOfInstruction, FILE* fpstatus);
void HLT(char* binaryCodeOfInstruction, FILE* fpstatus);
void print_status(FILE* fpstatus);

int main(int argc, char const *argv[])
{
	int i = 0;
	for(i = 0;i < registers_count; i++){ //initialising all registers to 0
		reg[i] = 0;
	}
	for(i = 0;i < flag_count; i++){ // initialising all flags to 0
		flag[i] = 0;
	}
<<<<<<< HEAD
	for(i = 0;i < number_Of_Images; i++){ // initialising all image_status to 0
		image_status[i] = 0;
=======
	FILE* fimages;
	fimages = fopen("imagesdetails.txt","r");
	int image;
	while(fscanf(fimages,"%d ",&image) != EOF)
	{
		image_status[image - 1] = 1;
>>>>>>> origin/master
	}
	node* root = getBinaryCodesTrie(); // initialising trie with opcodes and binarycode
	FILE* fpstatus;
	fpstatus = fopen("status.txt","w"); // status file 
	FILE* fp;
	fp = fopen("machineCodes.txt","r");  // open machine code containing file
	char binaryCodeOfInstruction[100];
	while(fscanf(fp,"%s",binaryCodeOfInstruction) != EOF)//one by one iterating through machine codes
	{
		if(check_binary_code(binaryCodeOfInstruction) == 0) { //
			printf("Invalid Binary String\n");
			continue;
		}
		int* code = getDetailsOfInstruction(root, binaryCodeOfInstruction);
		int val1 = *(code + 0);
		int val2 = *(code + 1);
		int flag_index = -1,command_index = -1;
		int number_Of_Operands = 0;
		if(val1 == -1 && val2 == -1){
			printf("Invalid Instruction\n");
			continue;
		} else if(val2 == -1){
			flag_index = val1;
		} else {
			command_index = val1;
			number_Of_Operands = val2;
		}
		if(number_Of_Operands == 0){
			switch(flag_index)
			{
				case 0: 
					HLT(binaryCodeOfInstruction,fpstatus);
					break;
				case 1:
					FLS(binaryCodeOfInstruction, fpstatus);
					break;
				case 2:
					CLP(binaryCodeOfInstruction, fpstatus);
					break;
				case 3:
					MME(binaryCodeOfInstruction, fpstatus);
					break;
				case 4:
					POW(binaryCodeOfInstruction, fpstatus);
					break;
				default :
					fprintf(fpstatus,"Invalid Flag\n");
					break;
			}
		} else {
			switch(command_index)
			{
				case 0:
					MFS(binaryCodeOfInstruction, fpstatus);
					break;
				case 1:
					GAL(binaryCodeOfInstruction, fpstatus);
					break;
				case 2:
					SHS(binaryCodeOfInstruction, fpstatus);
					break;
				case 3:
					ISO(binaryCodeOfInstruction, fpstatus);
					break;
				case 4:
					ZOM(binaryCodeOfInstruction, fpstatus);
					break;
				case 5:
					MOD(binaryCodeOfInstruction, fpstatus);
					break;
				case 6:
					APR(binaryCodeOfInstruction, fpstatus);
					break;
				case 7:
					SLT(binaryCodeOfInstruction, fpstatus);
					break;
				default :
					fprintf(fpstatus,"Invalid Command\n");
					break;
			}
		}
	}
	return 0;
}

node* getnode() // setting up node of trie
{
	node* p;
	p = (node*)malloc(sizeof(node)); // allocating memory
	p->leaf = 0; // intialising leaf 
	p->flag_id = p->command_id = p->type = -1; // setting up flag
	return p;
}
node* getBinaryCodesTrie() // create binary trie tree data structure
{
	node* root = getnode(); // allocating memory
	FILE* fp;
	fp = fopen("BinaryCodesTable.txt","r");
	char opcode[10],binaryCode[16];
	int commandindex = 0;
	int flagindex = 0;

<<<<<<< HEAD
	while(fscanf(fp,"%s %s",opcode,binaryCode) != EOF) // loading binary codes into trie
=======
	while(fscanf(fp,"%s %s",opcode,binaryCode) != EOF)
>>>>>>> origin/master
	{
		int len = strlen(binaryCode);
		int isFlag = 0;
		if(len == 16){ //flag if length of its binary code is 16
			isFlag = 1;
		}
		node* v = root;
		int ind = 0;
		while(binaryCode[ind] != '\0'){ // iterarting trie with each binary code's elements
			node* temp = v->child[binaryCode[ind] - '0'];
			if(temp == NULL){
				temp = v->child[binaryCode[ind] - '0'] = getnode();
			}
			v = temp;
			ind++;
		}
		v->leaf = 1;
		if(isFlag){
			v->flag_id = flagindex;
			flagindex++;
		} else {
			v->command_id = commandindex;
			commandindex++;
		}
		v->type = (16 - len)/4;
	}
	return root;
}

int* getDetailsOfInstruction(node* root, char* binaryCodeOfInstruction)
{
	node* v = root;
	static int code[2];
	code[0] = code[1] = -1;
	int ind = 0;
	while(binaryCodeOfInstruction[ind] != '\0')
	{
		node* temp = v->child[binaryCodeOfInstruction[ind] - '0'];
		if(temp == NULL){
			return code;
		}
		if(temp->leaf == 1){
			if(temp->flag_id != -1){
				code[0] = temp->flag_id;
			} else {
				code[0] = temp->command_id;
				code[1] = temp->type;
			}
			break;
		}
		v = v->child[binaryCodeOfInstruction[ind] - '0'];
		ind++;
	}
	return code;
}

<<<<<<< HEAD
=======
int check_pow()
{
	FILE* fpread;
	fpread = fopen("POWER.txt","r");
	char power[100],condition[100];
	char OFF[3] = "OFF";
	char ON[2] = "ON";
	while(fscanf(fpread,"%s %s",power,condition) != EOF)
	{
		if(strcmp(condition,OFF) == 0){
			return 0;
		} else if(strcmp(condition,ON) == 0){
			return 1;
		}
	}
	return -1;
}
>>>>>>> origin/master
void getOperand(char* binaryCodeOfInstruction, char* operand, int start)
{
	int ind = 0;
	while(ind <= 3){
		operand[ind++] = binaryCodeOfInstruction[start++];
	}
	operand[ind] = '\0';
}
int convertBinaryToDecimal(char* binaryCodeForOperand)
{
	int val = 0;
	int ind = 0;
	while(binaryCodeForOperand[ind] != '\0')
	{
		val *= 2;
		val += binaryCodeForOperand[ind] - '0';
		ind++;
	}
	return val;
}
int check_binary_code(char* binaryCode) // checking binary code elememnts
{
	int ind = 0;
	while(binaryCode[ind] != '\0') {
		if(binaryCode[ind] != '0' && binaryCode[ind] != '1'){
			return 0;
		}
		ind++;
	}
	return 1;
}

void GAL(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
		print_status(fpstatus);
		return;
	}
	char operandBinaryCode1[10];
	char operandBinaryCode2[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,8);
	getOperand(binaryCodeOfInstruction,operandBinaryCode2,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	int operand2 = convertBinaryToDecimal(operandBinaryCode2);
	reg[0] = 1;
	if(image_status[operand1 - 1] == 0){
		fprintf(fpstatus,"Image not exist in Library\n");
		return;
	}
	char command1[100] = "python view.py ";
	char command2[100] = "python delete.py ";
	char str[10];
  	sprintf(str, "%d", operand1);
	strcat(command1,str);
	strcat(command2,str);
	fprintf(fpstatus,"%s %s\n",command1,command2);
	if(operand2 == 0){
		system(command1);
	}else if(operand2 == 1) {
		system(command2);
		image_status[operand1 - 1] = 0;
	}
	flag[8] = 0;
	print_status(fpstatus);
	fprintf(fpstatus,"GAL successfully executed\n");
}
void MFS(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0){
		fprintf(fpstatus,"Device is off.Manual Focus command not executed\n");
		print_status(fpstatus);
		return;
	}
	char operandBinaryCode1[10];
	char operandBinaryCode2[10];
	char operandBinaryCode3[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,4);
	getOperand(binaryCodeOfInstruction,operandBinaryCode2,8);
	getOperand(binaryCodeOfInstruction,operandBinaryCode3,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	int operand2 = convertBinaryToDecimal(operandBinaryCode2);
	int operand3 = convertBinaryToDecimal(operandBinaryCode3);
	reg[1] = 1;
	flag[8] = 0;
	print_status(fpstatus);
	char command[100] = "python try.py ";
	char str[30];
	sprintf(str, "%d", operand1);
	strcat(command,str);
	strcat(command," ");
	sprintf(str, "%d", operand2);
	strcat(command,str);
	strcat(command," ");
	sprintf(str, "%d", operand3);
	strcat(command,str);
	system(command);
	fprintf(fpstatus,"MFS successfully executed\n");
}
void SHS(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0 || reg[5] == 1){
		fprintf(fpstatus,"Device is off.Shutter Speed command not executed\n");
		print_status(fpstatus);
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	long long val = pow((double)operand1,6);
	val /= 6000;
	reg[2] = val;
	if(val >= 2000){
		flag[5] = 1;
	}
	if(val < 0){
		flag[6] = 1;
	}
	if(val == 0){
		flag[7] = 1;
	}
	flag[8] = 1;
	print_status(fpstatus);
	reg[2] = (int)val;
	fprintf(fpstatus,"SHS successfully executed\n");
}

void ISO(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0 || reg[5] == 1){
		fprintf(fpstatus,"Device is off.ISO set command not executed\n");
		print_status(fpstatus);
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	long val = pow(2.0,operand1);
	if(val >= 2000){
		flag[5] = 1;
	}
	if(val < 0){
		flag[6] = 1;
	}
	if(val == 0){
		flag[7] = 1;
	}
	flag[8] = 1;
	print_status(fpstatus);
	reg[3] = (int)val;
	fprintf(fpstatus,"ISO successfully executed\n");
}

void ZOM(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0){
		fprintf(fpstatus,"Device is off.ZOM set command not executed\n");
		print_status(fpstatus);
		return;
	}
	char operandBinaryCode1[100];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	if(operand1 >= 2000){
		flag[5] = 1;
	}
	if(operand1 < 0){
		flag[6] = 1;
	}
	if(operand1 == 0){
		flag[7] = 1;
	}
	flag[8] = 0;
	char command[100] = "python zoom.py ";
	char str[30];
	sprintf(str, "%d", operand1);
	strcat(command,str);
	system(command);
	print_status(fpstatus);
	reg[4] = operand1;
	fprintf(fpstatus,"ZOM successfully executed\n");
}

void MOD(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0){
		fprintf(fpstatus,"Device is off.Mode command not executed\n");
		print_status(fpstatus);
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	long val = operand1;
	if(val >= 2000){
		flag[5] = 1;
	}
	if(val < 0){
		flag[6] = 1;
	}
	if(val == 0){
		flag[7] = 1;
	}
	flag[8] = 0;
	print_status(fpstatus);
	reg[5] = operand1;
	fprintf(fpstatus,"MOD successfully executed\n");
}

void APR(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0){
		fprintf(fpstatus,"Device is off.Aperture command not executed\n");
		print_status(fpstatus);
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	long val = operand1;
	if(val >= 2000){
		flag[5] = 1;
	}
	if(val < 0){
		flag[6] = 1;
	}
	if(val == 0){
		flag[7] = 1;
	}
	flag[8] = 0;
	print_status(fpstatus);
	reg[6] = (int)val;
	fprintf(fpstatus,"APR successfully executed\n");
}
void SLT(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0){
		fprintf(fpstatus,"Device is off.Self-Timer command not executed\n");
		print_status(fpstatus);
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	long val = operand1;
	if(val >= 2000){
		flag[5] = 1;
	}
	if(val < 0){
		flag[6] = 1;
	}
	if(val == 0){
		flag[7] = 1;
	}
	flag[8] = 0;
	print_status(fpstatus);
	reg[7] = (int)val;
	char str[30];
	char command[100] = "python selftimer.py ";
	sprintf(str, "%d", reg[7]);
	strcat(command,str);
	system(command);
	int i = 0,check = -1;
	for(i = 0;i < number_Of_Images; i++){
		if(image_status[i] == 0){
			image_status[i] = 1;
			check = 1;
			break;
		}
	}
	if(check == -1){
		fprintf(fpstatus,"Memory Full. Can't click the pic\n");
		print_status(fpstatus);
		return;
	}
	reg[7] = 0;
	fprintf(fpstatus,"SLT successfully executed\n");
}
void POW(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0) flag[0] = 1;
	else flag[0] = 0;
	flag[8] = 0;
	print_status(fpstatus);
	fprintf(fpstatus,"POW successfully executed\n");
	if(flag[0] == 0) fprintf(fpstatus,"System is turned off\n");
	else fprintf(fpstatus,"System is turned on\n");
}
void FLS(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0){
		fprintf(fpstatus,"Device is off.Flash command not executed\n");
		print_status(fpstatus);
		return;
	}
	flag[1] = 1;
	flag[1] = 0;
	flag[8] = 0;
	print_status(fpstatus);
	fprintf(fpstatus,"FLS successfully executed\n");
}
void CLP(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0){
		fprintf(fpstatus,"Device is off.Click Pic command not executed\n");
		print_status(fpstatus);
		return;
	}
	int operand1 = -1;
	int i  = 0;
	for(i = 0;i < number_Of_Images; i++) {
		if(image_status[i] == 0){
			operand1 = i + 1;
			break;
		}
	}
	if(operand1 == -1){
		fprintf(fpstatus,"Memory Full. Can't click the pic\n");
		print_status(fpstatus);
		return;
	}
	flag[2] = 0;
	char command[100] = "python capture.py ";
	char str[10];
  	sprintf(str, "%d", operand1);
	strcat(command,str);
	system(command);
	image_status[operand1 - 1] = 1;
	flag[8] = 0;
	print_status(fpstatus);
	fprintf(fpstatus,"CLP successfully executed\n");
}
void MME(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	if(flag[0] == 0){
		fprintf(fpstatus,"Device is off.Movie Mode  command not executed\n");
		print_status(fpstatus);
		return;
	}
	flag[3] = 0;
	flag[8] = 0;
	char command[100] = "python mme.py ";
	system(command);
	print_status(fpstatus);
	fprintf(fpstatus,"MME successfully executed\n");
}
void HLT(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	flag[4] = 1;
	flag[8] = 0;
	print_status(fpstatus);
	fprintf(fpstatus,"HLT successfully executed\n");
	exit(0);
}
void print_status(FILE* fpstatus)
{
	if(flag[5] == 1) fprintf(fpstatus,"Overflow Flag : Set || ");
	else fprintf(fpstatus,"Overflow Flag : Unset || ");
	if(flag[6] == 1) fprintf(fpstatus,"Negative Flag : Set || ");
	else fprintf(fpstatus,"Negative Flag : Unset || ");
	if(flag[7] == 1) fprintf(fpstatus,"Zero Flag : Set || ");
	else fprintf(fpstatus,"Zero Flag : Unset || ");
	if(flag[8] == 1) fprintf(fpstatus,"ALU Operation Flag : Set");
	else fprintf(fpstatus,"ALU Operation Flag : Unset");
	flag[5] = flag[6] = flag[7] = flag[8] = 0;
	fprintf(fpstatus,"\n");
}
