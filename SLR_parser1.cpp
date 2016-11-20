#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int char_after_dot(char*);
void insert_dot(char*);
bool is_nonterminal(char);
void swap_dot_and_char(char*); 


//Contains details of a group, along with closure and goto

class group
{
    char name[10];
    char productions[100][100];
    int group_prod_count;
    char added[100];
    public:
    group()
    {
        group_prod_count = 0;
        for (int i=0; i<100; i++)
            added[i] = '0';
    }
    void set_name(char new_name[])
    {
        strcpy(name, new_name);
    }
    void add_prod(char prod[100])
    {
        strcpy(productions[group_prod_count], prod);
        group_prod_count++;
    }
    void closure(char given_prods[100][100], int given_prods_count)
    {
        //printf("\nProds are : \n");
        //for (int i=0; i<given_prods_count; i++)
        //    printf("%s", given_prods[i]);
        bool already_there;
        for (int i=0; i<group_prod_count; i++)
        {
            
            //printf("Taking %s", productions[i]);
            int next_char_loc;
            next_char_loc = char_after_dot(productions[i]);
            already_there = false;
            if (is_nonterminal(productions[i][next_char_loc]))
            {
                for (int k=0; added[k] != '0'; k++)
                {
                    if (added[k] == productions[i][next_char_loc])
                        already_there = true;
                }
                if (already_there) continue;
                for (int k=0; k<given_prods_count; k++)
                {
                    //printf("Considering %s", given_prods[k]);
                    if (productions[i][next_char_loc] == given_prods[k][0])
                    {
                        if (!strcmp(given_prods[k],productions[i])) continue;
                        add_prod(given_prods[k]);
                        group_prod_count++;
                        //printf("added : %s", given_prods[k]);
                    }
                }
                int l;
                for (l=0; added[l] != '0'; l++);
                added[l] = productions[i][next_char_loc];
                //printf("%c is new!\n", productions[i][next_char_loc]);
            }
         }
     } 
        
    void go2(char x, char gotoprods[100][100], int& num_of_prods)
    {
        int next_char_loc;
        num_of_prods = 0;
        for (int i=0; i<group_prod_count; i++)
        {
            next_char_loc = char_after_dot(productions[i]);
            if (x == productions[i][next_char_loc])
            {
                swap_dot_and_char(productions[i]);
                //printf("%s", productions[i]);
                strcpy(gotoprods[num_of_prods], productions[i]);
                num_of_prods++;
            }
        }
    }
           
    void display_prods()
    {
        printf ("Productions in %s are : \n", name);
        for (int i=0; i<group_prod_count; i++)
            printf("%s", productions[i]);
    }
};

void swap_dot_and_char(char* production)
{
    int loc;
    loc = char_after_dot(production);
    production[loc-1] = production[loc];
    production[loc] = '.';
}
    

int char_after_dot(char* production)
{
    for (int i=0; i<strlen(production); i++)
    {
        if (production[i] == '.')
            return i+1;
    }
    return -1;
}

//Takes old_prod, adds a '.' to the 3rd location, and puts it into new_prod
void insert_dot(char* old_prod)     
{
    for (int j=99; j>3; j--)
        old_prod[j] = old_prod[j-1];
    old_prod[3] = '.';
}

bool is_nonterminal(char character)
{
    if (character >= 'A' && character <= 'Z')
        return true;
    else //if (character >= 'A' && character <= 'Z')
        return false;
}

void find_characters(char characters[100], char productions[100][100], int prod_count)
{
    int i, j, k;
    bool already_there;
    for (i=0; i<100; i++)
        characters[i] = ' ';
        
    for (i=0; i<prod_count; i++)
    {
        for (j=0; productions[i][j] != '\n'; j++)
        {
            already_there = false;
            if (productions[i][j] == '=' || productions[i][j] == '.') continue;
            if (productions[i][j] == '-' && productions[i][j+1] == '>')
            {
                j++;
                continue;
            }
            for (k=0; characters[k] != ' '; k++)
            {
                if (characters[k] == productions[i][j])
                {
                    already_there = true;
                    break;
                }
            }
            if (!already_there)
                characters[k] = productions[i][j];
        }
    }
    
    
             
}

/*
//Thanks to Bazzy, http://www.cplusplus.com/forum/beginner/7777/
string convertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}
*/


int main()
{
    FILE* fd = NULL;
    char buff[100];
    char productions[100][100];
    group a[100];
    int prod_count = 0;
    
    memset(buff, 0, sizeof(buff));
    
    fd = fopen("input.txt", "r");
    
    if (fd == NULL)
    {
        printf("\nOops! There was an error opening the file\n");
        return 1;
    }
    printf("Input.txt opened!\n");
    printf("The list of production are : \n");
    while(fgets(buff, 80, fd) != NULL)
    {
        for (int i=0; i<strlen(buff); i++)
        {
            if (buff[i] == 'i' && buff[i+1] == 'd')
            {
                for (int j=i+1; j<strlen(buff); j++)
                    buff[j] = buff[j+1];
                buff[i] = '@';
            }
        }
	    printf("%s", buff);
	    strcpy(productions[prod_count], buff);
	    prod_count++;
    }
    
    for (int i=0; i<prod_count; i++)
        insert_dot(productions[i]);
     
     
    char gotoprods[100][100];
    int num_of_prods; 
    char characters[100];
    
    find_characters(characters, productions, prod_count);
    
    /*
        
    //HIGHLY EXPERIMENTAL!
    bool done = false;
    group c[100];
    a[0].add_prod(productions[0]);
    for (int group_iter = 0; !done; group_iter++)
    {
        for (int symbol_iter = 0; characters[symbol_iter] != ' ', symbol_iter++)
        {
            
        name[0] = 'I'; name[1] = '0'; name[2] = '\0';
        a[group_iter].set_name(name);
        a[group_iter].closure(productions, prod_count);
        a[group_iter].display_prods();
    } 
    */
    
    //---- Compute Closure(I0) ----
    a[0].set_name("I0");
    a[0].add_prod(productions[0]); 
    a[0].closure(productions, prod_count);    
    a[0].display_prods();
    
    //----- Compute Goto(I0) ------
    a[0].go2('T', gotoprods, num_of_prods);
    cout << "\n";
    
    //---- Add it to I1 and compute Closure(I1) ----
    a[1].set_name("I1");
    for (int i=0; i<num_of_prods; i++)
    {
        //cout << gotoprods[i];
        a[1].add_prod(gotoprods[i]);
    }
    a[1].closure(productions, prod_count);
    a[1].display_prods();
    
    a[1].go2('*', gotoprods, num_of_prods);
    cout << '\n';
    
    a[2].set_name("I2");
    for (int i=0; i<num_of_prods; i++)
    {
        //cout << gotoprods[i];
        a[2].add_prod(gotoprods[i]);
    }
    a[2].closure(productions, prod_count);
    a[2].display_prods();
    
    fclose(fd);
    return 0;
}
