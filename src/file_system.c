#include "file_system.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100
#define MIN 20
#define ARQ1 "Customers_table"
#define ARQ2 "Products_table"
#define ARQ3 "Orders_table"

struct customer{
    int customer_id;
    char name[MAX];
    char adress[MAX];
    char phone[MIN];    
};

struct product{
    int product_id;
    char product[MAX];
    int qty;
    float price;
};

struct order{
    int order_id;
    char date[MIN];
    int customer_id_ref;
    char shipping_adress[MAX];
    int product_id_ref;
    int qty;
};

void customer_id(Customer *c,FILE *customers_table){
    int cont_customer = 0;

	fseek(customers_table, 0, SEEK_END);
	cont_customer = ftell(customers_table);
 
	if(cont_customer == 0)
		c->customer_id = 1;
	
	else{
		Customer last_customer;
		fseek(customers_table, cont_customer - sizeof(Customer), SEEK_SET);
		fread(&last_customer, sizeof(Customer), 1, customers_table);
 		c->customer_id = last_customer.customer_id + 1;
	}
}

void create_customer(Customer customer,FILE *customers_table){
    fseek(customers_table, 0, SEEK_END);
    if(fwrite(&customer,sizeof(customer),1,customers_table)!=1){
        puts("Adicionar cliente: Falha na escrita do registro");
    }
    fclose(customers_table);
}

void customer(){
    Customer customer;
    FILE *customers_table;
    customers_table = fopen(ARQ1, "r+b"); //tentar abrir
    if(customers_table==NULL){
        customers_table = fopen(ARQ1, "a+b"); // criar o arquivo
        if(customers_table==NULL){
            printf(" Erro fatal: impossível criar arquivo de dados\n");
            return;
        }
    }    
    customer_id(&customer,customers_table);
	getchar();
    printf("Nome:    "); fgets(customer.name, MAX, stdin);
    customer.name[strcspn(customer.name,"\n")] = '\0';

    printf("Adress:  "); fgets(customer.adress, MAX, stdin);
    customer.adress[strcspn(customer.adress,"\n")] = '\0';

    printf("Phone:   "); fgets(customer.phone, MIN, stdin);
    customer.phone[strcspn(customer.phone,"\n")] = '\0';
    create_customer(customer,customers_table);
	 
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
}

void product_id(Product *p, FILE *products_table){
    int cont_product = 0;

	fseek(products_table, 0, SEEK_END);
	cont_product = ftell(products_table);
 
	if(cont_product == 0)
		p->product_id = 1;
	
	else{
		Product last_product;
		fseek(products_table, cont_product - sizeof(Product), SEEK_SET);
		fread(&last_product, sizeof(Product), 1, products_table);
 		p->product_id = last_product.product_id + 1;
	}
}

void create_product(Product product,FILE *products_table){
    fseek(products_table, 0, SEEK_END);
    if(fwrite(&product,sizeof(Product),1,products_table)!=1){
        puts("Adicionar cliente: Falha na escrita do registro");
    }
    fclose(products_table);
}

void product(){
    Product product;
    FILE *products_table;
    products_table = fopen(ARQ2, "r+b"); //tentar abrir
    if(products_table==NULL){
        products_table = fopen(ARQ2, "a+b"); // criar o arquivo
        if(products_table==NULL){
            printf(" Erro fatal: impossível criar arquivo de dados\n");
            return;
        }
    }
    product_id(&product,products_table);
	getchar();    
    printf("Produto:      "); fgets(product.product, MAX, stdin);
    product.product[strcspn(product.product,"\n")] = '\0';

    printf("Preço:        "); scanf("%f",&product.price);

    printf("Quantidade:   "); scanf("%d",&product.qty);
    create_product(product,products_table);
    getchar();    
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
}

