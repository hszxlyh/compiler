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
    int val;//������������char ��Intֵ��һ��
    int level;
    int tabindex;
}symtab[tabmax];*/

extern char id[alfa];

extern char ch;
int addop;
int isvoid;
void enter()//������ű���������
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
    printf("���������ʼ\n");
    if(sym==constsym)
    {
        getsym();
        conststate();
        printf("ȫ�ֳ���˵��\n");
        //��ⳣ��˵���������sym=int/char/void
    }
    while(sym==intsym||sym==charsym)//��������Ǳ�����Ҳ��������ֵ�������֣������ŷֿ�
    {
       /* headsym=sym;
        getsym();
        tempsym=sym;
        getsym();*/

        getsym();
        if(sym!=ident)
        {
            printf("ERROR ȱ�ٱ�ʶ��\n");
        }
        enter();
        getsym();
        if(sym==lparent)//��ʼ���к�������
        {
            printf("ȫ�ֱ���˵��\n");
            break;
        }
        else if(sym==lbrack)
        {
            getsym();
            if(sym!=numsym)
                printf("ERROR ȱ���޷�������\n");
            getsym();
            if(sym!=rbrack)
                printf("ERROR ȱ��������\n");
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
        else printf("�Ƿ���������\n");
        if(sym==semicolon)//�������if��ԭ��
        {
            printf("ȫ�ֱ�������\n");
            getsym();
        }
        else printf("ERROR ��Ч�ķ���\n");
    }

    printf("����˵�������˵�����\n");

    if(sym==voidsym)
    {
        getsym();
        getsym();
        isvoid=1;
    }


    //��������
    //enter();//���ͱ�����ȫ�ֱ���tp��
    //getsym();
    while(1)
    {
        if(strcmp(id,"main")==0)//��ʱ���ж���Ҫ�������͵�
        {
            break;//��ʱsym=lparent
        }
        else
        {
            //getsym();  printf("����ͷ��\n");
           /* if(isvoid)
            {
                //getsym();//Ԥ��void fun/main�����Σ�С����û�ж���Ҫ��һ��
                isvoid=0;
            }*/
            getsym();
            para();//������֮ǰ�Ѿ�����
            if(sym!=lbrace)
                printf("ERROR ȱ�ٴ�����\n");
            getsym();
            compstate();    printf("һ�������������\n");
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
                else printf("ERROR  �Ƿ���ʶ��\n");

            }
            else
            {
                printf("ERROR �Ƿ������void int char\n");
            }
        }
    }
    //����main����
    //�����ж�һ�������Ƿ��׼.....
    printf("����main����\n");
    getsym();
    if(sym!=lparent)printf("ERROR ȱ��main��������\n");
    getsym();
    if(sym!=rparent)printf("ERROR ȱ��main��������\n");
    getsym();
    if(sym!=lbrace)printf("ȱ��������\n");
    getsym();
    compstate();
    printf("main��������\n");

    printf("�����������\n");
}

void conststate()//����const�����뺯������
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
                printf("ERROR ȱ�ٷֺ�\n");
            }
        }
        printf("����˵��\n");
    }
    else
    {
        printf("ERROR ȱ�ٷֺ�\n");
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
                    printf("�Ƿ��ַ�\n");
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
                            printf("ERROR ȱ�ٵȺ�\n");
                        }
                        if(sym!=character)
                            printf("�Ƿ��ַ�\n");
                        getsym();
                    }
                    else
                    {
                        printf("ERROR ���Ǳ�ʶ��\n");
                    }
                }
            }
            else
            {
                printf("ȱ�ٵȺ�\n");
            }

        }
        else
        {
            printf("ȱ�ٱ�ʶ��\n");
        }

    }
    else if(sym==intsym)//����intsym
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
                            printf("ERROR ȱ�ٵȺ�\n");
                        }
                    }
                    else
                    {
                        printf("ERROR ���Ǳ�ʶ��\n");
                    }
                }
            }
            else
            {
                printf("ȱ�ٵȺ�\n");
            }

        }
        else
        {
            printf("ȱ�ٱ�ʶ��\n");
        }
    }
    else printf("�Ƿ��ַ�\n");
    printf("��������\n");
}

void varstate()//ֻ����һ��
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
    else printf("ERROR  ���Ǳ�ʶ��\n");
}



void vardef()//ֻ���嶨��һ��
{
    //getsym();
    if(sym!=ident)
    {
        printf("ERROR Ӧ���Ǳ�ʶ��\n");
    }
    enter();
    getsym();
    if(sym==lbrack)
    {
        getsym();
        if(sym!=numsym)
            printf("ERROR Ӧ�����޷�������\n");
        getsym();
        if(sym==rbrack)
        {
            getsym();
        }
        else printf("ERROR ȱ��������\n");
    }
    //ɾȥelse

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
        printf("ERROR !��������\n");
    }
}


