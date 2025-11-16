#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define clrscr() printf("\e[1;1H\e[2J")
#define PRODUCTS_AMOUNT 4
#define TOTAL_PRODUCTS_PER_ORDER PRODUCTS_AMOUNT

const char *main_product_desc[] = {"Massa de chocolate, recheio à base de chocolate e leite condensado", "Coxinha frita recheada com frango", "Brigadeiro pequeno para festa", "Mini Pizza individual pequena"};
const char *main_product_name[] = {"Bolo de Chocolate", "Coxinha", "Beijinho", "Mini Pizza"};
const char *main_product_amount_name[] = {"fatia", "cento", "cento", "cento"};
const int main_product_amount[] = {40, 100, 100, 100};
const float  main_product_value[] = {100.0, 70.0, 90.0, 125.0};
const int main_product_max_order_amount[] = {5, 5, 5, 5};
char client_name[250], client_cep[9], individual_taxpayer_registration[15], client_food_restriction[250], address[250], contact_number[50], *payment_method, *is_delivery;
int id_client, client_product_switched;
float total_value = 0;

bool in_list(int value, const int list[], int size);
const char* time_now();
void order_slip(const int _id, const char *_client_name, const char *individual_taxpayer_registration, int position);
bool validate_itr(const char *string_individual_taxpayer_registration);
void validate_input(char *input_variable, int *i, int max_value, int number_length);
void validate_number(char *phone_number);

typedef struct {
    char product_name[200];
    char product_description[250];
    float product_value;
    int product_amount;
    char amount_name[10];
    int max_order_amount;
    int order_amount;
   // You can add more information
} Product;

Product selectedProducts[PRODUCTS_AMOUNT];
Product selectProduct(Product *productList, char *productInput);

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

/* 
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
*/

// Maybe the best way to store this data is using a vector.
void order_slip(const int _id, const char *_client_name, const char *individual_taxpayer_registration, int position) {
    int i;
    int selectedProductsLen = sizeof(selectedProducts) / sizeof(selectedProducts[0]);
    // The output
    printf("-------------------------------------------------------------------------------\n");    
    printf("Número do pedido (ID):  %04d\n", _id);
    printf("Nome do cliente: %s",_client_name);
    printf("CPF: %s", individual_taxpayer_registration);
    time_now(); // We need a way to save this information
    printf("Forma de pagamento: %s\n", payment_method);
    //printf("Quando paga? \n");
    printf("Entrega?: %s\n", is_delivery);
    printf("Valor total: R$%.2f\n", total_value);
    printf("\nDescrição:\n");
    printf("-------------------------------------------------------------------------------\n");    

    for (i = 0; i < selectedProductsLen; i++) {
        if (!(selectedProducts[i].order_amount)) { continue; } // If the amount ordered is 0, then it shouldn't be displayed
        printf("\n%s - %s\nValor: %.2f\nQuantidade: %i\n", selectedProducts[i].product_name, selectedProducts[i].product_description, selectedProducts[i].product_value, selectedProducts[i].order_amount) ;
    }

    printf("\n-------------------------------------------------------------------------------\n");    
    printf("Endereço: %s\n", address);
    printf("Contato: %s", contact_number);
    printf("-------------------------------------------------------------------------------\n");    
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
    int i;
    char deliveryInput[10];
    char paymentInput[10];
    char productInput[10];

    id_client = 1;
    client_product_switched = 0;
    Product product[PRODUCTS_AMOUNT]; // Products vector
    //clrscr();
    individual_taxpayer_registration[2] = true;

    // Will add the main product to us 
    for(i = 0; i < PRODUCTS_AMOUNT; i++){
        snprintf(product[i].product_name, 200, "%s",main_product_name[i]);
        snprintf(product[i].product_description, 250,"%s", main_product_desc[i]);
        product[i].product_value = main_product_value[i];
        product[i].product_amount = main_product_amount[i];   
        product[i].max_order_amount = main_product_max_order_amount[i];
        snprintf(product[i].amount_name, 10, "%s", main_product_amount_name[i]);
    };

    /* Will show our products
    printf("Cardápio");
    for(i = 0; i <=2; i++){
        printf("------------------------------\n");    
        printf("Produto: %d\n", i+1);
        printf("Nome: %s\n", product[i].product_name);
        printf("Descrição: %s\n", product[i].product_description);
        printf("Valor: R$%.2f\n", product[i].product_value);
        printf("Porção: %d\n", product[i].product_amount);
    }

    printf("* Digite teu produto: ");
    validate_input(productInput, &client_product_switched, PRODUCTS_AMOUNT);
    */

    for (i = 0; i < PRODUCTS_AMOUNT; i++) {
        //Product nextProduct = selectProduct(product);
        Product nextProduct = selectProduct(product, productInput);
        //printf("Value of string: %s\n", productInput);
        //printf("Value of comparation to 0: %i\n", (strcmp(productInput, "0")));
        if (productInput[0] == '0') { 
            if (i == 0) {
                printf("Pedido vazio. Saindo...");
                return 0;
            }
            break;
        }
        snprintf(selectedProducts[i].product_name, 200, "%s", nextProduct.product_name);
        snprintf(selectedProducts[i].product_description, 250,"%s", nextProduct.product_description);
        selectedProducts[i].product_value = nextProduct.product_value;
        selectedProducts[i].product_amount = nextProduct.product_amount;   
        selectedProducts[i].max_order_amount = nextProduct.product_amount;
        selectedProducts[i].order_amount = nextProduct.order_amount;
    }

    // Registering the client in our system
    clrscr();
    printf("* Escreva teu nome : ");
    fgets(client_name, sizeof client_name, stdin);
    printf("Escreva teu cpf : ");
    fgets(individual_taxpayer_registration, sizeof individual_taxpayer_registration, stdin);

    while (strlen(individual_taxpayer_registration) > 1 && !(validate_itr(individual_taxpayer_registration))) 
    {
        printf("Seu CPF foi considerado inválido, aperte enter ou tente digitar novamente!");
        printf("\n Escreva teu cpf : ");
        fgets(individual_taxpayer_registration, sizeof individual_taxpayer_registration, stdin);
    }

    // Payment method, delivery and contact info input
    printf("------------------------------\n");    
    printf("1 - Dinheiro\n");
    printf("2 - Cartão\n");
    printf("------------------------------\n");    
    printf("Escolha a forma de pagamento: ");

    validate_input(paymentInput, &i, 2, 1);
   
    payment_method = (i == 1) ? "Dinheiro" : "Cartão";
    
    printf("------------------------------\n");    
    printf("1 - Entrega\n");
    printf("2 - Retirada\n");
    printf("------------------------------\n");    
    printf("Escolha entre entrega e retirada: ");

    validate_input(deliveryInput, &i, 2, 1);
    
    is_delivery = (i == 1) ? "Sim" : "Não";

    if (!(strcmp(is_delivery, "Sim"))) {
        printf("Digite seu endereço: ");
        fgets(address, sizeof(address), stdin);
    } else {
        strcpy(address, "-");
    } 

    printf("\nDigite um número para contato (formato: 11111111111; digite 0 para não informar): ");
    validate_number(contact_number);

    // Order of products
    
    clrscr();
    order_slip(id_client, client_name,individual_taxpayer_registration, client_product_switched);
    return 0;
}