void order_id(Order *o,FILE *orders_table){
    int cont_order = 0;

	fseek(orders_table, 0, SEEK_END);
	cont_order = ftell(orders_table);
 
	if(cont_order == 0)
		o->order_id = 1;
	
	else{
		Order last_order;
		fseek(orders_table, cont_order - sizeof(Order), SEEK_SET);
		fread(&last_order, sizeof(Order), 1, orders_table);
 		o->order_id = last_order.order_id + 1;
	}
}

void create_order(Order order, FILE *orders_table){
    fseek(orders_table, 0, SEEK_END);
    if(fwrite(&order,sizeof(order),1,orders_table)!=1){
        puts("Adicionar cliente: Falha na escrita do registro");
    }
    fclose(orders_table);
}

void update_product_qty(int product_id, int order_qty){

	FILE *products_table = fopen(ARQ2, "r+b");
	if(products_table == NULL){
		printf("\nFalha ao abrir arquivo(s)!\nOu as informações necessárias ainda não foram registradas");
		getchar();  
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c");
		return;
	}
	rewind(products_table);

	Product p;
	while(1){

		if(fread(&p, sizeof(Product), 1, products_table) == 0)
			break;
 
		if(p.product_id == product_id){
			p.qty = p.qty - order_qty;
			fseek(products_table, - sizeof(Product), SEEK_CUR);
			if(fwrite(&p,sizeof(Product),1,products_table)!=1){
				puts("Erro");
				break;
			}
			break;
		}
	}	
	fclose(products_table);

}

void make_order(){
    Order order;
    FILE *orders_table;
    orders_table = fopen(ARQ3, "r+b");
    if(orders_table==NULL){
        orders_table = fopen(ARQ3, "a+b");
        if(orders_table==NULL){
            printf(" Erro fatal: impossível criar arquivo de dados\n");
            return;
        }
    }
    order_id(&order,orders_table);

    char str_customer_id[10];
	int customer_id;
 
	FILE *customers_table = fopen(ARQ1, "rb+");

	if(customers_table == NULL){
		printf("\nFalha ao abrir arquivo(s)!\nOu as informações necessárias ainda não foram registradas");
		getchar();  
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c");
		return;
	}
	FILE *products_table = fopen(ARQ2, "rb+");
	if(products_table == NULL){
		printf("\nFalha ao abrir arquivo(s)!\nOu as informações necessárias ainda não foram registradas");
		getchar();  
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c");
		return;
	}

 
	printf("\nDigite o ID do cliente: ");
	scanf("%10s%*c", str_customer_id);
 
 
	if(only_number(str_customer_id) == 1){
		sscanf(str_customer_id, "%d", &customer_id);
        
        Customer *c = get_customer(customers_table, customer_id);
		if(c != NULL){
			char str_product_id[10];
			int product_id;

            printf("Data:(XX/XX/XXXX) "); fgets(order.date, MAX, stdin);
            order.date[strcspn(order.date,"\n")] = '\0';
			printf("\nDigite o ID do produto: ");
			scanf("%10s%*c", str_product_id);
            printf("Quantidade:       ");
            scanf("%d",&order.qty);

 
			if(only_number(str_product_id) == 1){
				sscanf(str_product_id, "%d", &product_id);
 
				Product *p = get_product(products_table, product_id);

				if(p != NULL){
					if(p->qty > order.qty || p->qty == order.qty){
						int order_qty = order.qty;
						update_product_qty(product_id,order_qty);
						order.customer_id_ref = customer_id;
						order.product_id_ref = product_id;
						strcpy(order.shipping_adress,c->adress);
						free(p);
						free(c); 
				
					}
					else{
							getchar();
							printf("\nHá somente %d unidade(s) desse produto.\n",p->qty);
							printf("\nPressione <Enter> para continuar...");
							scanf("%*c");
							return;
					}
				}
				else
					printf("\nNao existe product com o ID \"%d\".\n", product_id);
			}
			else
				printf("\nO ID so pode conter numeros!\n");
		}
		else
			printf("\nNao existe cliente com o ID \"%d\".\n", customer_id);
	}
	else
		printf("\nO ID so pode conter numeros!\n");

    fflush(stdin);
    create_order(order,orders_table);
	fclose(customers_table);
	fclose(products_table);
	getchar();
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
}


