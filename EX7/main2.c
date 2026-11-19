#include <stdio.h>
#include <string.h>

typedef struct Books {
    int id;
    int price;
    char title[64];
} book_t;

void total_price(book_t books[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += books[i].price;
    }
    printf("Total price = %d\n\n", sum);
}

void list_books(book_t books[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Book ID    = %d\n", books[i].id);
        printf("Book Price = %d\n", books[i].price);
        printf("Book Title = %s\n\n", books[i].title);
    }
}

void book_writefile(book_t books[], int n) {
    FILE *fp = fopen("Book.bin", "wb+");
    if (fp == NULL) {
        printf("無法寫入 Book.bin\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fwrite(&books[i], sizeof(book_t), 1, fp);
    }
    fclose(fp);
}

void book_readfile(book_t books[], int n) {
    FILE *fp = fopen("Book.bin", "rb");
    if (fp == NULL) {
        printf("無法讀取 Book.bin\n");
        return;
    }
    int i = 0;
    while (i < n && fread(&books[i], sizeof(book_t), 1, fp)) {
        i++;
    }
    fclose(fp);
}

int main() {
    book_t books[6] = {
        {1, 1000, "All the Light We Cannot See"},
        {2,  300, "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4,  550, "Killers of the Flower Moon"},
        {5,  870, "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    book_writefile(books, 6);

    book_t read_books[6];
    book_readfile(read_books, 6);

    total_price(read_books, 6);
    list_books(read_books, 6);

    return 0;
}
