#include <stdio.h>

#include <time.h>

#include <ctype.h>

#include <stdlib.h>

struct Card //struct for the cards
{
	
	char suit; //the type of card Hearts, Diamonds, Spades, & Clubs
	
	int value; //the value on the card
	
};

struct bagNode
{
	
	struct Card* card; //pointer to the Card struct
	
	struct bagNode* next; //helps us iterate to next
	
};

/////////////////////////MENU/////////////////////////////////////
//////////////////////////////////////////////////////////////////
void menu()
{//menu begins here

	/*
	This function declares a displays the menu options for the user to choose
	from.
	*/
	
	printf("\nChoose option:\n");
	printf("1 - Next card will be higher\n");
	printf("2 - Next card will be lower\n");
	printf("3 - Guess exact value\n");
	
}//menu ends here

/////////////////////////getSelect////////////////////////////////
//////////////////////////////////////////////////////////////////
char getSelect()
{//getSelect begins here

	/*
	This function get an input from the user
	*/

	char input;
	
	scanf(" %c", &input);
	printf("\n");
	
	return(input);

}//getSelect ends here

//////////////////////fillWithCards///////////////////////////////
//////////////////////////////////////////////////////////////////
struct bagNode* fillWithCards(struct bagNode* head)
{//begins fillWithCards function
	
	/*
	fills the bag with a new deckof 52
	*/
	
	//Local Variables
	struct bagNode* curr; //stands for current
	
	char cardSuits[4] = "CDHS"; //array to call the Clubs, Diamdonds, Hearts, & Spades
	
	int i = 0;
	
	int j = 0;
	
	//function code
	
	if(head == NULL)
	{
		
		head = (struct bagNode*)malloc(sizeof(struct bagNode));//allocates memory for the node
		
		head->card = (struct Card*)malloc(sizeof(struct Card));//allocates memory for the pointer of the node
		
		head->next = NULL;//sets what is after head to NULL
		
		head->card->suit = cardSuits[j];//gives a value to head's suit
		
		head->card->value = 1;//gives a numerical value to head value
		
		curr = head;//sets current equal to head 
		
		for(i = 2; i <= 13;i++)//loop initializes all the value in the bag
		{//for loop begins here
			
			struct bagNode* temp;
		
			temp = (struct bagNode*)malloc(sizeof(struct bagNode));
			
			temp->card = (struct Card*)malloc(sizeof(struct Card));//initializes the card pointer
			
			temp->card->suit = cardSuits[j];//gives the card its suit value
	
			temp->card->value = i;//gives the card its number value
			
			if((i == 13) && (j != 3))//resets the counter to add the next values and suits
			{
				i = 0;//must be set to zero because the for loop adds 1 to i before adding anything to the LL
				j = j + 1;
			}

			//the following statements put the last node in the linked list
			temp->next = curr->next;
			curr->next = temp;
			curr = curr->next;
			
		}//ends for(i = 2; i <= 13;i++)
	}//if statement ends
	
	return(head);
	
}// ends fillWithCards function

int getCurrentSize(struct bagNode* head, int dispCount)
{
	/*
	This function counts the amount of cards in a the bag
	*/
	
	struct bagNode* curr;
	
	int deckCount = 0;
	
	if(head == NULL)
	{
		printf("\nThere is nothing in the bag\n");
	}
	else
	{	
		curr = head;
		
		do
		{
			
			curr = curr->next;
			
			deckCount = deckCount + 1;
			
		}while(curr != NULL);
	}
	
	if(dispCount == 1)
	{
		printf("Cards left in deck: %d\n", deckCount);
	}
	
	return(deckCount);
}

///////////////////////isEmpty///////////////////////////////
/////////////////////////////////////////////////////////////
int isEmpty(struct bagNode* head)
{
	/*
	checks if the bag is empty
	*/
	
	int empty = 0;
	//if empty equals 1 the bag is empty
	//if empty = 0 then the the bag is full
	
	if(head == NULL)
	{
		empty = 1;
	}
	
	return(empty);	
}

/////////////////////////Empty///////////////////////////////
/////////////////////////////////////////////////////////////
struct bagNode* empty(struct bagNode* head)
{//empty funciton begins here
	/*
	empties the bag
	*/
	
