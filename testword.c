/*lexical analysis program*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  alfa 20
#define  lmax 100  //每行最多100个字符
#define  nmax 10
#define  wordnum  13
#define  strmax  50
/*type symbol =
     ( nul,ident,number,plus,minus,times,slash,oddsym,eql,neq,lss,
       leq,gtr,geq,lparen,rparen,comma,semicolon,period,becomes,
       beginsym,endsym,ifsym,thensym,whilesym,dosym,callsym,constsym,
       varsym,procsym,readsym,writesym );*/
/*char symbol[wordnum][alfa]={"ident","number","constsym","intsym","charsym","voidsym","mainsym",
             "ifsym","whilesym","switchsym","casesym","defaultsym","scanfsym","printfsym","returnsym",
             "plus","minus","multi","div",
             "commma","semicolon","colon","lparent","rparent","lbrack","rbrack","lbrace","rbrace",
             "squote","quote","becomes","eql","neq","lte","gte","lth","gth"};*/
char ch;
char line[lmax];
int k=0;
int kk=0;
int cc=0;
int ll=0;
int symnum=0;
int strle;
char word[wordnum][alfa]={"case","char","const","default","if","int","main","printf",
               "return","scanf","switch","void","while"};
char wsym[wordnum][alfa]={"casesym","charsym","constsym","defaultsym","ifsym","intsym","mainsym","printfsym",
               "returnsym","scanfsym","switchsym","voidsym","whilesym"};
char a[alfa];
char id[alfa];
char sym[alfa];
char str[strmax];
//char temp[strmax];
FILE *fp;


