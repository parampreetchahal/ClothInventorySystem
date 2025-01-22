#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define ENTER 13
#define BKSP 8
#define SPACE 32
#define TAB 9

void COLOR(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

struct GOODS
{
    char item_name[40], item_qua[40], c;
    int item_id;
    int cost;
    int number;
} st;

void wel_come(void);
void title(void);
void login();
void menu(void);
void deleteproduct(void);

void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void add_GOODS();
void read_GOODS();
void search_GOODS();
void edit_GOODS();
void total_bill();

int main()
{
    wel_come();
    login();
}

void wel_come(void)
{
    time_t t;
    time(&t);

    printf("WELCOME TO CHAHAL CLOTHING STORE\n");
    printf("%s", ctime(&t));
    printf("\nPress enter to continue\n");

    getch();
    system("cls");
}

void login()
{
    int a = 0, i = 0;
    char uname[10], c = ' ';
    char pword[10];
    do
    {
        printf("\nEnter username and password to login\n");
        printf("USERNAME: ");
        scanf("%s", uname);
        printf("PASSWORD: ");

        while (i < 10)
        {
            pword[i] = getch();
            c = pword[i];
            if (c == ENTER)
                break;
            else
                printf("*");
            i++;
        }
        pword[i] = '\0';
        i = 0;

        if (strcmp(uname, "admin") == 0 && strcmp(pword, "admin") == 0)
        {
            printf("\nLOGIN SUCCESSFUL");
            printf("\nCHAHAL CLOTHING STORE EXTENDS YOUR WARM WELCOME");
            printf("\n\nWAIT UNTIL THE SYSTEM IS LOADING.......\n");
            for (i = 0; i < 3; i++)
            {
                printf(".");
                Sleep(500);
            }
            printf("\nPress enter to continue");
            getch();
            break;
        }
        else
        {
            printf("\nLOGIN UNSUCCESSFUL. TRY AGAIN");
            a++;
            getch();
        }
    } while (a <= 2);

    if (a > 2)
    {
        printf("\nToo many failed attempts. Exiting...");
        getch();
    }
    system("cls");
    menu();
}

void menu(void)
{
    int choice;
    system("cls");
main:
    printf("\nMAIN MENU");
    printf("\n1. Add items");
    printf("\n2. Delete items");
    printf("\n3. Search items");
    printf("\n4. View items");
    printf("\n5. Edit item");
    printf("\n6. Calculate Bill");
    printf("\n7. Exit");

    printf("\n Enter your choice from the above option");
    scanf("%i", &choice);

    system("cls");
    switch (choice)
    {
    case 1:
        add_GOODS();
        break;
    case 2:
        deleteproduct();
        break;
    case 3:
        search_GOODS();
        break;
    case 4:
        read_GOODS();
        break;
    case 5:
        edit_GOODS();
        break;
    case 6:
        total_bill();
        break;
    case 7:
        printf("EXIT");
        exit(0);
        break;

    default:
        printf("Invalid choice\n");
        break;
    }
}

void add_GOODS()
{
    int index, valid;
    char c;
    int a = 0;
    FILE *fp;
    do
    {
        system("cls");
        printf("Enter Item Details: ");
        int ID;
        fp = fopen("NextFile.dat", "a+");
        if ((fp = fopen("NextFile.dat", "a+")) != NULL)
        {
        I:
            printf("\nItem Code\t :");
            scanf("%i", &ID);
            while (fscanf(fp, "%s %s %i %i %i", st.item_name, st.item_qua, &st.cost, &st.item_id, &st.number) != EOF)
            {
                if (ID == st.item_id)
                {
                    printf("\nThis product code already exits\n");
                    goto I;
                }
            }
            st.item_id = ID;
        }
        else
        {
            printf("\nItem code\t :");
            scanf("%i", &st.item_id);
        }
        do
        {

            fflush(stdin);
            printf("\nItem Name\t :");
            gets(st.item_name);
            st.item_name[0] = toupper(st.item_name[0]);

            for (index = 0; index < strlen(st.item_name); ++index)
            {
                if (isalpha(st.item_name[index]))
                {
                    valid = 1;
                }
                else
                {
                    valid = 0;
                    break;
                }
            }
            if (!valid)
            {
                printf("\nInvalid entry! Try again");
                getch();
            }
        } while (!valid);

        do
        {
            char item_qua[40];
            fflush(stdin);
            printf("\nItem Brand\t :");
            gets(st.item_qua);
            st.item_qua[0] = toupper(st.item_qua[0]);

            for (index = 0; index < strlen(st.item_qua); ++index)
            {
                if (isalpha(st.item_qua[index]))
                {
                    valid = 1;
                }
                else
                {
                    valid = 0;
                    break;
                }
            }
            if (!valid)
            {
                printf("\nInvalid entry! Try again");
                getch();
            }
        } while (!valid);

        do
        {
            printf("\ncost [10-5000]$:");
            scanf("%i", &st.cost);
            if (st.cost < 10 || st.cost > 5000)
            {
                printf("\n\tYou Cannot Enter the cost Limit [10-5000]. Re-Enter. ");
            }
        } while (st.cost < 10 || st.cost > 5000);

        do
        {
            printf("\nQuantity [1-500]$:");
            scanf("%i", &st.number);
            if (st.number < 1 || st.number > 500)
            {
                printf("\n\tYou Cannot Enter the cost Limit [1-500]. Re-Enter. ");
            }
        } while (st.number < 1 || st.number > 500);

        fp = fopen("NextFile.dat", "a");
        fprintf(fp, "\n%s %s %i %i %i", st.item_name, st.item_qua, st.cost, st.item_id, st.number);
        fclose(fp);
        printf("\nPress 'Enter' to add more GODDS and any oyher key to go to main menu ");
    } while ((c = getch()) == '\r');
    menu();
}

void search_GOODS()
{
    char target[40];
    int found = 0;
    FILE *sfile = fopen("NextFile.dat", "r");
    printf("\nenter name to serach: ");
    fflush(stdin);
    gets(target);
    target[0] = toupper(target[0]);
    while (!feof(sfile) && found == 0)
    {
        fscanf(sfile, "%s %s %i %i %i", st.item_name, st.item_qua, &st.cost, &st.item_id, &st.number);
        if (strcmp(target, st.item_name) == 0)
        {
            found = 1;
        }

        if (found)
        {
            printf("\n Record Found");
            printf("\nItem name\t\t:%s \nBrand of the item\t\t:%s \ncost of the item\t\t:%i \nItem id\t\t:%i \nQuantity\t:%i", st.item_name, st.item_qua, st.cost, st.item_id, st.number);
        }
        else
        {
            printf("\n\tRecord Not Found");
            fclose(sfile);
            printf("\npress enter to go to the main menu");
            while ((st.c = getch()) == '\r ')
                ;
            menu();
        }
    }
}

void deleteproduct(void)
{
    char target[40];
    int found = 0;
    FILE *sfile, *tfile;
    sfile = fopen("NextFile.dat", "r");
    tfile = fopen("TempFile.dat", "w+");
    printf("\n Enter the item mane to delete: ");
    fflush(stdin);
    scanf("%s", target);
    target[0] = toupper(target[0]);
    while (fscanf(sfile, "%s %s %i %i %i", st.item_name, st.item_qua, &st.cost, &st.item_id, &st.number) != EOF)
    {

        if (strcmp(target, st.item_name) == 0)
        {
            found = 1;
        }
        else
        {
            fprintf(tfile, "%s %s %i %i %i\n", st.item_name, st.item_qua, st.cost, st.item_id, st.number);
        }
    }

    if (!found)
    {
        printf("\nUnscucessfull try. Record not found ");
        getch();
        menu();
    }
    else
    {
        printf("\n\tRecord delete successfully");
    }
    fclose(sfile);
    fclose(tfile);
    remove("NextFile.dat");
    rename("TempFile.dat", "NextFile.dat");

    printf("\npress enter to go to the main menu");
    while ((st.c = getch()) == '\r ')
        ;
    menu();
}

void total_bill()
{
    float T_A, A, S_T, D_T, T_T, Q, V, D, T;

    printf("\n Enter the quantity of the items to be sold: ");
    scanf("%f", &Q);

    printf("\n Enter the value of item: ");
    scanf("%f", &V);

    printf("\n Enter the discount percentage: ");
    scanf("%f", &D);

    printf("\n Enter the tax: ");
    scanf("%f", &T);

    A = Q * V;
    D_T = (A * D) / 100.0;
    S_T = A - D_T;
    T_A = (S_T * T) / 100.0;
    // T_A = S_T + T_A;

    printf("\n Total Bill: ");
    printf("\nQuantitySold: %f", Q);
    printf("\ncostperitem: %f", V);
    printf("\n -------------");
    printf("\nAmount: %f", A);
    printf("\n Discount: -%f", D_T);
    printf("\n Discounted Total: %f", S_T);
    printf("\n Tax: +%f", T_A);
    printf("\n -------------");
    printf("\n Total Amount %f", T_A);

    getch();
    menu();
}

void read_GOODS()
{
    FILE *f;
    int i, q;
    if ((f = fopen("Nextfile.dat", "r")) == NULL)
    {
        gotoxy(10, 3);
        printf("NO RECORDS");
        printf("\nPress enter to open main menu.");
        getch();
        menu();
    }
    else
    {
        gotoxy(0, 5);
        for (i = 0; i < 100; i++)
        {
            printf("\xdb");
        }
        gotoxy(5, 6);
        printf("GOODS's Name");
        gotoxy(25, 6);
        printf("GOODS's cost");
        gotoxy(40, 6);
        printf("GOODS's Brand");
        gotoxy(60, 6);
        printf("GOODS's CODE");
        gotoxy(80, 6);
        printf("GOODS's Quantity\n");

        for (i = 0; i < 100; i++)
        {
            printf("\xdb");
        }
        q = 8;
        while (fscanf(f, "%s %s %i %i %i \n", st.item_name, st.item_qua, &st.cost, &st.item_id, &st.number) != EOF)
        {
            gotoxy(5, q);
            printf("%s", st.item_name);
            gotoxy(25, q);
            printf("%s", st.item_qua);
            gotoxy(40, q);
            printf("%i", st.cost);
            gotoxy(60, q);
            printf("%i", st.item_id);
            gotoxy(80, q);
            printf("%i", st.number);

            q++;
        }

        printf("\n");
        for (i = 0; i < 100; i++)
        {
            printf("\xdb");
        }
    }

    fclose(f);

    printf("\nPress enter to go to main menu.");
    getch();
    menu();
}

void edit_GOODS()
{
    int index, valid;
    char target[40];
    FILE *fp, *rp;
    int a = 0;
    int id;
    char edit;
    long int size = sizeof(st);

    if ((fp = fopen("nextfile.dat", "r")) == NULL)
    {
        printf("Record not added.");
        menu();
    }
    else
    {
        rp = fopen("TempFile.dat", "a");
        system("cls");
        printf("Enter the item code to edit:");
        scanf("%i", &id);
        fflush(stdin);

        while (fscanf(fp, "%s %s %i %i %i\n", st.item_name, st.item_qua, &st.cost, &st.item_id, &st.number))
        {
            if (id == st.item_id)
            {
                a = 1;
                printf("\nRecord Found ");
                printf("\nItem's Name\t\t: %s", st.item_name);
                printf("\nItem's Brand\t\t: %s", st.item_qua);
                printf("\nCost:\t\t%i", st.cost);
                printf("\nItem's Code\t\t: %i", st.item_id);
                printf("\nItem's Quantity\t:%i", st.number);

                printf("\n*** New Record ***");

                do
                {
                    fflush(stdin);
                    printf("\nNew GOODS's Name\t\t: ");
                    gets(st.item_name);
                    st.item_name[0] = toupper(st.item_name[0]);

                    for (index = 0; index < strlen(st.item_name); ++index)
                    {
                        if (isalpha(st.item_name[index]))
                            valid = 1;
                        else
                        {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid)
                    {
                        printf("\nINVALID ENTRY. TRY AGAIN");
                        getch();
                    }
                } while (!valid);

                do
                {
                    char item_qua[40];
                    fflush(stdin);
                    printf("\nNew GOODS's Brand\t\t:");
                    gets(st.item_qua);
                    st.item_qua[0] = toupper(st.item_qua[0]);

                    for (index = 0; index < strlen(st.item_qua); ++index)
                    {
                        if (isalpha(st.item_qua[index]))
                            valid = 1;
                        else
                        {
                            valid = 0;
                            break;
                        }
                    }
                    if (!valid)
                    {
                        printf("\nINVALID ENTRY. TRY AGAIN");
                        getch();
                    }
                } while (!valid);

                do
                {
                    printf("\nNew cost [10-5000]:");
                    scanf("%i", &st.cost);
                    if (st.cost < 10 || st.cost > 5000)
                    {
                        printf("\n\tINVALID ENTRY. TRY AGAIN");
                    }
                } while (st.cost < 10 || st.cost > 5000);

                printf("\nEnter New item's Code:");
                scanf("%i", &st.item_id);

                do
                {
                    printf("\nNew Quantity [1-500]\t:");
                    scanf("%i", &st.number);
                    if (st.number < 1 || st.number > 500)
                    {
                        printf("\n\tINVALID ENTRY. TRY AGAIN");
                    }
                } while (st.number < 1 || st.number > 500);

                printf("TO DO MORE UPDATES PRESS 'Y' OR ANY OTHER KEY TO EXIT...");
                edit = getche();
                if (edit == 'y' || edit == 'Y')
                {
                    fprintf(rp, "%s %s %i %i %i\n", st.item_name, st.item_qua, st.cost, st.item_id, st.number);
                    fflush(stdin);
                    printf("\nRECORD UPDATED SUCCESSFULLY!");
                }
            }
            else
            {
                fprintf(rp, "%s %s %i %i %i\n", st.item_name, st.item_qua, st.cost, st.item_id, st.number);
                fflush(stdin);
            }
        }
        if (!a)
        {
            printf("Record doesn't exite !!!!");
        }
        fclose(rp);
        fclose(fp);
        remove("NextFile.dat");
        rename("TempFile.dat", "NextFile.dat");
        getch();
    }
    menu();
}
