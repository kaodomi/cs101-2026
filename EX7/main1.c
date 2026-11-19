#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    int n;
    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩:");
    scanf("%d", &n);

    if (n < 1 || n > 5) {
        printf("購買組數請輸入 1 到 5 之間！\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    time_t curtime;
    time(&curtime);
    char *time_str = ctime(&curtime);
    time_str[strlen(time_str) - 1] = '\0';

    FILE *fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        printf("無法開啟 lotto.txt\n");
        return 1;
    }

    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "= %s =\n", time_str);

    for (int i = 1; i <= 5; i++) {
        fprintf(fp, "[%d]: ", i);
        if (i <= n) {
            int nums[7];
            int count = 0;

            while (count < 7) {
                int r = (rand() % 69) + 1;
                int duplicate = 0;
                for (int j = 0; j < count; j++) {
                    if (nums[j] == r) {
                        duplicate = 1;
                        break;
                    }
                }
                if (!duplicate) {
                    nums[count++] = r;
                }
            }

            for (int j = 0; j < 7; j++) {
                fprintf(fp, "%02d%s", nums[j], (j == 6) ? "" : " ");
            }
            fprintf(fp, "\n");
        } else {
            fprintf(fp, "-- -- -- -- -- -- --\n");
        }
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

    printf("以為您購買的%d組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}
