#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* otp_encrypt(char* text, char* key) {
	char* output = (char*)malloc((sizeof(char) * (strlen(text) * 2)) + 1);
	char xor;
	int i = 0;

	while (text[i] != '\0') {
		xor = text[i] ^ key[i];
		sprintf(&output[i * 2], "%02x", xor);
		++i;
	}

	output[i * 2] = '\0';

	return output;
}

int main(void) {
	char* text = "kyoto";
	char* key =  "bitse";
	char* output = otp_encrypt(text, key);

	printf("Text: %s\nKey: %s\nOutput: %s\n", text, key, output);
}
