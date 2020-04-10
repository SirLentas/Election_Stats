#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "hashFunctions.h"
//#include "bloom.h"
#include "postlist.h"
//#include "redblack.h"
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){
    char* input;
    char* out;
    int numofupdates=5;
    for(int i=0;i<argc;i++){
      if(strcmp(argv[i],"-i")==0){
          input=argv[i+1];
      }else if(strcmp(argv[i],"-n")==0){
          numofupdates=atoi(argv[i+1]);
      }
    }
    unsigned int number_of_lines = 0;
    FILE *infile = fopen(input, "r");
    if(infile==NULL){
      cout<<"Give a valid input"<<endl;
      return 0;
    }
    int ch;

    while (EOF != (ch=getc(infile)))
        if ('\n' == ch)
            ++number_of_lines;

    fclose(infile);
    BloomFilter* b;
    b=new BloomFilter(number_of_lines);

    int changes_made=0;

    RBTree tree;
    char* id;
    char* fn;
    char* ln;
    char* ag;
    char* sx;
    char* postal;

    List list;

    infile = fopen(input, "r");
    char line[120];
    while(fgets(line, sizeof(line), infile)){
        id=strtok (line,"  ,\t");
        fn=strtok (NULL,"  ,\t");
        ln=strtok (NULL,"  ,\t");
        ag=strtok (NULL,"  ,\t");
        sx=strtok (NULL,"  ,\t");
        postal = strtok (NULL," \n\0");
        cout<<id<<" / "<<fn<<" / "<<ln<<" / "<<ag<<" / "<<sx<<" / "<<postal<<endl;

        b->add(id);

        tree.insert(id,fn,ln,ag,sx,atoi(postal));

        if(list.searchPostalCode(atoi(postal))){

            list.addInPostal(list.returnPostList(atoi(postal)),id);
        }else{
            list.addNewPostal(atoi(postal),id);
        }

    }
    fclose(infile);
    bool done=false;
    char command[120];
    char* c1;
    char* c2;
    char* c3;
    char* c4;
    char* c5;
    char* c6;
    char* c7;

    while(done==false){
        cout<<"TYPE YOUR COMMAND (TYPE help FOR MENU)"<<endl;
        fgets(command, 120, stdin);
        printf("\nCOMMAND: %s",command);
        c1=strtok(command,"  \n\0");
        if(strcmp(c1,"lbf")==0){
            c2=strtok(NULL," \n\0");
            if(b->search(c2)){
                printf("# KEY %s POSSIBLY-IN REGISTRY \n",c2);
            }
            else{
                printf("# KEY %s Not-in-LBF \n",c2);
            }
        }else if(strcmp(c1,"lrb")==0){
            c2=strtok(NULL," \n\0");
            if(tree.search2(c2)){
                printf("# KEY %s FOUND-IN-RBT\n",c2);
            }else{
                printf("# KEY %s NOT-IN-RBT\n",c2);
            }
        }else if(strcmp(c1,"ins")==0){
            c2=strtok(NULL,"  ");
            c3=strtok(NULL,"  ");
            c4=strtok(NULL,"  ");
            c5=strtok(NULL,"  ");
            c7=strtok(NULL,"  ");
            c6=strtok(NULL,"  \n\0");
            b->add(id);

            bool exist;
            exist=tree.insert(c2,c3,c4,c6,c7,atoi(c5));
            if(exist==1){
                printf("# REC-WITH %s INSERTED-IN-BF-RBT \n",c2);
            }else{
                printf("# REC-WITH %s EXISTS \n",c2);
            }

            if(list.searchPostalCode(atoi(c5))){
                list.addInPostal(list.returnPostList(atoi(c5)),c1);
            }else{
                list.addNewPostal(atoi(c5),c1);
            }
            changes_made++;
            number_of_lines++;
            if(changes_made==numofupdates){
                delete b;
                BloomFilter* b;
                b=new BloomFilter(number_of_lines);
                tree.renewBloom(b);
                changes_made=0;
            }
        }else if(strcmp(c1,"find")==0){
            c2=strtok(NULL,"  \n\0");
            if(!b->search(c2)){
                cout<<"# REC-WITH "<<c2<<" NOT-in-structs "<<endl;
            }else{
                if(tree.search2(c2)){
                    cout<<"# REC_IS: ";
                    tree.showNode(tree.search(c2));
                }else{
                    cout<<"# REC-WITH "<<c2<<" NOT-in-structs "<<endl;
                }
            }
        }else if(strcmp(c1,"delete")==0){
            c2=strtok(NULL,"  \n\0");
            if(tree.deleteByVal(c2)){
                cout<<"# DELETED "<<c2<<" FROM-structs"<<endl;
            }else{
                cout<<"- KEY "<<c2<<" NOT-in-structs "<<endl;
            }

            list.deletefromList(c2);
            changes_made++;
            number_of_lines--;
            if(changes_made==numofupdates){
                delete b;
                BloomFilter* b;
                b=new BloomFilter(number_of_lines);
                tree.renewBloom(b);
                changes_made=0;
            }
        }else if(strcmp(c1,"vote")==0){
            c2=strtok(NULL,"  \n\0");
            Node* src=tree.search(c2);
            if(strcmp(src->val,c2)==0){
                if(src->has_voted==0){
                    tree.vote(src);
                    cout<<"# REC-WITH "<<c2<<" SET-VOTED"<<endl;
                }else{
                    cout<<"# REC-WITH "<<c2<<" ALREADY-VOTED"<<endl;
                }
            }else{
                cout<<"- REC-WITH "<<c2<<" NOT_IN_STRUCTS"<<endl;
            }
        }else if(strcmp(c1,"load")==0){
            c2=strtok(NULL,"  \n\0");
            FILE* fok = fopen(c2, "r"); //load fileofkeys
            if (fok==NULL){
                cout<<"- NO FILE WITH THIS NAME"<<endl;
            }else{
                char vtrkey[10];
                char* keyv;
                while(fgets(vtrkey, sizeof(vtrkey), fok)){
                    keyv=strtok(vtrkey,"\n");
                    Node* src=tree.search(keyv);
                    if(strcmp(src->val,keyv)==0){
                        if(src->has_voted==0){
                            tree.vote(src);
                            cout<<"# REC-WITH "<<keyv<<" SET-VOTED"<<endl;
                        }else{
                            cout<<"# REC-WITH "<<keyv<<" ALREADY-VOTED"<<endl;
                        }
                    }else{
                        cout<<"- REC-WITH "<<keyv<<" NOT_IN_STRUCTS"<<endl;
                    }
                }
                fclose(fok);
            }
        }else if(strcmp(c1,"voted")==0){
            c2=strtok(NULL," \n\0");
            if(c2==NULL){
                int nov=0; //voted
                tree.hasVoted(&nov);
                cout<<"# NUMBER "<<nov<<endl;
            }else{
                int nok=0; //voted postcode
                tree.hasVotedwPC(&nok,atoi(c2));
                cout<<"# IN "<<atoi(c2)<<" VOTERS-ARE "<<nok<<endl;
            }
        }else if(strcmp(c1,"votedperpc")==0){
            list.renewNTV(tree); //votedperpc
            list.printPercentage();
        }else if(strcmp(c1,"exit")==0){
            done=true;
        }else if(strcmp(c1,"help")==0){
            cout<<"lbf key"<<endl<<"lrb key"<<endl<<"ins key firstname lastname postcode gender year"<<endl<<"find key"<<endl<<"delete key"<<endl<<"vote key"<<endl<<"load fileofkeys"<<endl<<"voted"<<endl<<"voted postcode"<<endl<<"votedperpc"<<endl<<"exit"<<endl;
        }
    }
    cout<<"======STATISTICS======="<<endl;
    list.renewNTV(tree); //votedperpc
    list.printPercentage();
    cout<<"======================="<<endl;
    FILE *output = fopen("output.txt","w");
    for(int i=0;i<argc;i++){
      if(strcmp(argv[i],"-o")==0){
          fclose(output);
          output = fopen(argv[i+1],"w");
      }
    }
    tree.printInOrder(output);
    delete b;
    tree.deletelist(); //like destructor
    fclose(output);

}
