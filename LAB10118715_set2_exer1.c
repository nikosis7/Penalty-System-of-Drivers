#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct driver{                // orizoume mia nea domh driver
          long long int adt;
          long int licence_num;
   };          
   
struct owner{                 // orizoume mia nea domh owner
          long long int adt; 
          char vehicle_num[7];
   };
   
     
struct offense{                // orizoume mia nea domh offense
          char vehicle_num[7]; 
          int penalti; 
   };
   
    
struct revoke{                // orizoume mia nea domh revoke
          long long int adt; 
          long int licence_num; 
   };  
       


void bubble_sort(struct driver *,int k);     //  Taksinomisi se fthinousa seira ws pros ta ADT toy pinaka Odigwn (Drivers)
void bubble_sort1(struct owner *, int l);   //  Taksinomisi se auksousa seira ws pros tous arithmous oximatwn toy pinaka Idioktitwn (Owners) 
int search1(struct driver *, long long int adt,int k);  // Anazitisi ston Pinaka Odigwn (Drivers) enos adt kai epistrofi ths thesis pou brethike o sygkekrimenos ADT
int search2(struct offense *,char vehicle_num[7],int m);  //  Anazitisi ston Pinaka Offenses enos Arithmou Oximatos kai epistrofi toy arithnou twn poinwn toy sygkekrimenou oximatos
int search3(struct offense *,char vehicle_num[7],int m);  // Anazitisi ston Pinaka Offenses enos Arithmou Oximatos kai epistrofi tou synolou twn poinwn toy sygkekrimenou Oximatos

void main()
{
      int i,k,l,m,choice,a,b,c;     //k= arithmos eggrafwn tou arxeiou drivers, l= arithmos eggrafwn tou arxeiou owners, m= arithmos eggrafwn tou arxeiou offenses, choice = epilogh tou xrhsth
                                    //pou dinei o xrhsths, f=elegxos gia to ean yparxei mia eggtafi mesa ston pinaka
      FILE *fp1,*fp2,*fp3,*fp4;     // oi tesseris deiktes typou arxeiou. O prwtos gia na anoiksoume gia diabasma to arxeio "drivers.txt"
      char str[20];                 // O deyteros gia na anoiskoume to arxeio "owners.txt" gia diabasma, O tritos gia na anoiksoume gia diabasma to arxeio "offenses.txt"
                                    // O tetartos gia na anoiskoume to arxeio "revokes.txt" gia eggrafi
      fp1=fopen("drivers.txt","r");
      fp2=fopen("owners.txt","r");
      fp3=fopen("offenses.txt","r");
      fp4=fopen("revoke.txt","w");
      
      //eksetazoume an den mporesei na anoiksei ta arxeia
      if(fp1==NULL)
        printf("Cannot open file \n");
      if(fp2==NULL)
        printf("Cannot open file \n");  
      if(fp3==NULL)
        printf("Cannot open file \n");  
      if(fp4==NULL)
        printf("Cannot open file \n");    
        
     // Metafora twn arxeiwn stous pinakes
      rewind(fp1);
      fscanf(fp1,"%d",&k);
      struct driver *Drivers;                 // Drivers = Pinakas eggrafwn me stoixeia odigwn
      Drivers = (struct driver *)malloc(k*sizeof(struct driver)); 
      for (i=0;i<k;i++)
	        fscanf(fp1,"%I64d,%ld",&Drivers[i].adt,&Drivers[i].licence_num);
        
      
      rewind(fp2);
      fscanf(fp2,"%d",&l);
      struct owner *Owners;                 // Owners = Pinakas eggrafwn me stoixeia idioktitwn
      Owners = (struct owner *)malloc(l*sizeof(struct owner)); 
      for (i=0;i<l;i++)
	       fscanf(fp2,"%I64d,%s",&Owners[i].adt,Owners[i].vehicle_num);
     
     
      rewind(fp3);
      fscanf(fp3,"%d",&m);
      struct offense *Offenses;            // Offenses = Pinakas eggrafwn me stoixeia poinwn
      Offenses = (struct offense *)malloc(m*sizeof(struct offense)); 
      for (i=0;i<m;i++)
           fscanf(fp3,"%s %d",Offenses[i].vehicle_num,&Offenses[i].penalti);
        
    
      do
      {
      printf("1.Screen printing of the list of numbers of vehicles sorted alphabetically \n");
      printf("2.Print on screen the list of ADT of drivers in descending order \n");
      printf("3.Print list with total penalties for every driver \n");
      printf("4.Create a text file that will contain the drivers from whom you should removed the driver because they have zero (or have become negative) their points \n");
      printf("5.Exit \n");
      
      printf("Give a choice from 1 to 5 \n");
      scanf("%d" , &choice);
      
           
      if(choice==1){           //Emfanizoume ola ta dedomena tou pinaka oximatvn, lexikografika taksinomimena
      
        bubble_sort1(Owners,l);
         for (i=0;i<l;i++)
           printf("%I64d %s\n",Owners[i].adt,Owners[i].vehicle_num);
        }
      else if(choice==2)      // Emfanizoume ola ta dedomena tou Pinaka Odhgwn taksinomena se fthinousa seira ws pros ta ADT 
      {
           
         bubble_sort(Drivers,k);
         for (i=0;i<k;i++)
           printf("%I64d %ld\n",Drivers[i].adt,Drivers[i].licence_num);
       }
       
      else if(choice==3)       //Emfanizoume thn lista twn poinwn gia kathe odigo
      { 
           
           for (i=0;i<m;i++){
             a=search1(Drivers,Owners[i].adt, k);
             b=search2(Offenses,Owners[i].vehicle_num, m);
             printf("%I64d %ld %d\n", Owners[i].adt, Drivers[a].licence_num, b);
             }
          }
      
      else if(choice==4)     //  dimourgoume to arxeio revoke.txt
      {
      	  b=0;
          for (i=0;i<l;i++)
          {
              a=search3(Offenses,Owners[i].vehicle_num, m);
              if (a<=0) b++;
           }
          struct revoke *Revokes;            // Revokes = Pinakas eggrafwn me stoixeia poinwn
          Revokes = (struct revoke *)malloc(b*sizeof(struct revoke)); 
		  rewind(fp4); 
          fprintf(fp4,"%d\n",b);
          for (i=0;i<l;i++)
          {
              a=search3(Offenses,Owners[i].vehicle_num, m);
              if (a<=0) {
                c=search1(Drivers,Owners[i].adt,k);        
                fprintf(fp4,"%I64d,%ld\n",Owners[i].adt,Drivers[c].licence_num); 
                }
           }
           free(Revokes);
      }
      
     
      }while (choice!=5);
      fclose(fp1);
      fclose(fp2);
      fclose(fp3);
      fclose(fp4);
      free(Drivers);
      free(Owners);
      free(Offenses);
      
      system("pause");
      }
      
      
     
     
