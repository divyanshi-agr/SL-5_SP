#include<bits/stdc++.h>
using namespace std;

int line_number = 0;
bool isoperator(char c)
{
    return (c=='+' || c=='-' || c=='*' || c=='/' || c=='#' || c=='(' || c==')' 
    || c=='{' || c=='}' || c==';' || c=='%' || c==',' || c=='.' || c=='<' || c=='>' || c=='&');
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

void get_words(){

    FILE* fp=fopen("sample.c","r");
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
            
            //inserting word in words array
            while(ans[i]){                
                if(isSymbol(ans[i]))
                {
                    if(ans[i] != ' ')
                    {
                        temp += ans[i];
                        words.push_back(temp);
                        temp = "";
                    }
                }
                else if(!isSymbol(ans[i]) && !isSymbol(ans[i+1]))
                    temp += ans[i];

                else if(!isSymbol(ans[i]) && isSymbol(ans[i+1]))
                {
                    temp += ans[i];
                    words.push_back(temp);
                    temp = "";
                }
                else
                {
                    words.push_back(temp);
                    temp = "";
                }

                i++;
            }
                                 
            for(auto x:words){
                cout<<x<<endl;
            }
       
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
    get_words();
    return 0;
}


