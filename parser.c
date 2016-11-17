#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexical.h"
#include "parser.h"

#define tabmax 50


extern enum symbol sym;
extern int num;
extern int overzero;

/*struct table{
    char name[alfa];
    char type[alfa];
    int val;//考虑另建其他表？char 和Int值不一样
    int level;
    int tabindex;
}symtab[tabmax];*/

extern char id[alfa];

extern char ch;
int addop;
int isvoid;
void enter()//进入符号表？？？？？
{
   /* tx++;
    strcpy(table[tx].name,id);
    strcpy(table[tx].type,typ);
    case typ*/
}
/*int position(char id[alfa])
{
    int i;
    strcpy(table[0].name,id);
    i=tx;
    while(strcmp(table[0].name,id)!=0)  i--;

    return i;

}*/


void prog()
{
    printf("程序分析开始\n");
    if(sym==constsym)
    {
        getsym();
        conststate();
        printf("全局常量说明\n");
        //检测常量说明部分完成sym=int/char/void
    }
    while(sym==intsym||sym==charsym)//这里可能是变量，也可能是有值函数部分，用括号分开
    {
       /* headsym=sym;
        getsym();
        tempsym=sym;
        getsym();*/

        getsym();
        if(sym!=ident)
        {
            printf("ERROR 缺少标识符\n");
        }
        enter();
        getsym();
        if(sym==lparent)//开始进行函数分析
        {
            printf("全局变量说明\n");
            break;
        }
        else if(sym==lbrack)
        {
            getsym();
            if(sym!=numsym)
                printf("ERROR 缺少无符号整数\n");
            getsym();
            if(sym!=rbrack)
                printf("ERROR 缺少右括号\n");
            getsym();
            while(sym==comma)
            {
                getsym();
                vardef();
            }
        }
        else if(sym==comma)
        {
            while(sym==comma)
            {
                getsym();
                vardef();
            }
        }
        else if(sym==semicolon);
        else printf("非法变量定义\n");
        if(sym==semicolon)//这里采用if的原因
        {
            printf("全局变量定义\n");
            getsym();
        }
        else printf("ERROR 无效的符号\n");
    }

    printf("常量说明与变量说明完成\n");

    if(sym==voidsym)
    {
        getsym();
        getsym();
        isvoid=1;
    }


    //函数定义
    //enter();//类型保存在全局变量tp中
    //getsym();
    while(1)
    {
        if(strcmp(id,"main")==0)//到时候判断需要加上类型的
        {
            break;//此时sym=lparent
        }
        else
        {
            //getsym();  printf("声明头部\n");
           /* if(isvoid)
            {
                //getsym();//预留void fun/main的情形，小括号没有读还要读一个
                isvoid=0;
            }*/
            getsym();
            para();//左括号之前已经读了
            if(sym!=lbrace)
                printf("ERROR 缺少大括号\n");
            getsym();
            compstate();    printf("一个函数定义结束\n");
            if(sym==intsym||sym==charsym||sym==voidsym )
            {
                getsym();
                if(sym==ident)
                {
                    enter();
                    getsym();
                }
                else if(sym==mainsym)
                {
                    break;
                }
                else printf("ERROR  非法标识符\n");

            }
            else
            {
                printf("ERROR 非法类别不是void int char\n");
            }
        }
    }
    //处理main函数
    //这里判断一下类型是否标准.....
    printf("进入main函数\n");
    getsym();
    if(sym!=lparent)printf("ERROR 缺少main的左括号\n");
    getsym();
    if(sym!=rparent)printf("ERROR 缺少main的右括号\n");
    getsym();
    if(sym!=lbrace)printf("缺少左括号\n");
    getsym();
    compstate();
    printf("main函数结束\n");

    printf("程序分析结束\n");
}

void conststate()//已有const，进入函数调用
{
    constdef();
    if(sym==semicolon)
    {
        getsym();
        while(sym==constsym)
        {
            getsym();
            constdef();
            if(sym==semicolon)
                getsym();
            else
            {
                printf("ERROR 缺少分号\n");
            }
        }
        printf("常量说明\n");
    }
    else
    {
        printf("ERROR 缺少分号\n");
    }
}