void list_costumer(){
    Customer c;
    FILE *customers_table;
    customers_table = fopen(ARQ1, "rb");

    if(customers_table){
		fseek(customers_table, 0, SEEK_SET);
        puts(" ");
        printf("========= Tabela de Clientes =========\n");        
        while(!feof(customers_table)){
            if(fread(&c,sizeof(Customer),1,customers_table)){
                printf("\nID: %d",c.customer_id);
                printf("\nNome: %s",c.name);
                printf("\nEndereço: %s",c.adress);
                printf("\nTelefone: %s\n",c.phone);
            }
        }
        fclose(customers_table);
    }
    else
        printf("\nErro ao abrir arquivo!\nNão há clientes cadastrados.");
    
	getchar();    
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
}


void list_product(){
    Product p;
    FILE *products_table;
	products_table = fopen(ARQ2, "rb");

    if(products_table){
		fseek(products_table, 0, SEEK_SET);
        puts(" ");
        printf("========= Tabela de Produtos =========\n");         
        while(!feof(products_table)){
            if(fread(&p,sizeof(Product),1,products_table)){
                printf("\nID: %d",p.product_id);
                printf("\nProduct: %s",p.product);
                printf("\nPreço: %.2f",p.price);
                printf("\nQuantidade: %d\n",p.qty);
            }
        }
        fclose(products_table);
    }
    else
        printf("\nErro ao abrir arquivo!\nNão há produtos cadastrados.");
    
	fflush(stdin);

    getchar();    
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
}

void list_order(){
    Order o;
    FILE *orders_table;
    orders_table = fopen(ARQ3, "rb");

    if(orders_table){
		fseek(orders_table, 0, SEEK_SET);
        puts(" ");
        printf("========= Tabela de Pedidos ==========\n");
        while(!feof(orders_table)){
            if(fread(&o,sizeof(Order),1,orders_table)){
                printf("\nOrder: %d",o.order_id);
                printf("\nData: %s",o.date);
                printf("\nID Cliente: %d",o.customer_id_ref);
                printf("\nID Produto: %d",o.product_id_ref);                
                printf("\nEndereço de entrega: %s",o.shipping_adress);                
                printf("\nQuantidade: %d\n",o.qty);
            }
        }
        fclose(orders_table);
    }
    else
        printf("\nErro ao abrir arquivo!\nNão há pedidos registrados");
    
	fflush(stdin);
    
    getchar();    
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
}

Customer *get_customer(FILE *customers_table, int customer_id){
    rewind(customers_table);
	Customer *customer;
    customer = (Customer *)malloc(sizeof(Customer));
	
    while(1){
 	
 		if(fread(customer, sizeof(Customer), 1, customers_table) == 0){
			free(customer);
			return NULL;
		}
		if(customer->customer_id == customer_id)
			break;
	}
	return customer;
}

Product *get_product(FILE *products_table, int product_id){
    rewind(products_table);
	Product *product;
    product = (Product *)malloc(sizeof(Product));
	
    while(1){
 		size_t result = fread(product, sizeof(Product), 1, products_table);
 		if(result == 0){
			free(product);
			return NULL;
		}
		if(product->product_id == product_id)
			break;
	}
	return product;
}

void search_customer(){
	char name[MAX];
	int customer_found = 0;
 
 	FILE *customers_table = fopen(ARQ1, "rb");
 
 	if(customers_table == NULL){
		printf("\nFalha ao abrir arquivo(s)!\nOu as informações necessárias ainda não foram registradas");
		getchar();  
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c");
		return;
	}
 
	printf("\nDigite o nome do cliente:  ");
	scanf("%s%*c", name);
 
	printf("\n\nClientes com o nome \"%s\":\n", name);

	Customer c;

	while(1){

		if(fread(&c, sizeof(Customer), 1, customers_table) == 0)
			break;
 
		char name_aux[MAX];
		strcpy(name_aux, c.name);
 
 		if(strcasecmp(name_aux,name) == 0){
            printf("\nID: %d",c.customer_id);
            printf("\nNome: %s",c.name);
            printf("\nEndereço: %s",c.adress);
            printf("\nTelefone: %s\n",c.phone);
			customer_found = 1;
		}
	}
 
	if(customer_found == 0)
		printf("Nenhum customer encontrado.\n\n");
 
	fclose(customers_table);
 
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
 
}

