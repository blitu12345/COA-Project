#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define registers_count 8
#define flag_count 8
#define number_Of_Images 15

int reg[registers_count]; // declared 8 registers
int flag[flag_count];  // declared flag
int image_status[number_Of_Images];

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
int check_pow();
void getOperand(char* binaryCodeOfInstruction, char* opernad, int start);
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
	for(i = 0;i < registers_count; i++){
		reg[i] = 0;
	}
	for(i = 0;i < flag_count; i++){
		flag[i] = 0;
	}
	FILE* fimages;
	fimages = fopen("imagesdetails.txt","r");
	int image;
	while(fscanf(fimages,"%d ",&image) != EOF)
	{
		image_status[image - 1] = 1;
	}
	node* root = getBinaryCodesTrie(); //
	FILE* fpstatus;
	fpstatus = fopen("status.txt","w");
	FILE* fp;
	fp = fopen("machineCode.txt","r");  // open machine code containing file
	char binaryCodeOfInstruction[100];
	while(fscanf(fp,"%s",binaryCodeOfInstruction))
	{
		if(check_binary_code(binaryCodeOfInstruction) == 0) {
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
		} else if(val2 == -1){
			flag_index = val1;
		} else {
			command_index = val1;
			number_Of_Operands = val2;
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
	node* root = getnode();
	FILE* fp;
	fp = fopen("BinaryCodesTable.txt","r");
	char opcode[10],binaryCode[16];
	int commandindex = 0;
	int flagindex = 0;

	while(fscanf(fp,"%s %s",opcode,binaryCode) != EOF)
	{
		int len = strlen(binaryCode);
		int isFlag = 0;
		if(len == 16){
			isFlag = 1;
		}
		node* v = root;
		int ind = 0;
		while(binaryCode[ind] != '\0'){
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
void getOperand(char* binaryCodeOfInstruction, char* operand, int start)
{
	int ind = 0;
	while(ind <= 3){
		operand[ind++] = binaryCodeOfInstruction[start++];
	}
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
int check_binary_code(char* binaryCode)
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
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
		return;
	}
	char operandBinaryCode1[10];
	char operandBinaryCode2[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,8);
	getOperand(binaryCodeOfInstruction,operandBinaryCode2,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	int operand2 = convertBinaryToDecimal(operandBinaryCode2);
	reg[0] = 1;
	///****************************///
	if(operand2 == 0){
		system("python view.py %d",operand1);
	} else if(operand2 == 1) {
		system("python delete.py %d",operand1);
	}
	fprintf(fpstatus,"GAL executed \n", );
}
void MFS(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
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
	print_status(fpstatus);
	system("python mfs.py %d %d %d",operand1, operand2, operand3);
}
void SHS(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	long long val = pow(operand1,6);
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
	print_status(fpstatus);
	reg[2] = (int)val;
}
void ISO(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	long val = pow(2,operand1);
	if(val >= 2000){
		flag[5] = 1;
	}
	if(val < 0){
		flag[6] = 1;
	}
	if(val == 0){
		flag[7] = 1;
	}
	print_status(fpstatus);
	reg[3] = (int)val;
}
void ZOM(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
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
	print_status(fpstatus);
	reg[4] = (int)val;
	reg["SHS"] = operand1* (equation);
}
void MOD(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
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
	print_status(fpstatus);
	reg[5] = (int)val;
}
void APR(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
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
	print_status(fpstatus);
	reg[6] = (int)val;
}
void SLT(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
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
	print_status(fpstatus);
	reg[7] = (int)val;
	system("python wait.py %d",reg[7]);
	reg[7] = 1;
}
void POW(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	flag[0] = 0;
	flag["SHS"] = 0 || 1;
	FILE* fp;
	fp = fopen("POWER.txt","w");
}
void FLS(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	flag[1] = 0;
	flag["SHS"] = 1 || 0;
}
void CLP(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	flag[2] = 0;
	flag["SHS"] = 1 || 0;
}
void MME(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	flag[3] = 0;
	flag["SHS"] = 1 || 0;
}
void HLT(char* binaryCodeOfInstruction, FILE* fpstatus)
{
	int power_status = check_pow();
	if(check_pow() == 0){
		fprintf(fpstatus,"Device is off.Gallery command not executed\n");
		return;
	}
	char operandBinaryCode1[10];
	getOperand(binaryCodeOfInstruction,operandBinaryCode1,12);
	int operand1 = convertBinaryToDecimal(operandBinaryCode1);
	flag[4] = 1;
	exit(0);
}
void print_status(FILE* fpstatus)
{
	if(flag[5] == 1) fprintf(fpstatus,"Overflow Flag : Set ");
	else fprintf(fpstatus,"Overflow Flag : Unset ");
	if(flag[6] == 1) fprintf(fpstatus,"Negative Flag : Set ");
	else fprintf(fpstatus,"Negative Flag : Unset ");
	if(flag[7] == 1) fprintf(fpstatus,"Zero Flag : Set");
	else fprintf(fpstatus,"Zero Flag : Unset");
	fprintf(fpstatus,"\n");
}
