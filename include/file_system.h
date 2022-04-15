#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include<stdio.h>

typedef struct customer Customer;
typedef struct product Product;
typedef struct order Order;

/**
 * Exibir o menu com todas as opções do programa
 * @return int: um inteiro correspondente a opção
 */
int menu();

/**
 * Exibe o menu com as opções de pesquisa por pedidos;
 * @return int: um inteiro correspondente a opção;
 */
int menu_order();

/**
 * Gerar um ID para o cliente;
 * @param Customer*: ponteiro para a struct do cliente;
 * @param FILE*: ponteiro para o arquivo a ser lido; 
 */
void customer_id(Customer *,FILE *);

/**
 * Gravar os dados do cliente em um arquivo;
 * @param Customer: struct com os dados do cliente;
 * @param FILE*:  ponteiro para o arquivo a ser modificado; 
 */
void create_customer(Customer ,FILE *);

/**
 * Cadastrar um cliente;
 */
void customer();

/**
 * Gerar um ID para o produto;
 * @param Product*: ponteiro para a struct do produto;
 * @param FILE*:  ponteiro para o arquivo a ser lido; 
 */
void product_id(Product *, FILE *);

/**
 * Gravar os dados do produto em um arquivo;
 * @param Product: struct com os dados do produto;
 * @param FILE*:  ponteiro para o arquivo a ser modificado; 
 */
void create_product(Product ,FILE *);

/**
 * Cadastrar um produto;
 */
void product();

/**
 * Gerar um ID para o pedido;
 * @param Order*: ponteiro para a struct do pedido;
 * @param FILE*:  ponteiro para o arquivo a ser lido; 
 */
void order_id(Order *,FILE *);

/**
 * Gravar os dados do pedido em um arquivo;
 * @param Order: struct com os dados do pedido;
 * @param FILE*:  ponteiro para o arquivo a ser modificado; 
 */
void create_order(Order , FILE *);

/**
 * Realizar um pedido;
 */
void make_order();

/**
 *Exibe todos os clientes cadastrados;
 */
void list_costumer();

/**
 *Exibe todos os produtos cadastrados;
 */
void list_product();

/**
 *Exibe todos os pedidos realizados;
 */
void list_order();

/**
 * Pesquisa clientes e exibe suas informações;
 */
void search_customer();

/**
 * Pesquisa produtos e exibe suas informações;
 */
void search_product();

/**
 * Pesquisa pedidos através do ID do cliente e exibe suas informações;
 */
void search_order_by_product();

/**
 * Pesquisa pedidos através do ID do produto e exibe suas informações;
 */
void search_order_by_customer();

/**
 * Atualiza as informações do produto no arquivo;
 */
void update_products();

/**
 * Atualiza as informações do cliente no arquivo;
 */
void update_customer();

/**
 * Exclui um produto do arquivo;
 */
void delete_product();

/**
 * Atualiza a quantidade do produto;
 * @param int: ID do produto que será atualizado;
 * @param int: Total de unidades a serem retiradas ;
 */
void update_product_qty(int, int);

/**
 * Procura um cliente pelo ID;
 * @param FILE*: ponteiro para um arquivo aberto;
 * @param int: ID do cliente que será buscado;
 * @return Customer*: um ponteiro para o cliente encontrado ou NULL caso o ID não exista;
 */
Customer *get_customer(FILE *, int);

/**
 * Procura um produto pelo ID;
 * @param FILE*: ponteiro para um arquivo aberto;
 * @param int: ID do produto que será buscado;
 * @return Product*: um ponteiro para o produto encontrado ou NULL caso o ID não exista;
 */
Product *get_product(FILE *, int);

/**
 * Informa se a string é um número
 * @param char*: ponteiro para uma cadeia de caracteres
 * @return int: 1 se a string contém apenas números ou 0 caso contrário
 */
int only_number(char *str);

#endif