void search_product(){
	char product[MAX];
	int product_found = 0;
 
 	FILE *products_table = fopen(ARQ2, "rb");
 
 	if(products_table == NULL){
		printf("\nFalha ao abrir arquivo(s)!\nOu as informações necessárias ainda não foram registradas");
		getchar();  
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c");
		return;
	}
 
	printf("\nDigite o nome do produto:  ");
	scanf("%s%*c", product);
 
	printf("\n\nProdutos com o nome \"%s\":\n", product);

	Product p;

	while(1){

		if(fread(&p, sizeof(Product), 1, products_table) == 0)
			break;
 
		char product_aux[MAX];
		strcpy(product_aux, p.product);
 
 		if(strcasecmp(product_aux,product) == 0){
            printf("\nID: %d",p.product_id);
            printf("\nProduct: %s",p.product);
            printf("\nPreço: %.2f",p.price);
            printf("\nQuantidade: %d\n",p.qty);
			product_found = 1;
		}
	}
 
	if(product_found == 0)
		printf("Nenhum produto encontrado.\n\n");
 
	fclose(products_table);
	
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
 
} 

void search_order_by_customer(){
	
    int order_found = 0;
    char str_customer_id[50];
	int customer_id;

 	FILE *orders_table = fopen(ARQ3, "rb");
	FILE *customers_table = fopen(ARQ1, "rb");
    
    if(orders_table == NULL || customers_table == NULL){
		printf("\nFalha ao abrir arquivo(s)!\nOu as informações necessárias ainda não foram registradas");
		getchar();  
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c");
		return;
	}
 
	printf("\nDigite o ID do cliente: ");
    scanf("%10s%*c", str_customer_id);    

    if(only_number(str_customer_id) == 1){
		sscanf(str_customer_id, "%d", &customer_id);
    
        Customer *c = get_customer(customers_table, customer_id);
        if(c != NULL){
            printf("\nPedidos de \"%s\":\n", c->name);

            Order o;

            while(1){

                if(fread(&o, sizeof(Order), 1, orders_table) == 0)
                    break;

                if(o.customer_id_ref == customer_id){
                    printf("\nOrder: %d",o.order_id);
                    printf("\nData: %s",o.date);
                    printf("\nID Cliente: %d",o.customer_id_ref);
                    printf("\nID Produto: %d",o.product_id_ref);                
                    printf("\nEndereço de entrega: %s",o.shipping_adress);                
                    printf("\nQuantidade: %d\n",o.qty);
                    order_found = 1;
                }
            }
        }else
			printf("\nNao existe cliente com o ID \"%d\".\n", customer_id);
    }
    else
		printf("\nO ID so pode conter numeros!\n");
 
	if(order_found == 0)
		printf("Nenhum pedido encontrado.\n\n");
 
	fclose(orders_table);
 
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
 
} 


