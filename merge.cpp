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

linkedList* addToBeginning(int newData, linkedList *head){
	//temporary pointer for 'juggling' nodes, also first data holder
	linkedList *temp = NULL;
	temp = (linkedList*)malloc(sizeof(linkedList));

	temp->data = newData;
	temp->next = head;
	return head = temp;
}

void addToEnd(int newData, linkedList *head){
	//This adds a node to the END of the linkedList
	linkedList *temp = NULL;
	linkedList *end = NULL;
	end = (linkedList*)malloc(sizeof(linkedList));
	temp = (linkedList*)malloc(sizeof(linkedList));

	temp = head;              // transfer the address of 'head' to 'end'
	while(temp->next!=NULL){ // go to the last node
		temp = temp->next;//tranfer the address of 'end1->next' to 'end'
  	}
	end->data = newData;                   // store data(first field)
	end->next = NULL;                  // second field will be null(last node)
	temp->next = end;
}

void addtoMid(int newData, int nodeLocation, linkedList *head){
	//inserting after 'x' number of nodes
	linkedList *temp = NULL;
	linkedList *mid = NULL;
	mid = (linkedList*)malloc(sizeof(linkedList));
	temp = (linkedList*)malloc(sizeof(linkedList));

	temp = head;
	for( int i = 1; i <= nodeLocation ; i++ ){
		if( temp == NULL ){
	    	printf("Node %i does not exist.\n", nodeLocation);
	    	break;
	    }

	    else if ( i == nodeLocation ){
	      	mid = (linkedList*)malloc(sizeof(linkedList));
	      	mid->data = newData;
	      	mid->next = temp->next;
	      	temp->next = mid;
	      	break;
	    }
	   temp = temp->next;           // go to the next node
	}
}

void outputLinkedList(linkedList* head){
	//This will output each node in the linkedList
	linkedList *end;
	end=(linkedList*)malloc(sizeof(linkedList));
  	end=head;
  	int i = 0;
	while( end!=NULL ){
		printf("\n");
		cout<< end->data<<" ";// show the data in the linked list
		cout<< end->next<<" ";
		end = end->next;   // tranfer the address of 'end->next' to 'end'
		if (i > 9){break;}
		i++;
	}
	printf("\n");
}

void moveNode(int currentLocation,int newLocation,linkedList* head){
		// create a  pointer to step through linkedList
	linkedList *stepPtr;
		// create a temporary pointer to hold current current-1's pointer
	linkedList *tempPtr;
	stepPtr = head;
		//look for currentLocation
	for( int i = 0; i <= currentLocation ; i++ ){
	    if ( i == currentLocation-2 ){ //need to stop at 2 previous for Ptr

	    	tempPtr = stepPtr->next;
	    	//update pionter to point past the one we are moving
	    	stepPtr->next = tempPtr->next;
	    	cout << tempPtr;printf("\n");
	    	cout << stepPtr->next;printf("\n");
	    	cout << stepPtr;printf("\n");

	    	//start back at the top:
	    	stepPtr = head;
	    	//look for newLocation
	    	for( int j=0; j <=  newLocation; j++){
	    		if( stepPtr->next == NULL ){
	    			printf("Node %i for newLocation does not exist. "
	    			       "Added to last location instead.\n", newLocation);
	    			tempPtr->next = NULL;
	    			stepPtr->next = tempPtr;
	    			break;
	    		}
	    		if ( j == newLocation - 2 ){
	    			tempPtr->next = stepPtr->next;
	    			stepPtr->next = tempPtr;
	    			break;
	    		}
	    		stepPtr = stepPtr->next;
	    	}
	    	break;
	    }
	    if( stepPtr == NULL ){
	    	printf("Node %i for currentLocation does not exist. "
	    	       "Exiting moveNode early.\n", currentLocation);
	    	break;
	    }
	   stepPtr = stepPtr->next;

	}
}

int main(){
	int node_number;
	//first pointer to start/header of linked list,
	//this will be used to add to the beginning of the linkedList
	linkedList *head = createLinkedList();
	head = addToBeginning(345, head);
	head = addToBeginning(346, head);
	head = addToBeginning(347, head);
	addToEnd(344, head);
	addToEnd(343, head);
	addToEnd(342, head);
	addToEnd(341, head);

	// cout << "ENTER THE NODE LOCATION TO ADD NUMBER:";
	// cin >> node_number;                   // take the node number from user
	addtoMid(5000, 3, head);



	outputLinkedList(head);

	moveNode(8,2,head);

	outputLinkedList(head);



return 0;
}
