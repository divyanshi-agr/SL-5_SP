#include<bits/stdc++.h>
#include <typeinfo>
using namespace std;

int line_number = 0;

struct ust_info {
    string token;
    string token_class;
    int index;
};

struct terminal {
	string indicator;
    int index;
};

struct identifier {
    string id_name;
    int index;  
};

struct literal {
    string lit_name;
    int index;
};

vector<identifier> identifier_table;
vector<literal> literal_table;
vector<ust_info> ust_table;
unordered_map<string, terminal> terminal_table;

void initialize(unordered_map<string, terminal> &trm_table)
{
    trm_table["int"] = {"key", 1};
    trm_table["float"] = {"key", 2};
    trm_table["double"] = {"key", 3};
    trm_table["char"] = {"key", 4};
    trm_table["struct"] = {"key", 5};
    trm_table["if"] = {"key", 6};
    trm_table["else"] = {"key", 7};
    trm_table["return"] = {"key", 8};
    trm_table["for"] = {"key", 9};
    trm_table["do"] = {"key", 10};
    trm_table["while"] = {"key", 11};
    trm_table["+"] = {"op", 12};
    trm_table["-"] = {"op", 13};
    trm_table["*"] = {"op", 14};
    trm_table["/"] = {"op", 15};
    trm_table["%"] = {"op", 16};
    trm_table["="] = {"op", 17};
    trm_table["<"] = {"op", 18};
    trm_table[">"] = {"op", 19};
    trm_table["!"] = {"op", 20};
    trm_table["&"] = {"op", 21};
    trm_table["|"] = {"op", 22};
    trm_table["?"] = {"op", 23};
    trm_table[":"] = {"op", 24};
    trm_table["+"] = {"op", 25};
    trm_table["^"] = {"op", 26};
    trm_table["("] = {"BC", 27};
    trm_table[")"] = {"BC", 28};
    trm_table["{"] = {"BC", 29};
    trm_table["}"] = {"BC", 30};
    trm_table[","] = {"BC", 31};
    trm_table[";"] = {"BC", 32};
}

bool isSymbol(char c)
{
    if(((int)c >= 32 && (int)c <= 47) || ((int)c >= 58 && (int)c <= 64)
        || ((int)c >= 91 && (int)c <= 96) || ((int)c >= 123 && (int)c <= 126))
    {
        return true;
    }

    return false;
}

bool isNo(char c)
{
    if(c >= '0' && c <= '9')
    {
        return true;
    }
    return false;
}