	//local variables
	struct bagNode* curr;//node to traverse the list
	
	//function code
	curr = head;
	
	curr = curr->next;
	
	while (head->next != NULL)
	{

		head->next = curr->next;//gets pointer of the next node
		
		curr = curr->next;// goes unto the next node
		
		free(curr); //frees the node
	}

	return(head);
	
}//empty function ends here

//////////////////////////grab///////////////////////////////
/////////////////////////////////////////////////////////////
struct bagNode* grab(struct bagNode* head, time_t tiempo)
{
	/*
	gets a random card from the bag
	*/
	
	//local variables
	int deckCount = 1;
	
	int deckSize = getCurrentSize(head, 0);//gets size of the deck
	
	int takeOut = (rand() % (deckSize  - 1 + 1)) + 1;//randomly chooses 
	
	struct bagNode* retNode = NULL;//sets the return node to null
	
	//function code
	if(head != NULL)
	{
		retNode = head;
		
		while(deckCount < takeOut)//this loop gets the random node from the linked list
		{
			retNode = retNode->next;
			
			deckCount = deckCount + 1;
		}		
	}
	
	return (retNode);
	
}//ends the grab function

////////////////////discardBin///////////////////////////////
/////////////////////////////////////////////////////////////
void discardBin(struct bagNode removedCards[], struct bagNode* fremoveThis)
{//discardBin begins
	
	//inserts the the discarded card into the removedCards array
	
	int i = 0;
	
	while((removedCards[i].card->suit != '\0') && (removedCards[i].card->value != 0))
	{
		i = i + 1;	
	}
	
	removedCards[i].card->suit = fremoveThis->card->suit;
	
	removedCards[i].card->value = fremoveThis->card->value;
}//discardBin ends

///////////////////////findTail//////////////////////////////
/////////////////////////////////////////////////////////////
struct bagNode* findTail(struct bagNode* head)
{
	//finds the tail of the linked list
	
	//local variables
	struct bagNode* curr;
	
	int numIterator = getCurrentSize(head, 0);
	
	int i = 1;
	
	//function code
	curr = head;
	
	while(i < numIterator)
	{
		curr = curr->next;
		
		i = i + 1;
	}
		
	return(curr);
}

/////////////////////removeTail//////////////////////////////
/////////////////////////////////////////////////////////////
struct bagNode* removeTail(struct bagNode* head)
{
	//removes the tail	
	
	//local variables
	struct bagNode* curr;// stands for current
	
	struct bagNode* preCurr;// stands for preCurrent
	
	//local code
	preCurr = head;//sets precurr to head
	
	curr = preCurr->next;//sets to the first node after head
	
	while(curr->next != NULL)//loop looks for tail
	{
		preCurr = preCurr->next;//
		
		curr = curr->next;
	}
				
	preCurr->next = curr->next;	
	
	free(curr);
	
	return(head);
}//ends removeTail function ends here

/////////////////////arbritraryRemoval///////////////////////
/////////////////////////////////////////////////////////////
struct bagNode* arbritraryRemoval(struct bagNode* head, struct bagNode* removeThis)
{
	//arbritrarly removes a part of the node
	
	//local variables
	struct bagNode* curr;
	
	struct bagNode* preCurr;
	
	//function code
	preCurr = head;
	
	curr = preCurr->next;
	
	while(curr != removeThis)//finds the node to remove
	{
		preCurr = preCurr->next;
		curr = curr->next;
	}
	
	preCurr->next = curr->next;	
	
	free(curr);//frees up the memory
	
	return(head);
}//arbritraryRemoval ends

//////////////////////removeHead/////////////////////////////
/////////////////////////////////////////////////////////////
struct bagNode* removehead(struct bagNode* head)
{
	//removes head
	
	//local variables
	struct bagNode* curr;
	
	struct bagNode* preCurr;
	
	//function code
	curr = head;
	
	preCurr = head;
	
	curr = curr->next;
	
	free(preCurr);//gets rid of head
	
	return(curr);
	
}//ends removeHead

////////////////////////discard//////////////////////////////
/////////////////////////////////////////////////////////////
struct bagNode* discard(struct bagNode* head, struct bagNode* fremoveThis)
{
	//uses the previously coded remove functions to remove the appropriate node from the bag
	
