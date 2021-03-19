#include<bits/stdc++.h>
using namespace std;

int LC=0,PTP=0,LTP=0,STP=0,line_number=0;
string int_code;

struct field{
    int machine_code;
    string Class;
    int no_of_op;
};

struct symbol{
    string name;
    int address;
    int size;
};

struct literal{
    string literal;
    int address;
};

bool isoperator(char c){
    return (c=='+' || c=='-' || c=='*' || c=='/');
}

unordered_map<string,field> m;
unordered_map<string,int> registers;
vector<symbol> symbol_table;
vector<literal> literal_table;
vector<int> pool_table;

void initialize(unordered_map<string,field> &m){
    m["STOP"]={0,"IS",0};
    m["ADD"]={1,"IS",2};
    m["SUB"]={2,"IS",2};
    m["MULT"]={3,"IS",2};
    m["MOVER"]={4,"IS",2};
    m["MOVEM"]={5,"IS",2};
    m["COMP"]={6,"IS",2};
    m["BC"]={7,"IS",2};
    m["DIV"]={8,"IS",2};
    m["READ"]={9,"IS",1};
    m["PRINT"]={10,"IS",1};
    m["START"]={1,"AD",1};
    m["END"]={2,"AD",1};
    m["LTORG"]={3,"AD",1};
    m["ORIGIN"]={4,"AD",1};
    m["EQU"]={5,"AD",1};
    m["DC"]={1,"DL",1};
    m["DS"]={2,"DL",1};
    
    registers["AREG"]=1;
    registers["BREG"]=2;
    registers["CREG"]=3;
    registers["DREG"]=4;
    //LC=100;
}

void get_words(){

    FILE* fp=fopen("inst.txt","r");
    char c;
    
    char buffer[100];
    int k=0;
    
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

            //check if more than 1 spaces, then only take 1 space
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
            
            vector<string> words;
            
            while(ans[i]){
                if(ans[i]==' '){
                    words.push_back(temp);
                    temp="";
                }
                else temp+=ans[i];
                i++;
            }
            if(temp.length()){
                words.push_back(temp);
            }
            
            vector<string> temp_words;
            for(int i=0;i<words.size();i++){
                if(words[i]!="="){
                    temp_words.push_back(words[i]);
                }
                else{
                    temp_words.push_back("="+words[i+1]);
                    i++;
                }
            }
            words=temp_words;
           
            for(auto x:words){
                cout<<x<<"  ";
            }
            
            //Entering a label in symbol table
            if(words.size()==4){
            	bool f=false;
                //check if label present in symbol table
                if(symbol_table.size()>0){
                    for(auto y:symbol_table){
                        if(y.name==words[0]){
                            f=true;
                            break;
                        }
                    }
                }
                //if label not present in symbol table, make an entry
                if(!f){
                    symbol_table.push_back({words[0],LC,1});
                }
               
            }
                
          
            for(auto x:words){
            	bool only_num=true;
                //checking if a constant is there, if yes then write (C, constant)
            	for(auto y:x){
            		if(y>='0' && y<='9'){
            			only_num=true;
            		}
            		else only_num=false;
            	}
            	if(only_num){
            		int_code+="(C "+x+")";
            		
            	}

                //if a word encountered (not a constant)
            	else{
                //special cases
		            if(line_number==1){
		                LC=stoi(words.back());
		            }
		            
                    //if LTORG encountered
		            if(x=="LTORG"){
		                //process the literals and allocate them memory
		                bool ispooldone=false;
		                for(int LTP=0;LTP<literal_table.size();LTP++){
		                    if(literal_table[LTP].address==-1){
		                    	if(!ispooldone){
		                    		pool_table.push_back(LC);
		                    	}
		                    	literal_table[LTP].address=LC++;
		                    }
		                }
		                LC--;
		                
		            }
		            
                    //if DS encountered
		            if(x=="DS"){
		            
		            	auto it=find(words.begin(),words.end(),"DS");
		            	it--;
		                for(int STP=0;STP<symbol_table.size();STP++){
		                    if(symbol_table[STP].name==*it){
		                        symbol_table[STP].address=LC;   
		                        break; 
		                    }
		                }
		            }
		            
                    //Generating intermediate code
		            if(m.find(x)!=m.end()){             //for Imperative statement (IS)
		                temp=m[x].Class+" "+to_string(m[x].machine_code);
		                int_code+="("+temp+")";     
		            }
		            else if(registers.find(x)!=registers.end()){    //for Registers (R)
		                int_code+="(R "+to_string(registers[x])+")";
		            }
		            else if(x.find("=")<x.length()){    //inserting literal in literal table
		                bool f=false;
		                if(literal_table.size()>0){
		                    for(auto y:literal_table){
		                        if(y.literal==x){
		                            f=true;
		                            break;
		                        }
		                    }
		                }
		                if(!f){
		                    literal_table.push_back({x,-1});
		                }
		                for(int LTP=0;LTP<literal_table.size();LTP++){  //for Literals (L)
		                    if(literal_table[LTP].literal==x){
		                        int_code+="(LT "+ to_string(LTP+1) +")";    
		                    }
		                }
		            }
		            else{       //inserting variable in symbol table
		                bool f=false;
		                if(symbol_table.size()>0){
		                    for(auto y:symbol_table){
		                        if(y.name==x){
		                            f=true;
		                            break;
		                        }
		                    }
		                }
		                if(!f){
		                    symbol_table.push_back({x,-1,-1});
		                }
		                for(int STP=0;STP<symbol_table.size();STP++){      //for Symbols (S)
		                    if(symbol_table[STP].name==x){
		                        int_code+="(ST "+ to_string(STP+1) +")";    
		                    }
		                }
		            }
                }
            }
            cout<<"  	"<<LC++<<"  	"<<int_code<<endl;
            int_code="";
            
        }
        else{
            if(isdigit(c) || c=='=' || isalpha(c) || c==' ' || c=='\t' || isoperator(c)){
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

int main(){ 
    initialize(m);
    get_words();
    cout<<endl<<endl<<endl;

    cout<<"LITERAL TABLE:"<<endl;
    for(auto x:literal_table){
    	cout<<x.literal<<" "<<x.address<<endl;
    }
    cout<<endl;
    cout<<"SYMBOL TABLE:"<<endl;
    for(auto x:symbol_table){
    	cout<<x.name<<" "<<x.address<<endl;
    }
}