void get_words(){

    FILE* fp=fopen("sample.txt","r");
    char c;
    
    char buffer[100];
    int k=0;
    int idIndex = 1, litIndex = 1; 

    
    while((c=fgetc(fp))!=EOF){
        if(c=='\n'){
            line_number++;
            buffer[k]=0;
            k=0;
            int word_c=0;
            char ans[100];
            int p=0;
            int i=0;
            int f=0;
                    

            //check if more than 1 spaces, then take only 1 space
            while(buffer[i]){
                if(buffer[i]==' ' || buffer[i]=='\t'){
                    if(f){
                        ans[p]=' ';
                        p++;
                    }
                    while(buffer[i]==' ' || buffer[i]=='\t')
                        i++; 
                }
                else{
                    ans[p]=buffer[i];
                    f=1;
                    p++;i++;
                }
            }
            i=0;
            ans[p]=0;
            
            //buffer stores 1 line of file
            //ans stores 1 line of file without extra spaces
            if(ans[0]==' ')word_c--;
            if(ans[p-1]==' ')word_c--;  
            string temp;
            string op;
            vector<string> words;
            vector<string> lits;
            vector<string>::iterator it;
            
            //inserting word in words array
            while(ans[i]){
                //for special characters             
                if(isSymbol(ans[i]))
                {
                    //for checking literal
                    if(ans[i] == '"')
                    {
                        temp += ans[i];     //store first " in temp
                        i++;
                        while(ans[i] != '"')
                        {
                            temp += ans[i]; //store everything inside "" in temp
                            i++;
                        }
                        temp += ans[i];     //store last " in temp
                        words.push_back(temp);
                        lits.push_back(temp);
                        temp = "";
                    }
                    //if any other symbol occurs, which is not a space
                    else if(ans[i] != ' ')
                    {
                        temp += ans[i];
                        words.push_back(temp);
                        temp = "";
                    }
                    
                }
                //for number and lookahead also number
                else if(isdigit(ans[i]) && isdigit(ans[i+1]))
                {
                    temp += ans[i];
                }
                //for number and lookahead a symbol
                else if(isdigit(ans[i]) && isSymbol(ans[i+1]))
                {
                    temp += ans[i];
                    words.push_back(temp);
                    lits.push_back(temp);
                    temp = "";
                }
                //for alphabet and lookahead also alphabet
                else if(isalpha(ans[i]) && isalpha(ans[i+1]))
                    temp += ans[i];
                
                //for alphabet and lookahead not alphabet but symbol
                else if(isalpha(ans[i]) && isSymbol(ans[i+1]))
                {
                    temp += ans[i];
                    words.push_back(temp);
                    temp = "";
                }
                //if space comes
                else
                {
                    words.push_back(temp);
                    temp = "";
                }

                i++;
            }
 
            //distributing in respective tables
            for(auto x:words){
                
                //if token is a terminal, just push it in UST table
                if(terminal_table.find(x)!=terminal_table.end()){   
                   ust_table.push_back({x, "Terminal", terminal_table[x].index});
                }

                 //if the token is not found in terminal table
                if(terminal_table.find(x)==terminal_table.end()){ 

                    it = find(lits.begin(), lits.end(), x );
                    //if token is a literal
                    if (it != lits.end())
                    {
                        ust_table.push_back({x, "A Literal", litIndex});
                        literal_table.push_back({x, litIndex});
                        litIndex++;
                    }
                    //if token is an identifier
                    else {
                        ust_table.push_back({x, "Identifier", idIndex});
                        identifier_table.push_back({x, idIndex});
                        idIndex++;
                    }
                } 
            }       
    }
    else{
            if(isdigit(c) || c=='=' || isalpha(c) || c==' ' || c=='\t' || isSymbol(c)){
                buffer[k]=c;
                k++;
            }
            else{
                buffer[k]=' ';
                k++;
            }
        }
    }
    
    fclose(fp);     
}

int main() { 
   initialize(terminal_table);
    get_words();
    std::cout<<endl<<endl<<"UST TABLE ::";
    std::cout<<endl<<"----------------------------------";
    std::cout<<endl<<"TOKEN"<<"\t"<<"CLASS"<<"\t\t"<<"INDEX"<<endl;
    std::cout<<"----------------------------------"<<endl;

        for(auto x:ust_table){
            std::cout<<x.token<<"\t"<<x.token_class<<"\t"<<x.index<<endl;
        
        }

    std::cout<<endl<<endl<<"IDENTIFIER TABLE ::";
    std::cout<<endl<<"----------------------------------";
    std::cout<<endl<<"IDENTIFIER"<<"\t"<<"INDEX";
    std::cout<<endl<<"----------------------------------"<<endl;

        for(auto x:identifier_table){
            std::cout<<x.id_name<<"\t\t"<<x.index<<endl;
        }

    std::cout<<endl<<endl<<"LITERAL TABLE ::";
    std::cout<<endl<<"----------------------------------";
    std::cout<<endl<<"LITERAL"<<"\t\t"<<"INDEX"<<endl;
    std::cout<<"----------------------------------"<<endl;

        for(auto x:literal_table){
            std::cout<<x.lit_name<<"\t\t"<<x.index<<endl;
        }

    std::cout<<endl;
    return 0;
}

