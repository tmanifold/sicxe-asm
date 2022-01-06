
#include "hashmap.h"
#include <math.h>


//Function on setting the table Size.
void hashMap::setTableSize(int newSize){

    tableSize = newSize;

}

int hashMap::search_Ele(std::string looking_for)
{
	int hash = hashMap::hash(looking_for);

	hashNode* iter = table[hash];

	int val = -1;

	if (iter)
	{
		if (iter->getKey() == looking_for)
		{
			val = iter->getValue();
		}
		else
		{
			while (iter->next && iter->next->getKey() != looking_for)
			{
				iter = iter->next;
			}

			if (iter->next)
				val = iter->next->getValue();;
		}
	}

	return val;
}
/*
int hashMap::search_Ele(std::string looking_for){

    int hash = hashMap::hash(looking_for);  //hash the string we are looking to see if it exists.

    hashNode* iter = table[hash];           // iterator to step through the sublist

    int found;
    //-----------------------------------------------------------------------------------------------------------------------------//
    if(table[hash] ==  NULL)
    {
        //std::cout << "Hash does not exists"  << std::endl;
        found = -1;
    }
    else
    {
        if(iter->next == NULL)
        {
            //std::cout << "Key: " << iter->getKey() << std::endl;
            found = iter->getValue();
        }
        //std::cout << "Found: " << found << std::endl;
        //While the hash exists and there exists element after it. Iterate through it until an end is reached or conditions met.
        while(iter->next != NULL)
        {
            //if the element equals the value we are looking exists return true.
            if(iter->getKey() == looking_for)
            {
                //std::cout << "KEY: " << iter->getKey() << std::endl;
                found = iter->getValue();
            }
            else
            {
                iter = iter->next;
                //std::cout << "Key: " << iter->getKey() << std::endl;
            }
        }
    }
    //----------------------------------------------------------------------------------------------------------------------------//
    return found;
}
*/
int hashMap::hash(std::string key){

    unsigned int hash = 0;

    /*
    for(int i = 0;  i < key.length(); i++){

        hash  = hash + (int)key[i];

        //std::cout << hash << std::endl;
    }
    */

    // This formula will give positional weight to characters.
    // The idea is that this should minimize the number of collisions in the table.
    // However, this implies the table size will need to be quite large due to the
    // large initial hash value
    //
    // For example, the ADD Instruction
    //
    // Pos  | 10^2    10^1    10^0
    // Char |	A	D	D
    // ASCII|  65      68      68
    // Total| 165 +    78  +   67   =   310

    for (int i = key.length() - 1, k = 0; i >=  0; i--, k++)
    {
	    hash += (int)key[i] + pow(10, k);

	   // printf("%s: %c, %d = %d + (10^%d)\n", __func__, key[i], hash, (int)key[i], k);
    }

    return hash % tableSize;

}

void hashMap::insert(std::string key, int value){

    int offset = 0;

    int hash = this->hash(key);

    // this bucket already contains data
    if (table[hash])
    {
	   // printf ("%s: collision detected @%d, (%s 0x%02X)<-(%s, 0x%02X)\n",__func__, hash, table[hash]->getKey().c_str(), table[hash]->getValue(),key.c_str(), value);

	    hashNode* iter = table[hash]; // iterator to step through the sublist
	    //printf("iter: %s, 0x%02X)\n", iter->getKey().c_str(), iter->getValue());

	    while (iter->next)
	    {
		    iter = iter->next;
	    }

	    // at the end of the loop, iter->next will point to the last node in the sub-list, which should be NULL
	    // so, we create a new node at the position pointed to by iter

	    iter->next = new hashNode(key, value);
	    //printf("iter: %s, 0x%02X)\n", iter->getKey().c_str(), iter->getValue());
	    //printf("iter: %s, 0x%02X)\n", iter->next->getKey().c_str(), iter->next->getValue());
    }
    // no data already present, create a new node and put it at that hash value
    else
    {
	    table[hash] = new hashNode(key, value);
	    //printf("%s: created new node @%d (%s, 0x%02X)\n", __func__, hash, key.c_str(), value);
    }
/*
    // For now adding an offset is an ugly hack just to get the table to work right.
    // There is probably a more elegant solution that will allow us to better implement
    // searching, but for now this works - tdm
    while (table[(hash+offset) % tableSize])
    	offset += 1;

    table[hash+offset] = new hashNode(key, value);

    printf("%s: Inserted key: %s \t 0x%02X\t hash: %d+%d=%d\n", __func__, key.c_str(), this->table[hash+offset]->getValue(),
    	hash, offset, (hash + offset) % tableSize);
*/
}

void hashMap::print()
{
	for (int i = 0; i < tableSize; i++)
	{
		if (table[i])
		{
			printf("hashmap.%s: %d. ", __func__, i);

			hashNode* iter = table[i];
			printf("(%s,0x%02X)", iter->getKey().c_str(), iter->getValue());

			while (iter->next)
			{
				iter = iter->next;

				printf("=>(%s, 0x%02X)",
					(iter != NULL) ? iter->getKey().c_str() : "",
					(iter != NULL) ? iter->getValue() : 0x0
				);

			}

			printf("\n");
		}
	}
}

/*/
int main(){

    hashMap *basicTable = new hashMap();


    std::string key;
    int value = 0x0;


    std::cout << "OP CODE" << std::endl;
    std::cin >> key;

    std::cout << "Value" << std::endl;
    std::cin >> value;

    basicTable->insert(key, value);

    std::string inputkey;


    std::cout << "SEARCH" << std::endl;
    std::cin >> inputkey;

    basicTable->search_Ele(inputkey);


    return 0;
}
/**/
//----------------------------------------------------------------------------------------------------------------------------//