void getlet()//接受一行字符
{
    if(cc==ll)
    {
        ll=0;
        cc=0;
        do
        {
            //ch=getchar();
            ch=fgetc(fp);
            line[ll++]=ch;
        }while(ch!='\n'&&ch!=EOF);

        line[ll]=' ';//将空格作为一行读入的结束标志
    }
    ch=line[cc];
    //printf("^^%d\n",cc);
    cc++;
}
//词法分析程序
int main()
{
    freopen("a.txt","w",stdout);

    fp=fopen("14081089_test.txt"  ,"r");
    if(fp==NULL)printf("ERROR: can't open the file\n");

    int i,j;
    int findwd,num;
    getlet();
    while(ch!=EOF)//ch!='.'
    {
        while(ch==' '||ch=='\n')
        {
            getlet();
        }
        if( (ch<='z'&&ch>='a')||(ch<='Z'&&ch>='A')||ch=='_' )
        {
            i=0;
            findwd=0;
            do
            {
                a[i]=ch;
                i++;
                getlet();
            }
            while( i<alfa  &&((ch<='z'&&ch>='a')||(ch<='Z'&&ch>='A')||ch=='_'
                     ||   (ch<='9'&&ch>='0')      )          );
            if(i>=kk)
                kk=i;
            a[i]='\0';
            strcpy(id,a);
            i=0;
            j=wordnum;
            while(i<j)
            {
                if(strcmp(id,word[i])==0)
                {
                    findwd=1;
                    break;
                }
                i++;
            }
            if(findwd==1)
            {
                strcpy(sym,wsym[i]);
                printf("%d %s  %s\n",++symnum,wsym[i],id);
            }
            else
            {
                strcpy(sym,"ident");
                printf("%d %s %s\n",++symnum,sym,id);
            }


        }
        else if(ch<='9'&&ch>='0')
        {
            k=0;
            num=0;
            strcpy(sym,"number");
            do
            {
                num=10*num+(ch-'0');
                k++;
                getlet();
            }
            while( ch<='9'&&ch>='0' );
            if(k>nmax)
            {
                printf("error :too long number\n ");
                exit(1);
            }
            printf("%d %s %d\n",++symnum,sym,num);

        }
        else{
            switch(ch)
            {
                case '+':{strcpy(sym,"plus");printf("%d %s +\n",++symnum,sym);getlet();break;}
                case '-':{strcpy(sym,"minus");printf("%d %s -\n",++symnum,sym);getlet();break;}
                case '*':{strcpy(sym,"mult");printf("%d %s *\n",++symnum,sym);getlet();break;}
                case '/':{strcpy(sym,"div");printf("%d %s  / \n",++symnum,sym);getlet();break;}
                case ',':{strcpy(sym,"comma");printf("%d %s ,  \n",++symnum,sym);getlet();break;}
                case ';':{strcpy(sym,"semicolon");printf("%d %s ; \n",++symnum,sym);getlet();break;}
                case ':':{strcpy(sym,"colon");printf("%d %s : \n",++symnum,sym);getlet();break;}
                case '(':{strcpy(sym,"lparent");printf("%d %s ( \n",++symnum,sym);getlet();break;}
                case ')':{strcpy(sym,"rparent");printf("%d %s ) \n",++symnum,sym);getlet();break;}
                case '[':{strcpy(sym,"lbrack");printf("%d %s [ \n",++symnum,sym);getlet();break;}
                case ']':{strcpy(sym,"rbrack");printf("%d %s ] \n",++symnum,sym);getlet();break;}
                case '{':{strcpy(sym,"lbrace");printf("%d %s { \n",++symnum,sym);getlet();break;}
                case '}':{strcpy(sym,"rbrace");printf("%d %s } \n",++symnum,sym);getlet();break;}

                case '\'':{
                    strcpy(sym,"sinquo");
                    printf("%d %s \' \n",++symnum,sym);
                    getlet();
                    if(   (ch>='a'&&ch<'z') ||(ch>='A'&&ch<='Z')||ch=='_'||ch=='-' ||ch=='+'   )
                    {
                        strcpy(sym,"character");
                        printf("%d %s %c\n",++symnum,sym,ch);
                        getlet();
                        if(ch=='\'')
                        {
                            strcpy(sym,"sinquo");
                            printf("%d %s \' \n",++symnum,sym);
                            getlet();
                        }
                        else{
                            printf("no single quote error\n");
                            exit(1);
                        }
                    }

                    break;
                }
            case '"':
                {
                    strle=0;
                    strcpy(sym,"quote");
                    printf("%d %s \" \n",++symnum,sym);
                    getlet();
                    while(ch!='"')
                    {
                        str[strle++]=ch;
                        if(strle==strmax)
                            printf("error of string\n");
                        getlet();
                    }
                    if(strlen(str)>0)
                    {
                        strcpy(sym,"string");
                        //strcpy(str,temp);
                        printf("%d %s %s \n",++symnum,sym,str);
                        memset(str,0,sizeof(str));
                    }
                    if(ch=='"')
                    {
                        strcpy(sym,"quote");
                        printf("%d %s \" \n",++symnum,sym);
                        getlet();
                    }
                    break;
                }

            case '<':
                {
                    getlet();
                    if(ch=='=')
                    {
                        strcpy(sym,"lte");
                        printf("%d %s <= \n",++symnum,sym);
                        getlet();
                    }
                    else{
                        strcpy(sym,"les");
                        printf("%d %s < \n",++symnum,sym);
                    }
                    break;
                }
                case '>':{
                    getlet();
                    if(ch=='=')
                    {
                        strcpy(sym,"gte");
                        printf("%d %s >= \n",++symnum,sym);\
                        getlet();
                    }
                    else{
                        strcpy(sym,"gre");
                        printf("%d %s > \n",++symnum,sym);
                    }
                    break;
                }
                //case '=':{strcpy(sym,"becomes");printf("%d %s =",++symnum,sym);getlet();break;}
                case '=':{
                    getlet();
                    if(ch=='=')
                    {
                        strcpy(sym,"eql");
                        printf("%d %s == \n",++symnum,sym);
                        getlet();
                    }
                    else{
                        strcpy(sym,"becomes");
                        printf("%d %s = \n",++symnum,sym);
                    }
                    break;
                }
                case '!':{
                    getlet();
                    if(ch=='=')
                    {
                        strcpy(sym,"neq");
                        printf("%d %s != \n",++symnum,sym);
                        getlet();
                    }
                    else{
                        printf("valid character! end of program\n");
                        exit(1);
                    }
                    break;
                }
                //default:{printf("error end of program\n");exit(1);}

            }
        }


    }
    return 0;
}
