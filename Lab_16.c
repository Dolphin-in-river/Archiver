#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

long long getFileSize(const char* file_name) {
	long long file_size = 0;
	FILE* f = fopen(file_name, "rb");
	if (f == NULL) {
		file_size = -1;
	}
	else {
		fseek(f, 0, SEEK_END);
		file_size = ftell(f);
		fclose(f);
	}
	return file_size;
}

void creat(int argc, char *argv[], char *namearch) {
	FILE *nf = fopen(namearch, "wb");
	long long temp = argc - 4;
	fwrite(&temp, sizeof(long long), 1, nf);
	printf("%d\n", temp);
    int i = 4;
    while (i < argc) {
		FILE *f = fopen(argv[i], "rb");
		fwrite(argv[i], 1, 40, nf);
		long long size = getFileSize(argv[i]);
		fwrite(&size, sizeof(long long), 1, nf);
		char tmp[1000];
		fread(&tmp, 1, 1000 * sizeof(char), f);
		int cnt;
        int j;
		//fseek(f, 0, SEEK_SET);
        int kol_vo = 0;
        for (j = 0; j < size; j++){
            if (tmp[j] != tmp[j+1]){
                kol_vo++;
                fwrite(&kol_vo, 1, sizeof(int), nf);
                fwrite(&tmp[j], 1, sizeof(char), nf);
                kol_vo = 0;
            } else
                kol_vo++;
		}
		fclose(f);
		remove(argv[i]);
		i++;
	}

	fclose(nf);
}

void extract(char *archname) {
	FILE *f = fopen(archname, "r+b");
	char buffer[8];
	fread(buffer, 1, 8, f);
	int i = 0;
	long long count = 0;
	while (i < 8) {
	    count += buffer[i] * powl(256, i);
		i++;
	}
	//count = buffer[0] + buffer[1] * 256 + buffer[2] * 256 * 256 + buffer[3] * 256 * 256 * 256 + buffer[4]*256*256*256;
	printf("%d", count);
	while (count != 0) {
		char filename[40] = {0};
		long long size = 0;
		char buff[8];
		fread(&filename, 1, 40, f);
		printf("%s\n", filename);
		FILE *nf = fopen(filename, "ab");
		fread(&buff, 1, 8, f);
		int t = 0;
		while (t < 8) {
			size += buff[t] * powl(256, t);
			t++;
		}
		int jj =0;
		while (jj < size*5){
		char *mass = (char*)malloc(sizeof(char)*5);
		fread(mass, 1, 5 * sizeof(char), f);
		int e = 0;
		int num = 0;
		while (e < 4) {
            num += mass[e] * powl(256, e);
			e++;
		}
        printf("Kol-vo: %d\n", num);
        printf("Bukva/Cifra: %c\n", mass[4]);
        int y;
        for (y = 0; y < num; y++)
             fwrite(&mass[4], 1, sizeof(char), nf);
        jj +=5*num;
		}
		fclose(nf);
		count--;
	}
	fclose(f);
}

void lict(char *archname) {
	FILE *f = fopen(archname, "rb");
	char buffer[8];
	fread(buffer, 1, 8, f);
	int i = 0;
	long long count = 0;
	while (i < 8) {
		count += buffer[i] * powl(256, i);
		i++;
	}
	while (count != 0) {
		char *filename = (char*)malloc(40 * sizeof(char));
		long long size = 0;
		char buff[8];
		fread(filename, 1, 40, f);
		fread(buff, 1, 8, f);
		int t = 0;
		while (t < 8) {
			size += buff[t] * powl(256, t);
			t++;
		}
		int jj=0;
        while (jj < size*5){
		char *mass = (char*)malloc(sizeof(char)*5);
		fread(mass, 1, 5 * sizeof(char), f);
		int e = 0;
		int num = 0;
		while (e < 4) {
            num += mass[e] * powl(256, e);
			e++;
		}
        jj +=5*num;
		}
		//fseek(f, size, SEEK_CUR);
		fputs(filename, stdout);
		printf("\n");
		count--;
	}
}




int main(int argc, char *argv[]) {
	int c = 0;
	int e = 0;
	int l = 0;
	char *namearch = (char*)malloc(sizeof(char)*20);
    int i;
	for (i = 1; i < argc; i++) {
		if (!strcmp("--create", argv[i])) {
			c = 1;
		}
		if (!strcmp("--extract", argv[i]))
			e = 1;
		if (!strcmp("--list", argv[i]))
			l = 1;
	}
	namearch = argv[2];
    if (c == 1) {
		creat(argc, argv, namearch);
	}
	if (e == 1) {
		extract(namearch);
		remove(namearch);
	}
	if (l==1) {
		lict(namearch);
	}

	return 0;
}
//C:\Users\Иван\Desktop\Proga\Lab_16.exe --file C:\Users\Иван\Desktop\Proga\data.arc --create C:\Users\Иван\Desktop\Proga\a.txt C:\Users\Иван\Desktop\Proga\b.txt
//C:\Users\Иван\Desktop\Proga\Lab_16.exe --file C:\Users\Иван\Desktop\Proga\data.arc --create C:\Users\Иван\Desktop\Proga\a.txt C:\Users\Иван\Desktop\Proga\b.txt