	//local variables
	struct bagNode* tail;
	
	//function code
	tail = findTail(head);
	
	if(head == NULL)
	{
		printf("The deck is empty");
	}
	else if(head == fremoveThis)//removes head
	{
		head = removehead(head);	
	}
	else if((tail == fremoveThis))//removes tail
	{
		head = removeTail(head);
	}
	else//arbritrary removal
	{
		arbritraryRemoval(head, fremoveThis);
	}
	
	return(head);
}//discard ends here

///////////////////////getFrequency//////////////////////////
/////////////////////////////////////////////////////////////
int getFrequency(struct bagNode* head, int cardValue)
{//begins getFrequency
	
	/*
		This function counts how many times a specified number
		appears int he deck (linked list)
	*/
	
	//local Variables
	int frequencyOfCard = 0; //counts the amount of times a card appears
	
	struct bagNode* curr;//used to traverse the linked list. Abreviated current
	
	curr = head;
	
	//function code
	do{//iterates through the list to count value.
		
		if(curr->card->value == cardValue)//will add the value if the number is found
		{
			frequencyOfCard = frequencyOfCard + 1;
		}
		
		curr = curr->next;
	
	}while(curr->next != NULL);
		
	if(curr->card->value == cardValue)
	{
		frequencyOfCard = frequencyOfCard + 1;
	}
		
	return(frequencyOfCard);
	
}//ends getFrequency

///////////////////dispProbabilities/////////////////////////
/////////////////////////////////////////////////////////////
void dispProbabilities(struct bagNode* head, int lastCard)
{
	//displays the probability of getting the next card
	
	//local variables
	double probabilities[14];
	
	int cardValue = 1;

	double higherProb = 0.0;
	
	double lowerProb = 0.0;
	
	int size = getCurrentSize(head, 0);
	
	//function code
	do{//gets the probability of getting the next card
		
		probabilities[cardValue] = ((float) getFrequency(head, cardValue)/ (float)size) * 100;
		
		cardValue = cardValue + 1;
		
	}while(cardValue <= 13);
	
	cardValue = 1;
	
	while(cardValue < lastCard)//gets the probobility of the next card being lower
	{	
		lowerProb = lowerProb + probabilities[cardValue];
		
		cardValue = cardValue + 1;
	}
	
	cardValue = lastCard + 1;
	
	while(cardValue <= 13)//gets the probobility of the next card being higher
	{
		higherProb = higherProb + probabilities[cardValue];
		
		cardValue = cardValue + 1;
	}
	
	printf("Probability of next card being higher: %.2f%%\n", higherProb);//displays probabilities
	printf("Probability of next card being lower: %.2f%%\n", lowerProb);//displays probabilities
	printf("Probability of next card being the same: %.2f%%\n\n",probabilities[lastCard]);//displays probabilities
	
	cardValue = 1;
	
	printf("Probability of next card being:\n");
	printf("A\t%.2f%%\n", probabilities[cardValue]);
	
	for(cardValue = 2; cardValue <= 10; cardValue++)
	{
		printf("%d\t%.2f%%\n", cardValue, probabilities[cardValue]);
	}
	
	cardValue = 11;
	printf("J\t%.2f%%\n", probabilities[cardValue]);
	
	cardValue = 12;
	printf("Q\t%.2f%%\n", probabilities[cardValue]);
	
	cardValue = 13;
	printf("K\t%.2f%%\n", probabilities[cardValue]);
}//dispProbabilities function ends here

////////////////////prettyPrint//////////////////////////////
/////////////////////////////////////////////////////////////
void prettyPrint(struct bagNode nnode)
{//begins prettyPrint
	
	//This function displays the card in a nice format
	
	if(nnode.card->value == 11)//will print the Jack value
		{
			printf("[J-%c] ", nnode.card->suit);
		}
		else if(nnode.card->value == 12)//will print the Queen value
		{
			printf("[Q-%c] ", nnode.card->suit);
		}
		else if(nnode.card->value == 13)//will print the King value
		{
			printf("[K-%c] ", nnode.card->suit);
		}
		else if (nnode.card->value == 1)//will print the Ace value
		{
			printf("[A-%c] ", nnode.card->suit);
		}
		else//print
		{
			printf("[%d-%c] ", nnode.card->value, nnode.card->suit);
		}
}//ends prettyPrint function

