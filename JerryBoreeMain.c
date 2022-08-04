#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"
#include "HashTable.h"
#include "KeyValuePair.h"
#include "MultiValueHashTable.h"
#include "LinkedList.h"
#include "Jerry.h"


int main(int argc, char* argv[]) {

	//Data

	//save planets
	int numOfPlanets=atoi(argv[1]);
	Planet** Planets= (Planet**)malloc(numOfPlanets*sizeof(Planet*));
	if (Planets == NULL)
	{
		printf("Memory Problem\n");
		return 1;
	}

	//save jerries
	//hash size - size of what (?)
	int hashsize = 1;
	hashTable jerries = createHashTable((CopyFunction)CopyFunction_Jerry,(FreeFunction)free_str,(PrintFunction) displayValue,(CopyFunction)CopyFunction_Jerry, (FreeFunction)FreeFunction_jerry, (PrintFunction)displayValue,(EqualFunction)EqualFunction_id, (TransformIntoNumberFunction)TransformIntoNumberFunction_jerry,hashsize);
    if(jerries == NULL){
        printf("Memory Problem\n");
        destroyHashTable(jerries);
        free(Planets);
        return 1;
    }
	//each node->element is char* of the jerry id by the order it get's into the system
	LinkedList jerries_by_order1 = createLinkedList ((CopyFunction)CopyFunction_Jerry,(FreeFunction)free_str,(PrintFunction)jerryprint,(EqualFunction)EqualFunction_id, (EqualFunction) EqualFunction_id);
    if(jerries_by_order1 == NULL){
        destroyHashTable(jerries);
        printf("Memory Problem\n");
        destroyList(jerries_by_order1);
        free(Planets);
        return 1;
    }


	// multihash for attributes
	MultiValueHashTable mvt = createMultiValueHashTable(hashsize, (EqualFunction)EqualFunction_jerry_attribute, (FreeFunction) destroyList, (FreeFunction) free_str, (EqualFunction) EqualFunction_id, (CopyFunction) CopyFunction_Jerry, (EqualFunction) EqualFunction_id, (TransformIntoNumberFunction) TransformIntoNumberFunction_jerry, (PrintFunction) jerryprint);
    if(mvt ==NULL){
        destroyHashTable(jerries);
        printf("Memory Problem\n");
        destroyList(jerries_by_order1);
        free(Planets);
        return 1;
    }

	//read file
	char * filelocation=argv[2];
	FILE* f =fopen(filelocation, "r");
	char line[100];
	fgets(line, 300, f);
	fgets(line, 300, f);


	//insert planets
	char* Pname;
	char* numchar;
	float x,y,z;
	Planet* newP=NULL;
	int num=0;
	for(int i=0; i<numOfPlanets;i++){
		Pname= strtok(line, ",");
		numchar= strtok(NULL, ",");
		x= atof(numchar);
		numchar= strtok(NULL, ",");
		y= atof(numchar);
		numchar= strtok(NULL, ",");
		z= atof(numchar);
		newP= initplanet(Pname, x, y, z);

        if(newP ==NULL){
            destroyHashTable(jerries);
            printf("Memory Problem\n");
            destroyList(jerries_by_order1);
            for(int i=0; i<num ; i++){
                free(Planets[i]->Planet_name);
                free(Planets[i]);
            }
            destroyMultiValueHashTable(mvt);
            free(Planets);
            return 1;
        }

		Planets[num]= newP;
		num++;
		fgets(line, 300, f);
	}


	//insert jerries
	fgets(line, 300, f);
	Origin* newOr=NULL;
	int happy;
	float value;
	PhysicalCharacteristics* ps;
	char *id,*origin, *planet, *happiness, *att, *val;
	Jerry* newJ;
	while (!feof(f)){
		id = strtok(line, ",");
		origin= strtok(NULL,",");
		planet=strtok(NULL,",");
		happiness= strtok(NULL,",");
		happy= atoi(happiness);
		for(int j=0; j<numOfPlanets;j++){
			if(strcmp(planet, Planets[j]->Planet_name)==0){
				newP=Planets[j];
			}
		}
		newOr=initorigin(origin, newP);

        if(newOr ==NULL){
            destroyHashTable(jerries);
            printf("Memory Problem\n");
            destroyList(jerries_by_order1);
            for(int i=0; i<num ; i++){
                free(Planets[i]->Planet_name);
                free(Planets[i]);
            }
            free(Planets);
            destroyMultiValueHashTable(mvt);
            return 1;
        }

		newJ=initjerry(id, happy, newOr);

        if(newOr ==NULL){
            destroyHashTable(jerries);
            printf("Memory Problem\n");
            destroyList(jerries_by_order1);
            for(int i=0; i<num ; i++){
                free(Planets[i]->Planet_name);
                free(Planets[i]);
            }
            free(Planets);
            free(newOr->origin_name);
            free(newOr);
            free(newJ);
            destroyMultiValueHashTable(mvt);
            return 1;
        }

		char* jid2 = (char*)malloc(sizeof(char)*strlen(id)+1);
        if(jid2 ==NULL){
            destroyHashTable(jerries);
            printf("Memory Problem\n");
            destroyList(jerries_by_order1);
            for(int i=0; i<num ; i++){
                free(Planets[i]->Planet_name);
                free(Planets[i]);
            }
            free(Planets);
            free(newOr->origin_name);
            free(newOr);
            FreeFunction_jerry(newJ);
            destroyMultiValueHashTable(mvt);
            return 1;
        }
		strcpy(jid2,newJ->Jerry_id);

		if( addToHashTable(jerries,(Element) jid2,(Element)newJ)==failure)
			return -1;

		char* Jid1= (char*) malloc (strlen(newJ->Jerry_id) +1);

        if(jid2 ==NULL){
            destroyHashTable(jerries);
            printf("Memory Problem\n");
            destroyList(jerries_by_order1);
            for(int i=0; i<num ; i++){
                free(Planets[i]->Planet_name);
                free(Planets[i]);
            }
            free(Planets);
            free(newOr->origin_name);
            free(newOr);
            FreeFunction_jerry(newJ);
            destroyMultiValueHashTable(mvt);
            return 1;
        }

		strcpy(Jid1,  newJ->Jerry_id);
		if ( appendNode(jerries_by_order1, Jid1)==failure)
			return -1;


        char* ab;
        fgets(line, 300, f);
		while(line[0]=='\t'){
			att=strtok(line, "\t");
			att=strtok(att, ":");
			val = strtok(NULL,":");
			value = atof(val);
			ps= initattribute(att, value);
			addattribute(newJ, ps);

			ab = (char*)malloc(sizeof(char)*strlen(att)+1);
			if(ab==NULL){
                destroyHashTable(jerries);
                printf("Memory Problem\n");
                destroyList(jerries_by_order1);
                for(int i=0; i<num ; i++){
                    free(Planets[i]->Planet_name);
                    free(Planets[i]);
                }
                free(Planets);
                destroyMultiValueHashTable(mvt);
                return 1;
			}


			strcpy(ab,att);
			char* Jid= (char*) malloc (strlen(newJ->Jerry_id) +1);
            if(Jid==NULL){
                destroyHashTable(jerries);
                printf("Memory Problem\n");
                destroyList(jerries_by_order1);
                for(int i=0; i<num ; i++){
                    free(Planets[i]->Planet_name);
                    free(Planets[i]);
                }
                free(Planets);
                destroyMultiValueHashTable(mvt);
                free(Jid);
                return 1;
            }
			strcpy(Jid,  newJ->Jerry_id);
			if (addToMultiValueHashTable(mvt,(Element)Jid,(Element)ab) == failure)
				return 1;



			if(fgets(line, 300, f)==NULL){
				break;
			}
		}

	}
		fclose(f);


		char ch='0', ch7='0', ch8='0';
		char id1[300], planet1[300], dim1[300], phisical1[300], number[300];
		int foundplanet, num8, planetposition, newJhappiness, totaljerries,happiness6, strenth, diffrence, minDiference, Valnum, index5,numofattributes, ind, my_ind;
		Origin* newOrigin;
		Jerry* newJerry, *j;
		Element temp_elem, temp_elem2, temp_elem3,temp_elem4;
		char* temp_id, *temp_id1;
		PhysicalCharacteristics* att1;
		char* addAtribute,*id8,*idnew,*id72;
		LinkedList list;
		while( ch != '9' ) {
			  printf("Welcome Rick, what are your Jerry's needs today ? \n");
		      printf("1 : Take this Jerry away from me \n");
		      printf("2 : I think I remember something about my Jerry \n");
		      printf("3 : Oh wait. That can't be right \n");
		      printf("4 : I guess I will take back my Jerry now \n");
		      printf("5 : I can't find my Jerry. Just give me a similar one \n");
		      printf("6 : I lost a bet. Give me your saddest Jerry \n");
		      printf("7 : Show me what you got \n");
		      printf("8 : Let the Jerries play \n");
		      printf("9 : I had enough. Close this place \n");
		      scanf(" %s", &ch );
		      switch( ch )
		      {
		      	  case'1':
		      		  printf("What is your Jerry's ID ? \n");
		      		  scanf("%s", id1 );
		      		  temp_elem = lookupInHashTable(jerries,id1);
		      		  if (temp_elem != NULL)
		      		  {
		      			printf("Rick did you forgot ? you already left him here ! \n");
		      					break;
		      		  }
		      		  else
		      		  {
		      			printf("What planet is your Jerry from ? \n");
		      			scanf("%s", planet1);
		      			foundplanet = 0;
		      			for(int i=0; i<numOfPlanets;i++)
		      			{
		      				if(strcmp(planet1, Planets[i]->Planet_name)==0)
		      				{
		      					foundplanet = 1;
		      					planetposition = i;
		      					break;
		      				}
		      		    }

		      			if (foundplanet == 0){
	      					printf("%s is not a known planet ! \n",planet1);
	      					break;
		      			}
		      		  }
		      		  //check dimension
		      		  printf("What is your Jerry's dimension ? \n");
		      		  scanf("%s", dim1 );

		      		  //check happiness
		      		  printf("How happy is your Jerry now ? \n");
		      		  scanf("%d", &newJhappiness );
		      		  newOrigin = initorigin(dim1, Planets[planetposition]);
		      		  if (newOrigin == NULL)
		      			  return -1;
		      		  newJerry = initjerry (id1,newJhappiness, newOrigin);
		      		  if (newJerry == NULL)
		      			  return -1;
		      		  idnew = (char*)malloc(sizeof(char)*strlen(id1)+1);
					  if(idnew==NULL){
						  return -1;
					  }
					  strcpy(idnew, id1);
		      		  if( addToHashTable(jerries,(Element) idnew,(Element)newJerry)==failure)
		      			  return -1;
		      		  idnew = (char*)malloc(sizeof(char)*strlen(id1)+1);
		      		  if(idnew==NULL){
		      			  return -1;
		      		  }
		      		  strcpy(idnew, id1);
		      		  if ( appendNode(jerries_by_order1, idnew)==failure)
		      			return -1;

		      		  jerryprint((Element)newJerry);
		      		  break;

		      	  case '2':
		      		printf("What is your Jerry's ID ? \n");
					  scanf("%s", id1 );
					  j = (Jerry*) lookupInHashTable(jerries, (Element)id1);
					  if(j ==NULL){
						  printf("Rick this Jerry is not in the daycare ! \n");
						  break;
					  }
					  printf("What physical characteristic can you add to Jerry - %s ? \n", id1);
					  scanf("%s", phisical1 );
					  if(is_attribute_exist(j, phisical1)){
						  printf("The information about his %s already available to the daycare ! \n",phisical1);
						  break;
					  }
					  printf("What is the value of his %s ? \n", phisical1);
					  scanf("%s", number );
					  strenth = atof(number);
					  printf("%s : \n", phisical1);
					  att1 = initattribute(phisical1, strenth);
					  addAtribute = (char*)malloc(sizeof(char)*strlen(phisical1)+1);
					  if(addAtribute==NULL){
						  return -1;
					  }
					  strcpy(addAtribute,phisical1);
					  id8 = (char*)malloc(sizeof(char)*strlen(id1)+1);
					  if(id8==NULL){
						  return -1;
					  }
					  strcpy(id8,id1);


					  if(addattribute(j, att1)==false){
						  break;
					  }
					if(addToMultiValueHashTable(mvt, id8, addAtribute)==failure){
							return -1;}

						list= lookupInMultiValueHashTable(mvt, phisical1);
						totaljerries = getLengthList(list);

						for (int i=0;i<totaljerries;i++)
						{
							temp_elem = getDataByIndex(list,i); //temp is char*
							temp_elem2 = lookupInHashTable(jerries,temp_elem); //temp is Jerry*
							jerryprint(temp_elem2);
						}

					  break;


		      	  case '3':
		      		  printf("What is your Jerry's ID ? \n");
		      		  scanf("%s", id1 );
		      		  j = (Jerry*) lookupInHashTable(jerries, (Element)id1);
		      		  if(j ==NULL){
						  printf("Rick this Jerry is not in the daycare ! \n");
						  break;
					  }
		      		  printf("What physical characteristic do you want to remove from Jerry - %s ? \n",id1);
		      		  scanf("%s", phisical1 );
		      		  if(is_attribute_exist(j, phisical1)==false){
						  printf("The information about his %s not available to the daycare ! \n",phisical1);
						  break;
					  }
		      		  if(removeFromMultiValueHashTable(mvt,phisical1,id1)==failure){
		      			  return -1;
		      		  }
		      		  removeattribute(j, phisical1);
		      		  jerryprint(j);
		      		  break;

		      	  case '4':
		      		  printf("What is your Jerry's ID ? \n");
		      		  scanf("%s", id1 );
		      		  temp_elem = lookupInHashTable(jerries,id1);
		      		  if (temp_elem == NULL)
		      		  {
		      			printf("Rick this Jerry is not in the daycare ! \n");
		      			break;
		      		  }
		      		  j =(Jerry*)temp_elem;
			      		for(int i=0; i< j->numofattributes; i++){
			      			if(removeFromMultiValueHashTable(mvt,j->attributes[i]->name, j->Jerry_id)==failure){
			      				return -1;
			      			}
			      		}
		      			if ( remove_by_element(jerries_by_order1, id1)==failure)
		      				return -1;
		      		  	if (removeFromHashTable(jerries,(Element)id1) == failure)
		      		  		return -1;


		      		  printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
		      		  break;

		      	case '5':
		      		printf("What do you remember about your Jerry ? \n");
		      		scanf("%s", phisical1 );
		      		list = lookupInMultiValueHashTable(mvt, phisical1);
		      		if(phisical1 == NULL || list == NULL){
		      			printf("Rick we can not help you - we do not know any Jerry's %s ! \n", phisical1);
		      			break;
		      		}
		      		printf("What do you remember about the value of his %s ? \n", phisical1);
		      		scanf("%s", number );
		      		Valnum = atoi(number);
		      		totaljerries = getLengthList(list);
		      		index5=0;
		      		j =(Jerry*) lookupInHashTable(jerries,(getDataByIndex(list,0)));
		      		minDiference = Valnum - getAttributeValue(j, phisical1);
		      		if (minDiference<0){
		      			minDiference = minDiference *(-1);
		      		}
		      		for(int i=1; i < totaljerries; i++){
		      			j =(Jerry*) lookupInHashTable(jerries,(getDataByIndex(list,i)));
		      			diffrence= Valnum - getAttributeValue(j, phisical1);
		      			if(diffrence<0){
		      				diffrence = diffrence *(-1);
		      			}
		      			if(diffrence< minDiference){
		      				minDiference = diffrence;
		      				index5 = i;
		      			}
		      		}
		      		j =(Jerry*) lookupInHashTable(jerries,(getDataByIndex(list,index5)));
		      		printf("Rick this is the most suitable Jerry we found : \n");
		      		if(jerryprint(lookupInHashTable(jerries,(getDataByIndex(list,index5))))==false){
		      			return -1;
		      		}
		      		printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
		      		if(remove_by_element(jerries_by_order1, j->Jerry_id)==failure){
		      			return -1;
		      		}
		      		for(int i=0; i< j->numofattributes; i++){
		      			if(removeFromMultiValueHashTable(mvt,j->attributes[i]->name, j->Jerry_id)==failure){
		      				return -1;
		      			}
		      		}

		      		if(removeFromHashTable(jerries, j->Jerry_id)== failure){
		      			return -1;
		      		}
		      		break;



		      	case '6':
		      		totaljerries = getLengthList(jerries_by_order1);
		      		if (totaljerries == 0)
		      		{
		      			printf ("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
		      			break;
		      		}
		      		happiness6=101;
		      		for (int i=0;i<totaljerries;i++)
		      		{
		      			temp_elem = getDataByIndex(jerries_by_order1,i); //temp is char*
			      		temp_elem2 = lookupInHashTable(jerries,temp_elem); //temp is Jerry*
			      		if (gethappiness(temp_elem2) < happiness6)
			      		{
			      			happiness6 = gethappiness(temp_elem2);
			      			temp_elem3 = temp_elem;
			      			temp_elem4 = temp_elem2;
			      		}
		      		}

		      		printf ("Rick this is the most suitable Jerry we found : \n");
		      		jerryprint(temp_elem4);
		      		printf ("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");

		      		j= (Jerry*) temp_elem4;
		      		for(int i=0; i< j->numofattributes; i++){
		      			if(removeFromMultiValueHashTable(mvt,j->attributes[i]->name, j->Jerry_id)==failure){
		      				return -1;
		      			}
		      		}

	      		  	if (removeFromHashTable(jerries,(Element)temp_elem3) == failure)
	      		  		return -1;
	      			if ( remove_by_element(jerries_by_order1, temp_elem3)==failure)
	      				return -1;

		      		break;



		      	case '7':

						while( ch7 != '3' ) {
						printf ("What information do you want to know ? \n");
						printf ("1 : All Jerries \n");
						printf ("2 : All Jerries by physical characteristics \n");
						printf ("3 : All known planets \n");
						scanf(" %s", &ch7 );
						switch( ch7 )
							  {
								  case'1':
									  totaljerries = getLengthList(jerries_by_order1);
							      		if (totaljerries == 0)
							      		{
							      			printf ("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
							      			break;
							      		}
							      		for (int i=0;i<totaljerries;i++)
							      		{
							      			temp_elem = getDataByIndex(jerries_by_order1,i); //temp is char*
								      		temp_elem2 = lookupInHashTable(jerries,temp_elem); //temp is Jerry*
								      		jerryprint(temp_elem2);

							      		}

										  break;

								  case'2':
									  	printf("What physical characteristics ? \n");
										scanf("%s", phisical1 );
										list= lookupInMultiValueHashTable(mvt, phisical1);
										totaljerries = getLengthList(list);
										if (totaljerries == 0)
										{
											printf("Rick we can not help you - we do not know any Jerry's %s ! \n", phisical1);
											break;
										}
										if (totaljerries != 0)
											printf("%s : \n");
										for (int i=0;i<totaljerries;i++)
										{
											temp_elem = getDataByIndex(list,i); //temp is char*
											temp_elem2 = lookupInHashTable(jerries,temp_elem); //temp is Jerry*
											jerryprint(temp_elem2);
										}

										break;
								  case'3':
										  for(int i=0; i<numOfPlanets;i++){
											  planetprint(Planets[i]);
										  }
										  break;
								  default:
									  printf("Rick this option is not known to the daycare ! \n");
									  break;
							  }
							break;

						}


							break; // case 7 break







		      	case '8':
		      		ch8='0';
		      		totaljerries = getLengthList(jerries_by_order1);
		      		if (totaljerries == 0)
		      		{
		      			printf ("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
		      			break;
		      		}
		      		while( ch8 != '3' ) {
					printf ("What activity do you want the Jerries to partake in ? \n");
					printf ("1 : Interact with fake Beth \n");
					printf ("2 : Play golf \n");
					printf ("3 : Adjust the picture settings on the TV \n");
					scanf(" %s", &ch8 );
					switch( ch8 )
					  {

						  case'1':

					      		for (int i=0;i<totaljerries;i++)
					      		{
									temp_elem = getDataByIndex(jerries_by_order1,i); //temp is char*
									temp_elem2 = lookupInHashTable(jerries,temp_elem); //temp is Jerry*
									if (addhappiness(temp_elem2,1) == failure)
										return -1;
								}

					      		printf ("The activity is now over ! \n");
					      		for (int i=0;i<totaljerries;i++)
					      		{
					      			temp_elem = getDataByIndex(jerries_by_order1,i); //temp is char*
						      		temp_elem2 = lookupInHashTable(jerries,temp_elem); //temp is Jerry*
						      		jerryprint(temp_elem2);

					      		}
								break;

						  case'2':
								for (int i=0;i<totaljerries;i++)
								{
									temp_elem = getDataByIndex(jerries_by_order1,i); //temp is char*
									temp_elem2 = lookupInHashTable(jerries,temp_elem); //temp is Jerry*
									if (addhappiness(temp_elem2,2) == failure)
										return -1;
								}

					      		printf ("The activity is now over ! \n");
					      		for (int i=0;i<totaljerries;i++)
					      		{
					      			temp_elem = getDataByIndex(jerries_by_order1,i); //temp is char*
						      		temp_elem2 = lookupInHashTable(jerries,temp_elem); //temp is Jerry*
						      		jerryprint(temp_elem2);

					      		}
								break;


						  case'3':
								for (int i=0;i<totaljerries;i++)
								{
									temp_elem = getDataByIndex(jerries_by_order1,i); //temp is char*
									temp_elem2 = lookupInHashTable(jerries,temp_elem); //temp is Jerry*
									if (addhappiness(temp_elem2,3) == failure)
										return -1;
								}

					      		printf ("The activity is now over ! \n");
					      		for (int i=0;i<totaljerries;i++)
					      		{
					      			temp_elem = getDataByIndex(jerries_by_order1,i); //temp is char*
						      		temp_elem2 = lookupInHashTable(jerries,temp_elem); //temp is Jerry*
						      		jerryprint(temp_elem2);

					      		}
								break;





						  default:
							  printf("Rick this option is not known to the daycare ! \n");
							  break;
					  }
					break;


		      		}


		    		break; // case 8 break



				  case '9':
					  for(int i=0; i<numOfPlanets; i++){
						  free(Planets[i]->Planet_name);
						  free(Planets[i]);
					  }
					  free(Planets);
					  destroyMultiValueHashTable(mvt);
					  destroyList(jerries_by_order1);
					  destroyHashTable(jerries);
					  printf("The daycare is now clean and close ! \n");
					  break;



		      	  default:
		      		  printf("Rick this option is not known to the daycare ! \n");
		      	      break;
		      }//switchcase }
		}//while }
}
