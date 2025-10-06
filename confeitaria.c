#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define PRODUCTS_AMOUNT 3
const char *main_product_desc[] = {"Um produto doce, recheado de chocolate com moranfo", "Um produto feito para os amantes de salgadinhos, vindo com um frango bem temperado e uma massa feita pensando justamente em você!", "Agridoce"};
const char *main_product_name[] = {"Produto A", "Produto B", "Produto C"};
const int main_product_amount[] = {20, 4, 3};
const float  main_product_value[] = {19.99,20.50,4.55};
char client_name[250], client_cep[9], individual_taxpayer_registration[15], client_food_restriction[250];
typedef struct {
    char product_name[200];
    char product_description[250];
    float product_value;
    int product_amount;
   // You can add more information
} Product;

// All possible combinations of digit sums in the CPF(valid)
const int valid_values[] = {
        10, 11, 12, 21, 22, 23,
        32, 33, 34, 43, 44, 45,
        54, 55, 56, 65, 66, 67,
        76, 77, 78, 87, 88
    };

// Function to verify if our value is inside of some list (It´s like the 'in' in Python)
bool in_list(int value, const int list[], int size) {for (int i = 0; i < size; i++) {if (value == list[i]){return true;}}return false;}
    
int time_now(){
   time_t t = time(NULL); 
    struct tm *currentTime = localtime(&t); 

    int year = currentTime->tm_year + 1900; 
    int month = currentTime->tm_mon + 1;   
    int day = currentTime->tm_mday;       
    int hour = currentTime->tm_hour;
    int minute = currentTime->tm_min;
    printf("Data (Sistema): %02d/%02d/%04d %02d:%02d \n", day, month, year, hour, minute);
    return 0;
}

// The function will verify if your cpf is real or fake
bool validate_itr(const char *string_individual_taxpayer_registration) {
    int i; // Variable to count
    int sub_plus; // Variable to sum our cpf
    sub_plus = 0;
    i = 0;
    for (i = 0; i < strlen(string_individual_taxpayer_registration); i++) {
        // Our cpf is a vetor, for each char has only position, we can access the position using 'for' and the count variable
        //printf("---> %c\n", string_individual_taxpayer_registration[i]); 

        if(isdigit(string_individual_taxpayer_registration[i])){ // Will verify if our char is a number or not
            int num = string_individual_taxpayer_registration[i] - '0'; // If it´s a number, will declare a num and will convert the char into a int
            //printf("Number version --> %d\n", num);
            sub_plus = sub_plus + num; 
        }
    }
    int size = sizeof(valid_values) / sizeof(valid_values[0]);
    printf("Number version --> %d\n", sub_plus);
    if (in_list(sub_plus, valid_values, size)) {
        return true;
    }
    return false;
}

int main() {
    Product product[PRODUCTS_AMOUNT];
    int i;
    // Will add the main product to us 
    for(i = 0; i <= 2; i++){
    snprintf(product[i].product_name, 200, "%s",main_product_name[i]);
    snprintf(product[i].product_description, 250,"%s", main_product_desc[i]);
    product[i].product_value = main_product_value[i];
    product[i].product_amount = main_product_amount[i];   
    };

    // Will show our products
    printf("Cardápio");
    for(i = 0; i <=2; i++){
    printf("------------------------------\n");    
    printf("Produto: %d\n", i+1);
    printf("Nome: %s\n", product[i].product_name);
    printf("Descrição: %s\n", product[i].product_description);
    printf("Valor: R$%.2f\n", product[i].product_value);
    printf("Porção: %d\n", product[i].product_amount);};
    // Alert: If you wrote your name with space, It´s will affect your cpf -- WE NEED TO VALIDATE
    
    
    printf("* Escreva teu nome : ");
    scanf("%s",client_name);
    printf("Escreva teu cpf : ");
    scanf("%s",individual_taxpayer_registration);
    // We need to create a while loop that only allows valid CPFs or empty input.
    if(validate_itr(individual_taxpayer_registration)){ 
    printf("Your cpf is real");
    }else{printf("Your cpf is fake");}
    return 0;
}