void search_order_by_product(){
	
    int order_found = 0;
    char str_product_id[50];
	int product_id;

 	FILE *orders_table = fopen(ARQ3, "rb");
	FILE *products_table = fopen(ARQ2, "rb");
    
    if(orders_table == NULL || products_table == NULL){
		printf("\nFalha ao abrir arquivo(s)!\nOu as informações necessárias ainda não foram registradas");
		getchar();  
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c");
		return;
	}
 
	printf("\nDigite o ID do produto: ");
    scanf("%s%*c", str_product_id);    

    if(only_number(str_product_id) == 1){
		sscanf(str_product_id, "%d", &product_id);
    
        Product *p = get_product(products_table, product_id);
        if(p != NULL){
            printf("\nPedidos de \"%s\":\n", p->product);

            Order o;

            while(1){

                if(fread(&o, sizeof(Order), 1, orders_table) == 0)
                    break;

                if(o.product_id_ref == product_id){
                    printf("\nOrder: %d",o.order_id);
                    printf("\nData: %s",o.date);
                    printf("\nID Cliente: %d",o.product_id_ref);
                    printf("\nID Produto: %d",o.product_id_ref);                
                    printf("\nEndereço de entrega: %s",o.shipping_adress);                
                    printf("\nQuantidade: %d\n",o.qty);
                    order_found = 1;
                }
            }
        }else
			printf("\nNao existe produto com o ID \"%d\".\n", product_id);
    }
    else
		printf("\nO ID so pode conter numeros!\n");
 
	if(order_found == 0)
		printf("Nenhum pedido encontrado.\n\n");
 
	fclose(orders_table);
 
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
 
} 

void update_customer(){
    int str_customer_id;
    int customer_found = 0;
    int ans;

	FILE *customers_table = fopen(ARQ1, "rb+");
    
    if(customers_table == NULL){
		printf("\nFalha ao abrir arquivo(s)!\nOu as informações necessárias ainda não foram registradas");
		getchar();  
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c");
		return;
	}
 
	printf("\nDigite o ID do cliente: ");
    scanf("%d", &str_customer_id);

	rewind(customers_table);
 
	Customer c;
	while(1){

		if(fread(&c, sizeof(Customer), 1, customers_table) == 0)
			break;
 
		if(c.customer_id == str_customer_id){
		
			printf("\nID: %d",c.customer_id);
            printf("\nCliente: %s",c.name);
        
			printf("\nDeseja mudar o endereço do cliente?[sim: 1 / nao: 0] ");
			scanf("%d", &ans);
			if(ans){
                getchar();
				printf("Adress:  "); fgets(c.adress, MAX, stdin);
                c.adress[strcspn(c.adress,"\n")] = '\0';			
            }

            printf("\nDeseja mudar o telefone do cliente?[sim: 1 / nao: 0] ");
            scanf("%d", &ans);
            if(ans){
				getchar();
                printf("Phone:   "); fgets(c.phone, MIN, stdin);
                c.phone[strcspn(c.phone,"\n")] = '\0';
			}

			fseek(customers_table, - sizeof(Customer), SEEK_CUR);
			if(fwrite(&c,sizeof(Customer),1,customers_table)!=1){
				puts("Adicionar cliente: Falha na escrita do registro");
			}			
			customer_found = 1;
			break;
		}
	}
    if(customer_found == 0)
		printf("Nenhum cliente encontrado.\n\n");
 
	fclose(customers_table);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
}

void update_products(){
    int str_product_id;
    int product_found = 0;
    int ans;

	FILE *products_table = fopen(ARQ2, "rb+");
    
    if(products_table == NULL){
		printf("\nFalha ao abrir arquivo(s)!\nOu as informações necessárias ainda não foram registradas");
		getchar();  
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c");
		return;
	}
 
	printf("\nDigite o ID do produto: ");
    scanf("%d", &str_product_id);

	rewind(products_table);
 
	Product p;
	while(1){

		if(fread(&p, sizeof(Product), 1, products_table) == 0)
			break;
 
		if(p.product_id == str_product_id){
		
			printf("\nID: %d",p.product_id);
            printf("\nProduct: %s",p.product);
            printf("\nDeseja mudar o preco do produto?[sim: 1 / nao: 0] ");
            scanf("%d", &ans);
            if(ans){
                printf("Novo preço:        "); scanf("%f",&p.price);
			}
			printf("\nDeseja mudar a quantidade do produto?[sim: 1 / nao: 0] ");
			scanf("%d", &ans);
			if(ans){
				printf("Nova Quantidade:   "); scanf("%d",&p.qty);
			}
			fseek(products_table, - sizeof(Product), SEEK_CUR);
			if(fwrite(&p,sizeof(Product),1,products_table)!=1){
				puts("Adicionar cliente: Falha na escrita do registro");
				break;
			}			
			product_found = 1;
			
		}
	}
    if(product_found == 0)
		printf("Nenhum produto encontrado.\n\n");
 
	fclose(products_table);
	getchar();
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
}

