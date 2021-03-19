#include <fstream>
#include <cstring> 
#include <iostream>  
#include <string>
using namespace std; 
  
int main() 
{ 
    fstream fp; 
    string filename;
    string line;
    int word_count, delimiters, flag=0, total;
    
    cout<<"Enter a file name: ";
    getline(cin, filename);
    
    fp.open(filename); 
    if(!fp)
    	cout<<"File does not exist!"<<endl;
  
    while (fp) 
    { 
    	word_count=0;
        total = 0;
    	delimiters=0;
        getline(fp, line);
        cout<<line<<endl;

        char* _line = const_cast<char*>(line.c_str());
        char *token = strtok(_line, " ");
        while(token ) {
             word_count++;
            cout<<token<<endl;
            token = strtok(NULL, " ");          
        }

        for(int i=0 ; i<line.length() ; i++)
		{
            
			if(line[i]==',' || line[i]=='.' || line[i]=='+' || line[i]=='-')
			{
				delimiters++;
                
			}
		}
		if(word_count==0 && delimiters==0)
	        	continue;
       
        cout<<"No. of words = "<<word_count<<endl;
        cout<<"No. of delimiters = "<<delimiters<<endl<<endl;
    } 
    
    fp.close(); 
    return 0;
}