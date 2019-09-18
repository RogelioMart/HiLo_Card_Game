#include "bag.h"

int main()
{//main begins here
	
	//main variables
	char select;
	
	time_t tiempo;//used to simulate randomness for the game
	
	struct bagNode* head; //declares head of the node
	
	struct bagNode removedCards[35] = {{0}};
	
	int z = 0;
	
	int points = 0;
	
	//main code
	for(z = 0; z < 35; z++)//initializes all the card pointers for the array removedCards
	{ 
		removedCards[z].card = (struct Card*)malloc(sizeof(struct Card));
		
		removedCards[z].card->suit = '\0';
		
		removedCards[z].card->value = 0;
	}
	
	head = NULL;//initializes head of the node
	
	srand(time(&tiempo)); //seeds the random function to produce varied integers
	
	printf("/npoints: %d/n", points);
	
	head = dealer (head, removedCards, tiempo, &points);
	
	do{
		
		menu();
		
		select = getSelect();
		
		head = mainProcess(select, tiempo, head, removedCards, &points);
		
		
	}while(points >= 1);
	
	points = points * -1;
	
	head = empty(head);//frees up the memory
	
	free(head);//frees up the head
	
	printf("\n\nGAME OVER");
	
	printf("\n\nYour Final Score %d", points);
	
	return(0);
	
}//main ends