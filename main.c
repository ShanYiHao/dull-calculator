#include"header.h"
int Map[255];//建立一个符号到数的映射
double qu[100];
int ty[100],h=0;
Status conduct(char* pch,Stack *pStack){
    char c,d,*pc;
    double b;
    int f=0;//f代表栈中左括号个数
    pc=strtok(pch," ");
    while(pc!=NULL){
        c=pc[0];
        if(strlen(pc)>1)c='1';
        //printf("c=%c\n",c);
        switch(Map[c]){
        case 1://当读到数字时
            b=atof(pc);
            qu[h]=b;
            ty[h++]=1;
            break;
        case 2://当读到低级运算符时
            while(!is_empty(pStack)){
                if(!stack_get_top(pStack,&d))return (enum E)ERROR;
                if(Map[d]==4)break;
                if(!stack_pop(pStack,&d))return (enum E)ERROR;
                qu[h]=d;
                ty[h++]=2;
            }
            stack_push(pStack,&c);
            break;
        case 3://当读到高级运算符时
            while(!is_empty(pStack)){
                if(!stack_get_top(pStack,&d))return (enum E)ERROR;
                if(Map[d]==4||Map[d]==2)break;
                if(!stack_pop(pStack,&d))return (enum E)ERROR;
                qu[h]=d;
                ty[h++]=2;
            }
            stack_push(pStack,&c);
            break;
        case 4://左括号
            stack_push(pStack,&c);
            f++;
            break;
        case 5://右括号
            while(1){
            if(f<=0)return (enum E)ERROR;
            if(!stack_pop(pStack,&d))return (enum E)ERROR;
            if(Map[d]!=4){
                qu[h]=d;
                ty[h++]=2;
            }
            if(Map[d]==4)break;
            }
        case 6:continue;
        default:return (enum E)ERROR;
        }
        //printf("pc=%s\n",pc);
        pc=strtok(NULL," ");
    }
    while(!is_empty(pStack)){//最后输出掉栈里所有东西
        if(!stack_pop(pStack,&d))return (enum E)ERROR;
        qu[h]=d;
        ty[h++]=2;
    }
    return (enum E)OK;
}
void init_str(char *ch,char *ch2){
int i=0,j=0;
    while(ch[i]!='\n'){
        if(ch[i]=='+'||ch[i]=='*'||ch[i]=='/'||(ch[i]=='-'&&Map[ch[i+1]]!=1)){
            ch2[j++]=' ';
            ch2[j++]=ch[i++];
            ch2[j++]=' ';
        }
        else {
            ch2[j++]=ch[i++];
        }
    }
    ch2[j]='\0';
}
double calculate(){
    double st1[200],x1,x2;
    int h1=-1;
    for(int i=0;i<h;i++){
        if(ty[i]==1){
            //printf("st1[%d]=%lf\n",h1,qu[i]);
            st1[++h1]=qu[i];
        }
        if(ty[i]==2){
            x1=st1[h1--];
            printf("x1=%lf\n",x1);
            x2=st1[h1--];
            printf("x2=%lf\n",x2);
            switch((int)qu[i]){
            case '+':
                st1[++h1]=x1+x2;
                break;
            case '-':
                st1[++h1]=x1-x2;
                break;
            case '*':
                st1[++h1]=x1*x2;
                break;
            case '/':
                if(x2==0)printf("ERROR!\n");
                st1[++h1]=x1/x2;
                break;
            }
        }
    }
    return st1[0];
}
int main(){
    for(int i='0';i<='9';i++)Map[i]=1;
    Map['+']=2;Map['-']=2;Map['*']=3;Map['/']=3;Map['(']=4;Map[')']=5;Map[' ']=6;
    Stack S;
    Stack *pStack=&S;
    while(1){
    char ch[200],ch2[200];
    fgets(ch,sizeof(ch),stdin);
    if(ch=="quit")break;
    if(ch=="help")printf("请输入任意总长度不超过200的字符串表达式进行计算\nquit:退出程序\nhelp:查看帮助\n");
    init_str(ch,ch2);
    printf("ch2=  %s\n",ch2);
    S.size=sizeof(ch2);
    init_stack(pStack);//一定要初始化！！
    if(!conduct(ch2,pStack))printf("ERROR\n");
    printf("%lf\n",calculate());
    stack_free(pStack);
    }
    return 0;
}