void constdef()
{
    if(sym==charsym)
    {
        getsym();
        if(sym==ident)
        {
            getsym();
            if(sym==assignsym)
            {
                getsym();
                if(sym!=character)
                    printf("非法字符\n");
                getsym();
                while(sym==comma)
                {
                    getsym();
                    if(sym==ident)
                    {
                        getsym();
                        if(sym==assignsym)
                        {
                            getsym();
                        }
                        else
                        {
                            printf("ERROR 缺少等号\n");
                        }
                        if(sym!=character)
                            printf("非法字符\n");
                        getsym();
                    }
                    else
                    {
                        printf("ERROR 不是标识符\n");
                    }
                }
            }
            else
            {
                printf("缺少等号\n");
            }

        }
        else
        {
            printf("缺少标识符\n");
        }

    }
    else if(sym==intsym)//常量intsym
    {
        getsym();
        if(sym==ident)
        {
            getsym();
            if(sym==assignsym)
            {
                getsym();
                numana();
                while(sym==comma)
                {
                    getsym();
                    if(sym==ident)
                    {
                        getsym();
                        if(sym==assignsym)
                        {
                            getsym();
                            numana();
                        }
                        else
                        {
                            printf("ERROR 缺少等号\n");
                        }
                    }
                    else
                    {
                        printf("ERROR 不是标识符\n");
                    }
                }
            }
            else
            {
                printf("缺少等号\n");
            }

        }
        else
        {
            printf("缺少标识符\n");
        }
    }
    else printf("非法字符\n");
    printf("常量定义\n");
}

void varstate()//只定义一种
{
    if(sym==ident)
    {
        vardef();
        while(sym==comma)
        {
            getsym();
            vardef();
        }
    }
    else printf("ERROR  不是标识符\n");
}



void vardef()//只定义定义一项
{
    //getsym();
    if(sym!=ident)
    {
        printf("ERROR 应该是标识符\n");
    }
    enter();
    getsym();
    if(sym==lbrack)
    {
        getsym();
        if(sym!=numsym)
            printf("ERROR 应该是无符号整数\n");
        getsym();
        if(sym==rbrack)
        {
            getsym();
        }
        else printf("ERROR 缺少右括号\n");
    }
    //删去else

}

void numana()
{
    if(sym==plussym||sym==minussym)
    {
        if(sym==plussym)
        {
            addop=1;
        }
        else addop=2;
        getsym();
    }
    if(sym==numsym)
    {
        if(overzero==1)
            printf("OVERZERO\n");
        if(num==0)
        {
            if(addop!=0)
                printf("NOT ALLOW + or - operator before0\n");
        }
        if(addop==2)
            num=-num;
        getsym();
        addop=0;

    }
    else
    {
        printf("ERROR !不是整数\n");
    }
}


void compstate()
{
    if(sym==constsym)
    {
        getsym();
        conststate();
        printf("函数定义内常量说明\n");
    }
    if(sym==intsym||sym==charsym)//elete else
    {
        getsym();
        varstate();
        if(sym!=semicolon)
            printf("缺少分号\n");
        getsym();
        while(sym==intsym||sym==charsym)
        {
            getsym();
            varstate();//注意varstate最后读getsym
            if(sym!=semicolon)
                printf("ERROR 缺少分号\n");
            getsym();
        }
        if(sym==semicolon)
            getsym();
        printf("函数定义内变量说明\n");
    }//需要判断一下分号


    while(sym==ifsym||sym==whilesym||sym==lbrace||sym==ident||
          sym==printfsym||sym==scanfsym||sym==switchsym||
          sym==returnsym||sym==semicolon)//语句的头符号集
    {
        statement();//开始不加getsym
    }
    if(sym!=rbrace)
    {
        printf("ERROR 函数缺少大括号\n");
    }
    getsym();
}






//真实的statement
void statement()
{
    if(sym==ifsym)
    {
        getsym();
        conditionstate();
        printf("条件语句\n");
    }
    else if(sym==whilesym)
    {
        getsym();
        conditionstate();
        printf("循环语句\n");
    }
    else if(sym==lbrace)
    {
        getsym();
        while(sym!=rbrace)
        {
            statement();
        }
        if(sym!=rbrace)
            printf("Error rbrace\n");
        getsym();
        printf("语句列\n");
    }
    else if(sym==ident)
    {
        getsym();
        if(sym==lparent)//函数调用语句
        {
            getsym();
            if(sym!=rparent)
                valpara();
            if(sym==rparent)
            {
                getsym();

            }
            else printf("valid\n");
            printf("函数调用语句\n");
        }
        else if(sym==assignsym)
        {
            getsym();
            expression();
            if(sym!=semicolon)
                printf("ERROR semicolon\n");
            getsym();
            printf("赋值语句\n");
        }
        else if(sym==lbrack)
        {
            getsym();
            expression();
            if(sym!=rbrack)
                printf("error rbrack\n");
            getsym();
            if(sym!=assignsym)
                printf("error =\n");
            getsym();
            expression();
            if(sym!=semicolon)
                printf("缺少分号\n");
            getsym();
            printf("赋值语句\n");
        }

    }
    else if(sym==printfsym)
    {
        getsym();
        if(sym!=lparent)
            printf("缺少左括号\n");
        getsym();
        if(sym==stringg)
        {
            getsym();
            if(sym==comma)
            {
                getsym();
                expression();
                if(sym!=rparent)
                    printf("error--rpare\n");
                getsym();
            }
            else if(sym==rparent)
            {
                getsym();
            }
            else printf("invalid\n");

        }
        else
        {
            expression();
            if(sym!=rparent)
                printf("右括号 error\n");
            getsym();
        }
        if(sym!=semicolon)
            printf("error 应该是分号\n");
        getsym();

        printf("写语句\n");
    }
    else if(sym==scanfsym)
    {
        getsym();
        if(sym!=lparent)
            printf("error scanf lpare\n");
        getsym();
        if(sym==ident)
        {
            enter();
            getsym();
            while(sym==comma)
            {
                getsym();
                if(sym==ident)
                {
                    enter();
                    getsym();
                }
                else printf("error scanf ident\n");
            }
            if(sym!=rparent)
                printf("error\n");
            getsym();
            if(sym!=semicolon)
                printf("error--semi\n");
            getsym();
        }
        else printf("error scanf ident\n");

        printf("读语句\n");
    }
    else if(sym==switchsym)
    {
        getsym();
        if(sym!=lparent)
            printf("error\n");
        getsym();
        expression();
        if(sym!=rparent)
            printf("error\n");
        getsym();
        if(sym==lbrace)
        {
            getsym();
            casestate();
            while(sym==casesym)
            {
                casestate();
            }//没有default直接退出时读到的是}
            if(sym==defaultsym)
            {
                getsym();
                if(sym!=colon)
                    printf("缺少冒号\n");
                getsym();
                statement();
            }
            if(sym!=rbrace)
            {
                printf("error\n");
            }
            getsym();
        }
        printf("情况语句\n");
    }
    else if(sym==returnsym)
    {
        getsym();
        if(sym==lparent)
        {
            getsym();
            expression();
            if(sym!=rparent)
                printf("ERROR 返回表达式缺少右括号\n");
            getsym();
            if(sym!=semicolon)
                printf("error-semicolon\n");
            getsym();
        }
        else ;
        printf("返回语句\n");
    }
    else if(sym==semicolon)
    {
        getsym();
        printf("空语句\n");
    }
    else printf("非法语句\n");


}
//----state

