#include <iostream>
#include <fstream>
using namespace std;

struct linkedList
{
	int data;
	linkedList *next;
};

linkedList* createLinkedList(){
	//first pointer to start/header of linked list,
	//this will be used to add to the beginning of the linkedList
	linkedList *head = NULL;
	return head;
}

linkedList* insertToBeginning(int newData, linkedList *head){
	//temporary pointer for 'juggling' nodes, also first data holder
	linkedList *newHead = NULL;
	newHead = (linkedList*)malloc(sizeof(linkedList));

	newHead->data = newData;
	newHead->next = head;
	return head = newHead;
}

void insertToEnd(int newData, linkedList *head){
	//This adds a node to the END of the linkedList
	linkedList *temp = NULL;
	linkedList *end = NULL;
	end = (linkedList*)malloc(sizeof(linkedList));

	temp = head;
	while(temp->next!=NULL){
		temp = temp->next;
  	}
	end->data = newData;
	end->next = NULL;
	temp->next = end;
}

void insertToMid(int newData, int nodeLocation, linkedList *head){
	//inserting after 'x' number of nodes
	linkedList *temp = NULL;
	linkedList *mid = NULL;
	mid = (linkedList*)malloc(sizeof(linkedList));
	temp = head;
	for( int i = 1; i <= nodeLocation ; i++ ){
		if( temp->next == NULL ){
	    	printf("Node %i does not exist,"
	    	       " added to end Node.\n", nodeLocation);
	    	mid->data = newData;
	    	mid->next = NULL;
	    	temp->next = mid;
	    	break;
	    }

	    else if ( i == nodeLocation ){
	      	mid->data = newData;
	      	mid->next = temp->next;
	      	temp->next = mid;
	      	break;
	    }
	   temp = temp->next;
	}
}


linkedList* insertNode(int newData, int nodeLocation, linkedList *head){
	if ( nodeLocation == 0 ){
		head = insertToBeginning(newData, head);
	}
	else if ( nodeLocation == -1 )
	{
		insertToEnd(newData, head);
	}
	else{
		insertToMid(newData, nodeLocation, head);
	}
	return head;
}

void outputLinkedList(linkedList* head){
	//This will output each node in the linkedList
	linkedList *end;
  	end=head;
  	int i = 0;
	while( end!=NULL ){
		printf("%i ",end->data );
		printf("%p\n",end->next );
		end = end->next;   // tranfer the address of 'end->next' to 'end'
		if (i > 9){break;}
		i++;
	}
	printf("\n");
}

void moveToLast(linkedList *tempPtr, linkedList *stepPtr, int newLocation){
	printf("When looking for newLocation, "
		"Node %i, reached end of linkedList, "
		"moved to last Node.\n", newLocation);
	tempPtr->next = NULL;
	stepPtr->next = tempPtr;
}

linkedList* moveFirstNode(int newLocation, linkedList* tempPtr,
                          linkedList* stepPtr, linkedList* head)
{
	tempPtr = stepPtr;
	head = stepPtr->next;
	//update pionter to point past the one we are moving
	stepPtr->next = tempPtr->next;
	//start back at the top:
	stepPtr = head;
	for( int j=0; j <=  newLocation; j++){
		if( stepPtr->next == NULL ){
			moveToLast(tempPtr, stepPtr, newLocation);
			break;
		}
		else if ( j == newLocation - 2 ){
			tempPtr->next = stepPtr->next;
			stepPtr->next = tempPtr;
			break;
		}
		stepPtr = stepPtr->next;
	}
	return head;
}

linkedList* moveMidNode(int currentLocation, int newLocation,
                        linkedList* tempPtr,linkedList* stepPtr,
                        linkedList* head )
{
	for( int i = 0; i <= currentLocation ; i++ ){
	    if( stepPtr->next == NULL ){
	    	printf("Node %i for currentLocation does not exist. "
	    	       "Exiting moveNode early.\n", currentLocation );
	    	break;
	    }
	    else if ( i == currentLocation-2 ){
	    	tempPtr = stepPtr->next;
	    	stepPtr->next = tempPtr->next;
	    	stepPtr = head;
	    	if ( newLocation == -1 ){
	    		while( stepPtr->next != NULL ){ stepPtr = stepPtr->next; }
			    moveToLast( tempPtr, stepPtr, newLocation );
			    break;
	    	}
	    	for( int j=0; j <=  newLocation; j++){
	    		if ( newLocation == 1 || newLocation == 0){
	    			tempPtr->next = head;
	    			head = tempPtr;
	    			break;
	    		}
				else if( stepPtr->next == NULL ){
			    	moveToLast( tempPtr, stepPtr, newLocation );
	    			break;
	    		}
	    		else if ( j == newLocation - 2 ){
	    			tempPtr->next = stepPtr->next;
	    			stepPtr->next = tempPtr;
	    			break;
	    		}
	    		stepPtr = stepPtr->next;
	    	}
	    	break;
	    }
		stepPtr = stepPtr->next;
	}
	return head;
}

linkedList* moveLastNode(int newLocation, linkedList* tempPtr,
                         linkedList* stepPtr, linkedList* head)
{
//need to rearrange some logic here for moving lastnode
	while( stepPtr->next != NULL ){ stepPtr = stepPtr->next; }
	tempPtr = stepPtr->next;
	stepPtr->next = NULL;
	stepPtr = head;
	if ( newLocation == -1 ){
		while( stepPtr->next != NULL ) { stepPtr = stepPtr->next; }
		moveToLast( tempPtr, stepPtr, newLocation );
	}
	for ( int j=0; j <=  newLocation; j++){
		printf("%i \n",j ); // debugging
		if ( newLocation == 1 || newLocation == 0){
			tempPtr->next = head;
			head = tempPtr;
			break;
		}
		else if ( stepPtr->next == NULL ){
	    	moveToLast( tempPtr, stepPtr, newLocation );
			break;
		}
		else if ( j == newLocation - 2 ){
			printf("asdf\n");
			tempPtr->next = NULL; //seg fault
			printf("asdf\n");
			stepPtr->next = tempPtr;
			break;
		}
		stepPtr = stepPtr->next;
	}
	return head;
}

linkedList* moveNode(int currentLocation,int newLocation,linkedList* head){
	// create a  pointer to step through linkedList
	linkedList *stepPtr;
	// create a temporary pointer to hold current current-1's pointer
	linkedList *tempPtr;
	stepPtr = head;
	//look for currentLocation
	if ( currentLocation == -1 )
	{
		head = moveLastNode(newLocation, tempPtr, stepPtr, head);
	}
	else if ( currentLocation == 0 || currentLocation == 1 ){
		head = moveFirstNode(newLocation, tempPtr, stepPtr, head);
	}
	else {
		head = moveMidNode(currentLocation, newLocation, tempPtr, stepPtr,
		                   head);
	}
	return head;
	// if (newLocation == -1)
	// {
	// 	/* code */
	// }
}

int main(){
	int node_number;
	//first pointer to start/header of linked list,
	//this will be used to add to the beginning of the linkedList
	linkedList *head = createLinkedList();
	head = insertToBeginning(345, head);
	head = insertToBeginning(346, head);
	head = insertToBeginning(347, head);
	insertToEnd(344, head);
	insertToEnd(343, head);
	insertToEnd(342, head);
	insertToEnd(341, head);

	insertToMid(5000, 5, head);

	head = insertNode(80085,7,head);

	outputLinkedList(head);

	head = moveNode(-1,3,head); //add -1 to choose last one

	outputLinkedList(head);



return 0;
}