void bubble_sort(struct driver *Drivers,int k){     //  Taksinomisi se fthinousa seira ws pros ta ADT toy pinaka Odigwn (Drivers) 
     int i,j;
     long long int temp1; long int temp2;
	 
  
     for (i=1; i<k ;i++)
       for (j=k-1; j>=i;j--)
         if (Drivers[j-1].adt<Drivers[j].adt){
            (temp1=Drivers[j-1].adt);
            (Drivers[j-1].adt=Drivers[j].adt);
            (Drivers[j].adt=temp1);
            (temp2=Drivers[j-1].licence_num);
            (Drivers[j-1].licence_num=Drivers[j].licence_num);
            (Drivers[j].licence_num=temp2);
            }
}
      

void bubble_sort1(struct owner *Owners, int l){    //  Taksinomisi se auksousa seira ws pros tous arithmous oximatwn toy pinaka Idioktitwn (Owners) 
     int i,j;
     long long int temp1;
     char temp2[7];
      
     for (i=1; i<l; i++)
       for (j=l-1; j>=i; j--)
         if (strcmp(Owners[j-1].vehicle_num,Owners[j].vehicle_num)>0){
            strcpy(temp2,Owners[j-1].vehicle_num);
            strcpy(Owners[j-1].vehicle_num,Owners[j].vehicle_num);
            strcpy(Owners[j].vehicle_num,temp2);
            (temp1=Owners[j-1].adt);
            (Owners[j-1].adt=Owners[j].adt);
            (Owners[j].adt=temp1);
            }
}
         
int search1(struct driver Drivers[], long long int adt,int k){  // Anazitisi ston Pinaka Odigwn (Drivers) enos adt kai epistrofi ths thesis pou brethike o sygkekrimenos ADT
             int i=0, position=0, done=0;
             while ((done==0) && (i<k))
             {
                   if (Drivers[i].adt==adt)
                	{
                           done=1;
                           position=i;
                	}
                   i++;
            }
        	return position;
}
                   
             
             
int search2(struct offense Offenses[],char vehicle_num[7],int m){  //  Anazitisi ston Pinaka Offenses enos Arithmou Oximatos kai epistrofi toy arithnou twn poinwn toy sygkekrimenou oximatos
           int i=0, s=0;
           while (i<m)
           {
                 if (strcmp(Offenses[i].vehicle_num,vehicle_num)==0)
                 {
                      s++;
                 }
                 i++;
           }
           return s;
}
                 
int search3(struct offense Offenses[],char vehicle_num[7],int m){   // Anazitisi ston Pinaka Offenses enos Arithmou Oximatos kai epistrofi tou synolou twn poinwn toy sygkekrimenou Oximatos
           int i=0,s=10;
            while (i<m)
           {
                 if (strcmp(Offenses[i].vehicle_num,vehicle_num)==0)
                 {
                      if (Offenses[i].penalti==0)
                          s--;
                      else
                          s=s-5;
                 }
                 i++;
           }
           return s;
}
      
      
      
            
      
      
      
      
      
      
      
      
            
           
                        