Product selectProduct(Product *productList, char *productInput) {
    int i;
    Product selectedProduct;
    char amountInput[10];
    //char productInput[10];

    clrscr();
    printf("Cardápio");
    printf(" - (Número máximo de produtos por pedido: %d)\n", TOTAL_PRODUCTS_PER_ORDER);
    printf("\n------------------------------\n");    
    for(i = 0; i < PRODUCTS_AMOUNT; i++){
        printf("Produto: %d\n", i+1);
        printf("Nome: %s\n", productList[i].product_name);
        printf("Descrição: %s\n", productList[i].product_description);
        printf("Porção: %d\n", productList[i].product_amount);
        printf("Valor: R$%.2f/%s\n", productList[i].product_value, productList[i].amount_name);
        printf("------------------------------\n");    
    }

    printf("\n* Selecione um produto: ");
    validate_input(productInput, &i, PRODUCTS_AMOUNT, 1);
    selectedProduct = productList[i - 1]; 
    if (productInput[0] == '0') { return selectedProduct; };
    printf("Quantidade de porções (máximo: %d): ", selectedProduct.max_order_amount);
    validate_input(amountInput, &i, selectedProduct.max_order_amount, 1);
    selectedProduct.order_amount = i;

    total_value += selectedProduct.product_value * i;

    return selectedProduct;

}

void validate_input(char *input_variable, int *i, int max_value, int number_length) {
    while (fgets(input_variable, sizeof(input_variable), stdin)) {
        if (sscanf(input_variable, "%d", i) == number_length && (*i == 1 || *i <= max_value)) {
            break;
        }
        printf("Entrada inválida. Digite um número de 1 a %d para prosseguir: ", max_value);
    }

}

void validate_number(char *phone_number) {
    while (fgets(phone_number, 50, stdin)) {
        if (phone_number[0] == '0') {
            strcpy(phone_number, "-\n");
            break;
        }

        if (strlen(phone_number) == 12) {
            break;
        }
        printf("Entrada inválida. Digite um número de telefone válido: ");
    }

}
