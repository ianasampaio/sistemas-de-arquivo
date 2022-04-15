#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "file_system.h"

/**
 * Guia:
 * Antes de tudo você deve inserir os produtos existentes no estoque na opção (1) 
 * (será gerado um ID que pode ser visualizado na opção de listagem de produtos) *
 * 
 * Quando um cliente desejar realizar uma compra, primeiramente, você deve cadastrar 
 * os dados dele na opção(2).  
 * (será gerado um ID que pode ser visualizado na opção de listagem de clientes) *.
 * 
 * Logo após, você deve inserir os dados do pedido na opção (3), tendo o ID do Cliente e 
 * o ID do produto em mãos. 
 *  * (será gerado um ID que pode ser visualizado na opção de listagem de pedidos) *.
 * 
 * Se o cliente e o produto estiverem registrados na tabela e o produto ainda estiver em 
 * estoque o pedido será realizado com sucesso.
 * 
 * Ademais, você poderá realizar outras opções presentes no menu.
 * 
 * * O ID é gerado automaticamente em ordem crescente a partir do 1.
 * */


int main(){
	int result;
	int s;
    
 	while(1){
		result = menu();
 
		if(result == 1)
			product();
		else if(result == 2)
			customer();
		else if(result == 3)
			make_order();
		else if(result == 4)
			list_product();
		else if(result == 5)
			list_costumer();
		else if(result == 6)
			list_order();
		else if(result == 7)
			search_product();
		else if(result == 8)
			search_customer();
		else if(result == 9){
			s = menu_order();
			if(s==1)
				search_order_by_product();
			if(s==2)
				search_order_by_customer();
		}
		else if(result == 10)
			update_products();
		else if(result == 11)
			update_customer();
		else if(result == 12)
			delete_product();
		else if(result == 0) 
			break;
		else{
			printf("\nOpcao invalida! Pressione <Enter> para continuar...\n");
			scanf("%*c");
		}
		system("clear");
	}
    return 0;
}