void delete_product(){
	char str_id_product[10];
	int product_id;
 
	printf("\nDigite o ID do produto: ");
	scanf("%10s%*c", str_id_product);
  
	if(only_number(str_id_product) == 1){

		sscanf(str_id_product, "%d", &product_id);
 
 		FILE *products_table = fopen(ARQ2, "rb");
 
		if(products_table == NULL){
            printf("\nFalha ao abrir arquivo(s)!\nOu não há produtos registrados.");
            getchar();  
			printf("\nPressione <Enter> para continuar...");
			scanf("%*c");
			return;
	    }
 
 		Product *p = get_product(products_table, product_id);
 
		if(p != NULL){
			char name_p[MAX];

			FILE *temp_products_table = fopen("temp_products_table", "a+b");
			if(temp_products_table == NULL){
				printf("\nFalha ao criar arquivo temporario!\n");
				fclose(products_table);
				return;
			}

			rewind(products_table);
 
			Product p;
			while(1){
 				
				if(fread(&p, sizeof(Product), 1, products_table) == 0)
					break;
 
				if(p.product_id != product_id){
					fwrite(&p, sizeof(Product), 1, temp_products_table);
				}
				else
					strcpy(name_p, p.product);
			}

			fclose(products_table);
			fclose(temp_products_table);
 
 			if(remove(ARQ2) != 0)
				printf("\nErro ao deletar o arquivo \"Products_table\"\n");
			
            else{
				int r = rename("temp_products_table", "Products_table");
				if(r != 0){
					printf("\nPermissao negada para renomear o arquivo!\n");
					printf("Feche esse programa bem como o arquivo \"temp_products_table\" e renomeie manualmente para \"Products_table\"\n");
				}
				else
					printf("\nProduto \"%s\" removido com sucesso!\n", name_p);
			}
		}
		
        else{
			fclose(products_table);
			printf("\nNao existe produto com o ID \"%d\".\n", product_id);
		}
	}
	else
		printf("\nO ID so pode conter numeros!\n");
 
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
}

int menu(){
	int s;
 
	printf("================  Loja  =====================\n");
	printf("|	1 - Cadastrar um produto  	    |\n");
	printf("|	2 - Cadastrar um cliente  	    |\n");
	printf("|	3 - Registrar um pedido  	    |\n");	
	printf("|	4 - Listar todos os produtos  	    |\n");
	printf("|	5 - Listar todos os clientes  	    |\n");
	printf("|	6 - Listar todos os pedidos  	    |\n");
	printf("|	7 - Pesquisar por produto  	    |\n");
	printf("|	8 - Pesquisar por cliente  	    |\n");
	printf("|	9 - Pesquisar por pedido  	    |\n");
	printf("|	10 - Atualizar um produto  	    |\n");
	printf("|	11 - Atualizar um cliente  	    |\n");
	printf("|	12 - Excluir um produto  	    |\n");
	printf("|	0 - Sair          	      	    |\n");
	printf("=============================================\n");
	printf("Digite o numero da opcao: ");

    scanf("%d", &s);
 
	return s;
}

int menu_order(){
	int s2;
    printf("================  Loja  ====================\n");
	printf("|	1 - Pesquisar por ID de produto    |\n");
	printf("|	2 - Pesquisar por ID de cliente    |\n");
	printf("|	0 - Sair                    	   |\n");
	printf("============================================\n");
	printf("Digite o numero da opcao: ");
	scanf("%d", &s2);
	return s2;
}

int only_number(char *str){
	int i = 0;
	int len_str = strlen(str);
 
	for(i = 0; i < len_str; i++)
		if(str[i] < '0' || str[i] > '9')
			return 0;
	return 1;
}