////////////////////dispCardsDrawn///////////////////////////
/////////////////////////////////////////////////////////////
void dispCardsDrawn(struct bagNode removedCards[])
{
	//displays the cards that have been drawn from the linked list
	
	int i = 0;//
	
	printf("Cards Drawn:\n");
	
	while((removedCards[i].card->value != 0) && (removedCards[i].card->suit != '\0'))//loop displays all the cards
	{	
		prettyPrint(removedCards[i]);
		
		if(((i%10) == 0) && (i != 0))//newline every 10 cards for better organization
		{
			printf("\n");	
		}
		
		i = i + 1;
	}

	printf("\n\n");//Space for aesthetics in the interface
}//dispCardsDrawn ends here

/////////////////////getLastCard/////////////////////////////
/////////////////////////////////////////////////////////////
struct bagNode getLastCard(struct bagNode removedCards[])
{//begins getLastCard function
	
	/*
	find the last card that was drawn from the bag
	*/
	
	//local variables
	int i = 0;
	
	int j = 1;
	
	//function code
	
	//this loop will iterate through the array until the last card is found
	while((removedCards[j].card->value != 0) && (removedCards[j].card->suit != '\0'))
	{
		i = i + 1;
		
		j = j + 1;
	}
	
	return(removedCards[i]);
	
}//ends getLastCard function

///////////////////dispProbabilities/////////////////////////
/////////////////////////////////////////////////////////////
struct bagNode* dealer (struct bagNode* head, struct bagNode removedCards[], time_t tiempo, int *points)
{
	//this function sets up the game
	
	//local variables
	struct bagNode* pulledCard;
	
	struct bagNode ultima;
	
	//function code
	if(head == NULL)
	{
		head = fillWithCards(head); //fills Linked list with cards
	
		pulledCard = grab(head, tiempo); //grabs a card from the linked list
	
		discardBin(removedCards, pulledCard); //inserts the card into an array
	
		head = discard(head, pulledCard); //removes the card from the linked list
	}
	
	ultima = getLastCard(removedCards);//gets the last card that was taken from the bag
	
	dispCardsDrawn(removedCards); //displays all the cards that have been removed
	
	getCurrentSize(head, 1);//displays the amount of cards on the deck
	
	dispProbabilities(head, ultima.card->value);//display the probability of the next card being removed
	
	printf("Last card: ");//display the prompt for the last card drawn
	prettyPrint(ultima);//display last card drawn
	
	printf("\npoints: %d\n", *points);//displays the points
	
	return(head);
}

/////////////////////////////add//////////////////////////////////
//////////////////////////////////////////////////////////////////
struct bagNode* add(struct bagNode* head, struct bagNode removedCards[])
{//begins add function
	
	//This function will refill the deck after 34 cards have been drawn from it
	
	int size = getCurrentSize(head, 0); //gets the number of cards left in the liked list

	int i = 32; //declares and initializes i
	
	if(size == 18)//refills the deck if there are too few cards in the bag
	{
		
		printf("\nAFTER THE LAST TURN THE DECK WAS REFILLED\n\n");
		
		for(i = 32; i >= 0; i--)//this loop takes the cards from the removed cards array and puts them back into the deck
		{
			struct bagNode* temp;
		
			temp = (struct bagNode*)malloc(sizeof(struct bagNode));
			
			temp->card = (struct Card*)malloc(sizeof(struct Card));
			
			temp->card->value = removedCards[i].card->value;
			
			temp->card->suit = removedCards[i].card->suit;
			
			temp->next = head->next; //sets the removed card to what is after head
		
			head->next = temp; //sets head next to the removed card
		}//ends (i = 32; i >= 0; i--)
	
		removedCards[0].card->value = removedCards[33].card->value; //moves the last card removed to the first index

		removedCards[0].card->suit = removedCards[33].card->suit; //moves the last card removed to the first index
		
		for(i = 1; i <= 34; i++) //this loop sets all the value in the array to null or zero
		{ 
			removedCards[i].card = (struct Card*)malloc(sizeof(struct Card));
		
			removedCards[i].card->suit = '\0';
		
			removedCards[i].card->value = 0;
		}
	}//ends if (size == 18)
		
	return(head);
}//ends add function