void para()
{
    if(sym==intsym||sym==charsym)
    {
        getsym();
        if(sym==ident)
        {
            enter();
            getsym();
            while(sym==comma)
            {
                getsym();
                if(sym==intsym||sym==charsym)
                {
                    getsym();
                    if(sym==ident)
                    {
                        getsym();
                    }
                    else printf("ERROR 缺少标识符\n");

                }
                else printf("ERROR 不是类别标识符\n");
            }
            if(sym==rparent)
            {
                getsym();

            }

            else printf("ERROR 缺少右括号\n");
        }
        else
        {
            printf("ERROR 缺少标识符\n");
        }
        printf("参数表\n");

    }
    else if(sym==rparent)
    {
        getsym();
        printf("参数表\n");
    }
    else
    {
        printf("ERROR 非法的参数表\n");
    }

}

void expression()
{
    if(sym==plussym||sym==minussym)
    {
        getsym();
    }
    term();
    while(sym==plussym||sym==minussym)
    {
        getsym();
        term();
    }
    printf("表达式\n");
}

void term()
{
    factor();
    while(sym==multsym||sym==divsym)
    {
        getsym();
        factor();
    }

    printf("项\n");

}

void factor()
{
    if(sym==ident)
    {
        getsym();
        if(sym==lbrack)
        {
            getsym();
            expression();
            if(sym!=rbrack)
                printf("error\n");
            getsym();
        }
        else if(sym==lparent)//函数调用
        {
            getsym();
            if(sym!=rparent)
                valpara();

            if(sym!=rparent)
                printf("error\n");
            getsym();
        }
        else;
    }
    else if(sym==lparent)
    {
        getsym();
        expression();
        if(sym!=rparent)printf("ERROR 缺少右括号\n");
        getsym();
    }
    else if(sym==plussym||sym==minussym||sym==numsym)
    {
        numana();
    }
    else if(sym==character)
        getsym();
    else printf("非法字符\n");

    printf("因子\n");

}


void valpara()
{
    expression();
    while(sym==comma)
    {
        getsym();
        expression();
    }
}

void conditionstate()
{
    if(sym!=lparent)
        printf("条件缺少左括号\n");
    getsym();
    expression();//eql,neq,lte,gte,les,gre,
    if(sym==eql||sym==neq||sym==lte||
       sym==gte||sym==les||sym==gre)
    {
        getsym();
        expression();
    }
    else
    {
        //getsym();
    }
    if(sym!=rparent)
        printf("ERROR 缺少右括号\n");
    getsym();
    statement();


    printf("条件 语句\n");
}


void casestate()
{
    if(sym!=casesym)
        printf("应该是case\n");
    getsym();
    if(sym==character )
    {
        getsym();
       /* if(sym!=colon)
            printf("ERROR --:\n");
        getsym();
        statement();*/
    }
    else  if(sym==numsym||sym==plussym||sym==minussym)
    {
        numana();
    }
    else printf("error case value\n");
    if(sym!=colon)
        printf("缺少冒号\n");
    getsym();
    statement();
    printf("情况子语句\n");
}