void compstate()
{
    if(sym==constsym)
    {
        getsym();
        conststate();
        printf("���������ڳ���˵��\n");
    }
    if(sym==intsym||sym==charsym)//elete else
    {
        getsym();
        varstate();
        if(sym!=semicolon)
            printf("ȱ�ٷֺ�\n");
        getsym();
        while(sym==intsym||sym==charsym)
        {
            getsym();
            varstate();//ע��varstate����getsym
            if(sym!=semicolon)
                printf("ERROR ȱ�ٷֺ�\n");
            getsym();
        }
        if(sym==semicolon)
            getsym();
        printf("���������ڱ���˵��\n");
    }//��Ҫ�ж�һ�·ֺ�


    while(sym==ifsym||sym==whilesym||sym==lbrace||sym==ident||
          sym==printfsym||sym==scanfsym||sym==switchsym||
          sym==returnsym||sym==semicolon)//����ͷ���ż�
    {
        statement();//��ʼ����getsym
    }
    if(sym!=rbrace)
    {
        printf("ERROR ����ȱ�ٴ�����\n");
    }
    getsym();
}






//��ʵ��statement
void statement()
{
    if(sym==ifsym)
    {
        getsym();
        conditionstate();
        printf("�������\n");
    }
    else if(sym==whilesym)
    {
        getsym();
        conditionstate();
        printf("ѭ�����\n");
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
        printf("�����\n");
    }
    else if(sym==ident)
    {
        getsym();
        if(sym==lparent)//�����������
        {
            getsym();
            if(sym!=rparent)
                valpara();
            if(sym==rparent)
            {
                getsym();

            }
            else printf("valid\n");
            printf("�����������\n");
        }
        else if(sym==assignsym)
        {
            getsym();
            expression();
            if(sym!=semicolon)
                printf("ERROR semicolon\n");
            getsym();
            printf("��ֵ���\n");
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
                printf("ȱ�ٷֺ�\n");
            getsym();
            printf("��ֵ���\n");
        }

    }
    else if(sym==printfsym)
    {
        getsym();
        if(sym!=lparent)
            printf("ȱ��������\n");
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
                printf("������ error\n");
            getsym();
        }
        if(sym!=semicolon)
            printf("error Ӧ���Ƿֺ�\n");
        getsym();

        printf("д���\n");
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

        printf("�����\n");
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
            }//û��defaultֱ���˳�ʱ��������}
            if(sym==defaultsym)
            {
                getsym();
                if(sym!=colon)
                    printf("ȱ��ð��\n");
                getsym();
                statement();
            }
            if(sym!=rbrace)
            {
                printf("error\n");
            }
            getsym();
        }
        printf("������\n");
    }
    else if(sym==returnsym)
    {
        getsym();
        if(sym==lparent)
        {
            getsym();
            expression();
            if(sym!=rparent)
                printf("ERROR ���ر��ʽȱ��������\n");
            getsym();
            if(sym!=semicolon)
                printf("error-semicolon\n");
            getsym();
        }
        else ;
        printf("�������\n");
    }
    else if(sym==semicolon)
    {
        getsym();
        printf("�����\n");
    }
    else printf("�Ƿ����\n");


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
                    else printf("ERROR ȱ�ٱ�ʶ��\n");

                }
                else printf("ERROR ��������ʶ��\n");
            }
            if(sym==rparent)
            {
                getsym();

            }

            else printf("ERROR ȱ��������\n");
        }
        else
        {
            printf("ERROR ȱ�ٱ�ʶ��\n");
        }
        printf("������\n");

    }
    else if(sym==rparent)
    {
        getsym();
        printf("������\n");
    }
    else
    {
        printf("ERROR �Ƿ��Ĳ�����\n");
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
    printf("���ʽ\n");
}

void term()
{
    factor();
    while(sym==multsym||sym==divsym)
    {
        getsym();
        factor();
    }

    printf("��\n");

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
        else if(sym==lparent)//��������
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
        if(sym!=rparent)printf("ERROR ȱ��������\n");
        getsym();
    }
    else if(sym==plussym||sym==minussym||sym==numsym)
    {
        numana();
    }
    else if(sym==character)
        getsym();
    else printf("�Ƿ��ַ�\n");

    printf("����\n");

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
        printf("����ȱ��������\n");
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
        printf("ERROR ȱ��������\n");
    getsym();
    statement();


    printf("���� ���\n");
}


void casestate()
{
    if(sym!=casesym)
        printf("Ӧ����case\n");
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
        printf("ȱ��ð��\n");
    getsym();
    statement();
    printf("��������\n");
}



