#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define clrscr() printf("\e[1;1H\e[2J")


#define PRODUCTS_AMOUNT 3


const char *main_product_desc[] = {"Um produto doce, recheado de chocolate com moranfo", "Um produto feito para os amantes de salgadinhos, vindo com um frango bem temperado e uma massa feita pensando justamente em você!", "Agridoce"};
const char *main_product_name[] = {"Produto A", "Produto B", "Produto C"};
const int main_product_amount[] = {20, 4, 3};
const float  main_product_value[] = {19.99,20.50,4.55};
char client_name[250], client_cep[9], individual_taxpayer_registration[15], client_food_restriction[250];
int id_client;

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
    
const char* time_now(){
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
bool empty_value(const char *string_individual_taxpayer_registration){
    int i;
    i = 2;
    {
        printf("%d\n", string_individual_taxpayer_registration[i]);
        //If the cpf is empty, the CPF[2] will be true/1
        if(string_individual_taxpayer_registration[i] == 1){ 
            return true;
        }
        return false; 
    }
    

}
// Maybe the best way to storage this data is using a vector.
void order_slip(const int _id, const char *_client_name, const char *individual_taxpayer_registration){
    // The output
       printf("ID:  %04d\n", _id);
       printf("Nome: %s",_client_name);
       time_now(); // We need a way to save this information
       // We need to validate the formatt of our cpf
       // example: 11111111111 -> 111.111.111-11
       printf("CPF: %s", individual_taxpayer_registration);
    }
// The function will verify if your cpf is real or fake
bool validate_itr(const char *string_individual_taxpayer_registration) {
    int i; 
    int sub_plus; // Variable to sum our cpf
    sub_plus = 0;
    i = 0;
    for (i = 0; i < strlen(string_individual_taxpayer_registration); i++) {
        // Our cpf is a vetor, for each char has only position, we can access the position using 'for' and the count variable
        //printf("---> %c\n", string_individual_taxpayer_registration[i]); 

        if(isdigit(string_individual_taxpayer_registration[i])){ // Will verify if our char is a number or not
            int num = string_individual_taxpayer_registration[i] - '0'; // If it´s a number, will declare a num and will convert the char into an int
            //printf("Number version --> %d\n", num);
            sub_plus = sub_plus + num; 
        }
    }
    int size = sizeof(valid_values) / sizeof(valid_values[0]);
    //printf("Number version --> %d\n", sub_plus); <- Uncomment to see the sum of your cpf
    if (in_list(sub_plus, valid_values, size)) {
        return true;
    }
    return false;
}

int main() {
    id_client = 1;
    Product product[PRODUCTS_AMOUNT];
    clrscr();
    individual_taxpayer_registration[2] = true;
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
    
    
    
    
    // Registering the client in our system
    printf("* Escreva teu nome : ");
    fgets(client_name, sizeof client_name, stdin);
    printf("Escreva teu cpf : ");
    fgets(individual_taxpayer_registration, sizeof individual_taxpayer_registration, stdin);
 while (!(validate_itr(individual_taxpayer_registration)) && empty_value(individual_taxpayer_registration) == false)
    {
            printf("Seu CPF foi considerado inválido, aperte enter ou tente digitar novamente!");
            printf("\n Escreva teu cpf : ");
            fgets(individual_taxpayer_registration, sizeof individual_taxpayer_registration, stdin);
    }
    order_slip(id_client, client_name,individual_taxpayer_registration);
    return 0;
}