//////////////////////guessHiOrLo/////////////////////////////////
//////////////////////////////////////////////////////////////////
struct bagNode* guessHiOrLo(struct bagNode* head, struct bagNode removedCards[], time_t tiempo, int *points, int HiOrLo)
{//guessHi begins here

	//This function will get a new card and adjust the points depeding on 
	//whether or not the the next card is higher than the last one.
	
	//Note*: the HiOrLo is the answer of whether the user guessed high or Low
	//       HiOrLo = 1 : user guessed high
	//		 HiOrLo = 0 : user guessed low
	
	//local variables
	struct bagNode* newPulledCard; //to temporarily save the most recently pulled card
	
	struct bagNode last; //to temporarily store the last card that was drawn before the guess
	
	int newValue; //value for the newPulledCard's digit

	//function code
	last = getLastCard(removedCards); // to get the last card that was drawn before the guess

	newPulledCard = grab(head, tiempo); //grabs a card from the linked list

	newValue = newPulledCard->card->value;
	
	discardBin(removedCards, newPulledCard); //inserts the card into an array

	head = discard(head, newPulledCard); //removes the card from the linked list
	
	if(last.card->value == newValue)//if the cards are the same value
	{
		printf("\nSame card\n");
	}	
	else if ((last.card->value < newValue) && (HiOrLo == 1))//if the user guessed hi and was correct
	{
		*points = *points + 1;
	}
	else if((last.card->value > newValue) && (HiOrLo == 1)) //if the user guessed hi and was wrong
	{
		*points = *points * -1;
	}
	else if ((last.card->value > newValue) && (HiOrLo == 0))//if the user guessed Low and was correct
	{
		*points = *points + 1;
	}
	else if ((last.card->value < newValue) && (HiOrLo == 0))//if the user guessed Low and was wrong
	{
		*points = *points * -1;
	}

	return(head);
}//guessHi ends here

///////////////////////guessSame//////////////////////////////////
//////////////////////////////////////////////////////////////////
struct bagNode* guessSame(struct bagNode* head, struct bagNode removedCards[], time_t tiempo, int *points)
{//guessSame begins here
	
	//This function will get a new card from the bag and adjust the
	//points depending on whether or not the user was able to guess
	//what the next card will be
	
	//local variables
	struct bagNode* newPulledCard; //to temporarily save the most recently pulled card
	
	int guessValue;
	
	int newValue;//value of the new card
	
	//function code
	newPulledCard = grab(head, tiempo); //grabs a card from the linked list
	
	newValue = newPulledCard->card->value;//gets the value of the card
	
	discardBin(removedCards, newPulledCard); //inserts the card into an array

	head = discard(head, newPulledCard); //removes the card from the linked list
	
	//prompts for and gets the user's input
	printf("What number do you believe the next card will be: \n");
	printf("(For Ace, Jack, Queen, & King input 1, 11, 12, 13 respectively)\n");
	printf("Input answer: "); 
	scanf(" %d", &guessValue);
	printf("\n\n");	
	
	if(newValue == guessValue)//adds points if answer it correct
	{
		*points = *points + 3;
	}
	else//sets up a game over if the answer is incorrect
	{
		*points = *points * -1;
	}
	
	return(head);
}//guessSame ends here

/////////////////////mainProcess//////////////////////////////////
//////////////////////////////////////////////////////////////////
struct bagNode* mainProcess(char fselect, time_t tiempo, struct bagNode* head, struct bagNode removedCards[], int *points)
{//mainProcess function begins here
	
	//processes the user's input
	
	if(fselect == '1')//user guessed high
	{
		head = guessHiOrLo(head, removedCards, tiempo, points, 1);
	}
	else if(fselect == '2')//user guessed low
	{
		head = guessHiOrLo(head, removedCards, tiempo, points, 0);
	}
	else if(fselect == '3')//user wants to guess the exact card
	{
		head = guessSame(head, removedCards, tiempo, points);
	}
	else//if there is incorrect input from the user
	{
		printf("\nIncorrect input please try again.\n");
	}
	
	head = add(head, removedCards);//checks if the deck needs to be refilled and if true it refills it
	
	dealer (head, removedCards, tiempo, points);//displays the score if the 
	
	return(head);
	
}//mainProcess function ends here